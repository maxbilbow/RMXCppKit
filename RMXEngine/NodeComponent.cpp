//
//  NodeComponent.cpp
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
//#import <iostream>
#import "Includes.h"
#import "GameNode.hpp"
#import "NodeComponent.hpp"
#import "Transform.hpp"
//#import "NodeComponent.hpp"

using namespace rmx;
using namespace std;



NodeComponent::NodeComponent() {
//    this->node = (GameNode*)malloc(sizeof(GameNode));
    this->setName(typeid(this).name());
}

bool NodeComponent::isEnabled() {
    return this->enabled;
}

inline void NodeComponent::setEnabled(bool enabled) {
    this->enabled = enabled;
}

//NodeComponent::setNode(GameNode *node) {
//    GameNode * oldNode = this->node;
//    this->node = node;
//    this->setName(this->Name() + "::" + node->Name());
//    return oldNode;
//}

//inline Node * NodeComponent::setNode(Node * node) {
//    Node * oldNode = this->node;
//    this->node = node;
//    return oldNode;
//}

GameNode * NodeComponent::getNode() {
    return this->node;
}

Transform * NodeComponent::getTransform() {
    return this->node->getTransform();
}