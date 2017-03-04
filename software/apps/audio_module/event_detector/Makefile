# makefile for user application

# the current directory
APP_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

LIB_DIR := $(HOME)/gcwa/c

# files needed for this code
C_SRCS   := $(wildcard *.c) $(LIB_DIR)/ridgeTracker.c $(LIB_DIR)/dynArray.c
INCLUDE_PATHS += . $(LIB_DIR) $(LIB_DIR)/kiss_fft $(LIB_DIR)/kiss_fft/tools

CFLAGS += -DFIXED_POINT=16 -std=c99

TOCK_BOARD = audio_module

# include makefile settings that are shared between applications
include ../../AppMakefile.mk

