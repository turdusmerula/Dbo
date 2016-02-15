#include "dbo2/stmt/Statement.h"

#include "dbo2/connection.h"

#include <boost/lexical_cast.hpp>

#include <iostream>

#include <postgresql/libpq-fe.h>

using namespace dbo2::stmt ;

Statement::Statement(connection& conn, std::string sql)
	:	conn_(conn),
		prepared_(false)
{
    name_ = boost::lexical_cast<std::string>(std::hash<std::string>{}(sql)) ;
    sql_ = convertToNumberedPlaceholders(sql) ;
    paramCount_ = getNumberPlaceHolders(sql_) ;
    std::cout << "stmt " << name_ << "  " << paramCount_ << ": " << sql << std::endl ;
}

Statement::Statement(connection& conn, std::string name, std::string sql)
	:	conn_(conn),
		name_(name),
		prepared_(false)
{
    sql_ = convertToNumberedPlaceholders(sql) ;
    paramCount_ = getNumberPlaceHolders(sql_) ;
    std::cout << "stmt " << name_ << "  " << paramCount_ << ": " << sql << std::endl ;
}

void Statement::bind()
{
	if(prepared_==false)
		oids_.push_back(OIDDefault) ;

	svalues_.push_back("") ;
	values_.push_back(nullptr) ;
	lengths_.push_back(0) ;
	formats_.push_back(0) ;

	std::cout << "bind null" << std::endl ;
}

void Statement::bind(const std::string& value)
{
	if(prepared_==false)
		oids_.push_back(OIDDefault) ;

	svalues_.push_back(value) ;
	values_.push_back(svalues_.back().c_str()) ;
	lengths_.push_back(0) ;
	formats_.push_back(0) ;

	std::cout << "bind " << value << std::endl ;
}

void Statement::bind(const std::vector<unsigned char>& value)
{
	if(prepared_==false)
		oids_.push_back(OIDBytea) ;

	svalues_.push_back("") ;
	values_.push_back(svalues_.back().c_str()) ;
	lengths_.push_back(value.size()) ;
	formats_.push_back(1) ;

	std::string p=values_.back() ;
	p.resize(value.size()) ;
	if(value.size()>0)
		memcpy(const_cast<char *>(p.data()), &(*value.begin()), value.size()) ;

	std::cout << "bind binary" << std::endl ;
}

void Statement::prepare()
{
	if(conn_.connected()==false)
		Exception("Database not connected") ;

	std::cout << paramCount_ << "   " << oids_.size() << " " << sql_ << std::endl ;

	if(oids_.size()!=paramCount_)
		throw Exception("Statement types not properly set") ;

	auto result=PQprepare(conn_.conn_, name_.c_str(), sql_.c_str(), oids_.size(), (Oid *)oids_.data()) ;
	auto err=PQresultStatus(result) ;
	if(err!=PGRES_COMMAND_OK && err!=PGRES_TUPLES_OK)
	{
		PQclear(result) ;
		throw Exception(PQerrorMessage(conn_.conn_)) ;
	}
	PQclear(result) ;

	prepared_ = true ;
}

void Statement::reset()
{
	values_.clear() ;
	svalues_.clear() ;
	lengths_.clear() ;
	formats_.clear() ;
}

void Statement::execute()
{
	if(svalues_.size()<paramCount_)
		throw Exception("Statement missing bindings values") ;

	auto result=PQexecPrepared(conn_.conn_, name_.c_str(), oids_.size(), values_.data(), lengths_.data(), formats_.data(), 0) ;
	auto err=PQresultStatus(result) ;
	if(err!=PGRES_COMMAND_OK && err!=PGRES_TUPLES_OK)
	{
		PQclear(result) ;
		throw Exception(PQerrorMessage(conn_.conn_)) ;
	}
	PQclear(result) ;
}

std::string Statement::convertToNumberedPlaceholders(const std::string& sql)
{
	std::stringstream result ;

	enum
	{
		Statement,
		SQuote,
		DQuote
	} state = Statement ;
	int placeholder=1 ;

	for(unsigned i=0 ; i<sql.length() ; ++i)
	{
		switch(state)
		{
		case Statement:
			if(sql[i]=='\'')
				state = SQuote ;
			else if(sql[i]=='"')
				state = DQuote ;
			else if(sql[i]=='?')
			{
				result << '$' << placeholder++ ;
				continue ;
			}
			break ;
		case SQuote:
			if(sql[i]=='\'')
			{
				if(i+1==sql.length())
					state = Statement ;
				else if(sql[i+1]=='\'')
				{
					result << sql[i] ;
					++i ; // skip to next
				}
				else
					state = Statement ;
			}
			break ;
		case DQuote:
			if(sql[i]=='"')
				state = Statement ;
			break ;
		}
		result << sql[i] ;
	}

	return result.str() ;
}

size_t Statement::getNumberPlaceHolders(const std::string& sql)
{
	std::map<std::string, std::string> placeholders ;

	for(size_t i=0 ; i<sql.length() ; ++i)
	{
		if(sql[i]=='$')
		{
			std::string placeholder="$" ;
			for(size_t j=i+1 ; j<sql.length() && isdigit(sql[j]) ; j++)
			{
				if(isdigit(sql[j]))
				{
					placeholder += j ;
					i++ ;
				}
			}
			if(placeholder.size()>1)
				placeholders[placeholder] = placeholder ;
		}
	}

	return placeholders.size() ;
}