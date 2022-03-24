#!/bin/bash

export infilehead=""

export MinimizeFunctionName="minimizedfunconretroadddarkratenumaddacceptance"
export ValueNumber=7
export MaxFunctionCalls=10000
export MaxIterations=10000
export Tolerance=0.01
Step=(1. 1. 1. 0.1 0.1 0.1 0.1)
Lower=(-3000. -3000. -3000. -400. -3. -100. 1.)
Upper=(3000. 3000. 3000. 0. 3. 100. 1000.)
export OuttreeMinimize="minimizeT"
export MinimizeNEvents=10000

export SERVENAME=workq
goodnessfilelist=(`grep -rlI GoodnessSearch /rhome/fujigami/retro/lowe/analizefile/ | xargs grep -rl compare_digital | sed "s/^/-e /g"`)
echo "${#goodnessfilelist[@]}"
infilelist=(`grep -rlI Likelihood /rhome/fujigami/retro/lowe/analizefile/ | xargs grep -rl "${goodnessfilelist[@]}"`)
echo "${infilelist[@]}"
echo "${#infilelist[@]}"
sleep 2
for infilehead in "${infilelist[@]}"
do
    cp process_Minimize_contents.sh process_Minimize_contents_replaced.sh
    chmod +x process_Minimize_contents_replaced.sh
    source ./process_Minimize_contents_replaced.sh
    sleep 2
done
