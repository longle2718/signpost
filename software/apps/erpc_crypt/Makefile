# makefile for user application

APP_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

C_SRCS   := $(wildcard *.c)
ERPC_SRCS := $(wildcard *.erpc)

# include makefile settings that are shared between applications
include ../AppMakefile.mk

