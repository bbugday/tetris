#pragma once

#include <map>
#include <string>
#include <cassert>
#include <memory>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename)
	{
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
		insertResource(id, std::move(resource));
	}

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, Parameter& secondParam)
	{
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename, secondParam))
			throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
		insertResource(id, std::move(resource));
	}

	Resource& get(Identifier id)
	{
		auto found = mTextureMap.find(id);
		assert(found != mTextureMap.end());
		return *found->second;
	}

	const Resource& get(Identifier id) const
	{
		auto found = mTextureMap.find(id);
		assert(found != mTextureMap.end());
		return *found->second;
	}

private:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource)
	{
		auto inserted = mTextureMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}

private:
	std::map<Identifier, std::unique_ptr<Resource>> mTextureMap;
};
