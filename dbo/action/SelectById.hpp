#ifndef _DBO_ACTION_SELECTBYID_HPP_
#define _DBO_ACTION_SELECTBYID_HPP_

namespace dbo {

namespace action {

enum class SelectByIdState {
	PreparingStatement,
	Selecting,
	ReadingResult
} ;

template<class C>
class SelectById
{
public:
	using IdType = typename traits::dbo_traits<C>::IdType ;

	SelectById(ptr<C> ptr, std::shared_ptr<mapping::Mapping<C>> mapping, stmt::PreparedStatement& stmt) ;
	SelectById(ptr<C> ptr, IdType id, std::shared_ptr<mapping::Mapping<C>> mapping, stmt::PreparedStatement& stmt) ;

	void visit() ;

	template<typename V> void act(const mapping::FieldRef<V>& field) ;

	template<typename V> void actId(V& value, const std::string& name, int size) ;
	template<class D> void actId(ptr<D>& value, const std::string& name, int size, int fkConstraints) ;

	template <class D> void actPtr(const mapping::PtrRef<D>& field) ;
	template <class D> void actWeakPtr(const mapping::WeakRef<D>& field) ;

	template<class D> void actCollection(const mapping::CollectionRef<D>& field) ;

	connection& conn() { return stmt_.conn() ; } ;
private:
	ptr<C> ptr_ ;
	std::shared_ptr<mapping::Mapping<C>> mapping_ ;
	stmt::PreparedStatement& stmt_ ;

	// id to be loaded
	IdType id_ ;

	SelectByIdState state_ ;

	SelectById(std::shared_ptr<mapping::Mapping<C>> mapping, stmt::PreparedStatement& stmt) ;

	template <class D> friend class SelectById ;
};

}}

#endif
