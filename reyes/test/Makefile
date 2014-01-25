#---------
#
# CppUTest Examples Makefile
#
#----------

#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

#--- Inputs ----#
COMPONENT_NAME = all
CPPUTEST_HOME = ../cpputest

CPPUTEST_USE_EXTENSIONS = N
CPP_PLATFORM = GCC
CPPFLAGS += -g -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h -v
CPPUTEST_CPPFLAGS = -x c++ -g -DCPPUTEST
CFLAGS += -g --std=c99 -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

SRC_DIRS = \
	../src\
	./helpers

TEST_SRC_DIRS = \
	./ \
	./**

INCLUDE_DIRS =\
	./helpers\
	../inc\
  $(CPPUTEST_HOME)/include\

include MakefileWorker.mk
