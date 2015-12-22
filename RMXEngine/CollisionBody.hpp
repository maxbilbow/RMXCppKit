//
//  CollisionBody.hpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef CollisionBody_hpp
#define CollisionBody_hpp

#include <stdio.h>

#endif /* CollisionBody_hpp */

#define NO_COLLISIONS                  -1
#define DEFAULT_COLLISION_GROUP         0
#define EXCLUSIVE_COLLISION_GROUP   01234

namespace rmx {
    class CollisionBody : public Object {
        int collisionGroup = DEFAULT_COLLISION_GROUP;
        PhysicsBody * _physicsBody;
        BoundingBox * _boundingBox;
        BoundingSphere * _boundingSphere;
        
       
        
    public:
        int CollisionGroup();
        PhysicsBody * physicsBody();
         LinkedList<CollisionBody> * contacts = new LinkedList<CollisionBody>();
        
        //	public final node;
        CollisionBody(PhysicsBody * body);
        
        int getCollisionGroup();
        
        void setCollisionGroup(int collisionGroup);
        
        
        bool intersects(CollisionBody * other);
        
        BoundingBox * boundingBox();
        BoundingSphere * boundingSphere();
        
        GameNode * getNode();
    };
}