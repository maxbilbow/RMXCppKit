//
//  RMXNotificationCenter.hpp
//  RMXKit
//
//  Created by Max Bilbow on 28/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef RMXNotificationCenter_cpp
#define RMXNotificationCenter_cpp


#define EVENT_STATUS_IDLE       0
#define EVENT_STATUS_ACTIVE     1
#define EVENT_STATUS_COMPLETE   2
#define EVENT_STATUS_FAILURE    3

#define EventStatus unsigned short
#define EventArgs void *
#define AnEvent std::string

//#include "LinkedList.h"
//#include "Dictionary.h"
#include <list>
#include <map>


namespace rmx {

    class EventListener {

    public:
//        typedef const std::string& AnEvent;
        /*!
         *  @author Max Bilbow, 15-08-04 16:08:30
         *
         *  Notify's all active listeners that an event is about to start
         *  @param theEvent as string
         *  @param args     anything
         *  @since 0.1
         */
        virtual void onEventDidStart(AnEvent theEvent, EventArgs args) = 0;

        /*!
         *  @author Max Bilbow, 15-08-04 16:08:53
         *
         *  Notify's all active listeners that an event did start
         *  @param theEvent string identifier
         *  @param args     anything
         *  @since 0.1
         */
        virtual void onEventDidEnd(AnEvent theEvent, EventArgs args) = 0;


        /*!
         *   @author Max Bilbow, 15-08-04 16:08:55
         *
         *   Receives a message
         *   Has to be overridden for to add specific method handing
         *   as it is currently not automatic to call a method this way
         *   @param message Name of selector or any other message
         *   @param args    any object.
         *   @since 0.1
         */
        virtual void sendMessage(AnEvent message, EventArgs args) = 0;
    };
    /*!
     *   @author Max Bilbow, 15-08-04 16:08:21
     *
     *   @brief  class for handling global notifications throughout a system.
     *
     *   @since <#0.1#>
     */
    class NotificationCenter {
    public:

        typedef std::string EventType;
//        typedef unsigned int EventStatus;
    private:
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  List of all active EventListeners, assuming they were added to the list.
         *  @see EventListener::EventListener(std::string name, bool add);
         *  @since 0.1
         */
        std::list<EventListener*> listeners = std::list<EventListener*>();
//        LinkedList<SimpleEventListener> * listeners;
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Dictionaty containing all events, that have been activated at least once, and their statuses.
         *  @since 0.1
         */
        std::map<EventType, EventStatus> events = std::map<EventType, EventStatus>();

//        Dictionary<EventType, EventStatus> * events;

    public:

        static NotificationCenter * getInstance();
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Returns true if the listener exists withing listeners
         *  i.e. The given listener is listening.
         *  @since 0.1
         */
        bool hasListener(EventListener * listener);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  If the given EventType exists and is not Idle, the event's status is set to EVENT_STATUS_IDLE.
         *  @since 0.1
         */
        void reset(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Adds the given listerner to listenrers iff it does not already exist (i.e. is already listening)
         *  @since 0.1
         */
        void addListener(EventListener * listener);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Removes the given listener from the list (i.e. it stops listening)
         *  @since 0.1
         */
        EventListener * removeListener(EventListener * listener);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Returns the status of a given EventType or the default 'Idle' if the EventType was never started.
         *  @since 0.1
         */
        EventStatus statusOf(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Returns true iff an event is EVENT_STATUS_IDLE or non-existent
         *  @since 0.1
         */
        bool isIdle(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *
         *  Returns true iff an event is EVENT_STATUS_ACTIVE
         *  @since 0.1
         */
        bool isActive(EventType theEvent) ;
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Use this when you merely wish to notify of an events occurrance and do not have any actions to perform between eventWillStart() and eventDidEnd()
         *  @code
         *  if (check that something happenned) {
         *     NotificationCenter::eventDidOccur("Something Happened", Args);
         *  }
         *  @endcode
         *  @see Calls eventWillStart(EventType theEvent, EventArgs o), @see eventDidEnd(EventType theEvent, EventArgs o)
         *  @since 0.1
         */
        void eventDidOccur(EventType theEvent, EventArgs o = nullptr);
       
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42

         *  Returns true iff an event exists and has the status EVENT_STATUS_COMPLETE.
         *  @see eventDidEnd(EventType theEvent, EventArgs o);
         *  @code
         *  NotificationCenter::eventDidEnd("Something finished happening", EVENT_STATUS_COMPLETE);
         *  @endcode
         *  @since 0.1
         */
        bool isComplete(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42

         *  Returns true iff an event exists and has the status EVENT_STATUS_FAILURE.
         *  @see eventDidEnd(EventType theEvent, EventArgs o);
         *  @code
         *  NotificationCenter::eventDidEnd("Something finished happening", EVENT_STATUS_FAILURE);
         *  @endcode
         *  @since 0.1
         */
        bool didFail(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42

         *  Call this method before performing an event.
         *  @code
         *  NotificationCenter::eventWillStart("Something id happening", Args);
         *  PerformAnEvent();
         *  NotificationCenter::eventDidEnd("Something id happening", Args);
         *  @endcode
         *  @see Calls eventWillStart(EventType theEvent, EventArgs o)
         *  @see eventDidEnd(EventType theEvent, EventArgs o)
         *  @since 0.1
         */
        void eventWillStart(EventType theEvent, EventArgs o = nullptr);

        /*!
         *  @author Max Bilbow, 15-08-04 17:08:17
         *
         *  Call this method once an event has finished.
         *  @code
         *  NotificationCenter::eventWillStart("Something id happening", Args);
         *  PerformAnEvent();
         *  NotificationCenter::eventDidEnd("Something id happening", Args);
         *  @endcode
         *  @see Calls eventWillStart(EventType theEvent, EventArgs o)
         *  @see eventDidEnd(EventType theEvent, EventArgs o)
         *  @param theEvent string
         *  @param o       anything
         *  @since 0.1
         */
        void eventDidEnd(EventType theEvent, EventArgs o = nullptr);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:52
         *
         *  Ideally this should invoke custom methods that are present.
         *  However it is not currently possible to convert strings to method names so the Object::SendMessage(message,args) method will have to be overridden to implement the desired behaviour.
         *  @see EventListener::SendMessage(message,args);
         *  @param message string
         *  @param args    anything
         *  @since 0.1
         */
        void notifyListeners(std::string message, EventArgs args = nullptr);

        
    };
}



#endif /* RMXNotificationCenter_cpp */