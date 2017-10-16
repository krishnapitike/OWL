#include <iostream>
#include "RandomNumberGenerator.hpp"


std::mt19937 rng;
//int RngSeed {-1};

void initializeRandomNumberGenerator(MPICommunicator phy_sys_comm, int RngSeed)
{
 
  // if random number seed is not supplied, get one from time 
  if (RngSeed == -1) {
    RngSeed = int(time(NULL));
    std::cout << "Rank: " << phy_sys_comm.thisMPIrank
              << " No random number seed supplied. Take current time as a seed.\n";
  }
  //else
    //std::cout << "Random number seed supplied: " << RngSeed << std::endl;

  // Make the seeds different for each walker
  if (phy_sys_comm.thisMPIrank == 0)
    RngSeed += GlobalComm.thisMPIrank;

  // Broadcast (synchronize) the random number seed within the same walker
  MPI_Bcast(&RngSeed, 1, MPI_INT, 0, phy_sys_comm.communicator);
  std::cout << "Rank: " << GlobalComm.thisMPIrank << " Random number seed supplied: " << RngSeed << std::endl;
  //std::cout << "Rank: " << phy_sys_comm.thisMPIrank << " Random number seed supplied: " << RngSeed << std::endl;

  // Initialize random number generators
  rng.seed(RngSeed);

}