#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Matrix.hpp"
using namespace std;


void initializeRandomNumberGenerator(int seed = -1);
void proposeMCmoves(Matrix<double> &atom_positions, Matrix<double> &cell_vectors);
