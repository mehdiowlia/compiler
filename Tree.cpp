/*
In The Name Of God
simple tree structure in c++
*/

#include<iostream>

using namespace std;

/////////////////////////////Tree Class//////////////////////////////////
class Tree
{
public:

    Tree* left;
    Tree* right;
    string info;

    Tree()
    {
        this->left=NULL;
        this->right=NULL;
        this->info="";
    }
    Tree(string info)
    {
        this->left=NULL;
        this->right=NULL;
        this->info=info;
    }    
    Tree(string info,Tree* left,Tree* right)
    {
        this->left=left;
        this->right=right;
        this->info=info;
    }
};
/////////////////////////LinkedTree/////////////////////////////////
class LinkedList
{
    public:
    
        Tree* root;
        //constructor
        LinkedList()
        {
            root=NULL;
        }
        //Insert new node to the tree
        void mainInsert(Tree* &subTree, string info)
        {
            if (subTree == NULL)
            {
                subTree = new Tree(info);
                return;
            }
            if (info.compare(subTree->info) == -1)
            {
                mainInsert(subTree->left, info);
            }
            else
            {
                mainInsert(subTree->right, info);
            }
        }
        //print all the nodes in the tree
        //it can be better if ouput become like this:
        /*
                       x
                      /  \
                     y    z
                    / \  / \
                    .
                    .
                    .
        */
        void mainPrintTree(Tree* newroot)
        {
            if(newroot==NULL)
            {
                return;
            }
            cout<<newroot->info<<endl;
            mainPrintTree(newroot->left);
            mainPrintTree(newroot->right);
        }
         //fuction to call "mainInsert" function from "main" or othere places
        void insert(string info)
        {
            mainInsert(this->root , info);
        }
         //fuction to call "mainPrint" function from "main" or othere places
        void printTree()
        {
            mainPrintTree(this->root);
        }

};

/////////////////////////////Main/////////////////////////////////////

int main()
{
    //build object from "LinkedList" class
    LinkedList myTree;
    //insert some nodes to tree
    myTree.insert("2");
    myTree.insert("1");
    myTree.insert("3");
    myTree.insert("7");
    myTree.insert("0");
    //print nodes
    myTree.printTree();
  
    return 0;
}


