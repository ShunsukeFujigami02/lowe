#!/bin/bash

export infilehead="/rhome/fujigami/retro/lowe/analizefile/wcsim_20211101_102748.csv"
export GoodnessSigma=5 # (ns)
export GoodnessType="NoRetro"
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
export GoodnessSearchNumber=1000

export SERVENAME=workq

cp process_Goodness_contents.sh process_Goodness_contents_replaced.sh
chmod +x process_Goodness_contents_replaced.sh
./process_Goodness_contents_replaced.sh
