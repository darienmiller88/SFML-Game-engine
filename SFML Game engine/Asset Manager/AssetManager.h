#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "..//Utilities/NonMovable.h"
#include "..//Utilities/NonCopyable.h"
#include "..//Utilities/Font string names.h"
/**
* Asset managing class to maintain a number of fonts, textures and texts.
*/
class AssetManager : public NonCopyable, NonMovable {
	public:

		/**
		*function to add a sf::Font object into a container.
		*
		*@param fontKey: The key that will determine where in the hashmap the actual sf::font object will go
		*@param fileName: The file path that leads to the font file that will be used to create the Font
		*/
		void addFont(const FontNames::Fonts &fontKey, const std::string &fileName);

		/**
		*\brief function to return a Font object.
		*
		* @param fontKey: The key that will determine where in the hashmap to retrieve the desired sf::Font object.
		*/
		const sf::Font &getFont(const FontNames::Fonts &fontKey);

		/**
		*\brief function to construct and add a sf::Texture object to the hashmap of textures.
		*
		*@param textureKey: The key that will determine where in the hashmap the actual sf::Texture will go
		*@param fileName: The file path that leads to the image that will be used to create the Texture
		*/
		void addTexture(const std::string &textureKey, const std::string &fileName);

		/**
		*\brief function to return a Texture object.
		*
		*@param textureKey: The key that will determine where in the hashmap to retrieve the desired sf::Texture object.
		*/
		const sf::Texture &getTexture(const std::string & textureKey) const;


		void unloadTextures();

		void loadTextures();

		template<class type>
		void tryToReadFile(type& texture, const std::string& fileName);
		
		static AssetManager &get();
	private:
		AssetManager();
		std::unordered_map < FontNames::Fonts, sf::Font > fonts;
		std::unordered_map < std::string, sf::Texture > textures;
};

template<class type>
inline void AssetManager::tryToReadFile(type &texture, const std::string &fileName){
	if (!texture.loadFromFile(fileName)) {
		std::cout << "Cannot read from file!\n";
		exit(1);
	}
}
