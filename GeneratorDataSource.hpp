#pragma once
#include"DataSource.hpp"
template<typename T>
class GeneratorDataSource :public DataSource<T> {

public:
	using GeneratorFunction = T(*)();
	GeneratorDataSource(GeneratorFunction gen);
	virtual ~GeneratorDataSource() = default;

	virtual T& nextElement()override;
	virtual Vector<T> nextElements(size_t n)override;
	virtual bool hasNext()const override;
	virtual bool reset()override;
	virtual T& operator()() override;
	virtual DataSource<T>& operator>>(T& value)override;
	virtual operator bool() const override;
	virtual DataSource<T>* clone() const override;
private:
	GeneratorFunction generator;
	Vector<T> data;
	size_t index;
};

template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource(GeneratorFunction gen) 
	:generator(std::move(gen)),index(0)
{
	if (generator == nullptr) {
		throw std::invalid_argument("Generator function cannot be null");
	}
}

template<typename T>
inline T& GeneratorDataSource<T>::nextElement()
{
	if (index >= data.getSize()) {
		T newObj = generator();
		data.push_back(std::move(newObj));
	}
	return data[index++];
}

template<typename T>
inline Vector<T> GeneratorDataSource<T>::nextElements(size_t n)
{
	Vector<T> elements;
	for (size_t i = 0; i < n; ++i) {
		elements.push_back(nextElement());
	}
	return elements;
}

template<typename T>
inline bool GeneratorDataSource<T>::hasNext() const
{
	return true;
}

template<typename T>
inline bool GeneratorDataSource<T>::reset()
{
	index = 0;
	return true;
}
template<typename T>
inline T& GeneratorDataSource<T>::operator()() {
	return nextElement();
}

template<typename T>
inline DataSource<T>& GeneratorDataSource<T>::operator>>(T& value)
{
	value = nextElement();
	return *this;
}

template<typename T>
inline GeneratorDataSource<T>::operator bool() const
{
	return hasNext();
}

template<typename T>
inline DataSource<T>* GeneratorDataSource<T>::clone() const
{
	return new GeneratorDataSource<T>(*this);
}

