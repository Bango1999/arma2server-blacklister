//list.cpp

#include "list.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <cstdlib>
using namespace std;

//----------------------------------------------
List::List() {
    
   Head = NULL;
}

//----------------------------------------------
//List::List(const List & list) {
//
//   // Create first node
//   Node *copy = new Node();
//   Head = copy;
//
//   // Walk list to copy nodes
//   Node *ptr = list.Head;
//   while (ptr != NULL)
//   {
//      copy->setNext(new Node());
//      copy = copy->getNext();
//      //copy->setFirstName(ptr->getFirstName());
//      //copy->setLastName(ptr->getLastName());
//      copy->setNext(NULL);
//      ptr = ptr->getNext();
//   }
//
//   // Tidy first node
//   copy = Head;
//   Head = copy->getNext();
//   delete copy;
//}

//----------------------------------------------

List::~List() {}

//---------------
//Function:     insertHead
//Purpose:      insert a new node as the head node
//---------------
void List::insertHead(string name, int id, string status) {
   
   // Insert new node
   Node *ptr = new Node(name,id,status);
   ptr->setNext(Head);
   Head = ptr;
}

//---------------
//Function:     insertTail
//Purpose:      insert a new node at the end of the list
//---------------
void List::insertTail(string name, int id, string status) {
   
    // Find tail node
   Node *ptr = Head;
   while ((ptr != NULL) && (ptr->getNext() != NULL)) //second condition will fail before the first, why have the first condition? (these conditions taken from one of my labs)
      ptr = ptr->getNext();

   // Insert new node
   if (ptr != NULL)
      ptr->setNext(new Node(name,id,status));
   else
      Head = new Node(name,id,status);

}

//---------------
//Function:     sortedInsert
//Purpose:      insert a new node and keep last names in alphabetical order in the list
//---------------
void List::sortedInsert(string name, int id, string status) {

        
    Node *ptr = Head;
    Node *temp = Head;
    Node *messy = Head;
    while (temp != NULL && (status.compare(temp->getStatus()) == 0 || status.compare(temp->getStatus()) == 1)) { //while the last name is equal to or greater than the name of the listed player
        
        //cout << temp->getLastName() << lastName.compare(temp->getLastName()) << endl;
        temp = temp->getNext(); //temp equals next pointer
        messy = temp->getNext(); //messy is the next one after temp
        
        if (status.compare(messy->getStatus()) != -1) { //sets pointer to equal the person who were adding a new node after
            ptr = temp;
            //cout << "Ptr = " << ptr->getLastName() << endl;
            //cout << "Temp = " << temp->getLastName() << endl;
        }
    }
    
    if (status.compare(ptr->getStatus()) == 1 || status.compare(ptr->getStatus()) == 0) { //if the person's last name is equal or greater than the last name in the ptr (making sure the boundary is still valid)
        ptr->setNext(new Node(name, id, status)); //add a new node after pointer, linked by the pointer
        ptr = ptr->getNext(); //set ptr equal to the node we just added
        //cout << "Pointer is now pointing to " << ptr->getLastName() << endl;
        //cout << "Setting ptr to link to " << temp->getLastName() << endl;
        ptr->setNext(temp); //link the new node to its next node in the chain
    
    } else { //if the boundary check failed, the code did not do its job, so just run insertHead on it
        List::insertHead(name, id, status);
    }
    
    
    
}

//---------------
//Function:     printAll
//Purpose:      print the stats of all of the players consecutively
//---------------
void List::printAll() const {
    
   Node *ptr = Head;
   if (Head == NULL)
       cout << "There are no players in the list!" << endl;
   else {
    cout << endl << "PLAYER NAME\t\t";
    cout << "PLAYER ID\t";
    cout << "STATUS" << endl;
    cout << "-----------\t\t";
    cout << "---------\t";
    cout << "------" << endl;
    while (ptr != NULL) { //print all nodes
        ptr->print();
        ptr = ptr->getNext();
    }
    cout << endl;
   }
}

void List::PrintNames() {
    Node *ptr = Head;
   if (Head == NULL)
       cout << "There are no players in the list!" << endl;
   else {
    while (ptr != NULL) { //print all nodes
        cout << ptr->getName() << endl;
        ptr = ptr->getNext();
    }
    cout << endl;
   }
}

void List::PrintBanned() {
    Node *ptr = Head;
   if (Head == NULL)
       cout << "There are no players in the list!" << endl;
   else {
    while (ptr != NULL) { //print all nodes
        if (ptr->getStatus() == "Banned" || ptr->getStatus() == "Banned (Definite Hacker)")
                cout << ptr->getName() << endl;
        ptr = ptr->getNext();
    }
    cout << endl;
   }
}

void List::PrintHackers() {
    Node *ptr = Head;
   if (Head == NULL)
       cout << "There are no players in the list!" << endl;
   else {
    while (ptr != NULL) { //print all nodes
        if (ptr->getStatus() == "Banned (Definite Hacker)")
                cout << ptr->getName() << endl;
        ptr = ptr->getNext();
    }
    cout << endl;
   }
}

void List::PrintNotBanned() {
    Node *ptr = Head;
   if (Head == NULL)
       cout << "There are no players in the list!" << endl;
   else {
    while (ptr != NULL) { //print all nodes
        if (ptr->getStatus() == "Not Banned")
                cout << ptr->getName() << endl;
        ptr = ptr->getNext();
    }
    cout << endl;
   }
}

//---------------
//Function:     printName
//Purpose:      match a given name with a name in the list, and print that player's stats
//---------------
void List::printName(string Name) {
    
   Node *ptr = Head;
   if (Head == NULL)
       cout << "There are no players in the list!" << endl;
   else {
       while (ptr->getName() != Name && ptr != NULL) //try to find a match
           ptr = ptr->getNext();
       if (ptr->getName() == Name) //if found, print it
           ptr->print();
       else
           cout << "Player not found..." << endl;
   }
}

//---------------
//Function:     deleteAll
//Purpose:      delete every node in the list
//---------------
void List::deleteAll() {
    
    while (Head != NULL) { //set head to what head next is pointing to, delete it, for every node
        Node* temp = Head;
        Head = Head->getNext();
        delete temp;
        temp=NULL; 
    }
    if (Head == NULL)
        cout << "List was deleted successfully..." << endl;
    else
        cout << "ERROR: Head still holds value." << endl;
}

bool List::deleteByID(int id)
{
   // Walk list to deletion point
   Node *curr = Head;
   Node *prev = Head;
   while ((curr != NULL) && (curr->getID() != id))
   {
      prev = curr;
      curr = curr->getNext();
   }

   // Check if value was found
   if (curr == NULL)
      return false;

   // Delete node from list
   if (curr == Head)
      Head = curr->getNext();
   else
      prev->setNext(curr->getNext());
   cout << endl << "Player " << curr->getName() << " deleted successfully" << endl << endl;
   delete curr;
   return true;
}



//SORTING
void List::SortByName() {
        Node * temphead = Head;
	int tempID;
	string tempname,tempstat;
	int counter = 0;
	while (temphead)
	{
		temphead = temphead->getNext();
		counter++;
	}
	temphead = Head;
	
	for (int j=0; j<counter; j++)
	{
		while (temphead->getNext())
		{
                    string current;
                    string next;
                    current = temphead->getName();
                    next = temphead->getNext()->getName();
                    
                    int curl = current.length();
                    int nexl = next.length();
                    for (int i = 0; i < curl; i++) {
                        if (current[i] >=65 && current[i] <= 90) {
                            current[i] = current[i] + 32;
                        }
                    }
                    for (int i = 0; i < nexl; i++) {
                        if (next[i] >= 65 && next[i] <= 90) {
                            next[i] = next[i] + 32;
                        }
                    }
                    //cout << next << " " << current << endl;
                    
			if (current > next)
			{
				tempID = temphead->getID();
				temphead->setID(temphead->getNext()->getID());
				temphead->getNext()->setID(tempID);

				tempname = temphead->getName();
				temphead->setName(temphead->getNext()->getName());
				temphead->getNext()->setName(tempname);
                                
                                tempstat = temphead->getStatus();
				temphead->setStatus(temphead->getNext()->getStatus());
				temphead->getNext()->setStatus(tempstat);
			}
			temphead = temphead->getNext();
		}	
		temphead = Head;
	}

}

void List::SortByID() {
        Node * temphead = Head;
	int tempID;
	string tempname,tempstat;
	int counter = 0;
	while (temphead)
	{
		temphead = temphead->getNext();
		counter++;
	}
	temphead = Head;
	
	for (int j=0; j<counter; j++)
	{
		while (temphead->getNext())
		{
			if (temphead->getID() > temphead->getNext()->getID())
			{
				tempID = temphead->getID();
				temphead->setID(temphead->getNext()->getID());
				temphead->getNext()->setID(tempID);

				tempname = temphead->getName();
				temphead->setName(temphead->getNext()->getName());
				temphead->getNext()->setName(tempname);
                                
                                tempstat = temphead->getStatus();
				temphead->setStatus(temphead->getNext()->getStatus());
				temphead->getNext()->setStatus(tempstat);
			}
			temphead = temphead->getNext();
		}	
		temphead = Head;
	}

}

void List::SortByStatus() {
        Node * temphead = Head;
	int tempID;
	string tempname,tempstat;
	int counter = 0;
	while (temphead)
	{
		temphead = temphead->getNext();
		counter++;
	}
	temphead = Head;
	
	for (int j=0; j<counter; j++)
	{
		while (temphead->getNext())
		{
			if (temphead->getStatus() > temphead->getNext()->getStatus())
			{
				tempID = temphead->getID();
				temphead->setID(temphead->getNext()->getID());
				temphead->getNext()->setID(tempID);

				tempname = temphead->getName();
				temphead->setName(temphead->getNext()->getName());
				temphead->getNext()->setName(tempname);
                                
                                tempstat = temphead->getStatus();
				temphead->setStatus(temphead->getNext()->getStatus());
				temphead->getNext()->setStatus(tempstat);
			}
			temphead = temphead->getNext();
		}	
		temphead = Head;
	}

}

int List::CSearchName(string name) {
	   // Walk list to find node
   Node *ptr = Head;
   string ptrname = "";
   //cout << "Names matching " << name << ":" << endl;
   for (int i = 0; i < name.length(); i++) {
	   if (name[i] >=65 && name[i] <= 90) {
		   name[i] = name[i] + 32;
	   }
   }

   while (ptr != NULL) {
       string n = "";
       for (int i = 0; i < ptr->getName().length();i++) {
           n += ptr->getName()[i];
		   if (n[i] >= 65 && n[i] <= 90) {
			   n[i] = n[i] + 32;
		   }
       }
       //cout << n << endl;
       if (n != name) {
        ptr = ptr->getNext();
       } else {
           break;
       }
   }
   if (ptr != NULL) {
       return ptr->getID();
   } else {
       return 0;
   }
}

int List::searchByName(string name)
{
   // Walk list to find node
   Node *ptr = Head;
   string ptrname = "";
   cout << "Names matching " << name << ":" << endl;
   for (int i = 0; i < name.length(); i++) {
	   if (name[i] >=65 && name[i] <= 90) {
		   name[i] = name[i] + 32;
	   }
   }

   while (ptr != NULL) {
       string n = "";
       for (int i = 0; i < ptr->getName().length();i++) {
           n += ptr->getName()[i];
		   if (n[i] >= 65 && n[i] <= 90) {
			   n[i] = n[i] + 32;
		   }
       }
	   if (name.length() <= n.length()) {
			size_t index;
			index = n.find(name);
			if (index <= ptr->getName().length()) {
				cout << ptr->getName() << endl;
			}
	   }
       //cout << n << endl;
       if (n != name) {
        ptr = ptr->getNext();
       } else {
           break;
       }
   }
   if (ptr != NULL) {
       return ptr->getID();
   } else {
       return 0;
   }
}

int List::searchByID(int id)
{
   // Walk list to find node
   Node *ptr = Head;
   while ((ptr != NULL) && (ptr->getID() != id))
      ptr = ptr->getNext();
   if (ptr != NULL) {
       return ptr->getID();
   } else {
       return 0;
   }
}

string List::GetName(int id) {
       // Walk list to find node
   Node *ptr = Head;
   while ((ptr != NULL) && (ptr->getID() != id))
      ptr = ptr->getNext();
   if (ptr != NULL) {
       return ptr->getName();
   } else {
       return "ERROR";
   }
}

string List::GetStatus(int id) {
       // Walk list to find node
   Node *ptr = Head;
   while ((ptr != NULL) && (ptr->getID() != id))
      ptr = ptr->getNext();
   if (ptr != NULL) {
       return ptr->getStatus();
   } else {
       return "ERROR";
   }
}

void List::Back() {
	ifstream bans, bl, black;
	bans.open("../../../ban.txt");
	black.open("../../../Blacklist.txt");
	bl.open("../../../Blacklist.bl");
	if (bans.is_open() && bl.is_open() && black.is_open()) {

		string blLine;
		string blackLine;
		string banLine;

		ofstream obans,obl,oblack;
		obans.open("../../../ban-BACKUP.txt");
		obl.open("../../../Blacklist-BACKUP.bl");
		oblack.open("../../../Blacklist-BACKUP.txt");
		if (obans.is_open() && obl.is_open() && oblack.is_open()) {

			//all files open and ready to do their job
			int f = 0;
			while (!bans.eof()) {
				getline(bans,banLine);
				if (f == 0) {
					obans << banLine;
					f++;
				} else {
					obans << "\n" << banLine;
				}
			}
			//cout << "ban backed up" << endl;
			int first = 0;
			while (!bl.eof()) {

				getline(bl,blLine);
				if (first == 0) {
					obl << blLine;
					first++;
				} else {
					obl << "\n" << blLine;
				}
			}
			//cout << "bl backed up" << endl;
			int b = 0;
			while (!black.eof()) {
				getline(black,blackLine);
				if (b == 0) {
					oblack << blackLine;
					b++;
				} else {
					oblack << "\n" << blackLine;
				}
			}
			//cout << "blacklist backed up" << endl;

			obl.close();
			oblack.close();
			obans.close();
			bans.close();
			black.close();
			bl.close();


		} else {
			if (!obans.is_open()) {
				cout << "ERROR: could not open file 'ban-BACKUP.txt' for writing" << endl;
			}
			if (!oblack.is_open()) {
				cout << "ERROR: could not open file Blacklist-BACKUP.txt' for writing" << endl;
			}
			if (!obl.is_open()) {
				cout << "ERROR: could not open file 'Blacklist-BACKUP.bl' for writing" << endl;
			}
			obl.close();
			oblack.close();
			obans.close();
			bans.close();
			black.close();
			bl.close();
			return;
		}

	} else {
		if (!bans.is_open()) {
			cout << "ERROR: Could not open file 'ban.txt' for reading" << endl;
		}
		if (!bl.is_open()) {
			cout << "ERROR: Could not open file 'Blacklist.bl' for reading" << endl;
		}
		if (!black.is_open()) {
			cout << "ERROR: Could not open file 'Blacklist.txt' for reading" << endl;
		}
		bans.close();
		bl.close();
		black.close();
		return;
	}
	cout << endl << "Blacklist backed up" << endl << endl;
}

void List::SaveAs(string filename) {
	//cout << "made it to saveas\nfilename = " << filename << endl;
	string line;
	ifstream inbl;
	inbl.open("../../../Blacklist.bl");
	if (inbl.is_open()) {
		ofstream outbl;
		outbl.open(filename.c_str());
		if (outbl.is_open()) {
			int first = 0;
			while (!inbl.eof()) {
				getline(inbl,line);
				if (first == 0) {
					outbl << line;
					first++;
				} else {
					outbl << "\n" << line;
				}
			}
			cout << endl << "Backup " << filename << " created" << endl << endl;
		} else {
			cout << "ERROR: Could not open file '" << filename << "' to write" << endl;
		}
		outbl.close();
	} else {
		cout << "ERROR: Could not open file 'Blacklist.bl' to read" << endl;
	}
	inbl.close();
}

void List::UpdateBlack() {
    int biggest = 0;
    
    ifstream longest;
    longest.open("../../../Blacklist.bl");
    if (longest.is_open()) {
        int count = 0;
        string test;
        string bigstring;
        while (!longest.eof()) {
            if (count == 0) {
                getline(longest,test);
                //cout << test << endl;
                count++;
            } else {
                getline(longest,test);
                getline(longest,test);
                getline(longest,test);
                //cout << test << endl;
                count++;
            }
            if (test.length() > biggest) {
                biggest = test.length();
                bigstring = test;
            }
        }
        //cout << "longest name is " << bigstring << " at " << biggest << " characters" << endl;
        longest.close();
    } else {
        cout << "Error: Could not open file 'Blacklist.bl' to read contents..." << endl;
        longest.close();
        return;
    }
    
    
    ofstream black;
    ofstream bl;
    black.open("../../../Blacklist.txt");
    bl.open("../../../Blacklist.bl");
    if (black.is_open() && bl.is_open()) {
        Node *ptr = Head;
        if (Head == NULL) {
            cout << "Head is Null" << endl;
            black.close();
            bl.close();
            return;
        }
        int k = 0;
        biggest = biggest+5;
        int p = biggest-11;
        int ol = 0;
        string pname = "PLAYER NAME";
        string idandstat = "PLAYER ID     PLAYER STATUS";
        black << pname;
        for (int i = 0; i < p; i++) {
            black << " ";
            ol++;
        }
        black << idandstat << "\r\n";
        ol = ol + pname.length() + idandstat.length();
        for (int i = 0; i < ol; i++) {
            black << "-";
        }
        black << "\r\n\r\n";
        
        
        while (ptr != NULL) {
            
            //bl
            if (k == 0) {
                bl << ptr->getName() << "\n" << ptr->getID() << "\n" << ptr->getStatus();

            } else {
                bl << "\n" << ptr->getName() << "\n" << ptr->getID() << "\n" << ptr->getStatus();
            }
            
            //blacklist
            black << ptr->getName();
            p = biggest - ptr->getName().length();
            for (int i = 0; i < p; i++) {
                black << " ";
            }
            black << ptr->getID();
            stringstream convert;
            convert << ptr->getID();
            string id = convert.str();
            p = 13 - (id.length());
            for (int i = 0; i < p; i++)
                black << " ";
            black << ptr->getStatus() << "\r\n";
            
            
            k++;
            ptr = ptr->getNext();
        }
        black.close();
        bl.close();
    } else {
        if (!black.is_open()) {
            cout << "Error: Could not open the file 'Blacklist.txt'. Make sure you have the appropriate permissions..." << endl;
            bl.close();
            black.close();
            return;
        }
        if (!bl.is_open()) {
            cout << "Error: Could not open the file 'Blacklist.bl'. Make sure you have the appropriate permissions..." << endl;
            black.close();
            bl.close();
            return;
        }
    }
    cout << endl <<  "Blacklist updated" << endl << endl;
}

void List::UpdateBan() {
    ofstream bans;
    //int c = 0;
    bans.open("../../../ban.txt");
    if (bans.is_open()) {
        Node *ptr = Head;
        if (Head == NULL) {
            cout << "Head is null" << endl;
            return;
        }
        while (ptr != NULL) {
            string stat = "";
            int len = ptr->getStatus().length();
            for (int i = 0; i < len; i++) {
                stat += ptr->getStatus()[i];
            }
            if (stat == "Banned" || stat == "Banned (Definite Hacker)") {
				if ((ptr->getNext() != NULL) && ptr->getID() != ptr->getNext()->getID()) {
                //c++;
                bans << ptr->getID() << "\n";
				}
            }
            ptr = ptr->getNext();
        }
    } else {
        cout << "ERROR: Could not open 'ban.txt'. Make sure you have the appropriate permissions..." << endl;
        return;
    }
	//cout << "exited loop" << endl;
    bans.close();
    //cout << "ban.txt updated: " << c << " IDs in list." << endl;
}

void List::SetStat(int id, string newStat) {
	// Walk list to find node
   Node *ptr = Head;
   while ((ptr != NULL) && (ptr->getID() != id))
      ptr = ptr->getNext();
   if (ptr != NULL) {
	   cout << "changed " << ptr->getStatus() << " to ";
	   ptr->setStatus(newStat);
	   cout << ptr->getStatus() << endl;
   } else {
       cout << "No Such player in list!" << endl;
   }
}