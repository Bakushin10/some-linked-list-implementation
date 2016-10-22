#include "pa2.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;


linkedlist::linkedlist() {
    //initialize to 0 indicates that array is empty


}

linkedlist::~linkedlist() {

}

int linkedlist::getChoice() {
    int choice=0;
    bool valid = false;

    while(!valid) {
        std::cout<<"1. Add program"<<endl;
        std::cout<<"2. Kill program"<<endl;
        std::cout<<"3. Fragmentation"<<endl;
        std::cout<<"4. Print memory"<<endl;
        std::cout<<"5. Exit"<<endl;
        std::cout<<":";
        std::cin >> choice;

        if((choice<0 || choice>5)) {
            std::cout<<"\n\n*** Please Enter 1-5 ***\n\n\n";
            continue;
        }
        if(cin.fail()) {
            std::cout<<"\n\n*** Invalid input ***\n\n\n";
            std::cout<<"    Enter an Integer\n";
            cin.clear();
            cin.ignore(255, '\n');
            continue;
        }

        valid = true;
    }
    return choice;
}

Node::Node() {

}

Node::Node(int memoryInUse,char* name) {
    this->memoryInUse=memoryInUse;///user input(raw data)
    this->name=name;
};

bool Node::hasSameName(Node* plist,char* name) {
    while(plist != NULL) {
        if(strcmp(plist->name,name)==0)
            return true;
        plist = plist->next;
    }
    ///does not have same progrm name
    return false;
}///end of hasSameName

bool Node::hasEnoughMemory(int inputMemory,Node* plist) {

    int memoryLeft=0;
    int temp;

    ///when there is no nodes
    if(plist == NULL)
        return true;

    memoryLeft = plist->start;

    while(plist != NULL) {
        if(plist->next!= NULL) {
            temp = plist->next->start - plist->end;
            if(temp > memoryLeft)
                memoryLeft = temp;
        } else {
            temp = 32-plist->end;
            if(temp > memoryLeft)
                memoryLeft = temp;
        }
        plist= plist->next;
    }

    if(memoryLeft >= inputMemory)
        return true;
    else
        return false;
}///end of hasEnoghtMemory

int Node::getMemoryInUse(int data) {
    ///return the amount of memory that will be used
    int memory;

    if(data%4 != 0)
        memory = 1+(data/4);
    else
        memory = (data/4);

    return memory;
}

Node* Node::insert_worst(Node *list, int data, char* name,int start) {

    Node* saveList = list;
    Node* savelink = 0;
    Node* pNew = new Node(data,name);
    int diff =0;
    int savediff =0;
    bool match = false;

    ///when list is empty
    if(list == NULL) {
        pNew->start = start;
        pNew->end = data;
        return pNew;
    }

    ///first node;
    savediff = list->start;
    pNew->start = 0;
    pNew->end = data;
    int endSpace;

    while(list != NULL) {

        if(list->next == NULL) {
            endSpace = 32-list->end;
            if(endSpace >= savediff) {
                pNew->start = list->end;
                pNew->end = list->end+data;
                savelink = list->next;
                savediff = endSpace;
            }
            list = list->next;
            continue;
        }

        ///if list->next != NULL
        diff = list->next->start - list->end;

        if(diff>savediff) {
            pNew->start = list->end;
            pNew->end = list->end+data;
            savelink = list->next;
            savediff = diff;
        }
        list = list->next;
    }///end of while

    list = saveList;
    diff =  list->start;

    if(diff == savediff) {
        pNew->next = list;
        return pNew;
    }

    while(!match) {

        if(list->next == NULL) {
            list->next = pNew;
            match = true;
            continue;
        } else {
            diff = list->next->start - list->end;
        }

        if(diff == savediff) {
            ///do swap
            list->next = pNew;
            pNew->next = savelink;
            match = true;
            continue;
        }

        list= list->next;
    }

    return saveList;
}///end of worst

///this function is NOT a recursive function
Node* Node::insert_best(Node *list, int data, char* name,int start) {

    Node* saveList = list;
    Node* savelink = 0;
    Node* pNew = new Node(data,name);
    int diff =0;
    int savediff =0;
    bool match = true;

    ///if list is empty
    if(list == NULL) {
        pNew->start=start;
        pNew->end=data;
        return pNew;
    }

    if(list->start >= data) {
        ///if found he best fit at the beginning
        if(list->start == data) {
            pNew->start = start;
            pNew->end = data;
            pNew->next = list;
            return pNew;
        } else {
            pNew->start = start;
            pNew->end = data;
            savediff = list->start;
        }
    }


    ///find the best fit
    while(list != NULL) {
        if(list->next == NULL) {
            diff = 32 - list->end;
            if(diff<savediff) {
                pNew->start = list->end;
                pNew->end = list->end+data;
                savediff = diff;
                savelink = list->next;
            }
            if(savediff == 0) {
                ///this happens when there is no space in the list
                pNew->start = list->end;
                pNew->end = list->end+data;
                savediff = diff;
                savelink = list->next;
            }
            list = list->next;
            continue;
        }

        diff = list->next->start - list->end;

        if((diff < savediff) || (savediff == 0 && diff != 0)) {
            pNew->start = list->end;
            pNew->end = list->end+data;
            savediff = diff;
            savelink = list->next;
        }

        list= list->next;
    }//end of while

    list = saveList;

    while(match) {

        ///you did not find any space to put a node in
        if(list->next == NULL) {

            list->next = pNew;
            match = false;///to stop loop
            continue;
        }

        diff = list->next->start - list->end;

        if(diff == savediff) {
            list->next = pNew;
            pNew->next = savelink;
            match = false;
            continue;
        }
        list = list->next;
    }//end of while
    return saveList;

}//end of insert_best

Node* Node::kill(Node *front, char* name) {

    Node* temp = front;
    Node* del = 0;

    // Only need to delete if the list is not null.
    if (temp != NULL) {
        // Take care of the case where first node needs to be deleted.
        if (strcmp(temp->name, name)==0) {
            del = temp -> next;
            delete (temp);
            return del;
        }
        // Otherwise, loop until you find the node to delete and do so.
        while (temp->next != NULL) {
            if (strcmp(temp ->next->name, name)==0) {
                del = temp -> next;
                temp->next = temp ->next->next;
                delete (del);
                return front;
            }
            temp = temp -> next;
        }

    }
    return front;
}

int Node::fragmentation(Node* list) {
    int flag=1;
    
    ///if list is empty
    if(list == NULL)
        return 0;
        
    while(list != NULL) {

        ///if list->next exits, do the following
        if(list->next != NULL) {
            ///if there is more than one fragment
            if(list->end != list->next->start)
                flag++;
        }

        list=list->next;
    }
    return flag;
}//end of fragmentation

int Node::getData() {
    int data;
    bool valid = false;

    while(valid == false) {
        cout<<"Program Size (KB) - ";
        cin >> data;

        if(cin.fail()) {
            std::cout<<"\n*** Invalid input ***\n";
            std::cout<<"    Enter an Integer\n";
            cin.clear();
            cin.ignore(255, '\n');
            continue;
        }
        valid = true;
    }

    return data;
}

char* Node::getName() {
    char* name = new char[25];
    cout<<"Program Name - ";
    cin>> name;
    return name;
}

void Node::print(Node* list) {

    // Iterate through each item and print it!
    while (list != NULL) {
        printf("-->%i ", list->memoryInUse);
        cout<<list->start<<","<<list->end<<endl;
        list = list->next;
    }
    printf("\n");
}

void Node::printMemory_2(Node* list) {
    int i=0;
    ///checks if node is empty
    if(list != NULL) {
        while(i<32) {

            if(i%8 == 0 && i!=0)
                cout<<endl;
            if(list != NULL) {
                if(list->end == i) {
                    list =list->next;
                    continue;
                }

                if(list->start <= i) {
                    std::cout<<list->name<<" ";
                    i++;
                    continue;
                }
            }
            std::cout<<"Free ";
            i++;
        }//end of while
    }///when there is no
    else {
        for(int i=0; i<4; i++) {
            for(int j=0; j<8; j++) {
                std::cout<<"Free ";
            }
            std::cout<<endl;
        }
    }
}//end of printMemory


int main(int argc,char** argv) {

    int choice =0;
    int best_worst=0; /// best = 0, worst =1
    linkedlist* ll = 0;
    Node* plist = 0;
    char* name;
    int data;
    int inputMemory=0;
    int Fragmentation=0;


    if(strcmp(argv[1],"best")==0) {
        cout<<"\n\n\tRunning on Best Case\n\n\n";
    } else if(strcmp(argv[1],"worst")==0) {
        cout<<"\n\n\tRunning on worst Case\n\n\n";
        best_worst = 1;
    } else {
        cout<<"\n\n\tInvalid input Bye-Bye\n\n\n";
        choice = 5;
    }

    while(choice!=5) {
        choice = ll->getChoice();
        switch(choice) {
        case 1:
            name = plist->getName();
            data = plist->getData();
            inputMemory = plist->getMemoryInUse(data);

            ///check the same name
            if(plist->hasSameName(plist,name)) {
                std::cout<<"\nError, Program "<<name<<" is already running.\n\n";
                continue;
            }

            ///check if momery has enoough space
            if(plist->hasEnoughMemory(inputMemory,plist)) {
                if(best_worst == 0)
                    plist = plist->insert_best(plist,inputMemory,name,0);
                else
                    plist = plist->insert_worst(plist,inputMemory,name,0);

                std::cout<<"\nProgram "<< name <<" added successfully: " << inputMemory << " page(s) used.\n";
            } else
                std::cout<<"\nError, Not enough memory for "<<name<<endl;

            break;
        case 2:
            name = plist->getName();
            plist = plist->kill(plist,name);
            break;
        case 3:
            Fragmentation=plist->fragmentation(plist);
            std::cout<<"There are "<<Fragmentation<< " fragment(s).\n";
            break;
        case 4:
            plist->printMemory_2(plist);
            break;
        }
        plist->print(plist);
    }

    return 0;
}

