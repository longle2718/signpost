# makefile for user application

# the current directory
APP_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# files needed for this code
C_SRCS   := $(wildcard *.c) 
INCLUDE_PATHS += . ./kiss_fft ./kiss_fft/tools ./log2fix/

CFLAGS += -DFIXED_POINT=16 -std=c99
CFLAGS += -Wno-type-limits -Wno-sign-compare

TOCK_BOARD = audio_module

# include makefile settings that are shared between applications
include ../../AppMakefile.mk

