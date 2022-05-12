#pragma once
#include <glad/glad.h>
#include <iostream>
#include "GraphicsConventions.h"


namespace ClusterEngine
{
    class Sprite {
    public:
        unsigned char* data;
        
        Sprite();
        Sprite(const char* path);

        void SetPath(const char* path);

        static void SetIsFlipped(bool state);
        
        bool GetIsTransparent() const noexcept;
        int GetNChannels() const noexcept;

        int GetWidth() const noexcept;
        int GetHeight() const noexcept;

        void CreateTexture();
        TEXTURE* GetTexture();

        void Dispose();
        bool IsPathInitialized() const noexcept;

        ~Sprite();
    private:
        int width, height, nrChannels;
        bool isCleaned = false;
        bool isTextureCreated = false;
        bool isImageTaken = false;
        const char* path;
        std::shared_ptr<TEXTURE> tex;

        void LoadImage();
    };
}