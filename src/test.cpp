#include "../include/crow.h"

int main()
{
    crow::SimpleApp app; //define your crow application

    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load_text("index.html");
        return page;
    });

    CROW_ROUTE(app, "/drug").methods("POST"_method)([](const crow::request& req) {
        auto x = req.get_body_params().get("DrugName");
        if (!x) return crow::response{"Ruh Roh!"};
        return crow::response{x};
    });

    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}