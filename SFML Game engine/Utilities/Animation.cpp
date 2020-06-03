#include "Animation.h"
#include <iostream>

Animation::Animation(const std::string &textureFileName, float spriteTimeLength, const sf::Vector2u &numSprites) : 
SPRITE_LENGTH_TIME(spriteTimeLength), currentFrame(0){

	if (!spriteTexture.loadFromFile(textureFileName)) {
		std::cout << "File: " << textureFileName << " cannot be opened. Exiting program\n";
		exit(1);
	}

	spriteTexture.setSmooth(true);
	sf::Vector2u spriteSize;

	//On the sprite sheet image that was read into "spriteTexture", it is a numSprites.x by numSprites.y sheet, so to get the
	//length and width of each sprite, I have to divide the length and width of the sprite sheet by the number of sprites
	//on each dimension.
	spriteSize.x = spriteTexture.getSize().x / numSprites.x;
	spriteSize.y = spriteTexture.getSize().y / numSprites.y;

	for (int y = 0; y < numSprites.y; y++){
		for (int x = 0; x < numSprites.x; x++){
			spriteRects.push_back(sf::IntRect(spriteSize.x * x, spriteSize.y * y, spriteSize.x, spriteSize.y));
		}
	}

	std::cout << spriteRects.size() << "\n";
}

void Animation::updateSprites(float deltaTime){
	currentTime = clock.getElapsedTime().asSeconds();

	if (currentTime >= SPRITE_LENGTH_TIME) {
		currentTime -= SPRITE_LENGTH_TIME;
		clock.restart();
		if (++currentFrame >= spriteRects.size())
			currentFrame = 0;
	}
}

void Animation::applyToSprite(sf::Sprite &sprite){
	sprite.setTexture(spriteTexture);
	sprite.setTextureRect(spriteRects[currentFrame]);
}
