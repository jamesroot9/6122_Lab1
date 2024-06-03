/*
Author: James Root
Class: ECE 6122 R
Last Date Modified: 9/19/23

Description:

Derived class of PointCharge, adds functionality of computing the electric field given a certain point.

*/

#include <cmath>
#include <iostream>
#include "ECE_PointCharge.h"

using namespace std;

class ECE_ElectricField : public ECE_PointCharge
{
protected:
    double Ex; // Electric field in the x direction
    double Ey; // Electric field in the y direction
    double Ez; // Electric field in the z direction
public:
    ECE_ElectricField(); // default constructor
    ECE_ElectricField(double Ex, double Ey, double Ez); // verbose constructor

    ~ECE_ElectricField();

    void computeFieldAt(double x, double y, double z);
    void getElectricField(double &Ex, double &Ey, double &Ez);
};

