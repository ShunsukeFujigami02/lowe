#!/bin/bash

export infilehead="/raid1/kuzelab/fujigami/analizefile/Minimize*"
export EnergyFunctionName="OnRetroFinalver3"
export EnergyNEvents=10000
export Lambda=15000.

export SERVENAME=workq
wcsimfilelist=(`grep -rlI EmitPositionSphereCenterX,double,1300 /rhome/fujigami/retro/lowe/analizefile/ | sed "s/^/-e /g"`)
echo "${#wcsimfilelist[@]}"
goodnessfilelist=(`grep -rlI GoodnessSearch /rhome/fujigami/retro/lowe/analizefile/ | xargs grep -rl compare_nodigital | xargs grep -rl "${wcsimfilelist[@]}" | sed "s/^/-e /g"`)
echo "${#goodnessfilelist[@]}"
likelihoodfilelist=(`grep -rlI LikelihoodNoRetroFunction /rhome/fujigami/retro/lowe/analizefile/ | xargs grep -rl "${goodnessfilelist[@]}" | sed "s/^/-e /g"`)
echo "${#likelihoodfilelist[@]}"
infilelist=(`grep -rlI Minimize /rhome/fujigami/retro/lowe/analizefile/ | xargs grep -rl "${likelihoodfilelist[@]}"`)
echo "${infilelist[@]}"
echo "${#infilelist[@]}"
sleep 2
for infilehead in "${infilelist[@]}"
do
    cp process_Energy_contents.sh process_Energy_contents_replaced.sh
    chmod +x process_Energy_contents_replaced.sh
    source ./process_Energy_contents_replaced.sh
    sleep 2
done
