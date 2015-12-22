//
//  PhysicsBody.cpp
//  RMXKit
//
//  Created by Max Bilbow on 20/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
//#import "RMXEngine.hpp"
//#import "PhysicsBody.hpp"


#import "Includes.h"


//
#import "NodeComponent.hpp"

#import "Transform.hpp"
#import "BoundingBox.hpp"
#import "BoundingSphere.hpp"
#import "CollisionBody.hpp"
#import "PhysicsBody.hpp"
#import "GameNode.hpp"


using namespace rmx;
using namespace std;

PhysicsBodyType PhysicsBody::type() {
    return _type;
}
void PhysicsBody::setType(PhysicsBodyType type) {
    this->_type = type;
}

PhysicsBody::PhysicsBody() {
    NodeComponent::NodeComponent();
    this->mass = 1;
    this->setName("PhysicsBody");
    this->forces = GLKVector3Make(0,0,0);
    this->velocity = GLKVector3Make(0,0,0);
    this->rotationalVelocity = GLKVector3Make(0,0,0);
    this->torque = GLKVector3Make(0,0,0);
    this->_type = Dynamic;
}


GameNode * PhysicsBody::setNode(GameNode * node) {
    this->_collisionBody = new CollisionBody(this);
    switch (this->type()) {
        case Dynamic:
            _collisionBody = new CollisionBody(this);
            _collisionBody->setCollisionGroup(DEFAULT_COLLISION_GROUP);
            break;
        case Static:
            _collisionBody = new CollisionBody(this);
            _collisionBody->setCollisionGroup(DEFAULT_COLLISION_GROUP);
            break;
        case Kinematic:
            _collisionBody = new CollisionBody(this);
            _collisionBody->setCollisionGroup(EXCLUSIVE_COLLISION_GROUP);
            break;
        case Transient:
            _collisionBody = new CollisionBody(this);
            _collisionBody->setCollisionGroup(NO_COLLISIONS);
            break;
    }
    return NodeComponent::setNode(node);
}

PhysicsBody * PhysicsBody::newStaticBody() {
    PhysicsBody * body = new PhysicsBody();
    body->_type = Static;
    return body;
}

PhysicsBody * PhysicsBody::newDynamicBody() {
    PhysicsBody * body = new PhysicsBody();
    body->_type = Dynamic;
    
    return body;
}

PhysicsBody * PhysicsBody::newKinematicBody() {
    PhysicsBody * body = new PhysicsBody();
    body->_type = Kinematic;
    
    return body;
}

PhysicsBody * PhysicsBody::newTransientBody() {
    PhysicsBody * body = new PhysicsBody();
    body->_type = Transient;    
    return body;
}

void PhysicsBody::setMass(float mass) {
    this->mass = mass;
}
float PhysicsBody::getMass() {
    return this->mass;
}

float PhysicsBody::TotalMass() {
    return this->getNode()->getTransform()->mass();
}

void PhysicsBody::setFriction(float friction) {
    this->friction = friction;
}

void PhysicsBody::setRollingFriction(float rollingFriction) {
    this->rollingFriction = rollingFriction;
}

void PhysicsBody::setDamping(float damping) {
    this->damping = damping;
}

void PhysicsBody::setRotationalDamping(float rotationalDamping) {
    this->rotationalDamping = rotationalDamping;
}


CollisionBody * PhysicsBody::collisionBody() {
    return this->_collisionBody;
}


void PhysicsBody::applyForce(RMXMessage direction, float force)
{
    switch (direction) {
        case Forward:
            this->applyForce(force, this->getNode()->getTransform()->forward());
            break;
        case Up:
            this->applyForce(force, this->getNode()->getTransform()->up());
            break;
        case Left:
            this->applyForce(force, this->getNode()->getTransform()->left());
            break;
        default:
            break;
    }
}

void PhysicsBody::applyTorque(RMXMessage direction, float force)
{
    switch (direction) {
        case Pitch:
            this->applyTorque(force, this->getNode()->getTransform()->left());
            break;
        case Yaw:
            this->applyTorque(force, this->getNode()->getTransform()->up());
            break;
        case Roll:
            this->applyTorque(force, this->getNode()->getTransform()->forward());
            break;
        default:
            break;
    }
}

void PhysicsBody::applyForce(float force, Vector3 direction, Vector3 atPoint) {
    if (_type != Dynamic)
        return;
    force /= (1 + this->damping);
    this->forces.x += direction.x * force;
    this->forces.y += direction.y * force;
    this->forces.z += direction.z * force;
//    cout << this->forces << endl;
}

void PhysicsBody::applyTorque(float force, Vector3 axis, Vector3 atPoint) {
    if (_type != Dynamic)
        return;
    force /= (1 + this->rotationalDamping);
    this->torque.x += axis.x * force;
    this->torque.y += axis.y * force;
    this->torque.z += axis.z * force;
}

Vector3 PhysicsBody::getVelocity() {
    return this->velocity;
}

void PhysicsBody::updatePhysics(PhysicsWorld * physics){
    if (_type != Dynamic)
        return;
    GameNode * node = this->getNode();
    
    
    float mass = this->TotalMass();
    //Update velocity with forces
    this->velocity.x += this->forces.x / mass;
    this->velocity.y += this->forces.y / mass;
    this->velocity.z += this->forces.z / mass;
    this->forces.x = this->forces.y = this->forces.z = 0;
    
    //Updaye rotational velocity with torque
    this->rotationalVelocity.x += this->torque.x / mass;
    this->rotationalVelocity.y += this->torque.y / mass;
    this->rotationalVelocity.z += this->torque.z / mass;
    this->torque.x = this->torque.y = this->torque.z = 0;
    
    
    
    //apply velocities to translation
    node->getTransform()->translate(this->velocity);
    node->getTransform()->rotate(this->rotationalVelocity.x, 1, 0, 0);
    node->getTransform()->rotate(this->rotationalVelocity.y, 0, 1, 0);
    node->getTransform()->rotate(this->rotationalVelocity.z, 0, 0, 1);
    
    //lose energy
    this->velocity *= (1 / (1 + this->friction));
    this->rotationalVelocity *= (1 / (1 + this->rollingFriction));
    
}


float PhysicsBody::getRestitution() {
    return this->restitution;
}

void PhysicsBody::setRestitution(float restitution) {
    if (restitution > 1)
        this->restitution = 1;
    else if (restitution < 0)
        this->restitution = 0;
    else
        this->restitution = restitution;
}

void PhysicsBody::setEffectedByGravity(bool effectedByGravity) {
    this->effectedByGravity = effectedByGravity;
}

bool PhysicsBody::isEffectedByGravity() {
    return this->effectedByGravity;
}


