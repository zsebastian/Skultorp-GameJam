#ifndef UTILITY_H
#define UTILITY_H

#include <algorithm>
#include <SFML\System\Vector2.hpp>
#include <sstream>


namespace Util
{
	template <class T, typename predT>
	inline void eraseIf(T cont, predT pred)
	{
		cont.erase(
			std::remove_if(cont.begin(), cont.end(), pred),
			cont.end());
	};

	template <typename T>
	T distance(sf::Vector2<T> v0, sf::Vector2<T> v1)
	{
		float dx = v0.x - v1.x;
		float dy = v0.y - v1.y;
		return std::abs(std::sqrt((dx*dx) + (dy*dy)));
	};

	template <typename T>
	sf::Vector2<T> normalize(sf::Vector2<T> v)
	{
		return (v * (1 / length(v)));
	};

	template <typename T>
	T length(sf::Vector2<T> v)
	{
		return std::abs(std::sqrt((v.x*v.x) + (v.y*v.y)));
	};

	template <typename T>
	T fromString(const std::string& str)
	{
		std::istringstream ss(str);
		T ret;

		return (ss >> ret) ? ret : throw "invalid string";
	};

	template <typename T>
	std::string toString(const T& value)
	{
		std::ostringstream ss("");
		
		return (ss << value) ? ss.str() : throw "invalid string";
	};
};


#endif
