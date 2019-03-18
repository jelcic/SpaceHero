#pragma once

#include <vector>
#include "eImage.h"

namespace Engine
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		bool AddImage(eImage* image);
		bool RemoveImage(int imageTag);
		bool RemoveImage(eImage* image);
		eImage* GetImage(int imageTag);

	private:
		std::vector<eImage*> ImageList;
	};
}
