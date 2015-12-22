//
//  BoundingBox.cpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//


#import "Includes.h"


//
#import "NodeComponent.hpp"

#import "Transform.hpp"
#import "CollisionBody.hpp"
#import "PhysicsBody.hpp"
#import "GameNode.hpp"
#include "BoundingBox.hpp"


using namespace rmx;

BoundingBox::BoundingBox(PhysicsBody * body) {
//    NodeComponent::NodeComponent();
    this->body = body;
}

GameNode * BoundingBox::getNode() {
    return this->body->getNode();
}

Transform * BoundingBox::transform() {
    return this->getNode()->getTransform();
}

float BoundingBox::xMin() {
    return - this->transform()->getWidth() / 2;
}
float BoundingBox::yMin() {
    return - this->transform()->getHeight() / 2;
}
float BoundingBox::zMin() {
    return - this->transform()->getLength() / 2;
}
float BoundingBox::xMax() {
    return + this->transform()->getWidth() / 2;
}
float BoundingBox::yMax() {
    return + this->transform()->getHeight() / 2;
}
float BoundingBox::zMax() {
    return + this->transform()->getLength() / 2;
}

bool BoundingBox::intersects(BoundingBox * other) {
    Vector3 a = this->transform()->position();
    Vector3 b = other->transform()->position();
    
    if (this->xMin() + a.x > other->xMax() + b.x)
        return false;
    if (this->yMin() + a.y > other->yMax() + b.y)
        return false;
    if (this->zMin() + a.z > other->zMax() + b.z)
        return false;
    if (this->xMax() + a.x < other->xMin() + b.x)
        return false;
    if (this->yMax() + a.y < other->yMin() + b.y)
        return false;
    if (this->zMax() + a.z < other->zMin() + b.z)
        return false;
    
    return true;
}

Vector3 BoundingBox::getCollisionNormal(BoundingBox * other) {
    Vector3 a = this->transform()->position();
    Vector3 b = other->transform()->position();
    Vector3 normal = GLKVector3Make(0,0,0);
    
    float xMinA = this->xMin() + a.x;
    float xMaxA = this->xMax() + a.x;
    float yMinA = this->yMin() + a.y;
    float yMaxA = this->yMax() + a.y;
    float zMinA = this->zMin() + a.z;
    float zMaxA = this->zMax() + a.z;
    
    float xMinB = other->xMin() + b.x;
    float xMaxB = other->xMax() + b.x;
    float yMinB = other->yMin() + b.y;
    float yMaxB = other->yMax() + b.y;
    float zMinB = other->zMin() + b.z;
    float zMaxB = other->zMax() + b.z;
    
    //find the x value
    //		if (xMinA < xMaxB && xMinA > xMinB)
    
    
    return normal;
}


