//
//  Delegates.h
//  RMXKit
//
//  Created by Max Bilbow on 20/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Delegates_h
#define Delegates_h


#endif /* Delegates_h */


namespace rmx {
    class RenderDelegate {
    public:
        
        virtual void updateBeforeScene(GLWindow * window){
            throw std::invalid_argument("updateBeforeScene must be overriden");
        };
        
        virtual void updateAfterScene(GLWindow * window){};
        
    };
}