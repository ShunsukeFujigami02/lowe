
# setup gcc 4.9.4
#prefix="$HOME/retro/gcc-4.9.4-install"
#export PATH="$prefix/bin:$PATH"
#export LD_LIBRARY_PATH="$prefix/lib:$prefix/lib64:$LD_LIBRARY_PATH"
export  CC="$(which gcc)"
export CXX="$(which g++)"

# cmake
#export PATH="$HOME/retro/cmake-3.3.2/bin:$PATH"

# root
source "$HOME/retro/root-6.08.02_build/bin/thisroot.sh"
#alias root="root -l" # do not show splash screen
#KLABOPTDIR=/disk1/opt
#source ${KLABOPTDIR}/root-v5.34.38/install/bin/thisroot.sh
export PYTHONPATH="$ROOTSYS/lib:$PYTHONPATH"

# python

export PATH="$HOME/retro/Python-2.7.18_build/bin:$PATH"
export LD_LIBRARY_PATH="$HOME/retro/Python-2.7.18_build/lib:$LD_LIBRARY_PATH"
# geant4
source "/rhome/fujigami/retro/geant4-10.4.1-customOpBoundary-install/bin/geant4.sh"
# source "/home/fujigami/retro/geant4-10.4.1-install/bin/geant4.sh"

export PATH="$HOME/usr/local/bin:$PATH"

