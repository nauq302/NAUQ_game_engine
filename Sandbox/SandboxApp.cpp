

#include <nauq.hpp>

class Sandbox :
        public nauq::Application
{
public:
    explicit Sandbox() = default;
    ~Sandbox() override = default;
};


nauq::Application* nauq::createApp()
{
    return new Sandbox;
}