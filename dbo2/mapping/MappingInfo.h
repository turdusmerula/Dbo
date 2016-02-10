#ifndef _DBO_MAPPING_MAPPINGINFO_H_
#define _DBO_MAPPING_MAPPINGINFO_H_

#include <dbo2/mapping/FieldInfo.h>
#include <dbo2/mapping/SetInfo.h>

#include <vector>

#include <boost/optional.hpp>

namespace dbo2 {
class database ;

namespace mapping {

class MappingInfo
{
public:
	MappingInfo() ;
	virtual ~MappingInfo() ;

	bool initialized_ ;

	std::string tableName ;
	boost::optional<std::string> surrogateIdFieldName ;

	std::string naturalIdFieldName ; // for non-auto generated id
	int naturalIdFieldSize ;         // for non-auto generated id

	std::string idCondition ;

	std::vector<FieldInfo> fields ;
	std::vector<SetInfo> sets ;

	std::vector<std::string> statements ;

	virtual void init(database& conn) ;
	std::string primaryKeys() const ;
} ;

}}

#endif