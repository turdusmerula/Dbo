/*
 * Copyright (C) 2010 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef DBO_FIXED_SQL_CONNECTION_POOL_H_
#define DBO_FIXED_SQL_CONNECTION_POOL_H_

#include <wtdbo/SqlConnectionPool.h>

#include <vector>

namespace wtdbo
{

/*! \class FixedSqlConnectionPool Dbo/FixedSqlConnectionPool Dbo/FixedSqlConnectionPool
 *  \brief A connection pool of fixed size.
 *
 * This provides a connection pool of fixed size: its size is determined at
 * startup time, and the pool will not grow as more connections are needed.
 *
 * This is adequate when the number of threads (which need different
 * connections to work with) is also bounded, like when using a fixed
 * size thread pool. This is for example the case when used in
 * conjunction with %Wt. Note that you do not need as many connections
 * as sessions, since Session will only use a connection while
 * processing a transaction.
 *
 * \ingroup wtdbo
 */
class FixedSqlConnectionPool : public SqlConnectionPool
{
public:
	/*! \brief Creates a fixed connection pool.
	 *
	 * The pool is initialized with the provided \p connection, which is
	 * cloned (\p size - 1) times.
	 *
	 * The pool thus takes ownership of the given connection.
	 */
	FixedSqlConnectionPool(SqlConnection *connection, int size);

	virtual ~FixedSqlConnectionPool();
	virtual SqlConnection *getConnection();
	virtual void returnConnection(SqlConnection *);
	virtual void prepareForDropTables() const;

private:
	struct Impl;
	Impl *impl_;
};

}

#endif // DBO_SQL_CONNECTION_POOL_H_
