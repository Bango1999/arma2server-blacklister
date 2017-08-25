//main.cpp

/* ----------------------------------
 *
 * SERVER BLACKLIST
 * Author:       Bango
 * Date:         5/9/15
 *
 * ---------------------------------*/

//#include "list.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

// int main (int argc, char* argv[]) {
//
// 	string run = "./run";
// 	string query = "./query";
//
// 	if (strcmp(argv[0],"./run") == 0) {
// 		  cout << "./run" << endl;
// 	} else if (strcmp(argv[0],"./query") == 0) {
// 		  cout << "./query" << endl;
// 	} else {
// 		cout << argv[0] << "!" << endl;
// 	}
//
// 	return 0;
// }


void Test() {
    ifstream ban;
    ban.open("../ban.txt");
    if (ban.is_open()) {
        string x;
        getline(ban,x);
        cout << x << endl;
    } else {
        cout << "NO!" << endl;
    }
}
//---------------
// Function:     read file
// Purpose:      read in the text file, store values in player nodes
//---------------
void ReadFile(List& blacklist, int &count) {

    string name,status,sid;
    char cid[8];
    int id;
    ifstream read;
    read.open("../../../Blacklist.bl");
    if (read.is_open()) {
        while (!read.eof()) {
            getline(read,name);
            getline(read,sid);
            if (sid.length() == 8) {
                //cout << "id = 8 digits" << endl;
                for (int i = 0; i < 8; i++) {
                    cid[i] = sid[i];
                }
            } else if (sid.length() == 7) {
                //cout << "id = 7 digits" << endl;
                for (int i = 0; i < 7; i++) {
                    cid[i] = sid[i];
                }
            } else if (sid.length() == 6) {
				for (int i = 0; i < 6; i++) {
					cid[i] = sid[i];
				}
			} else {
                cout << "Error: an ID is not equal to 6, 7 or 8 characters!" << endl;
                cout << "length is " << sid.length() << endl;
                cout << sid << endl;
                return;
            }
            id = atoi(cid);
            getline(read,status);

            blacklist.insertTail(name,id,status);//make a new node, adding each player to the end of the list
            count++;//increment count to see how many players were added in all
        }
    } else {
        cout << "Could not access the file 'Blacklist.bl'" << endl;
    }
    read.close();
    //cout << "Found " << count << " players in list" << endl;

}

bool YesNo(string input) {
    if (input == "y" || input == "Y" || input == "yes") {
        return true;
    } else {
        return false;
    }
}

//---------------
// Function:     add player
// Purpose:      add a new player node
//---------------
void AddPlayer(List& blacklist, string input, int &count) {
    string name, sid, yn = "";
    char cid[8];
	char cid7[7];
    bool cancel = false;
    int id, stat, index = 0;




    //if plain add
    if (input == "add") {
        cout << "Name: ";
        getline(cin,name);
        cout << "ID: ";
        getline(cin,sid);
        while (sid.length() != 8 && sid.length() != 7) {
            //cout << "id is " << sid.length() << " digits" << endl;
            cout << "ERROR: ID is not 7 or 8 digits! Do you want to try again (y/n): ";
            getline(cin,yn);
            if (YesNo(yn)) {
                cout << "ID: ";
                getline(cin,sid);
            } else {
                cancel = true;
                break;
            }
        }
        bool badFlag = false;
        int len = sid.length();
        //cout << len << endl;
        if (len == 8) {
            for (int i = 0; i < 8; i++) {
                if (sid[i] < 48 || sid[i] > 57) {
                    cout << "error " << sid[i] << endl;
                    badFlag = true;
                    break;
                }
            }
        } else if (len == 7) {
            for (int i = 0; i < 7; i++) {
                if (sid[i] < 48 || sid[i] > 57) {
                    cout << "error2 " << sid[i] << endl;
                    badFlag = true;
                    break;
                }
            }
        } else {
			//cout << "Got here" << endl;
		}
        while (badFlag) {
            cout << "ERROR: ID is invalid! It must be digits (0-9). Do you want to try again (y/n): ";
            getline(cin,yn);
            if (YesNo(yn)) {
                cout << "ID: ";
                getline(cin,sid);
                len = sid.length();
                //cout << len << endl;
                bool badFlag2 = false;
                if (len == 8) {
                    for (int i = 0; i < 8; i++) {
                            if (sid[i] < 48 || sid[i] > 57) {
                                cout << "error " << sid[i] << endl;
                                badFlag2 = true;
                                break;
                            }
                    }
                    if (!badFlag2) {
                        badFlag = false;
                    }
                } else if (len == 7) {
                    for (int i = 0; i < 7; i++) {
                            if (sid[i] < 48 || sid[i] > 57) {
                                cout << "error2 " << sid[i] << endl;
                                badFlag2 = true;
                                break;
                            }
                    }
                    if (!badFlag2) {
                        badFlag = false;
                    }
                }
            } else {
                cancel = true;
                break;
            }
        }

    //if adding an argument
    } else if (input[3] == ' ' && input[4] == '-') {
        //name argument
        if (input[5] == 'n' && input[6] == ' ') {
            for (index = 7; index < input.length(); index++) {
                if (input[index] == ' ' && input[index+1] == '-' && input[index+2] == 'i') {
                    //cout << "Found break" << endl;
                    //cout << input[index] << input[index+1] << input[index+2] << endl;
                    break;
                } else {
                    name += input[index];
                }
            }
        } else {
            cout << "ERROR: syntax for add is 'add -n playerName -i 12345678" << endl;
            cancel = true;
        }
        //id argument
        int chars8 = 0;
        //cout << "argument = x" << input[index] << input[index+1] << input[index+2] << input[index+3] << "x" << endl;
        if (!cancel && (input[index] == ' ' && input[index+1] == '-' && input[index+2] == 'i' && input[index+3] == ' ')) {
            index = index+4;
            for (int i = index; i < input.length(); i++) {
                if (input[i] >= 48 && input[i] <= 57) {
                    // << "Adding " << input[i] << endl;
                    //cout << "index = " << i << endl;
                    sid += input[i];
                    chars8++;
                    //cout << "chars8 inc to " << chars8 << endl;
                    index++;
                } else {
                    cout << "ERROR: Player ID is not valid.  Do you want to try again? (y/n): ";
                    getline(cin, yn);
                    if (YesNo(yn)) {
                        input = "add";
                        AddPlayer(blacklist,input, count);
                    }
                    cancel = true;
                }
            }
            //cout << "SID = " << sid << endl;

            if (!cancel && (chars8 != 8 && chars8 != 7)) {
                cancel = true;
                //cout << chars8 << endl;
                //cout << "index at finish = " << index << endl;
                cout << "ERROR: ID is not 7 or 8 characters. Do you want to try again? (y/n): ";
                getline(cin, yn);
                if (YesNo(yn)) {
                    input = "add";
                    AddPlayer(blacklist,input,count);
                }
            }

        } else {
            cout << "ERROR: syntax for add is 'add -n playerName -i 12345678" << endl;
            cancel = true;
        }
    } else {
        cout << "ERROR: add accepts arguments '-n' and '-i' or no argument." << endl;
        cancel = true;
    }


    if (!cancel) {
        string choice;
		int len = sid.length();
		if (len == 8) {
			for (int i = 0; i < 8; i++)
				cid[i] = sid[i];
		} else if (len == 7) {
			for (int i = 0; i < 7; i++)
				cid[i] = sid[i];
		}
        id = atoi(cid);

        //STATUS
        string status[4] = {"Banned","Banned (Definite Hacker)","Not Banned","N/A"};
        cout << "Enter the number corresponding to the player's Status:" << endl;
        cout << "1) " << status[0] << endl;
        cout << "2) " << status[1] << endl;
        cout << "3) " << status[2] << endl;
        cout << "4) " << status[3] << endl;
        cout << "admin@BlackList: ";
        getline(cin,choice);
        while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "exit") {
            cout << "ERROR: Incorrect input (1-4).  Please try again." << endl;
            cout << "Enter the number corresponding to the player's Status:" << endl;
                cout << "1) " << status[0] << endl;
                cout << "2) " << status[1] << endl;
                cout << "3) " << status[2] << endl;
                cout << "4) " << status[3] << endl;
                cout << "admin@BlackList: ";
                getline(cin,choice);
        }
        if (choice != "exit") {
        char ch[1] = {choice[0]};

        stat = atoi(ch);
        stat = stat-1;
        //cout << stat << endl;

        blacklist.insertHead(name,id,status[stat]);
        count++;
        cout << endl << "Player added successfully" << endl << endl;
        }
    }
}



string GetInput(string before) {
    string input = "";
    cout << before;
    getline(cin, input);
    return input;
}

void Sort(List& blacklist, string &input) {
    if (input == "sort -n") {
        blacklist.SortByName();
		cout << endl << "Blacklist was sorted by Player Name" << endl << endl;
    } else if (input == "sort -i") {
        blacklist.SortByID();
		cout << endl << "Blacklist was sorted by Player ID" << endl << endl;
    } else if (input == "sort -s") {
        blacklist.SortByStatus();
		cout << endl << "Blacklist was sorted by Player Status" << endl << endl;
    } else {
        string i;
        cout << "What field do you want to sort by?" << endl << endl;
        cout << "1) Name" << endl;
        cout << "2) ID" << endl;
        cout << "3) Status" << endl;
        cout << "admin@BlackList: ";
        getline(cin,i);
        while (i != "1" && i != "2" && i != "3" && i != "exit") {
            cout << "ERROR: Incorrect input. Please choose a number 1-3 : ";
            getline(cin,i);
        }
        if (i == "exit") {
            input = "exit";
            return;
        } else if (i == "1") {
            input = "sort -n";
            Sort(blacklist,input);
            //cout << endl << "Blacklist was sorted by Player Name" << endl << endl;
            return;
        } else if (i == "2") {
            input = "sort -i";
            Sort(blacklist,input);
            //cout << endl << "Blacklist was sorted by Player ID" << endl << endl;
            return;
        } else if (i == "3") {
            input = "sort -s";
            Sort(blacklist,input);
            //cout << endl << "Blacklist was sorted by Player Status" << endl << endl;
            return;
        }

    }
}


void QSort(List& blacklist, string &input) {
	blacklist.SortByID();
}

void Delete(List& blacklist, string &input, int &count) {
    char Id[8];
    char Id7[7];
    int pid;
    if (input == "delete") {
        string id;
        cout << "Enter Player ID: ";
        getline(cin, id);
        while (id.length() != 8 && id.length() != 7) {
            if (id.length() < 7) {
                cout << "ERROR: ID is too short, it must be 7 or 8 digits! Try again: ";
                getline(cin,id);
            } else if (id.length() > 8) {
                cout << "ERROR: ID is too large, it must be 7 or 8 digits! Try again: ";
                getline(cin,id);
            } else {
                cout << "poop" << endl;
            }
        }
        bool bad = false;
        if (id.length() == 8) {
            for (int i = 0; i < 8; i++) {
                if (id[i] >= 48 && id[i]<= 57)
                    Id[i] = id[i];
                else {
                    cout << "ERROR: Could not parse the ID.  Please try again" << endl;
                    bad = true;
                }
            }
        } else if (id.length() == 7) {
            for (int i = 0; i < 7; i++) {
                if (id[i] >= 48 && id[i]<= 57)
                    Id7[i] = id[i];
                else {
                    cout << "ERROR: Could not parse the ID.  Please try again" << endl;
                    bad = true;
                }
            }
        }
        if (!bad) {
            if (id.length() == 8)
                pid = atoi(Id);
            else if (id.length() == 7)
                pid = atoi(Id7);
            if (blacklist.deleteByID(pid)) {
                count--;
                return;
            } else {
                cout << "Player ID " << pid << " was not found in the Blacklist!" << endl;
                return;
            }
        }

    } else {
        if ((input.length() == 15 || input.length() == 14) && input[6] == ' ') {
            if (input.length() == 15) {
                int x = 0;
                for (int i = 7; i < 15; i++) {
                    if (input[i] >= 48 && input[i] <= 57) {
                    Id[x] = input[i];
                    x++;
                    } else {
                        string n;
                        cout << "ERROR: ID is invalid, it must be numbers (0-9) only!" << endl;
                        cout << "Try again? (y/n): ";
                        getline(cin,n);
                        if (YesNo(n)) {
                            input = "delete";
                            Delete(blacklist,input,count);
                            return;
                        } else {
                            return;
                        }
                    }
                }
                pid = atoi(Id);
                if (blacklist.deleteByID(pid)) {
                    count--;
                } else {
                    cout << "Player ID " << pid << " was not found in the Blacklist!" << endl;
                }
            } else if (input.length() == 14) {
                int x = 0;
                for (int i = 7; i < 14; i++) {
                    if (input[i] >= 48 && input[i] <= 57) {
                        Id7[x] = input[i];
                        x++;
                    } else {
                        string n;
                        cout << "ERROR: ID is invalid, it must be numbers (0-9) only!" << endl;
                        cout << "Try again? (y/n): ";
                        getline(cin,n);
                        if (YesNo(n)) {
                            input = "delete";
                            Delete(blacklist,input,count);
                            return;
                        } else {
                            return;
                        }
                    }
                }
                pid = atoi(Id7);
                if (blacklist.deleteByID(pid)) {
                    count--;
                } else {
                    cout << "Player ID " << pid << " was not found in the Blacklist!" << endl;
                }
            }


        } else {
            string yn;
            cout << "ERROR: Syntax invalid. Proper syntax is 'delete 12345678'" << endl;
            cout << "Try again? (y/n): ";
            getline(cin,yn);
            if (YesNo(yn)) {
                input = "delete";
                Delete(blacklist,input,count);
                return;
            }
        }
    }
}

void Change(List& blacklist, string& input) {
	string inName;
	string sid;
	char cid7[7];
	char cid8[8];
	int id;
	int identifier;
	bool badFlag = false;
	if (input == "change") {
		string choice1;
		cout << "How would you like to find the player?" << endl;
		cout << "1) By Name" << endl;
		cout << "2) By ID" << endl << endl;
		cout << "admin@Blacklist: ";
		getline(cin,choice1);
		while(choice1 != "1" && choice1 != "2" && choice1 != "exit") {
			cout << "Incorrect input.  Expected 1 or 2." << endl;
			cout << "Try again? (y/n): ";
			getline(cin,choice1);
			if (YesNo(choice1)) {
				input = "change";
				Change(blacklist,input);
				return;
			} else {
				return;
			}
		}
		if (choice1 == "1") {
			cout << "Name: ";
			getline(cin,inName);
			identifier = blacklist.CSearchName(inName);
			if (identifier == 0) {
				cout << "Player not found in the Blacklist..." << endl;
				badFlag = true;
				return;
			}
		} else if (choice1 == "2") {
			cout << "ID: ";
			getline(cin,sid);
			int len = sid.length();
			//cout << len << endl;
			while (len < 7 || len > 8) {
				cout << "ERROR: ID must be 7 or 8 characters." << endl;
				cout << "ID: ";
				getline(cin,sid);
				len = sid.length();
			}
			len = sid.length();
			for (int i = 0; i < len; i++) {
				if (sid[i] < 48 || sid[i] > 57) {
					badFlag = true;
					break;
				}
			}
			if (!badFlag) {
				for (int i = 0; i < len; i++) {
					if (len == 7) {
						cid7[i] = sid[i];
					} else if (len == 8) {
						cid8[i] = sid[i];
					}
				}
				if (len == 7)
					id = atoi(cid7);
				else if (len == 8)
					id = atoi(cid8);
				identifier = blacklist.searchByID(id);
				if (identifier == 0) {
					cout << "ERROR: Player was not found in the Blacklist..." << endl;
					return;
				}
			}

		} else if (input == "exit") {
			input = "exit";
			return;
		}

	} else if (input.length() > 9 && input[6] == ' ' && input[7] == '-') {



		if (input[8] == 'n' && input[9] == ' ') {
			string temp = "";
			int len1 = input.length();
			for (int i = 10; i < len1; i++) {
				temp += input[i];
			}
			identifier = blacklist.CSearchName(temp);
			if (identifier <= 0) {
				cout << "ERROR: Player was not found in the Blacklist..." << endl;
				badFlag = true;
				return;
			}

		} else if (input[8] == 'i' && input[9] == ' ') {
			string temp = "";
			int len1 = input.length();
			int sevenOrEight = input.length() - 10;
			if (sevenOrEight == 7 || sevenOrEight == 8) {
				for (int i = 10; i < len1; i++) {
					//cout << input[i];
					if (input[i] >= 48 && input[i] <= 57) {
						temp += input[i];
					} else {
						badFlag = true;
						cout << "ERROR: ID must be digits (0-9)" << endl;
						return;
					}
				}
				for (int i = 0; i < sevenOrEight; i++) {
					if (sevenOrEight == 7)
						cid7[i] = temp[i];
					else if (sevenOrEight == 8)
						cid8[i] = temp[i];
				}
				if (sevenOrEight == 7)
					id = atoi(cid7);
				else if (sevenOrEight == 8)
					id = atoi(cid8);
				identifier = blacklist.searchByID(id);
				if (identifier == 0) {
					cout << "ERROR: Player was not found in the Blacklist..." << endl;
					badFlag = true;
					return;
				}
			} else {
				cout << "ERROR: ID must be 7 or 8 digits" << endl;
				cout << "Try again? (y/n): ";
				string yn;
				getline(cin,yn);
				if (YesNo(yn)) {
					cout << "ID: ";
					getline(cin,temp);
					while (temp.length() != 7 && temp.length() != 8 && temp != "exit") {
						cout << "ERROR: ID must be 7 or 8 digits!" << endl;
						cout << "ID: ";
						getline(cin,temp);
					}
					if (temp == "exit") {
						badFlag = true;
						input = "exit";
						return;
					}
					sevenOrEight = temp.length();
					for (int i = 0; i < sevenOrEight; i++) {
						if (!(temp[i] >= 48 && temp[i] <= 57)) {
							badFlag = true;
							cout << "ERROR: ID must be digits (0-9)" << endl;
							return;
						}
					}
					for (int i = 0; i < sevenOrEight; i++) {
						if (sevenOrEight == 8)
							cid8[i] = temp[i];
						else if (sevenOrEight == 7)
							cid7[i] = temp[i];
					}
					if (sevenOrEight == 8)
						id = atoi(cid8);
					else if (sevenOrEight == 7)
						id = atoi(cid7);
					identifier = blacklist.searchByID(id);
					if (identifier == 0) {
						cout << "Player was not found in the Blacklist..." << endl;
						badFlag = true;
						return;
					}
				} else {
					badFlag = true;
					return;
				}
			}
		} else {
			cout << "ERROR: Invalid syntax. Type 'help' for a list of commands" << endl;
			return;
		}


	} else {
		cout << "ERROR: Invalid syntax. Type 'help' for a list of commands" << endl;
		return;
	}
	if (!badFlag) {

		//cout << endl << endl << "DEBUGGING: at this point, we should have a real ID..." << endl;
		//cout << "ID = " << identifier << endl << endl;
		cout << "What is the player's new status?" << endl;
		cout << "1) Banned" << endl;
		cout << "2) Banned (Definite Hacker)" << endl;
		cout << "3) Not Banned" << endl;
		cout << "4) N/A" << endl;
		string choice2;
		cout << "Choice: ";
		getline(cin,choice2);
		//cout << choice2 << endl;
		while (choice2 != "1" && choice2 != "2" && choice2 != "3" && choice2 != "4" && choice2 != "exit") {
			cout << "ERROR: Invalid input. Expected 1 or 2..." << endl;
			cout << "Try again? (y/n): ";
			getline(cin,choice2);
			if (YesNo(choice2)) {
				cout << "Choice: ";
				getline(cin,choice2);
			} else {
				return;
			}
		}
			//cout << "got here0" << endl;
			string stats[4] = {"Banned","Banned (Definite Hacker)","Not Banned","N/A"};
			//cout << "got here1" << endl;
			int choice3;
			if (choice2 == "exit") {
				input = "exit";
				return;
			} else if (choice2 == "1") {
				choice3 = 0;
			} else if (choice2 == "2") {
				choice3 = 1;
			} else if (choice2 == "3") {
				choice3 = 2;
			} else if (choice2 == "4") {
				choice3 = 3;
			} else {
				cout << "Debug me, change function" << endl;
			}
			//cout << "got here" << endl;
			blacklist.SetStat(identifier,stats[choice3]);
			cout << endl << "Status changed successfully" << endl << endl;
	}
}

void Backup(List& blacklist) {
	blacklist.Back();
}

void ShowHelp() {
            cout << endl << "BLACKLIST VIEWER COMMANDS" << endl;
            cout << "-------------------------" << endl;
            cout << "help\tDisplays the list of commands with syntax" << endl;
            cout << "add\tAllows you to add a player to the Blacklist" << endl;
            cout << "\t\targuments: -n [name] AND -i [id]" << endl;
            cout << "\t\texample: add -n Some Other Random Dude -i 12345678" << endl;
            cout << "delete\tAllows you to delete a player from the Blacklist" << endl;
            cout << "\t\texample: delete 12345678" << endl;
            cout << "search\tAllows you to search for a specific player" << endl;
            cout << "\t\targuments: -n [name] OR -i [id]" << endl;
            cout << "\t\texample: search -n Bango[ELD] OR search -i 12345678" << endl;
            cout << "sort\tAllows you to sort the data based on 1 of the 3 categories" << endl;
            cout << "\t\targuments: -n OR -i OR -s" << endl;
            cout << "\t\texample: sort -n (to sort the Blacklist by Name)" << endl;
            cout << "\t\texample: sort -i (to sort the Blacklist by ID)" << endl;
            cout << "\t\texample: sort -s (to sort the Blacklist by Status)" << endl;
			cout << "change\tAllows you to change a user's status" << endl;
			cout << "\t\targuments: -i OR -n" << endl;
			cout << "\t\texample: change -i 1234567 OR change -n Admin" << endl;
            cout << "print\tPrints the Blacklist to the screen" << endl;
            cout << "count\tDisplays the number of players in the Blacklist" << endl;
            cout << "\t\targuments: -a OR -b OR -h OR -n" << endl;
            cout << "\t\texample: count -a (to list all players in the Blacklist)" << endl;
            cout << "\t\texample: count -b (to list all Banned players in the Blacklist)" << endl;
            cout << "\t\texample: count -h (to list all Definite Hackers in the Blacklist)" << endl;
            cout << "\t\texample: count -n (to list all players who are Not Banned in the Blacklist)" << endl;
			cout << "clear\tClears the screen" << endl;
			cout << "update\tAllows you to update ban.txt and Blacklist.txt from within the command prompt" << endl;
			cout << "save\tDoes the exact same thing as update, but easier to remember save/saveas" << endl;
			cout << "\t\targuments: -b OR -e OR -be" << endl;
			cout << "\t\texample: update -b (update and backup)" << endl;
			cout << "\t\texample: update -e (update and exit)" << endl;
			cout << "\t\texample: update -be (update, backup, and exit)" << endl;
			cout << "backup\tAllows you to update your backup files -- in case a bug causes data loss in main files" << endl;
			cout << "saveas\tAllows you to create a unique backup of the current Blacklist by specifying a file name" << endl;
			cout << "\t\targuments: -n [filename]" << endl;
			cout << "\t\texample: saveas -n OctoberBackup" << endl;
			cout << "changelog\tDisplays the Blacklist changelog" << endl;
			cout << "about\tDisplays information about the Blacklist Viewer" << endl;
			cout << "ue\tUpdate and exit" << endl;
            cout << "exit\tExits the program" << endl << endl;
}

void Update(List& blacklist, string& input) {


    blacklist.UpdateBlack();
	input = "sort -i";
	QSort(blacklist, input);
	blacklist.UpdateBan();
}

void Search(List &blacklist, string &input) {
    if (input == "search") {
        string x;
        cout << "What do you want to search by?" << endl;
        cout << "1) Name" << endl;
        cout << "2) ID" << endl;
        getline(cin,x);
        while (x != "1" && x != "2" && x != "exit") {
            cout << "ERROR: Invalid command.  Please choose 1 or 2: ";
            getline(cin,x);
        }
        if (x == "exit") {
            input == "exit";
            return;
        } else if (x == "1") {
            cout << "Name: ";
            string y;
            getline(cin,y);
			cout << endl;
            int p = blacklist.searchByName(y);
            //cout << "p = " << p << endl;
            if (p != 0) {
                string nameout,statusout;
                nameout = blacklist.GetName(p);
                statusout = blacklist.GetStatus(p);
                cout << endl << "Player found in Blacklist:" << endl;
                cout << "Name: " << nameout << endl;
                cout << "ID: " << p << endl;
                cout << "Status: " << statusout << endl << endl;
            } else {
                cout << endl << "Player " << y << " was not found in the Blacklist." << endl;
                return;
            }
        } else if (x == "2") {
            cout << "ID: ";
            getline(cin,x);
            while (x.length() != 8 && x.length() != 7) {
                cout << "ERROR: ID must be 7 or 8 digits!" << endl;
                cout << "Try again? (y/n)";
                getline(cin,x);
                if (YesNo(x)) {
                    input = "search";
                    Search(blacklist,input);
                    return;
                } else {
                    return;
                }
            }
            if (x.length() == 8) {
                char cid[8];
                for (int i = 0; i < 8; i++) {
                    if (x[i] >= 48 && x[i] <= 57) {
                        cid[i] = x[i];
                    } else {
                        cout << "ERROR: ID must be digits only (0-9)" << endl;
                        cout << "Try again? (y/n): ";
                        getline(cin,x);
                        if (YesNo(x)) {
                            input = "search";
                            Search(blacklist,input);
                            return;
                        } else {
                            return;
                        }
                    }
                }
                int id;
                id = atoi(cid);
				cout << endl;
                if (blacklist.searchByID(id) != 0) {
                    string nameout,statusout;
                    nameout = blacklist.GetName(id);
                    statusout = blacklist.GetStatus(id);
                    cout << endl << "Player found in Blacklist:" << endl;
                    cout << "Name: " << nameout << endl;
                    cout << "ID: " << id << endl;
                    cout << "Status: " << statusout << endl << endl;
                    return;
                } else {
                    cout << endl << "Player ID " << id << " was not found in the Blacklist." << endl;
                    return;
                }
            } else if (x.length() == 7) {
                char cid[7];
                for (int i = 0; i < 7; i++) {
                    if (x[i] >= 48 && x[i] <= 57) {
                        cid[i] = x[i];
                    } else {
                        cout << "ERROR: ID must be digits only (0-9)" << endl;
                        cout << "Try again? (y/n): ";
                        getline(cin,x);
                        if (YesNo(x)) {
                            input = "search";
                            Search(blacklist,input);
                            return;
                        } else {
                            return;
                        }
                    }
                }
                int id;
                id = atoi(cid);
                if (blacklist.searchByID(id) != 0) {
                    string nameout,statusout;
                    nameout = blacklist.GetName(id);
                    statusout = blacklist.GetStatus(id);
                    cout << endl << "Player found in Blacklist:" << endl;
                    cout << "Name: " << nameout << endl;
                    cout << "ID: " << id << endl;
                    cout << "Status: " << statusout << endl << endl;
                    return;
                } else {
                    cout << "Player ID " << id << " was not found in the Blacklist." << endl;
                    return;
                }
            } else {
                cout << "ERROR: ID must be 7 or 8 digits." << endl;
                cout << "Try again? (y/n): ";
                string yn;
                getline(cin,yn);
                if (YesNo(yn)) {
                    input = "search";
                    Search(blacklist,input);
                    return;
                } else {
                    return;
                }
            }
        }
    } else if (input[6] == ' ' && input[7] == '-') {
        int counter = 0;
        if (input[8] == 'n' && input[9] == ' ') {
            string name = "";
            for (int i = 10; i < input.length(); i++) {
                name += input[i];
                counter++;
            }
            cout << endl;
			int id = blacklist.searchByName(name);
            if (id != 0) {
                string status = blacklist.GetStatus(id);
                cout << endl << "Player found in Blacklist:" << endl;
                cout << "Name: " << name << endl;
                cout << "ID: " << id << endl;
                cout << "Status:" << status << endl << endl;
                return;
            } else {
                cout << endl << "Player " << name << " was not found in the Blacklist." << endl;
                return;
            }
        } else if (input[8] == 'i' && input[9] == ' ') {
            string sid = "";
            for (int i = 10; (i < input.length()); i++) {
                if (input[i] >= 48 && input[i] <= 57) {
                        sid += input[i];
                } else {
                    cout << "ERROR: ID must be digits (0-9)." << endl;
                    cout << "Try again? (y/n): ";
                    string yn;
                    getline(cin,yn);
                    if (YesNo(yn)) {
                        input = "search";
                        Search(blacklist,input);
                        return;
                    } else {
                        return;
                    }
                }
            }
            const int len = sid.length();
            char* cid;
            for (int i = 0; i < len; i++) {
                cid[i] = sid[i];
            }
            int id = atoi(cid);
			cout << endl;
            if (blacklist.searchByID(id) != 0) {
                string name, status = "";
                name = blacklist.GetName(id);
                status = blacklist.GetStatus(id);
                cout << endl << "Player found in Blacklist:" << endl;
                cout << "Name: " << name << endl;
                cout << "ID: " << id << endl;
                cout << "Status: " << status << endl << endl;
                return;
            } else {
                cout << endl << "Player ID " << id << " was not found in the Blacklist." << endl;
                return;
            }
        } else {
            cout << "ERROR: Invalid syntax. Proper syntax is 'search -n nazguleye' OR 'search -i 12345678'" << endl;
                cout << "Try again? (y/n): ";
                getline(cin,input);
                if (YesNo(input)) {
                        input = "search";
                        Search(blacklist,input);
                        return;
                } else {
                        return;
        }
        }
    } else {
        cout << "ERROR: Invalid syntax. Proper syntax is 'search -n nazguleye' OR 'search -i 12345678'" << endl;
        cout << "Try again? (y/n): ";
        getline(cin,input);
        if (YesNo(input)) {
            input = "search";
            Search(blacklist,input);
            return;
        } else {
            return;
        }
    }
}

void About() {
    cout << endl << "BLACKLIST VIEWER v1.0.0b" << endl;
    cout << "Created by Logan Swango (Bango)" << endl;
    cout << "All rights reserved." << endl << endl;
    cout << "This program is intended to run alongside arma2server.exe, in order to make the process of banning players easier on admins." << endl;
    cout << "Blacklist Viewer is still in beta testing as of 6.10.13" << endl;
    cout << "Report bugs to Bango." << endl << endl;
}

void RemoveBL(string& filename) {
	int len = filename.length();
	int check = len - 3;
	string newname = "";
	if (filename[check] == '.' && filename[check+1] == 'b' && filename[check+2] == 'l') {
		for (int i = 0; i < check; i++) {
			newname += filename[i];
		}
		//cout << "newname = " << newname << endl;
		filename = newname;
	}
}

void SaveAs(List& blacklist, string& input) {
	string filename = "";
	string yn;
	int len = 0;
	bool valid = true;
	cout << "Do you want to update the Blacklist before creating this backup? (y/n)" << endl;
	cout << "admin@Blacklist: ";
	getline(cin,yn);
	if (YesNo(yn)) {
		Update(blacklist,input);
	}
	string dir = "../../../Blacklist_Backups/";
	if (input == "saveas") {
		cout << "File name: ";
		getline(cin,filename);
		len = filename.length();
		for (int i = 0; i < len; i++) {
			if (filename[i] == 92 || filename[i] == 47 || filename[i] == 58 || filename[i] == 42 || filename[i] == 60 || filename[i] == 62 || filename[i] == 124 || filename[i] == 63 || filename[i] == 34) {
				valid = false;
				break;
			}
		}
		if (!valid) {
			cout << "ERROR: File name cannot have characters \ / : * ? < > |" << endl;
			return;
		} else {
			RemoveBL(filename);
			filename = dir + filename + ".bl";
			//cout << "Dir = " << filename << endl;
			blacklist.SaveAs(filename);
		}
	} else {
		if (input[6] == ' ' && input[7] == '-' && input[8] == 'n' && input[9] == ' ') {
			len = input.length();
			for (int i = 10; i < len; i++) {
				if (input[i] == 92 || input[i] == 47 || input[i] == 58 || input[i] == 42 || input[i] == 60 || input[i] == 62 || input[i] == 124 || input[i] == 63 || input[i] == 34) {
					valid = false;
					break;
				} else {
					filename += input[i];
				}
			}
			if (!valid) {
				cout << "ERROR: File name cannot have characters \ / : * ? < > |" << endl;
				return;
			} else {
				RemoveBL(filename);
				filename = dir + filename + ".bl";
				blacklist.SaveAs(filename);
			}
		} else {
			cout << "ERROR: Invalid syntax. Type 'help' for a list of commands" << endl;
			return;
		}
	}
}

void Count(List& blacklist, string& input,int count) {
    if (input == "count") {
        cout << endl << count << " players were found in the blacklist" << endl << endl;
    } else if (input[5] == ' ' && input[6] == '-') {
        if (input[7] == 'a') {
			cout << endl;
            blacklist.PrintNames();
			//cout << endl;
        } else if (input[7] == 'b') {
            cout << endl << "Banned Players:" << endl;
            blacklist.PrintBanned();
			//cout << endl;
        } else if (input[7] == 'h') {
            cout << endl << "Definite Hackers:" << endl;
            blacklist.PrintHackers();
			//cout << endl;
        } else if (input[7] == 'n') {
            cout << endl << "Players who are Not Banned:" << endl;
            blacklist.PrintNotBanned();
			//cout << endl;
        } else {
            cout << "ERROR: invalid argument '" << input[7] << "'. Type 'help' for a list of commands." << endl;
        }
    } else {
        cout << "ERROR: Incorrect syntax. Type 'help' for a list of commands." << endl;
    }
}

void Load(List& blacklist, string& input) {
	cout << "Called load function" << endl;

	//args: -n [filename]
	//load function idea
	//load will be able to load in a blacklist besides blacklist.bl
	//if the user tries to save or update, they will be asked if they want to update the file they loaded, or the main blacklist
	//if they choose the main blacklist, warn them that they are overwriting the main blacklist with a previously saved blacklist
	//if input is "loadbackup", let them load the local backup, no args
}

void ChangeLog() {
	ifstream cl;
	cl.open("../../../Blacklist/blacklist_changelog.log");
	if (cl.is_open()) {
		string line;
			cout << endl;
		while (!cl.eof()) {
			getline(cl,line);
			cout << line << endl;
		}
		cout << endl;
	} else {
		cout << "ERROR: Could not access the file 'blacklist_changelog.log'" << endl;
	}
}



//---------------
// Function:     main
// Purpose:      act as the main loop
//---------------
int main() {
	string input = " ";
    int count = 0;
    List blacklist;

    cout << " ______________________" << endl;
    cout << "|  *BLACKLIST VIEWER*  |" << endl << endl;
    //Test();
    ReadFile(blacklist,count);

    while (input != "exit" && input != "quit") {

        //cout << "Main Menu/" << endl;

        input = GetInput("admin@Blacklist: ");


        //HELP
		if (input == "help") {
            ShowHelp();
        //ADD
		} else if (input.length() >= 3 && input[0] == 'a' && input[1] == 'd' && input[2] == 'd') {
            AddPlayer(blacklist,input,count);
        //DELETE
        } else if (input.length() >= 6 && input[0] == 'd' && input[1] == 'e' && input[2] == 'l' && input[3] == 'e' && input[4] == 't' && input[5] == 'e') {
            Delete(blacklist,input,count);
        //SEARCH
        } else if (input.length() >= 6 && input[0] == 's' && input[1] == 'e' && input[2] == 'a' && input[3] == 'r' && input[4] == 'c' && input[5] == 'h') {
            Search(blacklist,input);
        //SORT
        } else if (input.length() >= 4 && input[0] == 's' && input[1] == 'o' && input[2] == 'r' && input[3] == 't') {
            Sort(blacklist,input);
        //UPDATE
        } else if (input == "update" || input == "save") {
			QSort(blacklist,input);
            Update(blacklist,input);
        //PRINT
        } else if (input == "print") {
            blacklist.printAll();
        //EXIT
        } else if (input.length() >= 5 && input[0] == 'c' && input[1] == 'o' && input[2] == 'u' && input[3] == 'n' && input[4] == 't') {
            Count(blacklist,input,count);
		//ABOUT
        } else if (input == "about") {
			About();
		//BACKUP
        } else if (input == "backup") {
			Backup(blacklist);
		//CLEAR
		} else if (input == "clear") {
			system("CLS");
		//UPDATE & EXIT
		} else if (input == "ue" || input == "update -e" || input == "save -e") {
			Update(blacklist,input);
			return 0;
		//UPDATE & BACKUP
		} else if (input == "update -b" || input == "save -b") {
			Update(blacklist,input);
			Backup(blacklist);
		//LOAD
		} else if (input[0] == 'l' && input[1] == 'o' && input[2] == 'a' && input[3] == 'd') {
			Load(blacklist,input);
		//UPDATE & BACKUP & EXIT
		} else if (input == "update -be" || input == "save -be") {
			Update(blacklist,input);
			Backup(blacklist);
			return 0;
		//SAVEAS
		} else if (input.length() >= 6 && input[0] == 's' && input[1] == 'a' && input[2] == 'v' && input[3] == 'e' && input[4] == 'a' && input[5] == 's') {
			SaveAs(blacklist,input);
		//EXIT
		} else if (input == "exit") {
            return 0;
		//CHANGELOG
		} else if (input == "changelog") {
			ChangeLog();
		//CHANGE
        } else if (input.length() >= 6 && input[0] == 'c' && input[1] == 'h' && input[2] == 'a' && input[3] == 'n' && input[4] == 'g' && input[5] == 'e') {
			Change(blacklist, input);
		//INVALID INPUT CATCH
		} else {
            int length = input.length();
            string error = "";
			if (length > 0) {
				for (int i = 0; i < length; i++) {
					if (input[i] != ' ') {
						error += input[i];
					} else {
						break;
					}
				}
				cout << "ERROR: " << error << " is not a valid command. Type 'help' for a list of valid commands." << endl;
			}
			//} else {
				//GetInput("admin@Blacklist: ");
				//break;
			//}

        }

    }//end main loop



    return 0;
}
