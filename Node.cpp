//Node.cpp

#include "Node.h"
#include <sstream>

//----------------------------------------------
Node::Node() {
   
   NAME = STATUS = "";
   ID = 0;
   Next = NULL;
}

//----------------------------------------------
Node::Node(string name, int id, string status) {
   
    NAME = name;
    ID = id;
    STATUS = status;
    Next = NULL;
}
Node::~Node() {}

//---------------
//Function:     getName
//Purpose:      return the player's name
//---------------
string Node::getName() const {
    
   return NAME;
}

//---------------
//Function:     getStatus
//Purpose:      return the player's ban status
//---------------
string Node::getStatus() const {
    
   return STATUS;
}

//---------------
//Function:     getID
//Purpose:      return the player's ID
//---------------
int Node::getID() const {
		return ID;
}

//---------------
//Function:     GetNext
//Purpose:      return the node that the current node points to
//---------------
Node *Node::getNext() const {
    
   return Next;
}
//---------------
//Function:     setStatus
//Purpose:      set the status
//---------------
void Node::setStatus(string status) {
    
   STATUS = status;
}

//---------------
//Function:     setName
//Purpose:      set the players name
//---------------
void Node::setName(string name) {
    
   NAME = name;
}

//---------------
//Function:     setTD
//Purpose:      set the touchdowns value
//---------------
void Node::setID(int id) {
    
   ID = id;
}

//---------------
//Function:     setNext
//Purpose:      point a node to another node when you want the next node
//---------------
void Node::setNext(Node * next) {

   Next = next;
}

//---------------
//Function:     print
//Purpose:      print out the player's information in a pretty way
//---------------
void Node::print() {
    
    string spaces = "";
    stringstream stream;
    stream << ID;
    string idspace = stream.str();
    int len = idspace.length();
    string putme = "";
    for (int i = 0; i < 16-len; i++) {
        putme += " ";
    }
    for (int i = 0; i < 24-NAME.length(); i++)
        spaces+= " ";
    cout << NAME;
    cout << spaces;
    cout << ID << putme;
    cout << STATUS << endl;
}




