//
//  BoundingBox.hpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef BoundingBox_hpp
#define BoundingBox_hpp

#include <stdio.h>

#endif /* BoundingBox_hpp */


namespace rmx {
    class BoundingBox : public Object {
        PhysicsBody * body;
    public:
        BoundingBox(PhysicsBody *);
        
        GameNode * getNode();
        Transform * transform();
        
        float xMin();
        float yMin();
        float zMin();
        float xMax();
        float yMax();
        float zMax();
        
        bool intersects(BoundingBox * other);
        
        Vector3 getCollisionNormal(BoundingBox * other);
    };
    
}