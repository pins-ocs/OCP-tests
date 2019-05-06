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

#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

namespace Brachiostocrona2Define {

  using namespace std;

  real_type
  Brachiostocrona2::arctan2( real_type y, real_type x ) const {
    return Mechatronix::arctan2( y, x );
  }

  real_type
  Brachiostocrona2::arctan2_D_1( real_type y, real_type x ) const {
    real_type sx = 1, ax = x;
    if ( x < 0 ) { sx = -1; ax = -x; }
    return sx/(ax+y*y/(ax+1e-10));
  }

  real_type
  Brachiostocrona2::arctan2_D_2( real_type y, real_type x ) const {
    real_type sy = 1, ay = y;
    if ( y < 0 ) { sy = -1; ay = -y; }
    return -sy/(ay+x*x/(ay+1e-10));
  }

}
