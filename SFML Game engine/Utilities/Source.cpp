#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow window({ 600, 600 }, "circles", Style::Close | Style::Titlebar);
	RectangleShape verticalSlider({ 40, 100 });

	//States for button/events
	bool mouseClicked = false;
	bool mouseInsideRect = false;
	bool dragging = false;

	sf::Vector2f mouseRectOffset;

	//Variables
	int mouseX = 0;
	int mouseY = 0;


	verticalSlider.setPosition({window.getSize().x - verticalSlider.getSize().x, 0.f});
	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
			if (e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left){
				std::cout << "mouse clicked\n";
				if (verticalSlider.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
					dragging = true;
					mouseRectOffset.x = e.mouseButton.x - verticalSlider.getGlobalBounds().left - verticalSlider.getOrigin().x;
					mouseRectOffset.y = e.mouseButton.y - verticalSlider.getGlobalBounds().top - verticalSlider.getOrigin().y;
				}
			}
			
			if (e.type == sf::Event::MouseButtonReleased and e.mouseButton.button == sf::Mouse::Left){
				dragging = false;
			}

			//Mouse Moved in window
			if (e.type == sf::Event::MouseMoved)
			{
				mouseX = e.mouseMove.x;
				mouseY = e.mouseMove.y;
			}

			
		}
		if (dragging == true){
			verticalSlider.setPosition(verticalSlider.getPosition().x, mouseY - mouseRectOffset.y);
		}
			
		window.clear();
		window.draw(verticalSlider);
		window.display();
	}
}