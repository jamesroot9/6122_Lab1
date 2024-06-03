/*
Author: James Root
Class: ECE 6122 R
Last Date Modified: 9/25/23

Description:

This file serves as the main function to utilize 
the ElectricField and PointCharge classes via user
inputs.

*/

#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <cmath>

#include "ECE_ElectricField.h"

using namespace std;


/******************************************************************/
// Prompts user for inputs regarding matrix size, xy separation,
// and charge values. 
/******************************************************************/
void matrixInputs (int *n, int *m, double *xSep, double *ySep, double *q)
{
    int numThreads = thread::hardware_concurrency(); // defines number of threads supported by system
    string nValue, mValue;       // defines the amount of rows in columns desired
    string xSepValue, ySepValue; // defines the separation distances between x and y
    string commCharge;           // defines the charge of threads
    while (true)
    {
        // ask user for charge point to input

        // take in user inputs for n, m, xSeparation, ySeparation, and q
        std::cout << "Your computer supports " << numThreads << " concurrent threads.\n";
        std::cout << "Please enter the number of rows and columns in the N x M array: ";
        std::cin >> nValue >> mValue;

        // check for valid inputs and convert to numerical variables
        // check correctN
        bool correctNM = true;
        for (int i = 0; i < nValue.length(); i++)
        {
            // check for non digit values
            if (!isdigit(nValue[i]))
            {
                correctNM = false;
                break;
            }
        }
        for (int i = 0; i < mValue.length(); i++)
        {
            // check for non digit values
            if (!isdigit(mValue[i]))
            {
                correctNM = false;
                break;
            }
        }

        // check if we had correct formatting
        if (correctNM)
        {
            // if so, convert values to variables
            *n = stoi(nValue);
            *m = stoi(mValue);
        }
        else
        {
            // if not, let users know requirements and attempt value input again.
            cout << "N, M must be natural numbers. Please try input again.\n\n";
            continue;
        }

        std::cout << "Please enter the x and y separation distances in meters: ";
        std::cin >> xSepValue >> ySepValue;

        // check for valid inputs and convert to numerical variables
        // check correctN
        bool correctXY = true;

        // bool for use of one digit
        bool singleDigit = true;
        for (int i = 0; i < xSepValue.length(); i++)
        {
            // check for non digit values, allow use of period one time
            if (!(isdigit(xSepValue[i]) || (xSepValue[i] == '.' && singleDigit)))
            {
                correctXY = false;
                break;
            }

            // if there was a digit used, flag so another will not be
            if (xSepValue[i] == '.')
            {
                singleDigit = false;
            }
        }
        singleDigit = true;
        for (int i = 0; i < ySepValue.length(); i++)
        {

            // check for non digit values
            if (!(isdigit(ySepValue[i]) || (ySepValue[i] == '.' && singleDigit)))
            {
                correctXY = false;
                break;
            }

            // if there was a digit used, flag so another wont be
            if (ySepValue[i] == '.')
            {
                singleDigit = false;
            }
        }

        // check if we had correct formatting
        if (correctXY)
        {
            // if so, convert values to variables
            *xSep = stod(xSepValue);
            *ySep = stod(ySepValue);
        }
        else
        {
            // if not, let users know requirements and attempt value input again.
            std::cout << "The separation between x & y values must be natural numbers. Please try again.\n\n";
            continue;
        }

        std::cout << "Please enter the common charge on the points in micro C: ";
        std::cin >> commCharge;

        // check for valid inputs and convert to numerical variables
        // check C
        bool correctC = true;

        // bool for use of one digit
        singleDigit = true;
        for (int i = 0; i < commCharge.length(); i++)
        {
            // check for non digit values, allow use of period one time
            if (!(isdigit(commCharge[i]) || (commCharge[i] == '.' && singleDigit) || (commCharge[i] == '-' && i == 0)))
            {
                correctC = false;
                break;
            }

            // if there was a digit used, flag so another will not be
            if (commCharge[i] == '.')
            {
                singleDigit = false;
            }
        }

        // check if we had correct formatting
        if (correctC)
        {
            // if so, convert values to variables
            *q = stod(commCharge);
        }
        else
        {
            // if not, let users know requirements and attempt value input again.
            cout << "The charge value must be a natural number. Please try again.\n\n";
            continue;
        }
        return;
    }
}

/******************************************************************/
// calculates the EF for a specific thread k in list of mod thread
/******************************************************************/
void calculateEFbyIDX(std::vector<std::vector<ECE_ElectricField> > &nmMatrix, unsigned int k, unsigned int mod, double x, double y, double z)
{
    // iterate through each element in the matrix
    for (int i = 0; i < nmMatrix.size(); i++)
    {
        for (int j = 0; j < nmMatrix[i].size(); j++) 
        {
            // calculate electric field for only the items required for the thread (idx number % mod == k)
            if ((i * nmMatrix[i].size() + j) % mod == k)
            {
                nmMatrix[i][j].computeFieldAt(x, y, z);
            }
        }
    }
}

int main()
{
    string xValue, yValue, zValue;                      // defines the xyz pair values
    int n, m;                                           // values derived from nmValue
    double xSep, ySep;                                  // values derived from xySeparation
    double q;                                           // value derived from commCharge
    double x, y, z;                                     // value derived from xyzValue
    bool singleDigit;

    // gather inputs for the matrix values
    matrixInputs(&n, &m, &xSep, &ySep, &q);

    // Iterate loop until proper inputs are given for nmValue, xySeparation, and commCharge are given.
    while (true)
    {
        // take location input and analyze
        std::cout << "\nPlease enter the location in space to determine the electric field (x y z) in meters: ";
        std::cin >> xValue >> yValue >> zValue;

        // begin count for calculations
        auto start = std::chrono::high_resolution_clock::now();

        // check for valid inputs and convert to numerical variables
        // check correctN
        bool correctXYZ = true;

        // bool for use of one digit
        bool singleDigit = true;
        for (int i = 0; i < xValue.length(); i++)
        {
            // check for non digit values, allow use of period one time
            if (!(isdigit(xValue[i]) || (xValue[i] == '.' && singleDigit)))
            {
                correctXYZ = false;
                break;
            }

            // if there was a digit used, flag so another will not be
            if (xValue[i] == '.')
            {
                singleDigit = false;
            }
        }
        singleDigit = true;
        for (int i = 0; i < yValue.length(); i++)
        {

            // check for non digit values
            if (!(isdigit(yValue[i]) || (yValue[i] == '.' && singleDigit)))
            {
                correctXYZ = false;
                break;
            }

            // if there was a digit used, flag so another wont be
            if (yValue[i] == '.')
            {
                singleDigit = false;
            }
        }
        singleDigit = true;
        for (int i = 0; i < zValue.length(); i++)
        {

            // check for non digit values
            if (!(isdigit(zValue[i]) || (zValue[i] == '.' && singleDigit)))
            {
                correctXYZ = false;
                break;
            }

            // if there was a digit used, flag so another wont be
            if (zValue[i] == '.')
            {
                singleDigit = false;
            }
        }

        // check if we had correct formatting
        if (correctXYZ)
        {
            // if so, convert values to variables
            x = stod(xValue);
            y = stod(yValue);
            z = stod(zValue);
        }
        else
        {
            // if not, let users know requirements and attempt value input again.
            std::cout << "The x, y, and z values must be natural numbers. Please try again.\n\n";
            continue;
        }

        // Establish matrix

        // calculate the position of the leftmost element
        double x0 = -1 * (n - 1) * xSep / 2;
        double y0 = (m - 1) * ySep / 2;

        // create matrix to populate values with
        std::vector<std::vector<ECE_ElectricField> > nmMatrix(n, std::vector<ECE_ElectricField>(m));

        // establish (0, 0) to be at (x0, y0) (top left of matrix)
        // increment other values based position w.r.t (x0, y0) with xSep and ySep
        // increment on x axis
        for (int i = 0; i < n; i++)
        {
            //increment on y axis
            for (int j = 0; j < m; j++)
            {
                // initialize electric field object
                nmMatrix[i][j] = ECE_ElectricField();

                // set the charge of this object
                nmMatrix[i][j].setCharge(q);

                // set the position of the object dependent on the positioning in the grid
                nmMatrix[i][j].setLocation(x0 + xSep * i, y0 - ySep * j, 0);
            }
        }


        // optimize thread number if there are less operations needed than threads
        int num_threads = thread::hardware_concurrency() < n * m ? thread::hardware_concurrency() : n * m;

        // iterate through number of threads
        vector<thread> threads;
        for (int i = 0; i < num_threads; i++)
        {
            // call lambda function that makes each thread call the calculate EF function
            threads.emplace_back([&nmMatrix, i, num_threads, x, y, z]()
            {  
                calculateEFbyIDX(nmMatrix, i, num_threads, x, y, z);  
            });
        }

        // iterate through all threads and join back to our solution
        for (int i = 0; i < num_threads; i++)
        {
            threads[i].join();
        }

        // declare counter variables
        double Ex = 0, Ey = 0, Ez = 0;
        // iterate through each item in the nmMatrix to add up EF values
        for (int i = 0; i < nmMatrix.size(); i++)
        {
            for (int j = 0; j < nmMatrix[i].size(); j++)
            {
                // add up all electric fields
                nmMatrix[i][j].getElectricField(Ex, Ey, Ez);
            }
        }

        cout.precision(5);
        // begin print of calculated values
        cout << "The electric field at (" << double(x) << ", " << y << ", " << z << ") in V/m is\n";
        // print Ex
        cout << "Ex = " << Ex / pow(10, floor(log10(abs(Ex)))) << " * 10^" << floor(log10(abs(Ex))) << "\n";
        // print Ey
        cout << "Ey = " << Ey / pow(10, floor(log10(abs(Ey)))) << " * 10^" << floor(log10(abs(Ey))) << "\n";
        // print Ez
        cout << "Ez = " << Ez / pow(10, floor(log10(abs(Ez)))) << " * 10^" << floor(log10(abs(Ez))) << "\n";

        double absE = sqrt(pow(Ex, 2.0) + pow(Ey, 2.0) + pow(Ez, 2.0));
        // print |E|
        cout << "|E| = " << absE / pow(10, floor(log10(absE))) << " * 10^" << floor(log10(absE)) << "\n";

        // finish timing
        auto finish = std::chrono::high_resolution_clock::now();
        // calculate and print calculation time 
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
        cout << "The calculation took " << duration.count() << " nmicrosec!\n";
        // check if user would like to have a new location
        string yn;
        while (true)
        {
            std::cout << "Do you want to enter a new location (Y/N)? ";
            std::cin >> yn;
            //check for y or Y given (valid yes)
            if (yn == "y" || yn == "Y")
            {
                break; //repeat loop
            }
            // check for n or N given (valid no)
            else if (yn == "n" || yn == "N")
            {
                std::cout << "Bye!\n";
                return 0; // end function
            }
        }
    }

    return 0;
}