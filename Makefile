prefix=/data/app/timetask

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++

INC=

LIBS=

LIBS_DIR=

OPT=-O2 -fPIC $(INC)

CFLAGS =-Wall $(OPT)
CXXFLAGS =-Wall $(OPT)


SOURCES +=main.c task.c

OBJS += $(patsubst %cpp,%o,$(filter %cpp ,$(SOURCES))) 
OBJS +=$(patsubst %c,%o,$(filter %c ,$(SOURCES)))

TARGET :=all

timetask: $(OBJS)
	$(CC) $(LIBS_DIR)  -o $@ $(OBJS) $(LIBS)

.PHONY: help 	
help:

.PHONY: install 
install:
	rm -rf $(prefix)
	mkdir -p $(prefix)
	cp timetask $(prefix)/
	cp timetask.conf $(prefix)/
	
.PHONY: clean 
clean:
	rm -rf $(OBJS) timetask 
	
%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 
