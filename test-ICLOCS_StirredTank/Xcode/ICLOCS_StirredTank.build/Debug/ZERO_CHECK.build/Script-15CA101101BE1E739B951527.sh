#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode
  make -f /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode
  make -f /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode
  make -f /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode
  make -f /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/CMakeScripts/ReRunCMake.make
fi

