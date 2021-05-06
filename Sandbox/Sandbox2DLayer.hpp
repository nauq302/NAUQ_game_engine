//
// Created by nauq302 on 08/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_SANDBOX2DLAYER_HPP
#define NAUQ_GAME_ENGINE_SANDBOX2DLAYER_HPP

#include <nauq.hpp>
#include "ParticleSystem.hpp"

namespace nq = nauq;

class Sandbox2DLayer :
        public nq::Layer
{
private:
    nq::OrthographicCameraController cameraController;

    ParticleSystem particleSystem;
    ParticleProps props;

    // Temp
    nq::Ref<nq::Shader> shader;
    nq::Ref<nq::VertexArray> vertexArray;
    nq::Ref<nq::Texture2D> hv;
    nq::Ref<nq::Texture2D> sheet;
    nq::Ref<nq::SubTexture2D> test;

    glm::vec4 sqColor = { 0.2f, 0.3f, 0.8f, 1.0f };

public:
    explicit Sandbox2DLayer();
    ~Sandbox2DLayer() override = default;

public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(nq::TimeStep ts) override;
    void onImGuiRender() override;
    void onEvent(nq::Event& event) override;
};


#endif //NAUQ_GAME_ENGINE_SANDBOX2DLAYER_HPP
