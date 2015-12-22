//
//  PhysicsWorld.cpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"

#import "BoundingBox.hpp"
#import "BoundingSphere.hpp"



#import "NodeComponent.hpp"
#import "PhysicsBody.hpp"
#import "CollisionBody.hpp"
#import "CollisionEvent.hpp"
#import "GameNode.hpp"
#import "Transform.hpp"
#import "PhysicsWorld.hpp"


using namespace std;
using namespace rmx;



Vector3 PhysicsWorld::getGravity() {
    return this->gravity;
}
    
void PhysicsWorld::setGravity(Vector3 gravity) {
    this->gravity = gravity;
}

void PhysicsWorld::setGravity(float x, float y, float z) {
        this->gravity.x = x;
        this->gravity.y = y;
        this->gravity.z = z;
}
    
void PhysicsWorld::updatePhysics(GameNode * rootNode) {
    GameNodeList::Iterator * i = rootNode->getChildren()->getIterator();
    while (i->hasNext()) {
        GameNode * node = i->next();
        if (node->hasPhysicsBody()) {
            this->applyGravityTo(node);
            node->physicsBody()->updatePhysics(this);
        }
    }
}

const double spf = 0.0167;
float getCurrentFramerate() {
    return spf;
}
    
void PhysicsWorld::applyGravityTo(GameNode * node) {
    if (node->physicsBody()->type() == Dynamic && node->physicsBody()->isEffectedByGravity()) {
        Transform * t = node->getTransform();
        float ground = t->scale().y;
        float mass = node->getTransform()->mass();
        float framerate = getCurrentFramerate();
       
//        if (t->position().y < ground)
//            t->setPosition(0, ground, 0);// setM(3 * 4 + 1, ground);
//        else
        t->physicsBody()->applyForce( framerate * mass, this->gravity);
    }
}


void PhysicsWorld::buildCollisionList(GameNode * rootNode) {
    
    this->staticBodies = new LinkedList<CollisionBody>();
    this->dynamicBodies = new LinkedList<CollisionBody>();
    this->kinematicBodies = new LinkedList<CollisionBody>();
    LinkedList<GameNode>::Iterator * i = rootNode->getChildren()->getIterator();
    while (i->hasNext()){
        GameNode * node = i->next();
        if (node->hasPhysicsBody()) {
            if (node->collisionBody()->CollisionGroup() != NO_COLLISIONS)
                switch (node->physicsBody()->type()) {
                    case Dynamic:
                        this->dynamicBodies->append(node->collisionBody());
                        break;
                    case Static:
                        this->staticBodies->append(node->collisionBody());
                        break;
                    case Kinematic:
                        this->kinematicBodies->append(node->collisionBody());
                        break;
                    default:
                        break;
                }
        }
    }
}

void PhysicsWorld::updateCollisionEvents(GameNode * rootNode) {
    
    
    this->buildCollisionList(rootNode);
    
    
    if (!dynamicBodies->isEmpty()) {
        if (!staticBodies->isEmpty())
            checkForStaticCollisions(dynamicBodies, staticBodies);
        checkForDynamicCollisions(dynamicBodies);
//        count = checks = 0;
        //			swapLists();
    }
    free(this->staticBodies);//.clear();
    free(this->dynamicBodies);
    free(this->kinematicBodies);
    
}


void PhysicsWorld::checkForStaticCollisions(LinkedList<CollisionBody> * dynamic, LinkedList<CollisionBody> * staticBodies) {
    LinkedList<CollisionBody>::Iterator * si = staticBodies->getIterator();
    while (si->hasNext()) {
        CollisionBody * staticBody = si->next();
        LinkedList<CollisionBody>::Iterator * di = dynamic->getIterator();
        while (di->hasNext()) {
            CollisionBody * dynamicBody = di->next();
//            checks++;
            if (this->checkForCollision(staticBody,dynamicBody)) {
//                count++;
                
                //					di.remove();
            }
        }
    }
}

//int count = 0; int checks = 0;
void PhysicsWorld::checkForDynamicCollisions(LinkedList<CollisionBody> * dynamic) {
    CollisionBody * A = dynamic->removeFirst();
    LinkedList<CollisionBody>::Iterator * i = dynamic->getIterator();
    while (i->hasNext()) {
        CollisionBody * B = i->next();
//        checks++;
        if (this->checkForCollision(A,B)) {
//            count++;
            //					if (unchecked.remove(A))
            //						System.err.println(A.uniqueName() + " removed twie");//checked.addLast(A);
//            if (
            dynamic->removeValue(B);
//                == null)
//                cout << "WARNING: " << B->uniqueName() << " was not removed from unchecked" << endl;
//            else
//                cout << "SUCCESS: " << B->uniqueName() << " was removed from unchecked" << endl;
            if (!dynamic->isEmpty()) {
                this->checkForDynamicCollisions(dynamic);
                return;
            }
        }
    }
    if (!dynamic->isEmpty()) {
        this->checkForDynamicCollisions(dynamic);
    }
}
const static unsigned int secureKey = rand() % 100;
bool PhysicsWorld::checkForCollision(CollisionBody * A, CollisionBody * B) {
    if (A == B)
        return false;
    if (A->getCollisionGroup() != B->getCollisionGroup())
        if (A->getCollisionGroup() != EXCLUSIVE_COLLISION_GROUP &&
            B->getCollisionGroup() != EXCLUSIVE_COLLISION_GROUP)
            return false;
    
    switch (A->getCollisionGroup()) {
        case NO_COLLISIONS:
        case EXCLUSIVE_COLLISION_GROUP:
            return false;
    }
    
    
    bool isHit = A->intersects(B);
    if (isHit) {
        CollisionEvent * e = new CollisionEvent(A->getNode(),B->getNode(),secureKey);
        if (collisionDelegate != nullptr)
            collisionDelegate->handleCollision(A->getNode(), B->getNode(), e);
        e->processCollision(secureKey);
    } 
    return isHit;			
    
}



