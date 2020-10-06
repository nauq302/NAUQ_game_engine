

#include <nauq.hpp>

/**
 *
 */
class ExampleLayer :
        public nauq::Layer
{
public:
    ExampleLayer() : nauq::Layer("Example") {}

    void onUpdate() override
    {
//        NAUQ_INFO("Example Layer: Update");
    }

    void onEvent(nauq::Event& event) override
    {
        if (event.getEventType() == nauq::EventType::KEY_PRESS) {
            auto& e = (nauq::KeyPressEvent&) event;

            if (e.getKeyCode() == NAUQ_KEY_TAB) {
                NAUQ_TRACE("Tab is pressed");
            } else {
                NAUQ_TRACE("{0}", (char) e.getKeyCode());
            }
        }
    }

    void onImGuiRender() override
    {
        ImGui::Begin("Text");
        ImGui::Text("Ahuhu");
        ImGui::End();
    }
};

/**
 *you
 */
class Sandbox :
        public nauq::Application
{
public:
    explicit Sandbox()
    {
        pushLayer(new ExampleLayer);
    }
    ~Sandbox() override = default;
};


nauq::Application* nauq::createApp()
{
    return new Sandbox;
}