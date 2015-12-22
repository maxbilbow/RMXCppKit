//
//  BoundingSphere.hpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef BoundingSphere_hpp
#define BoundingSphere_hpp

#include <stdio.h>

#endif /* BoundingSphere_hpp */


namespace rmx {
    class BoundingSphere : public Object {
        
        PhysicsBody * body;
    public:
        BoundingSphere(PhysicsBody * body);
        GameNode * getNode();
        Transform * transform();
        float radius();
        bool intersects(BoundingSphere*);
    };
}