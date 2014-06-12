#pragma once

#include <SimpleMath.h>

namespace NoughtsAndCrosses
{
  class BackgroundRenderer
  {
  public:
    BackgroundRenderer();
    ~BackgroundRenderer();

    DirectX::SimpleMath::Color GetClearColour();

  private:
    DirectX::SimpleMath::Color clearColour;
  };

}