//
//  SimpleEventListener.cpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "SimpleEventListener.h"

#ifdef DEBUG_RMX_EVENT_LISTENER
#define DEBUG_THIS true
#endif

using namespace rmx;
using namespace std;

SimpleEventListener::SimpleEventListener(NotificationCenter *notificationCenter) {
    this->notificationCenter = notificationCenter;
}

SimpleEventListener::~SimpleEventListener(){
    try {
        this->stopListening();
#if DEBUG_MALLOC
        cout << "~DELETING SimpleEventListener: " << *this << endl;
#endif
    } catch (exception & e) {
        cout << "ERROR deleting Listener: " << e.what() << endl;
    }
   
}


SimpleEventListener * SimpleEventListener::startListening() {
    this->notificationCenter->addListener(this);
    return this;
}

SimpleEventListener * SimpleEventListener::stopListening() {
    this->notificationCenter->removeListener(this);
    return this;
}

void SimpleEventListener::sendMessage(AnEvent message, EventArgs args) {
#ifdef DEBUG_THIS
    std::cout << this << "\n    Message Received: " << message << std::endl << std::endl;
#endif
}

void SimpleEventListener::onEventDidEnd(AnEvent theEvent, EventArgs args) {
#ifdef DEBUG_THIS
    std::cout << this << "\n         Event Ended: " << theEvent << ", with args: " << args << std::endl << std::endl;
#endif
}

void SimpleEventListener::onEventDidStart(AnEvent theEvent, EventArgs args) {
#ifdef DEBUG_THIS
    std::cout << this << "\n       Event Started: " << theEvent << ", with args: " << args << std::endl << std::endl;
#endif
}


#ifdef DEBUG_THIS
#undef DEBUG_THIS
#endif