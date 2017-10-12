//
//  Includes.h
//  RMXKit
//
//  Created by Max Bilbow on 20/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Includes_h
#define Includes_h


#include <iostream>


//typedef int BOOL;
#define TRUE 1
#define FALSE 0
//typedef nullptr null;
//#define null nullptr

#include <LinkedList.h>
#include <Dictionary.h>

//
//#include <vector>
//#include <list>


//#define GLFW
#ifdef GLFW
//#import <CoreVideo/CoreVideo.h>
//#import <IOKit/IOKitLib.h>
//#import <Cocoa/Cocoa.h>
#include <GLFW/glfw3.h>
typedef GLFWwindow GLWindow;
#else

typedef long GLWindow;
#endif

namespace rmx {
    class Transform;
    class GameNode;
    class Behaviour;
    class SpriteBehaviour;
    class Geometry;
    class NodeComponent;
    class PhysicsBody;
    class Camera;
    class Scene;
    class PhysicsWorld;
    class GameView;
    class Floor;
    class Cube;
    class RenderDelegate;
    class GameController;
    class CollisionBody;
    class CollisionEvent;
    class BoundingBox;
    class BoundingSphere;
    typedef Dictionary<std::string, NodeComponent> GameNodeComponents;
    typedef LinkedList<Behaviour> GameNodeBehaviours;
    typedef LinkedList<GameNode> GameNodeList;
}

enum RMXMessage {
    Forward, Left, Up, X, Y, Z,
    Pitch, Yaw, Roll,
    Jump
};


#endif /* Includes_h */