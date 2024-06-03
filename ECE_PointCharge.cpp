/*
Author: James Root
Class: ECE 6122 R
Last Date Modified: 9/19/23

Description:

Implementations of constuctors and methods for the PointCharge class

*/

#include "ECE_PointCharge.h"

/******************************************************************/
// Default Constructor
/******************************************************************/
ECE_PointCharge::ECE_PointCharge() : x(0.0), y(0.0), z(0.0), q(0.0)
{

}

/******************************************************************/
// Constructor with default position
/******************************************************************/
ECE_PointCharge::ECE_PointCharge(double q) : x(0.0), y(0.0), z(0.0)
{
    this->q = q;
}

/******************************************************************/
// Constructor with default charge
/******************************************************************/
ECE_PointCharge::ECE_PointCharge(double x, double y, double z) : q(0.0)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

/******************************************************************/
// Constructor with default charge
/******************************************************************/
ECE_PointCharge::ECE_PointCharge(double x, double y, double z, double q)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->q = q;
}

/******************************************************************/
// Deconstructor
/******************************************************************/
ECE_PointCharge::~ECE_PointCharge()
{
    // leave empty
}

/******************************************************************/
// sets the location of the point charge
/******************************************************************/
void ECE_PointCharge::setLocation(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

/******************************************************************/
// sets the charge of the point charge
/******************************************************************/
void ECE_PointCharge::setCharge(double q)
{
    this->q = q;
}
