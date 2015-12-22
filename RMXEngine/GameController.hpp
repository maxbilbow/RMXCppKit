//
//  GameController.hpp
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef GameController_hpp
#define GameController_hpp

#include <stdio.h>

#endif /* GameController_hpp */

namespace rmx {

    typedef bool KeyStates;

    class GameController : public Object,  public RenderDelegate  {
    protected:
    
        GameView * view;
        static GameController * _singleton;
        
        virtual void initpov() {};
   
        virtual void setup(){
            this->initpov();
        }

        
        
        static int keys[600];
        
        bool cursorLocked = false;
    public:
        GameController();
        static GameController * getInstance();
        void lockCursor(bool lock);
        bool isCursorLocked();
        void run();
        
//        bool * keys = new KeyStates[500];
        
        void repeatedKeys(GLWindow * window);
        
        void setView(GameView * view);
        
        static void keyCallback(GLWindow* w,int a,int b,int c,int d);
        
        static void cursorCallback(GLWindow*,double,double);
        void updateBeforeScene(GLWindow * window) override;
        void updateAfterScene(GLWindow * window) override;
        GameView * getView();
        static void windowSizeCallback(GLWindow * window, int width, int height);
    };

}