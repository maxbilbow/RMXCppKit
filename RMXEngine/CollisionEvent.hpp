//
//  CollisionEvent.hpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef CollisionEvent_hpp
#define CollisionEvent_hpp

#include <stdio.h>

#endif /* CollisionEvent_hpp */

#define ON_COLLISION_START "onCollisionStart"
#define ON_COLLISION_END   "onCollisionEnd"


namespace rmx {
    class CollisionEvent : public Object {
        unsigned int key;
        bool newCollision = false;
    public:
        GameNode * nodeA, * nodeB;
        Vector3 hitPointA, hitPointB, AtoB;
        float startingDistance, planeDistance;
//        std::string _log;
    private:
        std::string axis;
        bool prevented = false;
        void seperateBodies(Transform * A, Transform * B);
        void processMomentum(Transform * A, Transform * B);
//        void finishUp(CollisionBody * A,  CollisionBody * B);
    public:
        CollisionEvent(GameNode * nodeA, GameNode * nodeB, unsigned int key);
        
        float getPlaneDistance();
        
        float getDistance();
        
        void preventCollision(bool prevent);
        
        bool isPrevented();
        
        void processCollision(unsigned int key);
        
    };
}