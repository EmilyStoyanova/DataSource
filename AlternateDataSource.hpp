#pragma once
#include"DataSource.hpp"


template<typename T>
class AlternateDataSource :public DataSource<T>
{
public: 
	AlternateDataSource();
	AlternateDataSource(Vector<DataSource<T>*>& data);
	AlternateDataSource(const AlternateDataSource<T>& other);
	AlternateDataSource<T>& operator=(const AlternateDataSource<T>& other);
	virtual ~AlternateDataSource();

	virtual T& nextElement()override;
	virtual Vector<T> nextElements(size_t n)override;
	virtual bool hasNext()const override;
	virtual bool reset()override;
	virtual T& operator()()override;
	virtual DataSource<T>& operator>>(T& value)override;
	virtual operator bool() const override;
	virtual DataSource<T>* clone() const override;

	size_t size() const;
	size_t getCurrentIndex()const;

	void pushBack(DataSource<T>* elem);
	bool popBack();
	DataSource<T>* operator[](size_t index);
	const DataSource<T>* operator[](size_t index) const;
	DataSource<T>* at(size_t index);
	const DataSource<T>* at(size_t index) const;
	
	
private:
	void copy(const AlternateDataSource& other);
	void clear();
private:
	Vector<DataSource<T>*> vec;
	size_t currentIndex;
};
template<typename T>
inline AlternateDataSource<T>::AlternateDataSource() :currentIndex(0)
{

};

template<typename T>
inline AlternateDataSource<T>::AlternateDataSource(Vector<DataSource<T>*>& data):AlternateDataSource() {
	for (size_t i = 0; i < data.getSize(); i++)
	{
		vec.push_back(data[i]->clone());
	}
}
template<typename T>
inline AlternateDataSource<T>::AlternateDataSource(const AlternateDataSource<T>& other)
{
	copy(other);
}

template<typename T>
inline AlternateDataSource<T>& AlternateDataSource<T>::operator=(const AlternateDataSource<T>& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

template<typename T>
inline AlternateDataSource<T>::~AlternateDataSource()
{
	clear();
}
template<typename T>
inline size_t AlternateDataSource<T>::getCurrentIndex() const
{
	return currentIndex;
}
template<typename T>
inline size_t AlternateDataSource<T>::size() const
{
	return vec.getSize();
}
template<typename T>
inline void AlternateDataSource<T>::copy(const AlternateDataSource& other)
{
	try
	{
		vec.reserve(other.vec.getSize());
		for (size_t i = 0; i < other.vec.getSize(); i++)
			vec.push_back(other.vec[i]->clone());
	}
	catch (...)
	{
		clear();
		throw;
	}
}
template<typename T>
inline void AlternateDataSource<T>::clear()
{
	for (size_t i = 0; i < vec.getSize(); i++) {
		delete vec[i];
	}
	vec.clean();
}
template<typename T>
inline void AlternateDataSource<T>::pushBack(DataSource<T>* elem)
{
	vec.push_back(elem);
}

template<typename T>
inline bool AlternateDataSource<T>::popBack()
{
	if (vec.getSize() == 0) {
		return false;
	}
	delete[] vec[vec.getSize() - 1];
	return true;
}

template<typename T>
inline DataSource<T>* AlternateDataSource<T>::operator[](size_t index)
{
	return vec[index];
}

template<typename T>
inline const DataSource<T>* AlternateDataSource<T>::operator[](size_t index) const
{
	return vec[index];
}

template<typename T>
inline DataSource<T>* AlternateDataSource<T>::at(size_t index)
{
	return vec.at(index);
}

template<typename T>
inline const DataSource<T>* AlternateDataSource<T>::at(size_t index) const
{
	return vec.at(index);
}

template<typename T>
inline T& AlternateDataSource<T>::nextElement()
{
	if (!hasNext()) {
		throw std::out_of_range("No more elements available.");
	}
	while (!vec[currentIndex]->hasNext()) {
		currentIndex = (currentIndex + 1) % vec.getSize();
	}
	T& element = vec[currentIndex]->nextElement();
	currentIndex = (currentIndex + 1) % vec.getSize();
	return element;

}

template<typename T>
inline Vector<T> AlternateDataSource<T>::nextElements(size_t n)
{
	Vector<T> elements;
	elements.reserve(n);
	for (size_t i = 0; i < n && hasNext(); ++i) {
		elements.push_back(nextElement());
	}
	return elements;
}

template<typename T>
inline bool AlternateDataSource<T>::hasNext() const
{
	for (size_t i = 0; i < vec.getSize(); ++i) {
		if (vec[i]->hasNext()) {
			return true;
		}
	}
	return false;
}

template<typename T>
inline bool AlternateDataSource<T>::reset()
{
	currentIndex = 0;
	for (size_t i = 0; i < vec.getSize(); ++i) {
		if (!vec[i]->reset()) {
			return false;
		}
	}
	return true;
}
template<typename T>
inline T& AlternateDataSource<T>::operator()() {
	return nextElement();
}

template<typename T>
inline DataSource<T>& AlternateDataSource<T>::operator>>(T& value)
{
	value = nextElement();
	return *this;
}

template<typename T>
inline AlternateDataSource<T>::operator bool() const
{
	return hasNext();
}
template<typename T>
inline DataSource<T>* AlternateDataSource<T>::clone() const
{
	return new AlternateDataSource<T>(*this);
}
