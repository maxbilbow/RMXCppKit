//
//  Tests.h
//  RMXKit
//
//  Created by Max Bilbow on 04/08/2015.
//  Copyright © 2015 Max Bilbow. All rights reserved.
//

#ifndef Tests_h
#define Tests_h


#endif /* Tests_h */

#define DEBUG_ALL                           0
#define DEBUG_MALLOC                        DEBUG_ALL || 0
#define DEBUG_INCLUDE_TEST_OUTPUT           DEBUG_ALL || 0

#define DEBUG_RMX_PRINTABLE                 DEBUG_ALL || 0
///Successfully tests the cout << operator.
void RMXPrintableTest();


#define DEBUG_RMX_OBJECT                    DEBUG_ALL || 0
///Successfully tests the clone and instantiate methods.
void RMXObjectCloneTest();
#define D_ObjectCountInitAndDeinitTest      DEBUG_ALL || 0
void RMXObjectCountInitAndDeinitTest();

#define DEBUG_RMX_DICTIONARY                DEBUG_ALL || 0
void RMXDictionaryTest();

#define DEBUG_RMX_LINKED_LIST               DEBUG_ALL || 0
void RMXLinkedListTest(void);

#define DEBUG_RMX_BEHAVIOURS                DEBUG_ALL || 0
void RMXBehaviourTest();

#define DEBUG_RMX_NOTIFICATION_CENTER       DEBUG_ALL || 0

#define DEBUG_RMX_EVENT_LISTENER            DEBUG_ALL || 0
///Successfull test of
/// • Object::clone()
/// • Object::Instantiate(Object inheritance)
/// • Event Listening with cloned objects
void RMXEventListenerTest();