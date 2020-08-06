#include "AssetManager.h"

#include <iostream>
#include <numeric>
#include <exception>

AssetManager::AssetManager() {
	loadDefaultFonts();
	for (auto &filePairs : fileNames) {
		sf::Font font;
		
		if (!font.loadFromFile("SFML Game Engine\\Asset Manager\\fonts\\" + filePairs.second)) {
			std::cout << "File: SFML Game Engine\\Asset Manager\\fonts\\" + filePairs.second + " does not exist! Please enter a different file name\n";
			return;
		}

		defaultFonts[filePairs.first] = std::move(font);
	}
}

void AssetManager::loadDefaultFonts() {
	fileNames.insert(std::make_pair(Fonts::AMATIC_BOLD, "Amatic-Bold.ttf"));
	fileNames.insert(std::make_pair(Fonts::AMATIC_SC, "AmaticSC-Regular.ttf"));
	fileNames.insert(std::make_pair(Fonts::ARCADE_N, "ARCADE_N.TTF"));
	fileNames.insert(std::make_pair(Fonts::ARCADE_I, "ARCADE_I.TTF"));
	fileNames.insert(std::make_pair(Fonts::ARCADE_N, "ARCADE_N.TTF"));
	fileNames.insert(std::make_pair(Fonts::ARCADE_R, "ARCADE_R.TTF"));
	fileNames.insert(std::make_pair(Fonts::ARIAL_ITALIC, "arialItalic.ttf"));
	fileNames.insert(std::make_pair(Fonts::CALIBRI, "Calibri.ttf"));
	fileNames.insert(std::make_pair(Fonts::CALIBRI_B, "CALIBRIB.TTF"));
	fileNames.insert(std::make_pair(Fonts::CALIBRI_I, "CALIBRII.TTF"));
	fileNames.insert(std::make_pair(Fonts::CALIBRI_Z, "CALIBRIZ.TTF"));
	fileNames.insert(std::make_pair(Fonts::DROID_SANS, "DroidSans.ttf"));
	fileNames.insert(std::make_pair(Fonts::FFF_TUSJ, "FFF_Tusj.ttf"));
	fileNames.insert(std::make_pair(Fonts::LEADCOAT, "leadcoat.ttf"));
	fileNames.insert(std::make_pair(Fonts::ROBOTO_BLACK, "Roboto-Black.ttf"));
	fileNames.insert(std::make_pair(Fonts::ROBOTO_REGULAR, "Roboto-Regular.ttf"));
	fileNames.insert(std::make_pair(Fonts::SEASRN, "SEASRN__.ttf"));
	fileNames.insert(std::make_pair(Fonts::SIXTY, "SIXTY.TTF"));
	fileNames.insert(std::make_pair(Fonts::STOCKY, "stocky.ttf"));
	fileNames.insert(std::make_pair(Fonts::TIMES_ROMAN_NUMERAL, "times-new-roman.ttf"));
}

void AssetManager::addFont(const std::string &fontKey, const std::string &fileName){
	sf::Font font;

	if (!font.loadFromFile(fileName)) {
		std::cout << "File: " + fileName + " does not exist! Please enter a different file name\n";
		return;
	}

	userAddedFonts[fontKey] = std::move(font);
}

const sf::Font &AssetManager::getDefaultFont(const Fonts &fontKey){
	return defaultFonts.at(fontKey);
}

const sf::Font &AssetManager::getUserAddedFont(const std::string &fontKey){
	if (userAddedFonts.find(fontKey) == userAddedFonts.end()) {
		std::cout << "Font with key: " << fontKey << " was not found\n";
		return sf::Font();
	}

	return userAddedFonts.at(fontKey);
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
	if (textures.find(textureKey) == textures.end()) {
		std::cout << "texture for key: " << textureKey << " not found\n";
		return sf::Texture();
	}

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
