#!/bin/sh
set -ex
sudo apt-get update
sudo apt-cache search gflags
sudo apt-get install libgflags2 libgflags-dev
sudo apt-get install libsnappy-dev
sudo apt-get install zlib1g-dev
sudo apt-get install libbz2-dev
sudo apt-get install libpthread-stubs0-dev
