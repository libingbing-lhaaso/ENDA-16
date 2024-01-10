 name := arr_time
 G4TARGET := $(name)
 G4EXLIB := true

 #COAST_DIR=/net/minus/home/shchegolev/CORSIKA/corsika-75600
 
# CPPFLAGS  += -I$(COAST_DIR)/include
# EXTRALIBS += -L$(COAST_DIR)/lib -L$(COAST_DIR)/lib/unknown
# EXTRALIBS += -lCorsikaFileIO
# EXTRALIBS += -lCorsikaIntern

 .PHONY: all

 all: lib bin

 include $(G4INSTALL)/config/binmake.gmk

 all: ${name}

 ${name}: arr_time.o


