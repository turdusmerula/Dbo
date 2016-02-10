/*
 * Copyright (C) 2009 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef _DBO_TRAITS_STDSQLTRAITS_H_
#define _DBO_TRAITS_STDSQLTRAITS_H_

#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_enum.hpp>

#include <dbo2/traits/sql_value_traits.hpp>

namespace dbo2 {
namespace traits {

template<>
struct sql_value_traits<std::string, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(const std::string& v, SqlStatement *statement, int column, int size) ;
//	static bool read(std::string& v, SqlStatement *statement, int column, int size) ;
} ;

template<>
struct sql_value_traits<long long, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(long long v, SqlStatement *statement, int column, int size);
//	static bool read(long long& v, SqlStatement *statement, int column, int size);
} ;

template<>
struct sql_value_traits<int, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(int v, SqlStatement *statement, int column, int size);
//	static bool read(int& v, SqlStatement *statement, int column, int size);
} ;

template<>
struct sql_value_traits<long, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(long v, SqlStatement *statement, int column, int size);
//	static bool read(long& v, SqlStatement *statement, int column, int size);
} ;

template<>
struct sql_value_traits<short, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(short v, SqlStatement *statement, int column, int size);
//	static bool read(short& v, SqlStatement *statement, int column, int size);
} ;

template<>
struct sql_value_traits<bool, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(bool v, SqlStatement *statement, int column, int size);
//	static bool read(bool& v, SqlStatement *statement, int column, int size);
} ;

template<>
struct sql_value_traits<float, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(float v, SqlStatement *statement, int column, int size);
//	static bool read(float& v, SqlStatement *statement, int column, int size);
} ;

template<>
struct sql_value_traits<double, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(double v, SqlStatement *statement, int column, int size);
//	static bool read(double& v, SqlStatement *statement, int column, int size);
} ;

template<>
struct sql_value_traits<size_t, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(size_t v, SqlStatement *statement, int column, int size);
//	static bool read(size_t& v, SqlStatement *statement, int column, int size);
};

template<>
struct sql_value_traits<boost::posix_time::ptime, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(const boost::posix_time::ptime& v, SqlStatement *statement, int column, int size);
//	static bool read(boost::posix_time::ptime& v, SqlStatement *statement, int column, int size);
} ;

template<>
struct sql_value_traits<boost::posix_time::time_duration, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(const boost::posix_time::time_duration& v, SqlStatement *statement, int column, int size);
//	static bool read(boost::posix_time::time_duration& v, SqlStatement *statement, int column, int size);
} ;

template<typename Enum>
struct sql_value_traits<Enum, typename boost::enable_if<boost::is_enum<Enum>>::type> : public sql_value_traits<int>
{
//	static void bind(Enum v, SqlStatement *statement, int column, int size)
//	{
//		sql_value_traits<int>::bind(static_cast<int>(v), statement, column, size);
//	}
//
//	static bool read(Enum& v, SqlStatement *statement, int column, int size)
//	{
//		return sql_value_traits<int>::read(reinterpret_cast<int&>(v), statement, column, size);
//	}
} ;

template<>
struct sql_value_traits<std::vector<unsigned char>, void>
{
	static const bool specialized=true ;

	static std::string type(int size) ;
//	static void bind(const std::vector<unsigned char>& v, SqlStatement *statement, int column, int size);
//	static bool read(std::vector<unsigned char>& v, SqlStatement *statement, int column, int size);
};

template<typename T>
struct sql_value_traits<boost::optional<T>, void>
{
	static const bool specialized=true ;

	static std::string type(int size)
	{
		std::string nested = sql_value_traits<T>::type(size) ;
		if(nested.length()>9 && nested.substr(nested.length()-9)==" not null")
			return nested.substr(0, nested.length()-9) ;
		else
			return nested ;
	}

//	static void bind(const boost::optional<T>& v, SqlStatement *statement, int column, int size)
//	{
//		if(v)
//			sql_value_traits<T>::bind(v.get(), statement, column, size);
//		else
//			statement->bindNull(column);
//	}
//
//	static bool read(boost::optional<T>& v, SqlStatement *statement, int column, int size)
//	{
//		T result;
//		if(sql_value_traits<T>::read(result, statement, column, size))
//		{
//			v = result;
//			return true;
//		}
//		else
//		{
//			v = boost::optional<T>();
//			return false;
//		}
//	}
};

}}

#endif
