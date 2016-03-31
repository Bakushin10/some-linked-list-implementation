#ifndef LINKEDLIST_H
#define LINKEDLIST_H


/*

	3/19/15
	Shin Nagai
	Program 2
	linked list





*/

class Node{
    public:
        Node();
        Node(int data,char* name);
        Node* insert_worst(Node* plist, int dataSize, char* name,int start);
        Node* insert_best(Node* plist, int dataSize, char* name,int start);
        Node* kill(Node* plist,char* name); ///delete the Node
        int getData();
        char* getName();
        void print(Node* plist);
        int getMemoryInUse(int data);
        void printMemory(Node* plist);
        void printMemory_2(Node* plist);
        bool hasEnoughMemory(int inputMemory,Node* plist);
        bool hasSameName(Node* plist,char* name);
        void nextRow(int* a, int* b);
        int fragmentation(Node* plist);
    private:
        //int dataSize;//keep track of how many cells one node is using
        int data;//row input
        int memoryInUse;
        int start;///indicates the point where node starts
        int end;  ///indicatest the point where each node ends
        char* name;
        Node* next;
};

class linkedlist{

    public:
        linkedlist();
        virtual ~linkedlist();
        int getChoice();
       // void addToGrid(Node* plist);
    private:
        Node *head;
};

#endif // LINKEDLIST_H

