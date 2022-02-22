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

CFLAGS= -O3 -ansi -g -Wno-unused-result -DARCH=$(shell uname)    

LFLAGS=   -lpthread -lz -lm

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
