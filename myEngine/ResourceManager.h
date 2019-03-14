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
		bool RemoveImage(std::string imageTag);
		bool RemoveImage(eImage* image);
		eImage* GetImage(std::string imageTag);

	private:
		std::vector<eImage*> ImageList;
	};
}
