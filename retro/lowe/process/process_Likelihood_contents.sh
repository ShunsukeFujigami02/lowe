#!/bin/bash

outputfile="Likelihood_`date '+%Y%m%d_%H%M%S'`"
outputfilecsv="$HOME/retro/lowe/analizefile/${outputfile}.csv"
outputfileroot="$HOME/retro/lowe/analizefile/${outputfile}.root"
conftemp="$HOME/retro/lowe/config/config_LikelihoodDirection_template.sh"
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

echo "LikelihoodType,string,${LikelihoodType}" >> ${outputfilecsv}

if [ ${LikelihoodType} = "NoRetro" ];then
    sed -i -e "s/onelikelihooddirectioncalculatetype/noretro/g" ${confhalf}
elif [ ${LikelihoodType} = "Sum" ];then
    sed -i -e "s/onelikelihooddirectioncalculatetype/sum/g" ${confhalf}
else
    echo ${LikelihoodType} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi
echo "LikelihoodNoRetroFunction,string,${LikelihoodNoRetroFunction}" >> ${outputfilecsv}
if [ ${LikelihoodNoRetroFunction} = "Prototype" ];then
    sed -i -e "s/fdirectionnoretrotype/prototype/g" ${confhalf}
elif [ ${LikelihoodNoRetroFunction} = "ByData" ];then
    sed -i -e "s/fdirectionnoretrotype/bydata/g" ${confhalf}
else
    echo ${LikelihoodNoRetroFunction} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi
echo "LikelihoodOnRetroFunction,string,${LikelihoodOnRetroFunction}" >> ${outputfilecsv}

if [ ${LikelihoodOnRetroFunction} = "NotUse" ];then
    sed -i -e "s/fdirectiononretrotype/prototype/g" ${confhalf}
elif [ ${LikelihoodOnRetroFunction} = "Prototype" ];then
    sed -i -e "s/fdirectiononretrotype/prototype/g" ${confhalf}
elif [ ${LikelihoodOnRetroFunction} = "ByData" ];then
    sed -i -e "s/fdirectiononretrotype/bydata/g" ${confhalf}
else
    echo ${LikelihoodOnRetroFunction} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi
echo "LikelihoodNoRetroAcceptanceFunction,string,${LikelihoodNoRetroAcceptanceFunction}" >> ${outputfilecsv}
if [ ${LikelihoodNoRetroAcceptanceFunction} = "Prototype" ];then
    sed -i -e "s/afuncnoretrotype/prototype/g" ${confhalf}
else	
    echo ${LikelihoodNoRetroAcceptanceFunction} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "LikelihoodOnRetroAcceptanceFunction,string,${LikelihoodOnRetroAcceptanceFunction}" >> ${outputfilecsv}
if [ ${LikelihoodOnRetroAcceptanceFunction} = "NotUse" ];then
    sed -i -e "s/afunconretrotype/prototype/g" ${confhalf}
elif [ ${LikelihoodOnRetroAcceptanceFunction} = "Prototype" ];then
    sed -i -e "s/afunconretrotype/prototype/g" ${confhalf}
else
    echo ${LikelihoodOnRetroAcceptanceFunction} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "LikelihoodSearchRange,string,${LikelihoodSearchRange}" >> ${outputfilecsv}

if [ ${LikelihoodSearchRange} = "True" ];then
    sed -i -e "s/likelihoodsearchtype/true/g" ${confhalf}
elif [ ${LikelihoodSearchRange} = "Normal" ];then
    sed -i -e "s/likelihoodsearchtype/normal/g" ${confhalf}
    sed -i -e "s/searchcosthetamin/${LikelihoodSearchCosThetamin}/g" ${confhalf}
    sed -i -e "s/searchcosthetanum/${LikelihoodSearchCosThetaNumber}/g" ${confhalf}
    sed -i -e "s/searchcosthetawidth/${LikelihoodSearchCosThetaWidth}/g" ${confhalf}
    sed -i -e "s/searchphimin/${LikelihoodSearchPhimin}/g" ${confhalf}
    sed -i -e "s/searchphiwidth/${LikelihoodSearchPhiWidth}/g" ${confhalf}
    sed -i -e "s/searchphinum/${LikelihoodSearchPhiNumber}/g" ${confhalf}
    echo "LikelihoodSearchCosThetamin,double,${LikelihoodSearchCosThetamin}" >> ${outputfilecsv}
    echo "LikelihoodSearchCosThetaNumber,int,${LikelihoodSearchCosThetaNumber}" >> ${outputfilecsv}
    echo "LikelihoodSearchCosThetaWidth,double,${LikelihoodSearchCosThetaWidth}" >> ${outputfilecsv}
    echo "LikelihoodSearchPhimin,double,${LikelihoodSearchPhimin}" >> ${outputfilecsv}
    echo "LikelihoodSearchPhiNumber,int,${LikelihoodSearchPhiNumber}" >> ${outputfilecsv}
    echo "LikelihoodSearchPhiWidth,double,${LikelihoodSearchPhiWidth}" >> ${outputfilecsv}
else
    echo ${LikelihoodSearchRange} + "is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "LikelihoodTimeWindowNoRetro,double,${LikelihoodTimeWindowNoRetro}" >> ${outputfilecsv}

sed -i -e "s/timewindownoretro/${LikelihoodTimeWindowNoRetro}/g" ${confhalf}

echo "LikelihoodTimeWindowOnRetro,double,${LikelihoodTimeWindowOnRetro}" >> ${outputfilecsv}

sed -i -e "s/timewindowonretro/${LikelihoodTimeWindowOnRetro}/g" ${confhalf}

echo "LikelihoodEventNumber,int,${LikelihoodEventNumber}" >> ${outputfilecsv}

sed -i -e "s/likelihoodeventnumber/${LikelihoodEventNumber}/g" ${confhalf}


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
echo "(time ../build/LikelihoodDirection) > "$logname" 2>&1" >> "$jobname"
echo "isseg=\`grep 'segmentation violation' ${logname}\`" >> "$jobname"
echo "if [ -n \"\$isseg\" ];then" >> "$jobname"
echo "   \rm ${outputfilecsv}" >> "$jobname"
echo "   \rm ${outputfileroot}" >> "$jobname"
echo "fi" >> "$jobname"
chmod +x "$jobname"
qsub -q ${SERVENAME} -e /dev/null -o /dev/null "$jobname"
