/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * 
 */

#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include <Box2D/Box2D.h>

 // #ifdef __APPLE__
// #include <GLUT/glut.h>
// #else
// #include "GL/freeglut.h"
// #endif

// #define DEGTORAD 0.0174532925199432957f
// #define RADTODEG 57.295779513082320876f

struct b2AABB;


//! This class implements debug drawing callbacks that are invoked
//! inside b2World::Step.
//! we included "DrawTom" and "DrawJerry" callbacks in this class for drawing figures of Tom and Jerry.
class debug_draw_t : public b2Draw
{
public:
  void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
  
  void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
  
  void DrawTom(const b2Color& color);

  void DrawJerry(const b2Color& color);

  void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
  
  void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
  
  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
  
  void DrawTransform(const b2Transform& xf);
  
  void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
  
  void DrawString(int x, int y, const char* string, ...); 
  
  void DrawAABB(b2AABB* aabb, const b2Color& color);
};


// //structure to store current surface velocity of a fixture
// struct ConveyorSegment {
//     float minAngle;
//     float maxAngle;
//     float surfaceVelocity;
// };
// //did not inherit Test class 
// class iforce2d_Conveyors 
// {
// public:
//     iforce2d_Conveyors()
//     {
//         //
//     }
    
//     void Keyboard(unsigned char key)
//     {
//         switch (key) {
//         case 'q': m_circleConveyor.surfaceVelocity = -5; break;
//         case 'e': m_circleConveyor.surfaceVelocity =  5; break;
//         case 'a': m_polygonConveyor.surfaceVelocity = -5; break;
//         case 'd': m_polygonConveyor.surfaceVelocity =  5; break;

//         case 'w': m_circleBody->ApplyLinearImpulse( b2Vec2( 0, 150 ), m_circleBody->GetWorldCenter() ); break;
//         default: Test::Keyboard(key);
//         }
//     }

//     void KeyboardUp(unsigned char key)
//     {
//         switch (key) {
//         case 'q': case 'e': m_circleConveyor.surfaceVelocity = 0; break;
//         case 'a': case 'd': m_polygonConveyor.surfaceVelocity = 0; break;
//         default: Test::Keyboard(key);
//         }
//     }
//     void Step(Settings* settings)
//     {
//         m_debugDraw.DrawString(5, m_textLine, "Use q/w/e to control circle, a/d to control polygon");
//         m_textLine += 15;

//         Test::Step(settings);
//     }

//     static Test* Create()
//     {
//         return new iforce2d_Conveyors;
//     }
//     ConveyorSegment m_circleConveyor;
//     ConveyorSegment m_polygonConveyor;
//     ConveyorSegment m_chainConveyor1, m_chainConveyor2;
//     b2Body* m_circleBody;
// };


#endif
