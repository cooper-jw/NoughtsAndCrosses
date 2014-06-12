#include "pch.h"
#include "BackgroundRenderer.h"

using namespace NoughtsAndCrosses;

using DirectX::SimpleMath::Color;

BackgroundRenderer::BackgroundRenderer()
  : clearColour{ 0.960784376f, 0.960784376f, 0.862745166f } //Beige
{
}


BackgroundRenderer::~BackgroundRenderer()
{
}

Color BackgroundRenderer::GetClearColour()
{
  return this->clearColour;
}
