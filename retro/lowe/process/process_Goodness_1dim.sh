#!/bin/bash

export infilehead="/raid1/kuzelab/fujigami/analizefile/wcsim_20210503_190725"

export GoodnessSigma=5 # (ns)
export GoodnessType="compare_nodigital_ver3"
export GoodnessSearchRangeType="normal"
export GoodnessSearchRangeXNumber=29
export GoodnessSearchRangeXmin=-700 # (cm)
export GoodnessSearchRangeXWidth=50 # (cm)
export GoodnessSearchRangeYNumber=29
export GoodnessSearchRangeYmin=-700 # (cm)
export GoodnessSearchRangeYWidth=50 # (cm)
export GoodnessSearchRangeZNumber=29
export GoodnessSearchRangeZmin=-700 # (cm)
export GoodnessSearchRangeZWidth=50 # (cm)
export GoodnessSearchRangeTNumber=300
export GoodnessSearchRangeTmin=-300 # (ns)
export GoodnessSearchRangeTWidth=1 # (ns)
export GoodnessSearchNumber=10000

export SERVENAME=workq

infilelist=(`grep -rlI nospread /rhome/fujigami/retro/lowe/analizefile | xargs grep -rl EmitPositionSphereCenterX,double,0 | xargs grep -rl EmitPositionSphereRadius,double,200 | xargs grep -rl DarkRate,double,4.2 | xargs grep -rl ParticleEnergyFixedValue,double,15`)

echo "${#infilelist[@]}"
sleep 2

for infilehead in "${infilelist[@]}"
do
    cp process_Goodness_contents.sh process_Goodness_contents_replaced.sh
    chmod +x process_Goodness_contents_replaced.sh
    ./process_Goodness_contents_replaced.sh
    sleep 2
done

