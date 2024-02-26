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

namespace Train {

  using namespace std;
  using namespace MechatronixLoad;

  static real_type epsilon = 0.05;
  static real_type ss[3] = { -2, 0, 2 };
  static real_type zz[2] = { 2, 4 };

  static integer n_zz = integer(sizeof(zz)/sizeof(zz[0]));

  real_type
  Train::h( real_type x ) const {
    real_type res = 0;
    for ( integer j = 0; j < n_zz; ++j )
      res += (ss[j+1]-ss[j])*atan((x-zz[j])/epsilon);
    return res / m_pi;
  }

  real_type
  Train::h_D( real_type x ) const {
    real_type res = 0;
    for ( integer j = 0; j < n_zz; ++j )
      res += (ss[j+1]-ss[j])/(1+power2((x-zz[j])/epsilon));
    return res / m_pi / epsilon;
  }

  real_type
  Train::h_DD( real_type x ) const {
    real_type res = 0;
    for ( integer j = 0; j < n_zz; ++j ) {
      real_type dz  = x-zz[j];
      real_type dz2 = power2(dz/epsilon);
      res += (ss[j+1]-ss[j])*dz/power2(1+dz2);
    }
    return -2 * res / m_pi / epsilon / epsilon/ epsilon;
  }
}
