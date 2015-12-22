//
//  Dictionary.cpp
//  RMXKit
//
//  Created by Max Bilbow on 29/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//



//#import <iostream>
//
//
//#import "LinkedList.h"
#import "Tests.h"
#import "Dictionary.h"
#import "Object.h"
#define DEBUG_THIS (DEBUG_INCLUDE_TEST_OUTPUT || DEBUG_RMX_DICTIONARY)
using namespace std;
using namespace rmx;



typedef Object Thing;



void RMXDictionaryTest() {
    std::cout << "\n\n******** BEGIN TEST: Dictionary ********\n" << std::endl;
        //Lets start by adding a "Thing" to a linked list
    LinkedList<Thing> * things = new LinkedList<Thing>();
    things->append(new Thing());
#if DEBUG_THIS
    cout << "Added a Thing to the list: " << things->first() << endl;
#endif
    //Create a dictionary with a string key.
    Dictionary<string, Thing> * dict = new Dictionary<string, Thing>();
    
    //Set the first THING to the Thing we have in our list
    dict->setValueForKey("THING", things->getValue(0));
    dict->setValueForKey("THING2", new Thing());
//    things->getValue(0)->name = "World!";
#if DEBUG_THIS
    cout << endl;
    cout << "  Printing thing 2: " << dict->getValueForKey("THING2")->ToString() << endl;
    cout << "  Printing thing 1: " << dict->getValueForKey("THING")->ToString() << endl;
#endif
    things->first()->setName("World!");
    dict->getValueForKey("THING2")->setName("Hello!");
    //Check the name change in the list.
#if DEBUG_THIS
    cout << "Thing 1 is now: " << things->first() << endl;
    
    //Check the name was changed in the dictionary also.
    cout << endl;
    cout << "  Printing thing 2: " << dict->getValueForKey("THING2")->ToString() << endl;
    cout << "  Printing thing 1: " << dict->getValueForKey("THING")->ToString() << endl;
#endif
    //Create a new thing
    Thing * aThing = new Thing();
    aThing->setName("Monty");
    
    //Replace the thing at key "THING"
#if DEBUG_THIS
    Thing* oldThing = dict->setValueForKey("THING", aThing);

    //Do we still have the old Thing? I.e. was it actually replaced?
    cout << endl;
    cout << "  We Repleced (and removed) thing 1: " << oldThing << endl;
    //What remains in out dictionary?
    cout << "                   Printing thing 2: " << dict->getValueForKey("THING2") << endl;
    cout << "               Printing new thing 1: " << dict->getValueForKey("THING") << endl;
#endif
    std::cout <<   "\n********   END TEST: Dictionary ********\n" << std::endl;
    
}

