#!/usr/bin/env bash

if ! [ -f ogre.tar ]
then
	echo "ogre.tar not found"
fi

if ! [ -f ogre ]
then
	tar -xvf ogre.tar
fi

if ! [ -f ois-v1-3 ]
then
	tar -xvf ./ois_v1-3.tar.gz
fi

cd ./ogre
cmake .

make

cd ..
cd ./ois_v1-3
chmod +x bootstrap
./bootstrap
./configure
