#pragma once
#include "ScanElement.h"

template <class T>
class SortTable;

template <class T>
class Table
{
protected:
	Element<T> notFound;
	Element<T>* mas;
	int size, count;
public:
	Table(int _size = 10);
	Table(Table& table);

	int GetSize();
	int GetCount();
	Element<T> GetElem(int index);

	void Put(std::string _key, T _data);
	void Del(std::string _key);
	Element<T>& Search(std::string _key);

	T& operator[](std::string _key);

	friend class SortTable<T>;
	//friend class TreeTable<T>;
	friend std::ostream& operator<<(std::ostream& out, Table<T>& table)
	{
		out << "Print Table" << std::endl;
		for (int i = 0; i < table.count; i++)
			out << table.mas[i] << std::endl;
		return out;
	}
};

template <class T>
Table<T>::Table(int _size)
{
	if (_size < 0)
		throw Exception("Error! Size must be positive!");
	else if (_size == 0)
	{
		size = 0;
		count = 0;
		notFound.SetKey("NOT_FOUND");
		notFound.SetData({ 404 });
		mas = NULL;
	}
	else
	{
		size = _size;
		count = 0;
		notFound.SetKey("NOT_FOUND");
		notFound.SetData({ 404 });
		mas = new Element<T>[size];
	}
}

template <class T>
Table<T>::Table(Table& table)
{
	size = table.size;
	count = table.count;
	mas = new Element<T>[size];
	for (int i = 0; i < size; i++)
		mas[i] = table.mas[i];
}

template <class T>
void Table<T>::Put(std::string _key, T _data)
{
	if (size == count)
		throw Exception("Error! Table is full!");
	else
	{
		mas[count].SetKey(_key);
		mas[count].SetData(_data);
		count++;
	}
}

template <class T>
void Table<T>::Del(std::string _key)
{
	if (count == 0)
		throw Exception("Error! Table is empty!");
	else
	{
		Element<T>& tmp = Search(_key);
		if (!(tmp == notFound))
			tmp = notFound;
	}
}

template <class T>
Element<T>& Table<T>::Search(std::string _key)
{
	for (int i = 0; i < count; i++)
		if (_key == mas[i].GetKey())
			return mas[i];
	return notFound;
}

template <class T>
T& Table<T>::operator[](std::string _key)
{
	Element<T>& tmp = Search(_key);
	if (tmp == notFound)
	{
		Put(_key, 0);
		return mas[count - 1].GetDataAddress();
	}
	return tmp.GetDataAddress();
}

template <class T>
int Table<T>::GetSize()
{
	return size;
}

template <class T>
int Table<T>::GetCount()
{
	return count;
}

template <class T>
Element<T> Table<T>::GetElem(int index)
{
	if ((index >= 0) && (index < count))
		return mas[index];
	else
		throw Exception("Out-of-range");
}