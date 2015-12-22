//
//  Transform.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>

#endif /* Transform_hpp */
//#import "Node.hpp"


namespace rmx{
   
   
    class Transform : public NodeComponent {
//        Matrix4 _worldMatrix;
        Matrix4 _axis;
        Matrix4 _localMatrix;
//        Quaternion _quaternion;
//        Vector3 _eulerAngles;
        Vector3 _scale, _lastPosition;
        
        ///Exists to thwart defauly constructor.
        Transform();
        
    public:
        Transform(GameNode * node);
        typedef RMXMessage Move;
//        Transform(Node * node);
        Transform * New(GameNode * node);
        
        void setScale(float x, float y, float z);
        
        bool move(Move name, float scale = 1, std::string args = "");
        
        void setPosition(float x, float y, float z);
        
        Vector3 scale();
        
        /**
         * TODO: Test with children
         * @return sum of all mass
         */
        float mass();
        
        void setM(int i, float value);
        
        void addM(int i, float value);
        /**
         * 
         */
        Matrix4 worldMatrix();
        Transform * parent();
        Vector3 localPosition();
        Vector3 position();
        Vector3 left();
        Vector3 up();
        Vector3 forward();
        
        void setPosition(Vector3 position);
        
        void translate(float x, float y, float z);
        void translate(Vector3 v);
        void translate(Vector4 v);
        bool translate(Move direction, float scale);
        bool rotate(Move direction, float scale);
        void rotate(float radians,Vector3 v);
        void rotate(float radians, float x, float y, float z);
        
        Quaternion rotation();
        
        Quaternion localRotation();
        
        Vector3 eulerAngles();
        
        Vector3 localEulerAngles();
        
        
        Matrix4 localMatrix();
        
        
        GameNode * setNode(GameNode * node) override;
        
        float radius();
        float getWidth();
        float getHeight();
        float getLength();
        void updateLastPosition();
        Vector3 lastPosition();
        
        Transform * rootTransform();
        void stepBack(std::string);
        
        PhysicsBody * physicsBody();
        CollisionBody * collisionBody();
    };

}