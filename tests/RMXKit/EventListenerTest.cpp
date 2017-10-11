//
// Created by max on 11/10/17.
//
#include "../../RMXKit/EventListener.h"
#include "../../RMXKit/Object.h"
#include "../../RMXKit/NotificationCenter.h"

using namespace rmx;

class EventListenerTest : public EventListener, public Printable {

public:
    EventListenerTest(const std:: string &s) : EventListener::EventListener(s){};

    EventListenerTest(std:: string s, bool b) : EventListener::EventListener(s,b){};

};
///Successfull test of
/// • Object::clone()
/// • Object::Instantiate(Object inheritance)
/// • Event Listening with cloned objects
void RMXEventListenerTest(){
    std::cout << "\n\n******** BEGIN TEST: EventListener ********\n" << std::endl;
    EventListenerTest * o = new EventListenerTest(" O Will Listen");
    EventListenerTest p = EventListenerTest(" P Will Listen");
    EventListenerTest p2 = EventListenerTest("P2 Not Listening", false);
    p.setDescription("I am the second object! I SHOULD LISTEN");
    p2.setDescription("I am the third object and shaln't be listening!");
//    p2.clone();
//    o->setName("o1");
    EventListenerTest * clone = Object::Instantiate(o);
    EventListenerTest * clone2 = Object::Instantiate(clone);
//    Object::Instantiate(&p);
//    Object::Instantiate(&p2);
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

    NotificationCenter::eventDidOccur("Something's Happening!",  new std::string("Poof!"));
    NotificationCenter::notifyListeners("MESSAE RECEIVED!");


    std::cout <<   "\n********   END TEST: EventListener ********\n" << std::endl;

}