//
// Created by max on 11/10/17.
//
#include "Object.h"
//#include "NotificationCenter.h"
#include "SimpleEventListener.h"

using namespace rmx;

class EventListenerTest : public SimpleEventListener, public Printable {

    std::string desc;
public:
    explicit EventListenerTest(const std:: string &s) : SimpleEventListener()
    {
        desc = s;
    };

    std::string toString() override {
        return desc;
    }

    void onEventDidStart(AnEvent event,EventArgs args) override{
        std::cout << "EVENT START: " << event << ", ARGS: " << args << " ==> " << this << std::endl;
    }

    void onEventDidEnd(AnEvent event,EventArgs args) override{
        std::cout << "EVENT END: " << event << ", ARGS: " << args << " ==> " << this << std::endl;
    }

    void sendMessage(AnEvent message,EventArgs args) override{
        std::cout << "MSG: " << message << ", ARGS: " << args << " ==> " << this << std::endl;
    }



};
///Successfull test of
/// • Object::clone()
/// • Object::Instantiate(Object inheritance)
/// • Event Listening with cloned objects
void RMXEventListenerTest(){
    std::cout << "\n\n******** BEGIN TEST: SimpleEventListener ********\n" << std::endl;
    SimpleEventListener * o = (new EventListenerTest(" O SHOULD LISTEN"))->startListening();
    EventListenerTest p = EventListenerTest(" P Will Listen");
    p.startListening();
    EventListenerTest p2 = EventListenerTest("P2 Not Listening");



    auto nc = NotificationCenter::getInstance();
    nc->eventDidOccur("Something's Happening!",  new std::string("Poof!"));
    nc->notifyListeners("MESSAE RECEIVED!");


    std::cout <<   "\n********   END TEST: SimpleEventListener ********\n" << std::endl;

}

int main()
{
    RMXEventListenerTest();

    return 0;
}