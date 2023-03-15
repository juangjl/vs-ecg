#------------------------------------------------------------------------------#
# File : Makefile 
# Author: jl_juang@vsigntek.com
# Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
#------------------------------------------------------------------------------#
TARGET   = $(shell basename $(CURDIR))

CPP=g++
CC=g++
LL=g++

SRC=./src
OUT=./out

OS_NAME := $(shell uname -s)
#-----------------------------#
# OS TYPE
# WINDOWS : 0
# LINUXS  : 1
# MAC-OS  : 2
#-----------------------------
OS_TYPE_WINDOWS=0
OS_TYPE_UBUNTU=1
OS_TYPE_MAC_OS=2

OS_TYPE=OS_TYPE_WINDOWS
CFLAGS_OS=

ifeq ($(OS_NAME), Linux)	
	CFLAG_BLUETOOTH=$(shell pkg-config --cflags gio-2.0) 
	LFLAG_BLUETOOTH=$(shell pkg-config --libs gio-2.0) -lbluetooth	
	CFLAGS_OS= -Wno-format-overflow  -Wno-conversion-null -Wno-pointer-arith $(CFLAG_BLUETOOTH) -I./inc/lib -I./ 
	LFLAGS_OS= $(LFLAG_BLUETOOTH)
	OS_TYPE=OS_TYPE_UBUNTU	
endif

ifeq ($(OS_NAME), Darwin)
	OS_TYPE=OS_TYPE_MAC_OS
endif

CFLAGS= -O3 -ansi -g -Wno-unused-result -DARCH=$(shell uname)    -DOS_TYPE=$(OS_TYPE) $(CFLAGS_OS)
CFLAG_GTK= $(shell pkg-config --cflags  gtk+-3.0)

#LFLAGS= -lpthread -lz -lm
LFLAGS=   -lpthread -lz -lm $(LFLAGS_OS)
LDLIB_GTK= $(shell pkg-config --libs gtk+-3.0) -w

ifeq ($(OS_NAME), Darwin)
        LFLAGS+=  ./res/app.res
endif

INC=  -I./inc 

C_SRC    := $(wildcard $(SRC)/*.c)
C_OBJS   := $(C_SRC:%.c=%.o)

CPP_SRC  := $(wildcard $(SRC)/*.cpp)
CPP_OBJS := $(CPP_SRC:%.cpp=%.o)

OBJECTS  += $(CPP_OBJS) $(C_OBJS)


$(BINDIR)/$(TARGET): $(CPP_OBJS) $(C_OBJS)
	@$(LL) $(OBJECTS)  $(LFLAGS) $(LDLIB_GTK)  -o ${TARGET}.o
	@mv *.o $(OUT)
	@echo "Linking complete!"

$(CPP_OBJS): $(OBJ)%.o :%.cpp
	@$(CPP) $(CFLAGS) $(CFLAG_GTK) -c $< -o $@ ${INC}
	@echo "[CC] "$<

$(C_OBJS): $(OBJ)%.o : %.c
	@$(CC)  $(CFLAGS) $(CFLAG_GTK) -c $<  -o $@ ${INC} -Wno-deprecated
	@echo "[CC] "$<	

all:$(BINDIR)/$(TARGET)


clean:
	@rm -rf *.o *.out $(SRC)/*.o $(SRC)/*.out
	@rm -rf ${OUT}/*.o  *.o

objs:
	@echo $(OBJECTS)

cpp_objs:
	@echo $(CPP_OBJS)

test1:
	@echo $(C_SRC)
