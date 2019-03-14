#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

namespace Engine
{
	// DirectX wrapper class
	class GraphicsManager
	{
	public:
		GraphicsManager();
		~GraphicsManager();

		void Init(HWND Window, bool windowed, int window_width, int window_height);

		// called before any rendering
		void BeginRender();

		// called after rendering
		void EndRender();

		// loads a bitmap into a Direct3D surface
		IDirect3DSurface9* GetSurfaceFromFile(std::string filename);

		// returns a pointer to the back buffer
		IDirect3DSurface9* GetBackBuffer();

		// return the current Direct3D device
		IDirect3DDevice9* GetDevice();

		// Copy an offscreen surface to the back buffer
		void SurfaceToBackbuffer(IDirect3DSurface9* srcSurface,
			const RECT *srcRect,
			const RECT *destRect);

		// Clear rectangle on the back buffer
		void DrawRectangle(int x, int y, int width, int height, unsigned long color);

		// Draw line between two points in 2D space
		void GraphicsManager::DrawLine(float x1, float y1, float x2, float y2, float width, bool antialias, unsigned long color = 0xFFFFFFFF);

		// Draw circle
		void DrawCircle(float centerX, float centerY, float radius, float resolution, unsigned long color);

		// Draw text message to the back buffer
		void DrawTextMessage(std::string message, RECT fRect, short fontSize, int fontWidth, unsigned long color, int orientation = 0);
		void DrawTextMessage(ID3DXFont* font, std::string message, RECT rect, unsigned long color, int orientation = 0);

		// Print time statistics
		void PrintStatistics(float elapsedGameTime, int totalGameTime);

		// Get Window Client area 
		int GetGameWidth();

		// Get Window Client area 
		int GetGameHeight();

		D3DCOLOR clearColor;

		void Draw();
	private:
		HWND _window;
		LPDIRECT3D9 _direct3D;
		IDirect3DDevice9* _device;
		ID3DXFont* _font;
		// screen details
		int _window_width;
		int _window_height;
	};
}

