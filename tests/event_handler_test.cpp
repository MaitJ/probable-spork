#include <catch2/catch.hpp>
#include "glm_matchers.cpp"
#include "../events/event_handler.hpp"
#include "../events/events.hpp"


class TestClass {

public:
    bool is_called_void = false;

    glm::vec3 test_vec = glm::vec3(.0f, .0f, .0f);
    
    void onTestVoid() {
        this->is_called_void = true;
    }

    void onTestValue(glm::vec3 value) {
        this->test_vec = value;
    }
};

TEST_CASE("Event handler emit/receive event works", "[event_handler]") {
    TestClass test_class;

    EventHandler::registerSubscriber<EventType::TEST>(std::bind(&TestClass::onTestVoid, test_class));
    
    SECTION("Void event gets received") {
        EventHandler::emitEvent(Event<void>(EventType::TEST));
        EventHandler::pollEvents();

        REQUIRE(test_class.is_called_void);
    }
}
