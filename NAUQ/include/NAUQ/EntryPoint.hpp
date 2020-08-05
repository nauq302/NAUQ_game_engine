//
// Created by nauq302 on 05/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_ENTRYPOINT_HPP
#define NAUQ_GAME_ENGINE_ENTRYPOINT_HPP


int main(int argc, const char* argv[])
{
    auto* app = nauq::createApp();

    app->run();

    delete app;
}

#endif //NAUQ_GAME_ENGINE_ENTRYPOINT_HPP
