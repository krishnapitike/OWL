#ifndef COMMUNICATIONS_HPP
#define COMMUNICATIONS_HPP

#include "mpi.h"
#include "Globals.hpp"
#include "TypeTraits.hpp"


class MPICommunicator {

public :

  MPI_Comm communicator;
  int      thisMPIrank;
  int      totalMPIranks;

  // member functions
  void initialize(MPI_Comm incomingComm);    // this initializes communicator to be the same as the incoming one
  void finalize();                           // this finalizes communicator

  void barrier();                            // calls MPI_Barrier for this communicator

  template<typename T> void swapScalar(T &data, int partner);
  template<typename T> void swapVector(T data[], int nElements, int partner);

  template<typename T> void sendScalar(T &data, int partner);
  template<typename T> void recvScalar(T &data, int partner);

  void swapVector(void* data_ptr, int nElements, MPI_Datatype MPI_config_type, int partner);

};


// Definitions of template functions for MPI communications

template <typename T>
void MPICommunicator::swapScalar(T &data, int partner) {

  MPI_Status status;
  MPI_Sendrecv_replace(&data, 1, TypeTraits<T>::MPItype(), partner, 1, partner, 1, communicator, &status);

}

template <typename T>
void MPICommunicator::swapVector(T data[], int nElements, int partner) {

  MPI_Status status;
  MPI_Sendrecv_replace(&data[0], nElements, TypeTraits<T>::MPItype(), partner, 1, partner, 1, communicator, &status);

}

template <typename T>
void MPICommunicator::sendScalar(T &data, int partner) {

  MPI_Send(&data, 1, TypeTraits<T>::MPItype(), partner, 3, communicator);

}

template <typename T>
void MPICommunicator::recvScalar(T &data, int partner) {

  MPI_Status status;
  MPI_Recv(&data, 1, TypeTraits<T>::MPItype(), partner, 3, communicator, &status);

}



//////////////////////////////////////////////////////////////////////////
/// YingWai: Should the following be moved to a new header file?
/// (Because I want this file to contain only the MPICommunicator class)
/// Sep 17, 2017


// Global variables for MPI communicators info
extern MPICommunicator GlobalComm;

// Functions
void initializeMPICommunication(MPICommunicator& PhysicalSystemComm, MPICommunicator& MCAlgorithmComm);
void finalizeMPICommunication();

// The following should be replaced once the MPI classes are ready? (Jun 14, 17)
void initializeQEMPICommunication();
void finalizeQEMPICommunication();



#endif