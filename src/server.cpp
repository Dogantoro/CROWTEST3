#include "../include/crow.h"
#include <boost/algorithm/string.hpp>
#include <boost/url/src.hpp>
#include <boost/url/grammar/alnum_chars.hpp>
#include <string>
#include "csvManager.h"
#include "json-mgr.h"

int main()
{
    AdjList* al = new AdjList();
    processCSVs(al);
    AdjList* am = new AdjMatrix();
    processCSVs(am);


    crow::SimpleApp app;
    crow::mustache::set_global_base(SOURCE_DIR + std::string("/templates"));

    // load files at specified directories
    CROW_ROUTE(app, "/")([](){  // homepage
        auto page = crow::mustache::load_text("index.html");
        return page;
    });

    CROW_ROUTE(app, "/css/style.css")([](){  // css file
        auto page = crow::mustache::load_text("css/style.css");
        return page;
    });

    CROW_ROUTE(app, "/scripts/nav.js")([](){  // navbar script
        auto page = crow::mustache::load_text("scripts/nav.js");
        return page;
    });

    CROW_ROUTE(app, "/scripts/drug.js")([](){  // json wrangler script
        auto page = crow::mustache::load_text("scripts/drug.js");
        return page;
    });
    
    CROW_ROUTE(app, "/getservice").methods("POST"_method)([](crow::response &res){
        res.set_static_file_info_unsafe(SOURCE_DIR + std::string("/templates/getservice.dat"));
        res.set_header("content-type", "image/jpeg");
        res.end();
    });

    CROW_ROUTE(app, "/getservice")([](){
        return "You're Not Supposed To Be Here!";
    });

    CROW_ROUTE(app, "/drug").methods("POST"_method)([](const crow::request& req, crow::response &res) {
        auto x = req.get_body_params();
        auto y = x.get("DrugName");
        if (!y) {
            res.redirect("/");
            res.end();
            return;
        }
        auto z = std::string(y);
        if (z == "\u0061\u006D\u0061\u006E") {
            res.redirect("/getservice");
            res.end();
        }
        auto w = boost::urls::encode(z, boost::urls::unreserved_chars);
        res.redirect("/drug/" + w);
        res.end();
    });

    CROW_ROUTE(app, "/drug").methods("GET"_method)([](const crow::request& req, crow::response &res) {
        res.redirect("/");
        res.end();
    });

    CROW_ROUTE(app, "/drug/<string>").methods("POST"_method, "GET"_method)([](std::string a) {  // drug page
        boost::urls::pct_string_view decoded(a);
        auto txt = decoded.decode();
        auto page = crow::mustache::load("drug.html");
        crow::mustache::context ctx ({{"DrugName", txt}});
        return page.render(ctx);
    });

    CROW_ROUTE(app, "/dev/json")([](){  // json template
        auto page = crow::mustache::load_text("sample.json");
        return page;
    });

    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}