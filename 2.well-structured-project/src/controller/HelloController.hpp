#ifndef HelloController_hpp
#define HelloController_hpp

#include "dto/Message.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

/**
 * Sample Api Controller.
 */
class HelloController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  HelloController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:
  
/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)
  
  ENDPOINT("GET", "/hello", root) {
    OATPP_LOGI("MyApp", "GET /hello");
    
    auto dto = MessageDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World ma' fuckers!!!";
    
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  ENDPOINT("POST", "/hello", createMessage,
           BODY_DTO(MessageDto::ObjectWrapper, dto)){
    OATPP_LOGI("MyApp", "POST /hello - let's say we are saving this into some DB");
    
    dto->message = dto->message + " - processed!";
    dto->statusCode = 100;
    
    return createDtoResponse(Status::CODE_200, dto);
  }
  
/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)
  
};

#endif /* HelloController_hpp */
