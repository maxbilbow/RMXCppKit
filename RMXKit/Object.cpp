//
//  Object.cpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "Object.h"
#include <typeinfo>
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
        return strm << a->toString();
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

unsigned int Object::uniqueID() {
    return this->_id;
}

string Object::toString()  {
    return "Name: " + this->uniqueName() + ", Description: " + mDescription;
}

unsigned int Object::Count() {
    return _count;
//    return Object::_allObjects.count(); //_count - Object::_deleted;
}

std::string Object::ClassName() {
    return typeid(this).name();
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
    auto * o = (Object *) ptr;
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

#ifdef DEBUG_THIS
#undef DEBUG_THIS
#endif