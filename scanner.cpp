//In The Name of God
//Scanner for compiler

/*
Todo:
	✅word detector
		🚫some array exist in scanner should be a linked list
		🚫program in my some tests are work good but may have some bug(need more test)
	❎reserved word detector
	❎enum for reserved word
	❎link Scanner to other part of compiler
*/



#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

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
			head->info=info;
			return;
		}

		Node* temp = head;

		while (temp->next != NULL)
		{

			temp = temp->next;
		}


		temp->next = newNode;
		temp->next->info=info;

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
			strcpy(chArr, identifire.c_str());//copy string to char array
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
			cout << "symbole table : \n\n";
			for (int i = 0; i < 8; i++)
			{
				cout << "symbole raw " << i + 1 << " : ";
				table[i].printList();
				cout<<endl;
			}
		}

};

///////////////////////Scanner Class//////////////////////////
class ScannerClass
{

	private:

		//fstream for work with files
		fstream my_file;
		int file_pointer;
		//enum reserved_word {_program_,_begin_,_end_,_var_,_integer_,_function_};
	public:

		//class constructor
		ScannerClass()
		{	
			//when any object constructed pointer of file set to begin of file
			this->file_pointer=0;
		}

		string word_detector(string file_name)
		{
			//ios::in for open file just for read 
			my_file.open(file_name,ios::in);

			string word;
			int ch_counter=0;
			char ch;

			//seekg==>move the file pointer to corrent state
			my_file.seekg(this->file_pointer);

	        //🚫char temp should be linked list to become onlimited🚫//
			char temp[1000];

			while (true) 
			{	
				
				if (end_of_file())
				{
					return "";
				}
				//"my_file>>ch" ignore white spaces so i use "my_file >>noskipws>> ch"
				my_file >>noskipws>> ch;
				temp[ch_counter++]=ch;
				this->file_pointer++;
				//isspace is true when it detect spaces
				if(isspace(ch)||symbol_detector(ch))
				{	
					bool flag=false;

					for(int i=0;i<ch_counter-1;i++)
					{
						flag=true;
						word+=temp[i];
					}
					//if flag => some word is there
					if(flag)
					{	
						my_file.close();
						return word;
					}
					//if !flag => it's not a word it just white space and we should jump
					else
					{	
						//check for file is end ? or not
						if (end_of_file())
						{
							return "";
						}
						//for jumping
						my_file.seekg(this->file_pointer);
						//for start detecting next word 
						ch_counter=0;
					}
		
				}


			}
			
		}

		/*
		int hash_string(string str1)
		{
			string str=word_detector(str1);

			if(str=="program")
				return _program_;
			if(str=="begin")
				return _begin_;
			if(str=="end")
				return _end_;
			if(str=="var")
				return _var_;
			else
				return -1;
		}
		*/
		int symbol_detector(char ch)
		{
			char symbol[10]={';',':',',','<','>','+','=','-','*','/'};
			for(int i=0;i<10;i++)
			{
				if(ch==symbol[i])
				{
					return (i+1);//1-2-3.... = true
				}
			}
			return 0;//0 = false
		}

		bool end_of_file()
		{
			//eof() ==> true if arrive end of the file
			if (my_file.eof())
			{
				return true;
			}
			return false;
		}
		

};


int main()
{	
	
	string file_name = "test.txt";

	ScannerClass hi;
	LinkedList all_str;

	//string all_str[100];
	for(int i=0;!hi.end_of_file();i++)
	{
		string str=hi.word_detector(file_name);
		all_str.insertNode(str);
		//cout<<str<<endl;
	}

	HastTable t1;
	Node* ntemp;
	ntemp=all_str.head;
	for(int i=0;(i<=99) && (ntemp->next!=NULL);i++)
	{
		//cout<<"str "<<i+1<<" : "<<all_str[i]<<endl;
		t1.hashing(ntemp->name);
		ntemp=ntemp->next;

	}

	/*
	t1.hashing("position");
	t1.hashing("rate");
	t1.hashing("initial");
	t1.hashing("positino");//"positno" hash id equal to position
	t1.hashing("position");//if compiler arrive to repetitive identifire
	*/

	t1.printTable();

	return 0;  

}

