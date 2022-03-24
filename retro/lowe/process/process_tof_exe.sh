#!/bin/bash

export infilehead="/raid1/kuzelab/fujigami/analizefile/wcsim_20210618_114734"
export NWater=1.38072381233779451
export SERVENAME=dcjserv2

cp process_tof_exe_contents.sh process_tof_exe_contents_replaced.sh
chmod +x process_tof_exe_contents_replaced.sh
./process_tof_exe_contents_replaced.sh
