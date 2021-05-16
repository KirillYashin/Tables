#pragma once
#include "ScanTable.h"

template<class T>
class SortTable
{
protected:
	Element<T> notFound;
	Element<T>* mas;
	int size;
	int count;
public:
	SortTable(int _size = 10);
	SortTable(std::string* _keys, T* _data, int _size);
	SortTable(SortTable<T>& sorttable);
	~SortTable();

	int GetSize();
	int GetCount();
	void Resize(int _size);

	int Put(std::string _key, T _data);
	void Del(std::string _key);
	Element<T>& Search(std::string _key);
	T& operator[](std::string _key);

	void Print();

	void QuickSort(Table<T>& table, const int low, const int high);

	friend std::ostream& operator<<(std::ostream& out, SortTable<T>& sorttable)
	{
		out << "Table" << std::endl;
		for (int i = 0; i < sorttable.count; i++)
			out << sorttable.mas[i] << std::endl;
		return out;
	}
};

template<class T>
SortTable<T>::SortTable(int _size)
{
	if (_size <= 0)
		throw Exception("Size must be positive!");
	else
	{
		size = _size;
		count = 0;
		notFound.SetKey("NOT_FOUND");
		notFound.SetData({ 404 });
		mas = new Element<T>[size];
	}
}

template<class T>
SortTable<T>::SortTable(std::string* _keys, T* _data, int _size)
{
	if (_size <= 0)
		throw Exception("Size must be positive!");
	Table<T> table(_size);
	for (int i = 0; i < _size; i++)
	{
		table.Put(_keys[i], _data[i]);
	}
	size = table.size;
	count = table.count;
	mas = new Element<T>[size];
	SortTable<T>::QuickSort(table, 0, table.count - 1);
	for (int i = 0; i < count; i++)
		mas[i] = table.mas[i];
}


template<class T>
SortTable<T>::SortTable(SortTable<T>& sorttable)
{
	size = sorttable.size;
	count = sorttable.count;
	mas = new Element<T>[size];
	for (int i = 0; i < size; i++)
		mas[i] = sorttable.mas[i];
}

template <class T>
SortTable<T>::~SortTable()
{
	count = size = 0;
	delete[] mas;
}

template <class T>
int SortTable<T>::GetSize()
{
	return size;
}

template <class T>
int SortTable<T>::GetCount()
{
	return count;
}

template<class T>
void SortTable<T>::Resize(int _size)
{
	if (_size <= size)
		throw Exception("Wrong size!");
	Element<T>* newMas = new Element<T>[_size];
	for (int i = 0; i < size; i++)
		newMas[i] = mas[i];
	delete[] mas;
	mas = newMas;
	size = _size;
}

template<class T>
int SortTable<T>::Put(std::string _key, T _data)
{
	if (size == count)
		Resize(count * 2);
	if (count == 0)
	{
		mas[0].SetKey(_key);
		mas[0].SetData(_data);
		count++;
		return 0;
	}
	int right = count - 1;
	int left = 0;
	int cur = count / 2;
	while (left < right)
	{
		if (mas[cur].GetKey() > _key)
		{
			right = cur - 1;
			cur = ((left + right) / 2);
		}
		else if (mas[cur].GetKey() < _key)
		{
			left = cur + 1;
			cur = ((left + right) / 2);
		}
		else
		{
			throw Exception("Such key already exists!");
		}
	}

	if (mas[cur].GetKey() < _key)
		cur++;

	for (int i = count - 1; i >= cur; i--)
		mas[i + 1] = mas[i];
	mas[cur].SetKey(_key);
	mas[cur].SetData(_data);
	count++;
	return cur;
}

template<class T>
void SortTable<T>::Del(std::string _key)
{
	int right = count - 1;
	int left = 0;
	int cur = count / 2;
	if (count == 0) return;
	while (left <= right)
	{
		if (mas[cur].GetKey() > _key)
		{
			right = cur - 1;
			cur = ((left + right) / 2);
		}
		else if (mas[cur].GetKey() < _key)
		{
			left = cur + 1;
			cur = ((left + right) / 2);
		}
		else if (mas[cur].GetKey() == _key)
		{
			for (int i = cur; i < count - 1; i++)
				mas[i] = mas[i + 1];
			count--;
			return;
		}
		else
			return;
	}
}

template<class T>
Element<T>& SortTable<T>::Search(std::string _key)
{
	int right = count - 1;
	int left = 0;
	int cur = count / 2;
	while (left <= right)
	{
		if (mas[cur].GetKey() > _key)
		{
			right = cur - 1;
			cur = ((left + right) / 2);
		}
		else if (mas[cur].GetKey() < _key)
		{
			left = cur + 1;
			cur = ((left + right) / 2);
		}
		else
			return mas[cur];
	}
	return notFound;
}

template<class T>
T& SortTable<T>::operator[](std::string _key)
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
void SortTable<T>::Print()
{
	std::cout << "Print Table [" << count << "/" << size << "] \n";
	for (int i = 0; i < count; i++)
		std::cout << mas[i] << std::endl;
}

template <class T>
void SortTable<T>::QuickSort(Table<T>& table, const int low, const int high)
{
	int i = low, j = high;
	Element<T> d;
	Element<T> tmp = table.mas[(low + high) / 2];
	while (i <= j)
	{
		for (; table.mas[i].GetKey() < tmp.GetKey(); i++);
		for (; table.mas[j].GetKey() > tmp.GetKey(); j--);
		if (i <= j)
		{
			d = table.mas[i];
			table.mas[i++] = table.mas[j];
			table.mas[j--] = d;
		}
	}
	if (low < j)
		QuickSort(table, low, j);
	if (i < high)
		QuickSort(table, i, high);
}