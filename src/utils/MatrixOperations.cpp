/*
 * MatrixOperations.cpp
 *
 *  Created on: Jun 19, 2018
 *      Author: jpollard
 */


#include "MatrixOperations.h"
#include <cmath>


namespace matrix
{

Matrix createRotationMatrix(float a, float b, float g)
{
    Matrix R;

    R.push_back(cos(a)*cos(b));
    R.push_back(cos(a)*sin(b)*sin(g) - sin(a)*cos(g));
    R.push_back(cos(a)*sin(b)*cos(g) + sin(a)*sin(g));

    R.push_back(sin(a)*cos(b));
    R.push_back(sin(a)*sin(b)*sin(g) + cos(a)*cos(g));
    R.push_back(sin(a)*sin(b)*cos(g) - cos(a)*sin(g));

    R.push_back(-sin(b));
    R.push_back(cos(b)*sin(g));
    R.push_back(cos(b)*cos(g));

    return R;
}


Matrix multiplyRMatrix(Matrix R, Matrix Rb)
{
    Matrix ReturnedMatrix(9, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                ReturnedMatrix[i*3 + j] += R[i*3 + k] * Rb[j + k*3];

    return ReturnedMatrix;
}


Matrix multiplyPosition(Matrix R, Matrix p)
{
    Matrix ReturnedMatrix(3, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            ReturnedMatrix[i] += R[i*3 + j] * p[j];

    return ReturnedMatrix;
}

}

