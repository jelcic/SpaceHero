#include "GraphicsManager.h"
#include <vector>
#include "myMath.h"

namespace Engine
{
	GraphicsManager::GraphicsManager()
	{
		_direct3D = nullptr;
		_device = nullptr;
		clearColor = D3DCOLOR_ARGB(0, 0, 0, 0);
	}

	GraphicsManager::~GraphicsManager()
	{
		if (_font)
		{
			_font->Release();
			_font = nullptr;
		}

		if (_device)
		{
			_device->Release();
			_device = nullptr;
		}

		if (_direct3D)
		{
			_direct3D->Release();
			_direct3D = nullptr;
		}
	}

	void GraphicsManager::Init(HWND Window, bool windowed, int window_width, int window_height)
	{
		//Set main window handle
		_window = Window;
		_window_width = window_width;
		_window_height = window_height;

		//Create DirectX object
		_direct3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (_direct3D == nullptr)
			throw 1;

		D3DPRESENT_PARAMETERS presentationParams;
		ZeroMemory(&presentationParams, sizeof(presentationParams));
		presentationParams.Windowed = windowed;
		presentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentationParams.hDeviceWindow = Window;

		//Create device
		_direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window,
			D3DCREATE_MIXED_VERTEXPROCESSING, &presentationParams, &_device);
		if (_device == nullptr)
			throw 2;

		//surface = GetSurfaceFromFile("GameLogo.jpg");
	}

	void GraphicsManager::BeginRender()
	{
		// Clear the back buffer
		_device->Clear(0, NULL, D3DCLEAR_TARGET, clearColor, 1.0f, 0);
		_device->BeginScene();
	}

	void GraphicsManager::EndRender()
	{
		_device->EndScene();
		_device->Present(NULL, NULL, NULL, NULL);
	}

	IDirect3DSurface9* GraphicsManager::GetSurfaceFromFile(std::string filename)
	{
		IDirect3DSurface9* surface;
		D3DXIMAGE_INFO info;
		D3DXGetImageInfoFromFile(filename.c_str(), &info);

		_device->CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8,
			D3DPOOL_DEFAULT, &surface, NULL);
		D3DXLoadSurfaceFromFile(surface, NULL, NULL, filename.c_str(), NULL, D3DX_DEFAULT, 0, NULL);
		return surface;
	}

	IDirect3DSurface9* GraphicsManager::GetBackBuffer()
	{
		IDirect3DSurface9* backbuffer = nullptr;
		if (_device != nullptr)
			_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
		return backbuffer;
	}

	IDirect3DDevice9* GraphicsManager::GetDevice()
	{
		return _device;
	}

	void GraphicsManager::SurfaceToBackbuffer(IDirect3DSurface9* srcSurface, const RECT* srcRect, const RECT* destRect)
	{
		IDirect3DSurface9* backbuffer = GetBackBuffer();
		if (backbuffer)
			_device->StretchRect(srcSurface, srcRect, backbuffer, destRect, D3DTEXF_NONE);
	}

	void GraphicsManager::DrawRectangle(int x, int y, int width, int height, unsigned long color)
	{		
		D3DRECT rect = { x, GetGameHeight() - (y + height), x + width, GetGameHeight() - y };
		_device->Clear(1, &rect, D3DCLEAR_TARGET, color, 1.0f, 0);
	}

	void GraphicsManager::DrawLine(float x1, float y1, float x2, float y2, float width, bool antialias, unsigned long color)
	{
		LPD3DXLINE line;
		D3DXCreateLine(_device, &line);
		D3DXVECTOR2 lines[] = { D3DXVECTOR2(x1, GetGameHeight() - y1), D3DXVECTOR2(x2, GetGameHeight() - y2) };
		line->SetWidth(width);
		if (antialias) line->SetAntialias(1);
		line->Begin(); 
		line->Draw(lines, 2, color);
		line->End();
		line->Release();
	}

	void GraphicsManager::DrawCircle(float centerX, float centerY, float radius, float resolution, unsigned long color)
	{
		Vec2 firstPoint{ centerX, centerY + radius };
		float x{};
		float y{};

		for (float angle = resolution; angle <= (2.0f * PI); angle += resolution)
		{
			x = centerX + (radius* (float)sin(angle));
			y = centerY + (radius* (float)cos(angle));

			DrawLine(firstPoint.X, firstPoint.Y, x, y, 2, false, color);
			firstPoint = Vec2(x, y);
		}

		DrawLine(firstPoint.X, firstPoint.Y, centerX, centerY + radius, 2, false, color);
	}

	void GraphicsManager::DrawTextMessage(std::string message, RECT rect, short fontSize, int fontWidth, unsigned long color, int orientation)
	{
		if (!_font)
		{
			D3DXCreateFont(_device, fontSize, 0, fontWidth, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
				ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &_font);
		}

		if (orientation == 0)
			_font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_LEFT, color);
		else if (orientation == 1)
			_font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_CENTER, color);
		else if (orientation == 2)
			_font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_RIGHT, color);
	}

	void GraphicsManager::DrawTextMessage(ID3DXFont* font, std::string message, RECT rect, unsigned long color, int orientation)
	{
		if (orientation == 0)
			font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_LEFT, color);
		else if (orientation == 1)
			font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_CENTER, color);
		else if (orientation == 2)
			font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_RIGHT, color);
	}

	void GraphicsManager::PrintStatistics(float elapsedGameTime, int totalGameTime)
	{
		short mSPerFrame = (short)(1000 * elapsedGameTime);
		
		RECT rect;
		SetRect(&rect, 10, 10, 200, 30);
		DrawTextMessage("STATISTICS", rect, 16, 600, D3DCOLOR_XRGB(255, 255, 255));

		SetRect(&rect, 10, 30, 200, 50);
		std::string msgTime = "Total game time: " + std::to_string(totalGameTime);
		DrawTextMessage(msgTime, rect, 16, 600, D3DCOLOR_XRGB(255, 255, 255));

		SetRect(&rect, 10, 50, 300, 70);
		msgTime = "MillisecondsPerFrame: " + std::to_string(mSPerFrame) + " ms/f";
		DrawTextMessage(msgTime, rect, 16, 600, D3DCOLOR_XRGB(255, 255, 255));
	}

	int GraphicsManager::GetGameWidth()
	{
		return _window_width;
	}

	int GraphicsManager::GetGameHeight()
	{
		return _window_height;
	}

	void GraphicsManager::Draw()
	{

	}
}