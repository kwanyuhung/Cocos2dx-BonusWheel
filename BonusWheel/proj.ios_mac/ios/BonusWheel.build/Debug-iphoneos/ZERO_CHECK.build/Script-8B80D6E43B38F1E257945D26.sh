#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/kwanyuhung/Desktop/BonusWheel/proj.ios_mac/ios
  make -f /Users/kwanyuhung/Desktop/BonusWheel/proj.ios_mac/ios/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/kwanyuhung/Desktop/BonusWheel/proj.ios_mac/ios
  make -f /Users/kwanyuhung/Desktop/BonusWheel/proj.ios_mac/ios/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/kwanyuhung/Desktop/BonusWheel/proj.ios_mac/ios
  make -f /Users/kwanyuhung/Desktop/BonusWheel/proj.ios_mac/ios/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/kwanyuhung/Desktop/BonusWheel/proj.ios_mac/ios
  make -f /Users/kwanyuhung/Desktop/BonusWheel/proj.ios_mac/ios/CMakeScripts/ReRunCMake.make
fi

