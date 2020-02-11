#ifndef ApiTestClient_hpp
#define ApiTestClient_hpp

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "dto/Message.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class ApiTestClient : public oatpp::web::client::ApiClient {

  API_CLIENT_INIT(ApiTestClient)

  API_CALL("GET",  "/hello", getHello)
  API_CALL("POST", "/hello", postHello, BODY_DTO(MessageDto::ObjectWrapper, dto))

  // TODO - add more client API calls here

};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif // ApiTestClient_hpp

