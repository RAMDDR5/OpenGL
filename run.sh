#!/bin/bash
if [ "$1" = "-id" ]; then
	echo "Installing for debian/debian-based"
	sudo apt install gcc make glfw glad
elif [ "$1" = "-ia" ]; then
	echo "Installing for arch/arch-based"
	sudo pacman -S gcc make glfw glad
elif [ "$1" = "-c" ]; then
	echo "Compiling"
	make -f .Makefile
else 
	printf "usage: $0 [OPTION]\noptions:\n-ia to install for arch\n-id to install for debian\n-c to compile\n"
fi
