#!/bin/bash

export infilehead="/raid1/kuzelab/fujigami/analizefile/Likelihood_20210808_132915"

export MinimizeFunctionName="minimizedfunconretroadddarkratenumaddacceptance"
export ValueNumber=7
export MaxFunctionCalls=10000
export MaxIterations=10000
export Tolerance=0.01
Step=(1. 1. 1. 0.1 0.1 0.1 0.1)
Lower=(-3000. -3000. -3000. -400. -3. -100. 0.)
Upper=(3000. 3000. 3000. 0. 3. 100. 1000.)
export OuttreeMinimize="minimizeT"
export MinimizeNEvents=10000

export SERVENAME=dcjserv1

cp process_Minimize_contents.sh process_Minimize_contents_replaced.sh
chmod +x process_Minimize_contents_replaced.sh
source ./process_Minimize_contents_replaced.sh
