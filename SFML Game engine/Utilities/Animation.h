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
		void updateSprites(float deltaTime);
		void applyToSprite(sf::Sprite &sprite);

	private:
		sf::Clock clock;
		sf::Texture spriteTexture;
		std::vector<sf::IntRect> spriteRects;
		int currentFrame;
		float currentTime;
		
		//Time in seconds a singe sprite will stay on the screen.
		const float SPRITE_LENGTH_TIME;
};