//
// Created by nauq302 on 12/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_SHADER_HPP
#define NAUQ_GAME_ENGINE_SHADER_HPP

#include "nauq/Core.hpp"

#include <glm/glm.hpp>

#include <string>


namespace nauq {


    class Shader
    {
    public:
        virtual ~Shader() = default;

    public:
        static Ref<Shader> create(const std::string& filepath);
        static Ref<Shader> create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        [[nodiscard]] virtual const std::string& getName() const = 0;

        virtual void set(const std::string& name, int value) = 0;
        virtual void set(const std::string& name, float value) = 0;
        virtual void set(const std::string& name, const glm::vec3& value) = 0;
        virtual void set(const std::string& name, const glm::vec4& value) = 0;
        virtual void set(const std::string& name, const glm::mat4& value) = 0;
    };

    class ShaderLibrary
    {
    private:
        std::unordered_map<std::string, Ref<Shader>> shaders;

    public:
        void add(const Ref<Shader>& shader);
        void add(const std::string& name, const Ref<Shader>& shader);

        Ref<Shader> load(const std::string& filepath);
        Ref<Shader> load(const std::string& name, const std::string& filepath);
        Ref<Shader> get(const std::string& name);
    };
}


#endif //NAUQ_GAME_ENGINE_SHADER_HPP
