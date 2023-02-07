#define CROW_STATIC_DIRECTORY "src/static/"
#define CROW_STATIC_ENDPOINT "/<path>"

#include "grid.hpp"
#include "solver.hpp"

#include "crow.h"
#include "crow/middlewares/cors.h"

#include <string>
#include <vector>

int main()
{
    // Enable CORS
    crow::App<crow::CORSHandler> app;

    // Serve index.html
    CROW_ROUTE(app, "/")
    ([](const crow::request &, crow::response &res)
     {
        res.set_static_file_info(CROW_STATIC_DIRECTORY "/index.html");
        res.end(); });

    // Receives an unsolved grid in a string and returns the solved grid in a string
    CROW_ROUTE(app, "/solve/<string>")
    ([](std::string strGrid)
     {
        std::vector<std::vector<Cell>> vGrid = stringToVector(strGrid, '1', '2');
        Grid grid(vGrid);
        Solver solver(grid);
        solver.solve();
        return vectorToString(vGrid, '1', '2', '0'); });

    app.port(18080).run();
}