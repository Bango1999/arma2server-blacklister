//list.h

#include "Node.h"
using namespace std;

//-----------------------------------------------------------
// List definitions 
//-----------------------------------------------------------
class List {
 public:
   // Constructors 
   List();
   List(const List & list);
   ~List();

   // Methods
   void insertHead(string name, int id, string status);
   void insertTail(string name, int id, string status);
   void sortedInsert(string name, int id, string status);
   void printAll() const;
   void printName(const string Name);
   bool deleteByID(int id);
   int searchByName(string name);
   int CSearchName(string name);
   int searchByID(int id);
   void deleteAll();
   string GetName(int id);
   string GetStatus(int id);
   void PrintNames();
   void PrintBanned();
   void PrintNotBanned();
   void PrintHackers();
   
   void SortByName();
   void SortByID();
   void SortByStatus();
   
   void UpdateBlack();
   void SaveAs(string filename);
   void UpdateBan();
   void Back();

   void SetStat(int id, string newStat);

 private:
     Node * Head;
};
