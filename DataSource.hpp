#pragma once
#include"Vector.hpp"
template<typename T>
class DataSource
{
public:
	virtual ~DataSource()=default;
	virtual T& nextElement()=0;
	virtual Vector<T> nextElements(size_t n) = 0;
	virtual bool hasNext()const=0;
	virtual bool reset()=0;
	virtual T& operator()()=0; 
	virtual DataSource<T>& operator>>(T& value)=0;
	virtual operator bool() const = 0;
	virtual DataSource<T>* clone() const = 0;
};

