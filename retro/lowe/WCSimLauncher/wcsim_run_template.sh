#!/bin/bash
source $HOME/retro/setup.sh
cd $HOME/retro/WCSim_build
(time ./WCSim MACFILE) > log 2>&1
