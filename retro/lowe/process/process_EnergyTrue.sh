#!/bin/bash

export infilehead="/rhome/fujigami/retro/lowe/analizefile/wcsim_20220126_204313.csv"
export EnergyFunctionName="OnRetroFinalTrue"
export EnergyNEvents=10000
export Lambda=15000.
export LambdaRetro=10000.

export SERVENAME=workq
wcsimfilelist=(`grep -rlI RetroType,string,OnRetro /rhome/fujigami/retro/lowe/analizefile/ | xargs grep -rl EmitPositionType,string,fixed | xargs grep -rl EmitPositionFixedX,double,200 | xargs grep -rl EmitDirectionFixedCostheta,double,0.78539`)
echo "${#wcsimfilelist[@]}"
sleep 2
for infilehead in "${wcsimfilelist[@]}"
do
    for EnergyFunctionName in "OnRetroFinalver3True"
    do
	for LambdaRetro in 5000. 6000. 7000. 8000. 9000. 10000. 11000. 12000. 13000. 14000. 15000.
	do
	    cp process_Energy_contents.sh process_Energy_contents_replaced.sh
	    chmod +x process_Energy_contents_replaced.sh
	    source ./process_Energy_contents_replaced.sh
	    sleep 2
	done
    done
done
