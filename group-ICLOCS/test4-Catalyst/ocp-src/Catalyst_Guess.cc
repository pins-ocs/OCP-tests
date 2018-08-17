/*-----------------------------------------------------------------------*\
 |  file: Catalyst_Guess.cc                                              |
 |                                                                       |
 |  version: 1.0   date 17/8/2018                                        |
 |                                                                       |
 |  Copyright (C) 2018                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "Catalyst.hh"
#include "Catalyst_Pars.hh"

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wunused-macros"
#elif defined(__llvm__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-macros"
#elif defined(_MSC_VER)
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#endif


// map user defined functions and objects with macros
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)



namespace CatalystDefine {

  using namespace std;

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  Catalyst::guess_eval( indexType            numNodes,
                        Q_const_pointer_type _q,
                        Z_pointer_type       _z,
                        P_pointer_type       _p,
                        OMEGA_pointer_type   _omega ) const {
    valueConstPointer q = _q.pointer();
    valuePointer      z = _z.pointer();
    valuePointer      p = _p.pointer();
    valuePointer  omega = _omega.pointer();
    // initialize parameters (if any)
        

    // initialize states and multiplier
    indexType numZvars = 2 * numXvars;
    std::fill( z, z+numNodes*numZvars, 0 );
    for ( indexType i = 0; i < numNodes; ++i ) {
      valuePointer      X__ = z + i * numZvars;
      valuePointer      L__ = X__ + numXvars;
      valueConstPointer Q__ = q + i * numQvars;
      // modify the following code if necessary
      indexType i_segment = indexType(pMesh->nodeToSegment(i));
      MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
      
      X__[ iX_x1 ] = ModelPars[iM_x1_i];
      X__[ iX_x2 ] = ModelPars[iM_x2_i];

      

    }
    // initialize boundary multiplier
    for ( indexType i = 0; i < numOMEGAvars; ++i ) omega[i] = 0;
  }

  /*\
   |    ____ _               _
   |   / ___| |__   ___  ___| | __
   |  | |   | '_ \ / _ \/ __| |/ /
   |  | |___| | | |  __/ (__|   <
   |   \____|_| |_|\___|\___|_|\_\
  \*/

  #define Xoptima__check__lt(A,B,MSG) ASSERT( (A) <  (B), MSG )
  #define Xoptima__check__le(A,B,MSG) ASSERT( (A) <= (B), MSG )
  void
  Catalyst::check_if_admissible( indexType                numNodes,
                                 Q_const_pointer_type     _q,
                                 Z_const_pointer_type     _z,
                                 P_const_pointer_type     _p,
                                 OMEGA_const_pointer_type _omega ) const {
    indexType i;
    indexType numZvars = 2 * numXvars;
    valueConstPointer q       = _q.pointer();
    valueConstPointer z       = _z.pointer();
    valueConstPointer P__     = _p.pointer();
    valueConstPointer OMEGA__ = _omega.pointer();
  }
}

// EOF: Catalyst_Guess.cc
