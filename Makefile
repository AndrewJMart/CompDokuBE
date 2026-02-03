# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lpthread

# Directories
OBJ_DIR = objs
SRC_DIR = src

# Object files
OBJS = $(OBJ_DIR)/Board.o \
       $(OBJ_DIR)/CandidateTracker.o \
       $(OBJ_DIR)/Validator.o \
       $(OBJ_DIR)/Solver.o \
       $(OBJ_DIR)/Generator.o \
       $(OBJ_DIR)/generate.o \
       $(OBJ_DIR)/playable.o \
       $(OBJ_DIR)/solvers.o \
       $(OBJ_DIR)/utils.o

# Targets
.PHONY: all clean test

all: main

main: $(OBJ_DIR)/main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test: $(OBJ_DIR)/test.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Main
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test
$(OBJ_DIR)/test.o: $(SRC_DIR)/test.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Board
$(OBJ_DIR)/Board.o: $(SRC_DIR)/Board/Board.cpp $(SRC_DIR)/Board/Board.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# CandidateTracker
$(OBJ_DIR)/CandidateTracker.o: $(SRC_DIR)/CandidateTracker/CandidateTracker.cpp \
                                $(SRC_DIR)/CandidateTracker/CandidateTracker.h \
                                $(SRC_DIR)/Board/Board.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Validator
$(OBJ_DIR)/Validator.o: $(SRC_DIR)/Validator/Validator.cpp \
                        $(SRC_DIR)/Validator/Validator.h \
                        $(SRC_DIR)/Board/Board.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Solver
$(OBJ_DIR)/Solver.o: $(SRC_DIR)/Solver/Solver.cpp \
                        $(SRC_DIR)/Solver/Solver.h \
                        $(SRC_DIR)/Board/Board.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Solver Methods - Solvers
$(OBJ_DIR)/solvers.o: $(SRC_DIR)/Solver/solvers.cpp \
                       $(SRC_DIR)/Board/Board.h \
                       $(SRC_DIR)/CandidateTracker/CandidateTracker.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generator
$(OBJ_DIR)/Generator.o: $(SRC_DIR)/Generator/Generator.cpp \
                        $(SRC_DIR)/Generator/Generator.h \
                        $(SRC_DIR)/Board/Board.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generator Methods - Generate
$(OBJ_DIR)/generate.o: $(SRC_DIR)/Generator/generate.cpp \
                       $(SRC_DIR)/Generator/Generator.h \
                       $(SRC_DIR)/Board/Board.h \
                       $(SRC_DIR)/Validator/Validator.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generator Methods - Playable
$(OBJ_DIR)/playable.o: $(SRC_DIR)/Generator/playable.cpp \
                       $(SRC_DIR)/Generator/Generator.h \
                       $(SRC_DIR)/Board/Board.h \
                       $(SRC_DIR)/CandidateTracker/CandidateTracker.h \
                       $(SRC_DIR)/Solver/Solver.h \
                       $(SRC_DIR)/Validator/Validator.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generator Methods - Utils
$(OBJ_DIR)/utils.o: $(SRC_DIR)/Generator/utils.cpp \
                    $(SRC_DIR)/Generator/Generator.h \
                    $(SRC_DIR)/Board/Board.h \
                    $(SRC_DIR)/Validator/Validator.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create Obj Dir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f main test