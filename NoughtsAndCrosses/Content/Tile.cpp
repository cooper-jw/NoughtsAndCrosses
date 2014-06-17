#include "pch.h"
#include "Tile.h"
#include "Common\DirectXHelper.h"
#include <WICTextureLoader.h>

//Allow us to use unqualified names for everything in the NoughtsAndCrosses namespace 
using namespace NoughtsAndCrosses;

//Allow us to use these names unqualified (i.e. without the namespace prefix)
using Microsoft::WRL::ComPtr;
using DirectX::SimpleMath::Color;
using DirectX::SimpleMath::Vector2;
using DirectX::SpriteBatch;
using DirectX::CommonStates;


Tile::Tile(std::shared_ptr<DX::DeviceResources> deviceResources)
  : spriteTexture{nullptr}          //nullptr is a safe initial value
  , spriteTint{1.0f, 1.0f, 1.0f}    //Tint white; i.e. use original colours 
  , spritePosition{100.0f, 100.0f}  //measured in pixels from top left corner of back buffer
  , state{TileState::Empty}         
  , spriteBatch{nullptr}
  , commonStates{nullptr}
{
  //Use DirectX Tool Kit to load an image into our spriteTexture member variable
  //  This completes the construction of a Tile object as all member variables
  //  now have meaningful values (not just safe ones)
  DX::ThrowIfFailed(
    DirectX::CreateWICTextureFromFile(
    deviceResources->GetD3DDevice(),
    deviceResources->GetD3DDeviceContext(),
    L"Assets/BoardTiles.png",
    0,
    &this->spriteTexture
    )
    );

  //Initialize the SpriteBatch and CommonStates objects
  this->spriteBatch
    = std::unique_ptr<SpriteBatch>(new SpriteBatch(deviceResources->GetD3DDeviceContext()));
  this->commonStates
    = std::unique_ptr<CommonStates>(new CommonStates(deviceResources->GetD3DDevice()));
}


Tile::~Tile()
{
}


void Tile::Render()
{
  //Set up the SpriteBatch ready to render our sprites
  this->spriteBatch->Begin(
    DirectX::SpriteSortMode_Deferred,       //Draw later sprites on top of earlier ones
    this->commonStates->NonPremultiplied()  //Using a 'plain' kind of PNG image file
    );
  //Give the SpriteBatch a single sprite
  this->spriteBatch->Draw(
    this->spriteTexture.Get(),  //Need the raw C++ pointer to the sprite texture
    this->spritePosition,
    this->spriteTint
    );
  //Instruct the SpriteBatch to actually render the sprites
  this->spriteBatch->End();
}