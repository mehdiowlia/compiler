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

///////////////////////Scanner Class//////////////////////////
class ScannerClass
{

	private:

		//fstream for work with files
		fstream my_file;
		int file_pointer;

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
				
				if (end_fo_file())
				{
					return "";
				}
				//"my_file>>ch" ignore white spaces so i use "my_file >>noskipws>> ch"
				my_file >>noskipws>> ch;
				temp[ch_counter++]=ch;
				this->file_pointer++;
				//isspace is true when it detect spaces
				if(isspace(ch))
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
						if (end_fo_file())
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

		bool reserved_words_detector()
		{
			return false;
		}

		
		bool end_fo_file()
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
	
	string file_name = "/home/cloud/programming/test/test1.txt";
	ScannerClass hi;
	//🚫all_str should be linked list to become onlimited🚫//
	string all_str[100];
	for(int i=0;!hi.end_fo_file();i++)
	{
		string str=hi.word_detector(file_name);
		all_str[i]=str;
		cout<<str<<endl;
	}

	
	for(int i=0;i<=99;i++)
	{
		cout<<"str "<<i+1<<" : "<<all_str[i]<<endl;
	}


	return 0;  

}

