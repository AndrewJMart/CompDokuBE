#include <iostream>
#include <crow.h>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

int main(){

    std::cout << "Initializing Backend";

    std::cout << "Reading Backend Config";

    crow::SimpleApp CompDokuBE;

    // Default Endpoint
    CROW_ROUTE(CompDokuBE, "/")([](){
        return "Hello world";
    });

    CROW_ROUTE(CompDokuBE, "/random_board")([](){
        crow::json::wvalue x({{"message", "Hello, World!"}});
        x["Message2"] = "hello again";

        return x;
    });



    // Single Thread App
    CompDokuBE.port(18080).run();
}
