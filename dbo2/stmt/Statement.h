#ifndef _DBO_STMT_STATEMENT_H_
#define _DBO_STMT_STATEMENT_H_

#include <string>
#include <vector>

namespace dbo2 {
class connection ;

namespace stmt {

class Statement
{
public:
	Statement(connection& conn, std::string sql) ;

	Statement(connection& conn, std::string name, std::string sql) ;

	/**
	 * Bind a null value
	 */
	void bind() ;

	/**
	 * Bind a string value
	 */
	void bind(const std::string& value) ;

	/**
	 * Bind a binary value
	 */
	void bind(const std::vector<unsigned char>& value) ;

	/**
	 * Prepare the statement and registers it
	 * Uses the bound values to chose the right oids
	 * NULL values binds to OIDDefault
	 * bind count must be equal to request parameters number
	 */
	void prepare() ;

	/**
	 * Clear the statement bound values
	 */
	void reset() ;

	/**
	 * Execute the prepared statement
	 */
	void execute() ;

	const std::string name() { return name_ ; }
	const std::string sql() { return sql_ ; }
	bool prepared() { return prepared_ ; }
protected:
	enum OIDEnum
	{
		OIDDefault = 0,
		OIDBytea = 17
	} ;

	connection& conn_ ;
	std::string name_ ;
	std::string sql_ ;
	bool prepared_ ;
	size_t paramCount_ ;

	std::vector<unsigned int> oids_ ;

	std::vector<std::string> svalues_ ;	// RAII version of values
	std::vector<const char*> values_ ;
	std::vector<int> lengths_ ;
	std::vector<int> formats_ ;

	std::string convertToNumberedPlaceholders(const std::string& sql) ;
	size_t getNumberPlaceHolders(const std::string& sql) ;
} ;

}}

#endif