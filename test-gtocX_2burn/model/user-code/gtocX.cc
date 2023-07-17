#include "gtocX.hh"

#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

namespace gtocX {

  // @@@@@@@@@@@@@@@@@@@@@@

  static real_type const k8 = -1.94316e-12;
  static real_type const k7 = 3.7516e-10;
  static real_type const k6 = -2.70559e-08;
  static real_type const k5 = 9.70521e-07;
  static real_type const k4 = -1.88428e-05;
  static real_type const k3 = 0.000198502;
  static real_type const k2 = -0.0010625;
  static real_type const k1 = 0.0023821;
  static real_type const k0 = 0.00287729;
  static real_type const kms_to_kpcMyr = 0.1022712165e-2; // 1e6*year/kpc;

  //static real_type const kpc  = 30856775814671900.0; // km per kpc
  //static real_type const year = 31557600.0;          // sec in a year
  //static real_type const kms_to_kpcMyr = 1e6*year/kpc;

  real_type
  vc( real_type r ) {
    real_type bot = k0+r*(k1+r*(k2+r*(k3+r*(k4+r*(k5+r*(k6+r*(k7+r*k8)))))));
    return kms_to_kpcMyr/bot;
  }

  real_type
  vc_D( real_type r ) {
    real_type bot   = k0+r*(k1+r*(k2+r*(k3+r*(k4+r*(k5+r*(k6+r*(k7+r*k8)))))));
    real_type bot_D = k1+r*(2*k2+r*(3*k3+r*(4*k4+r*(5*k5+r*(6*k6+r*(7*k7+r*8*k8))))));
    return -kms_to_kpcMyr*bot_D/(bot*bot);
  }

  real_type
  vc_DD( real_type r ) {
    real_type bot    = k0+r*(k1+r*(k2+r*(k3+r*(k4+r*(k5+r*(k6+r*(k7+r*k8)))))));
    real_type bot_D  = k1+r*(2*k2+r*(3*k3+r*(4*k4+r*(5*k5+r*(6*k6+r*(7*k7+r*8*k8))))));
    real_type bot_DD = 2*k2+r*(6*k3+r*(12*k4+r*(20*k5+r*(30*k6+r*(42*k7+r*56*k8)))));
    return kms_to_kpcMyr*(2*bot_D*bot_D/bot-bot_DD)/(bot*bot);
  }

  real_type
  muc( real_type R ) {
    real_type v = vc(R);
    return R*(v*v);
  }

  void
  starPV(
    Keplerian const & K0,
    real_type         t,
    real_type         PP[3],
    real_type         VV[3]
  ) {
    real_type R  = K0.a;
    real_type V  = vc(R);
    real_type n  = V/R;
    real_type nt = n*t+K0.omega;
    real_type CO = cos(K0.Omega);
    real_type SO = sin(K0.Omega);
    real_type CN = cos(nt);
    real_type SN = sin(nt);
    real_type Ci = cos(K0.i);
    real_type Si = sin(K0.i);

    PP[0] = R*(CN*CO-SN*SO*Ci);
    PP[1] = R*(CN*SO+SN*CO*Ci);
    PP[2] = R*(SN*Si);

    VV[0] = V*(-SN*CO-CN*SO*Ci);
    VV[1] = V*(-SN*SO+CN*CO*Ci);
    VV[2] = V*(CN*Si);
  }

  bool
  build_Lambert_guess(
    real_type     t0,
    Astro const & From,
    real_type     t1,
    Astro const & To,
    real_type     muS,
    Astro       & guess
  ) {
    dvec3_t P0, P1, V0, V1;
    integer m = 0;
    From.position( t0, P0 );
    To.position( t1, P1 );
    integer ok = AstroLib::Lambert( P0, P1, t1-t0, m, muS, V0, V1 );
    UTILS_ASSERT0( ok >= 0, "guess_setup, Lambert failed" );
    guess.setup_using_point_and_velocity( P0, V0, muS, t0 );
    return true;
  }

  bool
  build_Lambert_guess(
    real_type       t0,
    dvec3_t const & P0,
    real_type       t1,
    Astro const   & To,
    real_type       muS,
    Astro         & guess
  ) {
    dvec3_t P1, V0, V1;
    integer m = 0;
    To.position( t1, P1 );
    integer ok = AstroLib::Lambert( P0, P1, t1-t0, m, muS, V0, V1 );
    UTILS_ASSERT0( ok >= 0, "guess_setup, Lambert failed" );
    guess.setup_using_point_and_velocity( P0, V0, muS, t0 );
    return true;
  }

  /*\
   |       _       _        _
   |    __| | __ _| |_ __ _| |__   __ _ ___  ___
   |   / _` |/ _` | __/ _` | '_ \ / _` / __|/ _ \
   |  | (_| | (_| | || (_| | |_) | (_| \__ \  __/
   |   \__,_|\__,_|\__\__,_|_.__/ \__,_|___/\___|
   |
   |
   |   _ __ ___   __ _ _ __   _____   ___ __ ___
   |  | '_ ` _ \ / _` | '_ \ / _ \ \ / / '__/ _ \
   |  | | | | | | (_| | | | | (_) \ V /| | |  __/
   |  |_| |_| |_|\__,_|_| |_|\___/ \_/ |_|  \___|
  \*/

  vector<Astro>     stars;
  vector<real_type> star_ray;
  vector<real_type> star_thetaf;

  void
  loadStars( char const fname[] ) {

    stars.clear();  // svuoto vettore
    stars.reserve(100002);
    star_thetaf.clear();
    star_thetaf.reserve(100002);
    star_ray.clear();
    star_ray.reserve(100002);

    ifstream file(fname);
    UTILS_ASSERT(
      file.good(),
      "loadStars('{}',asteroids) cannot open file", fname
    );

    file >> eatline; // skip headers
    real_type t0 = 0;
    real_type M0 = 0;
    for ( int nline = 1; file.good(); ++nline ) {
      // ID, R (kpc), i (deg), Omega (deg), phi (deg), theta_f (deg)

      char line[1000];
      file.getline(line,1000);

      integer len = 0;
      for ( char *pc = line; *pc != '\0'; ++pc, ++len )
        if ( *pc == ',' )
          *pc = ' ';

      if ( len == 0 ) continue;

      integer   ID;
      real_type R(-1), i, Omega, phi, th_f;

      istringstream istr( line );
      istr >> ID >> R >> i >> Omega >> phi >> th_f;

      UTILS_ASSERT(
        R > 0,
        "loadStars, Bad R = {} at line {} star ID {}",
        R, nline, ID
      );

      real_type v  = vc(R);
      real_type mu = R*v*v;
      Keplerian K0;

      ostringstream ostr;
      ostr << "ID:" << ID;

      Astro S;

      K0.a     = R;
      K0.e     = 0;
      //K0.omega = phi;
      K0.Omega = degrees_to_radiants(Omega);
      K0.omega = degrees_to_radiants(phi);
      K0.i     = degrees_to_radiants(i);

      S.setup( ostr.str(), t0, K0, M0, mu );
      S.check_for_consistency();

      stars.push_back( S );
      star_thetaf.push_back( degrees_to_radiants(th_f) );
      star_ray.push_back(R);
    }
    file.close();
  }


}
