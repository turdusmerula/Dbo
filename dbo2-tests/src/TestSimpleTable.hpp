#include <gtest/gtest.h>

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include <dbo2/dbo.hpp>

extern std::string connection ;

// ----------------------------------------------------------------------------
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
	boost::gregorian::date date_value ;		//date only
	boost::posix_time::ptime ptime_value ;	// date time
	boost::posix_time::time_duration time_duration_value ;	// time only
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
		dbo2::field(a, string_value, "string_value", 100) ;
		dbo2::field(a, longlong_value, "longlong_value") ;
		dbo2::field(a, int_value, "int_value") ;
		dbo2::field(a, long_value, "long_value") ;
		dbo2::field(a, short_value, "short_value") ;
		dbo2::field(a, bool_value, "bool_value") ;
		dbo2::field(a, float_value, "float_value") ;
		dbo2::field(a, double_value, "double_value") ;
		dbo2::field(a, size_t_value, "size_t_value") ;
		dbo2::field(a, date_value, "date_value") ;
		dbo2::field(a, ptime_value, "ptime_value") ;
		dbo2::field(a, time_duration_value, "time_duration_value") ;
		dbo2::field(a, vector_value, "vector_value") ;
		dbo2::field(a, optional_value, "optional_value") ;
		dbo2::field(a, enum_value, "enum_value") ;
	}
} ;
// ----------------------------------------------------------------------------


// The fixture for testing class Database.
class TestSimpleTable : public ::testing::Test
{
public:
	static void SetUpTestCase()
	{
		db.connect(connection) ;
		db.mapClass<aSimpleTable>("asimple") ;
		db.createTables() ;
		db.showQueries(true) ;
		db.showBindings(true) ;
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
	static dbo2::connection db ;
} ;
dbo2::connection TestSimpleTable::db ;



TEST_F(TestSimpleTable, TestSql) {
	dbo2::connection db ;

	db.mapClass<aSimpleTable>("simple") ;

	std::cout << db.tableCreationSql() << std::endl ;
	db.debug() ;
}

TEST_F(TestSimpleTable, TestPtr) {
	dbo2::ptr<aSimpleTable> p ;
	dbo2::ptr<aSimpleTable> q ;

	ASSERT_FALSE(p) ;

	p = dbo2::make_ptr<aSimpleTable>() ;
	ASSERT_TRUE((bool)p) ;

	q = p ;
	ASSERT_TRUE((bool)q) ;
}

TEST_F(TestSimpleTable, TestInsert) {

	dbo2::ptr<aSimpleTable> p=dbo2::make_ptr<aSimpleTable>() ;
	p->string_value = "toto" ;
	p->longlong_value = 10 ;
	p->int_value = 20 ;
	p->long_value = 30 ;
	p->short_value = 40 ;
	p->bool_value = true ;
	p->float_value = 40.5 ;
	p->double_value = 50.6e15 ;
	p->size_t_value = 60 ;
	p->date_value = boost::gregorian::day_clock::local_day() ;
	p->ptime_value = boost::posix_time::second_clock::local_time() ;
	p->time_duration_value = boost::posix_time::second_clock::local_time().time_of_day() ;
	p->vector_value = std::vector<unsigned char>({0, 1, 2, 3, 4, 'a', 'b', 'c'}) ;
	// p->optional_value left null
	p->enum_value = aSimpleTable::Enum2 ;

	db.insert(p) ;

	ASSERT_TRUE( p.id()!=dbo2::traits::dbo_traits<aSimpleTable>::invalidId() ) ;
}

TEST_F(TestSimpleTable, TestLoad) {

	dbo2::ptr<aSimpleTable> p=dbo2::make_ptr<aSimpleTable>() ;
	p->string_value = "toto" ;
	p->longlong_value = 10 ;
	p->int_value = 20 ;
	p->long_value = 30 ;
	p->short_value = 40 ;
	p->bool_value = true ;
	p->float_value = 40.5 ;
	p->double_value = 50.6e15 ;
	p->size_t_value = 60 ;
	p->date_value = boost::gregorian::day_clock::local_day() ;
	p->ptime_value = boost::posix_time::second_clock::local_time() ;
	p->time_duration_value = boost::posix_time::second_clock::local_time().time_of_day() ;
	p->vector_value = std::vector<unsigned char>({0, 1, 2, 3, 4, 'a', 'b', 'c'}) ;
	// p->optional_value left null
	p->enum_value = aSimpleTable::Enum2 ;

	ASSERT_NO_THROW( db.insert(p) ) ;

	dbo2::ptr<aSimpleTable> q=db.load<aSimpleTable>(p.id()) ;
	ASSERT_TRUE( q->string_value=="toto" ) ;
	ASSERT_TRUE( q->longlong_value==10 ) ;
	ASSERT_TRUE( q->int_value==20 ) ;
	ASSERT_TRUE( q->long_value==30 ) ;
	ASSERT_TRUE( q->short_value==40 ) ;
	ASSERT_TRUE( q->bool_value==true ) ;
	ASSERT_TRUE( q->float_value==40.5 ) ;
	ASSERT_TRUE( q->double_value==50.6e15 ) ;
	ASSERT_TRUE( q->size_t_value==60 ) ;
	ASSERT_TRUE( q->date_value==p->date_value ) ;
	ASSERT_TRUE( q->ptime_value==p->ptime_value ) ;
	ASSERT_TRUE( q->time_duration_value==p->time_duration_value ) ;
	ASSERT_TRUE( q->vector_value==std::vector<unsigned char>({0, 1, 2, 3, 4, 'a', 'b', 'c'}) ) ;
	ASSERT_TRUE( q->optional_value.is_initialized()==false ) ;
	ASSERT_TRUE( q->enum_value==aSimpleTable::Enum2 ) ;

}

TEST_F(TestSimpleTable, TestUpdate) {

	dbo2::ptr<aSimpleTable> p=dbo2::make_ptr<aSimpleTable>() ;
	p->string_value = "toto" ;
	p->longlong_value = 10 ;
	p->int_value = 20 ;
	p->long_value = 30 ;
	p->bool_value = true ;
	p->float_value = 40.5 ;
	p->double_value = 50.6e15 ;
	p->size_t_value = 60 ;
	p->date_value = boost::gregorian::day_clock::local_day() ;
	p->ptime_value = boost::posix_time::second_clock::local_time() ;
	p->time_duration_value = boost::posix_time::second_clock::local_time().time_of_day() ;
	p->vector_value = std::vector<unsigned char>({0, 1, 2, 3, 4, 'a', 'b', 'c'}) ;
	// p->optional_value left null
	p->enum_value = aSimpleTable::Enum2 ;

	ASSERT_NO_THROW( db.insert(p) ) ;

	dbo2::ptr<aSimpleTable> q=db.load<aSimpleTable>(p.id()) ;

	q->string_value = "tata" ;
	q->longlong_value = 100 ;
	q->optional_value = 25 ;

//	ASSERT_NO_THROW( db.update(q) ) ;
	db.update(q) ;

	dbo2::ptr<aSimpleTable> r=db.load<aSimpleTable>(p.id()) ;

	ASSERT_TRUE( r->string_value=="tata" ) ;
	ASSERT_TRUE( r->longlong_value==100 ) ;
	ASSERT_TRUE( r->optional_value==25 ) ;

}
