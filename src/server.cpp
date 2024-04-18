// Copyright 2024 Dogan Torosdagli, Emma Coronado, Milana Tratsevska

#include <string>
#include "../include/crow.h"
#include <boost/algorithm/string.hpp>
#include <boost/url/src.hpp>
#include <boost/url/grammar/alnum_chars.hpp>
#include "./csvManager.h"
#include "./json-mgr.h"

int main()
{
    AdjList* al = new AdjList();
    processCSVs(al);
    AdjList* am = new AdjMatrix();
    processCSVs(am);


    crow::SimpleApp app;
    crow::mustache::set_global_base(SOURCE_DIR + std::string("/templates"));

    // Routes for files and APIs

    // Homepage
    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load("index.html");
        return page.render();
    });

<<<<<<< HEAD
    CROW_ROUTE(app, "/about")([](){  // homepage
        auto page = crow::mustache::load_text("about.html");
        return page;
    });

    CROW_ROUTE(app, "/css/style.css")([](){  // css file
=======
    // CSS file
    CROW_ROUTE(app, "/css/style.css")([](){
>>>>>>> 9d586d098c175bd65e28c72dbbf31437d191f270
        auto page = crow::mustache::load_text("css/style.css");
        auto response = crow::response{page};
        response.set_header("content-type", "text/css");
        return response;
    });

    // navbar JS
    CROW_ROUTE(app, "/scripts/nav.js")([](){
        auto page = crow::mustache::load_text("scripts/nav.js");
        auto response = crow::response{page};
        response.set_header("content-type", "text/javascript");
        return response;
    });

    // json wrangler JS
    CROW_ROUTE(app, "/scripts/drug.js")([](){
        auto page = crow::mustache::load_text("scripts/drug.js");
        auto response = crow::response{page};
        response.set_header("content-type", "text/javascript");
        return response;
    });

    // Testing for SSL
    CROW_ROUTE(app, "/getservice").methods("POST"_method)([](crow::response &res){
        res.set_static_file_info_unsafe(SOURCE_DIR + std::string("/templates/getservice.dat"));
        res.set_header("content-type", "image/jpeg");
        res.end();
    });

    // Incorrectly Accessed Testing
    CROW_ROUTE(app, "/getservice")([](){
        return "You're Not Supposed To Be Here!";
    });

    // Drug POST redirect to correct page via GET -- keeps URL clean while allowing pages to be bookmarked
    CROW_ROUTE(app, "/drug").methods("POST"_method)([](const crow::request& req, crow::response &res) {
        auto x = req.get_body_params();
        auto y = x.get("DrugName");
        if (!y) {
            res.redirect("/");
            res.end();
            return;  // invalid data from the form results in redirect to homepage
        }
        auto z = std::string(y);
        if (z == "\u0061\u006D\u0061\u006E") {
            res.redirect("/getservice");
            res.end();  // SSL Testing redirect
            return;
        }
        auto w = boost::urls::encode(z, boost::urls::unreserved_chars);
        res.redirect("/drug/" + w);
        res.end();  // redirect to drug data page
    });

    // Drug redirect page accessed with GET, redirect to main
    // This will likely only happen when user attempts to go back through the drug data page
    CROW_ROUTE(app, "/drug").methods("GET"_method)([](const crow::request& req, crow::response &res) {
        res.redirect("/");
        res.end();
    });

    // Drug data page through GET, allows bookmarking and keeps URL clean
    CROW_ROUTE(app, "/drug/<string>").methods("POST"_method, "GET"_method)([](std::string a) {
        boost::urls::pct_string_view decoded(a);
        auto txt = decoded.decode();
        auto page = crow::mustache::load("drug.html");
        crow::mustache::context ctx({{"DrugName", txt}});
        return page.render(ctx);
    });

    // JSON template for testing
    CROW_ROUTE(app, "/dev/json")([](){
        auto page = crow::mustache::load_text("sample.json");
        return page;
    });

    app.port(18080).multithreaded().run();
}
