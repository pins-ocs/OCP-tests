/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2007                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                |
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Meccanica e Strutturale                  |
 |      Universita` degli Studi di Trento                                   |
 |      Via Mesiano 77, I-38050 Trento, Italy                               |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

#include "Train.hh"

namespace TrainDefine {

  using namespace std ;
  using namespace MechatronixCommon ;
  
  static valueType epsilon = 0.05 ;
  static valueType ss[3] = { -2, 0, 2 } ;
  static valueType zz[2] = { 2, 4 } ;

  static indexType n_zz = indexType(sizeof(zz)/sizeof(zz[0])) ;

  valueType
  Train::h( valueType x ) const {
    valueType res = 0 ;
    for ( indexType j = 0 ; j < n_zz ; ++j )
      res += (ss[j+1]-ss[j])*atan((x-zz[j])/epsilon) ;
    return res / m_pi ;
  }

  valueType
  Train::h_D( valueType x ) const {
    valueType res = 0 ;
    for ( indexType j = 0 ; j < n_zz ; ++j )
      res += (ss[j+1]-ss[j])/(1+power2((x-zz[j])/epsilon)) ;
    return res / m_pi / epsilon ;
  }
  
  valueType
  Train::h_DD( valueType x ) const {
    valueType res = 0 ;
    for ( indexType j = 0 ; j < n_zz ; ++j ) {
      valueType dz  = x-zz[j] ;
      valueType dz2 = power2(dz/epsilon) ;
      res += (ss[j+1]-ss[j])*dz/power2(1+dz2) ;
    }
    return -2 * res / m_pi / epsilon / epsilon/ epsilon ;
  }
}
