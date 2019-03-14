#include "ResourceManager.h"

namespace Engine
{
	Engine::ResourceManager::ResourceManager()
	{
	}

	Engine::ResourceManager::~ResourceManager()
	{
		for (eImage* image : ImageList)
			delete image;
		
		ImageList.clear();
	}

	bool Engine::ResourceManager::AddImage(eImage * image)
	{
		if (image)
		{
			ImageList.push_back(image);
			return true;
		}
		return false;
	}

	bool Engine::ResourceManager::RemoveImage(std::string imageTag)
	{
		for (auto i = ImageList.begin(); i != ImageList.end(); i++)
		{
			if (imageTag == (*i)->tag)
			{
				ImageList.erase(i);
				return true;
			}
		}
		return false;
	}

	bool Engine::ResourceManager::RemoveImage(eImage* image)
	{
		for (auto i = ImageList.begin(); i != ImageList.end(); i++)
		{
			if (image == *i)
			{
				ImageList.erase(i);
				return true;
			}				
		}
		return false;
	}

	eImage * Engine::ResourceManager::GetImage(std::string imageTag)
	{
		eImage* img = nullptr;
		for(eImage* image : ImageList)
		{
			if (imageTag == image->tag)
			{
				img = image;
				break;
			}
		}
		return img;
	}
}