CC = g++
CXXFLAGS = -lpthread

SOLVER_DIR = src/solver
SOLVER_FILES = $(wildcard $(SOLVER_DIR)/*.cpp)
SOLVER_INC = -Isrc/solver
SOLVER_OBJS = $(SOLVER_FILES:.cpp=.o)

MAIN = server
MAIN_FILE = src/server/server.cpp

TESTS = solvertests
TESTS_FILE = tests/solvertests.cpp

main: $(SOLVER_OBJS)
	$(CC) $(SOLVER_INC) $(SOLVER_OBJS) $(MAIN_FILE) $(CXXFLAGS) -o $(MAIN)

tests: $(SOLVER_OBJS)
	$(CC) $(SOLVER_INC) $(SOLVER_OBJS) $(TESTS_FILE) -o $(TESTS)

.c.o:
	$(CC) $(SOLVER_INC) -c $< -o $@

clean:
	$(RM) $(SOLVER_OBJS) $(TESTS)