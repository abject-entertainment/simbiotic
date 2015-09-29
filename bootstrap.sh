#!/bin/bash

# parameters
doVS=0 # -vs - If running on Cygwin, build Visual Studio projects instead of makefiles
doUX=0 # -ux - If running on Mac, build Unix build scripts instead of Xcode projects
doJS=0 # -js - Build with emscripten for release on web/nwjs.io and for testing in node (NOT IMPLEMENTED)
doTV=0 # -tv - If running on Mac, include Apple TV as a build target (NOT IMPLEMENTED, POSSIBLY NOT NECESSARY)

doBuild=0 # -build - After generating build files, go ahead and build everything
doIDE=0 # -ide - After generating build files, open the IDE.  Overrides doBuild, but only works for Xcode and VS projects.

for param in "$@"
do
	if [[ "$param" == "-vs" ]]; then
		doVS=1
	elif [[ "$param" == "-ux" ]]; then
		doUX=1
	elif [[ "$param" == "-js" ]]; then
		doJS=1
		echo "JavaScript build is not yet supported.  Check back later (probably much later)."
	elif [[ "$param" == "-tv" ]]; then
		doTV=1
		echo "Apple TV build is not yet supported, and may not actually ever need to be a thing.  Check back later (probably much later)."
	elif [[ "$param" == "-build" ]]; then
		doBuild=1
	elif [[ "$param" == "-clean" ]]; then
		echo "[===> CLEANING build environment"
		rm -rfd build
	else
		echo "Unrecognized parameter: $param"
	fi
done

mkdir -p build
mkdir -p dependencies

# platform check
platform=$(uname)

generator="Unix Makefiles"
bdir="unix"

if [[ "$platform" == "Darwin" ]]; then
	if [ $doUX -eq 1 ]; then
		generator="Unix Makefiles"
	else
		generator="Xcode"
	fi
	bdir="macos"
elif [[ "$platform" == "CYGWIN_NT"* ]]; then
	if [ $doVS -eq 1 ]; then
		generator="Visual Studio 10 2010"
	else
		generator="Unix Makefiles"
	fi
	bdir="windows"
fi

# googletest
#if [ ! -d "dependencies/googletest" ]; then
#	echo "[===> GITTING Google Test"
#	cd dependencies
#	git clone https://github.com/google/googletest.git
#	cd ..
#fi
#
#echo "[===> BUILDING Google Test"
#mkdir -p build/googletest
#
#if [[ "$platform" == "Darwin" ]]; then
#	cd dependencies/googletest/googletest/xcode
#	xcodebuild -target gtest-framework
#	cp build/Release/*.a ../../../../build/googletest
#	cd ../../../..
#else
#	cd build/googletest
#	cmake ../../dependencies/googletest/googletest
#	make
#	cd ../..
#fi

# simbiotic
echo "[===> GENERATING build files"


echo "    --> PLATFORM: $bdir"
echo "    --> TOOLSET: $generator"

cd build
mkdir -p $bdir
cd $bdir

cmake -G "$generator" ../..

if [ $doIDE -eq 1 ] && ( [[ "$generator" == "Xcode" ]] || [[ "$generator" == "Visual Studio"* ]] ); then
	if [[ "$generator" == "Xcode" ]]; then
		open simbiotic_project.xcodeproj
	elif [[ "$generator" == "Visual Studio"* ]]; then
		cygstart simbiotic_project.sln
	fi
elif [ $doBuild -eq 1 ]; then
	echo "[===> BUILDING simbiotic"
	if [[ "$generator" == "Unix makefiles" ]]; then
		make
	elif [[ "$generator" == "Xcode" ]]; then
		xcodebuild -target simbiotic
	elif [[ "$generator" == "Visual Studio"* ]]; then
		msbuild simbiotic.vcxproj
	fi
fi
