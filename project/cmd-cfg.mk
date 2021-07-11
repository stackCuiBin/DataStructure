
AR := ar
ARFLAGS := crs

CC := g++
LFLAGS := 
CFLAGS := -I$(DIR_COMMON_INC) -I$(DIR_INC) -I$(DIR_LIBS_INC)

ifeq ($(DEBUG),true)
CFLAGS += -g
endif

MKDIR := mkdir
RM := rm -rf
CP := cp


