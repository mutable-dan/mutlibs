CPP=g++

LIB_INSTALL_DIR = /usr/local/lib/
INCLUDE_INSTALL = /usr/local/include/mutlib

INCLUDE_DIR = -I. 
LINK_LIBS := -lpthread -lboost_system -lboost_filesystem 

LIB = libmut.so
SOURCE = logger.cpp config.cpp util.cpp
HEADER = logger.h config.h util.h
OBJS = $(SOURCE:.cpp=.o) 
DEPS = $(SOURCE:.cpp=.d) 

-include $(DEPS)

DEBUG   = -g3 -DDEBUG
RELEASE = -O2 -DNDEBUG 
RELEASESYMBOLS = -O2 -DNDEBUG -g2

FLAGS   = -march=native -mtune=native -fno-default-inline -fno-stack-protector -pthread -Wall -pedantic -Wextra -Weffc++ -Waddress -Warray-bounds -Wno-builtin-macro-redefined -Wundef
FLAGS  += -std=c++17

FLAGSDEBUG    = $(FLAGS)
FLAGSDEBUG   += $(DEBUG)
FLAGSRELEASE  = $(FLAGS)
FLAGSRELEASE += $(RELEASE)
FLAGSREL_SYM  = $(FLAGS)
FLAGSREL_SYM += $(RELEASESYMBOLS)


.PHONY: release
release: CFLAGS = $(FLAGSRELEASE) -c -fPIC
release: all
#release: install

.PHONY: debug
debug: CFLAGS = $(FLAGSDEBUG) -c -fPIC
debug: all
#debug: install

.PHONY: release_symbols 
relsym: CFLAGS = $(RELEASESYMBOLS) -c -fPIC
relsym: all

all : $(OBJS)
	$(CC) -shared -o $(LIB) $(OBJS) $(LINK_LIBS)
	
%.o: %.cpp
	$(CPP) $(CFLAGS) -MMD -MP -c $< -o $@

#%.d: %.cpp
#	$(CC) $(CFLAGS) -MM -MT $< -o $@
# -MF  write the generated dependency rule to a file
# -MG  assume missing headers will be generated and don't stop with an error
# -MM  generate dependency rule for prerequisite, skipping system headers
# -MP  add phony target for each header to prevent errors when header is missing
# -MT  add a target to the generated dependency
	

clean :
	rm -f *.o *.so *.d

install : all
	install -d $(INCLUDE_INSTALL)
	install -m 644 $(LIB) $(LIB_INSTALL_DIR)
	install -m 644 $(HEADER) $(INCLUDE_INSTALL)

uninstall :
	rm -f $(LIB_INSTALL_DIR)/$(LIB)
	rm -f $(INCLUDE_INSTALL)/*.h
	rmdir $(INCLUDE_INSTALL)

