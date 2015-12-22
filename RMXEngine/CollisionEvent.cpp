//
//  CollisionEvent.cpp
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
#import "BoundingBox.hpp"
#import "BoundingSphere.hpp"
#import "GameNode.hpp"
#include "CollisionEvent.hpp"


using namespace rmx;
using namespace std;


CollisionEvent::CollisionEvent(GameNode * nodeA, GameNode * nodeB, unsigned int key) {
    this->key = key;
 
    this->nodeA = nodeA;
    this->nodeB = nodeB;
    this->hitPointA = Vector3Zero;
    this->hitPointB = Vector3Zero;
    this->planeDistance = this->getPlaneDistance();
    
    this->AtoB = GLKVector3Subtract(
                                    nodeA->getTransform()->position(),
                                    nodeB->getTransform()->position()
                                    );
    startingDistance = GLKVector3Distance(
                                          nodeA->getTransform()->position(),
                                          nodeB->getTransform()->position()
                                          ); // A.localPosition().getDistanceTo(B.localPosition());
   
    nodeA->BroadcastMessage(ON_COLLISION_START,this);
    nodeB->BroadcastMessage(ON_COLLISION_START,this);
}

void CollisionEvent::seperateBodies(Transform * A, Transform * B) {
    
    //apply force relative to overlapping areas
    float min;
    float dist = this->startingDistance;

    min = nodeA->collisionBody()->boundingSphere()->radius() + nodeB->collisionBody()->boundingSphere()->radius();
  
    
    const float delta = min - dist / 2;

    
    AtoB = GLKVector3Normalize(AtoB) * -delta;
//    AtoB.scale(-delta);
//    if (AtoB.isZero()) {
//        AtoB.set(-min,0,0);
//    }
    
    float diff = this->planeDistance;
    if (A->getNode()->tick() > 0) {
        if (A->physicsBody()->type() == Dynamic && A->physicsBody()->getVelocity() != Vector3Zero)
            A->rootTransform()->stepBack(axis);// -diff * sign);
        else if (B->physicsBody()->type() == Dynamic && B->physicsBody()->getVelocity() != Vector3Zero)
            B->rootTransform()->stepBack(axis);//diff * sign);
    }
    
    if (A->collisionBody()->boundingBox()->intersects(B->collisionBody()->boundingBox()) ) {
    
        float time = 0.017;// * 9.8f;//RMX.getCurrentFramerate();
        float escapeForce = time;// * AtoB.length();
        Vector3 dir = //AtoB.getNormalized();
        GLKVector3Make(axis == "x" ? 1 : 0, axis == "y" ? 1 : 0, axis == "z" ? 1 : 0);
        
								A->physicsBody()->applyForce(escapeForce * (A->mass() + diff), dir, hitPointA);//.translate(AtoB);
        
								B->physicsBody()->applyForce(-escapeForce * (B->mass() + diff), dir, hitPointB);//translate(AtoB);
        
        
    }
}



void CollisionEvent::processMomentum(Transform * A, Transform * B)  {
    
//    _log += "\n\nCollision Momentum Report: " + nodeA.uniqueName() + " vs. " + nodeB.uniqueName();
    
    Vector3 Va = A->physicsBody()->getVelocity();
    Vector3 Vb = B->physicsBody()->getVelocity();
    Vector3 direction = Va - Vb;
    if (isZero(direction))
        return;
    else
        GLKVector3Normalize(direction);
    
    float m1 = A->mass();
    float m2 = B->mass();
   
    
    
    float lossA = 1 - A->physicsBody()->getRestitution();
    float lossB = 1 - B->physicsBody()->getRestitution();
    float v1 = GLKVector3Length(Va);
    float v2 = GLKVector3Length(Vb);
    
    float mass = m1 + m2 + 0.01f;
    float diffMass = m1 - m2;
    float forceOnA = -m2;// (diffMass * v1 + 2 * m2 * v2 ) / mass;
    
    float forceOnB = m1;//(2 * m1 * v1 - diffMass * v2 ) / mass;
    
    //Transfer of forces
    
    A->physicsBody()->applyForce( forceOnA * lossA , direction, hitPointA);
    B->physicsBody()->applyForce( forceOnB * lossB , direction, hitPointB);
    
    
}

void CollisionEvent::processCollision(unsigned int key) {
    if (key != this->key)
        throw invalid_argument("CollisionEvent::processCollision(int key) cannot be called outside of the PhysicsWorld class");
    if(this->prevented)
        return;
    
    this->seperateBodies(nodeA->getTransform(), nodeB->getTransform());
    this->processMomentum(nodeA->getTransform(), nodeB->getTransform());
    
    nodeA->BroadcastMessage(ON_COLLISION_END,this);
    nodeB->BroadcastMessage(ON_COLLISION_END,this);
}


float CollisionEvent::getPlaneDistance() {
    BoundingBox * boxA = nodeA->collisionBody()->boundingBox(); BoundingBox * boxB = nodeB->collisionBody()->boundingBox();
    Vector3 posA = nodeA->getTransform()->localPosition(); Vector3 posB = nodeB->getTransform()->localPosition();
    
    
    float dx = boxA->xMax() + posA.x - boxB->xMin() - posB.x; //left
    float dx2 = boxB->xMax() + posB.x - boxA->xMin() - posA.x;//right
    float dy = boxA->yMax() + posA.y - boxB->yMin() - posB.y; //top
    float dy2 = boxB->yMax() + posB.y - boxA->yMin() - posA.y;//bottom
    float dz = boxA->zMax() + posA.z - boxB->zMin() - posB.z; //front
    float dz2 = boxB->zMax() + posB.z - boxA->zMin() - posA.z;//back
    string axis = "x"; float diff = dx; float sign = 1;
    
    
    if (dx2 < diff) {
        diff = dx2;
        axis = "x";
        sign = -1;
    }
    if (dy < diff) {
        diff = dy;
        axis = "y";
        sign = 1;
    }
    if (dy2 < diff) {
        diff = dy2;
        axis = "y";
        sign = -1;
    }
    if (dz < diff) {
        diff = dz;
        axis = "z";
        sign = 1;
    }
    if (dz2 < diff) {
        diff = dz2;
        axis = "z";
        sign = -1;
    }
    this->axis = axis;
    return diff * sign;
}

bool CollisionEvent::isPrevented() {
    return this->prevented;
}


void CollisionEvent::preventCollision(bool prevent) {
    this->prevented = prevent;
}
