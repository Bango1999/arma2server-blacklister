//Node.h

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

//-----------------------------------------------------------
// Node definitions 
//-----------------------------------------------------------
class Node {
 public:
   // Constructors 
   Node();
   Node(string name, int id, string status);
   //Node(const Node & node);
   ~Node();

   // Get methods
   string getName() const;
   string getStatus() const;
   int getID() const;
   Node *getNext() const;

   // Set methods
   void setName(const string name);
   void setStatus(const string status);
   void setID(const int ID);
   void setNext(Node * next);
   
   //Sort Methods
   void NameSort();
   void IDSort();
   void StatSort();

   // Other methods
   void print();
   


 private:
   Node *Next;
   string NAME, STATUS;
   int ID;

};


