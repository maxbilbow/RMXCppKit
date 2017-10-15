//
// Created by max on 11/10/17.
//
#include "EventListener.h"
#include "Object.h"
#include "NotificationCenter.h"

using namespace rmx;

class EventListenerTest : public EventListener, public Printable {

    std::string desc;
public:
    EventListenerTest(const std:: string &s) : EventListener::EventListener(s){};

    EventListenerTest(std:: string s, bool b) : EventListener::EventListener(s,b){};

    void setDescription(std::string s) {
        desc = s;
    }

    std::string toString() override {
        return desc;
    }

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
//    Object::Instantiate(&p);
//    Object::Instantiate(&p2);
//    clone2->setName("clone2");


    o->setDescription("I am the first object: I SHOULD LISTEN");

//    cout << endl;
//    cout << *o << endl;
//    cout << *clone << endl;
//    cout << *clone2 << endl;
//    cout << p.ToString() << endl;
//    cout << p2.ToString() << endl;
//    cout << endl;

    auto nc = NotificationCenter::getInstance();
    nc->eventDidOccur("Something's Happening!",  new std::string("Poof!"));
    nc->notifyListeners("MESSAE RECEIVED!");


    std::cout <<   "\n********   END TEST: EventListener ********\n" << std::endl;

}