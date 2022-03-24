export Detectortype="HK"
export Particle="electron"
export EmitPositionType="Sphere"
export EmitPositionFixedX=-100 # (cm)
export EmitPositionFixedY=0 # (cm)
export EmitPositionFixedZ=0 # (cm)
export EmitPositionSphereCenterX=0 # (cm)
export EmitPositionSphereCenterY=0 # (cm)
export EmitPositionSphereCenterZ=0 # (cm)
export EmitPositionSphereRadius=200 # (cm)
export EmitDirectionType="isotropic"
export EmitDirectionFixedCostheta=0
export EmitDirectionFixedPhi=0
export ParticleEnergyType="fixed"
export ParticleEnergyFixedValue=5 # (MeV)
export RetroType="OnRetro"
export ReflectivityFactorType="trapezoid"
export ReflectivityFactorTrapezoidReflectivity=1
export ReflectivityFactorTrapezoidAnglemin=20 # (degree)
export ReflectivityFactorTrapezoidAngleMax=60 # (degree)
export ReflectivitySpreadType="nospread"
export TriggerThreshold=27
export TriggerWindow=200 # (ns)
export TriggerPreWindow=-400 # (ns)
export TriggerPostWindow=950 # (ns)
export DarkRate=8.4 # (kHz)
export AdjustForNoise="false"
export WCSimEventNumber=10000

export servname=workq
for ParticleEnergyFixedValue in 5. 6. 7. 8. 9. 10. 11. 12. 13. 14. 15.
do
    for ReflectivityFactorTrapezoidReflectivity in 0.0 0.1 0.2
    do
	cp Launcher_contents.sh Launcher_contents_replaced.sh
	chmod +x Launcher_contents_replaced.sh
	./Launcher_contents_replaced.sh
	sleep 2
    done
done
