//
//  EntityGenerator.hpp
//  RMXKit
//
//  Created by Max Bilbow on 24/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef EntityGenerator_hpp
#define EntityGenerator_hpp

#include <stdio.h>

#endif /* EntityGenerator_hpp */

namespace rmx {
class EntityGenerator {
public:
    virtual GameNode * makeEntity(){ return nullptr;}
    int
    xMin, yMin, zMin,
    xMax, yMax, zMax;
    
    EntityGenerator() {
        xMax = yMax = zMax =  100;
        xMin = yMin = zMin = -100;
    }
    void makeShapesAndAddToScene(Scene * scene, int quantity) {
        for (int i = 0; i<quantity; ++i) {
            GameNode * entity = this->makeEntity();
            if (entity != nullptr)
                scene->rootNode()->addChild(this->initPositionOf(entity));
        }
    }
    
private:
    GameNode * initPositionOf(GameNode * node) {
        node->getTransform()->setPosition(
                                   rBounds(xMin, xMax),
                                   rBounds(yMin, yMax),
                                   rBounds(zMin, zMax)
                                   );
        node->getTransform()->rotate(Yaw, (float)rBounds(0, 360));
        return node;
    }
    
};
}