#include <catch2/catch.hpp>
#include "glm_matchers.cpp"
#include "../events/event_handler.hpp"
#include "../events/events.hpp"


class TestClass {

public:
    bool is_called_void = false;

    glm::vec3 test_vec = glm::vec3(.0f, .0f, .0f);

    TestClass() {
        EventHandler::registerSubscriber<EventType::TEST>(this, &TestClass::onTestVoid);
        EventHandler::registerSubscriber<glm::vec3, EventType::TEST>(this, &TestClass::onTestValue);
    }
    
    void onTestVoid() {
        this->is_called_void = true;
    }

    void onTestValue(glm::vec3 value) {
        this->test_vec = value;
    }

    void unsubscribe() {
        EventHandler::unsubscribe<EventType::TEST>(this, &TestClass::onTestVoid);
        this->is_called_void = false;
    }

    void unsubscribeValue() {
        EventHandler::unsubscribe<glm::vec3, EventType::TEST>(this, &TestClass::onTestValue);
        this->test_vec = glm::vec3(0.f, 0.f, 0.f);
    }

};

TEST_CASE("Event handler emit/receive event works", "[event_handler]") {
    using namespace glm;
    TestClass test_class;
    
    SECTION("Void event gets received") {
        EventHandler::emitEvent(Event<void>(EventType::TEST));
        EventHandler::pollEvents();

        REQUIRE(test_class.is_called_void);
    }

    SECTION("Void unsubscribe works") {
        test_class.unsubscribe();
        EventHandler::emitEvent(Event<void>(EventType::TEST));
        EventHandler::pollEvents();
        REQUIRE(!test_class.is_called_void);
    }

    SECTION("Valued event gets received") {
        vec3 test_vec(1.f, 1.f, 1.f);
        EventHandler::emitEvent(Event<glm::vec3>(EventType::TEST, test_vec));
        EventHandler::pollEvents();
        REQUIRE_THAT(test_class.test_vec, IsGlmVecEqual<glm::vec3>(test_vec));
    }

    SECTION("Valued event unsubscribe works") {
        test_class.unsubscribeValue();
        vec3 test_vec(1.f, 1.f, 1.f);
        EventHandler::emitEvent(Event<glm::vec3>(EventType::TEST, test_vec));
        EventHandler::pollEvents();

        REQUIRE_THAT(test_class.test_vec, IsGlmVecEqual<glm::vec3>(vec3(.0f, .0f, .0f)));
        
    }
}
