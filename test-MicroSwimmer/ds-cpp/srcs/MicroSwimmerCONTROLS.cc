/*--------------------------------------------------------------------------*\
 |  file: MicroSwimmerODE.cc                                                |
 |                                                                          |
 |  version: 1.0   date 2/3/2016                                            |
 |                                                                          |
 |  Copyright (C) 2016                                                      |
 |                                                                          |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti                |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      Via Sommarive 9, I-38123, Trento, Italy                             |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |             francesco.biral@unitn.it                                     |
 |             paolo.bosetti@unitn.it                                       |
\*--------------------------------------------------------------------------*/


#include "MicroSwimmerODE.hh"
#include "MicroSwimmerODE_Pars.hh"

namespace MicroSwimmerODEDefine {

  // user functions prototype (with derivative)
  valueType const tswitch = m_pi/3 ;
  
  valueType
  MicroSwimmerODE::u1loop( valueType t ) const {
    int tint = int(t/tswitch) % 4 ;
    switch (tint) {
      case 0: return tswitch  ;
      case 1: return 0  ;
      case 2: return -tswitch ;
      case 3: return 0  ;
    }
    return 0 ;
  }

  valueType MicroSwimmerODE::u1loop_D( valueType t ) const { return 0 ; }

  valueType MicroSwimmerODE::u1loop_DD( valueType t ) const { return 0 ; }

  valueType
  MicroSwimmerODE::u3loop( valueType t ) const {
    int tint = int(t/tswitch) % 4 ;
    switch (tint) {
      case 0: return 0  ;
      case 1: return -tswitch ;
      case 2: return 0  ;
      case 3: return tswitch  ;
    }
    return 0 ;
  }

  valueType MicroSwimmerODE::u3loop_D  ( valueType t ) const { return 0 ; }

  valueType MicroSwimmerODE::u3loop_DD ( valueType t ) const { return 0 ; }

}
