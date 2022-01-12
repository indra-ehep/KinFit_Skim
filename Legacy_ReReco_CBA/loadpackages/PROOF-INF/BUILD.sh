#! /bin/sh
# Build libEvent library.

#echo "Hello from BUILD.sh"

if test ! "x$ROOTPROOFLITE" = "x"; then
   echo "event-BUILD: PROOF-Lite node (session has $ROOTPROOFLITE workers)"
elif test ! "x$ROOTPROOFCLIENT" = "x"; then
   echo "event-BUILD: PROOF client"
else
   echo "event-BUILD: standard PROOF node"
fi

if [ "" = "clean" ]; then
   make distclean
   exit 0
fi

#make
rc=$?
#echo "rc=$?"

if [ $? != "0" ] ; then
   exit 1
fi
exit 0


