#pragma once
#include"DataSource.hpp"
#include<fstream>


template<typename T>
class FileDataSource :public DataSource<T>
{
public:
	FileDataSource(const char* name);
	FileDataSource(const FileDataSource& other);
	FileDataSource<T>& operator=(const FileDataSource<T>& other);
	virtual ~FileDataSource();

	virtual T& nextElement()override;
	virtual Vector<T> nextElements(size_t n)override;
	virtual bool hasNext()const override;
	virtual bool reset() override;
	virtual T& operator()() override;
	virtual DataSource<T>& operator>>(T& value) override;
	virtual operator bool() const override;
	virtual DataSource<T>* clone() const override;
private:
	std::ifstream file;
	char* fileName;
	Vector<T> data;
	size_t index;

	void loadDataFromFile();
	void copy(const FileDataSource& other);
	void clean();
};
template<typename T>
inline void FileDataSource<T>::clean() {
	delete[]fileName;
	fileName = nullptr;
}
template<typename T>
inline FileDataSource<T>::FileDataSource(const char* name) :index(0)
{
	this->fileName = new char[strlen(name) + 1];
	strcpy(fileName, name);
	loadDataFromFile();
}
template<typename T>
inline FileDataSource<T>::FileDataSource(const FileDataSource& other) {
	copy(other);
}

template<typename T>
inline FileDataSource<T>& FileDataSource<T>::operator=(const FileDataSource<T>& other)
{
	if (this != &other) {
		clean();
		copy(other);
	}
	return *this;
}

template<typename T>
inline FileDataSource<T>::~FileDataSource()
{
	clean();
}

template<typename T>
inline T& FileDataSource<T>::nextElement()
{
	if (!hasNext()) {
		throw std::out_of_range("No more elements");
	}
	else {
		return data[index++];
	}
}

template<typename T>
inline Vector<T> FileDataSource<T>::nextElements(size_t n)
{
	Vector<T> elements;
	while (n-- > 0 && hasNext()) {
		elements.push_back(nextElement());
	}
	return elements;
}

template<typename T>
inline bool FileDataSource<T>::hasNext() const
{
	return index < data.getSize();
}

template<typename T>
inline bool FileDataSource<T>::reset()
{
	if (!data.isEmpty()) {
		index = 0;
		return true;
	}
	return false;
}
template<typename T>
inline T& FileDataSource<T>::operator()() {
	return nextElement();
}
template<typename T>
inline DataSource<T>& FileDataSource<T>::operator>>(T& value)
{
	value = nextElement();
	return *this;
}

template<typename T>
inline FileDataSource<T>::operator bool() const
{
	return hasNext();
}

template<typename T>
inline void FileDataSource<T>::loadDataFromFile()
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("File is not open!");
	}
	T element;
	while (file >> element) {
		data.push_back(element);
	}
	file.close();
}

template<typename T>
inline DataSource<T>* FileDataSource<T>::clone()const {
	return new FileDataSource<T>(*this);
}
template<typename T>
inline void FileDataSource<T>::copy(const FileDataSource& other) {

	if (other.fileName) {
		fileName = new char[strlen(other.fileName) + 1];
		strcpy(fileName, other.fileName);
	}
	else {
		fileName = nullptr;
	}
	data = other.data;
	index = other.index;
	if (file.is_open()) {
		file.close();
	}

	if (fileName) {
		file.open(fileName);

		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file.");
		}
		file.seekg(other.index);
	}
}


