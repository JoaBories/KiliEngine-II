#pragma once

class IAsset
{
private:
    bool mLoaded;
    
public:
    IAsset(); // Constructor is just "fetching" the asset 
    virtual ~IAsset();
    
    virtual bool use() = 0; // Useful for assets like shader textures and vao
    
    virtual bool load() = 0;
    virtual bool unLoad() = 0;

    [[nodiscard]] bool isLoaded() const { return mLoaded; }
};