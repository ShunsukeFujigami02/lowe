#!/bin/bash

export infilehead=""

export LikelihoodType="Sum"
export LikelihoodNoRetroFunction="ByData"
export LikelihoodOnRetroFunction="ByData"
export LikelihoodNoRetroAcceptanceFunction="Prototype"
export LikelihoodOnRetroAcceptanceFunction="Prototype"
export LikelihoodSearchRange="Normal"
export LikelihoodSearchCosThetaNumber=401
export LikelihoodSearchCosThetamin=-1.
export LikelihoodSearchCosThetaWidth=0.005
export LikelihoodSearchPhiNumber=400
export LikelihoodSearchPhimin=-3.1415926535
export LikelihoodSearchPhiWidth=0.0157079632679489670
export LikelihoodTimeWindowNoRetro=10
export LikelihoodTimeWindowOnRetro=10
export LikelihoodEventNumber=10000

export SERVENAME=workq

infilelist=(`grep -rlI GoodnessSearch /rhome/fujigami/retro/lowe/analizefile/ | xargs grep -rl compare_digital`)
echo "${#infilelist[@]}"
sleep 2
for infilehead in "${infilelist[@]}"
do
    cp process_Likelihood_contents.sh process_Likelihood_contents_replaced.sh
    chmod +x process_Likelihood_contents_replaced.sh
    ./process_Likelihood_contents_replaced.sh
    sleep 2
done
