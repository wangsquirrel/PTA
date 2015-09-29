#include <assert.h>
#include <typeinfo>
#include <iostream>
enum Type
{
	INT, STRING, LIST, DICT
};
class PlaceHolder {
public:
  	virtual ~PlaceHolder() {}
  	virtual PlaceHolder *clone() const = 0;
	virtual const std::type_info & type() const = 0;         
};

template<typename ValueType>
class Holder : public PlaceHolder {
public:
	virtual const std::type_info & type() const  
	{   
       return typeid(ValueType);   
   	}   
  	Holder(const ValueType& value) : held_(value) {}
  	virtual PlaceHolder * clone() const  
    {   
        return new Holder(held_);
    }
    
  	ValueType held_;
};

class Any
{
public:
	Any() : content_(NULL) {};
	template<typename ValueType>
	Any(const ValueType& value) : content_(new Holder<ValueType>(value))  {}
  	Any(const Any & other) : content_(other.content_ ? other.content_->clone() : 0) {}
	Any& swap(Any & rhs)
    {
        std::swap(content_, rhs.content_);
        return *this;
	} 
  	Any & operator=(const Any & rhs)
    {
        Any(rhs).swap(*this);
        return *this;
    }
 
    
	const std::type_info & type() const  
	{   
	    return content_ ? content_->type() : typeid(void);   
    }     
  	~Any(){
		delete content_;
	}
	template<typename ValueType> friend ValueType any_cast(const Any& operand);
  		
private:
  		PlaceHolder* content_;
  		
};
template<typename ValueType>   
ValueType any_cast(const Any& operand)  
{
   	assert( operand.type() == typeid(ValueType) ); 
	return static_cast< Holder<ValueType> * >(operand.content_)->held_;   
}
