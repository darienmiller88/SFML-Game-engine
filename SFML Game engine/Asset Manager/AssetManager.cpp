#include "AssetManager.h"

#include <iostream>
#include <exception>

AssetManager::AssetManager() {
	for (auto &filePairs : FontNames::fileNames) {
		sf::Font font;

		if (!font.loadFromFile("SFML Game Engine\\Asset Manager\\fonts\\" + filePairs.second)) {
			std::cout << "File: SFML Game Engine\\Asset Manager\\fonts\\" + filePairs.second + " does not exist! Please enter a different file name\n";
			return;
		}

		fonts[filePairs.first] = std::move(font);
	}

}

void AssetManager::addFont(const FontNames::Fonts &fontKey, const std::string &fileName){
	sf::Font font;

	if (!font.loadFromFile(fileName)) {
		std::cout << "File: " + fileName + " does not exist! Please enter a different file name\n";
		return;
	}

	fonts[fontKey] = std::move(font);
}

void AssetManager::addTexture(const std::string &textureKey, const std::string &fileName){
	sf::Texture texture;

	if (!texture.loadFromFile(fileName)) {
		std::cout << "File: " + fileName + " does not exist! Please enter a different file name\n";
		return;
	}

	textures[textureKey] = std::move(texture);
}

const sf::Texture &AssetManager::getTexture(const std::string &textureKey) const{
	return textures.at(textureKey);
}

void AssetManager::unloadTextures()
{
}

void AssetManager::loadTextures()
{
}

AssetManager &AssetManager::get(){
	static AssetManager a;
	return a;
}

const sf::Font &AssetManager::getFont(const FontNames::Fonts &fontKey)  {
	if (!fonts.contains(fontKey)) {
		fonts[fontKey] = sf::Font();
	}

	return fonts.at(fontKey);
}
