#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include "utilities.h"
#include <iostream>

using namespace std;

// Node class
class Node {


public:

	double data;
	Node *next;


	//Constructor with initial value
	Node(double val) : data(val) {}

	friend class NodeList;
};

//Linked List - Queue Class
class NodeList {
public:

	Node *head;
	Node *tail;
	Node *v;


	NodeList();
	NodeList(double);
	NodeList(int);
	void display();
	Node* push(double);

	//accessor function to get head node
	//NodeList* getHeadPtr(NodeList);
};

// Creates a list of Nodes of predetermined length
// i.e., length of filter order for this particular application
NodeList::NodeList()
{
	head = new Node(0.0);
	head->next = NULL;
	tail = head;

	for (int i = 0; i < filterOrder-1; i++) { //Substitute 3 with filterOrder-1
		v = new Node(0.0);
		v->next = head;
		head = v;
	}

}

NodeList::NodeList(int length)
{
	head = new Node(0.0);
	head->next = NULL;
	tail = head;

	for (int i = 0; i < length; i++) { //Substitute 3 with filterOrder-1
		v = new Node(0.0);
		v->next = head;
		head = v;
	}

}

NodeList::NodeList(double x)
{
	head = new Node(x);
	head->next = NULL;
	tail = head;

}

void NodeList::display()
{
	Node *cur = head;

	while (cur)
	{
		cout << cur->data << endl;
		cur = cur->next;
	}
}

// Pushes a node to the front of the list
// and pushes the tail out of the list
// This Abstract Data Type acts as a Linked-List Queue
Node* NodeList::push(double y){
	v = new Node(y);
	v->next = head;
	head = v;

	Node *cur = head;
	while (cur) {
		if (cur->next == tail) {
			tail = cur;
			delete cur->next;
			cur->next = NULL;
		}
		cur = cur->next;
	}

	return head;
}



// Send measurements through filter 
// i.e., convolve with filter's impulse response
double filter(Node *wptr, Node *xptr) {

	double out = 0.0;

	for (int i = 0; i < filterOrder-1; i++) {
		out += wptr->data * xptr->data;
		wptr = wptr->next;
		xptr = xptr->next;
	}

	return out;
	
}

Node *adapt(Node *w, Node *xptr, double e) {
	Node *cur = w;
	for (int j = 0; j < filterOrder-1; j++) {
		cur->data += 2*beta * e * xptr->data;
		cur = cur->next;
		xptr = xptr->next;
	}
	return w;
	}


#endif
