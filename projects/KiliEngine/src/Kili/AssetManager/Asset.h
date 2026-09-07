#pragma once

namespace Kili
{
    class IAsset
    {
    protected:
        bool mLoaded;
    
    public:
        IAsset() : mLoaded(false) {} // Constructor will just "fetching" the asset in subclasses
        virtual ~IAsset() = default;
    
        virtual bool load() = 0;
        virtual bool unload() = 0;

        [[nodiscard]] bool isLoaded() const { return mLoaded; }
    };
}