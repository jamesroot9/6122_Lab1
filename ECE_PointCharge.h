/*
Author: James Root
Class: ECE 6122 R
Last Date Modified: 9/19/23

Description:

Header file for the ECE_PointCharge class, which 
represents a point charge on an item with both
a 3-D position and charge in micro C.

*/

#include <iostream>
using namespace std;

class ECE_PointCharge
{
protected:
    double x; // x coordinate
    double y; // y coordiate
    double z; // z coordinate
    double q; // charge of the point
public:
    ECE_PointCharge();                              // default constructor
    explicit ECE_PointCharge(double q);             // constructor
    ECE_PointCharge(double x, double y, double z);  // constructor
    ECE_PointCharge(double x, double y, double z, double q); // constructor
    ~ECE_PointCharge();

    // 
    void setLocation(double x, double y, double z);
    void setCharge(double q);
};