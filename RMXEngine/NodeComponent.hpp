//
//  NodeComponent.hpp
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef NodeComponent_hpp
#define NodeComponent_hpp

#include <stdio.h>

#endif /* NodeComponent_hpp */

namespace rmx {
    
    class NodeComponent : public Object { //, public _NodeComponent {
    protected:
        GameNode * node;
       
        bool enabled;
       
        
        
    public:
        NodeComponent();
//        NodeComponent(std::string name):Object(name){}
        
        virtual GameNode * setNode(GameNode * node) {
            GameNode * oldNode = this->node;
            this->node = node;
//            this->setName(this->Name() + "::" + node->Name());
            return oldNode;
        }
        
        GameNode * getNode();
        
        bool isEnabled();
        void setEnabled(bool);
        
        Transform * getTransform();
        
    };

}