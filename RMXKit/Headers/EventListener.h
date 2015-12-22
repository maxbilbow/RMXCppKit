//
//  Interfaces.h
//  RMXKit
//
//  Created by Max Bilbow on 28/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef EventListener_h
#define EventListener_h


#endif /* EventListener */
#import <iostream>
#import "Object.h"

namespace rmx {
    /*!
     * 
     *   @author Max Bilbow, 15-08-04 16:08:32
     *
     *   @brief  abstract class for EventListeners
     *   @see NotificationCenter
     *   @since 0.1
     */
    class EventListener : public Object {
        ///Private initilization adds this object to NotificationCenter::listeners iff add == true;
        ///@see NotificationCenter::listeners
        void init(bool add = true);
    public:
        typedef std::string AnEvent;
        typedef void * EventArgs;
        
        /*!
         *  @author Max Bilbow, 15-08-04 16:08:01
         *
         *  Initializes and adds the object to the list of active event listeners.
         *  @param name (default: "") inherited from rmx::Object
         *  @param add (default: true) whether to add this listener on initialization
         *  @see Object
         *  @since <#0.1#>
         */
        EventListener(std::string name = "", bool add = true):Object(name) {
            this->init(add);
        }

        ~EventListener();
        
        /*!
         *  @author Max Bilbow, 15-08-04 16:08:30
         *
         *  Notify's all active listeners that an event is about to start
         *  @param theEvent as string
         *  @param args     anything
         *  @since 0.1
         */
        virtual void OnEventDidStart(AnEvent theEvent, EventArgs args) {
            #ifdef DEBUG
            std::cout << this << "\n       Event Started: " << theEvent << ", with args: " << args << std::endl << std::endl;
            #endif
        }
        
        /*!
         *  @author Max Bilbow, 15-08-04 16:08:53
         *
         *  Notify's all active listeners that an event did start
         *  @param theEvent string identifier
         *  @param args     anything
         *  @since 0.1
         */
        virtual void OnEventDidEnd(AnEvent theEvent, EventArgs args) {
            #ifdef DEBUG
            std::cout << this << "\n         Event Ended: " << theEvent << ", with args: " << args << std::endl << std::endl;
            #endif
        }

        
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
        virtual void SendMessage(AnEvent message, EventArgs args = nullptr){
            #ifdef DEBUG
            std::cout << this << "\n    Message Received: " << message << std::endl << std::endl;
            #endif
        }

        /*!
         *   @author Max Bilbow, 15-08-04 16:08:22
         *
         *   @brief  Inserts the object into Notification::listeners, if it isn't already inserted.
         *
         *   @see NotificationCenter::addListener(listener)
         *   @since 0.1
         */
        void StartListening();
        
        /*!
         *   @author Max Bilbow, 15-08-04 16:08:22
         *
         *   @brief  Removes the object from Notification::listeners, if it exists in the list.
         *   @see NotificationCenter::removeListener(listener)
         *   @since <#0.1#>
         */
        void StopListening();

        
        ///Extends the Object::clone() method so that the listening status of the object is also copied.
        ///@see NotificationCenter::addListener(listener);
        EventListener * clone() override;

    };

}




