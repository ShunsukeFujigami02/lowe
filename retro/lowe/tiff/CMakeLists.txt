cmake_minimum_required(VERSION 3.10)
project(tiff CXX)
find_package(TinyTIFF REQUIRED PATHS /rhome/fujigami/retro/TinyTIFF_install)
find_package(ROOT REQUIRED PATHS /rhome/fujigami/retro/root_build)
include_directories(${ROOT_INCLUDE_DIRS} /rhome/fujigami/retro/TinyTIFF_install/include)

add_library(tiff STATIC ./src/config.cc
		 	./src/photo_to_hist.cc
			./src/integral_photo.cc
			./src/index_image.cc
			./src/histmacro.cc
			./src/CArea.cc
			)
target_include_directories(tiff PUBLIC ./include)
target_link_libraries(tiff TinyTIFF)

add_library(macro SHARED ./macro/src/histmacro.cc
		  	 ./macro/src/funclist.cc
			 )
target_include_directories(macro PUBLIC ./macro/include)

add_executable(TinyTIFF_test ./exe/TinyTIFF_test.cc)
target_compile_options(TinyTIFF_test PRIVATE "-Wall")
target_link_libraries(TinyTIFF_test TinyTIFF tiff ${ROOT_LIBRARIES})

add_executable(makehist ./exe/makehist.cc)
target_compile_options(makehist PRIVATE "-Wall")
target_link_libraries(makehist tiff ${ROOT_LIBRARIES})

add_executable(integral_photo ./exe/integral_photo_exe.cc)
target_compile_options(integral_photo PRIVATE "-Wall")
target_link_libraries(integral_photo tiff ${ROOT_LIBRARIES})

add_executable(integral_photo_dis ./exe/integral_photo_dis.cc)
target_compile_options(integral_photo_dis PRIVATE "-Wall")
target_link_libraries(integral_photo_dis tiff ${ROOT_LIBRARIES})

add_executable(fitting_responce_ccd ./exe/fitting_responce_ccd.cc)
target_compile_options(fitting_responce_ccd PRIVATE "-Wall")
target_link_libraries(fitting_responce_ccd tiff ${ROOT_LIBRARIES})

add_executable(gamma_correction ./exe/gamma_correction.cc)
target_compile_options(gamma_correction PRIVATE "-Wall")
target_link_libraries(gamma_correction tiff ${ROOT_LIBRARIES})

add_executable(reflectivity_angle_dis ./exe/reflectivity_angle_dis.cc)
target_compile_options(reflectivity_angle_dis PRIVATE "-Wall")
target_link_libraries(reflectivity_angle_dis tiff ${ROOT_LIBRARIES})
