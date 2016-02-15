#ifndef _DBO_ACTION_SAVEDBACTION_HPP_
#define _DBO_ACTION_SAVEDBACTION_HPP_

namespace dbo2 {
namespace mapping {
template <class T> class Mapping ;
template <class T> class FieldRef ;
}

namespace action {

template<class C>
class SaveDb
{
public:
	SaveDb(ptr<C> ptr, std::shared_ptr<mapping::Mapping<C>> mapping, stmt::Statement& stmt, int column) ;

	void visit() ;

	template<typename V> void act(const mapping::FieldRef<V>& field) ;
	template<typename V> void actId(V& value, const std::string& name, int size) ;
	template<class D> void actId(ptr<D>& value, const std::string& name, int size, int fkConstraints) ;

private:
	ptr<C> ptr_ ;
	std::shared_ptr<mapping::Mapping<C>> mapping_ ;
	stmt::Statement stmt_ ;
	int column_ ;
};

}}

#endif