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

#include "render.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cstdio>
#include <cstdarg>
#include <cstring>

using namespace std;

void debug_draw_t::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
}

void debug_draw_t::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4f(color.r, color.g, color.b, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
}

// Tom-The clever cat
void debug_draw_t::DrawTom(const b2Color& color)
{
    b2Vec2 center;
	center.x=-35.0f;
	center.y=33.78f;
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(color.r, color.g, color.b);
	// Tom's belly-ellipse
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + b2Vec2(3.0f*cosf(theta), 2.0f*sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	// Tom's face
    // outlint circle of redius=1
	glBegin(GL_LINE_LOOP);
	b2Vec2 scenter;
	scenter.x=center.x + 2.828f;
	scenter.y=center.y + 2.121f;
	theta = 0.0f;
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = scenter + b2Vec2(cosf(theta),sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	//nose and eyes
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2f(scenter.x, scenter.y);
    glVertex2f(scenter.x-0.5f,scenter.y+0.5f );
    glVertex2f(scenter.x+0.5f,scenter.y+0.5f );
    glEnd();
      
    //mouth
    glBegin(GL_LINE_LOOP);
    glVertex2f(scenter.x-0.5f,scenter.y-0.5f);
    glVertex2f(scenter.x-0.16f,scenter.y-0.6f);
    glVertex2f(scenter.x+0.16f,scenter.y-0.6f);
    glVertex2f(scenter.x+0.5f,scenter.y-0.5f);
    glEnd();
    //ears
    glBegin(GL_LINE_LOOP);
    glVertex2f(scenter.x+0.866f,scenter.y+0.5f);
    glVertex2f(scenter.x+1.2020f,scenter.y+1.2020f);
    glVertex2f(scenter.x+0.5f,scenter.y+0.866f);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(scenter.x-0.866f,scenter.y+0.5f);
    glVertex2f(scenter.x-1.2020f,scenter.y+1.2020f);
    glVertex2f(scenter.x-0.5f,scenter.y+0.866f);
    glEnd();
    //tail
    glBegin(GL_LINE_LOOP);
    b2Vec2 tcenter;
	tcenter.x=center.x - 4.7f;
	tcenter.y=center.y;
    theta = 0.0f;
    for (int32 i = 0; i < 14.0f; ++i)
	{
		b2Vec2 v = tcenter + b2Vec2(1.7f*cosf(theta), 0.5f*sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	//legs
	glBegin(GL_LINES);
    glVertex2f(center.x-1.13f,center.y-0.5f);
    glVertex2f(center.x-1.13f,center.y-3.5f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(center.x-2.121f,center.y-1.414f);
    glVertex2f(center.x-2.121f,center.y-3.5f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(center.x+2.121f,center.y-1.414f);
    glVertex2f(center.x+2.121f,center.y-3.5f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(center.x+1.5f,center.y-0.90f);
    glVertex2f(center.x+6.0f,center.y-0.90f);
    glEnd();
    glDisable(GL_BLEND);
}

//Jerry-The genius rat
void debug_draw_t::DrawJerry(const b2Color& color)
{
	b2Vec2 center;
	center.x=42.0f;
	center.y=12.7f;
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	//glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(color.r, color.g, color.b);
	// Jerry's face
	// outlint circle of redius=1
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + b2Vec2(cosf(theta),sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();	
    //nose and eyes
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2f(center.x, center.y);
    glVertex2f(center.x-0.5f,center.y+0.5f );
    glVertex2f(center.x+0.5f,center.y+0.5f );
    glEnd();
    //ears
	glBegin(GL_LINE_LOOP);
	b2Vec2 recenter;
	recenter.x=center.x + 1.007f;
	recenter.y=center.y + 1.007f;
	theta = 0.0f;
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = recenter + b2Vec2(0.3f*cosf(theta), 0.3f*sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	recenter.x=center.x - 1.007f;
	theta = 0.0f;
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = recenter + b2Vec2(0.3f*cosf(theta), 0.3f*sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	//mouth
    glBegin(GL_LINE_LOOP);
    glVertex2f(center.x-0.5f,center.y-0.5f);
    glVertex2f(center.x-0.16f,center.y-0.6f);
    glVertex2f(center.x+0.16f,center.y-0.6f);
    glVertex2f(center.x+0.5f,center.y-0.5f);
    glEnd();
    //Jerry's belly
    glBegin(GL_LINE_LOOP);
    glVertex2f(center.x,center.y-1.0f);
    glVertex2f(center.x+1.0f,center.y-1.0f);
    glVertex2f(center.x+1.0f,center.y-3.5f);
    glVertex2f(center.x-1.0f,center.y-3.5f);
    glVertex2f(center.x-1.0f,center.y-1.0f);
    glVertex2f(center.x,center.y-1.0);
    glEnd();
    //hands
    glBegin(GL_LINE_LOOP);
    glVertex2f(center.x+1.0f,center.y-2.0f);
    glVertex2f(center.x+1.5,center.y-2.0f);
    glVertex2f(center.x+1.5f,center.y-2.5f);
    glVertex2f(center.x+1.0f,center.y-2.5f);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(center.x-1.0f,center.y-2.0f);
    glVertex2f(center.x-1.5,center.y-2.0f);
    glVertex2f(center.x-1.5f,center.y-2.5f);
    glVertex2f(center.x-1.0f,center.y-2.5f);
    glEnd();
    //Jerry's legs
    glBegin(GL_LINE_LOOP);
    glVertex2f(center.x,center.y-3.0f);
    glVertex2f(center.x,center.y-3.4f);
    glVertex2f(center.x+1.0f,center.y-3.4f);
    glVertex2f(center.x+1.0f,center.y-3.0f);
    glVertex2f(center.x-1.0f,center.y-3.0f);
    glVertex2f(center.x-1.0f,center.y-3.4f);
    glVertex2f(center.x,center.y-3.4f);
    glEnd();
	//tail
    glBegin(GL_LINE_LOOP);
    b2Vec2 tcenter;
	tcenter.x=center.x + 1.65f;
	tcenter.y=center.y - 2.5f;
    theta = 0.0f;
    for (int32 i = 0; i < 14.0f; ++i)
	{
		b2Vec2 v = tcenter + b2Vec2(0.65f*cosf(theta), 0.3f*sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	//glDisable(GL_BLEND);
}
void debug_draw_t::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
}

void debug_draw_t::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	glDisable(GL_BLEND);

	theta = 0.0f;
	glColor4f(color.r, color.g, color.b, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();

	b2Vec2 p = center + radius * axis;
	glBegin(GL_LINES);
	glVertex2f(center.x, center.y);
	glVertex2f(p.x, p.y);
	glEnd();
}

void debug_draw_t::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}

void debug_draw_t::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;
	glBegin(GL_LINES);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(p1.x, p1.y);
	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	glVertex2f(p2.x, p2.y);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(p1.x, p1.y);
	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	glVertex2f(p2.x, p2.y);

	glEnd();
}

void debug_draw_t::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(p.x, p.y);
	glEnd();
	glPointSize(1.0f);
}

void debug_draw_t::DrawString(int x, int y, const char *string, ...)
{
	char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.9f, 0.6f, 0.6f);
	glRasterPos2i(x, y);
	int32 length = (int32)strlen(buffer);
	for (int32 i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void debug_draw_t::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	glColor3f(c.r, c.g, c.b);
	glBegin(GL_LINE_LOOP);
	glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
	glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
	glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
	glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
	glEnd();
}
