#include <gtest/gtest.h>

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

extern wtdbo::backend::Postgres* db ;

// The fixture for testing class Database.
class TestSimpleTable : public ::testing::Test
{
public:
	static void SetUpTestCase()
	{
	}

	static void TearDownTestCase()
	{

	}

	virtual void SetUp()
	{
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown()
	{
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Foo.
} ;

class aSimpleTable
{
public:
	std::string string_value ;
	long long  longlong_value ;
	int int_value ;
	long long_value ;
	short short_value ;
	bool bool_value ;
	float float_value ;
	double double_value ;
	size_t size_t_value ;
	boost::posix_time::ptime ptime_value ;
	boost::posix_time::time_duration time_duration_value ;
	std::vector<unsigned char> vector_value ;

	boost::optional<int> optional_value ;

	enum TypeEnum {
		Enum0 = 0,
		Enum1 = 1,
		Enum2 = 2
	};
	TypeEnum enum_value ;

	template<class Action>
	void persist(Action& a)
	{
		wtdbo::field(a, string_value, "string_value", 100) ;
		wtdbo::field(a, longlong_value, "longlong_value") ;
		wtdbo::field(a, int_value, "int_value") ;
		wtdbo::field(a, long_value, "long_value") ;
		wtdbo::field(a, short_value, "short_value") ;
		wtdbo::field(a, bool_value, "bool_value") ;
		wtdbo::field(a, float_value, "float_value") ;
		wtdbo::field(a, double_value, "double_value") ;
		wtdbo::field(a, size_t_value, "size_t_value") ;
		wtdbo::field(a, ptime_value, "ptime_value") ;
		wtdbo::field(a, time_duration_value, "time_duration_value") ;
		wtdbo::field(a, vector_value, "vector_value") ;
		wtdbo::field(a, optional_value, "optional_value") ;
		wtdbo::field(a, enum_value, "enum_value") ;
	}
} ;


TEST_F(TestSimpleTable, TestSql) {
	wtdbo::Session session ;
	session.setConnection(*db) ;

	session.mapClass<aSimpleTable>("simple") ;

	std::cout << session.tableCreationSql() << std::endl ;
}
