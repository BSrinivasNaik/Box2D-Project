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
  /**  The is the constructor
   * This is the documentation block for the constructor.
   */

  dominos_t::dominos_t()
  {
    //Ground
    /*! \var b1
     * \brief pointer to the body ground
     */
    b2Body* b1;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 3.0f), b2Vec2(90.0f, 3.0f));
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    //Top horizontal shelf Tom's palce
    {
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(-35.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //Tom's powerful pushing leg
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.85f, 0.001f);

      b2BodyDef bd;
      bd.position.Set(-31.25f, 32.88f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(-24.75f, 31.05f);
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

      for (int i = 0; i < 8; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-29.25f + 1.0f * i, 33.03f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    //Added sphere
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

    //The pulley system
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

    //The revolving horizontal platform
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

    //The heavy sphere on the platform
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
  	//train of pendulums
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
	//Trial for boat
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
    //end of trail for boat

	//Horizontal Platform before Boat
	{
      b2PolygonShape shape;
      shape.SetAsBox(1.3f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(22.00f, 28.05f);
      //bd.position.Set(1.0f, 21.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //The sphere on the platform which hits boat
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

    //Box to stop the ball..!!

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

//Inclined lines
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

    //Long horizontal lins
    {
      b2PolygonShape shape;
      shape.SetAsBox(22.0f, 0.001f);

      b2BodyDef bd;
      bd.position.Set(3.0f, 9.05f);
      //bd.position.Set(0.0f, 2.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //The see-saw system at the bottom
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

    //Multiple revolving horizontal platforms which act as stairs
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
    //Sphere that disturbs the dominos on the stairs
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
    //Stairs and dominos
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
	// large ball moving towards conveyer belt
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

   //inclined line as substitute for conveyer belt
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

   // dominos on the floor and the sphere

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

    //Fate changing ball of Jerry :)
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
    // Jerry's Den
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
    //Long Vertical lins
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.001f, 13.0f);

      b2BodyDef bd;
      bd.position.Set(38.7f, 16.05f);
      //bd.position.Set(0.0f, 2.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //Jerry's place
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
