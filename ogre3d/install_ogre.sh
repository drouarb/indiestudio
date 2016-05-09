#!/bin/bash

wget 163.172.133.5/all.tar -O all.tar

mkdir ~/.ogre
mv all.tar ~/.ogre
cd ~/.ogre
tar -xvf all.tar
rm -f all.tar
tar -xvf includes_OIS.tar
tar -xvf includes.tar
tar -xvf lib_OGRE.tar
tar -xvf lib_OIS.tar

chmod +x *.so*

echo "export LD_LIBRARY_PATH=\"/home/${USER}/.ogre/lib/:\$LD_LIBRARY_PATH\"" >> ~/.bashrc
echo "export LD_LIBRARY_PATH=\"/home/${USER}/.ogre/:\$LD_LIBRARY_PATH\"" >> ~/.bashrc
echo "export CPP_INCLUDE_PATH=\"/home/${USER}/.ogre/includes/:\$CPP_INCLUDE_PATH\"" >> ~/.bashrc
echo "export CPP_INCLUDE_PATH=\"/home/${USER}/.ogre/includes/linux:\$CPP_INCLUDE_PATH\"" >> ~/.bashrc
