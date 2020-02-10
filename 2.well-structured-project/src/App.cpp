#include "controller/HelloController.hpp"
#include "AppComponent.hpp"

#include "oatpp/network/server/Server.hpp"


void run() {

  /* Register Components in scope of run() method */
  AppComponent components;
  
  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
  
  /* Create HelloController and add all of its endpoints to router */
  auto myController = std::make_shared<HelloController>();
  myController->addEndpointsToRouter(router);

  
  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::server::ConnectionHandler>, connectionHandler);
  
  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
  
  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  oatpp::network::server::Server server(connectionProvider, connectionHandler);
  
  /* Print info about server port */
  OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());
  
  /* Run server */
  server.run();
}

int main() {

  /* Init oatpp Environment */
  oatpp::base::Environment::init();
  /* Run App */
  run();
  /* Destroy oatpp Environment */
  oatpp::base::Environment::destroy();

  return 0;

}

