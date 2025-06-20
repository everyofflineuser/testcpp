#include<sstream>
#include<fstream>
#include<iostream>

#include "ResourceManager.h"

ResourceManager::ResourceManager(const std::string &executablePath) {
    std::size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string &relativeFilePath) const {
    std::ifstream f;
    f.open(m_path+"/"+relativeFilePath, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string &shaderName, const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    std::string vertexString = getFileString(vertexShaderPath);
    if (vertexString.empty()) {
        std::cerr << "No vertex shader for " << shaderName << std::endl;
        return nullptr;
    }

    std::string fragmentString = getFileString(fragmentShaderPath);
    if (fragmentString.empty()) {
        std::cerr << "No fragment shader for " << shaderName << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
    if (newShader->isCompiled()) {
        return newShader;
    }

    std::cerr << "Failed to load shader for " << shaderName
    << "\nVertex: " << vertexShaderPath
    << "\nFragment: " << fragmentShaderPath << std::endl;

    return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName) {
    ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
    if (it == m_shaderPrograms.end()) {
        return it->second;
    }
    std::cerr << "Shader " << shaderName << " not found!" << std::endl;
    return nullptr;
}