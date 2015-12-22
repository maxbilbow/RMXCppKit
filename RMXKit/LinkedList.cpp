//
//  LinkedList.cpp
//  JustForFun
//
//  Created by Max Bilbow on 09/07/2015.
//  Copyright © 2015 Rattle Media. All rights reserved.
//
//#include "Interfaces.h"

//#include <iostream>

//#include "Tests.h"
#import "Tests.h"

#include "LinkedList.h"

#define DEBUG_THIS (DEBUG_INCLUDE_TEST_OUTPUT || DEBUG_RMX_LINKED_LIST)
using namespace std;


int TestVals[] = {0,1,2,3,4,5,6};//,5,6,7};

rmx::LinkedList<int> * MakeList() {
    rmx::LinkedList<int> * list = new rmx::LinkedList<int>();
    int length = sizeof(TestVals) / sizeof(int);

    for (int i = 0; i < length; ++i) {
        list->append(&TestVals[i]);
    }
    return list;
}


void TestRemoveAt(rmx::LinkedList<int> * list, int index) {
    try {
#if DEBUG_THIS || DEBUG_LINKED_LIST
        rmx::LinkedList<int>::Node * node = (rmx::LinkedList<int>::Node*) list->removeNodeAtIndex(index);
        cout << "Removed value at " << index <<  " (value: " << node->value << ")" << endl;
        list->print();
#endif
    } catch (invalid_argument e) {
        cout << "LnkedList.cpp: " << e.what() << endl;
    }

}

void TestArray(rmx::LinkedList<int> * list) {
    
#if DEBUG_THIS || DEBUG_LINKED_LIST
    for (int i = 0; i < list->count(); ++i) {
        std::cout << "Value at " << i << " is " << *list->getValue(i) << std::endl;
    }
    std::cout << "First Vaule is " << *list->first() << std::endl;
    std::cout << " Last Vaule is " << *list->last() << std::endl;
    
    int * vals = list->asArray();

    for (int i = 0; i < list->count(); ++i) {
        std::cout << "Array at " << i << " is " << vals[i] << std::endl;
    }
#endif
    
    list->asNodeArray()[1].value = new int(123);
#if DEBUG_THIS
    list->print();
#endif
    list->asArray()[1] = 123;
#if DEBUG_THIS
    list->print();
#endif
    delete list;
}

void TestRemove(rmx::LinkedList<int> * list) {
    TestRemoveAt(list,list->count() - 1); //last
    TestRemoveAt(list,3); //middle
    TestRemoveAt(list,0); //first
    TestRemoveAt(list,1); //last
    TestRemoveAt(list,1); //last
    TestRemoveAt(list,1); //last
    
    TestRemoveAt(list, -1);//error
    TestRemoveAt(list,3);
    
    list->removeAll();
#if DEBUG_THIS
    list->print();
#endif
    
    int vals[] = {0,1,2,3,4,5,6};//,5,6,7};
    list->append(vals, sizeof(TestVals));
#if DEBUG_THIS
    cout << "Removing first value: " << list->removeValueAtIndex(0) << endl;
    cout << "First: " << list->first() << ", Last: " << list->last() << endl;
    list->print();
#endif
    list->removeAll();
#if DEBUG_THIS
    list->print();
#endif

}

using namespace rmx;
void RMXLinkedListTest(void) {
    std::cout << "\n\n******** BEGIN TEST: LinkedList ********\n" << std::endl;
    
   LinkedList<int> * list = new LinkedList<int>();
    list->append(TestVals, sizeof(TestVals));
#if DEBUG_THIS
    list->print();
#endif
   TestArray(list);
    list->reverse();
#if DEBUG_THIS
    list->print();
#endif
    
    LinkedList<string> * sList = new LinkedList<string>();
    sList->append(new string("Hello"));
    sList->append("World");
    sList->append("Please");
    sList->append("Thanks");
#if DEBUG_THIS
    sList->print();
#endif
//    printList(list);
    sList->reverse();
#if DEBUG_THIS
    sList->print();

    cout << "Removing: " << sList->removeValue("Thanks") << endl;

    sList->print();
#endif
//    delete list;
//    delete sList;
    
   //   list->remove_by_value(3);
//   list->print();
	
	std::cout <<   "\n********   END TEST: LinkedList ********\n" << std::endl;
};

