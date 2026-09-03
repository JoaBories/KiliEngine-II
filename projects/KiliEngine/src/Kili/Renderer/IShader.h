#pragma once
#include "Kili/AssetManager/Asset.h"

enum class ShaderType : char
{
    Vertex,
    TessControl,
    TessEval,
    Geometry,
    Fragment,
};

class IShader : public IAsset
{
private:
    std::string mCode;
    ShaderType mShaderType;
    
public:
    explicit IShader(std::string path);
    
    [[nodiscard]] ShaderType getShaderType() const { return mShaderType; }
    [[nodiscard]] std::string getCode() const { return mCode; }

};

inline IShader::IShader(std::string path)
{
    
}
