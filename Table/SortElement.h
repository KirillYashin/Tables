#pragma once
#include <Exception.h>
#include <string>


template <class T>
class Element
{
protected:
	std::string key;
	T data;
public:
	Element(std::string _key = "", T _data = 0);
	Element(Element& copy);

	void SetKey(std::string _key);
	std::string GetKey();
	void SetData(T _data);
	T GetData();
	T& GetDataAddress();

	Element<T>& operator=(Element& elem);
	bool operator==(Element& elem);
	bool operator!=(Element<T>& elem);

	friend ostream& operator<<(ostream& out, Element<T>& elem)
	{
		out << "Key: " << elem.GetKey() << "\t|\t";
		out << "Data: " << elem.GetData();
		return out;
	}
};

template <class T>
Element<T>::Element(std::string _key, T _data)
{
	key = _key;
	data = _data;
}

template <class T>
Element<T>::Element(Element& elem)
{
	key = elem.key;
	data = elem.data;
}

template <class T>
void Element<T>::SetKey(std::string _key)
{
	key = _key;
}

template <class T>
std::string Element<T>::GetKey()
{
	return key;
}

template <class T>
void Element<T>::SetData(T _data)
{
	data = _data;
}

template <class T>
T Element<T>::GetData()
{
	return data;
}

template <class T>
T& Element<T>::GetDataAddress()
{
	return data;
}

template <class T>
Element<T>& Element<T>::operator=(Element& elem)
{
	if (this != &elem)
	{
		key = elem.key;
		data = elem.data;
	}
	return *this;
}

template <class T>
bool Element<T>::operator==(Element& elem)
{
	if (key != elem.key)
		return false;
	return true;
}

template <class T>
bool Element<T>::operator!=(Element<T>& elem)
{
	return !(*this == elem);
}