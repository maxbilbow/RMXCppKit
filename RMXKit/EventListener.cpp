//
//  EventListener.cpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Tests.h"
#import "EventListener.h"
#import "NotificationCenter.h"

#define DEBUG_THIS (DEBUG_INCLUDE_TEST_OUTPUT || DEBUG_RMX_EVENT_LISTENER)
using namespace rmx;
using namespace std;

void EventListener::init(bool add) {
    if (add)
        NotificationCenter::addListener(this);
}

EventListener::~EventListener(){
    try {
        NotificationCenter::removeListener(this);
        //    Object::~Object();
#if DEBUG_MALLOC
        cout << "~DELETING EventListener: " << *this << endl;
#endif
    } catch (exception e) {
        cout << "ERROR deleting Listener: " << e.what() << endl;
    }
   
}

EventListener * EventListener::clone() {
    EventListener * clone =  (EventListener*) Object::clone();
    if (NotificationCenter::hasListener(this)) {
#if DEBUG_THIS
        cout << "\n *** Should Add the Clone: " << Name() << endl << endl;
#endif
        NotificationCenter::addListener(clone);
    }
#if DEBUG_THIS
    else {
        cout << "\n *** Diddn't Add the Clone: " << Name() << endl << endl;
    }
#endif
    
    return clone;
}


void EventListener::StartListening() {
    NotificationCenter::addListener(this);
}

void EventListener::StopListening() {
    NotificationCenter::removeListener(this);
}

///Successfull test of
/// • Object::clone()
/// • Object::Instantiate(Object inheritance)
/// • Event Listening with cloned objects
void RMXEventListenerTest(){
    std::cout << "\n\n******** BEGIN TEST: EventListener ********\n" << std::endl;
    EventListener * o = new EventListener(" O Will Listen");
    EventListener p = EventListener(" P Will Listen");
    EventListener p2 = EventListener("P2 Not Listening", false);
    p.setDescription("I am the second object! I SHOULD LISTEN");
    p2.setDescription("I am the third object and shaln't be listening!");
//    p2.clone();
//    o->setName("o1");
    EventListener * clone = o->clone();
    EventListener * clone2 = Object::Instantiate(clone);
    Object::Instantiate(&p);
    Object::Instantiate(&p2);
//    clone2->setName("clone2");
    clone2->setDescription("AND IM A CLONE OF A CLONE! I SHOULD LISTEN");
    

    o->setDescription("I am the first object: I SHOULD LISTEN");
    
//    clone->setName("Clone1");
    clone->setDescription("I am a clone of the first object: I SHOULD LISTEN");
    
//    cout << endl;
//    cout << *o << endl;
//    cout << *clone << endl;
//    cout << *clone2 << endl;
//    cout << p.ToString() << endl;
//    cout << p2.ToString() << endl;
//    cout << endl;
    
    NotificationCenter::eventDidOccur("Something's Happening!",  new string("Poof!"));
    NotificationCenter::notifyListeners("MESSAE RECEIVED!");
    
    
    std::cout <<   "\n********   END TEST: EventListener ********\n" << std::endl;

}