

#include <nauq.hpp>

/**
 *
 */
class ExampleLayer : public nauq::Layer
{
public:
    ExampleLayer() : nauq::Layer("Example") {}

    void onUpdate() override
    {
//        NAUQ_INFO("Example Layer: Update");
    }

    void onEvent(nauq::Event& event) override
    {
        NAUQ_TRACE("{0}", event.toString());
    }
};

/**
 *
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