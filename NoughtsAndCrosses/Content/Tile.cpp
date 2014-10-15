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
  , spriteSourceRectangle{nullptr}
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

  //Initialize the sprite source rectangle to draw the leftmost image
  this->spriteSourceRectangle = std::unique_ptr<RECT>(new RECT);  //A RECT object with 0 width, 0 height and it's top left corner at (0,0)
  this->spriteSourceRectangle->left = 0;  //x coordinate of the top left corner
  this->spriteSourceRectangle->top = 0;   //y coordinate of the top left corner
  this->spriteSourceRectangle->right = 64; //x coordinate of the bottom right corner
  this->spriteSourceRectangle->bottom= 64; //y coordinate of the bottom right corner
}


Tile::~Tile()
{
}

void Tile::SetState(TileState newState) {
	this->state = newState;
}


void Tile::Render() {
  //Set up the SpriteBatch ready to render our sprites
  this->spriteBatch->Begin(
    DirectX::SpriteSortMode_Deferred,       //Draw later sprites on top of earlier ones
    this->commonStates->NonPremultiplied()  //Using a 'plain' kind of PNG image file
    );

  if (this->state == TileState::Empty) {
	  //Initialize the sprite source rectangle to draw the leftmost image
	  this->spriteSourceRectangle = std::unique_ptr<RECT>(new RECT);  //A RECT object with 0 width, 0 height and it's top left corner at (0,0)
	  this->spriteSourceRectangle->left = 0;  //x coordinate of the top left corner
	  this->spriteSourceRectangle->top = 0;   //y coordinate of the top left corner
	  this->spriteSourceRectangle->right = 64; //x coordinate of the bottom right corner
	  this->spriteSourceRectangle->bottom = 64; //y coordinate of the bottom right corner
  }
  else if (this->state == TileState::Nought) {
	  //Initialize the sprite source rectangle to draw the middle image
	  this->spriteSourceRectangle = std::unique_ptr<RECT>(new RECT);  //A RECT object with 0 width, 0 height and it's top left corner at (0,0)
	  this->spriteSourceRectangle->left = 64;  //x coordinate of the top left corner
	  this->spriteSourceRectangle->top = 0;   //y coordinate of the top left corner
	  this->spriteSourceRectangle->right = 128; //x coordinate of the bottom right corner
	  this->spriteSourceRectangle->bottom = 64; //y coordinate of the bottom right corner
  }
  else if (this->state == TileState::Cross) {
	  //Initialize the sprite source rectangle to draw the rightmost image
	  this->spriteSourceRectangle = std::unique_ptr<RECT>(new RECT);  //A RECT object with 0 width, 0 height and it's top left corner at (0,0)
	  this->spriteSourceRectangle->left = 128;  //x coordinate of the top left corner
	  this->spriteSourceRectangle->top = 0;   //y coordinate of the top left corner
	  this->spriteSourceRectangle->right = 192; //x coordinate of the bottom right corner
	  this->spriteSourceRectangle->bottom = 64; //y coordinate of the bottom right corner
  }

  //Give the SpriteBatch a single sprite
  this->spriteBatch->Draw(
    this->spriteTexture.Get(),  //Need the raw C++ pointer to the sprite texture
    this->spritePosition,
    this->spriteSourceRectangle.get(),  //Need the raw C++ pointer
    this->spriteTint,
    0,  //Angle of rotation in radians
    Vector2(0,0), //Origin for the rotation
    1.0f, //Scale factor
    DirectX::SpriteEffects_None, //Reflections about the horizontal and verticle axes
    0.0f  //Layer depth; not required as we use DirectX::SpriteSortMode_Deferred
    );
  //Instruct the SpriteBatch to actually render the sprites
  this->spriteBatch->End();
}