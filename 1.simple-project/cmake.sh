#!/bin/sh

# default values
OS="windows" 
BUILD_DIR="build-windows" 
CONFIG="Release"

do_clean() {
	rm -rf $BUILD_DIR
}

do_build() {
	mkdir $BUILD_DIR; 
	cd $BUILD_DIR
	# call cmake -> VERBOSE + Release build
	cmake  -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_BUILD_TYPE=Release ..
	cmake --build . --config $CONFIG --clean-first
}

do_install() {
	cd $BUILD_DIR
	if [ "${OS}" == "windows" ]; then
		cmake --install . 
	else
		make install
	fi
}


main(){
	# SET OS TYPE
	case "$OSTYPE" in
		linux*)   
			echo "Found OS: LINUX"
			OS="linux" 
			BUILD_DIR="build-linux"
			;;
		msys*)    
			echo "Found OS: WINDOWS"
			OS="windows" 
			BUILD_DIR="build-windows"
			;;
		*)        
			echo "Found OS: unknown: $OSTYPE"
			OS="unknown" 
			BUILD_DIR="build-unknown"
			;;
	esac
	
	case $1 in
	clean)
		do_clean
		;;
	build)
		do_build
		;;
	install)
		do_install
		;;
	*)
		echo "Usage: $0 { clean | build | install }"
		exit 1
		;;
	esac
}

main $1