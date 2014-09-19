#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/CApp.o \
	${OBJECTDIR}/src/CDataManager.o \
	${OBJECTDIR}/src/CGameControls.o \
	${OBJECTDIR}/src/CGuiManager.o \
	${OBJECTDIR}/src/CMapControls.o \
	${OBJECTDIR}/src/CProjectileControls.o \
	${OBJECTDIR}/src/CUnitControls.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath,../YmirCore/bin -L../YmirCore/bin -lYmirCore -lSDL -lSDLmain -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf `pkg-config --libs QtCore` `pkg-config --libs QtGui` `pkg-config --libs QtXml` -lguichan -lguichan_sdl -Wl,-rpath,../YmirEngine/bin -L../YmirEngine/bin -lYmirEngine  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/universe

bin/universe: ../YmirCore/bin/libYmirCore.so

bin/universe: ../YmirEngine/bin/libYmirEngine.so

bin/universe: ${OBJECTFILES}
	${MKDIR} -p bin
	${LINK.cc} -o bin/universe ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/CApp.o: src/CApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 -I/usr/local/include/guichan -I/usr/include/SDL -I../YmirEngine/include `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CApp.o src/CApp.cpp

${OBJECTDIR}/src/CDataManager.o: src/CDataManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 -I/usr/local/include/guichan -I/usr/include/SDL -I../YmirEngine/include `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CDataManager.o src/CDataManager.cpp

${OBJECTDIR}/src/CGameControls.o: src/CGameControls.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 -I/usr/local/include/guichan -I/usr/include/SDL -I../YmirEngine/include `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CGameControls.o src/CGameControls.cpp

${OBJECTDIR}/src/CGuiManager.o: src/CGuiManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 -I/usr/local/include/guichan -I/usr/include/SDL -I../YmirEngine/include `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CGuiManager.o src/CGuiManager.cpp

${OBJECTDIR}/src/CMapControls.o: src/CMapControls.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 -I/usr/local/include/guichan -I/usr/include/SDL -I../YmirEngine/include `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CMapControls.o src/CMapControls.cpp

${OBJECTDIR}/src/CProjectileControls.o: src/CProjectileControls.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 -I/usr/local/include/guichan -I/usr/include/SDL -I../YmirEngine/include `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CProjectileControls.o src/CProjectileControls.cpp

${OBJECTDIR}/src/CUnitControls.o: src/CUnitControls.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 -I/usr/local/include/guichan -I/usr/include/SDL -I../YmirEngine/include `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CUnitControls.o src/CUnitControls.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 -I/usr/local/include/guichan -I/usr/include/SDL -I../YmirEngine/include `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug
	cd ../YmirEngine && ${MAKE}  -f Makefile CONF=Debug
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug
	cd ../YmirEngine && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/universe

# Subprojects
.clean-subprojects:
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../YmirEngine && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../YmirEngine && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
