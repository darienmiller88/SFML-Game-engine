#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "..//Utilities/NonMovable.h"
#include "..//Utilities/NonCopyable.h"
//#include "..//Utilities/Font string names.h"

enum class Fonts {
	AMATIC_BOLD, AMATIC_SC, ARCADE_I,
	ARCADE_N, ARCADE_R, ARIAL_ITALIC,
	CALIBRI, CALIBRI_B, CALIBRI_I,
	CALIBRI_Z, DROID_SANS, FFF_TUSJ,
	LEADCOAT, ROBOTO_BLACK, ROBOTO_REGULAR,
	SEASRN, SIXTY, STOCKY, TIMES_ROMAN_NUMERAL
};

/**
* Asset managing class to maintain a number of fonts, textures and texts. This class is a singleton, so it CANNOT be
* instantiated. To access its functions you must first call the static function get() like so: AssetManager::get().
* "get()" will return a static instance of the class itself, so you must then use the "." operator on the function call
* to access the functions.
*/
class AssetManager : public NonCopyable, NonMovable {
	public:

		/**
		*function to add a sf::Font object into a container.
		*
		*@param fontKey: The key that will determine where in the hashmap the actual sf::font object will go
		*@param fileName: The file path that leads to the font file that will be used to create the Font
		*/
		void addFont(const std::string &fontKey, const std::string &fileName);

		/**
		*\brief function to return a default font that comes for free. 
		*
		* @param fontKey: The key to retrieve the desired font.
		*/
		const sf::Font &getDefaultFont(const Fonts &fontKey);

		/**
		*\brief function to return a font that the user added
		*
		* @param fontKey: The key that will determine where in the hashmap to retrieve the desired sf::Font object.
		*/
		const sf::Font &getUserAddedFont(const std::string &fontKey);

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
		static AssetManager &get();

		template<class type>
		void tryToReadFile(type& texture, const std::string &fileName);
	private:
		void loadDefaultFonts();
		AssetManager();
	private:
		std::unordered_map < Fonts, std::string > fileNames;
		std::unordered_map < Fonts, sf::Font > defaultFonts;//fonts that come for free
		std::unordered_map < std::string, sf::Font > userAddedFonts;//Fonts that the user can add
		std::unordered_map < std::string, sf::Texture > textures;
};

template<class type>
inline void AssetManager::tryToReadFile(type &texture, const std::string &fileName){
	if (!texture.loadFromFile(fileName)) {
		std::cout << "Cannot read from file: " << fileName << "\n";
		exit(1);
	}
}

