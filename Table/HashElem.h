#pragma once
#include <Exception.h>
#include <string>

template <class T>
class Elem
{
protected:
	std::string key;
	T data;
	Elem<T>* next;
public:
	Elem(std::string _key = "", T _data = { }, Elem<T>* _next = NULL);
	Elem(Elem<T>& copy);
	~Elem();

	void SetKey(std::string _key);
	std::string GetKey();
	void SetData(T _data);
	T GetData();
	T& GetDataAddress();
	void SetNext(Elem<T>* elem);
	Elem<T>* GetNext();

	Elem<T>& operator=(Elem<T>& elem);
	bool operator==(Elem<T>& elem);
	bool operator!=(Elem<T>& elem);

	friend std::ostream& operator<<(std::ostream& out, Elem<T>& elem)
	{
		out << "Key: " << elem.GetKey() << "\t|\t";
		T temp = elem.GetData();
		out << "Data: ";
		for (int i = 0; i < temp.size(); i++) {
			out << temp[i] << " ";
		}
		return out;
	}
};

template <class T>
Elem<T>::Elem(std::string _key, T _data, Elem<T>* _next)
{
	key = _key;
	data = _data;
	next = _next;
}

template <class T>
Elem<T>::Elem(Elem<T>& elem)
{
	key = elem.key;
	data = elem.data;
	next = elem.next;
}

template <class T>
Elem<T>::~Elem()
{
	next = NULL;
}

template <class T>
void Elem<T>::SetKey(std::string _key)
{
	key = _key;
}

template <class T>
std::string Elem<T>::GetKey()
{
	return key;
}

template <class T>
void Elem<T>::SetData(T _data)
{
	data = _data;
}

template <class T>
T Elem<T>::GetData()
{
	return data;
}

template <class T>
T& Elem<T>::GetDataAddress()
{
	return data;
}

template <class T>
void Elem<T>::SetNext(Elem<T>* elem)
{
	if (this == elem)
		throw Exception("Error");
	next = elem;
}

template <class T>
Elem<T>* Elem<T>::GetNext()
{
	return next;
}

template <class T>
Elem<T>& Elem<T>::operator=(Elem<T>& elem)
{
	if (this != &elem)
	{
		key = elem.key;
		data = elem.data;
		next = elem.next;
	}
	return *this;
}

template <class T>
bool Elem<T>::operator==(Elem<T>& elem)
{
	if (key != elem.key)
		return false;
	return true;
}

template <class T>
bool Elem<T>::operator!=(Elem<T>& elem)
{
	return !(*this == elem);
}