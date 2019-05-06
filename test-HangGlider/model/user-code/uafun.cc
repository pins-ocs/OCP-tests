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

  using namespace std;
  using namespace MechatronixLoad;
  
  static real_type uM = 2.5;
  static real_type R  = 100;

  real_type
  HangGlider::ua( real_type x ) const {
    real_type X = power2(x/R-2.5);
    return uM*(1-X)*exp(-X);
  }

  real_type
  HangGlider::ua_D( real_type x ) const {
    real_type X   = power2(x/R-2.5);
    real_type X_D = (x/R-2.5)*2/R;
    return (uM*(X-2)*exp(-X))*X_D;
  }
  
  real_type
  HangGlider::ua_DD( real_type x ) const {
    real_type X    = power2(x/R-2.5);
    real_type X_DD = 2/(R*R);
    return -(uM*(X-3)*exp(-X))*X_DD;
  }

}
