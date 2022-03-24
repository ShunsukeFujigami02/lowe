#!/bin/bash

export infilehead="/raid1/kuzelab/fujigami/analizefile/wcsim_20210602_131347"
export NWater=1.
export SERVENAME=dcjserv2

for NWater in 1.3330 1.3331 1.3332 1.3333 1.3334 1.3335 1.3336 1.3337 1.3338 1.3339 1.3340
do
    cp process_tof_exe_contents.sh process_tof_exe_contents_replaced.sh
    chmod +x process_tof_exe_contents_replaced.sh
    ./process_tof_exe_contents_replaced.sh
    sleep 2
done
