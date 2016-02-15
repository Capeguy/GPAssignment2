//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#ifndef LIST_H
#define LIST_H

#include <string>
#include <iostream>

template<class ItemType>
class List
{
private:
	struct Node
	{
		ItemType item;
		Node *next;
	};
	Node *firstNode;
	int size;
public:
	List();
	bool add(ItemType newItem);
	bool add(int index, ItemType newItem);
	ItemType get(int index);
	void remove(int index);
	void clear();
	int getLength();
	bool isEmpty();
	void print();
};

#endif