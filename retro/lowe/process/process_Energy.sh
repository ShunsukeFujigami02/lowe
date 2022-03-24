#!/bin/bash

export infilehead="/rhome/fujigami/retro/lowe/analizefile/Minimize_20211108_145819.csv"
export EnergyFunctionName="OnRetroFinal"
export EnergyNEvents=10000
export Lambda=10001
export LambdaRetro=10000
export SERVENAME=workq

cp process_Energy_contents.sh process_Energy_contents_replaced.sh
chmod +x process_Energy_contents_replaced.sh
source ./process_Energy_contents_replaced.sh
