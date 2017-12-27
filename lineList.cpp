#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <vector>
using namespace std;

class LineListException {
public:
	LineListException() {
		cout << "Error" << endl;
		_getch();
	}
	~LineListException() {}
};

template <class T>
class LineListElem {
	T data;
	LineListElem* next;
public:
	LineListElem(const T& adata, LineListElem* anext) {
		data = adata;
		next = anext;
	}
	const T& getData() const {
		return data;
	}

	LineListElem* getNext() {
		return next;
	}
	// В объявлениях друзей 
	// template повторяется
	template <class T> friend class LineList;
};


template<class T>
class LineList {
	LineListElem<T>* start;// Начало списка
	LineList(const LineList& list) // Зачем?
	{
		*this = list;
	}
	LineList& operator =(const LineList& list) {
		start = list.start;
		return *this;
	}

	LineListElem<T>* GetPtrElem(int index) {//указатель на искомый Index, с 0
		LineListElem<T>* it = start;
		int i = 0;
		if (!it || index <0) throw LineListException();
		for (; it && i++<index; it = it->getNext())
			if (!it) throw LineListException();
		return it;
	}
public:
	LineList() : start(0) {}
	~LineList() {
		while (start)
			deleteFirst();
	}

	void insertAfter(LineListElem<T>* ptr, const T& data);

	void insertFirst(const T& data) {
		LineListElem<T>* second = start;
		start = new LineListElem<T>(data, second);
	}

	LineListElem<T>* getStart() { return start; }

	void deleteFirst() {
		if (start) {
			LineListElem<T>* temp = start->next;
			delete start;
			start = temp;
		}
		else throw LineListException();
	}

	void deleteAfter(LineListElem<T>* ptr) {
		if (ptr && ptr->next) {
			LineListElem<T>* temp = ptr->next;
			ptr->next = ptr->next->next;
			delete temp;
		}
		else throw LineListException();
	}

	void del(int index) {//удалёниё п0 индёксу, с 0
		if (index == 0)	deleteFirst();
		else {
			LineListElem<T>* ptr = GetPtrElem(index - 1);
			deleteAfter(ptr);
		}
	}

	friend ostream& operator << <T>(ostream &out, const LineList<T> &list) {
		LineListElem<T>* ptr = list.start;
		if (!ptr)
			out << "EMPTY";
		else while (ptr) {
			out << ptr->getData() << ' ';
			ptr = ptr->getNext();
		}
		return out;
	}

	void insert(int index, const T& data) {
		if (index == 0) insertFirst(data);
		else if (GetPtrElem(index - 1)) {
			LineListElem<T>* ptr = GetPtrElem(index - 1);
			insertAfter(ptr, data);
		}
		else  throw LineListException();
	}

	vector<int> search(T a) {//поиск по значению
		LineListElem<T>* it = start;
		int index = 0, i = 0;
		vector<int> mind;
		while (it) {
			if (it->getData() == a) {
				mind.push_back(index);
			}
			it = it->getNext();
			index++;
		}
		return mind;
	}
	void printSearch(T a) {//вывод поиска
		vector<int> mind = search(a);
		for (int i = 0; i < mind.size(); i++)
		{
			cout << "Индекс значения " << a<< " : " << mind[i] << endl;
		}
	}
};
// Требования к T?
template <class T> void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data) {
	if (ptr) {
		LineListElem<T>* temp = ptr->next;
		ptr->next = new LineListElem<T>(data, temp);
	}
}
void main()
{
	setlocale(LC_ALL, "Russian");
	LineList<int> list;// Указываем, список какого типa
	cout << "Начало: ";
	cout << list << endl;
	list.insertFirst(10);
	LineListElem<int>* ptr = list.getStart();
	list.insertAfter(ptr, 15);
	list.insertAfter(ptr->getNext(), 12);
	list.insertFirst(7);
	cout << "Шаг1: " << list << endl;
	list.del(2);
	cout << "Шаг2: " << list << endl;
	list.insert(1, 7);
	cout << "Шаг3: " << list << endl;
	list.printSearch(7);
	_getch();
}
