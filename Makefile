CXX		  := clang++
CXX_FLAGS := -Wall -Wextra -std=c++17 -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= main
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	findArgs = -perm +111 -type f | xargs rm -rfv
else
	findArgs = -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f
endif


all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c*
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean: cleanbin cleandir
	@echo "clean finished"

cleandir:
	find ./ -name "*.dSYM*" | xargs rm -rfv
	find ./ -name "*.out" | xargs rm -rfv
	find ./ -name "*tempCodeRunnerFile" | xargs rm -rfv

cleanbin:
	-rm -rf $(BIN)/*
	find ./${SRC} ${findArgs}

	
