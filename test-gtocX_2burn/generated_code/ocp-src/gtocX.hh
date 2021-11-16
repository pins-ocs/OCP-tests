#ifndef GTOCX_HH
#define GTOCX_HH

#include <MechatronixCore/MechatronixCore.hh>
#include <iostream>
#include <sstream>
#include <chrono>
#include <vector>
#include <set>

namespace gtocX {

  using namespace MechatronixLoad;
  using namespace AstroLib;

  static integer const nstars = 100000;

  static real_type const Rmin = 2;  // kpc
  static real_type const Rmax = 32; // kpc

  static real_type const kms_to_kpc_My        = 0.001022712165;
  static real_type const min_delta_T_My       = 1;
  static real_type const min_wait_time_My     = 2;

  static integer   const mother_impulse       = 3;
  static real_type const mother_ship_max_DV   = 200*kms_to_kpc_My;
  static real_type const mother_ship_total_DV = 500*kms_to_kpc_My;
  static real_type const mother_ship_mean_DV  = 165*kms_to_kpc_My;

  static integer   const pod_impulse          = 1;
  static real_type const pod_max_DV           = 300*kms_to_kpc_My;

  static integer   const fast_ship_impulse    = 2;
  static real_type const fast_ship_max_DV     = 1500*kms_to_kpc_My;

  static integer   const settle_ship_impulse  = 5;
  static real_type const settle_ship_max_DV   = 175*kms_to_kpc_My;
  static real_type const settle_ship_total_DV = 400*kms_to_kpc_My;

  static real_type const tol_DV               = 0.01*kms_to_kpc_My;
  static real_type const tol_Time             = 1e-8;
  static real_type const tol_position         = 0.0001;

  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  extern vector<Astro>            stars;
  extern vector<real_type>        star_ray;
  extern vector<real_type>        star_thetaf;
  extern vector<real_type>        star_fr[31];
  extern vector<real_type>        star_ftheta[33];
  extern vector<vector<integer> > R_class;
  extern vector<vector<integer> > Theta_class;
  extern vector<integer>          star_to_R_class;
  extern vector<integer>          star_to_Theta_class;


  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  real_type vc( real_type r );
  real_type vc_D( real_type r );
  real_type vc_DD( real_type r );

  real_type muc( real_type R );

  void loadStars( char const fname[] );

  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  void
  starPV(
    Keplerian const & K0,
    real_type         t,
    real_type         PP[3],
    real_type         VV[3]
  );

  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  void
  FreeFlightEQ(
    real_type           t0,
    Equinoctial const & eq0,
    real_type           L0,
    real_type           t1,
    Equinoctial       & eq1,
    real_type         & L1,
    real_type           muS,
    real_type           dt
  );

  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  void
  FreeFlightEQ(
    real_type       t0,
    real_type const P0[3],
    real_type const V0[3],
    real_type       t1,
    real_type       P1[],
    real_type       V1[],
    real_type       dt,
    real_type     & rmin_m,
    real_type     & rmax_m
  );

  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  void
  FreeFlightXYZ(
    real_type       t0,
    real_type const P0[3],
    real_type const V0[3],
    real_type       t1,
    real_type       P1[],
    real_type       V1[],
    real_type       dt,
    real_type     & rmin_m,
    real_type     & rmax_m
  );

  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  void
  FreeFlight(
    real_type                 t0,
    real_type                 x0,
    real_type                 y0,
    real_type                 z0,
    real_type                 vx0,
    real_type                 vy0,
    real_type                 vz0,
    vector<real_type> const & t1,
    vector<real_type>       & X,
    vector<real_type>       & Y,
    vector<real_type>       & Z,
    vector<real_type>       & VX,
    vector<real_type>       & VY,
    vector<real_type>       & VZ,
    real_type                 dt,
    real_type               & rmin_m,
    real_type               & rmax_m
  );

  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  bool
  build_Lambert_guess(
    real_type     t0,
    Astro const & From,
    real_type     t1,
    Astro const & to_star,
    real_type     muS,
    Astro       & guess
  );

  bool
  build_Lambert_guess(
    real_type       t0,
    real_type const P0[3],
    real_type       t1,
    Astro const   & To,
    real_type       muS,
    Astro         & guess
  );

  /*\
   | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  \*/

  static
  inline
  bool
  build_Lambert_guess(
    real_type t0,
    integer   from_star,
    real_type t1,
    integer   to_star,
    real_type muS,
    Astro   & guess
  ) {
    return build_Lambert_guess( t0, stars[from_star], t1, stars[to_star], muS, guess );
  }

}

#endif
