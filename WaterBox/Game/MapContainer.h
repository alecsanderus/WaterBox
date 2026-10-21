#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Logger.h"

template <typename T>
struct MapContainer
{
	std::vector <T> Elements;
	std::unordered_map <std::string, int> BindMap;



	T DefaultValue;
	std::string ErrorName;

	inline T& GetElement(const int ID)
	{
#ifndef NDEBUG
		if (ID < Elements.size())
			return Elements[ID];
		else
		{
			LOG_ERROR("Cant find element " + std::to_string(ID) + "\n " + ErrorName);
			return DefaultValue;
		}
			
#else
		return Elements[ID];
#endif
	}

	inline int GetElementID(const std::string& name)
	{
		auto it = BindMap.find(name);

#ifndef NDEBUG
		if (it == BindMap.end())
		{
			LOG_ERROR("Cant find element in map" + name + "\n " + ErrorName);
			return 0;
		}

		if (it->second < Elements.size())
			return it->second;
		else
		{
			LOG_ERROR("Cant find element, but map contains it " + name + "  " + std::to_string(it->second) + "\n " + ErrorName);
			return 0;
		}

#else
		return (it != BindMap.end()) ? it->second : 0;
#endif

	}

	inline T& GetElement(const std::string& name)
	{
		return Elements[GetElementID(name)];
	}	

	std::pair <T&,int> ReserveAndGetElement(const std::string& name)
	{
		auto it = BindMap.find(name);
		if (it != BindMap.end())
		{
			if (it->second < Elements.size())
				return { GetElement(it->second), it->second};
			else
			{
				LOG_WARN("Cant find element, but map contains it " + name + "  " + std::to_string(it->second) + "\n " + ErrorName);
				int ID = Elements.size();
				it->second = ID;
				Elements.push_back(DefaultValue);
				return { Elements.back(), ID };
			}

		}

		int ID = Elements.size();
		auto [NewIt, OK] = BindMap.insert({name, ID});
		if (!OK)
		{
			LOG_ERROR("Cant insert element" + name + "\n " + ErrorName);
			static T val = DefaultValue;
			return { val, 0 };
		}

		Elements.push_back(DefaultValue);
		return {Elements.back(), ID};

	}

	inline int GetElementIdIfHasIt(const std::string& name)
	{
		auto it = BindMap.find(name);
		if (it == BindMap.end())		
			return -1;
		

		if (it->second < Elements.size())
			return it->second;
		else			
			return -1;
		
	}
};