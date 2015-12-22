//
//  GameController.cpp
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"

#import "Scene.hpp"

#import "GameNode.hpp"

#import "Delegates.hpp"
#import "Transform.hpp"
#import "Behaviour.hpp"
#import "PhysicsBody.hpp"

#import "GameView.hpp"
#import "Geometry.hpp"
#ifdef GLFW
#import "glfw3.h"
#endif
#import "GameController.hpp"
#import "EntityGenerator.hpp"
#import "SpriteBehaviour.hpp"
using namespace std;
using namespace rmx;

GameController::GameController() {
    if (_singleton != nullptr)
        throw invalid_argument("GameController already started");
    else
        _singleton = this;
    this->view = new GameView();
    this->view->setDelegate(this);
//    this->setView(new GameView());
}

GameController * GameController::_singleton = nullptr;// = new GameController();
GameController * GameController::getInstance() {
    if(_singleton ==   nullptr) {
        _singleton = new GameController();
    }
    return _singleton;
}





void GameController::run() {
 
            this->setup();
#ifdef GLFW
            this->view->initGL();
            this->view->enterGameLoop();
            

            glfwDestroyWindow(view->window());

            glfwTerminate();
#endif

    
}
    

void GameController::updateBeforeScene(GLWindow * window) {
    this->repeatedKeys(window);
}


void GameController::updateAfterScene(GLWindow * window) {
    
}

void GameController::repeatedKeys(GLWindow * window) {
    
    #ifdef GLFW
    GameNode * player = GameNode::getCurrent();//GameNode::getCurrent();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player->BroadcastMessage("forward", new float(1.0));
    }
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player->BroadcastMessage("forward", new float(-1.0));
    }
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player->BroadcastMessage("left", new float(1.0));
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player->BroadcastMessage("left", new float(-1.0));
    }
    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        player->BroadcastMessage("up", new float(1.0));
    }
    
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        player->BroadcastMessage("up", new float(- 1.0));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        player->BroadcastMessage("jump");
    }
    
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        player->getTransform()->move(Yaw, 1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        player->getTransform()->move(Yaw,-1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        view->pointOfView()->getTransform()->move(Pitch,-1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        view->pointOfView()->getTransform()->move(Pitch, 1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        player->getTransform()->move(Roll, 1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        player->getTransform()->move(Roll,-1.0f);
    }
#endif
//    cout << player->getTransform()->localMatrix();
//    cout << "             Euler: " << player->getTransform()->eulerAngles() << endl;
//    cout << "       Local Euler: " << player->getTransform()->localEulerAngles() << endl;
//    cout << "          Position: " << player->getTransform()->position() << endl;
//    cout << endl;
}


void GameController::setView(GameView * view) {
    this->view = view;
    this->view->setDelegate(this);
//    this->keys = new int[600];
}

int GameController::keys[600] = {0};

GameNode * player() {
    return GameNode::getCurrent();
}

void GameController::keyCallback(GLWindow *window, int key, int scancode, int action, int mods) {
    #ifdef GLFW
//    cout << "  KEYS: " << key << ", " << scancode << ", " << action << ", " << mods << endl;
    GameController * gc = getInstance();
    if (action == GLFW_PRESS) {
        gc->keys[key] = action;
        cout << "Key Down: " << (char) key << " " << scancode << " " << action << " " << mods << endl;
    } else if (action == GLFW_RELEASE) {
        gc->keys[key] = action;
        cout << "  Key Up: " << (char) key << " " << scancode << " " << action << " " << mods << endl;
    }
    
    if (action == GLFW_RELEASE)
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            case GLFW_KEY_W:
                //			 Node.getCurrent().transform.moveForward(1);
                break;
            case GLFW_KEY_M:
                
                if (gc->cursorLocked) {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    gc->lockCursor(false);
                } else {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                    gc->lockCursor(true);
                }
                break;
            case GLFW_KEY_G:
                if (mods == GLFW_MOD_SHIFT)
                    player()->physicsBody()->setEffectedByGravity(false);
                else
                    player()->physicsBody()->setEffectedByGravity(true);
                break;
        }
#endif
}

void GameController::lockCursor(bool lock) {
    this->cursorLocked = lock;
}
bool GameController::isCursorLocked() {
    return this->cursorLocked;
}

double xpos ,ypos;
bool restart = true;

void GameController::cursorCallback(GLWindow * w, double x, double y) {
    
    GameController * gc = getInstance();
    
    if (!gc->cursorLocked)
        return;
//    cout << "CURSOR: " << w << ", " << x << ", " << y << endl;
    if (restart) {
        xpos = x;
        ypos = y;
        restart = false;
        return;
    } else {
        double dx = x - xpos;
        double dy = y - ypos;
        dx *= 0.1; dy *= 0.1;
        xpos = x;
        ypos = y;
//        GameNode * pov =
        Transform * body = GameNode::getCurrent()->getTransform();
        Transform * head = gc->view->pointOfView()->getTransform();
        head->rotate(Pitch, -dy);
        body->rotate(Yaw,   dx);
        
    }
    
    
}
GameView * GameController::getView() {
    return this->view;
}

void GameController::windowSizeCallback(GLWindow * window, int width, int height) {
    GameController * gvc = getInstance();
    gvc->view->setWidth(width);
    gvc->view->setHeight(height);
    #ifdef GLFW
    glfwSetWindowSize(window, width, height);
#endif
}