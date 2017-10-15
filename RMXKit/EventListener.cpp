//
//  EventListener.cpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "EventListener.h"
#include "NotificationCenter.h"

#ifdef DEBUG_RMX_EVENT_LISTENER
#define DEBUG_THIS true
#endif

using namespace rmx;
using namespace std;

void EventListener::init(bool add) {
    if (add)
        NotificationCenter::getInstance()->addListener(this);
}

EventListener::~EventListener(){
    try {
        NotificationCenter::getInstance()->removeListener(this);
        //    Object::~Object();
#if DEBUG_MALLOC
        cout << "~DELETING EventListener: " << *this << endl;
#endif
    } catch (exception e) {
        cout << "ERROR deleting Listener: " << e.what() << endl;
    }
   
}


void EventListener::StartListening() {
    NotificationCenter::getInstance()->addListener(this);
}

void EventListener::StopListening() {
    NotificationCenter::getInstance()->removeListener(this);
}

void EventListener::SendMessage(const string &message, EventListener::EventArgs args) {
#ifdef DEBUG_THIS
    std::cout << this << "\n    Message Received: " << message << std::endl << std::endl;
#endif
}

void EventListener::OnEventDidEnd(const string &theEvent, EventListener::EventArgs args) {
#ifdef DEBUG_THIS
    std::cout << this << "\n         Event Ended: " << theEvent << ", with args: " << args << std::endl << std::endl;
#endif
}

void EventListener::OnEventDidStart(const string &theEvent, EventListener::EventArgs args) {
#ifdef DEBUG_THIS
    std::cout << this << "\n       Event Started: " << theEvent << ", with args: " << args << std::endl << std::endl;
#endif
}

#ifdef DEBUG_THIS
#undef DEBUG_THIS
#endif