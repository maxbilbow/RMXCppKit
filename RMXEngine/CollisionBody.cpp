//
//  CollisionBody.cpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"


#import "GameNode.hpp"
#import "NodeComponent.hpp"
#import "CollisionBody.hpp"
#import "Transform.hpp"

#import "PhysicsBody.hpp"


#import "BoundingBox.hpp"
#import "BoundingSphere.hpp"


using namespace rmx;
using namespace std;

CollisionBody::CollisionBody(PhysicsBody * body)
{
    NodeComponent::NodeComponent();
    this->collisionGroup = DEFAULT_COLLISION_GROUP;
    this->_physicsBody = body;
    this->_boundingBox = new BoundingBox(body);
    this->_boundingSphere = new BoundingSphere(body);
}

BoundingBox * CollisionBody::boundingBox() {
    return _boundingBox;
}

BoundingSphere * CollisionBody::boundingSphere() {
    return _boundingSphere;
}



int CollisionBody::getCollisionGroup() {
    return this->collisionGroup;
}

void CollisionBody::setCollisionGroup(int collisionGroup) {
    this->collisionGroup = collisionGroup;
}


bool CollisionBody::intersects(CollisionBody * other) {
    return this->boundingBox()->intersects(other->boundingBox());
}

GameNode * CollisionBody::getNode() {
    return this->_physicsBody->getNode();
}


PhysicsBody * CollisionBody::physicsBody() {
    return _physicsBody;
}


int CollisionBody::CollisionGroup() {
    return this->collisionGroup;
}