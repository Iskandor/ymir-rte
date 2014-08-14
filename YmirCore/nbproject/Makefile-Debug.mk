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
	${OBJECTDIR}/src/CAction.o \
	${OBJECTDIR}/src/CMap.o \
	${OBJECTDIR}/src/CMathUtils.o \
	${OBJECTDIR}/src/CObject.o \
	${OBJECTDIR}/src/CObjectEntity.o \
	${OBJECTDIR}/src/CObjectManager.o \
	${OBJECTDIR}/src/CPlayer.o \
	${OBJECTDIR}/src/CPlayerManager.o \
	${OBJECTDIR}/src/CRace.o \
	${OBJECTDIR}/src/CStrUtils.o \
	${OBJECTDIR}/src/CTile.o \
	${OBJECTDIR}/src/CUnit.o \
	${OBJECTDIR}/src/CUnitEntity.o \
	${OBJECTDIR}/src/CUnitManager.o \
	${OBJECTDIR}/src/CUnitModuleManager.o \
	${OBJECTDIR}/src/CUtils.o \
	${OBJECTDIR}/src/CXmlSerializable.o


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
LDLIBSOPTIONS=-L/usr/lib -lSDL

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/libYmirCore.${CND_DLIB_EXT}

bin/libYmirCore.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p bin
	${LINK.cc} -o bin/libYmirCore.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/CAction.o: src/CAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CAction.o src/CAction.cpp

${OBJECTDIR}/src/CMap.o: src/CMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CMap.o src/CMap.cpp

${OBJECTDIR}/src/CMathUtils.o: src/CMathUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CMathUtils.o src/CMathUtils.cpp

${OBJECTDIR}/src/CObject.o: src/CObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CObject.o src/CObject.cpp

${OBJECTDIR}/src/CObjectEntity.o: src/CObjectEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CObjectEntity.o src/CObjectEntity.cpp

${OBJECTDIR}/src/CObjectManager.o: src/CObjectManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CObjectManager.o src/CObjectManager.cpp

${OBJECTDIR}/src/CPlayer.o: src/CPlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CPlayer.o src/CPlayer.cpp

${OBJECTDIR}/src/CPlayerManager.o: src/CPlayerManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CPlayerManager.o src/CPlayerManager.cpp

${OBJECTDIR}/src/CRace.o: src/CRace.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CRace.o src/CRace.cpp

${OBJECTDIR}/src/CStrUtils.o: src/CStrUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CStrUtils.o src/CStrUtils.cpp

${OBJECTDIR}/src/CTile.o: src/CTile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CTile.o src/CTile.cpp

${OBJECTDIR}/src/CUnit.o: src/CUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CUnit.o src/CUnit.cpp

${OBJECTDIR}/src/CUnitEntity.o: src/CUnitEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CUnitEntity.o src/CUnitEntity.cpp

${OBJECTDIR}/src/CUnitManager.o: src/CUnitManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CUnitManager.o src/CUnitManager.cpp

${OBJECTDIR}/src/CUnitModuleManager.o: src/CUnitModuleManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CUnitModuleManager.o src/CUnitModuleManager.cpp

${OBJECTDIR}/src/CUtils.o: src/CUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CUtils.o src/CUtils.cpp

${OBJECTDIR}/src/CXmlSerializable.o: src/CXmlSerializable.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I/usr/include/qt4 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CXmlSerializable.o src/CXmlSerializable.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/libYmirCore.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
