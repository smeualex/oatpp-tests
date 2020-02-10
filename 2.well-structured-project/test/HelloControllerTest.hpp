#ifndef HelloControllerTest_hpp
#define HelloControllerTest_hpp

#include "oatpp-test/UnitTest.hpp"

class HelloControllerTest : public oatpp::test::UnitTest {
public:
                                /* Test TAG for logs */
  HelloControllerTest() : UnitTest("TEST[HelloControllerTest]"){}
  void onRun() override;

};

#endif // HelloControllerTest_hpp
