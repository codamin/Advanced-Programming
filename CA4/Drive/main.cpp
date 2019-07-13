#include <cstdlib>
#include <ctime>
#include <iostream>
#include "my_server.hpp"
#include "system/System.hpp"
#include "Handler.hpp"

using namespace std;

System* Handler::system;
bool Handler::is_copy;
string Handler::copy_source_name;
string Handler::copy_destination_name;
string Handler::file_path;
string Handler::last_directory;
int Handler::upload_number = 1;

int main(int argc, char** argv) {

  srand(time(NULL));
  try {
    System *_system = new System;

    Handler::system = _system;
    if(argc == 1)
        throw runtime_error("Not enough inputs");
    _system->set_download_directory(argv[1]);
    MyServer server(argc > 2 ? atoi(argv[2]) : 5000);

    server.setNotFoundErrPage("./static/404.html");

    server.get("/login", new ShowPage("./static/login.html"));
    server.get("/newDirectory", new ShowPage("./static/new_directory.html"));
    server.get("/signup", new ShowPage("./static/signup.html"));
    server.get("/userList", new Handler::UserListHandler());
    server.get("/elementList", new Handler::ElementListHandler());
    server.get("/upload", new ShowPage("static/upload.html"));
    server.get("/rand", new Handler::RandomNumberHandler());
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/datacent.jpg", new ShowImage("static/datacent.jpg"));
    server.get("/logincss", new ShowPage("./static/login.css"));
    server.get("/signupcss", new ShowPage("./static/signup.css"));
    server.get("/newDirectorycss", new ShowPage("./static/new_directory.css"));
    server.get("/", new ShowPage("./static/login.html"));

    server.post("/promote", new Handler::PromoteHandler());
    server.post("/demote", new Handler::DemoteHandler());
    server.post("/directory", new Handler::DirectoryHandler());
    server.post("/lastDirectory", new Handler::LastDirectoryHandler());
    server.post("/details", new Handler::DetailsHandler());
    server.post("/remove", new Handler::RemoveHandler());
    server.post("/copy", new Handler::CopyHandler());
    server.post("/move", new Handler::MoveHandler());
    server.post("/paste", new Handler::PasteHandler());
    server.post("/download", new Handler::DownloadHandler());
    server.post("/login", new Handler::LoginHandler());
    server.post("/logout", new Handler::LogoutHandler());
    server.post("/newDirectory", new Handler::NewDirectoryHandler());
    server.post("/signup", new Handler::SignupHandler());
    server.post("/upload", new Handler::UploadHandler());

    string filePath = _system->get_downlaod_directory () + "/temp.txt";
    server.get("/show_file", new ShowFile(filePath, getExtension(filePath)));
    server.run();
  }
  catch(exception& error) {
      cerr << error.what() << endl;
  }
  catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
