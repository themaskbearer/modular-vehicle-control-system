/*
 * MatrixOperations.h
 *
 *  Created on: Jun 19, 2018
 *      Author: jpollard
 */

#ifndef SRC_UTILS_MATRIXOPERATIONS_H_
#define SRC_UTILS_MATRIXOPERATIONS_H_

#include <vector>

namespace matrix
{

typedef std::vector<float> Matrix;

Matrix createRotationMatrix(float a, float b, float g);
Matrix multiplyRMatrix(Matrix R, Matrix Rb);
Matrix multiplyPosition(Matrix R, Matrix p);

}




#endif /* SRC_UTILS_MATRIXOPERATIONS_H_ */
