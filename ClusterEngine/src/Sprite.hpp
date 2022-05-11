#pragma once

namespace ClusterEngine
{
    class Sprite {
    private:
        int width, height, nrChannels;
        bool isCleaned = false;
    public:
        unsigned char* data;
        
        Sprite() = delete;
        Sprite(const char* path);
        
        static void SetIsFlipped(bool state);
        
        bool GetIsTransparent() const noexcept;
        int GetNChannels() const noexcept;

        int GetWidth() const noexcept;
        int GetHeight() const noexcept;
                
        void Dispose();
        
        ~Sprite();
    };
}