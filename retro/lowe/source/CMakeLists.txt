
cmake_minimum_required(VERSION 3.1)
project(lowe_make)
#option (USE_PERF "Use Google Profiler" OFF)

find_package(ROOT REQUIRED)
if(NOT ROOT_FOUND)
  message(STATUS "ROOT package not found.")
  return()
endif()

set(ROOT_LIBRARIES ${ROOT_LIBRARIES} "/rhome/fujigami/retro/root-6.08.02_build/lib/libMinuit.so")
#set(ROOT_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} "/disk1/opt/root-v5.34.38/root-5.34.38/bindings/pyroot/inc")
set(ROOT_LIBRARIES ${ROOT_LIBRARIES} "/rhome/fujigami/retro/root-6.08.02_build/lib/libPyROOT.so")

find_package(Geant4 REQUIRED)
if(NOT Geant4_FOUND)
  message(STATUS "Geant4 package not found.")
  return()
endif()
include(${ROOT_USE_FILE})
include_directories($ENV{WCSIMDIR}/include ${ROOT_INCLUDE_DIRS} ${Geant4_INCLUDE_DIR})
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -mtune=native -march=native")

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")


ROOT_GENERATE_DICTIONARY($ENV{MACRODIR}/src/macroRootDict $ENV{MACRODIR}/include/eventdisplay.hh $ENV{MACRODIR}/include/goodness_data.hh $ENV{MACRODIR}/include/likelihood_direction_data.hh $ENV{MACRODIR}/include/AnalizedData.hh $ENV{MACRODIR}/include/CSearch_range.hh LINKDEF $ENV{MACRODIR}/include/C4Number.hh $ENV{MACRODIR}/include/FileList.hh $ENV{MACRODIR}/include/efficiency.hh $ENV{MACRODIR}/include/HistByTree.hh $ENV{MACRODIR}/include/HistError.hh $ENV{MACRODIR}/include/HistBias.hh $ENV{MACRODIR}/include/AngleRange.hh $ENV{MACRODIR}/include/Thitinfo.hh $ENV{MACRODIR}/include/TReconstructdata.hh $ENV{MACRODIR}/include/Tfunction.hh $ENV{MACRODIR}/include/Tafunction.hh $ENV{MACRODIR}/include/Tdistance_function.hh $ENV{MACRODIR}/include/Tfdirection.hh $ENV{MACRODIR}/include/Tlikelihood.hh $ENV{MACRODIR}/include/Ttheta_dir_i.hh $ENV{MACRODIR}/include/Ttheta_i_func.hh $ENV{MACRODIR}/include/Ttof.hh $ENV{MACRODIR}/include/Tfgoodnessdirection.hh $ENV{MACRODIR}/include/TOption_minimize.hh $ENV{MACRODIR}/include/Tfgoodness.hh $ENV{MACRODIR}/include/Tfsumgoodness.hh $ENV{MACRODIR}/include/BiasError.hh $ENV{MACRODIR}/include/FileManager.hh $ENV{MACRODIR}/include/AnalizeTag.hh $ENV{MACRODIR}/include/AnalizeManager.hh $ENV{MACRODIR}/include/AnalizeFile.hh $ENV{MACRODIR}/include/TNinWater.hh macro/include/macroRootLinkDef.hh)

add_library(lowemacro SHARED $ENV{MACRODIR}/src/eventdisplay.cc
		      	     $ENV{MACRODIR}/src/goodness_data.cc
			     $ENV{MACRODIR}/src/likelihood_direction_data.cc
			     $ENV{MACRODIR}/src/AnalizedData.cc
			     $ENV{MACRODIR}/src/CSearch_range.cc
			     $ENV{MACRODIR}/src/C4Number.cc
			     $ENV{MACRODIR}/src/macroRootDict.cxx
			     $ENV{MACRODIR}/src/FileList.cc
			     $ENV{MACRODIR}/src/efficiency.cc
			     $ENV{MACRODIR}/src/HistByTree.cc
			     $ENV{MACRODIR}/src/HistError.cc
			     $ENV{MACRODIR}/src/HistBias.cc
			     $ENV{MACRODIR}/src/AngleRange.cc
			     $ENV{MACRODIR}/src/Thitinfo.cc
			     $ENV{MACRODIR}/src/TReconstructdata.cc
			     $ENV{MACRODIR}/src/Tafunction.cc
			     $ENV{MACRODIR}/src/Tdistance_function.cc
			     $ENV{MACRODIR}/src/Tfdirection.cc
			     $ENV{MACRODIR}/src/Tlikelihood.cc
			     $ENV{MACRODIR}/src/Ttheta_dir_i.cc
			     $ENV{MACRODIR}/src/Ttheta_i_func.cc
			     $ENV{MACRODIR}/src/Ttof.cc
			     $ENV{MACRODIR}/src/TOption_minimize.cc
			     $ENV{MACRODIR}/src/BiasError.cc
			     $ENV{MACRODIR}/src/Tfgoodness.cc
			     $ENV{MACRODIR}/src/Tfgoodnessdirection.cc
			     $ENV{MACRODIR}/src/Tfsumgoodness.cc
			     $ENV{MACRODIR}/src/Tfunction.cc
			     $ENV{MACRODIR}/src/AnalizeTag.cc
			     $ENV{MACRODIR}/src/AnalizeFile.cc
			     $ENV{MACRODIR}/src/FileManager.cc
			     $ENV{MACRODIR}/src/AnalizeManager.cc
			     $ENV{MACRODIR}/src/rotation3D.cc
			     $ENV{MACRODIR}/src/TNinWater.cc
			     $ENV{MACRODIR}/src/AnalizeFiledata.cc
			     $ENV{MACRODIR}/src/MinimizedFunction.cc
			     $ENV{MACRODIR}/src/theta_i_func.cc
			     $ENV{MACRODIR}/src/distance_function.cc
			     $ENV{MACRODIR}/src/fdirection.cc
			     $ENV{MACRODIR}/src/likelihood.cc
			     $ENV{MACRODIR}/src/theta_dir_i.cc
			     $ENV{MACRODIR}/src/tof.cc
			     $ENV{MACRODIR}/src/fgoodness.cc
			     $ENV{MACRODIR}/src/fgoodnessdirection.cc
			     $ENV{MACRODIR}/src/fsumgoodness.cc
			     $ENV{MACRODIR}/src/onelikelihoodtof.cc
			     $ENV{MACRODIR}/src/distanceerror.cc
			     $ENV{MACRODIR}/src/Energy.cc)
target_include_directories(lowemacro PUBLIC $ENV{MACRODIR}/include
                                            ../../fmath
				            $ENV{WCSIMDIR}/include
					    ${ROOT_INCLUDE_DIRS}
					    ${Geant4_INCLUDE_DIR})
target_link_libraries(lowemacro ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_library(lowe SHARED     ./general/src/config.cc
			    ./general/src/funcmap.cc
			    ./others/src/test.cc
#			    ./funcparts/src/theta_i_func.cc
#			    ./funcparts/src/distance_function.cc
#			    ./funcparts/src/fdirection.cc
#			    ./funcparts/src/likelihood.cc
#			    ./funcparts/src/theta_dir_i.cc
#			    ./funcparts/src/tof.cc
#			    ./funcparts/src/fgoodness.cc
#			    ./funcparts/src/fgoodnessdirection.cc
#			    ./funcparts/src/fsumgoodness.cc
#			    ./funcparts/src/onelikelihoodtof.cc
#			    ./funcparts/src/distanceerror.cc
#			    ./funcparts/src/Energy.cc
			    ./goodness/src/GoodnessManager.cc
			    ./goodness/src/GoodnessRunAction.cc
			    ./goodness/src/GoodnessEventManager.cc
			    ./goodness/src/GoodnessEvent.cc
			    ./goodness/src/GoodnessEventAction.cc
			    ./goodness/src/GoodnessParameters.cc
			    ./goodness/src/GoodnessVerboseManager.cc
			    ./goodness/src/GoodnessVerboseEventManager.cc
			    ./goodness/src/GoodnessVerboseCalculateManager.cc
			    ./goodness/src/GoodnessVerboseCalculateAction.cc
#			    ./goodness/src/GoodnessMinimizeManager.cc
#			    ./goodness/src/GoodnessMinimizeEventManager.cc
#			    ./goodness/src/GoodnessMinimizeRunAction.cc
#			    ./goodness/src/GoodnessMinimizeEventAction.cc
			    ./likelihood/src/LikelihoodDirectionManager.cc
#			    ./likelihood/src/LikelihoodDirectionCalculateManager.cc
			    ./likelihood/src/LikelihoodDirectionRunAction.cc
			    ./likelihood/src/LikelihoodDirectionEventAction.cc
			    ./likelihood/src/LikelihoodDirectionEventManager.cc
#			    ./likelihood/src/OneLikelihoodDirectionCalculateManager.cc
			    ./virtual/src/ProcessManager.cc
			    ./virtual/src/VAction.cc
			    ./minimize/src/MinimizeEventManager.cc
			    ./minimize/src/MinimizeManager.cc
#			    ./minimize/src/MinimizedFunction.cc
			    ./minimize/src/MinimizeRunAction.cc
			    ./minimize/src/MinimizeEventAction.cc)
target_include_directories(lowe PUBLIC ./goodness/include
				       ./likelihood/include
				       ./general/include
#				       ./funcparts/include
				       ./others/include
				       ./virtual/include
				       ./interface/include
				       ./minimize/include
				       $ENV{MACRODIR}/include
				       $ENV{WCSIMDIR}/include
				       ../../fmath
				       ${ROOT_INCLUDE_DIRS}
				       ${Geant4_INCLUDE_DIR})

target_link_libraries(lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so ${Geant4_LIBRARIES})


#add_executable(goodness_moment ./exe/goodness/goodness_moment.cc)
#target_compile_options(goodness_moment PRIVATE "-Wall")
#target_link_libraries(goodness_moment lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(convert ./exe/others/convert.cc)
target_compile_options(convert PRIVATE "-Wall")
target_link_libraries(convert lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(N200 ./exe/others/N200.cc)
target_compile_options(N200 PRIVATE "-Wall")
target_link_libraries(N200 lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(test1 ./exe/others/test.cc)

# Google Performance Analyzer
#if (USE_PERF)
#   find_library(GPERFTOOLS_LIBRARIES NAMES profiler HINTS $ENV{GPERFTOOLS})
#   target_link_libraries (test1 ${GPERFTOOLS_LIBRARIES})
#   message (STATUS "USE_PERF=${USE_PERF}")
#   message (STATUS "GPERFTOOLS_LIBRARIES=${GPERFTOOLS_LIBRARIES}")
#endif (USE_PERF)

target_compile_options(test1 PRIVATE "-Wall")
target_link_libraries(test1 lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(f_direction_use_fitting ./exe/likelihood/f_direction_use_fitting.cc)
target_compile_options(f_direction_use_fitting PRIVATE "-Wall")
target_link_libraries(f_direction_use_fitting ${ROOT_LIBRARIES})

add_executable(Goodness ./exe/goodness/Goodness.cc)
# Google Performance Analyzer
#if (USE_PERF)
#   find_library(GPERFTOOLS_LIBRARIES NAMES profiler HINTS $ENV{GPERFTOOLS})
#   target_link_libraries (Goodness ${GPERFTOOLS_LIBRARIES})
#   message (STATUS "USE_PERF=${USE_PERF}")
#   message (STATUS "GPERFTOOLS_LIBRARIES=${GPERFTOOLS_LIBRARIES}")
#endif (USE_PERF)

target_compile_options(Goodness PRIVATE "-Wall")
target_link_libraries(Goodness lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(LikelihoodDirection ./exe/likelihood/LikelihoodDirection.cc)

# Google Performance Analyzer
#if (USE_PERF)
#   find_library(GPERFTOOLS_LIBRARIES NAMES profiler HINTS $ENV{GPERFTOOLS})
#   target_link_libraries (LikelihoodDirection ${GPERFTOOLS_LIBRARIES})
#   message (STATUS "USE_PERF=${USE_PERF}")
#   message (STATUS "GPERFTOOLS_LIBRARIES=${GPERFTOOLS_LIBRARIES}")
#endif (USE_PERF)

target_compile_options(LikelihoodDirection PRIVATE "-Wall")
target_link_libraries(LikelihoodDirection lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

#add_executable(GoodnessMinimize ./exe/goodness/GoodnessMinimize.cc)
#target_compile_options(GoodnessMinimize PRIVATE "-Wall")
#target_link_libraries(GoodnessMinimize lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

#add_executable(printxyzbias ./exe/macro/printxyzbias.cc)
#target_compile_options(printxyzbias PRIVATE "-Wall")
#target_link_libraries(printxyzbias lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(comparecsv ./exe/macro/comparecsv.cc)
target_compile_options(comparecsv PRIVATE "-Wall")
target_link_libraries(comparecsv lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(isexistsamecsv ./exe/macro/isexistsamecsv.cc)
target_compile_options(isexistsamecsv PRIVATE "-Wall")
target_link_libraries(isexistsamecsv lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(Minimize ./exe/minimize/Minimize.cc)
target_compile_options(Minimize PRIVATE "-Wall")
target_link_libraries(Minimize lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(tof_exe ./exe/others/tof_exe.cc)
target_compile_options(tof_exe PRIVATE "-Wall")
target_link_libraries(tof_exe lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(functionplot ./root/functionplot.cc)
target_compile_options(functionplot PRIVATE "-Wall")
target_link_libraries(functionplot lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(pmtcostheta ./exe/others/pmtcostheta.cc)
target_compile_options(pmtcostheta PRIVATE "-Wall")
target_link_libraries(pmtcostheta lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawtofandcostheta ./root/drawtofandcostheta.cc)
target_compile_options(drawtofandcostheta PRIVATE "-Wall")
target_link_libraries(drawtofandcostheta lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH1Ddouble ./root/drawTH1Ddouble.cc)
target_compile_options(drawTH1Ddouble PRIVATE "-Wall")
target_link_libraries(drawTH1Ddouble lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH1Dsingle ./root/drawTH1Dsingle.cc)
target_compile_options(drawTH1Dsingle PRIVATE "-Wall")
target_link_libraries(drawTH1Dsingle lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH2D ./root/drawTH2D.cc)
target_compile_options(drawTH2D PRIVATE "-Wall")
target_link_libraries(drawTH2D lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(functionplotTH2D ./root/functionplotTH2D.cc)
target_compile_options(functionplotTH2D PRIVATE "-Wall")
target_link_libraries(functionplotTH2D lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH2DHit ./root/drawTH2DHit.cc)
target_compile_options(drawTH2DHit PRIVATE "-Wall")
target_link_libraries(drawTH2DHit lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH1Dbymultifile ./root/drawTH1Dbymultifile.cc)
target_compile_options(drawTH1Dbymultifile PRIVATE "-Wall")
target_link_libraries(drawTH1Dbymultifile lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH1DHit ./root/drawTH1DHit.cc)
target_compile_options(drawTH1DHit PRIVATE "-Wall")
target_link_libraries(drawTH1DHit lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(functionplotTH2DTrueaxis ./root/functionplotTH2DTrueaxis.cc)
target_compile_options(functionplotTH2DTrueaxis PRIVATE "-Wall")
target_link_libraries(functionplotTH2DTrueaxis lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH1Dtriple ./root/drawTH1Dtriple.cc)
target_compile_options(drawTH1Dtriple PRIVATE "-Wall")
target_link_libraries(drawTH1Dtriple lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH1Dmultifile ./root/drawTH1Dmultifile.cc)
target_compile_options(drawTH1Dmultifile PRIVATE "-Wall")
target_link_libraries(drawTH1Dmultifile lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(distanceerror_exe ./exe/others/distanceerror_exe.cc)
target_compile_options(distanceerror_exe PRIVATE "-Wall")
target_link_libraries(distanceerror_exe lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(distanceerror2D_exe ./exe/others/distanceerror2D_exe.cc)
target_compile_options(distanceerror2D_exe PRIVATE "-Wall")
target_link_libraries(distanceerror2D_exe lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(distanceerror1D_exe ./exe/others/distanceerror1D_exe.cc)
target_compile_options(distanceerror1D_exe PRIVATE "-Wall")
target_link_libraries(distanceerror1D_exe lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(distanceerror_drawfittingparameter ./exe/others/distanceerror_drawfittingparameter.cc)
target_compile_options(distanceerror_drawfittingparameter PRIVATE "-Wall")
target_link_libraries(distanceerror_drawfittingparameter lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

#add_executable(TOFbytruetrack ./exe/others/TOFbytruetrack.cc)
#target_compile_options(TOFbytruetrack PRIVATE "-Wall")
#target_link_libraries(TOFbytruetrack lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

#add_executable(TOFbytruetrackOnRetro ./exe/others/TOFbytruetrackOnRetro.cc)
#target_compile_options(TOFbytruetrackOnRetro PRIVATE "-Wall")
#target_link_libraries(TOFbytruetrackOnRetro lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(GetTagContents ./exe/macro/GetTagContents.cc)
target_compile_options(GetTagContents PRIVATE "-Wall")
target_link_libraries(GetTagContents lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(Photocoverage ./exe/others/Photocoverage.cc)
target_compile_options(Photocoverage PRIVATE "-Wall")
target_link_libraries(Photocoverage lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(NearPMT ./exe/others/NearPMT.cc)
target_compile_options(NearPMT PRIVATE "-Wall")
target_link_libraries(NearPMT lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(EnergyReconstruction ./exe/others/EnergyReconstruction.cc)
target_compile_options(EnergyReconstruction PRIVATE "-Wall")
target_link_libraries(EnergyReconstruction lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH1DHitsingle ./root/drawTH1DHitsingle.cc)
target_compile_options(drawTH1DHitsingle PRIVATE "-Wall")
target_link_libraries(drawTH1DHitsingle lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawTH1DRun ./root/drawTH1DRun.cc)
target_compile_options(drawTH1DRun PRIVATE "-Wall")
target_link_libraries(drawTH1DRun lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(EnergyAnalize ./root/EnergyAnalize.cc)
target_compile_options(EnergyAnalize PRIVATE "-Wall")
target_link_libraries(EnergyAnalize lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(momentumdis ./exe/others/momentumdis.cc)
target_compile_options(momentumdis PRIVATE "-Wall")
target_link_libraries(momentumdis lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(CompareNhits ./root/CompareNhits.cc)
target_compile_options(CompareNhits PRIVATE "-Wall")
target_link_libraries(CompareNhits lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(efficientHitsMeanCompareNoRetroOnRetroSideCenter ./root/efficientHitsMeanCompareNoRetroOnRetroSideCenter.cc)
target_compile_options(efficientHitsMeanCompareNoRetroOnRetroSideCenter PRIVATE "-Wall")
target_link_libraries(efficientHitsMeanCompareNoRetroOnRetroSideCenter lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(efficientHitsDirectPartMeanCompareNoRetroOnRetroSideCenter ./root/efficientHitsDirectPartMeanCompareNoRetroOnRetroSideCenter.cc)
target_compile_options(efficientHitsDirectPartMeanCompareNoRetroOnRetroSideCenter PRIVATE "-Wall")
target_link_libraries(efficientHitsDirectPartMeanCompareNoRetroOnRetroSideCenter lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(efficientHitsReflectPartMeanCompareNoRetroOnRetroSideCenter ./root/efficientHitsReflectPartMeanCompareNoRetroOnRetroSideCenter.cc)
target_compile_options(efficientHitsReflectPartMeanCompareNoRetroOnRetroSideCenter PRIVATE "-Wall")
target_link_libraries(efficientHitsReflectPartMeanCompareNoRetroOnRetroSideCenter lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(efficientHitsDis ./root/efficientHitsDis.cc)
target_compile_options(efficientHitsDis PRIVATE "-Wall")
target_link_libraries(efficientHitsDis lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(drawCorrectionCoefficient ./root/drawCorrectionCoefficient.cc)
target_compile_options(drawCorrectionCoefficient PRIVATE "-Wall")
target_link_libraries(drawCorrectionCoefficient lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(MeanChangeLambda ./root/MeanChangeLambda.cc)
target_compile_options(MeanChangeLambda PRIVATE "-Wall")
target_link_libraries(MeanChangeLambda lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(sigmachangeRandE ./root/sigmachangeRandE.cc)
target_compile_options(sigmachangeRandE PRIVATE "-Wall")
target_link_libraries(sigmachangeRandE lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)
