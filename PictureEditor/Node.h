#ifndef NODE_H
#define NODE_H
enum Error_code{underflow, overflow, rangeError, success, duplicateKey,notPresent};
template <class Node_entry>
struct Node {
// data members
	Node_entry entry;
	Node<Node_entry> *next;
// constructors
	Node( );
	Node(Node_entry item, Node<Node_entry> *link = NULL);
};
#endif