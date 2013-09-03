#!/bin/bash

VERSION="0.2.3"

SCRIPT=$(readlink -f $0)
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname $SCRIPT)
echo "executing script from $SCRIPTPATH"

mkdir /tmp/simtex-$VERSION
cp -r ../source/* /tmp/simtex-$VERSION
mkdir /tmp/simtex-$VERSION/share
cp -r deb/share/* /tmp/simtex-$VERSION/share
cd /tmp
tar czf $SCRIPTPATH/simtex.tar.gz simtex-$VERSION
#mv /tmp/simtex-0.1.10.tar.gz /tmp/myscript/simtex-$VERSION.tar.gz
