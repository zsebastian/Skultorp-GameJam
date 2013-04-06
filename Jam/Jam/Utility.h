#ifndef UTILITY_H
#define UTILITY_H

#include <algorithm>
#include <SFML\System\Vector2.hpp>
#include <sstream>
#include <cmath>

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

	template <typename T, typename stringT>
	T fromString(const stringT& str)
	{
		std::istringstream ss(str);
		T ret;

		return (ss >> ret) ? ret : throw "fromString: invalid string";
	};

	template <typename T>
	std::string toString(const T& value)
	{
		std::ostringstream ss("");
		
		return (ss << value) ? ss.str() : throw "toString: invalid value";
	};

	template <typename T>
	bool testCircleCollision(sf::Vector2<T> p0, T r0, sf::Vector2<T> p1, T r1) 
	{
		//return (x2-x1)^2 + (y1-y2)^2 <= (r1+r2)^2
		T dx2 = (p1.x - p0.x) * (p1.x - p0.x);
		T dy2 = (p1.y - p0.y) * (p1.y - p0.y);
		T rr2 = (r0 + r1) * (r0 + r1);
		
		return (dx2 + dy2 <= rr2);
	}

	template <typename T>
	sf::Vector2<T> getNormal(sf::Vector2<T> vectorIn)
	{
		sf::Vector2<T> vectorOut;

		vectorOut.x = vectorIn.y;
		vectorOut.y = -vectorIn.x;

		return vectorOut;
	}

	template <typename T>
	float angleBetween(sf::Vector2<T> v1, sf::Vector2<T> v2)
	{
		T dottProduct;
		sf::Vector2<T> dottVec;

		dottVec.x = v1.x * v2.x;
		dottVec.y = v1.y * v2.y;
		dottProduct = dottVec.x + dottVec.y;

		T lengthProduct = length(v1) * length(v2);

		T result = dottProduct / lengthProduct;
		
		float f = std::acos(result);
		
		f = f * 180 / 3.14f;

		return f;
	}
};


#endif
