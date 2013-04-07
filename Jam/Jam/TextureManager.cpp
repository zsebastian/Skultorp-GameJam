#include "TextureManager.h"

TextureManager* TextureManager::mInstance = 0;

void TextureManager::loadTexture(const std::string& filename)
{
	getInstance()->mTextures[filename].loadFromFile(filename);
	getInstance()->mTextures[filename].setSmooth(true);
}

sf::Texture& TextureManager::getTexture(const std::string& filename)
{
	return getInstance()->mTextures[filename];
}

TextureManager* TextureManager::getInstance()
{
	if(!mInstance)
		mInstance = new TextureManager;

	return mInstance;
}