#!/bin/bash

# run as ./scripts/autocheck-windows.sh

SOURCE=`cygpath -w $PWD`
GEN="NMake Makefiles"
CMAKE="/cygdrive/c/Program Files/CMake 2.4/bin/cmake.exe"
CMAKEOPTS="-DCREATE_GUIS:BOOL=FALSE -DCREATE_DEVICE_LIBRARY:BOOL=TRUE"

YARP1_INCLUDE="$PWD/../yarp/include"

if [ -e $YARP1_INCLUDE ]; then
	echo "Found YARP1"
	p=`cygpath -m $YARP1_INCLUDE`
	CMAKEOPTS="$CMAKEOPTS -DCOEXIST_WITH_YARP1:BOOL=ON -DYARP1_INCLUDE_DIR:PATH=$p"
else
	echo "Did not find YARP1"
fi

while true; do

rm -f should_report.txt

(

cvs update -d > cvslog.txt
cat cvslog.txt | grep -v "cvs update" | egrep -v "^\? " | egrep -v "^M " | tee cvslog2.txt

if egrep "[a-zA-Z]" cvslog2.txt; then

echo Working in directory $SOURCE | tee should_report.txt

rm -f CMakeCache.txt
rm -f failure.txt
"$CMAKE" $CMAKEOPTS -G "$GEN" $SOURCE || ( echo YARP_AUTOCHECK cmake configure failed | tee failure.txt )

nmake clean || echo "nmake clean failed"

if [ ! -e failure.txt ]; then
	nmake || ( echo YARP_AUTOCHECK nmake compile failed | tee failure.txt )
fi

echo "Regression tests not run" > testlog.txt
if [ ! -e failure.txt ]; then
	# helpful to go offline
	ipconfig /release
	(
	    nmake test || ( echo YARP_AUTOCHECK nmake regression failed | tee failure.txt )
	) | tee testlog.txt
	ipconfig /renew
fi

cat cvslog.txt

if [ -e failure.txt ]; then
	echo YARP_AUTOCHECK at least one failure happened
fi

else
	echo "Nothing new in CVS"
fi

) | tee report.txt

if [ -e should_report.txt ]; then
	date > report-decor.txt
	cat testlog.txt >> report-decor.txt
	echo >> report-decor.txt
	echo >> report-decor.txt
	cat report.txt >> report-decor.txt
	scp report-decor.txt eshuy@yarp0.sf.net:www/report-yarp2-windows.txt
fi

sleep 600

done
