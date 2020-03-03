/*\
 |    ____ _____ ___   ____
 |   / ___|_   _/ _ \ / ___|
 |  | |  _  | || | | | |
 |  | |_| | | || |_| | |___
 |   \____| |_| \___/ \____|
 |
\*/

#ifndef GTOCX_UTILS_HH
#define GTOCX_UTILS_HH

#include "gtocX.hh"
#include "gtocX_utils.hh"

namespace gtocX {

  inline
  void
  zero3( real_type a[3] )
  { a[0] = a[1] = a[2] = 0;  }

  inline
  void
  copy3( real_type const a[3], real_type b[3] )
  { b[0] = a[0]; b[1] = a[1]; b[2] = a[2]; }

  inline
  real_type
  norm3( real_type const v[3] )
  { return hypot(hypot(v[0],v[1]),v[2]); }

  inline
  real_type
  dot3( real_type const a[3], real_type const b[3] )
  { return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]; }

  inline
  real_type
  dist3( real_type const a[3], real_type const b[3] )
  { return hypot(hypot(a[0]-b[0],a[1]-b[1]),a[2]-b[2]); }

  inline
  void
  cross( real_type const a[3], real_type const b[3], real_type c[3] ) {
    c[0] = a[1]*b[2]-a[2]*b[1];
    c[1] = a[2]*b[0]-a[0]*b[2];
    c[2] = a[0]*b[1]-a[1]*b[0];
  }

}

#endif
