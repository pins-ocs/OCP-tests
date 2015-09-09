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

#include "HangGlider.hh"

namespace HangGliderDefine {

  using namespace std ;
  using namespace MechatronixCommon ;
  
  static valueType uM = 2.5 ;
  static valueType R  = 100 ;

  valueType
  HangGlider::ua( valueType x ) const {
    valueType X = power2(x/R-2.5) ;
    return uM*(1-X)*exp(-X) ;
  }

  valueType
  HangGlider::ua_D( valueType x ) const {
    valueType X   = power2(x/R-2.5) ;
    valueType X_D = (x/R-2.5)*2/R ;
    return (uM*(X-2)*exp(-X))*X_D ;
  }
  
  valueType
  HangGlider::ua_DD( valueType x ) const {
    valueType X    = power2(x/R-2.5) ;
    valueType X_DD = 2/(R*R) ;
    return -(uM*(X-3)*exp(-X))*X_DD ;
  }

}
