namespace dbo2 {

//template <class Result>
//query<Result>& query<Result>::select(const std::string& condition)
//{
//	sql_ += " where "+condition ;
//	return *this ;
//}
//
//template <class Result>
//query<Result>& query<Result>::where(const std::string& condition)
//{
//	sql_ += " where "+condition ;
//	return *this ;
//}
//
//template <class Result>
//query<Result>& query<Result>::orderBy(const std::string& fieldName)
//{
//	sql_ += " order by "+fieldname ;
//	return *this ;
//}
//
//template <class Result>
//query<Result>& query<Result>::groupBy(const std::string& fields)
//{
//	sql_ += " group by "+fields ;
//	return *this ;
//}
//
//template <class Result>
//query<Result>& query<Result>::having(const std::string& fields)
//{
//	return *this ;
//}
//
//template <class Result>
//query<Result>& query<Result>::offset(int count)
//{
//	return *this ;
//}
//
//template <class Result>
//query<Result>& query<Result>::offset(const std::string& count)
//{
//	return *this ;
//}
//
//template <class Result>
//query<Result>& query<Result>::limit(int count)
//{
//	return *this ;
//}
//
//template <class Result>
//query<Result>& query<Result>::limit(const std::string& count)
//{
//	return *this ;
//}

template <class C>
query& query::read(ptr<C>& ptr)
{
	if(hasrow_==false)
	{
		std::stringstream ss ;
		ss << "Query error: no data to fetch" ;
		ss << " -> " << sql_ ;
		throw Exception(ss.str()) ;
	}

	auto mapping=conn_->getMapping<C>() ;

	ptr = dbo2::make_ptr<C>() ;
	action::LoadDb<C> action(ptr, mapping, stmt_) ;
	action.visit() ;

	return *this ;
}

template <class C>
query& query::bind(const C& value)
{

}

}
