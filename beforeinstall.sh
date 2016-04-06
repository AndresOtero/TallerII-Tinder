#!/bin/sh
set -ex
sudo apt-get update
sudo apt-cache search libgflags-dev
sudo apt-get install libgflags-dev
sudo apt-get install libsnappy-dev
sudo apt-get install zlib1g-dev
sudo apt-get install libbz2-dev
sudo apt-get install libpthread-stubs0-dev
