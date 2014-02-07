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
#CPPUTEST_HOME = $(BASE_TEST_DIR)/cpputest
CPPUTEST_HOME = $(BASE_TEST_DIR)/.cpputest

CPPUTEST_USE_EXTENSIONS = Y
GMOCK_HOME = $(BASE_TEST_DIR)/.gmock
CPP_PLATFORM = GCC
CPPUTEST_USE_REAL_GMOCK = Y
CPPUTEST_USE_REAL_GTEST = Y
CPPFLAGS += -g -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h -v -std=c++11
CPPUTEST_CPPFLAGS = -x c++ -g -DCPPUTEST -std=c++11
CFLAGS += -g -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

TEST_SRC_DIRS += $(BASE_TEST_DIR)

INCLUDE_DIRS += $(BASE_TEST_DIR)/.cpputest/include/
INCLUDE_DIRS += $(BASE_TEST_DIR)/.gmock/include/
INCLUDE_DIRS += $(BASE_TEST_DIR)/.gmock/gtest/include/


include $(BASE_TEST_DIR)/MakefileWorker.mk
