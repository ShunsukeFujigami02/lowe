#!/bin/bash

export infilehead="/raid1/kuzelab/fujigami/analizefile/wcsim_20210602_131347"
export SERVENAME=dcjserv2

cp process_Minimize_refractive_contents.sh process_Minimize_refractive_contents_replaced.sh
chmod +x process_Minimize_refractive_contents_replaced.sh
./process_Minimize_refractive_contents_replaced.sh
