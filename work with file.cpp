//In The Name Of God
//work with file for read code to compile

#include <iostream>
//including "fstream" for working with files
#include <fstream>
//including "string" for using string functions linke getline and etc
#include <string>


using namespace std;

int main()
{	
	//file addr
	//if test.txt doesn't exist in D: the program is make it
	//if you dont have drive D: or working with liux and macOs change the below path
	string file_name = "D:/test.txt";

	//ofstream for write on files 
	//"ouput" is a general name and it can be any other name you like
	ofstream output(file_name);

	//write 2 line of strings in test.txt
	output << "c++ is powerful" << endl;
	output << "linux mac and windows" << endl;
	output << "android vs ios" << endl;
	output << "computer engineering" << endl;

	//ifstream for read from files
	//"input" is a general name and it can be any other name you like
	ifstream input(file_name);

	string str1;

	//copy line 1 to str1
	getline(input, str1);
	cout << "first line of test.txt : "<<str1<< endl;

	//copy line 2 to str1
	getline(input, str1);
	cout << "second line of test.txt : " << str1 << endl;

	//get all chars before first space and copy them to str1
	input >> str1;
	cout << "first piece of third line test.txt : " << str1 << endl;

	//copy line 3 to str1 without first piece
	getline(input, str1);
	cout << "third line of test.txt without \"android\": " << str1 << endl;


	getline(input, str1);
	cout <<"before seeking to begin ,str1="<<str1 << endl;

	//change the file postition to begin of file
	input.seekg(0);

	getline(input, str1);
	cout << "after seeking to begin ,str1=" << str1 << endl;


	//change the file postition to begin of file
	input.seekg(0);

	//read char by char
	char c;
	while (input.get(c))
	{
		if (c == '\n'||c==' ')
			cout <<"\n";
		else
			cout << c << "\t";
	}
	cout << endl;
	



	system("pause");
	return 0;  
}

