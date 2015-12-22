//
//  BoundingSphere.cpp
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
#include "BoundingSphere.hpp"


using namespace rmx;


BoundingSphere::BoundingSphere(PhysicsBody * body) {
    this->body = body;
}


GameNode * BoundingSphere::getNode() {
    return this->body->getNode();
}

Transform * BoundingSphere::transform() {
    return this->getNode()->getTransform();
}

float BoundingSphere::radius() {
    return GLKVector3Length(this->body->getNode()->getTransform()->scale());
}

bool BoundingSphere::intersects(BoundingSphere * B) {
    
    float min = this->radius() +
				B->radius();
    Vector3 collisionDistance = this->getNode()->getTransform()->position() = B->getNode()->getTransform()->position();
   
    float distance = GLKVector3Length(collisionDistance);
    
    return distance < min;
}

