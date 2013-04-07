#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class TextureManager
{
public:
	static void loadTexture(const std::string& filename);
	static sf::Texture& getTexture(const std::string& filename);

	static TextureManager* getInstance();
private:
	static TextureManager* mInstance;
	std::map<std::string, sf::Texture> mTextures;
};

#endif