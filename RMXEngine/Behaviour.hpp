//
//  Behaviour.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Behaviour_hpp
#define Behaviour_hpp

#include <cstdio>
#include "NotificationCenter.h"

namespace rmx {
    class Behaviour : public EventListener {
    protected:
        bool enabled;
    public:
       
        Behaviour() {
            this->enabled = true;
        }
        
        bool isEnabled(){
            return this->enabled;
        }
        
        void setEnabled(bool enabled) {
            this->enabled = enabled;
        }
        virtual void update(){}
        virtual void lateUpdate(){}
        
        virtual void sendMessage(AnEvent,EventArgs/*,SendMessageOptions*/) = 0;
        
        
    };
    
    
}


#endif /* Behaviour_hpp */
