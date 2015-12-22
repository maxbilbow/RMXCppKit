//
//  PhysicsWorld.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef PhysicsWorld_hpp
#define PhysicsWorld_hpp

#include <stdio.h>

#endif /* PhysicsWorld_hpp */

namespace rmx {
    class CollisionDelegate {
    public:
        virtual void handleCollision(GameNode * nodA,GameNode * nodB, CollisionEvent * e){}
    };
    class PhysicsWorld : public Object , public Unfinised {
        Vector3 gravity = GLKVector3Make(0.0f,-9.8f,0.0f);
//        Scene * scene;
        LinkedList<CollisionBody> * staticBodies = new LinkedList<CollisionBody>();
        LinkedList<CollisionBody> * dynamicBodies = new LinkedList<CollisionBody>();
        LinkedList<CollisionBody> * kinematicBodies = new LinkedList<CollisionBody>();
        void buildCollisionList(GameNode * rootNode);
        bool checkForCollision(CollisionBody * A, CollisionBody * B);
        CollisionDelegate * collisionDelegate;
    public:
//        PhysicsWorld():Object(scene->getName());
        Vector3 getGravity();
        
        void setGravity(Vector3 gravity);
        
        void setGravity(float x, float y, float z);
        
        void updatePhysics(GameNode * rootNode);
        
        void applyGravityTo(GameNode * node);
        
        
        void updateCollisionEvents(GameNode * rootNode);
        void checkForStaticCollisions(LinkedList<CollisionBody> * dynamic, LinkedList<CollisionBody> * staticBodies);
        void checkForDynamicCollisions(LinkedList<CollisionBody> * dynamic);
        
        CollisionDelegate * getCollisionDelegate();
        
        void setCollisionDelegate(CollisionDelegate * collisionDelegate);

        
        
    };

}