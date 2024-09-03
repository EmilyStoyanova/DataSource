#pragma once
#include"DataSource.hpp"



template<typename T>
class ArrayDataSource :public DataSource<T>
{
public:
	ArrayDataSource(const T* array,size_t size);
	virtual ~ArrayDataSource()=default;

	virtual T& nextElement()override;
	virtual Vector<T> nextElements(size_t n)override;
	virtual bool hasNext()const override;
	virtual bool reset()override;
	virtual T& operator()()override;
	virtual DataSource<T>& operator>>(T& value)override;
	virtual operator bool() const override;
	virtual DataSource<T>* clone() const override;

	ArrayDataSource<T>& operator+=(const T& element);
	ArrayDataSource<T> operator+(const T& element)const;

	ArrayDataSource<T>& operator--();
	ArrayDataSource<T> operator--(int);

	
private:
	Vector<T> data;
	size_t index;
	
};
template<typename T>
inline ArrayDataSource<T>::ArrayDataSource(const T* array,size_t size) :index(0)
{
	for (size_t i = 0; i < size; ++i) {
		data.push_back(array[i]);
	}
	
}
template<typename T>
inline T& ArrayDataSource<T>::nextElement()
{
	if (!hasNext()) {
		throw std::out_of_range("No more elements");
	}
	else {
		return data[index++];
	}
}

template<typename T>
inline Vector<T> ArrayDataSource<T>::nextElements(size_t n)
{
	Vector<T> elements;
	for (size_t i = 0; i < n; ++i) {
		elements.push_back(nextElement());
	}
	return elements;
}

template<typename T>
inline bool ArrayDataSource<T>::hasNext() const
{
	return index < data.getSize();
}

template<typename T>
inline bool ArrayDataSource<T>::reset()
{
	if (!data.isEmpty()) {
		index = 0;
		return true;
	}
	return false;
}
template<typename T>
inline  T& ArrayDataSource<T>::operator()() {
	return nextElement();
}
template<typename T>
inline DataSource<T>& ArrayDataSource<T>::operator>>(T& value)
{
	if (hasNext()) {
		value = data[index++];
	}
	else {
		throw std::out_of_range("No more elements");
	}
	return *this;
}
template<typename T>
inline ArrayDataSource<T>::operator bool() const
{
	return hasNext();
}

template<typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator+=(const T& element)
{
	data.push_back(element);
	return *this;
}
template<typename T>
inline ArrayDataSource<T> ArrayDataSource<T>::operator+(const T& element) const
{
	ArrayDataSource<T> temp = *this;
	temp.data.push_back(element);
	return temp;
}
template<typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator--()
{
	if (index == 0 ) {
		throw std::out_of_range("No more elements before that");
	} else if(index > 0) {
		--index;
	}
	return *this;
}

template<typename T>
inline ArrayDataSource<T> ArrayDataSource<T>::operator--(int)
{
	ArrayDataSource<T> temp= *this;
	if (index == 0) {
		throw std::out_of_range("No more elements before that");
	}else if (index > 0) {
		--index;
	}
	return temp;
}

template<typename T>
inline DataSource<T>* ArrayDataSource<T>::clone() const
{
	return new ArrayDataSource<T>(*this);
}




