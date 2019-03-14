#include "eImage.h"
#include "Director.h"
#include <string>

Engine::eImage::eImage(const char * fileName, std::string _tag, RECT* drawRect) : tag(_tag), DrawRect(drawRect)
{
	IDirect3DDevice9 * device = Director::getInstance()->GetGraphicsManager()->GetDevice();

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(fileName, &info);

	textureSize.Width = info.Width;
	textureSize.Width = info.Height;

	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device, fileName, info.Width, info.Height, D3DX_DEFAULT, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &Texture)))
	{
		std::string errorMessage = "Creating texture for file failed.";
		MessageBox(0, errorMessage.c_str(), 0, 0);
		return;
	}

	if (!SUCCEEDED(D3DXCreateSprite(device, &dx_Sprite)))
	{
		std::string errorMessage = "There was an issue creating the sprite from file";
		MessageBox(0, errorMessage.c_str(), 0, 0);
	}
}

Engine::eImage::~eImage()
{
	if (Texture)
	{
		Texture->Release();
		Texture = nullptr;
	}

	if (dx_Sprite)
	{
		dx_Sprite->Release();
		dx_Sprite = nullptr;
	}

	if (DrawRect)
	{
		delete DrawRect;
		DrawRect = nullptr;
	}
}

void Engine::eImage::Draw(RECT* pSrcRect, const Vec2 &position, const Size &objectSize, const Vec2 &rotationCenter, const Vec2 &anchorPoint, float angle, float scale, unsigned long color)
{
	// Determine which part to draw
	RECT* rectDraw;

	if (pSrcRect)
		rectDraw = pSrcRect;
	else
		rectDraw = DrawRect;

	if (Texture && dx_Sprite)
	{
		int gameHeight = Director::getInstance()->GetGraphicsManager()->GetGameHeight();
		D3DXVECTOR2 translate = D3DXVECTOR2(position.X - anchorPoint.X * (rectDraw->right - rectDraw->left) * scale, gameHeight + (anchorPoint.Y * objectSize.Height * scale - position.Y));
		D3DXVECTOR2 rotCenter(rotationCenter.X, rotationCenter.Y);
		D3DXVECTOR2 scaling((float)scale, (float)scale);

		dx_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMATRIX matrix;
		D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, &rotCenter, angle, &translate);
		dx_Sprite->SetTransform(&matrix);

		dx_Sprite->Draw(Texture, rectDraw, NULL, NULL, color);

		dx_Sprite->End();
	}
}
