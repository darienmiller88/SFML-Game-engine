#pragma once
#include <SFML/Graphics.hpp>

class Animation{
	public:

		/**
		*@param textureFileName: The file name for the spritesheet
		*@param spriteTimeLength: Time in seconds a singe sprite will stay on the screen.
		*@param numSprites: vector detailing how many sprites are on the spritesheet horizontally (x), and vertically (y).
		*/
		Animation(const std::string &textureFileName, float spriteTimeLength, const sf::Vector2u &numSprites);

		//Use this constructor if you have each individual image you want to animate.
		Animation(const std::vector<sf::Texture> &textures, float spriteTimeLength);
		void updateSprites(float deltaTime);
		void applyToSprite(sf::Sprite &sprite);
	private:
		sf::Clock clock;
		sf::Texture spriteTexture;
		std::vector<sf::IntRect> spriteRects;
		std::vector<sf::Texture> textures;
		int currentFrame;
		float currentTime;
		bool isUsingSpriteSheet;
		
		//Time in seconds a singe sprite will stay on the screen.
		const float SPRITE_LENGTH_TIME;
};