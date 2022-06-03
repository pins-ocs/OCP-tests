#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/enrico/Ricerca/develop/PINS/pins-mechatronix/tests/OCP/test-Brachiostocrona/generated_code/Xcode
  make -f /Users/enrico/Ricerca/develop/PINS/pins-mechatronix/tests/OCP/test-Brachiostocrona/generated_code/Xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/enrico/Ricerca/develop/PINS/pins-mechatronix/tests/OCP/test-Brachiostocrona/generated_code/Xcode
  make -f /Users/enrico/Ricerca/develop/PINS/pins-mechatronix/tests/OCP/test-Brachiostocrona/generated_code/Xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/enrico/Ricerca/develop/PINS/pins-mechatronix/tests/OCP/test-Brachiostocrona/generated_code/Xcode
  make -f /Users/enrico/Ricerca/develop/PINS/pins-mechatronix/tests/OCP/test-Brachiostocrona/generated_code/Xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/enrico/Ricerca/develop/PINS/pins-mechatronix/tests/OCP/test-Brachiostocrona/generated_code/Xcode
  make -f /Users/enrico/Ricerca/develop/PINS/pins-mechatronix/tests/OCP/test-Brachiostocrona/generated_code/Xcode/CMakeScripts/ReRunCMake.make
fi

