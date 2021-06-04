//
// Created by nauq302 on 05/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_ENTRYPOINT_HPP
#define NAUQ_GAME_ENGINE_ENTRYPOINT_HPP

#include "nauq/renderer/Renderer.hpp"

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char* argv[])
{
    nauq::Log::init();

    NQ_PROFILE_BEGIN_SESSION("Startup", "Nauq_Profile_startup.json");
    auto* app = nauq::createApp();
    NQ_PROFILE_END_SESSION();

    NQ_PROFILE_BEGIN_SESSION("Run", "Nauq_Profile_run.json");
    app->run();
    NQ_PROFILE_END_SESSION();

    NQ_PROFILE_BEGIN_SESSION("End", "Nauq_Profile_end.json");
    delete app;
    NQ_PROFILE_END_SESSION();

    NQ_CORE_INFO("Exit successful");
}

#endif //NAUQ_GAME_ENGINE_ENTRYPOINT_HPP
