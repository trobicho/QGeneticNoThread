SOURCES+=main.cpp
SOURCES+=QTank.cpp
SOURCES+=WinGL.cpp
SOURCES+=../genetic/PoolFunc/Tank.cpp
SOURCES+=../genetic/PoolFunc/TankPeople.cpp

HEADERS+=QTank.h
HEADERS+=WinGL.h
HEADERS+=../genetic/PoolFunc/Tank.h
HEADERS+=../genetic/PoolFunc/TankPeople.h

LIBS+= -lglut -lGLU
LIBS+= -L ~/lib -lgenetic -lneuralNet
QT+=opengl
CONFIG+=qt
CONFIG+=no_lflags_merge
CONFIG+=debug
