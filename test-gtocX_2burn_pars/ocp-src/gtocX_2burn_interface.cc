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

#define CLASS gtocX_2burn_pars

#include "gtocX.hh"
#include "gtocX_2burn_pars.hh"
#include "gtocX_2burn_pars_Pars.hh"

namespace gtocX_2burn_parsDefine {

  using namespace std;
  using namespace MechatronixLoad;

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
      UTILS_ASSERT( ok, "guess_setup, Lambert failed" );
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
  CLASS::p_guess( real_type ) const {
    guess_setup();
    return Guess.pOrbital();
  }

  real_type
  CLASS::f_guess( real_type ) const {
    guess_setup();
    return Guess.fOrbital();
  }

  real_type
  CLASS::g_guess( real_type ) const {
    guess_setup();
    return Guess.gOrbital();
  }

  real_type
  CLASS::h_guess( real_type ) const {
    guess_setup();
    return Guess.hOrbital();
  }

  real_type
  CLASS::k_guess( real_type ) const {
    guess_setup();
    return Guess.kOrbital();
  }

  real_type
  CLASS::L_guess( real_type t, real_type t0 ) const {
    guess_setup();
    return Guess.Lorbital( t0, t );
  }

  real_type CLASS::X_begin   ( real_type t ) const { return From->xPosition( t ); }
  real_type CLASS::X_begin_D ( real_type t ) const { return From->xVelocity( t ); }
  real_type CLASS::X_begin_DD( real_type t ) const { return From->xAcceleration( t ); }

  real_type CLASS::Y_begin   ( real_type t ) const { return From->yPosition( t ); }
  real_type CLASS::Y_begin_D ( real_type t ) const { return From->yVelocity( t ); }
  real_type CLASS::Y_begin_DD( real_type t ) const { return From->yAcceleration( t ); }

  real_type CLASS::Z_begin   ( real_type t ) const { return From->zPosition( t ); }
  real_type CLASS::Z_begin_D ( real_type t ) const { return From->zVelocity( t ); }
  real_type CLASS::Z_begin_DD( real_type t ) const { return From->zAcceleration( t ); }

  real_type CLASS::VX_begin   ( real_type t ) const { return From->xVelocity( t ); }
  real_type CLASS::VX_begin_D ( real_type t ) const { return From->xAcceleration( t ); }
  real_type CLASS::VX_begin_DD( real_type t ) const { return From->xJerk( t ); }

  real_type CLASS::VY_begin   ( real_type t ) const { return From->yVelocity( t ); }
  real_type CLASS::VY_begin_D ( real_type t ) const { return From->yAcceleration( t ); }
  real_type CLASS::VY_begin_DD( real_type t ) const { return From->yJerk( t ); }

  real_type CLASS::VZ_begin   ( real_type t ) const { return From->zVelocity( t ); }
  real_type CLASS::VZ_begin_D ( real_type t ) const { return From->zAcceleration( t ); }
  real_type CLASS::VZ_begin_DD( real_type t ) const { return From->zJerk( t ); }

  real_type CLASS::X_end   ( real_type t ) const { return To->xPosition( t ); }
  real_type CLASS::X_end_D ( real_type t ) const { return To->xVelocity( t ); }
  real_type CLASS::X_end_DD( real_type t ) const { return To->xAcceleration( t ); }

  real_type CLASS::Y_end   ( real_type t ) const { return To->yPosition( t ); }
  real_type CLASS::Y_end_D ( real_type t ) const { return To->yVelocity( t ); }
  real_type CLASS::Y_end_DD( real_type t ) const { return To->yAcceleration( t ); }

  real_type CLASS::Z_end   ( real_type t ) const { return To->zPosition( t ); }
  real_type CLASS::Z_end_D ( real_type t ) const { return To->zVelocity( t ); }
  real_type CLASS::Z_end_DD( real_type t ) const { return To->zAcceleration( t ); }

  real_type CLASS::VX_end   ( real_type t ) const { return To->xVelocity( t ); }
  real_type CLASS::VX_end_D ( real_type t ) const { return To->xAcceleration( t ); }
  real_type CLASS::VX_end_DD( real_type t ) const { return To->xJerk( t ); }

  real_type CLASS::VY_end   ( real_type t ) const { return To->yVelocity( t ); }
  real_type CLASS::VY_end_D ( real_type t ) const { return To->yAcceleration( t ); }
  real_type CLASS::VY_end_DD( real_type t ) const { return To->yJerk( t ); }

  real_type CLASS::VZ_end   ( real_type t ) const { return To->zVelocity( t ); }
  real_type CLASS::VZ_end_D ( real_type t ) const { return To->zAcceleration( t ); }
  real_type CLASS::VZ_end_DD( real_type t ) const { return To->zJerk( t ); }

}
