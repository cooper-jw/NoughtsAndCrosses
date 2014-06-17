#pragma once

#include <SimpleMath.h>
#include <string>
#include "Common\DeviceResources.h"
#include <SpriteBatch.h>
#include <CommonStates.h>

//Place everything declared in this file in the NoughtsAndCrosses namespace 
namespace NoughtsAndCrosses
{
  enum class TileState
  {
    Empty,
    Cross,
    Nought
  };

  class Tile
  {
  public:
    Tile(std::shared_ptr<DX::DeviceResources> deviceResources);
    ~Tile();

    void Render();

  private:
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> spriteTexture; 
    DirectX::SimpleMath::Color spriteTint;
    DirectX::SimpleMath::Vector2 spritePosition;
    TileState state;

    //DirectX Tool Kit
    std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
    std::unique_ptr<DirectX::CommonStates> commonStates;

  };

}