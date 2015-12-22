//
//  Scene.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>

#endif /* Scene_hpp */

#ifndef GameNode_hpp
#import "GameNode.hpp"
#endif

#ifndef NodeComponent_hpp
#import "NodeComponent.hpp"
#endif

#ifndef Camera_hpp
#import "Camera.hpp"
#endif

#ifndef PhysicsWorld_hpp
#import "PhysicsWorld.hpp"
#endif


namespace rmx {
    
//    class RootNode : public GameNode {
//    public:
//        RootNode():GameNode("rootNode"){}
//    };

    class Scene : public Object {
        static Scene * _current;
        GameNode * _rootNode =   nullptr;
        PhysicsWorld * _physicsWorld = new PhysicsWorld();

    public:
        Scene();
        GameNode * rootNode();
        static Scene * getCurrent();
        static Scene * setCurrent(Scene * scene);
        void updateSceneLogic();
        void renderScene(Matrix4);
        
        void setAsCurrent();
        
        GameNode * pointOfView();
    };

}