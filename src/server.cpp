// Copyright 2024 Dogan Torosdagli, Emma Coronado, Milana Tratsevska

#include <iostream>
#include <string>
#include "../include/crow.h"
#include <boost/algorithm/string.hpp>
#include <boost/url/src.hpp>
#include <boost/url/grammar/alnum_chars.hpp>
#include "./csvManager.h"
#include "./json-mgr.h"

int main() {
    std::cout << "Starting rx-warning server!\nLoading CSVs for Adjacency List";
    std::cout.flush();
    AdjList* al = new AdjList();
    processCSVs(al);
    std::cout << "\nLoading CSVs for Adjacency Matrix";
    std::cout.flush();
    AdjMatrix* am = new AdjMatrix();
    processCSVs(am);
    std::cout << "\nServer Started" << std::endl;

    crow::SimpleApp app;
    crow::mustache::set_global_base(SOURCE_DIR + std::string("/templates"));

    // Routes for files and APIs

    // Homepage
    CROW_ROUTE(app, "/").methods("POST"_method, "GET"_method)([](){
        auto page = crow::mustache::load("index.html");
        return page.render();
    });

    CROW_ROUTE(app, "/about")([](){  // homepage
        auto page = crow::mustache::load_text("about.html");
        return page;
    });

    CROW_ROUTE(app, "/css/style.css")([](){  // css file
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

    // improper search alert js
    CROW_ROUTE(app, "/scripts/index.js")([](){
        auto page = crow::mustache::load_text("scripts/index.js");
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
    CROW_ROUTE(app, "/drug").methods("POST"_method)([&al](const crow::request& req, crow::response &res) {
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
        z = convertName(z);
        if (!al->drugExists(z)) {
            res.redirect("/?error");
            res.end();
            return;
        }
        auto w = boost::urls::encode(z, boost::urls::unreserved_chars);
        auto dataStructure = std::string(x.get("SearchRadio"));
        if (dataStructure != "list" || dataStructure == "matrix") {
            res.redirect("/?error");
            res.end();
            return;
        }
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
        crow::mustache::context ctx({{"DSA", txt}});
        return page.render(ctx);
    });

    // JSON template for testing
    CROW_ROUTE(app, "/dev/json")([](){
        auto page = crow::mustache::load_text("sample.json");
        return page;
    });

    CROW_ROUTE(app, "/api")([&al, &am](const crow::request& req){
        auto drugName = req.url_params.get("drugName");
        if (!drugName) {
            auto response = crow::response{"{}"};
            response.set_header("content-type", "application/json");
            return response;
        }
        boost::urls::pct_string_view decoded(drugName);
        auto dn = decoded.decode();
        dn = convertName(dn);
        auto dataStructure = std::string(req.url_params.get("dataStructure"));
        std::string drugJson;
        if (dataStructure == "List")
            drugJson = DrugSerializer(al->getDrugInfo(dn));
        else
            drugJson = DrugSerializer(am->getDrugInfo(dn));
        auto response = crow::response{drugJson};
        return response;
    });

    CROW_ROUTE(app, "/random")([&al](const crow::request& req, crow::response &res) {
        std::string randomDrug = al->randomDrug();
        auto encoded = boost::urls::encode(randomDrug, boost::urls::unreserved_chars);
        res.redirect("/drug/" + encoded);
        res.end();
    });

    app.port(18080).multithreaded().run();
}
