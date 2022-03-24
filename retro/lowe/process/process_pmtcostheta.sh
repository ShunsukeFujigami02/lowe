#!/bin/bash

export infilehead="/raid1/kuzelab/fujigami/analizefile/wcsim_20210513_133925"

export SERVENAME=dcjserv2

cp process_pmtcostheta_contents.sh process_pmtcostheta_contents_replaced.sh
chmod +x process_pmtcostheta_contents_replaced.sh
./process_pmtcostheta_contents_replaced.sh
