#!/bin/bash

SCRIPT=$(readlink -f $0)
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname $SCRIPT)
echo "executing script from $SCRIPTPATH"

mkdir /tmp/simtex-0.1.10
cp -r ../source/* /tmp/simtex-0.1.10
mkdir /tmp/simtex-0.1.10/share
cp -r deb/share/* /tmp/simtex-0.1.10/share
cd /tmp
tar czf $SCRIPTPATH/simtex-0.1.10.tar.gz simtex-0.1.10
#mv /tmp/simtex-0.1.10.tar.gz /tmp/myscript/simtex-0.1.10.tar.gz
