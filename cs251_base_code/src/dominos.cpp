/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
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
//asdv

#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{
  /** \par The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  dominos_t::dominos_t()
  {
  /** \par Ground 
    -# shape -b2EdgeShape 
      -# A line segment (edge) shape
      -# These can be connected in chains or loops to other edge shapes
      -# The connectivity information is used to ensure correct contact normals
    -# bd -b2BodyDef 
      -# A body definition holds all the data needed to construct a rigid body
      -# You can safely re-use body definitions
      -# Shapes are added to a body after construction
    -# b2vec2 -variable
      -# A 2 dimensional column vector 
    -# Set -b2EdgeShape 
      -# Set this as an isolated edge
    -# CreateFixture -b2Body 
      -# Creates a fixture from a shape and attach it to this body
      -# This is a convenience function
      -# If the density is non-zero, this function automatically updates the mass of the body           
  */
    b2Body* b1;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 3.0f), b2Vec2(90.0f, 3.0f));
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

  /** \par Top Horizontal shelf-a place belonging to Tom
    -# shape -b2PolygonShape
      -# A convex polygon
      -# It is assumed that the interior of the polygon is to the left of each edge
      -# Polygons have a maximum number of vertices equal to b2_maxPolygonVertices
      -# In most cases you should not need many vertices for a convex polygon
    -# SetAsBox -b2PolygonShape 
      -# Build vertices to represent an oriented box
    -# bd -b2BodyDef 
      -# A body definition holds all the data needed to construct a rigid body
      -# You can safely re-use body definitions
      -# Shapes are added to a body after construction
    -# position -b2vec2
      -# A two dimensional column vector
    -# Set -b2vec2
      -# Set this vector to some specified coordinates
    -# ground -b2Body 
      -# A rigid body
    -# CreateFixture -b2Body 
      -# Creates a fixture from a shape and attach it to this body
      -# This is a convenience function
      -# If the density is non-zero, this function automatically updates the mass of the body              
  */
    {
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(-35.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    /** \par Tom's powerful pushing leg
      * This is the front leg of tom which is responsible for the disturbance of first domino
      * which finally leads to trapping of Jerry.
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.85f, 0.001f);

      b2BodyDef bd;
      bd.position.Set(-31.25f, 32.88f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    /** \par Top horizontal shelf
      * This is in the top right corner of the of the screen.
      * This serves as a platform for a long set of dominoes
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(-24.75f, 31.05f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    /** \par Dominos on the top right
      * This is the first set of dominoes which are situated in the top right corner of the screen.
      * This then lead to disturbing a sphere which falls into a pulley system.
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);

      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 12.0f;
      fd.friction = 0.1f;

      for (int i = 0; i < 8; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-29.25f + 1.0f * i, 33.03f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    /** \par solid sphere
     * This sphere is located at the top right corner of the screen.
     * This sphere when disturbed from its position by a knocking of domino, then falls into the solid open rectangular container.
    */
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 5.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-20.50f, 33.25f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
   



    //Another horizontal shelf
    /*
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);

      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
	*/

/*
    //The pendulum that knocks the dominos off
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.0f, 0.f);

	b2BodyDef bd;
	bd.position.Set(-36.5f, 42.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 0.0f);
      }

      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
*/
    //The train of small spheres
    /*
    {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.5;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;

      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
    */
   



    /** \par The pulley system
      * This pulley system is located in the top right corner of the screen and when sufficient amount weight is present in its left container
      * the right container moves up and disturbs a sphere on revolving platform.
    */
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,17);
      bd->fixedRotation = true;

      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.0;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(-6.0f,6.1f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(-4.0f,8.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-8.0f,8.f), 0);
      fd3->shape = &bs3;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(-4,20.5);
      fd1->density = 34.0f;
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      //b2Vec2 worldAnchorOnBody1(-28, 19); // Anchor point on body 1 in world axis
      //b2Vec2 worldAnchorOnBody2(-12, 19); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-16, 28.25f); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(-10,28.25f); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    /** \par The revolving horizontal platform
     * This is located in the top-center part of the screen
     * This platform holds a sphere which when falls of the platform disturbs a pendulum system and falls into the container 
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);

      b2BodyDef bd;
      bd.position.Set(-7.0f, 28.50f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-7.0f, 28.50f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    /** \par The heavy sphere on the platform
     * This sphere is located in the top-center part of the screen and is responsible for disturbing the series of pendulum system
      * This then falls off into the solid open rectangular container to stop it from disturbing other parts of the simulation.
    */
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 2.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-7.0f, 30.50f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }



    //Box
    /*
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.8f, 0.10f);

      b2BodyDef bd;
      bd.position.Set(-6.0f, 16.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {

      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_staticBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;


      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.0;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(-6.f,14.0f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(-4.0f,15.9f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-8.0f,15.9f), 0);
      fd3->shape = &bs3;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
  	}*/




  /** \par Open Rectangular Box to stop the sphere
   * This is located in the top-center part of the screen.
   * This Box is shaped in such a manner such that it is just sufficient to hold the sphere from falling off and disturbing the whole system below it.
  **/

{
  {
      b2PolygonShape shape;
      shape.SetAsBox(1.7f, 0.1f);

      b2BodyDef bd;
      bd.position.Set(-4.7f, 25.7f);
      //bd.position.Set(-6.0f, 16.7f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

  {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.35f);

      b2BodyDef bd;
      bd.position.Set(-6.2f, 26.0f);
      //bd.position.Set(-7.5f, 17.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

  {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.35f);

      b2BodyDef bd;
      bd.position.Set(-3.2f, 26.95f);
      //bd.position.Set(-4.5f, 17.95f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
}

  	/** \par Series of pendulums
     * This series of pendulums is present in the top-center corner of the screen
     * This is implemented by iterating in a "for loop" which creates a series of 6 pendulums
     * These the disturb a solid sphere which fals onto conveyer belt.
    */
  	{
      b2Body* b2;

	b2PolygonShape shape;
	shape.SetAsBox(2.0f, 0.0f);



	//b2BodyDef bd;
	//bd.position.Set(-36.5f, 38.0f);
	//b2 = m_world->CreateBody(&bd);
	//b2->CreateFixture(&shape, 0.0f);



      b2Body* b4;

    b2CircleShape circle;
    circle.m_radius = 0.5;



	//b2PolygonShape shape;
	//shape.SetAsBox(0.25f, 0.25f);




    b2FixtureDef ballfd;
    ballfd.shape = &circle;
    ballfd.density = 5.0f;
    ballfd.friction = 0.0f;
    ballfd.restitution = 0.0f;
    for (int i = 0; i < 6; ++i)
	{
	  b2BodyDef bd;
	  bd.position.Set(-4.90f + i*1.0f, 35.50f);
	  b2 = m_world->CreateBody(&bd);
	  b2->CreateFixture(&shape, 0.0f);
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-4.90f + i*1.0f, 29.50f);
	  b4 = m_world->CreateBody(&ballbd);
	  b4->CreateFixture(&ballfd);
	  b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-4.90f + i*1.0f, 35.50f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
	}
 }
	//This part of code to be replaced with code for conveyer belt
  

	//Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(10.0f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(9.95f, 28.05f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);

      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 12.0f;
      fd.friction = 0.1f;

      for (int i = 0; i < 19; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(0.95f + 1.0f * i, 29.03f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    //end of trail for conveyer belt
  


	/** \par Horizontal Platform After Conveyer Belt
   * This is located in the top-right corner of the screen.
   * This is the last platform after which the sphere falls onto the inclined lines and then is directed onto the wedge system
  */
	{
      b2PolygonShape shape;
      shape.SetAsBox(1.3f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(22.00f, 28.05f);
      //bd.position.Set(1.0f, 21.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    /** \par The sphere on the platform which is hit by sphere from conveyer belt
     * This sphere is located in the top-right corner of the screen
     * This sphere falls onto the inclined lines then is directed to disturb the box present of the other side of the wedge system
    */ 
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.8;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 6.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(21.10f, 29.05f);
      ballbd.gravityScale = 2.100000000000000e+00f;
      //ballbd.position.Set(0.10f, 22.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }



/** \par Inclined lines
 * These form a set of inclined lines which are located on to the right part of the screen
 * These are there to provide the sphere enough inertia to shoot off the box present of the other side of the wedge system
 * This then goes below the staris system in the simulation and is stopped there.
*/
    {
	{
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.08f);

      b2BodyDef bd;
      bd.position.Set(25.1f, 25.55f);
      //bd.position.Set(4.0f, 18.5f);
      bd.angle = -75;
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


	{
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.08f);
	  b2BodyDef bd;
      bd.position.Set(21.10f, 20.55f);
      //bd.position.Set(0.0f, 13.5f);
      bd.angle = 75;
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

	{
      b2PolygonShape shape;
      shape.SetAsBox(0.08f, 0.3f);

      b2BodyDef bd;
      bd.position.Set(15.7f, 23.35f);
      //bd.position.Set(-5.4f, 16.3f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.08f);

      b2BodyDef bd;
      bd.position.Set(28.10f, 16.05f);
      //bd.position.Set(7.0f, 9.0f);
      bd.angle = -75;
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.09f, 1.25f);

      b2BodyDef bd;
      bd.position.Set(31.8f, 18.65f);
      //bd.position.Set(10.7f, 11.6f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    /*{
      b2PolygonShape shape;
      shape.SetAsBox(2.25f, 0.08f);

      b2FixtureDef fd;
      fd.shape = &shape;
      fd.friction = 1.0f;

      b2BodyDef bd;
      bd.position.Set(-2.2, 2.8f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.08f, 1.4f);

      b2BodyDef bd;
      bd.position.Set(-4.4f, 1.4f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }*/


    }

    /** \par Long horizontal line
     * This is located in the center part of the screen and serves as the divider from the lower part of the screen. 
     * This is a long horizontal line which serves as a platform for the stairs, wedge system and multiple revolving platforms.  
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(22.0f, 0.001f);

      b2BodyDef bd;
      bd.position.Set(3.0f, 9.05f);
      //bd.position.Set(0.0f, 2.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    /** \par The see-saw system at the bottom
     * This is wedge system which is located in the lower-right part of the screen.
     * This then pushes off the box which disturbs multiple revolving platforms.
     * This consists of a long plank which is held by a joint at the center and helps in knocking off the box to enough height to disturb the revolving planks. 
    */
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.1);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(16.1f, 9.05f);
      //wedgebd.position.Set(-5.0f, 2.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(16.1f, 9.95f);
      //bd2.position.Set(-5.0f, 2.9f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(16.1f, 9.97f);
      //anchor.Set(-5.0f, 2.9f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(0.7f, 0.7f);
      b2BodyDef bd3;
      bd3.position.Set(10.4f, 11.15f);
      //bd3.position.Set(-7.5f, 3.7f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 3.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }

    /** \par Multiple revolving horizontal platforms which act as stairs
     * This system is designed and setup in such a way so as to revolve such that movement of just one of them disturbs all of them in series.
     * This helps in moving the impact from the box to move upwards untill it disturbs the last plank which holds the sphere which moves to later part of simulation 
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.55f, 0.2f);
      b2BodyDef bd;
      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      for(int i=0;i<6;i++){ 
      if(i<2){ 
      	bd.position.Set(11.0f-i*1.7f, 12.45f+i*1.45f); 	
      	bd2.position.Set(11.0f-i*1.7f, 12.45f+i*1.45f);    	
      	//bd.position.Set(-10.1f-i*1.7f, 5.0f+i*1.45f); 	
      	//bd2.position.Set(-10.1f-i*1.7f, 5.0f+i*1.45f);
       }
       else if (i<4){
       	bd.position.Set(14.2f-i*1.7f, 12.45f+i*1.45f); 	
      	bd2.position.Set(14.2f-i*1.7f, 12.45f+i*1.45f);
       	//bd.position.Set(-6.9f-i*1.7f, 5.0f+i*1.45f); 	
      	//bd2.position.Set(-6.9f-i*1.7f, 5.0f+i*1.45f);
       }
       else if (i<6){
       	bd.position.Set(17.4f-i*1.7f, 12.45f+i*1.45f); 	
      	bd2.position.Set(17.4f-i*1.7f, 12.45f+i*1.45f);
       }
       bd.type = b2_dynamicBody;
      	b2Body* body = m_world->CreateBody(&bd);
      	b2FixtureDef *fd = new b2FixtureDef;
      	fd->density = 0.5f;
      	fd->shape = new b2PolygonShape;
      	fd->shape = &shape;
      	body->CreateFixture(fd);
      	//bd2.gravityScale = 1.000000000000000e+00f;
      	b2Body* body2 = m_world->CreateBody(&bd2);
        
      	b2RevoluteJointDef jointDef;
      	jointDef.bodyA = body;
      	jointDef.bodyB = body2;
      	jointDef.localAnchorA.Set(0,0);
      	jointDef.localAnchorB.Set(0,0);
      	jointDef.collideConnected = false;
      	m_world->CreateJoint(&jointDef);

      }
      
    }
    /** \par Sphere that disturbs the dominos on the stairs
     * This sphere is located in the center part of the screen.
     * This sphere knocks off the first domino on the decending stair system
    */
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.5;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 11.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(8.9f, 21.7f);
      //ballbd.position.Set(-12.0f, 11.35f);
      ballbd.gravityScale = 1.500000000000000e+00f;
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }

    /** \par Stairs and dominos
     * This consists of both the dominos and decending stair system which are present in the center part of the screen
     * This is first disturbed by the sphere on the last plank of the revolving plank system
     * These dominoes are designed in such a way so that the heights are just enough to transfer the impact given by the sphere.
     * This system is followed by a series of dominoes of varying heights
    */ 
   {
    {
      b2PolygonShape shape, shaped;
      shaped.SetAsBox(0.1f, 1.4f); //shaped for dominos
      b2FixtureDef fdd;
      fdd.shape = &shaped;
      fdd.density = 10.0f;
      fdd.friction = 0.1f;
      b2BodyDef bd,bdd;
      bdd.type = b2_dynamicBody;
      for(int i=0;i<6;i++){
      	if(i%2==1){
      		shape.SetAsBox(0.01f, 1.2f);
      		//for dominos
      		bdd.position.Set(0.11f+i*1.28f, 22.5f-i*0.5f);
      		//bdd.position.Set(-17.8f+i*1.28f, 10.55f-i*0.5f);
      		b2Body* bodyd = m_world->CreateBody(&bdd);
	  		bodyd->CreateFixture(&fdd);
      	}
      	else {shape.SetAsBox(1.2f, 0.01f);}
      	bd.position.Set(6.42f-i*1.2f, 18.0f-i*1.2f);
      	//bd.position.Set(-13.9f-i*1.2f, 7.55f-i*1.2f);

      	b2Body* ground = m_world->CreateBody(&bd);
      	ground->CreateFixture(&shape, 0.0f);
      	
      }
    }
    {
    b2PolygonShape shape,shaped;
    //shaped.SetAsBox(0.1f, 1.4f); //shaped for dominos
    
    b2BodyDef bd;
    shape.SetAsBox(0.01f, 1.2f); // step
    bd.position.Set(0.42f, 10.3f);
    b2Body* ground = m_world->CreateBody(&bd);
    ground->CreateFixture(&shape, 0.0f);
        //bd.position.Set(-13.9f-i*1.2f, 7.55f-i*1.2f);
    for(int i=4;i<11;i++){//dominos
    	if(i>=4 &&i<8){
            shaped.SetAsBox(0.1f, (8-i)*0.6f);
        }
        if(i>=8 && i<11){
        	shaped.SetAsBox(0.1f, (i-6)*0.6f);
        }
            b2FixtureDef fdd;
            fdd.shape = &shaped;
    fdd.density = 5.0f;
    fdd.friction = 0.1f;
    b2BodyDef bdd;
    bdd.type = b2_dynamicBody;
            bdd.position.Set(2.5f - i*1.0f,14.0f);
            b2Body* bodyd = m_world->CreateBody(&bdd);
        bodyd->CreateFixture(&fdd);
          }
     
    }
   }

	/** \par Large ball moving towards inclined line to the left
   * This sphere is located in the center-left part of the screen.
   * This sphere is pushed off by the domins system which then travels to the inclined line to later part of the simulation
  */
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.8f;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 2.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-12.0f,10.3);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }

   //Inclined line to the left
   {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.08f);

      b2BodyDef bd;
      bd.position.Set(-25.1f, 8.55f);
      //bd.position.Set(4.0f, 18.5f);
      bd.angle = 75;
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

   /** Dominoes on the floor and a train of two spheres
    * This forms the lower part of the screen.
    * This system consists of Two sets of ascending and descending heights of dominoes and a train of two spheres
    * The dominoes of varying heights are designed by putting various for loops and conditional statements.
    * Ths train of two spheres help in transforming the impact of 1st set dominoes to 2nd set of dominoes of varying heights.
   */

   //inc-dec heights dominos-1
  {
      b2PolygonShape shape;
      for(int i=1;i<14;i++){
          if(i<5){
            shape.SetAsBox(0.1f, (i)*0.55f);
          }
          else if(i>=5 && i<8){
            shape.SetAsBox(0.1f, (8-i)*0.55f);
          }
          else if(i>=8 && i<=10){
            shape.SetAsBox(0.1f, (i-6)*0.55f);
          }
          else if(i>10 && i<=13){
            shape.SetAsBox(0.1f, (14-i)*0.55f);
          }
            b2FixtureDef fd;
            fd.shape = &shape;
            fd.density = 23.0f;
            fd.friction = 0.1f;
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(7.5f + 1.0f * i,6);
            b2Body* body = m_world->CreateBody(&bd);
            body->CreateFixture(&fd);
      }
    }
     //The train of small spheres
    {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.72;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 10.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;

      for (int i = 0; i < 2; ++i)
    {
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(2.5f + i*1.0, 4);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
    }
  }
  //inc-dec heights dominos-2
    {
      b2PolygonShape shape;
      for(int i=1;i<14;i++){
          if(i<5){
            shape.SetAsBox(0.1f, (i)*0.55f);
          }
          else if(i>=5 && i<8){
            shape.SetAsBox(0.1f, (8-i)*0.55f);
          }
          else if(i>=8 && i<=10){
            shape.SetAsBox(0.1f, (i-6)*0.55f);
          }
          else if(i>10 && i<=13){
            shape.SetAsBox(0.1f, (14-i)*0.55f);
          }
            b2FixtureDef fd;
            fd.shape = &shape;
            fd.density = 25.0f;
            fd.friction = 0.1f;
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-12.5f + 1.0f * i,6);
            b2Body* body = m_world->CreateBody(&bd);
            body->CreateFixture(&fd);
      }
    }

    /** \par Fate changing sphere of Jerry :)
     * This sphere is located in lower-right part of the screen.
     * This is designed to move up in the simulation by changing its "gravityScale" property.
     * This the pushes one side of the final pulley system which traps the Jerry.
    */
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(19.5f,9);
      ballbd.gravityScale = -1.000000000000000e+00f;
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
    /** \par Jerry's Den
     * This consists of the pulley system which has the trap for the Jery on the other side.
     * and open rectangle on one side.
    */
    //The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(16,15);
      //bd->position.Set(-10,17);
      //bd->fixedRotation = true;

      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.0;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(20.0f,3.1f), 0);
      //bs1.SetAsBox(2,0.2, b2Vec2(-6.0f,6.1f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(22.0f,5.f), 0);
      //bs2.SetAsBox(0.2,2, b2Vec2(-4.0f,8.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 20.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(18.0f,5.f), 0);
      //bs3.SetAsBox(0.2,2, b2Vec2(-8.0f,8.f), 0);
      fd3->shape = &bs3;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

       //The trap
      b2FixtureDef *ffd1 = new b2FixtureDef;
      ffd1->density = 10.0;
      ffd1->friction = 0.0;
      ffd1->restitution = 0.f;
      ffd1->shape = new b2PolygonShape;
      b2PolygonShape bss1;
      bss1.SetAsBox(2,0.2, b2Vec2(26.0f,4.1f), 0);
      //bs1.SetAsBox(2,0.2, b2Vec2(-6.0f,6.1f), 0);
      ffd1->shape = &bss1;
      b2FixtureDef *ffd2 = new b2FixtureDef;
      ffd2->density = 10.0;
      ffd2->friction = 0.5;
      ffd2->restitution = 0.f;
      ffd2->shape = new b2PolygonShape;
      b2PolygonShape bss2;
      bs2.SetAsBox(0.2,3, b2Vec2(24.0f,1.2f), 0);
      //bs2.SetAsBox(0.2,2, b2Vec2(-4.0f,8.f), 0);
      ffd2->shape = &bs2;
      b2FixtureDef *ffd3 = new b2FixtureDef;
      ffd3->density = 10.0;
      ffd3->friction = 0.5;
      ffd3->restitution = 0.f;
      ffd3->shape = new b2PolygonShape;
      b2PolygonShape bss3;
      bss3.SetAsBox(0.2,3, b2Vec2(28.0f,1.2f), 0);
      //bs3.SetAsBox(0.2,2, b2Vec2(-8.0f,8.f), 0);
      ffd3->shape = &bss3;

      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(ffd1);
      box2->CreateFixture(ffd2);
      box2->CreateFixture(ffd3);


      //bd->position.Set(22,17.5);
      //bd->position.Set(-4,20.5);
      //fd1->density = 34.0f;
      //b2Body* box2 = m_world->CreateBody(bd);
      //box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      //b2Vec2 worldAnchorOnBody1(-22, 19); // Anchor point on body 1 in world axis
      //b2Vec2 worldAnchorOnBody2(-12, 19); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(36, 25.25f); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(42,25.25f); // Anchor point for ground 2 in world axis
      //b2Vec2 worldAnchorGround1(-16, 28.25f); // Anchor point for ground 1 in world axis
      //b2Vec2 worldAnchorGround2(-10,28.25f); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
    //Long Vertical line
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.001f, 13.0f);

      b2BodyDef bd;
      bd.position.Set(38.7f, 16.05f);
      //bd.position.Set(0.0f, 2.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    /** \par Jerry's place
     * This is located in the rightmost corner of the screen and last part of the simulation.
     * This is the place which acts as the platform for the Jerry to stay.
     
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.0f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(42.0f, 9.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
