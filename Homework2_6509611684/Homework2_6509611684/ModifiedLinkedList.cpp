#include <iostream>
#include "ModifiedLinkedList.hpp"
using namespace std ;
void ModifiedLinkedList::add(double n) {
    Node* newNode = new Node(n);
    newNode->next = head;
    head = newNode;
    counter++;
    mid = head;
    for(int i = 1; i < (counter+1)/2; i++){
        mid = mid->next;
    }
}
 void ModifiedLinkedList::getData(double*& arr, int & size) {
            size = 0;
            Node* current = head ;
            while (current != NULL) {
                size++;
                current = current->next;
            }
            arr = new double[size];
            current = head;
            for (int i = 0; i < size; i++) {
                arr[i] = current->data;
                current = current->next;
            }
  }
 ModifiedLinkedList* ModifiedLinkedList::clone() {
     ModifiedLinkedList* clonedList = new ModifiedLinkedList();
     clonedList->counter = counter;
     Node* current = head;
     Node* newHead = NULL;
     Node* tail = NULL;
     while (current != NULL) {
         Node* newNode = new Node(current->data);
         if (newHead == NULL) {
             newHead = newNode;
             tail = newNode;
         } else {
             tail->next = newNode;
             tail = newNode;
         }
         current = current->next;
     }
     clonedList->head = newHead;
     if (counter % 2 == 0) {
         clonedList->mid = clonedList->head;
         for (int i = 1; i < counter / 2; i++) {
             clonedList->mid = clonedList->mid->next;
         }
     } else {
         clonedList->mid = clonedList->head;
         for (int i = 0; i < counter / 2; i++) {
             clonedList->mid = clonedList->mid->next;
         }
     }
     return clonedList;
 }
     ModifiedLinkedList* ModifiedLinkedList::mergeWith(ModifiedLinkedList* otherList) {
         if (otherList->head == NULL) {
             return this;
         }
         Node* lastNode = otherList->head;
         while (lastNode->next != NULL) {
             lastNode = lastNode->next;
         }
         lastNode->next = this->head;
         this->head = otherList->head;
         this->counter += otherList->counter;
         if (this->counter % 2 == 0) {
             this->mid = this->head;
             for (int i = 1; i < this->counter / 2; i++) {
                 this->mid = this->mid->next;
             }
         } else {
             this->mid = this->head;
             for (int i = 0; i < this->counter / 2; i++) {
                 this->mid = this->mid->next;
             }
         }
         return this;
     }
     int ModifiedLinkedList::cut(int position, ModifiedLinkedList* &cutList1, ModifiedLinkedList* &cutList2) {
         if (position < 1 || position > counter) {
             return -1;
         }
         if(head == NULL){
             return 1;
         } else{
        cutList1 = new ModifiedLinkedList();
        cutList2 = new ModifiedLinkedList();
        cutList1->counter = position;
        cutList2->counter = this->counter - position;
        Node* tmp = this->head;
        int curPos = 1;
        int mid1 = (position+1)/2;
        int mid2 = ((cutList2->counter + 1)/2) + position;
        cutList1->head = this->head;
        Node* cutNode = head;
        while(tmp != NULL){
        if(curPos == position){
            cutNode = tmp;
        }
        if(curPos == position+1){
            cutList2->head = tmp;
        }
        if(curPos == mid1){
            cutList1->mid = tmp;
        }
        if(curPos == mid2){
            cutList2->mid = tmp;
        }
        curPos++;
        tmp = tmp->next;
    }
    cutNode->next = NULL;
            return 0;
         }
     }
     void ModifiedLinkedList::removeAllNodes() {
         while (head != NULL) {
             Node* temp = head;
             head = head->next;
             delete temp;
         }
         counter = 0;
         mid = NULL;
     }
     void ModifiedLinkedList::print() {
         Node* current = head;
         while (current != NULL) {
             if (current == mid) {
                 cout << "[" << current->data << "] ";
             }else {
                 cout << current->data << " ";
             }
             current = current->next;
         }
         cout << ", Mid = :" << mid->data << endl;
     }
