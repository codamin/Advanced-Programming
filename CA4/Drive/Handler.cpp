#include <iostream>
#include "Handler.hpp"
#include "system/System.hpp"
using namespace std;

Response *Handler::RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *Handler::LoginHandler::callback(Request *req) {

  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  cout << "username: " <<  username << ",\tpassword: " << password << endl;
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string sessionId = getRandomSessionId(username);
  string body;
  try {

  Handler::system->login(username, password, sessionId);

} catch(std::exception& error) {

    string body = get_error_body(error.what());
    res->setBody(body);
    return res;
  }
  res->setSessionId(sessionId);
  if(system->findUser(username)->get_type() == "normal")
    body = get_elementList_page_body(sessionId);
  else
    body = get_manage_page_body();
  res->setBody(body);
  return res;
}


Response *Handler::LogoutHandler::callback(Request *req) {

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  try {

     system->logout(req->getSessionId());

   }catch(std::exception& error) {

       string body = get_error_body(error.what());
       res->setBody(body);
       return res;
    }
  res->setSessionId("0");
  res = Response::redirect("/");
  return res;
}

Response *Handler::DirectoryHandler::callback(Request *req) {

  Response *res = new Response;
  string directory_name = req->getBodyParam("directory_name");
  string current_directory = system->get_element_path(req->getSessionId());
  string new_path = current_directory + "/" + directory_name;
  if(system->find_element(new_path)->get_type()!= "File") {
    system->get_user(req->getSessionId())->set_current_directory(system->find_element(new_path));
    last_directory = current_directory;
    res->setHeader("Content-Type", "text/html");
    res->setBody(get_elementList_page_body(req->getSessionId()));
    return res;
  }
  else {
    try {

    system->download(new_path, "temp.txt");

  } catch(std::exception& error) {

      string body = get_error_body(error.what());
      res->setBody(body);
      return res;
   }
  Response *res = Response::redirect("/show_file");
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementList_page_body(req->getSessionId()));
  return res;
  }
}

Response *Handler::LastDirectoryHandler::callback(Request *req) {

  string current_directory = system->get_element_path(req->getSessionId());
  string parent_path = system->get_parent_path(current_directory);
  Response *res = new Response;
  system->get_user(req->getSessionId())->set_current_directory(system->find_element(parent_path));
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementList_page_body(req->getSessionId()));
  return res;
}

Response *Handler::ElementListHandler::callback(Request *req) {

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementList_page_body(req->getSessionId()));
  return res;
}

Response *Handler::NewDirectoryHandler::callback(Request *req) {

  string directory_name = req->getBodyParam("directory_name");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  try {

    system->add_directory(directory_name, req->getSessionId());

  }catch(std::exception& error) {

      string body = get_error_body(error.what());
      res->setBody(body);
      return res;
   }
   res->setBody(get_elementList_page_body(req->getSessionId()));
   return res;

}

Response *Handler::SignupHandler::callback(Request *req) {

  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  cout << "username: " <<  username << ",\tpassword: " << password << endl;
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  try {

    Handler::system->add_user(username, password, req->getSessionId());

  } catch(std::exception& error) {

    string body = get_error_body(error.what());
    res->setBody(body);
    return res;
  }

  res->setBody(get_manage_page_body());
  return res;
}


Response *Handler::UserListHandler::callback(Request *req) {

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_userList_page_body());
  return res;
}

Response *Handler::PromoteHandler::callback(Request *req) {

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string username = req->getBodyParam("username");
  try {

    system->promote(username);

  } catch(std::exception& error) {

    string body = get_error_body(error.what());
    res->setBody(body);
    return res;
  }

  string body = get_error_body("User promoted successfully");
  res->setBody(body);
  return res;
}

Response *Handler::DemoteHandler::callback(Request *req) {

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string username = req->getBodyParam("username");
  try {

    system->demote(username);

  } catch(std::exception& error) {

    string body = get_error_body(error.what());
    res->setBody(body);
    return res;
  }

  string body = get_error_body(string("User demoted successfully"));
  res->setBody(body);
  return res;
}


Response *Handler::UploadHandler::callback(Request *req) {

  string file = req->getBodyParam("file");
  string current_directory = system->get_element_path(req->getSessionId());
  Response *res = new Response;
  try {

    system->upload("File" + to_string(upload_number), file, current_directory, req->getSessionId());

  } catch(std::exception& error) {

      string body = get_error_body(error.what());
      res->setBody(body);
      return res;
   }
  upload_number ++;
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementList_page_body(req->getSessionId()));
  return res;
}

Response *Handler::DownloadHandler::callback(Request *req) {

   string file = req->getBodyParam("file");
   string current_directory = system->get_element_path(req->getSessionId());
   Response *res = new Response;
   res->setBody(file);
   res->setHeader("Content-Type", "text/plain");
   return res;
}

string Handler::getRandomSessionId(string username)
{
  std::hash<string> hasher;
	return to_string(hasher(username)) + to_string(rand() % 10000);
}

string Handler::get_error_body(string error) {

  string body = "";
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += "<style> body {text-align: center; background-image: url('http://www.gotechnologix.com/wp-content/uploads/2016/05/Solid-color-wallpapers-04-1920x1200.jpg'); } </style>";
  body += "</head>";
  body += "<body";
  body += "<h1>AP DRIVE HTTP </h1>";
  body += "<p>";
  body += error;
  body += "</p>";
  body += "<br>";
  body += " <a href=\"/login\">Go to login page</a>";
  body += "</body>";
  body += "</html>";
  return body;
}

string Handler::get_manage_page_body() {

  string body = "";
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += "<style> body {text-align: center; background-image: url('http://www.gotechnologix.com/wp-content/uploads/2016/05/Solid-color-wallpapers-04-1920x1200.jpg'); } </style>";
  body += "</head>";
  body += "<body>";
  body += "</form>";
  body += "<form action = \"/logout\" method =  \"post\">";
  body += "<button style =\"border-radius: 50px; background-color: red; */border: none; color: white;\" type=\"submit\"> Log out </button>";
  body += "</form>";
  body += "<h1> Manage page </h1>";
  body += "<br>";
  body += " <a href=\"/userList\">Go to UserList page</a>";
  body += "<br>";
  body += "<br>";
  body += "<br>";
  body += " <a href=\"/elementList\">Go to ElementList page</a>";
  body += "</body>";
  body += "</html>";
  return body;
}

string Handler::get_userList_page_body() {

  string body = "";
  body += "<!DOCTYPE html";
  body += "<html>";
  body += "<head>";
  body += "<style> body {text-align: center; background-image: url('http://www.gotechnologix.com/wp-content/uploads/2016/05/Solid-color-wallpapers-04-1920x1200.jpg'); } </style>";
  body += "</head>";
  body += "<body>";
  body += "<form action = \"/logout\" method =  \"post\">";
  body += "<button style =\"border-radius: 50px; background-color: red; */border: none; color: white;\" type=\"submit\"> Log out </button>";
  body += "</form>";
  body += "<h1>UserList Page</h1>";
  body += "<br />";
  body += "<a href = \"/signup\"> add new user </a>";
  vector<User*> users = system->get_users();
  for(int i = 0; i < users.size(); i++) {
    body += "<div class = \"users\">";
    body += "<p>";
    body += users[i]->get_username();;
    body += "</p>";
    body += " <form action = \"/promote\" method =  \"post\">";
    body += "<button style =\"background-color: #4CAF50; /* Green */border: none; color: white;\" type=\"submit\" name = \"username\" value=" + users[i]->get_username() + "> Promote</button>";
    body += "</form>";
    body += "<form action = \"/demote\" method =  \"post\">";
    body += "<button style =\"background-color: #4CAF50; /* Green */border: none; color: white;\" type=\"submit\" name = \"username\" value=" + users[i]->get_username() + "> Demote </button>";
    body += "</form>";
    body += "</div>";
  }
  body += "</body>";
  body += "</html>";
  return body;
}

string Handler::get_elementList_page_body(string sessionId) {

  string body = "";
  body += "<!DOCTYPE html";
  body += "<html>";
  body += "<head>";
  body += "<style> body {text-align: center; background-image: url('http://www.gotechnologix.com/wp-content/uploads/2016/05/Solid-color-wallpapers-04-1920x1200.jpg'); } </style>";
  body += "</head>";
  body += "<body>";
  body += "<form action = \"/logout\" method =  \"post\">";
  body += "<button style =\"border-radius: 50px; background-color: red; */border: none; color: white;\" type=\"submit\"> Log out </button>";
  body += "</form>";
  body += "<h1>Elements List Page</h1>";
  body += "<br />";
  body += "<a href = \"/newDirectory\"> new_directory </a>";
  body += "<br />";
  body += "</form>";

  body += "<form action = \"/lastDirectory\" method =  \"post\">";
  body += "<button style =\" border-radius: 20px; font-size: 15px;transition-duration: 0.4s; background-color: yellow border: none;:hover {background-color: white; color: white;}\" type=\"submit\"> ../ </button>";
  body += "</form>";

  FileSystem* dir = system->get_user(sessionId)->get_current_directory();

  body += "<form action = \"/upload\" method =  \"get\">";
  body += "<button style =\" border-radius: 30px; border: none; background-color: pink; color: white;\" type=\"submit\" name = \"directory_name\" value=" + dir->get_name() + "> Upload</button>";
  body += "</form>";

  body += "<form action = \"/paste\" method =  \"post\">";
  body += "<button style =\" border-radius: 30px; background-color: green; border: none; color: white;\" type=\"submit\" name = \"directory_name\" value=" + dir->get_name() + "> Paste</button>";
  body += "</form>";

  vector<FileSystem*> sub_dirs = dir->get_sub_directories();
  for(int i = 0; i < sub_dirs.size(); i++) {
    body += "</form>";
    body += "<form action = \"/directory\" method =  \"post\">";
    body += "<button style =\"border-radius: 20px; font-size: 30px;transition-duration: 0.4s; background-color: yellow border: none;:hover {background-color: white; color: white;}\" type=\"submit\" name = \"directory_name\" value=" + sub_dirs[i]->get_name() + ">" +
    sub_dirs[i]->get_name() + "</button>";
    body += "</form>";

    body += "<form action = \"/remove\" method =  \"post\">";
    body += "<button style =\"background-color: red; border: none; color: white;\" type=\"submit\" name = \"directory_name\" value=" + sub_dirs[i]->get_name() + "> Remove</button>";
    body += "</form>";

    body += "<form action = \"/details\" method =  \"post\">";
    body += "<button style =\"background-color: blue; border: none; color: white;\" type=\"submit\" name = \"directory_name\" value=" + sub_dirs[i]->get_name() + "> Details </button>";
    body += "</form>";

    body += "<form action = \"/move\" method =  \"post\">";
    body += "<button style =\"background-color: tomato; border: none; color: white;\" type=\"submit\" name = \"directory_name\" value=" + sub_dirs[i]->get_name() +  "> Move</button>";
    body += "</form>";

    body += "<form action = \"/copy\" method =  \"post\">";
    body += "<button style =\"background-color: yellow; border: none; color: white;\" type=\"submit\" name = \"directory_name\" value=" + sub_dirs[i]->get_name() + "> Copy</button>";
    body += "</form>";
  }
  body += "</body>";
  body += "</html>";
  return body;
}

Response *Handler::RemoveHandler::callback(Request *req) {

  Response *res = new Response;
  string directory_name = req->getBodyParam("directory_name");
  string current_directory = system->get_element_path(req->getSessionId());
  string new_path = current_directory + "/" + directory_name;
  try {

    system->remove(new_path);

  } catch(std::exception& error) {

      string body = get_error_body(error.what());
      res->setBody(body);
      return res;
   }
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementList_page_body(req->getSessionId()));
  return res;
}

Response *Handler::MoveHandler::callback(Request *req) {

  Response *res = new Response;
  string directory_name = req->getBodyParam("directory_name");
  string current_directory = system->get_element_path(req->getSessionId());
  string new_path = current_directory + "/" + directory_name;
  copy_source_name = new_path;
  is_copy = false;
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementList_page_body(req->getSessionId()));
  return res;
}

Response *Handler::CopyHandler::callback(Request *req) {

  Response *res = new Response;
  string directory_name = req->getBodyParam("directory_name");
  string current_directory = system->get_element_path(req->getSessionId());
  string new_path = current_directory + "/" + directory_name;
  copy_source_name = new_path;
  is_copy = true;
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementList_page_body(req->getSessionId()));
  return res;
}

Response *Handler::PasteHandler::callback(Request *req) {

  Response *res = new Response;
  string current_directory = system->get_element_path(req->getSessionId());
  copy_destination_name = current_directory;
  try {
    system->copy(copy_source_name, copy_destination_name, req->getSessionId());
  } catch(std::exception& error) {

      string body = get_error_body(error.what());
      res->setBody(body);
      return res;
   }
  if(!is_copy)
    system->remove(copy_source_name);
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementList_page_body(req->getSessionId()));
  return res;
}

string Handler::get_elementInfo_page_body(string sessionId, string new_path) {

  string body = "";
  body += "<!DOCTYPE html";
  body += "<html>";
  body += "<head>";
  body += "<style> body {text-align: center; background-image: url('http://www.gotechnologix.com/wp-content/uploads/2016/05/Solid-color-wallpapers-04-1920x1200.jpg'); } </style>";
  body += "</head>";
  body += "<body>";
  body += "<form action = \"/logout\" method =  \"post\">";
  body += "<button style =\"border-radius: 50px; background-color: red; */border: none; color: white;\" type=\"submit\"> Log out </button>";
  body += "</form>";
  body += "<h1>Element Info</h1>";
  body += "<br />";
  FileSystem* element = system->find_element(new_path);
  body += element->get_info();
  if(element->get_type() == "File") {
    body += "<p>";
    body += "size";
    body += "</nbsp>:</nbsp>";
    body += to_string(element->get_size());
    body += "B";
    body += "</p>";

    body += "<form action = \"/download\" method =  \"post\">";
    body += "<button style =\"background-color: blue; border: none; color: white;\" type=\"submit\" name = \"file_name\" value=" + element->get_name() + "> Download </button>";
    body += "</form>";
  }
  body += "</body>";
  body += "</html>";
  return body;
}

Response *Handler::DetailsHandler::callback(Request *req) {

  Response *res = new Response;
  string element_name = req->getBodyParam("directory_name");
  string current_directory = system->get_element_path(req->getSessionId());
  string new_path = current_directory + "/" + element_name;
  res->setHeader("Content-Type", "text/html");
  res->setBody(get_elementInfo_page_body(req->getSessionId(), new_path));
  return res;
}
