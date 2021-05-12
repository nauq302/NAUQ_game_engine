//
// Created by nauq302 on 08/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_SANDBOX2DLAYER_HPP
#define NAUQ_GAME_ENGINE_SANDBOX2DLAYER_HPP

#include <nauq.hpp>

namespace nauq {
    class Editor2DLayer :
            public Layer
    {
    private:
        OrthographicCameraController cameraController;

        // Temp
        Ref<Shader> shader;
        Ref<VertexArray> vertexArray;
        Ref<Texture2D> hv;
        Ref<Texture2D> sheet;
        Ref<SubTexture2D> test;
        Ref<Framebuffer> framebuffer;

        glm::vec4 sqColor = { 0.2f, 0.3f, 0.8f, 1.0f };
        glm::vec2 viewportSize = { 0, 0 };

        std::unordered_map<char,Ref<SubTexture2D>> textures;

    public:
        explicit Editor2DLayer();
        ~Editor2DLayer() override = default;

    public:
        void onAttach() override;
        void onDetach() override;
        void onUpdate(TimeStep ts) override;
        void onImGuiRender() override;
        void onEvent(Event& event) override;
    };
}



#endif //NAUQ_GAME_ENGINE_SANDBOX2DLAYER_HPP
