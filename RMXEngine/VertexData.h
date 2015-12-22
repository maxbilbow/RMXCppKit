//
//  VertexData.h
//  
//
//  Created by Max Bilbow on 03/09/2015.
//
//

#ifndef VertexData_h
#define VertexData_h

#include <stdio.h>

#endif /* VertexData_h */

//const unsigned int VERTS_CUBE = 0;
extern float * cubeVertexData;
extern long cubeVertexDataSize;
extern unsigned short cubeIndexData[];
extern float cubeNormalData[];
extern long cubeIndexDataSize;

extern float triandleVertexData[];
extern const long triandleVertexDataSize;
extern float * RMXVertsForShape(unsigned int);
extern long RMXSizeOf(unsigned int);
