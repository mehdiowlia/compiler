//In The Name Of God
//first try to develope a simple compiler with c++


//library calls: 

#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;


///////////////////////////////////Node Class/////////////////////////////
class Node
{


public:

	string name;
	Node* info;
	Node* next;

	//4 constructors:
	//1
	Node()
	{
		this->name = "";
		this->info = NULL;
		this->next = NULL;

	}
	//2    
	Node(string name)
	{
		this->name = name;
		this->info = NULL;
		this->next = NULL;
	}
	//3
	Node(string name, Node* info)
	{
		this->name = name;
		this->info = info;
		this->next = NULL;

	}
	//4
	Node(string name, Node* info, Node* next)
	{
		this->name = name;
		this->info = info;
		this->next = next;
	}

};

/////////////////////////////////////LinkedList Class/////////////////////////////////////////////

class LinkedList
{
public:

	Node* head;
	//constructor :
	LinkedList()
	{
		head = NULL;
	}
	//function for search a node :
	bool searchNode(string name)
	{
		Node* temp = head;

		while (temp != NULL)
		{
			if (temp->name == name)
			{
				return true;
			}
			temp = temp->next;
		}

		return false;

	}
	//function for insert new node to linked list :
	void insertNode(string name, Node* info = NULL)
	{
		if (searchNode(name))
		{
			return;
		}

		Node* newNode = new Node(name);

		if (head == NULL)
		{
			head = newNode;
			return;
		}

		Node* temp = head;

		while (temp->next != NULL)
		{

			temp = temp->next;
		}


		temp->next = newNode;


	}
	//function for print all the nodes :
	void printList()
	{
		if (head == NULL)
		{
			cout << "linked list is empty !" << endl;
			return;
		}

		Node* temp = head;

		while (temp != NULL)
		{
			cout << temp->name << "---->";
			temp = temp->next;
		}
		cout <<"NULL"<< endl;


	}

};
////////////////////////////Hash Table////////////////////////////////
class HastTable
{
private:

	LinkedList table[8];

public:

	//function for calculate hash of identifire's name and append it to table : 
	int hashing(string identifire)
	{
		int len = identifire.length();//length of input
		char chArr[256];//char array for casting
		strcpy_s(chArr, identifire.c_str());//copy string to char array
		int sum = 0;

		for (int i = 0; i < len; i++)
		{
			sum += int(chArr[i]);//add ascii code of char's to each other
		}

		int index = sum % 8;
		table[index].insertNode(identifire);
		return index;

	}
	//function to print Hash Table :
	void printTable()
	{
		cout << "symbole table : \n";
		for (int i = 0; i < 8; i++)
		{
			cout << "symbole raw " << i + 1 << " : ";
			table[i].printList();
		}
	}

};

int main()
{
	
	HastTable t1;

	t1.hashing("position");
	t1.hashing("rate");
	t1.hashing("initial");
	t1.hashing("positino");//"positno" hash id equal to position
	t1.hashing("position");//if compiler arrive to repetitive identifire



	t1.printTable();

	return 0;
}
