#ifndef _DBO_ACTION_SQLINSERT_HPP_
#define _DBO_ACTION_SQLINSERT_HPP_

namespace dbo {

namespace action {

struct SqlInsertData {
	int params_ ;
	std::stringstream sql_ ;

	SqlInsertData()
		:	params_(0)
	{}
} ;

template<class C>
class SqlInsert
{
public:
	using IdType = typename traits::dbo_traits<C>::IdType ;

	SqlInsert(std::shared_ptr<mapping::Mapping<C>> mapping, stmt::PreparedStatement& stmt) ;

	void visit() ;

	template<typename V> void act(const mapping::FieldRef<V>& field) ;

	template<typename V> void actId(V& value, const std::string& name, int size) ;
	template<class D> void actId(ptr<D>& value, const std::string& name, int size, int fkConstraints) ;

	template <class D> void actPtr(const mapping::PtrRef<D>& field) ;
	template <class D> void actWeakPtr(const mapping::WeakRef<D>& field) ;

	template<class D> void actCollection(const mapping::CollectionRef<D>& field) ;

	connection& conn() { return stmt_.conn() ; } ;
private:
	std::shared_ptr<mapping::Mapping<C>> mapping_ ;
	stmt::PreparedStatement& stmt_ ;

	std::shared_ptr<SqlInsertData> data_ ;

	SqlInsert(std::shared_ptr<mapping::Mapping<C>> mapping, stmt::PreparedStatement& stmt, std::shared_ptr<SqlInsertData> data) ;

	template <class D> friend class SqlInsert ;
};

}}

#endif
