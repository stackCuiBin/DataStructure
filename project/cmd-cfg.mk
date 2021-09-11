
AR := ar
ARFLAGS := crs

CC := g++
LFLAGS := 
CFLAGS := -Wall -I$(DIR_COMMON_INC) -I$(DIR_INC) -I$(DIR_LIBS_INC)

DEBUG := true

ifeq ($(DEBUG),true)
CFLAGS += -g
endif

MKDIR := mkdir
RM := rm -rf
CP := cp


