#pragma once
#include<iostream>
using namespace std;

void chapter_14_stack();

/*------------*/
/* Node Below */

template <typename T>
class Node
{
public:
	T _data;
	string _tag;
	Node* _nextptr;
	Node* _prevptr;

	Node();
	Node(T);
	Node(T, string);
	void print() const;
	Node<T>* operator++();
	Node<T>* operator++(int);
	Node<T>* operator--();
	Node<T>* operator--(int);
};


template <typename T>
Node<typename T>::Node()
{
	_nextptr = NULL;
	_prevptr = NULL;
}

template <typename T>
Node<typename T>::Node(T data):_data(data), _tag("e")
{
	_nextptr = NULL;
	_prevptr = NULL;
}

template <typename T>
Node<typename T>::Node(T data, string tag) :_data(data), _tag(tag)
{
	_nextptr = NULL;
	_prevptr = NULL;
}

template <typename T>
void Node<typename T>::print() const
{
	cout << "[" << _tag << "] " << _data << endl;
}


template <typename T>
Node<T>* Node<typename T>::operator++()
{
	return this->_nextptr;
}
template <typename T> // no difference
Node<T>* Node<typename T>::operator++(int)
{
	return this->_nextptr;
}
template <typename T>
Node<T>* Node<typename T>::operator--()
{
	return this->_prevptr;
}
template <typename T> // no difference
Node<T>* Node<typename T>::operator--(int)
{
	return this->_prevptr;
}


/*-------------------*/
/* Linked List Below */

template <typename T>
class LinkedList
{
protected:
	Node<T> *_headerptr;
	Node<T> *_trailerptr;
	int _size;

public:
	LinkedList();
	Node<T>* get_headerptr() { return _headerptr; };
	Node<T>* get_trailerptr() { return _trailerptr; };
	bool isEmpty() { return _size == 0; };
	bool isFull() { return false; }; // 링크드리스트 구현
	void print(bool reverse = false);
	void addLast(T);
	T removeLast();
};

template <typename T>
LinkedList<T>::LinkedList()
{
	_size = 0;
	_headerptr = new Node<T>(-1, "header");
	_trailerptr = new Node<T>(-1, "trailer");
	_headerptr->_nextptr = _trailerptr;
	_trailerptr->_prevptr = _headerptr;
}

template <typename T>
void LinkedList<T>::print(bool reverse)
{
	if (reverse)
	{
		Node<T>* ptr = _headerptr->_nextptr;
		while (ptr->_nextptr != NULL)
		{
			ptr->print();
			ptr = ptr->_nextptr;
		}
	}
	else
	{
		Node<T>* ptr = _trailerptr->_prevptr;
		while (ptr->_prevptr != NULL)
		{
			ptr->print();
			ptr = ptr->_prevptr;
		}
	}
}

template <typename T>
void LinkedList<T>::addLast(T data)
{
	if (isFull())
	{
		return;
	}

	Node<T>* ptr_prev = _trailerptr->_prevptr;
	Node<T>* ptr_next = _trailerptr;

	Node<T>* newnode;
	newnode = new Node<T>(data);
	newnode->_nextptr = ptr_next;
	newnode->_prevptr = ptr_prev;
	ptr_prev->_nextptr = newnode;
	ptr_next->_prevptr = newnode;

	_size++;
}

template <typename T>
T LinkedList<T>::removeLast()
{
	if (isEmpty())
	{
		return;
	}

	Node<T>* ptr_target = _trailerptr->_prevptr;
	Node<T>* ptr_prev = ptr_target->_prevptr;
	Node<T>* ptr_next = _trailerptr;
	
	_size--;

	T e = ptr_target->_data;
	// 구현안됨

	return e;
}


/*-------------*/
/* Stack Below */

template <typename T>
class Stack : LinkedList<T>
{
protected:
	Node<T>* _top;

public:
	Stack();
	void push(T);
	T pop();
	void print();
	T top();
};

template <typename T>
Stack<T>::Stack()
{
	LinkedList<T>();
	_top = this->get_headerptr();
}

template <typename T>
void Stack<T>::push(T data)
{
	this->addLast(data);
	_top++;
}

template <typename T>
T Stack<T>::pop()
{
	T e = this->removeLast();
	_top--;
	delete _top->_nextptr;
	return e;
}

template <typename T>
void Stack<T>::print()
{
	LinkedList<T>* li = new LinkedList<T>;
	li = this;
	li->print(true);
}

template <typename T>
T Stack<T>::top()
{
	return _top->_data;
}
