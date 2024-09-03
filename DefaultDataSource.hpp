#pragma once
#include"DataSource.hpp"
template<typename T>
class DefaultDataSource:public DataSource<T>
{
public:
	DefaultDataSource();
	virtual ~DefaultDataSource()=default;

	virtual T& nextElement()override;
	virtual Vector<T> nextElements(size_t n)override;
	virtual bool hasNext()const override;
	virtual bool reset()override;
	virtual T& operator()()override;
	virtual DataSource<T>& operator>>(T& value)override;
	virtual operator bool() const override;
	virtual DataSource<T>* clone() const override;
private:
	Vector<T> data;
	size_t index;
};

template<typename T>
inline DefaultDataSource<T>::DefaultDataSource():index(0)
{
}

template<typename T>
inline T& DefaultDataSource<T>::nextElement() {
	T newObj = T();
	data.push_back(newObj);
	index++;
	return newObj;
}

template<typename T>
inline Vector<T> DefaultDataSource<T>::nextElements(size_t n)
{
	Vector<T> elements;
	for (size_t i = index; i < n; ++i) {
		elements.push_back(nextElement());

	}
	return elements;
}
template<typename T>
inline bool DefaultDataSource<T>::hasNext() const
{
	return true;
}

template<typename T>
inline bool DefaultDataSource<T>::reset()
{
	index = 0;
	return true;
}
template<typename T>
inline T& DefaultDataSource<T>::operator()() {
	return nextElement();
}
template<typename T>
inline DataSource<T>& DefaultDataSource<T>::operator>>(T& value)
{
	value = nextElement();
	return *this;
}

template<typename T>
inline DefaultDataSource<T>::operator bool() const
{
	return hasNext();
}

template<typename T>
inline DataSource<T>* DefaultDataSource<T>::clone() const
{
	return new DefaultDataSource<T>(*this);
}
