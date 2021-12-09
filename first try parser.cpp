/*                    In The Name Of God
                  
parser by :          MOHAMMAD MEHDI OWLIA



finished:
        ✅stack class
        ✅parser class
        ✅test the parser with diffrent input
ToDo:
        🔼some reppititive parts can become a function in future
        ❌write answers to file!

used symbols:
✅finished works
🔼it's beter to do it
❌bug or not complite part

grammer:  
            S->Bde|Fpb
            B->aX|Cd
            C->awz|Fb
            X->wz|wp
            F->aw

tested strings :

            {"awpb","awbdde","awzdde","awzde","awpde","www","123"}            

*/




//library calls:
#include <iostream>
#include <string>
#include <string.h>


using namespace std;
////////////////////////////////Stack Class//////////////////////
class Stack
{
    private:

    //in this grammer stack size=3 is enough
    int array[3];
    int stackSize=3;
    int pointer=-1;

    public:

    void push(int input)
    {
        if(!isFull())
        {
        array[++pointer]=input;
        return;
        }
        cout<<"can't push,stack is full !"<<endl;
    }
    //*******************************
    int pop()
    {
        if(!isEmpty())
        {
            return array[pointer--];
        }
        cout<<"can't pop,stack is empty!"<<endl;
        return -1;
    }
    //*******************************
    bool isEmpty()
    {
        if(pointer==-1)
        {
            return true;
        }
        return false;
    }
    //*******************************
    bool isFull()
    {       
         if(pointer==stackSize-1)
        {
            return true;
        }
        return false;
    }

};

///////////////////////////////Parser Class//////////////////////
class Parser
{
private:
    //grammer:
    string grammer[5][2] =
    { 
        {"S", "Bde|Fpb"},
        {"B", "aX|Cd"},
        {"C", "awz|Fb"},
        {"X", "wz|wp"},
        {"F", "aw"} 
    };

    int size;
    string str;

public:
    //constructor:
    Parser(string str)
    {
        this->str=str;
        size=str.length();
    }
    //main part of the parser:
    bool main1()
    {
        //define object from stack
        Stack stack;
        //str_flag->become true if string become finished
        bool str_flag = false;
        //PR_flag->become true if production rule become finished
        bool PR_flag = false;
        //sP->string pointer
        //PR->wich production rule
        //sPR->place of terminal or Non terminal
        //var->string pointer before enter to new production rule
        int sP = 0, PR = 0, sPR = 0,var=0;
        //pushing->number for push to stack
        //next->for detect next part of the production rule 
        int pushing,next;


        while (true)
        {
            //if we have nonterminal
            if (grammer[PR][1][sPR] >= 'A' && grammer[PR][1][sPR] <= 'Z')
            {
                //push
                pushing=PR * 100 + sPR * 10 + var;
                stack.push(pushing);
                PR = findPlace(grammer[PR][1][sPR]);
                sPR=0;
                var=sP;
            }
            //if we have terminal
            else if (grammer[PR][1][sPR] >= 'a' && grammer[PR][1][sPR] <= 'z')
            {
                //compare and advance
                if (str[sP] == grammer[PR][1][sPR])
                {
                    sP++;
                    sPR++;
                    //if input string is finished
                    if (sP == size)
                    {
                        str_flag = true;
                    }
                }
                else
                {   
                    //back track and start new way from first
                    next=otherWay(grammer[PR][1],sPR);
                    if(next && stack.isEmpty())
                    {
                        sPR=next+1;
                        sP=0;
                    }
                    //back track and continue from last true part
                    else if(next && !(stack.isEmpty()))
                    {
                        sPR=next+1;
                        sP=var;
                    }
                    //if not equal and not other way and stack is empty(faild)
                    else if (stack.isEmpty())
                    {
                        return false;
                    }
                    // backtrack with pop
                    else
                    {
                        int temp = stack.pop();
                        sP = temp % 10;
                        var=sP;
                        sPR = (temp / 10) % 10 + 1;
                        PR = temp / 100;
                        next=otherWay(grammer[PR][1],sPR-1);
                        if(next)
                        {
                            sPR=next+1;
                            sP=0;
                        }
                    }
                }
            }
            //if corrent char = '|'
            else if (grammer[PR][1][sPR] == '|')
            {
                //accepted
                if (str_flag && stack.isEmpty())
                {
                    PR_flag = true;
                    break;
                }
                //faild
                else if (stack.isEmpty())
                {
                    return false;
                }
                //pop 
                else
                {
                    int temp = stack.pop();
                    sPR = (temp / 10) % 10 + 1;
                    PR = temp / 100;
                }
            }
            //end of production rule
            else if (sPR == grammer[PR][1].length())
            {
                if (stack.isEmpty())
                {
                    //accepted
                    if(str_flag)
                    {
                        return true;
                    }
                    //faild
                    else
                    {
                        return false;
                    }
                        
                }
                //pop
                int temp = stack.pop();
                sPR = (temp / 10) % 10 + 1;
                PR = temp / 100;
            }
        }

        //if it return true string was accepted!else string was faild
        return (stack.isEmpty() && str_flag && PR_flag);
    }

    //find line of pushed NonTerminal in grammer
    int findPlace(char ch)
    {
        for (int i = 0; i < 5; i++)
        {
            if (grammer[i][0][0] == ch)
            {
                return i;
            }
        }
        return -1;
    }

    //find other way of production rule-> ...|...|...|...   
    int otherWay(string s,int indx)
    {

        for(int i=indx;i<s.length();i++)
        {
            if(s[i]=='|')
            {
                return i;
            }
        }
        return 0;
    }

};

///////////////////////////////main////////////////////////////////

int main()
{
    string answer;
    string str[7] ={"awpb","awbdde","awzdde","awzde","awpde","www","123"};
    for(int i=0;i<7;i++)
    {
        Parser p(str[i]);
        answer= (p.main1())?"accepted":"faild"; 
        cout << str[i]<<" : "<<answer <<" . "<< endl;   
    }
}
