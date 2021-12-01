//
//  DrawBasket.cpp
//
//  Created by Kenny Jiang on 11/20/21.
//

#include "DrawBasket.h"
#include "fssimplewindow.h"
#include <math.h>
#define Pi 3.14159265

void Basket::DrawGround()
{
    glColor3ub(75, 60, 10);
    glBegin(GL_QUADS);
    glVertex2i(0, 700);
    glVertex2i(1300, 700);
    glVertex2i(1300, 800);
    glVertex2i(0, 800);
    glEnd();
}




void Basket::DrawInner()
{
    // Bottom
    glColor3ub(61, 137, 212);
    glBegin(GL_QUADS);
    glVertex2i(490, 650);
    glVertex2i(810, 650);
    glVertex2i(810, 660);
    glVertex2i(490, 660);
    glEnd();
    
    // Lower-Left corner
    glBegin(GL_TRIANGLE_FAN);
    int RL = 10;
    for(int i=0; i<180; i += 1)
    {
        double a=(double)i*Pi/180.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(490+c*RL, 650+s*RL);
    }
    glEnd();
    
    // Left wall
    glBegin(GL_QUADS);
    glVertex2i(490, 650);
    glVertex2i(480, 650);
    glVertex2i(480, 240);
    glVertex2i(490, 240);
    glEnd();
    
    
    // Lower-Right corner
    glBegin(GL_TRIANGLE_FAN);
    int RR = 10;
    for(int i=0; i<180; i += 1)
    {
        double a=(double)i*Pi/180.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(810+c*RR, 650+s*RR);
    }
    glEnd();
    
    
    // Right wall
    glBegin(GL_QUADS);
    glVertex2i(810, 650);
    glVertex2i(820, 650);
    glVertex2i(820, 240);
    glVertex2i(810, 240);
    glEnd();
    
    
    //Top part/lid
    glBegin(GL_QUADS);
    glVertex2i(480, 240);
    glVertex2i(480, 230);
    glVertex2i(820, 230);
    glVertex2i(820, 240);
    glEnd();
    
}


void Basket::DrawScale()
{
    glColor3ub(170, 170, 170);
    glBegin(GL_QUADS);
    
    for(int i=290; i<650; i += 60)
    {
        glVertex2i(700, i);
        glVertex2i(700, i+10);
        glVertex2i(780, i+10);
        glVertex2i(780, i);
    }
    glEnd();
}

void Basket::FillColor()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor3ub(135, 195, 255);
    glBegin(GL_QUADS);
    glVertex2i(450, 185);
    glVertex2i(450, 690);
    glVertex2i(480, 690);
    glVertex2i(480, 185);
    glEnd();
    glDisable(GL_BLEND);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor3ub(135, 195, 255);
    glBegin(GL_QUADS);
    glVertex2i(820, 660);
    glVertex2i(820, 690);
    glVertex2i(480, 690);
    glVertex2i(480, 660);
    glEnd();
    glDisable(GL_BLEND);
    
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor3ub(135, 195, 255);
    glBegin(GL_QUADS);
    glVertex2i(820, 690);
    glVertex2i(850, 690);
    glVertex2i(850, 185);
    glVertex2i(820, 185);
    glEnd();
    glDisable(GL_BLEND);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor3ub(135, 195, 255);
    glBegin(GL_QUADS);
    glVertex2i(480, 185);
    glVertex2i(480, 230);
    glVertex2i(820, 230);
    glVertex2i(820, 185);
    glEnd();
    glDisable(GL_BLEND);
}




void Basket::DrawBasket()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    
    // Bottom
    glColor3ub(61, 137, 212);
    glBegin(GL_QUADS);
    glVertex2i(450, 690);
    glVertex2i(850, 690);
    glVertex2i(850, 700);
    glVertex2i(450, 700);
    glEnd();
    
    // Lower-Left corner
    glBegin(GL_TRIANGLE_FAN);
    int RL = 10;
    for(int i=0; i<180; i += 1)
    {
        double a=(double)i*Pi/180.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(450+c*RL, 690+s*RL);
    }
    glEnd();
    
    // Left wall
    glBegin(GL_QUADS);
    glVertex2i(450, 690);
    glVertex2i(440, 690);
    glVertex2i(440, 200);
    glVertex2i(450, 200);
    glEnd();
    
    // Lower-Right corner
    glBegin(GL_TRIANGLE_FAN);
    int RR = 10;
    for(int i=0; i<180; i += 1)
    {
        double a=(double)i*Pi/180.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(850+c*RR, 690+s*RR);
    }
    glEnd();
    
    
    glBegin(GL_QUADS);
    glVertex2i(850, 690);
    glVertex2i(860, 690);
    glVertex2i(860, 200);
    glVertex2i(850, 200);
    glEnd();
    
    // Right corner
    glBegin(GL_TRIANGLE_FAN);
    int rL = 25;
    for(int i=90; i<270; i += 1)
    {
        double a=(double)i*Pi/180.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(450+c*rL, 200+s*rL);
    }
    glEnd();
    

    glBegin(GL_TRIANGLE_FAN);
    int rr = 25;
    for(int i=270; i<450; i += 1)
    {
        double a=(double)i*Pi/180.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(850+c*rr, 200+s*rr);
    }
    glEnd();
    
    //Top part
    glBegin(GL_QUADS);
    glVertex2i(450, 185);
    glVertex2i(450, 175);
    glVertex2i(850, 175);
    glVertex2i(850, 185);
    glEnd();
    
    
    //glColor3ub(255, 255, 255);
    glColor3ub(135, 195, 255);
    glBegin(GL_TRIANGLE_FAN);
    int rLw = 15;
    for(int i=90; i<270; i += 1)
    {
        double a=(double)i*Pi/180.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(450+c*rLw, 200+s*rLw);
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    int rrw = 15;
    for(int i=270; i<450; i += 1)
    {
        double a=(double)i*Pi/180.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(850+c*rrw, 200+s*rrw);
    }
    glEnd();
    
    
    DrawInner();
    DrawScale();
    FillColor();
}
