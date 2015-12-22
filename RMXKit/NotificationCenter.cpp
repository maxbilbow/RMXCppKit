//
//  RMXNotificationCenter.cpp
//  RMXKit
//
//  Created by Max Bilbow on 28/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//


#import <iostream>
//#import "EventListener.h"
//#import "LinkedList.h"
//#import "Dictionary.h"
#import "Tests.h"
#import "NotificationCenter.h"
#define DEBUG_THIS (DEBUG_INCLUDE_TEST_OUTPUT || DEBUG_RMX_NOTIFICATION_CENTER)

using namespace rmx;

typedef NotificationCenter::EventArgs EventArgs;
typedef NotificationCenter::EventType EventType;
typedef NotificationCenter::EventStatus EventStatus;


using namespace std;


LinkedList<EventListener> * NotificationCenter::listeners = new LinkedList<EventListener>();
Dictionary<EventType, EventStatus> * NotificationCenter::events = new Dictionary<EventType, EventStatus>();


//static bool _init;
//static NotificationCenter * _current;

//NotificationCenter * NotificationCenter::current() {
//    if (!_init) {
//        _current = new NotificationCenter();
//        _init = true;
//    }
//    return _current;
//}


bool NotificationCenter::hasListener(EventListener * listener) {
     return NotificationCenter::listeners->contains(listener);// Listeners.Contains (listener);
}

void NotificationCenter::reset(EventType theEvent) {
//    theEvent->status = Idle;
    NotificationCenter::events->setValueForKey(theEvent, EVENT_STATUS_IDLE);
}
    
void NotificationCenter::addListener(EventListener * listener) {
    if (!NotificationCenter::listeners->contains (listener)) {
        NotificationCenter::listeners->append(listener);
//        cout << "\nAdded to Listeners: " << *listener << endl;
    } else {
        cout << "\n !! Not Adding => Listeners already contain: " << listener << endl;
    }
}

EventListener * NotificationCenter::removeListener(EventListener * listener) {
    return NotificationCenter::listeners->removeValue(listener);
}

EventStatus NotificationCenter::statusOf(EventType theEvent) {
    try {
        return *NotificationCenter::events->getValueForKey(theEvent);
    } catch (exception e) {
        cout << typeid(NotificationCenter).name() << ": " << e.what() << ": setting new event as Idle" << endl;
        NotificationCenter::events->setValueForKey(theEvent, EVENT_STATUS_IDLE);
        return EVENT_STATUS_IDLE;
    }
}

bool NotificationCenter::isIdle(EventType theEvent) {
    return statusOf(theEvent) == EVENT_STATUS_IDLE;
}

 bool NotificationCenter::isActive(EventType theEvent) {
    return statusOf(theEvent) == EVENT_STATUS_ACTIVE;
}


void NotificationCenter::eventDidOccur(EventType theEvent, EventArgs o) {
    eventWillStart(theEvent,o);
    eventDidEnd(theEvent,o);
}


bool NotificationCenter::isComplete(EventType theEvent) {
    return statusOf(theEvent) == EVENT_STATUS_COMPLETE;
}

bool NotificationCenter::didFail(EventType theEvent) {
    return statusOf(theEvent) == EVENT_STATUS_FAILURE;
}


void NotificationCenter::eventWillStart(EventType theEvent, EventArgs o) {
    LinkedList<EventListener>::Node * node = NotificationCenter::listeners->firstNode();
    if (node->value == nullptr)
        return;
    else {
        while (node != nullptr) {
            node->value->OnEventDidStart(theEvent,o);
            node = node->next;
        }
    }
}

void NotificationCenter::eventDidEnd(EventType theEvent, EventArgs o) {
    LinkedList<EventListener>::Node * node = NotificationCenter::listeners->firstNode();
    if (node->value == nullptr)
        return;
    else {
        while (node != nullptr) {
            node->value->OnEventDidEnd(theEvent, o);
            node = node->next;
        }
    }
}

 void NotificationCenter::notifyListeners(string message, EventArgs args) {
     LinkedList<EventListener>::Node * node = NotificationCenter::listeners->firstNode();
     if (node->value == nullptr)
         return;
     else {
         while (node != nullptr) {
             node->value->SendMessage(message, args);
             node = node->next;
         }
     }
}


/*
///	Awake is called when the script instance is being loaded.
void NotificationCenter::Awake() {
    
}

///	This function is called every fixed framerate frame, if the MonoBehaviour is enabled.
void NotificationCenter::FixedUpdate() {
    
}

/// LateUpdate is called every frame, if the Behaviour is enabled.
void NotificationCenter::LateUpdate() {
    
}
/// Callback for setting up animation IK (inverse kinematics).
void NotificationCenter::OnAnimatorIK() {
    
}
///	Callback for processing animation movements for modifying root motion.
void NotificationCenter::OnAnimatorMove() {
    
}
///	Sent to all game objects when the player gets or loses focus.
void NotificationCenter::OnApplicationFocus() {
    
}
/// Sent to all game objects when the player pauses.
void NotificationCenter::OnApplicationPause() {
    
}
/// Sent to all game objects before the application is quit.
void NotificationCenter::OnApplicationQuit() {
    
}
///	If OnAudioFilterRead is implemented, Unity will insert a custom filter into the audio DSP chain.
void NotificationCenter::OnAudioFilterRead() {
    
}
///	OnBecameInvisible is called when the renderer is no longer visible by any camera.
void NotificationCenter::OnBecameInvisible() {}
/// OnBecameVisible is called when the renderer became visible by any camera.
void NotificationCenter::OnBecameVisible() {}
/// OnCollisionEnter is called when this collider/rigidbody has begun touching another rigidbody/collider.
void NotificationCenter::OnCollisionEnter() {}
/// Sent when an incoming collider makes contact with this object's collider (2D physics only).
void NotificationCenter::OnCollisionEnter2D() {}
///	OnCollisionExit is called when this collider/rigidbody has stopped touching another rigidbody/collider.
void NotificationCenter::OnCollisionExit() {}
/// Sent when a collider on another object stops touching this object's collider (2D physics only).
void NotificationCenter::OnCollisionExit2D() {}
/// OnCollisionStay is called once per frame for every collider/rigidbody that is touching rigidbody/collider.
void NotificationCenter::OnCollisionStay() {}
///	Sent each frame where a collider on another object is touching this object's collider (2D physics only).
void NotificationCenter::OnCollisionStay2D() {}
/// Called on the client when you have successfully connected to a server.
void NotificationCenter::OnConnectedToServer() {}
/// OnControllerColliderHit is called when the controller hits a collider while performing a Move.
void NotificationCenter::OnControllerColliderHit() {}
///	This function is called when the MonoBehaviour will be destroyed.
void NotificationCenter::OnDestroy() {}
/// This function is called when the behaviour becomes disabled () or inactive.
void NotificationCenter::OnDisable() {}
/// Called on the client when the connection was lost or you disconnected from the server.
void NotificationCenter::OnDisconnectedFromServer() {}
/// Implement OnDrawGizmos if you want to draw gizmos that are also pickable and always drawn.
void NotificationCenter::OnDrawGizmos() {}
/// Implement this OnDrawGizmosSelected if you want to draw gizmos only if the object is selected.
void NotificationCenter::OnDrawGizmosSelected() {}
/// This function is called when the object becomes enabled and active.
void NotificationCenter::OnEnable() {}
/// Called on the client when a connection attempt fails for some reason.
void NotificationCenter::OnFailedToConnect() {}
/// Called on clients or servers when there is a problem connecting to the MasterServer.
void NotificationCenter::OnFailedToConnectToMasterServer() {}
/// OnGUI is called for rendering and handling GUI events.
void NotificationCenter::OnGUI() {}
/// Called when a joint attached to the same game object broke.
void NotificationCenter::OnJointBreak() {}
///	This function is called after a new level was loaded.
void NotificationCenter::OnLevelWasLoaded() {}
/// Called on clients or servers when reporting events from the MasterServer.
void NotificationCenter::OnMasterServerEvent() {}
///	OnMouseDown is called when the user has pressed the mouse button while over the GUIElement or Collider.
void NotificationCenter::OnMouseDown() {}
/// OnMouseDrag is called when the user has clicked on a GUIElement or Collider and is still holding down the mouse.
void NotificationCenter::OnMouseDrag() {}
/// Called when the mouse enters the GUIElement or Collider.
void NotificationCenter::OnMouseEnter() {}
/// Called when the mouse is not any longer over the GUIElement or Collider.
void NotificationCenter::OnMouseExit() {}
/// Called every frame while the mouse is over the GUIElement or Collider.
void NotificationCenter::OnMouseOver() {}
/// OnMouseUp is called when the user has released the mouse button.
void NotificationCenter::OnMouseUp() {}
/// OnMouseUpAsButton is only called when the mouse is released over the same GUIElement or Collider as it was pressed.
void NotificationCenter::OnMouseUpAsButton() {}
/// Called on objects which have been network instantiated with Network.Instantiate.
void NotificationCenter::OnNetworkInstantiate() {}
/// OnParticleCollision is called when a particle hits a collider.
void NotificationCenter::OnParticleCollision() {}
/// Called on the server whenever a new player has successfully connected.
void NotificationCenter::OnPlayerConnected() {}
/// Called on the server whenever a player disconnected from the server.
void NotificationCenter::OnPlayerDisconnected() {}
/// OnPostRender is called after a camera finished rendering the scene.
void NotificationCenter::OnPostRender() {}
/// OnPreCull is called before a camera culls the scene.
void NotificationCenter::OnPreCull() {}
/// OnPreRender is called before a camera starts rendering the scene.
void NotificationCenter::OnPreRender() {}
/// OnRenderImage is called after all rendering is complete to render image.
void NotificationCenter::OnRenderImage() {}
/// OnRenderObject is called after camera has rendered the scene.
void NotificationCenter::OnRenderObject() {}
/// Used to customize synchronization of variables in a script watched by a network view.
void NotificationCenter::OnSerializeNetworkView() {}
/// Called on the server whenever a Network.InitializeServer was invoked and has completed.
void NotificationCenter::OnServerInitialized() {}
/// This function is called when the list of children of the transform of the GameObject has changed.
void NotificationCenter::OnTransformChildrenChanged() {}
/// This function is called when the parent property of the transform of the GameObject has changed.
void NotificationCenter::OnTransformParentChanged() {}
/// OnTriggerEnter is called when the Collider other enters the trigger.
void NotificationCenter::OnTriggerEnter() {}
/// Sent when another object enters a trigger collider attached to this object (2D physics only).
void NotificationCenter::OnTriggerEnter2D() {}
/// OnTriggerExit is called when the Collider other has stopped touching the trigger.
void NotificationCenter::OnTriggerExit() {}
/// Sent when another object leaves a trigger collider attached to this object (2D physics only).
void NotificationCenter::OnTriggerExit2D() {}
/// OnTriggerStay is called once per frame for every Collider other that is touching the trigger.
void NotificationCenter::OnTriggerStay() {}
/// Sent each frame where another object is within a trigger collider attached to this object (2D physics only).
void NotificationCenter::OnTriggerStay2D() {}
/// This function is called when the script is loaded or a value is changed in the inspector (Called in the editor only).
void NotificationCenter::OnValidate() {}
/// OnWillRenderObject is called once for each camera if the object is visible.
void NotificationCenter::OnWillRenderObject() {}
/// Reset to default values.
void NotificationCenter::Reset() {}
/// Start is called on the frame when a script is enabled just before any of the Update methods is called the first time.
void NotificationCenter::Start() {}
/// Update is called every frame, if the MonoBehaviour is enabled.
void NotificationCenter::Update() {}


*/



