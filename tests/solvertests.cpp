#include "grid.hpp"
#include "solver.hpp"

#include <iostream>
#include <string>
#include <vector>

#define ASSERT_EQUAL(x, y)                                \
    {                                                     \
        if (x != y)                                       \
            std::cout << "Failed on " << #x << std::endl; \
    }

std::string testSolver(const std::string &strGrid, char chPrimary, char chSecondary, char chEmpty)
{
    std::vector<std::vector<Cell>> vGrid = stringToVector(strGrid, chPrimary, chSecondary);
    Grid grid(vGrid);
    Solver solver(grid);
    solver.solve();
    return vectorToString(vGrid, chPrimary, chSecondary, chEmpty);
}

int main()
{
    std::string test1("---b"
                      "-r--"
                      "b---"
                      "-b-b");

    std::string soln1("rrbb"
                      "brbr"
                      "bbrr"
                      "rbrb");

    std::string test2("-----r"
                      "--bb--"
                      "------"
                      "b-b--b"
                      "--rr--"
                      "-----b");

    std::string soln2("brbrbr"
                      "rrbbrb"
                      "rbrbbr"
                      "brbrrb"
                      "bbrrbr"
                      "rbrbrb");

    std::string test3("-r---br-"
                      "--bbrbb-"
                      "--------"
                      "-r------"
                      "--r--bbr"
                      "rb---rb-"
                      "---r----"
                      "-brb--bb");

    std::string soln3("brbbrbrr"
                      "rrbbrbbr"
                      "bbrrbrrb"
                      "brbrbrrb"
                      "rbrbrbbr"
                      "rbrrbrbb"
                      "brbrbbrr"
                      "rbrbrrbb");

    std::string test4("r-----r-r-"
                      "r---r-rb-b"
                      "--r--b----"
                      "------b---"
                      "r-r-r-----"
                      "---b--r---"
                      "--r-----r-"
                      "----r-----"
                      "-rr---r-b-"
                      "r--b----b-");

    std::string soln4("rbbrbrrbrb"
                      "rbbrrbrbrb"
                      "brrbrbbrbr"
                      "brbrbrbrbr"
                      "rbrbrbrbrb"
                      "brbbrbrrbr"
                      "rbrrbrbbrb"
                      "brbrrbbrrb"
                      "brrbbrrbbr"
                      "rbrbbrbrbr");

    std::string test5("-r---rr---r-"
                      "-----r-----b"
                      "rr-b----br--"
                      "--b-r--r--r-"
                      "r--------b--"
                      "-----b-b---r"
                      "b----b--b---"
                      "--rr-------r"
                      "--r--r-rr-r-"
                      "b-----b----b"
                      "-r------b---"
                      "--r--r--b---");

    std::string soln5("brbrbrrbrbrb"
                      "bbrrbrrbrbrb"
                      "rrbbrbbrbrbr"
                      "brbbrbrrbrrb"
                      "rbrrbrbbrbbr"
                      "rbrbrbrbrbbr"
                      "brbrrbbrbrrb"
                      "bbrrbrrbbrbr"
                      "rbrbbrbrrbrb"
                      "brbrrbbrrbrb"
                      "rrbbrbrbbrbr"
                      "rbrbbrbrbrbr");

    ASSERT_EQUAL(testSolver(test1, 'r', 'b', '-'), soln1);
    ASSERT_EQUAL(testSolver(test2, 'r', 'b', '-'), soln2);
    ASSERT_EQUAL(testSolver(test3, 'r', 'b', '-'), soln3);
    ASSERT_EQUAL(testSolver(test4, 'r', 'b', '-'), soln4);
    ASSERT_EQUAL(testSolver(test5, 'r', 'b', '-'), soln5);
    return 0;
}