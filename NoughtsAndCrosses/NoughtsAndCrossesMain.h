#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\BackgroundRenderer.h"
#include "Content\Tile.h"

// Renders Direct2D and 3D content on the screen.
namespace NoughtsAndCrosses
{
	class NoughtsAndCrossesMain : public DX::IDeviceNotify
	{
	public:
		NoughtsAndCrossesMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~NoughtsAndCrossesMain();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
    BackgroundRenderer m_background;
    Tile m_tile;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}