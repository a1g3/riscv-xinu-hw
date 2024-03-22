#!/bin/bash

if [ $# -eq 1 ]; then
	VERSION=$1
else
	echo "Usage: $0 project_number"
	exit -1
fi

if [ -d xinu-hw${VERSION} ]; then
	if [ -e xinu-hw${VERSION}.tgz ]; then
		mv xinu-hw${VERSION}.tgz old-xinu-hw${VERSION}-`date +%F-%T.%N`.tgz
	fi
	tar cvzf xinu-hw${VERSION}.tgz xinu-hw${VERSION}
else
	echo "ERROR: Could not find directory xinu-hw${VERSION}!"
	exit -2
fi
