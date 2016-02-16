namespace dbo2 {

template <class C>
ptr<C>::ptr()
	:	ptr_(nullptr)
{

}

template <class C>
ptr<C>::ptr(C* obj)
{
	ptr_ = new Ptr ;
	ptr_->value_ = obj ;
	ptr_->ref_ = 1 ;
	ptr_->id_ = traits::dbo_traits<C>::invalidId() ;
}

template<class C>
ptr<C>::ptr(const ptr<C>& other)
		: ptr_(other.ptr_)
{
	take() ;
}

template<class C>
template<class D>
ptr<C>::ptr(const ptr<D>& other)
		: ptr_(other.ptr_)
{
	// Check if we can convert D* to C*
	dynamic_cast<C*>(other.ptr_->value_) ;
	take() ;
}

template <class C>
ptr<C>::~ptr()
{
	free() ;
}

template<class C>
void ptr<C>::reset(C* _ptr)
{
	free() ;
	if(ptr_)
	{
		ptr_ = new Ptr ;
		ptr_->value_ = _ptr ;
		ptr_->ref_ = 1 ;
		ptr_->id_ = traits::dbo_traits<C>::invalidId() ;
	}
}

template<class C>
ptr<C>& ptr<C>::operator=(const ptr<C>& other)
{
	if(ptr_!=other.ptr_)
	{
		free() ;
		ptr_ = other.ptr_ ;
		take();
	}

	return *this;
}

template<class C>
template<class D>
ptr<C>& ptr<C>::operator=(const ptr<D>& other)
{
	// Check if we can convert D* to C*
	dynamic_cast<C*>(other.value_) ;

	if(ptr_!=other.ptr_)
	{
		free();
		ptr_ = other.ptr_;
		take() ;
	}

	return *this ;
}

template<class C>
C* ptr<C>::operator->() const
{
	C* res=get() ;

	if(res==nullptr)
		throw Exception("dbo::ptr: null dereference") ;

	return res ;
}

template<class C>
C* ptr<C>::get() const
{
	if(ptr_)
		return ptr_->value_ ;
	else
		return nullptr ;
}

template<class C>
C& ptr<C>::operator*() const
{
	if(ptr_)
		return* ptr_->value_ ;
	else
		throw Exception("dbo::ptr: null dereference") ;
}

template<class C>
bool ptr<C>::operator==(const ptr<MutC>& other) const
{
	return ptr_==other.obj_ ;
}

template<class C>
bool ptr<C>::operator==(const ptr<const C>& other) const
{
	return ptr_==other.obj_ ;
}

template<class C>
bool ptr<C>::operator!=(const ptr<MutC>& other) const
{
	return !(*this==other) ;
}

template<class C>
bool ptr<C>::operator!=(const ptr<const C>& other) const
{
	return !(*this==other) ;
}

template<class C>
bool ptr<C>::operator<(const ptr<MutC>& other) const
{
	return ptr_<other.ptr_ ;
}

template<class C>
bool ptr<C>::operator<(const ptr<const C>& other) const
{
	return ptr_<other.ptr_ ;
}

template<class C>
ptr<C>::operator bool() const
{
	return ptr_!=nullptr ;
}

template<class C>
bool ptr<C>::loaded() const
{
	if(ptr_==nullptr)
		return false ;
	return ptr_->state_==State::Loaded ;
}

template<class C>
bool ptr<C>::orphan() const
{
	if(ptr_==nullptr)
		return false ;
	return ptr_->state_==State::Orphan ;
}

template<class C>
void ptr<C>::free()
{
	if(ptr_)
	{
		ptr_->ref_-- ;
		if(ptr_->ref_==0)
		{
			delete ptr_->value_ ;
			delete ptr_ ;
			ptr_ = nullptr ;
		}
	}
}

template<class C>
void ptr<C>::take()
{
	if(ptr_)
		ptr_->ref_++ ;
}

template<class C>
typename ptr<C>::IdType ptr<C>::id()
{
	if(ptr_)
		return ptr_->id_ ;
	return traits::dbo_traits<C>::invalidId() ;
}

template<class C>
void ptr<C>::id(const ptr<C>::IdType& value)
{
	if(ptr_)
		ptr_->id_ = value ;
}

}
