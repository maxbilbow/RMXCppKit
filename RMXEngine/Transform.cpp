//
//  Transform.cpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
#import "Includes.h"
#import "GameNode.hpp"
#import "NodeComponent.hpp"
#import "PhysicsBody.hpp"
#import "CollisionBody.hpp"
#import "Transform.hpp"

#import <math.h>


using namespace rmx;
using namespace std;

Transform * Transform::New(GameNode * node) {
    return new Transform(node);
}

Transform::Transform(){
    NodeComponent::NodeComponent();
    throw invalid_argument("Not allowed to use construct without node");
}

Transform::Transform(GameNode * node) {
    NodeComponent::NodeComponent();
    this->node = node;
    _axis = GLKMatrix4Identity;
    _localMatrix = GLKMatrix4Identity;
    _scale = GLKVector3Make(1,1,1);
    _lastPosition = GLKVector3Make(0, 0, 0);
    this->setName("Transform::"+node->Name());
}

Vector3 Transform::scale() {
    return this->_scale;
}

void Transform::setScale(float x, float y, float z) {
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;
}



/**
 * TODO: Test with children
 * @return
 */
float Transform::mass() {
    float mass = this->getNode()->physicsBody() != nullptr ? this->getNode()->physicsBody()->getMass() : 0.0f;
    GameNodeList::Iterator * i = this->getNode()->getChildren()->getIterator();
    while (i->hasNext())
        mass += i->next()->getTransform()->mass();
    return mass;
}


/**
 * TODO check maths
 * @return
 */
Matrix4 Transform::worldMatrix() {
    if (this->parent() != nullptr) {
        Transform * parent = this->parent();
        if (parent->parent() != nullptr) {
            return GLKMatrix4Multiply(parent->worldMatrix(),this->_localMatrix);
        } else {
            return this->_localMatrix;
        }
    } else {
        return this->_localMatrix;
    }
}

Transform * Transform::parent() {
    GameNode * parentNode = this->getNode()->getParent();
    return parentNode != nullptr ? parentNode->getTransform() : nullptr;
}

Vector3 Transform::localPosition() {
    return GLKVector3Make(_localMatrix.m30,
                          _localMatrix.m31,
                          _localMatrix.m32
                          );
}

Vector3 Transform::position() {
    return RMXMatrix4Position(this->worldMatrix());
//    Transform * parent = this->parent();
//    if (parent !=   null && parent->parent() !=   null) {
//        return this->localPosition() + parent->position();
//    }
//    return this->localPosition();
}

void Transform::setM(int i, float value) {
    this->_localMatrix.m[i] = value;
}

void Transform::addM(int i, float value) {
    this->_localMatrix.m[i] += value;
}

void Transform::setPosition(Vector3 position) {
    this->_localMatrix.m30 = position.x;
    this->_localMatrix.m31 = position.y;
    this->_localMatrix.m32 = position.z;
   
//    cout << _localMatrix;
}

void Transform::setPosition(float x, float y, float z) {
    this->_localMatrix.m30 = x;
    this->_localMatrix.m31 = y;
    this->_localMatrix.m32 = z;
}


    
string * readMessage(string message) {
    string * args = new string[message.length() / 3];
    int n = 0, j=0;
    cout<<message<<endl;
    for (int i = 0; i<message.length();++i){
        if (message[i] == ':') {
            n++; j=0;
        } else
            args[n][j++] = message[i];
    }
    return args;
}



bool Transform::move(Move name, float scale, string message) {

   return (this->translate(name, scale)
           || this->rotate(name, scale));
//        cout << "Successfully read message: " << name << ":" << message << endl;

}

//void Transform::translate(float x, float y, float z) {
//    _localMatrix = GLKMatrix4Translate(_localMatrix,x,y,z);
////    _localMatrix.m30 += x;
////    _localMatrix.m31 += y;
////    _localMatrix.m32 += z;
//}

void Transform::translate(Vector3 v) {
//    _localMatrix = GLKMatrix4TranslateWithVector3(_localMatrix, v);
    _localMatrix.m30 += v.x;
    _localMatrix.m31 += v.y;
    _localMatrix.m32 += v.z;
}

bool Transform::translate(Move direction, float scale) {
    Vector3 v;
    switch (direction) {
        case Forward:
            scale *= -1;
            v = this->forward();
            break;
        case Up:
            //			scale *= -1;
            v = this->up();
            break;
        case Left:
//            scale *= -1;
            v = this->left();
            break;
        case X:
            //			scale *= -1;
            v = GLKVector3Make(1,0,0);
            break;
        case Y:
            //			scale *= -1;
            v = GLKVector3Make(0,1,0);
            break;
        case Z:
            //			scale *= -1;
            v = GLKVector3Make(0,0,1);
            break;
        default:
            return false;
    }
//    _localMatrix =
    this->translate(v * scale * 0.4);
//    this->translate(v * scale);
    return true;
}



bool Transform::rotate(Move direction, float scale) {
    Vector3 v;
    switch (direction) {
        case Pitch:
//           scale *= -1;
            v = this->left();
            break;
        case Yaw:
            scale *= -1;
            v = this->up();
            break;
        case Roll:
//            scale *= -1;
            v = this->forward();
            break;
        default:
            return false;
    }
    this->rotate(scale * PI_OVER_180,v);
    return true;
}



void Transform::rotate(float radians, float x, float y, float z) {
    _localMatrix = GLKMatrix4Rotate(_localMatrix, radians, x,y,z);
}
void Transform::rotate(float radians, Vector3 v) {
    
//    Vector3 p = RMXMatrix4Position(_localMatrix);
//    _localMatrix.m30 = _localMatrix.m31 = _localMatrix.m32 = 0;
    _localMatrix = GLKMatrix4RotateWithVector3(_localMatrix, radians, v);
    
//    RMXMatrix4SetPosition(_localMatrix, p);
}


void Transform::translate(Vector4 v) {
    _localMatrix = GLKMatrix4TranslateWithVector4(_localMatrix, v);
}


Vector3 Transform::left() {
    Matrix4 m = this->localMatrix();
    return GLKVector3Make(m.m00,
                          m.m01,
                          m.m02
                          );
}

Vector3 Transform::up() {
    Matrix4 m = this->localMatrix();
    return GLKVector3Make(m.m10,
                          m.m11,
                          m.m12
                          );
}

Vector3 Transform::forward() {
    Matrix4 m = this->localMatrix();
    return GLKVector3Make(m.m20,
                          m.m21,
                          m.m22
                          );
}




Vector3 Transform::localEulerAngles() {
    return RMXMatrix3MakeEuler(this->_localMatrix);
}

Quaternion Transform::rotation() {
    return GLKQuaternionMakeWithMatrix4(this->worldMatrix());
}

Quaternion Transform::localRotation() {
    return GLKQuaternionMakeWithMatrix4(_localMatrix);
}

Vector3 Transform::eulerAngles() {
//    Transform * parent = this->parent();
    return RMXMatrix3MakeEuler(this->worldMatrix());//parent != null ? localEulerAngles() + parent->eulerAngles() : this->localEulerAngles();
}



Matrix4 Transform::localMatrix() {
    return _localMatrix;
}



GameNode * Transform::setNode(GameNode * node) {
//    if (this->getNode() != null)// && this->getNode() != node)
        throw new invalid_argument("Transform can only be assigned once: " + this->Object::ToString());
//    node->setTransform(this);
//    return   null;
}

float Transform::getWidth() {
    return scale().x * 2;
}

float Transform::radius() {
    return (_scale.x + _scale.y + _scale.z) / 3;
}

float Transform::getHeight() {
    // TODO Auto-generated method stub
    return scale().y * 2;
}

float Transform::getLength() {
    // TODO Auto-generated method stub
    return scale().z * 2;
}

void Transform::updateLastPosition() {
    _lastPosition = this->localPosition(); //this->position();
}

Vector3 Transform::lastPosition() {
    return _lastPosition;
}


Transform * Transform::rootTransform() {
    Transform * parent = this->parent();
    if (parent != nullptr && parent->parent() != nullptr) {
        return this->parent()->rootTransform();
    } else {
        return this;
    }
}

void Transform::stepBack(string s) {
    for (int i=0;i<s.length();++i)
        switch (s[i]) {
            case 'x':
                _localMatrix.m30 = _lastPosition.x;
                break;
            case 'y':
                _localMatrix.m31 = _lastPosition.y;
                break;
            case 'z':
                _localMatrix.m32 = _lastPosition.z;
                break;
            default:
                break;
        }
//    this->setPosition(_lastPosition);
}


PhysicsBody * Transform::physicsBody() {
    return this->getNode()->physicsBody();
}

CollisionBody * Transform::collisionBody() {
    return this->physicsBody()->collisionBody();
}
