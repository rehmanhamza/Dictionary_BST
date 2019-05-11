#include<stdio.h>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<string>
#include<malloc.h>
#include<stdlib.h>
#include <sstream>

using namespace std;

struct LNode{
	string name,meaning;
    int data;
    struct LNode* next;
};

/* A Binary Tree node */
struct TNode
{
    string name, meaning;
    int data;
    struct TNode* left;
    struct TNode* right;
};

struct TNode* newNode(int data, string name, string meaning);
int countLNodes(struct LNode *head);
struct TNode* sortedListToBSTRecur(struct LNode **head_ref, int n);

/* This function counts the number of nodes in Linked List and then calls
   sortedListToBSTRecur() to construct BST */
struct TNode* sortedListToBST(struct LNode *head)
{
    /*Count the number of nodes in Linked List */
    int n = countLNodes(head);

    /* Construct BST */
    return sortedListToBSTRecur(&head, n);
}

/* The main function that constructs balanced BST and returns root of it.
       head_ref -->  Pointer to pointer to head node of linked list
       n  --> No. of nodes in Linked List */
struct TNode* sortedListToBSTRecur(struct LNode **head_ref, int n)
{
        /* Base Case */
    if (n <= 0)
        return NULL;

    /* Recursively construct the left subtree */
    struct TNode *left = sortedListToBSTRecur(head_ref, n/2);

    /* Allocate memory for root, and link the above constructed left
       subtree with root */

    struct TNode *root = newNode((*head_ref)->data,(*head_ref)->name,(*head_ref)->meaning);

    root->left = left;

    /* Change head pointer of Linked List for parent recursive calls */
    *head_ref = (*head_ref)->next;

    /* Recursively construct the right subtree and link it with root
      The number of nodes in right subtree  is total nodes - nodes in
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = sortedListToBSTRecur(head_ref, n-n/2-1);


    return root;
}

/* UTILITY FUNCTIONS */

/* A utility function that returns count of nodes in a given Linked List */
int countLNodes(struct LNode *head)
{
    int count = 0;
    struct LNode *temp = head;
    while(temp!=NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

/* Function to insert a node at the beginging of the linked list */
void push(struct LNode** head_ref, int new_data, string new_name, string new_meaning)
{
    /* allocate node */
    struct LNode* new_node = new LNode;
    /* put in the data  */
    new_node->data  = new_data;
    new_node->name=new_name;
 	new_node->meaning=new_meaning;
    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Function to print nodes in a given linked list */
void printList(struct LNode *node)
{
    while(node!=NULL)
    {
        cout<<node->data<<" ";
        cout<<node->name<<" ";
        cout<<node->meaning<<" "<<endl;
        node = node->next;
    }
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct TNode* newNode(int data,string name, string meaning)
{
    struct TNode* node = new TNode;
    node->data=data;

    node->meaning=meaning;
    node->name=name;

	node->left = NULL;
    node->right = NULL;

    return node;
}
/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* node)
{
    if (node == NULL)
        return;
    cout<<endl<<node->data<<" ";
    cout<<node->name<<" ";
    cout<<node->meaning<<" ";
    preOrder(node->left);
    preOrder(node->right);
}
// Search function to search over the BST for the word being given by the user which is stored in the string variable look

TNode *searchBST(TNode *root, string look){
    if(root!=NULL){
 if(strcmp(root->name.c_str(),look.c_str())==0){
            cout<<"Word Found ! :"<<root->name<<" "<<root->meaning<<endl;
            return root;
        }
        if(strcmp(root->name.c_str(),look.c_str())<0){
            searchBST(root->right,look);
        }
        else{
            searchBST(root->left,look);
        }
    }
    if(root==NULL)
        cout<<"Not Found\n";
}

/* Driver program to test above functions*/
int main()
{
    string look;
    /* Start with the empty list */
    struct LNode* head = NULL;
    string str, token, delimiter = "-";
    int index,check=0;
    string name,mean;
	ifstream infile;
	size_t pos = 0;

	infile.open("input.txt");
	while(!infile.eof()){/// from line 1 to end of file read line by line to string str !
        infile>>str;/// Load the whole Line
        while ((pos = str.find(delimiter)) != std::string::npos) {///Tokenize the Line using "-" as delimiter !
            token = str.substr(0, pos);
            if(check==0)index=atoi(token.c_str());
            if(check==1)name=token;
            check++;
            str.erase(0, pos + delimiter.length());
        }
        mean=str;
        push(&head,index,name,mean);
        check=0;
	}
        infile.close();

        cout<<"Given Linked List "<<endl;
        printList(head);

        /* Convert List to BST */
        struct TNode *root = sortedListToBST(head);
        cout<<"\n \n \t PreOrder Traversal of constructed BST"<<endl;
        preOrder(root);


    int option;
    cout<<"\n\n\tEnter Option\n 1.Search\n 2.Exit\n";
    cin>>option;
    while(option!=2){
            cout<<"\n Enter a word to search: ";
            cin>>look;
            searchBST(root,look);
        }
    return 0;
}
