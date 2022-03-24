#!/bin/bash
export Detectortype="SK"
export Particle="electron"
export EmitPositionType="fixed"
export EmitPositionFixedX=-1300 # (cm)
export EmitPositionFixedY=0 # (cm)
export EmitPositionFixedZ=-1400 # (cm)
export EmitPositionSphereCenterX=1300 # (cm)
export EmitPositionSphereCenterY=0 # (cm)
export EmitPositionSphereCenterZ=1400 # (cm)
export EmitPositionSphereRadius=200 # (cm)
export EmitPositionCylinderCenterX=0 # (cm)
export EmitPositionCylinderCenterY=0 # (cm)
export EmitPositionCylinderCenterZ=0 # (cm)
export EmitPositionCylinderRadius=100 # (cm)
export EmitPositionCylinderHalfZ=1400 # (cm)
export EmitDirectionType="fixed"
export EmitDirectionFixedCostheta=0.785398
export EmitDirectionFixedPhi=0
export ParticleEnergyType="fixed"
export ParticleEnergyFixedValue=15 # (MeV)
export ParticleEnergyLinearMin=10 # (MeV)
export ParticleEnergyLinearMax=30 # (MeV)
export RetroType="OnRetro"
export ReflectivityFactorType="trapezoid"
export ReflectivityFactorTrapezoidReflectivity=1.0
export ReflectivityFactorTrapezoidAnglemin=20 # (degree)
export ReflectivityFactorTrapezoidAngleMax=60 # (degree)
export ReflectivitySpreadType="nospread"
export TriggerThreshold=24
export TriggerWindow=200 # (ns)
export TriggerPreWindow=-400 # (ns)
export TriggerPostWindow=950 # (ns)
export DarkRate=4.2 # (kHz)
export AdjustForNoise="false"
export WCSimEventNumber=10000

export servname=workq
for ReflectivityFactorTrapezoidReflectivity in 0.4 0.5 0.6 0.7 0.8 0.9
do
    cp Launcher_contents.sh Launcher_contents_replaced.sh
    chmod +x Launcher_contents_replaced.sh
    ./Launcher_contents_replaced.sh
    sleep 2
done
