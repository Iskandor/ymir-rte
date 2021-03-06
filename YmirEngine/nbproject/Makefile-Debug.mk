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
	${OBJECTDIR}/src/CFontRender.o \
	${OBJECTDIR}/src/CGuiElement.o \
	${OBJECTDIR}/src/CGuiElementManager.o \
	${OBJECTDIR}/src/CGuiElementRender.o \
	${OBJECTDIR}/src/CMapRender.o \
	${OBJECTDIR}/src/CMapSegment.o \
	${OBJECTDIR}/src/CObjectPicture.o \
	${OBJECTDIR}/src/CObjectRender.o \
	${OBJECTDIR}/src/COverText.o \
	${OBJECTDIR}/src/CPicture.o \
	${OBJECTDIR}/src/CPictureRender.o \
	${OBJECTDIR}/src/CProjectilePicture.o \
	${OBJECTDIR}/src/CProjectileRender.o \
	${OBJECTDIR}/src/CSprite.o \
	${OBJECTDIR}/src/CTileRender.o \
	${OBJECTDIR}/src/CUnitPicture.o \
	${OBJECTDIR}/src/CUnitRender.o \
	${OBJECTDIR}/src/SortedLinkedList.o


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
LDLIBSOPTIONS=-Wl,-rpath,../YmirCore/bin -L../YmirCore/bin -lYmirCore `pkg-config --libs SDL_gfx` `pkg-config --libs SDL_image` `pkg-config --libs SDL_mixer` `pkg-config --libs SDL_net` `pkg-config --libs SDL_ttf`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/libYmirEngine.${CND_DLIB_EXT}

bin/libYmirEngine.${CND_DLIB_EXT}: ../YmirCore/bin/libYmirCore.so

bin/libYmirEngine.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p bin
	${LINK.cc} -o bin/libYmirEngine.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/CFontRender.o: src/CFontRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CFontRender.o src/CFontRender.cpp

${OBJECTDIR}/src/CGuiElement.o: src/CGuiElement.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CGuiElement.o src/CGuiElement.cpp

${OBJECTDIR}/src/CGuiElementManager.o: src/CGuiElementManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CGuiElementManager.o src/CGuiElementManager.cpp

${OBJECTDIR}/src/CGuiElementRender.o: src/CGuiElementRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CGuiElementRender.o src/CGuiElementRender.cpp

${OBJECTDIR}/src/CMapRender.o: src/CMapRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CMapRender.o src/CMapRender.cpp

${OBJECTDIR}/src/CMapSegment.o: src/CMapSegment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CMapSegment.o src/CMapSegment.cpp

${OBJECTDIR}/src/CObjectPicture.o: src/CObjectPicture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CObjectPicture.o src/CObjectPicture.cpp

${OBJECTDIR}/src/CObjectRender.o: src/CObjectRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CObjectRender.o src/CObjectRender.cpp

${OBJECTDIR}/src/COverText.o: src/COverText.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/COverText.o src/COverText.cpp

${OBJECTDIR}/src/CPicture.o: src/CPicture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CPicture.o src/CPicture.cpp

${OBJECTDIR}/src/CPictureRender.o: src/CPictureRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CPictureRender.o src/CPictureRender.cpp

${OBJECTDIR}/src/CProjectilePicture.o: src/CProjectilePicture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CProjectilePicture.o src/CProjectilePicture.cpp

${OBJECTDIR}/src/CProjectileRender.o: src/CProjectileRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CProjectileRender.o src/CProjectileRender.cpp

${OBJECTDIR}/src/CSprite.o: src/CSprite.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CSprite.o src/CSprite.cpp

${OBJECTDIR}/src/CTileRender.o: src/CTileRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CTileRender.o src/CTileRender.cpp

${OBJECTDIR}/src/CUnitPicture.o: src/CUnitPicture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CUnitPicture.o src/CUnitPicture.cpp

${OBJECTDIR}/src/CUnitRender.o: src/CUnitRender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CUnitRender.o src/CUnitRender.cpp

${OBJECTDIR}/src/SortedLinkedList.o: src/SortedLinkedList.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I../YmirCore/include -I/usr/include/qt4 -I/usr/include/SDL `pkg-config --cflags SDL_gfx` `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_net` `pkg-config --cflags SDL_ttf` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SortedLinkedList.o src/SortedLinkedList.cpp

# Subprojects
.build-subprojects:
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/libYmirEngine.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../YmirCore && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
