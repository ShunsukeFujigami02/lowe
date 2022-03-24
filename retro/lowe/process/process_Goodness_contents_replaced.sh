#!/bin/bash

outputfile="Goodness_`date '+%Y%m%d_%H%M%S'`"
outputfilecsv="$HOME/retro/lowe/analizefile/${outputfile}.csv"
outputfileroot="$HOME/retro/lowe/analizefile/${outputfile}.root"
conftemp="$HOME/retro/lowe/config/config_Goodness_template.sh"
confhalf="$HOME/retro/lowe/config/half.sh"
today=$(date)

cp ${conftemp} ${confhalf}
confname="$HOME/retro/lowe/config/${outputfile}.sh"
logname="$HOME/retro/lowe/log/${outputfile}.log"
jobname="$HOME/retro/lowe/sh/${outputfile}.sh"

infilehead=${infilehead%.*}

infilecsv="${infilehead}.csv"
infileroot="${infilehead}.root"

if [ ! -f $infileroot ];then
    echo $infileroot + "is not exist... exit"
    exit
fi

if [ ! -f $infilecsv ];then
    echo $infilecsv + "is not exist... exit"
    exit
fi

echo ${infilecsv} > ${outputfilecsv}

sed -i -e "s!infile!${infileroot}!g" ${confhalf}

echo "GoodnessSigma,double,${GoodnessSigma}" >> ${outputfilecsv}

sed -i -e "s/sigma/${GoodnessSigma}/g" ${confhalf}

echo "GoodnessType,string,${GoodnessType}" >> ${outputfilecsv}


if [ ${GoodnessType} = "NoRetro" ];then
    sed -i -e "s/goodnesstype/no_retro/g" ${confhalf}
elif [ ${GoodnessType} = "OnRetro" ];then
    sed -i -e "s/goodnesstype/on_retro/g" ${confhalf}
elif [ ${GoodnessType} = "sum" ];then
    sed -i -e "s/goodnesstype/sum/g" ${confhalf}
elif [ ${GoodnessType} = "compare" ];then
    sed -i -e "s/goodnesstype/compare/g" ${confhalf}
elif [ ${GoodnessType} = "NoRetro_digital" ];then
    sed -i -e "s/goodnesstype/no_retro_digital/g" ${confhalf}
elif [ ${GoodnessType} = "compare_digital" ];then
    sed -i -e "s/goodnesstype/compare_digital/g" ${confhalf}
elif [ ${GoodnessType} = "compare_nodigital" ];then
    sed -i -e "s/goodnesstype/compare_nodigital/g" ${confhalf}
elif [ ${GoodnessType} = "compare_nodigital_ver3" ];then
    sed -i -e "s/goodnesstype/compare_nodigital_ver3/g" ${confhalf}
else
    echo ${GoodnessType} "is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "GoodnessSearchRangeType,string,${GoodnessSearchRangeType}" >> ${outputfilecsv}

if [ ${GoodnessSearchRangeType} = "true" ];then
    sed -i -e "s/goodnesssearchrangetype/True/g" ${confhalf}
elif [ ${GoodnessSearchRangeType} = "normal" ];then
    sed -i -e "s/searchxmin/${GoodnessSearchRangeXmin}/g" ${confhalf}
    sed -i -e "s/searchymin/${GoodnessSearchRangeYmin}/g" ${confhalf}
    sed -i -e "s/searchzmin/${GoodnessSearchRangeZmin}/g" ${confhalf}
    sed -i -e "s/searchtmin/${GoodnessSearchRangeTmin}/g" ${confhalf}
    sed -i -e "s/searchxwidth/${GoodnessSearchRangeXWidth}/g" ${confhalf}
    sed -i -e "s/searchywidth/${GoodnessSearchRangeYWidth}/g" ${confhalf}
    sed -i -e "s/searchzwidth/${GoodnessSearchRangeZWidth}/g" ${confhalf}
    sed -i -e "s/searchtwidth/${GoodnessSearchRangeTWidth}/g" ${confhalf}
    sed -i -e "s/searchxnumber/${GoodnessSearchRangeXNumber}/g" ${confhalf}
    sed -i -e "s/searchynumber/${GoodnessSearchRangeYNumber}/g" ${confhalf}
    sed -i -e "s/searchznumber/${GoodnessSearchRangeZNumber}/g" ${confhalf}
    sed -i -e "s/searchtnumber/${GoodnessSearchRangeTNumber}/g" ${confhalf}
    echo "GoodnessSearchRangeXNumber,int,${GoodnessSearchRangeXNumber}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeXmin,double,${GoodnessSearchRangeXmin}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeXWidth,double,${GoodnessSearchRangeXWidth}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeYNumber,int,${GoodnessSearchRangeYNumber}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeYmin,double,${GoodnessSearchRangeYmin}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeYWidth,double,${GoodnessSearchRangeYWidth}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeZNumber,int,${GoodnessSearchRangeZNumber}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeZmin,double,${GoodnessSearchRangeZmin}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeZWidth,double,${GoodnessSearchRangeZWidth}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeTNumber,int,${GoodnessSearchRangeTNumber}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeTmin,double,${GoodnessSearchRangeTmin}" >> ${outputfilecsv}
    echo "GoodnessSearchRangeTWidth,double,${GoodnessSearchRangeTWidth}" >> ${outputfilecsv}
    sed -i -e "s/goodnesssearchrangetype/normal/g" ${confhalf}
else
    echo ${GoodnessSearchRangeType} + "is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

reflectivityfactor=`../build/GetTagContents ${infilecsv} ReflectivityFactorTrapezoidReflectivity double`
if [ ${reflectivityfactor} = "false" ];then
    sed -i -e "s/reflectivity/0.3/g" ${confhalf}
else
    sed -i -e "s/reflectivity/${reflectivityfactor}/g" ${confhalf}
fi

echo "GoodnessSearchNumber,int,${GoodnessSearchNumber}" >> ${outputfilecsv}

echo "GoodnessVersion,int,2" >> ${outputfilecsv}

sed -i -e "s/goodnesseventnumber/${GoodnessSearchNumber}/g" ${confhalf}
isexistsamefile=`../build/isexistsamecsv ${outputfilecsv}`
if [ ${isexistsamefile} = "true" ];then
    echo ${outputfilecsv} + "is already exist... exit"
    \rm ${outputfilecsv}
    exit
elif [ ${isexistsamefile} = "false" ];then
    :
else
    echo ${isexistsamefile} + "is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

sed -i -e "s!outfile!${outputfileroot}!g" ${confhalf}
cp ${confhalf} ${confname}
echo "# Generated by the script at ${today} from ${conftemp} by $0" >> ${confname}

if [ ! -f $confname ]; then
    echo $confname + " is not exist... exit"
    \rm ${outputfilecsv}
    exit
fi
echo "log of ${outputfile}" > "$logname"
echo '#!/bin/bash' > "$jobname"
echo "cd '$PWD'" >> "$jobname"
echo "source ../../setup.sh" >> "$jobname"
echo "source ../setup.sh" >> "$jobname"
echo "source $confname" >> "$jobname"
echo "(time ../build/Goodness) > "$logname" 2>&1" >> "$jobname"
echo "isseg=\`grep 'segmentation violation' ${logname}\`" >> "$jobname"
echo "if [ -n \"\$isseg\" ];then" >> "$jobname"
echo "   \rm ${outputfilecsv}" >> "$jobname"
echo "   \rm ${outputfileroot}" >> "$jobname"
echo "fi" >> "$jobname"
chmod +x "$jobname"
qsub -q ${SERVENAME} -e /dev/null -o /dev/null "$jobname"
