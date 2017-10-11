//
//  Object.cpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "Object.h"
#include <cstring>
#include <utility>

#ifdef DEBUG_RMX_OBJECT
#define DEBUG_THIS true
#endif

using namespace std;
using namespace rmx;


std::ostream& operator<<(std::ostream &strm,  rmx::Printable * a) {
    if (a == nullptr)
        return strm << "WARNING: Printable Object is null!";
    else
        return strm << a->ToString();
}

std::ostream& operator<<(std::ostream &strm,  rmx::Printable & a) {
    return strm << typeid(a).name() <<  " @ " << static_cast<void *>(&a) << " >> " << &a;//.ToString();
}

unsigned int Object::_count = 0;

Object::Object(const std::string &name){
    
    this->_id = Object::_count++; //this->IncrementCount();
    this->name = !name.empty() ? name : "Unnamed Object";
//    Object::_allObjects.append(this);
    
#if DEBUG_MALLOC
    std::cout << "~INITIALIZING Object: " << *this << std::endl;
#endif
}

string Object::uniqueName() {
    return this->name + " (" + std::to_string(this->_id) + ")";
}

string Object::Name() {
    return this->name;
}

void Object::setName(std::string name) {
    this->name = std::move(name);
}

unsigned int Object::uniqueID() {
    return this->_id;
}

string Object::ToString()  {
    return "Name: " + this->uniqueName() + ", Description: " + Printable::ToString();
}

unsigned int Object::Count() {
    return _count;
//    return Object::_allObjects.count(); //_count - Object::_deleted;
}

Object::~Object() {
    _count--;
    try {
#if DEBUG_MALLOC
    std::cout << "~DELETING Object: " << *this;
#endif
//    Object::_deleted++;
//    Object::_allObjects.removeValue(this);
#if DEBUG_MALLOC
    std::cout << ", Remainig: " << Object::Count() << std::endl;
#endif
    } catch (exception e) {
        cout << "Deleting Object caused exception: " << e.what() << endl;
    }
}

Object * Object::clone() {
    void * ptr = malloc(sizeof(*this));//&o;
    memcpy(ptr, (void*)this, sizeof(*this));
    Object * o = (Object *) ptr;
    o->_id = _count++;
    if (o->name.find("CLONE of \"") == std::string::npos)
        o->setName("CLONE of \"" + this->name + "\"");// + std::to_string(this->getID()) + ")");
//    Object::_allObjects.append(o);
#if DEBUG_MALLOC
    std::cout << "~INITIALIZING CLONE: " << *o << std::endl;
#endif
    return o;
}

template<class T>
T *Object::Instantiate(T *object) {
    //            if( Object * o = dynamic_cast< Object* >( object ) )
    if (std::is_base_of<Object,T>::value) {
#if DEBUG_MALLOC
        std::cout << "Object::";
#endif
        return (T*) ((Object*) object)->clone();
    } else {
        void * ptr = malloc(sizeof(*object));//&o;
        memcpy(ptr, (void*)object, sizeof(*object));
#if DEBUG_MALLOC
        std::cout << "~UNKNOWN CLONE: " << ptr << std::endl;
#endif
        return (T*) ptr;
    }

}

//void Object::SendMessage(std::string message, Any args, SendMessageOptions options) {
//    Receiver receiver = nullptr; //*this->_receivers->getValueForKey(message);
//    if (receiver != nullptr) {
//        try {
//            receiver(this, args);
//        } catch (std::exception e) {
//            std::cout << "Receiver Error: "<< message << ", for: " << *this << "\n ==> ERROR: " << e.what() << std::endl;
//        }
//    } else if (options == RequiresReceiver)
//        throw std::invalid_argument("Receiver was not available: " + message);
//#if DEBUG_BEHAVIOURS
//    else
//        std::cout << "Receiver was not available: "<< message << ", for: " << *this << std::endl;
//#endif
//}



void Printable::setDescription(std::string description) {
    this->description = std::move(description);
}

std::string Printable::ToString() {
    return this->description.empty() ? "N/A" : this->description;
}

#ifdef DEBUG_THIS
#undef DEBUG_THIS
