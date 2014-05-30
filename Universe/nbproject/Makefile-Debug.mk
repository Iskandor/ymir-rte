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
	${OBJECTDIR}/src/CMapControls.o \
	${OBJECTDIR}/src/CMapRender.o \
	${OBJECTDIR}/src/CMapSegment.o \
	${OBJECTDIR}/src/CSprite.o \
	${OBJECTDIR}/src/CTileRender.o \
	${OBJECTDIR}/src/CUnitControls.o \
	${OBJECTDIR}/src/CUnitRender.o \
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
LDLIBSOPTIONS=-Wl,-rpath,../YmirCore/bin -L../YmirCore/bin -lYmirCore -lSDL -lSDLmain -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf `pkg-config --libs QtCore` `pkg-config --libs QtGui` `pkg-config --libs QtXml`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/universe

bin/universe: ../YmirCore/bin/libYmirCore.so

bin/universe: ${OBJECTFILES}
	${MKDIR} -p bin
	${LINK.cc} -o bin/universe ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/CApp.o: src/CApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CApp.o src/CApp.cpp

${OBJECTDIR}/src/CDataManager.o: src/CDataManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CDataManager.o src/CDataManager.cpp

${OBJECTDIR}/src/CMapControls.o: src/CMapControls.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CMapControls.o src/CMapControls.cpp

${OBJECTDIR}/src/CMapRender.o: src/CMapRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CMapRender.o src/CMapRender.cpp

${OBJECTDIR}/src/CMapSegment.o: src/CMapSegment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CMapSegment.o src/CMapSegment.cpp

${OBJECTDIR}/src/CSprite.o: src/CSprite.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CSprite.o src/CSprite.cpp

${OBJECTDIR}/src/CTileRender.o: src/CTileRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CTileRender.o src/CTileRender.cpp

${OBJECTDIR}/src/CUnitControls.o: src/CUnitControls.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CUnitControls.o src/CUnitControls.cpp

${OBJECTDIR}/src/CUnitRender.o: src/CUnitRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CUnitRender.o src/CUnitRender.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../YmirCore/include -Iinclude -I/usr/include/qt4 `pkg-config --cflags QtCore` `pkg-config --cflags QtGui` `pkg-config --cflags QtXml` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/universe

# Subprojects
.clean-subprojects:
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
