//
//  Behaviour.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Behaviour_hpp
#define Behaviour_hpp

#include <stdio.h>

#endif /* Behaviour_hpp */



namespace rmx {
    class Behaviour : public NodeComponent {
    protected:
        bool enabled;
    public:
       
        Behaviour():NodeComponent() {
            this->enabled = true;
            this->setName("Behaviour");
        }
        
        bool isEnabled(){
            return this->enabled;
        }
        
        void setEnabled(bool enabled) {
            this->enabled = enabled;
        }
        virtual void update(){}
        virtual void lateUpdate(){}
        
        virtual void SendMessage(std::string,void*,SendMessageOptions) override {
            Object::SendMessage("Message Received via Behaviour");
            }
        
        
    };
    
    
}