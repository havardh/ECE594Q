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
CPPUTEST_HOME = /usr/local/Cellar/cpputest/3.4

CPPUTEST_USE_EXTENSIONS = N
CPP_PLATFORM = GCC
CPPFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h -v
CPPUTEST_CPPFLAGS = -x c++ -g
CFLAGS += --std=c99 -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

SRC_DIRS = \
	../src\
	./helpers

TEST_SRC_DIRS = \
	./ \
	./matrix\
	./drawing\
	./shapes/

INCLUDE_DIRS =\
	../inc\
	./helpers\
  $(CPPUTEST_HOME)/include\

include MakefileWorker.mk
