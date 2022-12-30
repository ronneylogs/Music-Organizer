#include "PlayList.h"
#include <iostream>
#include <string>
#include <stdexcept>

using std::cout;
using std::endl;

// PlayList method implementations go here
//constructor
PlayList::PlayList():head(nullptr),length(0){}

//copy constructor
PlayList::PlayList(const PlayList& pl){
    
    unsigned int length = 0;
    if (pl.head == nullptr){
        return;
    }
    //setting the head as the song in playlist
    head = new PlayListNode(pl.head->song,nullptr);
    //setting prev and tmp node to traverse through play list
    PlayListNode * tmp = pl.head->next;
    PlayListNode * prev = head;
    while(tmp!=nullptr){
        //setting each new node one by one
        prev->next = new PlayListNode(tmp->song,nullptr);
        //adding 1 to the length of the play list for every iteration
        length++;
        tmp = tmp->next;//iterating through new play list
        prev = prev->next;// iterating through original play list
    }
}

//destructor
PlayList::~PlayList(){
    if(this->head == nullptr){

    }
    else{
        PlayListNode* cur = head;
        PlayListNode* tmp;
    

        while(cur!=nullptr){
            //traversing through playlist and deleting the previous node for each iteration
            tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
}


//overloaded assignment operator
PlayList& PlayList::operator=(const PlayList & pl){
    if(this==&pl){
        return *this;
    }
    PlayListNode* prev = head;
    PlayListNode* tmp = head;
    
    while(tmp!=nullptr){
        //deleting previous nodes
        prev = tmp;
        tmp = head->next;
        delete prev;
    }
    
    head = new PlayListNode(pl.head->song,nullptr);
    PlayListNode * t = pl.head->next;
    PlayListNode * p = head;
    while(t!=nullptr){
        p->next = new PlayListNode(t->song,nullptr);
        length++;
        t = t->next;//iterating through new play list
        p = p->next;// iterating through original play list
    }
    return *this;

}


//insert
//PRE:The pos must be greater than 0 and less than size - 1.
//POST:the length of play list will be 1 greater. New song in pos index.
void PlayList::insert(Song sng, unsigned int pos){
    unsigned int counter = 1;
    int flicker=0;
    PlayListNode * cur = head;
    PlayListNode * prev = nullptr;
    //if playlist is empty, make a new head 
    if(pos==0){
        auto new_node = new PlayListNode(sng,head);
        head = new_node;
        flicker=1;
    }
    //traverses through playlist
    while(cur!=nullptr&&flicker==0){
        prev = cur;
        cur = cur->next;
        //if the index is found
        if (counter == pos){
            //makes a new node at the position
            auto new_node = new PlayListNode(sng,cur);
            //previous node points to the new node
            prev->next = new_node;
            flicker=1;
        }
        counter++;
    }
    //length is now one node bigger
    this->length = length + 1;
}
    

//remove
//PRE:pos must be greater than 0 and less than size - 1.
//POST:the length of the play list will be 1 smaller. Song will be removed from play list.
Song PlayList::remove(unsigned int pos){
    unsigned int flicker1 = 0;
    PlayListNode * cur = head;
    int size = this->size();

    //edge case where there is only one item
    if(pos==0 && size == 1){

        Song del_song = this->head->song;
        PlayListNode* temp = this->head;
        this->head= this->head->next;
        delete temp;
        this->length--;
        return del_song;
    }
    //edge case where position is 0 and there is more than one song in play list
    if(pos == 0 && this->length > 1){
        Song del_song = this->head->song;
        PlayListNode* temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->length--;
        return del_song;
    }

    //traversing through play list to find node
    while(cur!=nullptr){
        //if index is found
        if (flicker1+1==pos){
            break;
        }
        cur = cur->next;
        flicker1++;
    }
    //node is removed by altering the nodes before and after
    PlayListNode* temp = cur->next;
    Song del_song = cur->next->song;
    cur->next = cur->next->next;
    this->length--;
    delete temp;
    return del_song;
}

//swap
//PRE: pos1 and pos2 must be greater than 0 and less than size - 1. pos1 and pos2 generally should not be the same
//POST: Swaps the song in pos1 with the song in pos2 using their nodes
void PlayList::swap(unsigned int pos1, unsigned int pos2){
    PlayListNode *prev_node1 = nullptr;
    PlayListNode *node1 = head;
    PlayListNode *prev_node2 = nullptr;
    PlayListNode *node2 = head;
    unsigned int counter1 = 0;
    unsigned int counter2 = 0;
    int boo1 = 0;
    int boo2 = 0;
    int adj = 0; // for adjacency test
    int equal = 0; //for equal pos test

    //checking for equal
    if(pos1==pos2){
        equal = 1;
    }
    //checking for adjacency
    if(pos1 + 1 == pos2 ||pos2 + 1 == pos1){
        adj = 1;
    }

    //traversing through play list to find pos1
    while(node1!=nullptr&&boo1!=1&&equal!=1){
        //if index is found
        if (counter1==pos1){
            boo1 = 1;
        }
        if(boo1!=1){
            prev_node1 = node1;
            node1 = node1->next;
            counter1++;
        }
    }
    //traversing through play list to find pos2
    while(node2!=nullptr&&boo2!=1&&equal!=1){
        //if index is found
        if (counter2==pos2){
            boo2 = 1;
        }
        if(boo2!=1){
            prev_node2 = node2;
            node2 = node2->next;
            counter2++;
        }
    }

    //swap part
    
    //dealing with next nodes
    PlayListNode *tmp = node2->next;
    node2->next=node1->next;
    node1->next=tmp;
    
    //dealing with previous notes

    //if one of the positions is the head
    if(prev_node1==nullptr&&adj!=1&&equal!=1){
        head = node2;
        prev_node2->next=node1;
    }
    if(prev_node2==nullptr&&adj!=1&&equal!=1){
        head = node1;
        prev_node1->next=node2;
    }

    //if both positions are not head nodes
    if(prev_node1!=nullptr&&prev_node2!=nullptr&&adj!=1&&equal!=1){
        prev_node1->next = node2;
        prev_node2->next = node1;
    }

    //adjacent nodes

    //prev_node1 is null and adjacent
    if(prev_node1==nullptr&&adj==1&&equal!=1){
        head = node2;
        head->next = node1;
        //prev_node2=nullptr;
    }

    //prev_node2 is null and adjacent
    if(prev_node2==nullptr&&adj==1&&equal!=1){
        head = node1;
        head->next = node2;
        //prev_node1=nullptr;
    }
    //boths nodes are inside nodes and adjacent
    if(prev_node1!=nullptr&&prev_node2!=nullptr&&adj==1&&equal!=1){
        if(pos1>pos2){
            node1->next=node2;
            prev_node2->next=node1;
            prev_node1=nullptr;
        }
        if(pos2>pos1){
            node2->next=node1;
            prev_node1->next=node2;
            prev_node2=nullptr;
        }
    }
}


//get
//PRE: pos must be greater than 0 and less than size - 1
//POST: Nothing happens to the play list. Returns the song in the pos index.
Song PlayList::get(unsigned int pos)const{
    
    PlayListNode* cur = this->head;
    int flicker = 0;
    unsigned int counter = 0;
    //traversing through play list
    while(cur!=nullptr&&flicker==0){
        //index is found
        if (counter == pos){
            flicker=1;
        }
        if(flicker==0){
            counter++;
            cur=cur->next;
        }
    }
    return cur->song;

}


//size
//PRE: Play list should exist.
//POST: Loops through play list and returns the size of it.
unsigned int PlayList::size()const{
    unsigned int counter = 0;
    auto cur = head;
    //traversing through play list and adding 1 for each iteration
    while(cur!=nullptr){
        counter++;
        cur = cur-> next;
    }
    return counter;
}
