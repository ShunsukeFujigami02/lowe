#!/bin/bash

export infilehead="/raid1/kuzelab/fujigami/analizefile/Goodness_20210806_233612"

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
export LikelihoodTimeWindowNoRetro=20
export LikelihoodTimeWindowOnRetro=20
export LikelihoodEventNumber=10000

export SERVENAME=dcjserv2

cp process_Likelihood_contents.sh process_Likelihood_contents_replaced.sh
chmod +x process_Likelihood_contents_replaced.sh
./process_Likelihood_contents_replaced.sh
