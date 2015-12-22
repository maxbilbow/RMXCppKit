/*
 *  RMXKit.cpp
 *  RMXKit
 *
 *  Created by Max Bilbow on 28/07/2015.
 *  Copyright © 2015 Rattle Media Ltd. All rights reserved.
 *
 */

#include "RMXKit.h"
#include "RMXKitPriv.h"

//using namespace rmx;
CFStringRef RMXKitUUID(void)
{
	CRMXKit* theObj = new CRMXKit;
	return theObj->UUID();
}

CFStringRef CRMXKit::UUID()
{
	return CFSTR("0001020304050607");
}
