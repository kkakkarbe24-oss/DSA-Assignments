#include <iostream>
using namespace std;

class Node{
	public:
	int info;
	Node*next= Null;
	
	Node(int val){
		info=val;
	}
};

class LinkedList{
	public:
		void InsertBeg(Node* head, int val){
			Node *newnode= new Node(val);
			newnode->next=head;
			head=newnode;
		}
		
		void InsertEnd(Node* head, int val){
			Node *newnode= new Node(val);
			Node *curr= head;
			while(curr->next!=NULL){
				curr=curr->next;
			}
			curr->next= newnode;
		}
		
		void InsertAfter(Node* head, int val, int after){
			Node *newnode= new Node(val);
			Node *curr= head;
			while(curr->info!=after){
				curr=curr->next;
			}
			newnode->next= curr->next;
			curr->next= newnode;
		}
		
		void InsertBefore(Node* head, int val, int before){
			Node *newnode= new Node(val);
			Node *curr= head;
			while(curr->next->info!=before){
				curr=curr->next;
			}
			newnode->next= curr->next;
			curr->next= newnode;
		}
		
		
		void DeleteBeg(Node*head){
			Node *ptr=head;
			delete ptr;
			head= head->next;
		}
		
		void DeleteEnd(Node*head){
			Node*ptr= head;
			while(ptr->next->next!=NULL){
			ptr=ptr->next;
			}
			
			delete ptr->next;
			ptr->next=NULL;
		}
	
			
		
		void DeleteThis(Node*head, int This){
			Node*ptr= head;
			while(ptr->next->info!=This){
			ptr=ptr->next;
			}
			
			ptr->next=ptr->next->next;
			delete ptr->next;
		}
		
		
		void Search(Node* head, int val){
			
			Node*ptr= head;
			int count=0;
			while(ptr->info!=val){
				ptr=ptr->next;
				count++;
			}
			
			cout<<"\n"<<val<<" is found at"<<count<<"positions from head";
		}
		
		void Display(Node*head)		{
			Node*ptr= head;
			while(ptr->next!=NULL){
				cout<<ptr-> info<<"<<";
				ptr= ptr-> next;
			}
		}
		
		void DeleteAll(Node*head, int val){
			Node*ptr= head;
			int count=0;
			while(ptr->next!=NULL){
				if(ptr->next->info==val){
					count++;
					ptr->next=ptr->next->next;
					delete ptr->next;
				}
			ptr=ptr->next;
			}
			
			cout<<"\nCount= "<<count<<"Updated linked list:";
			Display(head);
		}
		
		void FindMiddle(Node* head){
			Node* slow= head;
			Node* fast=head;
			
			while(fast->next!=NULL){
				slow=slow->next;
				fast= fast->next->next;
			}
			
			cout<<"\nMiddle element is"<<slow->info;
		}
		
		void ReverseList(Node*head){
			Node* next=NULL;
			Node*curr= head;
			Node* prev= NULL;
			
			while(next->next!=NULL){
				next= curr->next;
				curr->next= prev;
				prev=curr;
				curr=next;
			}
		}
};
