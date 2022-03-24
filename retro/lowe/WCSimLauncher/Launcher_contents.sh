#!/bin/bash
source ~/retro/setup.sh
source ~/retro/lowe/setup.sh

echo "Starting WCSim"

outputfile="wcsim_`date '+%Y%m%d_%H%M%S'`"
outputfilecsv="$HOME/retro/lowe/analizefile/${outputfile}.csv"
outputfileroottemp="$HOME/retro/lowe/analizefile/${outputfile}.root"
outputfileroot="$HOME/retro/lowe/analizefile/${outputfile}.root"
conftemp="$HOME/retro/lowe/WCSimLauncher/Launch_template/template.mac"
confhalf="$HOME/retro/lowe/WCSimLauncher/config/half.mac"
today=$(date)

cp ${conftemp} ${confhalf}
confname="$HOME/retro/lowe/config/${outputfile}.mac"
logname="$HOME/retro/lowe/log/log_${outputfile}.log"
jobname="$HOME/retro/lowe/WCSimLauncher/jobs/jobs_${outputfile}.sh"

echo -n -e "\n" > ${outputfilecsv}

if [ ${Detectortype} = "SK" ]; then
    sed -i -e 's/WCGEOM/SuperK/g' ${confhalf}
elif [ ${Detectortype} = "HK" ]; then
    sed -i -e 's/WCGEOM/HyperK/g' ${confhalf}
else
    echo ${Detectortype} + " is not vaild... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "Detectortype,string,${Detectortype}" >> ${outputfilecsv}

if [ ${Particle} = "electron" ]; then
    sed -i -e 's/PARTICLE/e-/g' ${confhalf}
elif [ ${Particle} = "positron" ]; then
    sed -i -e 's/PARTICLE/e+/g' ${confhalf}
elif [ ${Particle} = "muon" ]; then
    sed -i -e 's/PARTICLE/mu-/g' ${confhalf}
elif [ ${Particle} = "muonplus" ]; then
    sed -i -e 's/PARTICLE/mu+/g' ${confhalf}
elif [ ${Particle} = "proton" ]; then
    sed -i -e 's/PARTICLE/p/g' ${confhalf}
else
    echo ${Particle} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "Particle,string,${Particle}" >> ${outputfilecsv}

echo "EmitPositionType,string,${EmitPositionType}" >> ${outputfilecsv}

if [ ${EmitPositionType} = "fixed" ];then
    sed -i -e "s!#/gps/position!/gps/position!g" ${confhalf}
    sed -i -e "s/XPOSITION/${EmitPositionFixedX}/g" ${confhalf}
    sed -i -e "s/YPOSITION/${EmitPositionFixedY}/g" ${confhalf}
    sed -i -e "s/ZPOSITION/${EmitPositionFixedZ}/g" ${confhalf}
    echo "EmitPositionFixedX,double,${EmitPositionFixedX}" >> ${outputfilecsv}
    echo "EmitPositionFixedY,double,${EmitPositionFixedY}" >> ${outputfilecsv}
    echo "EmitPositionFixedZ,double,${EmitPositionFixedZ}" >> ${outputfilecsv}
elif [ ${EmitPositionType} = "Sphere" ];then
    sed -i -e "s!#/gps/pos/type!/gps/pos/type!g" ${confhalf}
    sed -i -e "s/GPSPOSTYPE/Volume/g" ${confhalf}
    sed -i -e "s!#/gps/pos/shape!/gps/pos/shape!g" ${confhalf}
    sed -i -e "s/GPSPOSSHAPE/Sphere/g" ${confhalf}
    sed -i -e "s!#/gps/pos/centre!/gps/pos/centre!g" ${confhalf}
    sed -i -e "s/GPSPOSCENTERX/${EmitPositionSphereCenterX}/g" ${confhalf}
    sed -i -e "s/GPSPOSCENTERY/${EmitPositionSphereCenterY}/g" ${confhalf}
    sed -i -e "s/GPSPOSCENTERZ/${EmitPositionSphereCenterZ}/g" ${confhalf}
    sed -i -e "s!#/gps/pos/radius!/gps/pos/radius!g" ${confhalf}
    sed -i -e "s/GPSPOSRADIUS/${EmitPositionSphereRadius}/g" ${confhalf}
    echo "EmitPositionSphereCenterX,double,${EmitPositionSphereCenterX}" >> ${outputfilecsv}
    echo "EmitPositionSphereCenterY,double,${EmitPositionSphereCenterY}" >> ${outputfilecsv}
    echo "EmitPositionSphereCenterZ,double,${EmitPositionSphereCenterZ}" >> ${outputfilecsv}
    echo "EmitPositionSphereRadius,double,${EmitPositionSphereRadius}" >> ${outputfilecsv}
elif [ ${EmitPositionType} = "Cylinder" ];then
    sed -i -e "s!#/gps/pos/type!/gps/pos/type!g" ${confhalf}
    sed -i -e "s/GPSPOSTYPE/Volume/g" ${confhalf}
    sed -i -e "s!#/gps/pos/shape!/gps/pos/shape!g" ${confhalf}
    sed -i -e "s/GPSPOSSHAPE/Cylinder/g" ${confhalf}
    sed -i -e "s!#/gps/pos/centre!/gps/pos/centre!g" ${confhalf}
    sed -i -e "s/GPSPOSCENTERX/${EmitPositionCylinderCenterX}/g" ${confhalf}
    sed -i -e "s/GPSPOSCENTERY/${EmitPositionCylinderCenterY}/g" ${confhalf}
    sed -i -e "s/GPSPOSCENTERZ/${EmitPositionCylinderCenterZ}/g" ${confhalf}
    sed -i -e "s!#/gps/pos/radius!/gps/pos/radius!g" ${confhalf}
    sed -i -e "s/GPSPOSRADIUS/${EmitPositionCylinderRadius}/g" ${confhalf}
    sed -i -e "s!#/gps/pos/halfz!/gps/pos/halfz!g" ${confhalf}
    sed -i -e "s/GPSPOSHALFZ/${EmitPositionCylinderHalfZ}/g" ${confhalf}
    echo "EmitPositionCylinderCenterX,double,${EmitPositionCylinderCenterX}" >> ${outputfilecsv}
    echo "EmitPositionCylinderCenterY,double,${EmitPositionCylinderCenterY}" >> ${outputfilecsv}
    echo "EmitPositionCylinderCenterZ,double,${EmitPositionCylinderCenterZ}" >> ${outputfilecsv}
    echo "EmitPositionCylinderRadius,double,${EmitPositionCylinderRadius}" >> ${outputfilecsv}
    echo "EmitPositionCylinderHalfZ,double,${EmitPositionCylinderHalfZ}" >> ${outputfilecsv}
else
    echo ${EmitPositionType} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "EmitDirectionType,string,${EmitDirectionType}" >> ${outputfilecsv}

if [ ${EmitDirectionType} = "fixed" ];then
    sed -i -e "s!#/gps/direction!/gps/direction!g" ${confhalf}
    xdirection=`echo "scale=10;costheta=$EmitDirectionFixedCostheta;phi=$EmitDirectionFixedPhi;sqrt(1-costheta*costheta)*c(phi)" | bc -l`
    ydirection=`echo "scale=10;costheta=$EmitDirectionFixedCostheta;phi=$EmitDirectionFixedPhi;sqrt(1-costheta*costheta)*s(phi)" | bc -l`
    zdirection=${EmitDirectionFixedCostheta}
    sed -i -e "s/XDIRECTION/${xdirection}/g" ${confhalf}
    sed -i -e "s/YDIRECTION/${ydirection}/g" ${confhalf}
    sed -i -e "s/ZDIRECTION/${zdirection}/g" ${confhalf}
    echo "EmitDirectionFixedCostheta,double,${EmitDirectionFixedCostheta}" >> ${outputfilecsv}
    echo "EmitDirectionFixedPhi,double,${EmitDirectionFixedPhi}" >> ${outputfilecsv}
elif [ ${EmitDirectionType} = "isotropic" ];then
    sed -i -e "s!#/gps/ang/type!/gps/ang/type!g" ${confhalf}
    sed -i -e "s/GPSANGTYPE/iso/g" ${confhalf}
else
    echo ${EmitDirectionType} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "ParticleEnergyType,string,${ParticleEnergyType}" >> ${outputfilecsv}

if [ ${ParticleEnergyType} = "fixed" ];then
    sed -i -e "s!#/gps/energy!/gps/energy!g" ${confhalf}
    sed -i -e "s/ENERGY/${ParticleEnergyFixedValue}/g" ${confhalf}
    echo "ParticleEnergyFixedValue,double,${ParticleEnergyFixedValue}" >> ${outputfilecsv}
elif [ ${ParticleEnergyType} = "linear" ];then
    sed -i -e "s!#/gps/ene/type!/gps/ene/type!g" ${confhalf}
    sed -i -e "s/GPSENETYPE/Lin/g" ${confhalf}
    sed -i -e "s!#/gps/ene/min!/gps/ene/min!g" ${confhalf}
    sed -i -e "s!#/gps/ene/max!/gps/ene/max!g" ${confhalf}
    sed -i -e "s/GPSENEMIN/${ParticleEnergyLinearMin}/g" ${confhalf}
    sed -i -e "s/GPSENEMAX/${ParticleEnergyLinearMax}/g" ${confhalf}
    echo "ParticleEnergyLinearMin,double,${ParticleEnergyLinearMin}" >> ${outputfilecsv}
    echo "ParticleEnergyLinearMax,double,${ParticleEnergyLinearMax}" >> ${outputfilecsv}
else
    echo ${ParticleEnergyType} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "RetroType,string,${RetroType}" >> ${outputfilecsv}

if [ ${RetroType} = "NoRetro" ];then
    sed -i -e 's/SHEET/blacksheet/g' ${confhalf}
elif [ ${RetroType} = "OnRetro" ];then
    sed -i -e 's/SHEET/retro/g' ${confhalf}
else

    echo ${RetroType} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "ReflectivityFactorType,string,${ReflectivityFactorType}" >> ${outputfilecsv}

if [ ${ReflectivityFactorType} = "blacksheet" ];then
    sed -i -e "s!/reflect!#/reflect!g" ${confhalf}
elif [ ${ReflectivityFactorType} = "trapezoid" ];then
    sed -i -e "s/REFLECTIVITY/${ReflectivityFactorTrapezoidReflectivity}/g" ${confhalf}
    sed -i -e "s/ANGLEMIN/${ReflectivityFactorTrapezoidAnglemin}/g" ${confhalf}
    sed -i -e "s/ANGLEMAX/${ReflectivityFactorTrapezoidAngleMax}/g" ${confhalf}
    echo "ReflectivityFactorTrapezoidReflectivity,double,${ReflectivityFactorTrapezoidReflectivity}" >> ${outputfilecsv}
    echo "ReflectivityFactorTrapezoidAnglemin,double,${ReflectivityFactorTrapezoidAnglemin}" >> ${outputfilecsv}
    echo "ReflectivityFactorTrapezoidAngleMax,double,${ReflectivityFactorTrapezoidAngleMax}" >> ${outputfilecsv}
else
    echo ${RFTYPE} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "ReflectivitySpreadType,string,${ReflectivitySpreadType}" >> ${outputfilecsv}

if [ ${ReflectivitySpreadType} = "blacksheet" ];then
    :
elif [ ${ReflectivitySpreadType} = "nospread" ];then
    :
else
    echo ${ReflectivitySpreadType} + " is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "TriggerThreshold,int,${TriggerThreshold}" >> ${outputfilecsv}
sed -i -e "s/TRIGGERTHRESHOLD/${TriggerThreshold}/g" ${confhalf}

echo "TriggerWindow,double,${TriggerWindow}" >> ${outputfilecsv}

sed -i -e "s/TRIGGERWINDOW/${TriggerWindow}/g" ${confhalf}

echo "TriggerPreWindow,double,${TriggerPreWindow}" >> ${outputfilecsv}

sed -i -e "s/PREWINDOW/${TriggerPreWindow}/g" ${confhalf}

echo "TriggerPostWindow,double,${TriggerPostWindow}" >> ${outputfilecsv}

sed -i -e "s/POSTWINDOW/${TriggerPostWindow}/g" ${confhalf}

echo "DarkRate,double,${DarkRate}" >> ${outputfilecsv}

sed -i -e "s/DARKRATE/${DarkRate}/g" ${confhalf}

echo "AdjustForNoise,string,${AdjustForNoise}" >> ${outputfilecsv}

if [ ${AdjustForNoise} = "false" ];then
    sed -i -e 's/ADJUSTFORNOISE/false/g' ${confhalf}
elif [ ${AdjustForNoise} = "true" ];then
    sed -i -e 's/ADJUSTFORNOISE/true/g' ${confhalf}
else
    echo ${AdjustForNoise} "is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

echo "WCSimEventNumber,int,${WCSimEventNumber}" >> ${outputfilecsv}
sed -i -e "s/EVENTNUMBER/${WCSimEventNumber}/g" ${confhalf}

if [ "`git --git-dir=../../WCSim/.git --work-tree=../../WCSim/.git rev-parse --abbrev-ref HEAD`" = "savetrack" ];then
    echo "UseWCSimGitBranch,string,SaveTrack" >> ${outputfilecsv}
elif [ "`git --git-dir=../../WCSim/.git --work-tree=../../WCSim/.git rev-parse --abbrev-ref HEAD`" = "retro" ];then
    echo "UseWCSimGitBranch,string,Retro" >> ${outputfilecsv}
else
    echo "invalid git name!"
    \rm ${outputfilecsv}
    exit
fi

isexistsame=`$HOME/retro/lowe/build/isexistsamecsv ${outputfilecsv}`
if [ ${isexistsame} = "true" ];then
    echo "file is already exist... exit"
    \rm ${outputfilecsv}
    exit
elif [ ${isexistsame} = "false" ];then
    :
else
    echo ${isexistsame} + "is not valid... exit"
    \rm ${outputfilecsv}
    exit
fi

sed -i -e "s!DOFILENAME!${outputfileroottemp}!g" ${confhalf}
cp ${confhalf} ${confname}
echo "# Generated by the script at ${today} from ${conftemp} by $0" >> ${confname}

if [ ! -f $confname ]; then
    echo $confname + " is not exist... exit"
    \rm ${outputfilecsv}
    exit
fi   
cat wcsim_run_template.sh |\
    sed 's!MACFILE!'${confname}'!' |\
    sed 's!log!'${logname}'!' \
        > ${jobname}
chmod +x ${jobname}
qsub -q ${servname} -e /dev/null -o /dev/null ${jobname}
#    bash ${jobname} 
