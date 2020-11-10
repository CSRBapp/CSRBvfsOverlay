#!/bin/bash

export LD_BIND_NOW=BIND
export LD_PRELOAD=`pwd`/CSRBvfsOverlay.so
$*
