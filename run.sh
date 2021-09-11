#!/bin/bash

export LD_BIND_NOW=BIND
export LD_LIBRARY_PATH=../../SASnet/build-shared-narf/:../../CSRBcore/build-shared-narf/
export LD_PRELOAD=../build-shared-narf/libCSRBvfs.so:$(dirname $0)/CSRBvfsOverlay.so
$*
