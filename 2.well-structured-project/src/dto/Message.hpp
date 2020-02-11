#ifndef Message_hpp
#define Message_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Message Data-Transfer-Object
 */
class MessageDto : public oatpp::data::mapping::type::Object {

  DTO_INIT(MessageDto, Object /* Extends */)

  DTO_FIELD(Int32, statusCode);   // Status code field
  DTO_FIELD(String, message);     // Message field

public:
  static MessageDto::ObjectWrapper create(Int32 statusCode, const String& message){
    auto dto = MessageDto::createShared();

    dto->statusCode = statusCode;
    dto->message    = message;

    return dto;
  }
};

/* TODO - Add more DTOs here */

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

#endif /* Message_hpp */
