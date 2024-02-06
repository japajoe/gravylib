#include "Noise.hpp"

namespace Gravy::System::Numerics
{
    std::unique_ptr<FastNoiseLite> Noise::noise = nullptr;

    void Noise::Initialize()
    {
        if(noise)
            return;
        noise = std::make_unique<FastNoiseLite>();
        noise->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);            
        noise->SetFrequency(0.03f);
        noise->SetFractalType(FastNoiseLite::FractalType_Ridged);
    }

    void Noise::SetType(FastNoiseLite::NoiseType type)
    {
        Initialize();
        noise->SetNoiseType(type);
    }

    void Noise::SetFractalType(FastNoiseLite::FractalType type)
    {
        Initialize();
        noise->SetFractalType(type);
    }

    void Noise::SetFrequency(float frequency)
    {
        Initialize();
        noise->SetFrequency(frequency);
    }

    float Noise::GetSample(float x, float y)
    {
        Initialize();
        return noise->GetNoise(x, y);
    }

    float Noise::GetSample(float x, float y, float z)
    {
        Initialize();
        return noise->GetNoise(x, y, z);
    }
};