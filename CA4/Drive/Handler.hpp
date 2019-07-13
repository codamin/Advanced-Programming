
#ifndef HANDLER
#define HANDLER

#include "server/server.hpp"
#include "system/System.hpp"
#include <cstdlib> 
#include <ctime>
#include <iostream>

class Handler {

public:

  static std::string getRandomSessionId(std::string username);
  static std::string get_error_body(std::string error);
  static std::string get_elementList_page_body(std::string sessionId);
  static std::string get_userList_page_body();
  static std::string get_manage_page_body();
  static std::string get_elementInfo_page_body(std::string sessionId, std::string new_path);
  static int upload_number;

  static System* system;

  class RandomNumberHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class LoginHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class LogoutHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class SignupHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class ElementListHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class DirectoryHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class LastDirectoryHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class NewDirectoryHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class RemoveHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class CopyHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class DetailsHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class MoveHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class PasteHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class UploadHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class DownloadHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class UserListHandler : public RequestHandler {
  public:
    Response *callback(Request *);
  };

  class PromoteHandler : public RequestHandler {
  public:
    PromoteHandler() {};
    Response *callback(Request *);
  };

  class DemoteHandler : public RequestHandler {
  public:
    DemoteHandler() {};
    Response *callback(Request *);
  };

private:
  static bool is_copy;
  static std::string copy_source_name;
  static std::string copy_destination_name;
  static std::string file_path;
  static std::string last_directory;
};


#endif
