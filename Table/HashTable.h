#pragma once
#include "HashElem.h"


template<class T>
class HashList
{
protected:
	Elem<T> notFound;
	Elem<T>** mas;
	int size;
	int count;

	long long Hash(std::string _key);
	void Resize(int _size);
public:
	HashList(int _size = 5);
	HashList(HashList<T>& hashtable);
	~HashList();

	int GetSize();
	int GetCount();

	void Put(std::string _key, T _data, Elem<T>* _next = NULL);
	//void Put(TElemL<T>& elem);
	bool Del(std::string _key);
	Elem<T>& Search(std::string _key);

	bool IsSimple(const int nubmer);

	friend std::ostream& operator<<(std::ostream& out, HashList<T>& hashtable)
	{
		for (int i = 0; i < hashtable.size; i++)
			if (hashtable.mas[i] != &hashtable.notFound)
			{
				Elem<T>* temp = hashtable.mas[i];
				do
				{
					out << "Hash: " << hashtable.Hash(temp->GetKey()) << "\t|\t" << (*temp) << std::endl;
					temp = temp->GetNext();
				} while (temp != NULL);
			}
		return out;
	}
};

template <class T>
HashList<T>::HashList(int _size)
{
	if (_size <= 0)
		throw Exception("Error size");
	count = 0;
	size = _size;
	notFound.SetKey("NOT_FOUND");
	notFound.SetData({ 404 });
	notFound.SetNext(NULL);
	mas = new Elem<T>*[size];
	for (int i = 0; i < size; i++)
		mas[i] = &notFound;
}

template <class T>
HashList<T>::HashList(HashList<T>& hashtable)
{
	count = hashtable.count;
	size = hashtable.size;
	mas = new Elem<T>*[size];
	for (int i = 0; i < size; i++)
	{
		if (*hashtable.mas[i] == notFound)
			mas[i] = &notFound;
		else
		{
			Elem<T>* iter1 = hashtable.mas[i], * iter2;
			mas[i] = new Elem<T>(*hashtable.mas[i]);
			iter2 = mas[i];
			while (iter1->GetNext() != NULL)
			{
				iter2->SetNext(new Elem<T>(*(iter1->GetNext())));
				iter1 = iter1->GetNext();
				iter2 = iter2->GetNext();
			}
		}
	}
}

template <class T>
HashList<T>::~HashList()
{
	for (int i = 0; i < size; i++)
	{
		if (mas[i] != &notFound)
		{
			Elem<T>* iter = mas[i];
			do
			{
				Elem<T>* tmp = iter->GetNext();
				delete iter;
				iter = tmp;
			} while (iter != NULL);
		}
	}
	delete[] mas;
}

template <class T>
long long HashList<T>::Hash(std::string _key)
{
	const int p = 31;
	long long hash = 0, p_pow = 1;
	for (size_t i = 0; i < _key.length(); ++i)
	{
		// желательно отнимать 'a' от кода буквы
		// единицу прибавляем, чтобы у строки вида 'aaaaa' хэш был ненулевой
		hash += (_key[i] - 'a' + 1) * p_pow;
		p_pow *= p;
	}
	return hash;
}

template <class T>
void HashList<T>::Resize(int _size)
{
	if (_size <= size)
		throw Exception("Error size");
	while (!IsSimple(_size))
		_size++;
	Elem<T>** tmp = new Elem<T>*[_size];
	for (int i = 0; i < size; i++)
		tmp[i] = mas[i];
	for (int i = size; i < _size; i++)
		tmp[i] = &notFound;
	size = _size;
	delete[] mas;
	mas = tmp;
}

template <class T>
bool HashList<T>::IsSimple(const int number)
{
	for (int i = 2; i < number / 2; i++)
		if (number % i == 0)
			return false;
	return true;
}

template <class T>
int HashList<T>::GetSize()
{
	return size;
}

template <class T>
int HashList<T>::GetCount()
{
	return count;
}

template <class T>
void HashList<T>::Put(std::string _key, T _data, Elem<T>* _next)
{
	if (count == size)
		Resize(count * 2);
	unsigned hashvalue = Hash(_key);
	if (hashvalue > size)
		Resize(hashvalue + 10);
	if (mas[hashvalue] == &notFound)
	{
		mas[hashvalue] = new Elem<T>(_key, _data, _next);
		count++;
	}
	else
	{
		if (mas[hashvalue]->GetData() != _data && mas[hashvalue]->GetKey() != _key) {
			Elem<T>* tmp = new Elem<T>(_key, _data, _next);
			tmp->SetNext(mas[hashvalue]);
			mas[hashvalue] = tmp;
			count++;
		}
		if (mas[hashvalue]->GetData() != _data && mas[hashvalue]->GetKey() == _key) {
			T temp = mas[hashvalue]->GetData();
			temp.insert(temp.end(), _data.begin(), _data.end());
			mas[hashvalue] = new Elem<T>(_key, temp, _next);
		}
	}
}

/*template <class T>
void THashTableList<T>::Put(TElemL<T>& elem)
{
	unsigned hashvalue = Hash(elem.GetKey());
	if (count == size)
		Resize(count * 2);
	if (hashvalue > (unsigned)size)
		Resize(hashvalue + 10);
	if (mas[hashvalue] == &notFound)
	{
		mas[hashvalue] = new TElemL<T>(elem);
		count++;
	}
	else
	{
		if (mas[hashvalue]->GetData() != elem.data && mas[hashvalue]->GetKey() != elem.key) {
			TElemL<T>* tmp = new TElemL<T>(elem);
			tmp->SetNext(mas[hashvalue]);
			mas[hashvalue] = tmp;
			count++;
		}
		if (mas[hashvalue]->GetData() != elem.data && mas[hashvalue]->GetKey() == elem.key) {
			T temp = elem->GetData();
			temp.insert(temp.end(), elem.GetData().begin(), elem.GetData().end());
			TElemL<T>* tmp = new TElemL<T>(elem.key, temp, elem.next);
			tmp->SetNext(mas[hashvalue]);
			mas[hashvalue] = tmp;
			count++;
		}
	}
}*/

template <class T>
bool HashList<T>::Del(std::string _key)
{
	unsigned hashvalue = Hash(_key);
	if (hashvalue > (unsigned)size)
		return false;
	Elem<T>* iter = mas[hashvalue];
	Elem<T>* par = NULL;
	if (mas[hashvalue] == &notFound)
	{
		return false;
	}
	else if (mas[hashvalue]->GetNext() == NULL)
	{
		delete mas[hashvalue];
		count--;
		mas[hashvalue] = &notFound;
		return true;
	}
	else
	{
		while ((iter->GetNext() != NULL) && (iter->GetKey() != _key))
		{
			par = iter;
			iter = iter->GetNext();
		}
		if (iter->GetKey() == _key)
		{
			if (par != NULL)
				par->SetNext(iter->GetNext());
			else
				mas[hashvalue] = iter->GetNext();
			delete iter;
			count--;
			return true;
		}
	}
	return false;
}

template <class T >
Elem<T>& HashList<T>::Search(std::string _key)
{
	unsigned hashvalue = Hash(_key);
	if (hashvalue > (unsigned)size)
		return notFound;
	if (mas[hashvalue]->GetKey() == _key)
	{
		return (*mas[hashvalue]);
	}
	else if (mas[hashvalue]->GetNext() != NULL)
	{
		Elem<T>* iter = mas[hashvalue];
		while (iter != NULL)
		{
			if (iter->GetKey() == _key)
				return *iter;
			iter = iter->GetNext();
		}
	}
	return notFound;
}