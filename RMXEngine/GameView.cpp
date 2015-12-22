//
//  GameView.c
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//


#import "Includes.h"

#import "Scene.hpp"

#import "Transform.hpp"
#import "NodeComponent.hpp"
#import "GameNode.hpp"
#import "Behaviour.hpp"
#import "PhysicsBody.hpp"
#import "Delegates.hpp"
//#import <GLFW/glfw3.h>
#import "GameController.hpp"
#import "GameView.hpp"


#define GLFW_INCLUDE_GLU



//#import <Glut/Glut.h>
using namespace rmx;
using namespace std;

GameView::GameView(){
//    this->setPointOfView(GameNode::newCameraNode());
}


long GameNode::tick() {
    return _tick;
}

void GameView::initGL() {
    
   
    
#ifdef GLFW
    // Initialize GLFW. Most GLFW functions will not work before doing this.
    if ( glfwInit() != GL_TRUE )
        throw new invalid_argument("Unable to initialize GLFW");
    
    glfwDefaultWindowHints(); // optional, the current window hints are already the default
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // the window will stay hidden after creation
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // the window will be resizable
    _window = glfwCreateWindow(_width, _height, "Hello World!", nullptr, nullptr);
    if ( _window == nullptr )
        throw new invalid_argument("Failed to create the GLFW window");

    
   
    // Create the window
    
  
    
    // Setup a key callback. It will be called every time a key is pressed, repeated or released.
    glfwSetKeyCallback(_window, GameController::keyCallback);
    glfwSetWindowSizeCallback(_window, GameController::windowSizeCallback);
    
    glfwSetCursorPosCallback(_window, GameController::cursorCallback);
    // Get the resolution of the primary monitor
    const GLFWvidmode * vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    // Center our window
    glfwSetWindowPos(
                     _window,
                     (vidmode->width - _width) / 2,
                     (vidmode->height - _height) / 2
                     );
    
    // Make the OpenGL context current
    glfwMakeContextCurrent(_window);
    // Enable v-sync
    glfwSwapInterval(1);
    
    // Make the window visible
    glfwShowWindow(_window);
    
    //        more();
    
#endif
}

void GameView::enterGameLoop() {
    //    	glfwGenuffers(1, frameBuffer);
    // This line is critical for LWJGL's interoperation with GLFW's
    // OpenGL context, or any context that is managed externally.
    // LWJGL detects the context that is current in the current thread,
    // creates the ContextCapabilities instance and makes the OpenGL
    // bindings available for use.
//    GLFWwindow * window =
#ifdef GLFW
    glfwMakeContextCurrent(_window);

  
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
 
    while ( glfwWindowShouldClose(_window) == GL_FALSE ) {
        Scene * scene = Scene::getCurrent();
        Camera * camera = pointOfView()->getCamera();
        
        if (this->delegate != nullptr)
            this->delegate->updateBeforeScene(_window);
        
        scene->updateSceneLogic();
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        camera->makePerspective(this);
        
        
        
        glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer
        glMatrixMode(GL_MODELVIEW);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glLoadIdentity();
        
//            camera.look();
        scene->renderScene(camera->viewMatrix());
        
        glfwSwapBuffers(_window);
        
        glMatrixMode(GL_PROJECTION);
        // swap the color buffers
        if (this->delegate != nullptr)
            this->delegate->updateAfterScene(_window);
        
        // Poll for window events. The key callback above will only be
        // invoked during this call.
        glfwPollEvents();
        
        NotificationCenter::eventDidOccur(END_OF_GAMELOOP);
        
    }
#endif
}



bool GameView::setPointOfView(GameNode * pointOfView) {
    cout << "Setting GameView::_pointOfView: " << pointOfView << endl;
    if (!pointOfView->hasCamera()) 
        throw new invalid_argument("PointOfView musy have a camera != null");//pointOfView->setCamera(new Camera());//
    this->_pointOfView = pointOfView;
    return true;
}

RenderDelegate * GameView::getDelegate() {
    return this->delegate;
}


void GameView::setDelegate(RenderDelegate * delegate) {
    this->delegate = delegate;
}




GLWindow * GameView::window() {
    // TODO Auto-generated method stub
    return _window;
}

void GameView::errorCallback(int i, const char *c) {
    cout << "there was an error: " << c << endl;
}



int GameView::width() {
    return _width;
}

void GameView::setWidth(int width) {
    this->_width = width;
}

int GameView::height() {
    return _height;
}

void GameView::setHeight(int height) {
    this->_height = height;
}

GameNode * GameView::pointOfView() {
    if (_pointOfView != nullptr )//|| this->setPointOfView(GameNode::getCurrent()))
        return _pointOfView;
    throw invalid_argument("ERROR: Could Not Set _pointOfView");
    return   nullptr;
}
