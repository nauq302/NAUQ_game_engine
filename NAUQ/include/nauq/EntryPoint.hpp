//
// Created by nauq302 on 05/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_ENTRYPOINT_HPP
#define NAUQ_GAME_ENGINE_ENTRYPOINT_HPP

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char* argv[])
{
    nauq::Log::init();
    NAUQ_CORE_INFO("Initialized Log!");
    NAUQ_INFO("Initialized Log!");

    auto* app = nauq::createApp();

    app->run();

    delete app;
}

#endif //NAUQ_GAME_ENGINE_ENTRYPOINT_HPP
