//
//  RMXNotificationCenter.hpp
//  RMXKit
//
//  Created by Max Bilbow on 28/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef RMXNotificationCenter_cpp
#define RMXNotificationCenter_cpp

//#include <stdio.h>
//#import <list>
//#import <vector>



#endif /* RMXNotificationCenter_cpp */

#define EVENT_STATUS_IDLE       0ui
#define EVENT_STATUS_ACTIVE     1ui
#define EVENT_STATUS_COMPLETE   2ui
#define EVENT_STATUS_FAILURE    3ui


#import "LinkedList.h"
#import "Dictionary.h"
#import "EventListener.h"



namespace rmx {
    
    /*!
     *   @author Max Bilbow, 15-08-04 16:08:21
     *
     *   @brief  static class for handling global notifications throughout a system.
     *
     *   @since <#0.1#>
     */
    class NotificationCenter {
    public:
        typedef void * EventArgs;
        typedef std::string EventType;
        typedef unsigned short EventStatus;
    private:
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  List of all active EventListeners, assuming they were added to the list.
         *  @see EventListener::EventListener(std::string name, bool add);
         *  @since 0.1
         */
        static LinkedList<EventListener> * listeners;
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Dictionaty containing all events, that have been activated at least once, and their statuses.
         *  @since 0.1
         */
        static Dictionary<EventType, EventStatus> * events;

    public:
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Returns true if the listener exists withing listeners
         *  i.e. The given listener is listening.
         *  @since 0.1
         */
        static bool hasListener(EventListener * listener);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  If the given EventType exists and is not Idle, the event's status is set to EVENT_STATUS_IDLE.
         *  @since 0.1
         */
        static void reset(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Adds the given listerner to listenrers iff it does not already exist (i.e. is already listening)
         *  @since 0.1
         */
        static void addListener(EventListener * listener);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Removes the given listener from the list (i.e. it stops listening)
         *  @since 0.1
         */
        static EventListener * removeListener(EventListener * listener);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Returns the status of a given EventType or the default 'Idle' if the EventType was never started.
         *  @since 0.1
         */
        static EventStatus statusOf(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *  Returns true iff an event is EVENT_STATUS_IDLE or non-existent
         *  @since 0.1
         */
        static bool isIdle(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42
         *
         *  Returns true iff an event is EVENT_STATUS_ACTIVE
         *  @since 0.1
         */
        static bool isActive(EventType theEvent) ;
        
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
        static void eventDidOccur(EventType theEvent, EventArgs o = nullptr);
       
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42

         *  Returns true iff an event exists and has the status EVENT_STATUS_COMPLETE.
         *  @see eventDidEnd(EventType theEvent, EventArgs o);
         *  @code
         *  NotificationCenter::eventDidEnd("Something finished happening", EVENT_STATUS_COMPLETE);
         *  @endcode
         *  @since 0.1
         */
        static bool isComplete(EventType theEvent);
        
        /*!
         *  @author Max Bilbow, 15-08-04 17:08:42

         *  Returns true iff an event exists and has the status EVENT_STATUS_FAILURE.
         *  @see eventDidEnd(EventType theEvent, EventArgs o);
         *  @code
         *  NotificationCenter::eventDidEnd("Something finished happening", EVENT_STATUS_FAILURE);
         *  @endcode
         *  @since 0.1
         */
        static bool didFail(EventType theEvent);
        
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
        static void eventWillStart(EventType theEvent, EventArgs o = nullptr);

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
        static void eventDidEnd(EventType theEvent, EventArgs o = nullptr);
        
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
        static void notifyListeners(std::string message, EventArgs args = nullptr);

        
    };
}

