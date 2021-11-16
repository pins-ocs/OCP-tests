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

#define CLASS gtocX_2burn

#include "gtocX.hh"
#include "gtocX_2burn.hh"
#include "gtocX_2burn_Pars.hh"

namespace gtocX_2burnDefine {

  using namespace std;
  using namespace MechatronixLoad;
  using namespace AstroLib;

  static Astro const * From;
  static Astro const * To;
  static Astro Guess;
  static bool  do_setup = true;

  real_type
  CLASS::guess_setup() const {
    if ( do_setup ) {
      gtocX::loadStars( "./data/stars.txt" );
      From = &gtocX::stars[0];
      To   = &gtocX::stars[12003];

      real_type t0  = ModelPars[iM_time_i];
      real_type t1  = ModelPars[iM_time_f];
      real_type muS = ModelPars[iM_muS];
      bool ok = gtocX::build_Lambert_guess( t0, *From, t1, *To, muS, Guess );
      UTILS_ASSERT0( ok, "guess_setup, Lambert failed" );
      do_setup = false;
      real_type ret = ModelPars[iM_retrograde];
      if ( ret < 0 ) Guess.make_retrograde();
      else           Guess.make_not_retrograde();
    }
    return 0;
  }

  real_type
  CLASS::vc( real_type r__XO ) const {
    return gtocX::vc( r__XO );
  }

  real_type
  CLASS::vc_D( real_type r__XO ) const {
    return gtocX::vc_D( r__XO );
  }

  real_type
  CLASS::vc_DD( real_type r__XO ) const {
    return gtocX::vc_DD( r__XO );
  }

  real_type
  CLASS::p_guess( real_type t ) const {
    guess_setup();
    return Guess.p_orbital();
  }

  real_type
  CLASS::f_guess( real_type t ) const {
    guess_setup();
    return Guess.f_orbital();
  }

  real_type
  CLASS::g_guess( real_type t ) const {
    guess_setup();
    return Guess.g_orbital();
  }

  real_type
  CLASS::h_guess( real_type t ) const {
    guess_setup();
    return Guess.h_orbital();
  }

  real_type
  CLASS::k_guess( real_type t ) const {
    guess_setup();
    return Guess.k_orbital();
  }

  real_type
  CLASS::L_guess( real_type t, real_type t0 ) const {
    guess_setup();
    return Guess.L_orbital( t0, t );
  }

  real_type CLASS::X_begin   ( real_type t ) const { return From->x_position( t ); }
  real_type CLASS::X_begin_D ( real_type t ) const { return From->x_velocity( t ); }
  real_type CLASS::X_begin_DD( real_type t ) const { return From->x_acceleration( t ); }

  real_type CLASS::Y_begin   ( real_type t ) const { return From->y_position( t ); }
  real_type CLASS::Y_begin_D ( real_type t ) const { return From->y_velocity( t ); }
  real_type CLASS::Y_begin_DD( real_type t ) const { return From->y_acceleration( t ); }

  real_type CLASS::Z_begin   ( real_type t ) const { return From->z_position( t ); }
  real_type CLASS::Z_begin_D ( real_type t ) const { return From->z_velocity( t ); }
  real_type CLASS::Z_begin_DD( real_type t ) const { return From->z_acceleration( t ); }

  real_type CLASS::VX_begin   ( real_type t ) const { return From->x_velocity( t ); }
  real_type CLASS::VX_begin_D ( real_type t ) const { return From->x_acceleration( t ); }
  real_type CLASS::VX_begin_DD( real_type t ) const { return From->x_jerk( t ); }

  real_type CLASS::VY_begin   ( real_type t ) const { return From->y_velocity( t ); }
  real_type CLASS::VY_begin_D ( real_type t ) const { return From->y_acceleration( t ); }
  real_type CLASS::VY_begin_DD( real_type t ) const { return From->y_jerk( t ); }

  real_type CLASS::VZ_begin   ( real_type t ) const { return From->z_velocity( t ); }
  real_type CLASS::VZ_begin_D ( real_type t ) const { return From->z_acceleration( t ); }
  real_type CLASS::VZ_begin_DD( real_type t ) const { return From->z_jerk( t ); }

  real_type CLASS::X_end   ( real_type t ) const { return To->x_position( t ); }
  real_type CLASS::X_end_D ( real_type t ) const { return To->x_velocity( t ); }
  real_type CLASS::X_end_DD( real_type t ) const { return To->x_acceleration( t ); }

  real_type CLASS::Y_end   ( real_type t ) const { return To->y_position( t ); }
  real_type CLASS::Y_end_D ( real_type t ) const { return To->y_velocity( t ); }
  real_type CLASS::Y_end_DD( real_type t ) const { return To->y_acceleration( t ); }

  real_type CLASS::Z_end   ( real_type t ) const { return To->z_position( t ); }
  real_type CLASS::Z_end_D ( real_type t ) const { return To->z_velocity( t ); }
  real_type CLASS::Z_end_DD( real_type t ) const { return To->z_acceleration( t ); }

  real_type CLASS::VX_end   ( real_type t ) const { return To->x_velocity( t ); }
  real_type CLASS::VX_end_D ( real_type t ) const { return To->x_acceleration( t ); }
  real_type CLASS::VX_end_DD( real_type t ) const { return To->x_jerk( t ); }

  real_type CLASS::VY_end   ( real_type t ) const { return To->y_velocity( t ); }
  real_type CLASS::VY_end_D ( real_type t ) const { return To->y_acceleration( t ); }
  real_type CLASS::VY_end_DD( real_type t ) const { return To->y_jerk( t ); }

  real_type CLASS::VZ_end   ( real_type t ) const { return To->z_velocity( t ); }
  real_type CLASS::VZ_end_D ( real_type t ) const { return To->z_acceleration( t ); }
  real_type CLASS::VZ_end_DD( real_type t ) const { return To->z_jerk( t ); }

}
