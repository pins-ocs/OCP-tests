/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_UserFunctions.cc        |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "ICLOCS_MinimumFuelOrbitRaising.hh"
#include "ICLOCS_MinimumFuelOrbitRaising_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


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


namespace ICLOCS_MinimumFuelOrbitRaisingDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  ICLOCS_MinimumFuelOrbitRaising::mass( real_type xo__t ) const {
    real_type result__ = -xo__t * ModelPars[iM_md] + 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mass( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_MinimumFuelOrbitRaising::mass_D( real_type xo__t ) const {
    real_type result__ = -ModelPars[iM_md];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mass_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_MinimumFuelOrbitRaising::mass_DD( real_type xo__t ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mass_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_UserFunctions.cc
