#include <iostream>
#include "Operators.hpp"
using namespace std ;
void Operators::makeList(double arr[], int size) {
    if (topList >= 0) {
        return;
    }
    ModifiedLinkedList* newList = new ModifiedLinkedList();
    for (int i = 0; i < size; i++) {
        newList->add(arr[i]);
    }
    topList++;
    lists[topList] = newList;
}
void Operators::cutList(int position) {
    if (topList < 0) {
        return;
    }
    ModifiedLinkedList* cutList1;
    ModifiedLinkedList* cutList2;
    int result = lists[topList]->cut(position, cutList1, cutList2);
    if (result == -1) {
        return;
    }
    else if(result == 0){
        lists[topList] = cutList1;
        topList++;
          lists[topList] = cutList2;
    }
    topOp++;
    ops[topOp] = new Op(position);
    cout<< "CUT Operation has been done." << endl;
}
void Operators::cloneList() {
    if (topList < 0) {
        return;
    }
    ModifiedLinkedList* clonedList = lists[topList]->clone();
    topList++;
    lists[topList] = clonedList;
    topOp++;
    ops[topOp] = new Op(-1);
    cout<< "CLONE Operation has been done"<<endl;
}
void Operators::printCurrentList() {
    if (topList < 0) {
        return;
    }
    lists[topList]-> print();
}
void Operators::printHistory() {
    cout << "===The lists in the history stack: ===" << endl;
    for(int i = topList;i>=0;i--){
        cout << "Index in the stack: " << i  << endl;
        lists[i]->print();
    }
    cout<< endl;
    cout << "============================================" << endl;
    cout << endl << "===The Operator in the history stack: ===" << endl;
    if(topOp==-1){
        cout << "[X] Nothing in this stack ..." << endl;
    }
    else {
        for(int i = topOp;i>=0;i--){
            cout <<"Index in the stack: " << i << endl ;
            cout << "Operator: "<< ops[i]->op  ;
            if(ops[i]->pos!=-1){
                cout << " at the position : " <<  ops[i]->pos;
            }
            cout << endl;
        }
    }
    cout <<endl<< "==============================================" << endl;
}
void Operators::undo() {
    if (topOp < 0) {
        return;
    }
    Op* lastOp = ops[topOp];
    if (lastOp->op == "CUT") {
        if (topList < 1) {
            return;
        }
        ModifiedLinkedList* list1 = lists[topList];
        topList--;
        ModifiedLinkedList* list2 = lists[topList];
        topList--;
        ModifiedLinkedList* mergedList = list1->mergeWith(list2);
        topList++;
        lists[topList] = mergedList;
    } else if (lastOp->op == "CLONE") {
        if (topList < 0) {
            return;
        }
        delete lists[topList];
        topList--;
    }
    delete lastOp;
    topOp--;
}
