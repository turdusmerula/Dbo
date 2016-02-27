// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef DBO_EXCEPTION_H_
#define DBO_EXCEPTION_H_

#include <string>
#include <stdexcept>

namespace wtdbo
{

/*! \class Exception Dbo/Exception Dbo/Exception
 *  \brief %Exception base class for %%Dbo.
 *
 * \ingroup wtdbo
 */
class Exception : public std::runtime_error
{
public:
	/*! \brief Constructor.
	 */
	Exception(const std::string& error, const std::string& code = std::string());

	virtual ~Exception() throw();

	/*! \brief A (backend-specific) error code.
	 *
	 * For native SQL errors, a native backend code may be available
	 * (see the backend documentation for details). This is typically
	 * the (semi-standardized) SQLSTATE code value.
	 *
	 * When not available, an empty string is returned.
	 */
	std::string code() const
	{
		return code_;
	}

private:
	std::string code_;
};

/*! \class StaleObjectException Dbo/Exception Dbo/Exception
 *  \brief %Exception thrown when %%Dbo detects a concurrent modification
 *
 * %%Dbo uses optimistic locking for detecting and preventing
 * concurrent modification of database objects. When trying to save an
 * object that has been modified concurrently by another session, since
 * it was read from the database, this exception is thrown.
 *
 * This exception is thrown during flushing from Session::flush() or
 * ptr::flush(). Since flushing will also be done automatically when
 * needed (e.g. before running a query or before committing a
 * transaction), you should be prepared to catch this exception from most
 * library API calls.
 *
 * \note We should perhaps also have a ptr::isStale() method to find out
 *       what database object is stale ?
 *
 * \ingroup wtdbo
 */
class StaleObjectException : public Exception
{
public:
	/*! \brief Constructor.
	 */
	StaleObjectException(const std::string& id, int version);
};

/*! \class ObjectNotFoundException Dbo/Exception Dbo/Exception
 *  \brief %Exception thrown when trying to load a non-existing object.
 *
 * This %Exception is thrown by Session::load() when trying to load an object
 * that does not exist.
 *
 * \ingroup wtdbo
 */
class ObjectNotFoundException : public Exception
{
public:
	/*! \brief Constructor.
	 */
	ObjectNotFoundException(const std::string& id);
};

/*! \class NoUniqueResultException Dbo/Exception Dbo/Exception
 *  \brief %Exception thrown when a query unexpectedly finds a non-unique result.
 *
 * This %Exception is thrown by Query::resultValue() when the query has
 * more than one result.
 *
 * \ingroup wtdbo
 */
class NoUniqueResultException : public Exception
{
public:
	/*! \brief Constructor.
	 */
	NoUniqueResultException();
};

}

#endif // DBO_EXCEPTION_H_
