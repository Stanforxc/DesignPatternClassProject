#pragma once

#include"Node.cpp"
template <class List_entry>
class List {
public:
// Specifications for the methods of the list ADT go here.
// The following methods replace compiler-generated defaults.
	~List( );
	List( );
	List(const List<List_entry> &copy);
	void operator = (const List<List_entry> &copy);
	int size( ) const;
	bool full( ) const;
	bool empty( ) const;
	void clear( );
	void traverse(void (*visit)(List_entry &));
	Error_code retrieve(int position, List_entry &x) const;
	Error_code replace(int position, const List_entry &x);
	Error_code remove(int position, List_entry &x);
	Error_code insert(int position, const List_entry &x);
protected:
// Data members for the linked list implementation now follow.
	int count;
	mutable int current_position;
	mutable Node<List_entry> *current;
	Node<List_entry> *head;
// The following auxiliary function is used to locate list positions
	void set_position(int position) const;
};