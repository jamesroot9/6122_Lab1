/*
Author: James Root
Class: ECE 6122 R
Last Date Modified: 9/25/23

Description:

Implementation of ElectricField header

*/

#include "ECE_ElectricField.h"

/******************************************************************/
// Default Constructor
/******************************************************************/
ECE_ElectricField::ECE_ElectricField() : Ex(0.0), Ey(0.0), Ez(0.0)
{
}
/******************************************************************/
// Default Constructor
/******************************************************************/
ECE_ElectricField::~ECE_ElectricField()
{

}

/******************************************************************/
// Constructor with default position
/******************************************************************/
ECE_ElectricField::ECE_ElectricField(double Ex, double Ey, double Ez)
{
    this->x = Ex;
    this->y = Ey;
    this->z = Ez;
}

/******************************************************************/
// Calculates the electric field at the point xyz due to the charge.
// Updates Ex, Ey, and Ez member variables.
/******************************************************************/
void ECE_ElectricField::computeFieldAt(double x, double y, double z)
{
    double r = pow(x - this->x, 2.0) + pow(y - this->y, 2.0) + pow(z - this->z, 2.0);
    double k = 9000; // Nm^2 / mC^2
    this->Ex = k * this->q * (x - this->x) / pow(r, 1.5);
    this->Ey = k * this->q * (y - this->y) / pow(r, 1.5);
    this->Ez = k * this->q * (z - this->z) / pow(r, 1.5);
    return;
}

/******************************************************************/
// Updates the inputs with the values at Ex, Ey, Ez
/******************************************************************/
void ECE_ElectricField::getElectricField(double &Ex, double &Ey, double &Ez)
{
    Ex = Ex + this->Ex;
    Ey = Ey + this->Ey;
    Ez = Ez + this->Ez;
    return;
}