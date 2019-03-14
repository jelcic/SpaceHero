#ifndef _IMAGE_H
#define _IMAGE_H

#include <d3dx9.h>
#include <string>
#include "eTypes.h"

namespace Engine
{
	// Loads one image (D3D texture) and can render it multiple times
	class eImage
	{
	public:
		// Load the texture from the path. Supports all file types recognized by DX9 (.bmp, .dds, .dib, .hdr, .jpg, .pfm, .png, .ppm, .tga).
		eImage(const char* fileName, std::string _tag, RECT* drawRect = nullptr);
		// Unloads the image
		virtual ~eImage();

		// Draws the image centered at pos, with the given size (both X and Y) and color (ARGB format)
		// You can call this many times per frame (presumably with different parameters)
		void Draw(RECT* pSrcRect, const Vec2 & position, const Size &objectSize, const Vec2 & rotationCenter, const Vec2& anchorPoint, float angle, float scale, unsigned long color = 0xffffffff);
		Size textureSize;
		std::string tag;
		RECT* DrawRect;
	protected:
		// The pointer to the D3D 9 texture
		IDirect3DTexture9* Texture;

		// The pointer to the D3D 9 sprite object
		LPD3DXSPRITE dx_Sprite;
	};
}

#endif /* _IMAGE_H */