#include "crow/crow.h"

//Adding bson and mongo libs
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <boost/filesystem.hpp>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/oid.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::basic::kvp;
using mongocxx::cursor;

using namespace std;
using namespace crow;

/* 
main app file to do evrything inside public folder
*/

void sendFile(response &res, string filename, string contentType){
  ifstream in("../public/" + filename, ifstream::in);
  if(in){
    ostringstream contents;
    contents << in.rdbuf();
    in.close();
    res.set_header("Content-Type", contentType);
    res.write(contents.str());
  } else {
    res.code = 404;
    res.write("Not found");
  }
  res.end();
}

void sendHtml(response &res, string filename){
  sendFile(res, filename + ".html", "text/html");
}

void sendImage(response &res, string filename){
  sendFile(res, "images/" + filename, "image/jpeg");
}

void sendScript(response &res, string filename){
  sendFile(res, "scripts/" + filename, "text/javascript");
}

void sendStyle(response &res, string filename){
  sendFile(res, "styles/" + filename, "text/css");
}

int main(int argc, char* argv[]) {
  crow::SimpleApp app;

  // Mongo DB connection
  mongocxx::instance instance{};
  // string mongoConnect = std::string(getenv("MONGODB_URI"));
  // mongocxx::client conn{mongocxx::uri{"mongodb://localhost:27017"}};
  mongocxx::client client(mongocxx::uri{"mongodb://localhost:27017"});
  // auto collection = conn["test"]["contacts"];
  mongocxx::database db = client["test"];
  mongocxx::collection collection = db["contacts"];

  // Simple write to any base route: uncomment and build it.
  // CROW_ROUTE(app, "/")
  //   ([](){
  //     return "<div><h1>Hello, Crow.</h1></div>";
  //   });

  // Simple index.html serving example. without various functions. Uncomment and build it.
  // CROW_ROUTE(app, "/")
  // ([](const request &req, response &res){
  //   ifstream in("../public/index0.html", ifstream::in);
  //   if(in){
  //     ostringstream contents;
  //     contents << in.rdbuf();
  //     in.close();
  //     res.write(contents.str());
  //   } else {
  //     res.write("Not Found");
  //   }
  //   res.end();
  // });

  CROW_ROUTE(app, "/styles/<string>")
    ([](const request &req, response &res, string filename){
      sendStyle(res, filename);
    });

  CROW_ROUTE(app, "/scripts/<string>")
    ([](const request &req, response &res, string filename){
      sendScript(res, filename);
    });

  CROW_ROUTE(app, "/images/<string>")
    ([](const request &req, response &res, string filename){
      sendImage(res, filename);
    });

  CROW_ROUTE(app, "/about")
    ([](const request &req, response &res){
      sendHtml(res, "about");
    });

  // Contacts page access from mongo test db   
  CROW_ROUTE(app, "/contacts")
    ([&collection](){
      mongocxx::options::find opts;
      opts.skip(9);
      opts.limit(10);
      auto docs = collection.find({}, opts);
      std::ostringstream os;
      for(auto &&doc : docs){
        os << bsoncxx::to_json(doc) << "\n";
      }
      return crow::response(os.str());
    });

  CROW_ROUTE(app, "/")
    ([](const request &req, response &res){
      sendHtml(res, "index");
    });

  char* port = getenv("PORT");
  uint16_t iPort = static_cast<uint16_t>(port != NULL? stoi(port): 18080);
  cout << "PORT = " << iPort << "\n";
  app.port(iPort).multithreaded().run();

  return(0);
}
