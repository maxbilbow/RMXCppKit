//
//  Geometry.cpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"
#import "GameNode.hpp"
#import "NodeComponent.hpp"
#import "Transform.hpp"
#ifdef GLFW
#import "glfw3.h"
#endif
#import "Geometry.hpp"

#include "VertexData.h"


using namespace rmx;
using namespace std;

void Floor::drawWithScale(float x, float y, float z) {
#ifdef GLFW
    float inf = 99999;//Float.POSITIVE_INFINITY;
    glBegin(GL_POLYGON);
    glColor3f(0.8f,0.8f,0.8f);
    glVertex3f( inf, -y,-inf);
    glVertex3f(-inf, -y,-inf);
    glVertex3f(-inf, -y, inf);
    glVertex3f( inf, -y, inf);
    glEnd();
#endif
}

//private ByteBuffer _elements;
//private ShortBuffer _indexData;
//private int _e = 0;
Geometry::Geometry(float * verts, long  size, unsigned short * indices, long indexDataSize) {
    NodeComponent::NodeComponent();
    _vertexData = verts;//new int[sizeof(int) * size];
    _vertexDataSize = size;//= new int[sizeof(int) * size / 3]; 0.4, 0.4, 1.0, 1.0
    _indexData = indices;
    _indexDataSize = indexDataSize;
    _color = GLKVector4Make((float) (rand() % 100) / 100,
                            (float) (rand() % 100) / 100,
                            (float) (rand() % 100) / 100,
                            (float) 1.0);
    cout << _color << endl;
}

float * Geometry::vertexData() {
    return _vertexData;
}

long Geometry::vertexDataSize() {
    return _vertexDataSize;
}

unsigned short * Geometry::indexData() {
    return _indexData;
}

long Geometry::indexDataSize() {
    return _indexDataSize;
}

Vector4 Geometry::color() {
    return this->_color;
}

Vector3 Geometry::scale() {
    return this->getNode()->getTransform()->scale();
}

//const float * Geometry::vertexData() {
//    return _vertexData;
//}
//
//int * Geometry::indexData() {
//    return _indexData;
//}
//void Geometry::addVertex(Vector3 v) {
//    this->addVertex(v.x, v.y, v.z);
//}




void Geometry::render(GameNode * node, Matrix4 base) {
    
#ifdef GLFW
    
    Matrix4 model = node->getTransform()->worldMatrix();
    
    EulerAngles modelA = node->getTransform()->localEulerAngles();
    
    glPushMatrix();
    
    glTranslatef(
                 model.m30 + base.m30,
                 model.m31 + base.m31,
                 model.m32 + base.m32
                 );
    
    glRotatef(modelA.x, 1,0,0);
    glRotatef(modelA.y, 0,1,0);
    glRotatef(modelA.z, 0,0,1);

    

    float X = node->getTransform()->scale().x;
    float Y = node->getTransform()->scale().y;
    float Z = node->getTransform()->scale().z;
    drawWithScale(X, Y, Z);
    
    
    glPopMatrix();
#endif
}

Matrix4 Geometry::modelMatrix() {
    return this->getTransform()->worldMatrix();
}
void _render() {
    //this.pushMatrx();
    //		glVertex3dv(_elements);
    //glColor3f(0.0f,0.0f,1.0f);
    //glDrawElements(GL_QUADS, _elements);
    //this.popMatrix();
}



    /*Bugger.logAndPrint("Cube with " + 6*3*4 + " elements", true);
     _cube = new Geometry(6 * 3 * 4);
     _cube.addVertex( 1.0f, 1.0f,-1.0f);
     _cube.addVertex(-1.0f, 1.0f,-1.0f);
     _cube.addVertex(-1.0f, 1.0f, 1.0f);
     _cube.addVertex( 1.0f, 1.0f, 1.0f);
     //            glColor3f(1.0f,0.5f,0.0f);
     _cube.addVertex( 1.0f,-1.0f, 1.0f);
     _cube.addVertex(-1.0f,-1.0f, 1.0f);
     _cube.addVertex(-1.0f,-1.0f,-1.0f);
     _cube.addVertex( 1.0f,-1.0f,-1.0f);
     //            glColor3f(1.0f,0.0f,0.0f);
     _cube.addVertex( 1.0f, 1.0f, 1.0f);
     _cube.addVertex(-1.0f, 1.0f, 1.0f);
     _cube.addVertex(-1.0f,-1.0f, 1.0f);
     _cube.addVertex( 1.0f,-1.0f, 1.0f);
     //            glColor3f(1.0f,1.0f,0.0f);
     _cube.addVertex( 1.0f,-1.0f,-1.0f);
     _cube.addVertex(-1.0f,-1.0f,-1.0f);
     _cube.addVertex(-1.0f, 1.0f,-1.0f);
     _cube.addVertex( 1.0f, 1.0f,-1.0f);
     //            glColor3f(0.0f,0.0f,1.0f);
     _cube.addVertex(-1.0f, 1.0f, 1.0f);
     _cube.addVertex(-1.0f, 1.0f,-1.0f);
     _cube.addVertex(-1.0f,-1.0f,-1.0f);
     _cube.addVertex(-1.0f,-1.0f, 1.0f);
     //            glColor3f(1.0f,0.0f,1.0f);
     _cube.addVertex( 1.0f, 1.0f,-1.0f);
     _cube.addVertex( 1.0f, 1.0f, 1.0f);
     _cube.addVertex( 1.0f,-1.0f, 1.0f);
     _cube.addVertex( 1.0f,-1.0f,-1.0f);
     _cube.prepare();
     }*/
//    return _cube;
//}

Geometry::Geometry() {
    throw invalid_argument("Geometry must be initialized with Geometry(float* ,long )");       //    Geometry::Geometry(cubeData, cubeDataSize);
}
#ifdef GLFW
Cube::Cube(float* cd,long size) {
    Geometry::Geometry(cubeData, cubeDataSize);
}


void Cube::drawWithScale(float X, float Y, float Z)override {
    
    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,0.0f);
    glNormal3f(0,1,0);
    glVertex3f( X, Y,-Z);
    glVertex3f(-X, Y,-Z);
    glVertex3f(-X, Y, Z);
    glVertex3f( X, Y, Z);
    glColor3f(1.0f,0.5f,0.0f);
    glNormal3f(0,-1,0);
    glVertex3f( X,-Y, Z);
    glVertex3f(-X,-Y, Z);
    glVertex3f(-X,-Y,-Z);
    glVertex3f( X,-Y,-Z);
    glColor3f(1.0f,0.0f,0.0f);
    glNormal3f(0,0,1);
    glVertex3f( X, Y, Z);
    glVertex3f(-X, Y, Z);
    glVertex3f(-X,-Y, Z);
    glVertex3f( X,-Y, Z);
    glColor3f(1.0f,1.0f,0.0f);
    glNormal3f(0,0,-1);
    glVertex3f( X,-Y,-Z);
    glVertex3f(-X,-Y,-Z);
    glVertex3f(-X, Y,-Z);
    glVertex3f( X, Y,-Z);
    glColor3f(0.0f,0.0f,1.0f);
    glNormal3f(-1,0,0);
    glVertex3f(-X, Y, Z);
    glVertex3f(-X, Y,-Z);
    glVertex3f(-X,-Y,-Z);
    glVertex3f(-X,-Y, Z);
    glColor3f(1.0f,0.0f,1.0f);
    glNormal3f(1,0,0);
    glVertex3f( X, Y,-Z);
    glVertex3f( X, Y, Z);
    glVertex3f( X,-Y, Z);
    glVertex3f( X,-Y,-Z);
    glEnd();
}
#endif


//Geometry * Geometry::_cube = nullptr;
Geometry * Geometry::Cube() {
    Geometry * cube = new Geometry(cubeVertexData, cubeVertexDataSize, cubeIndexData, cubeIndexDataSize);
    return cube;
}







