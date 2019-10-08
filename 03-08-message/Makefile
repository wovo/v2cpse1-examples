#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := message.cpp

# header files in this project
HEADERS := message.hpp

# other places to look for files for this project
SEARCH  := 

message.cpp: Makefile make_message.exe   
	./make_message.exe splash "Hello brave new world!" > message.cpp
   
make_message.exe: make_message.cpp
	g++ make_message.cpp -o make_message.exe

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
