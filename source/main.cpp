#include <iostream>
#include <SFML\Graphics.hpp>
#include "vec2.h"



int main()
{
	sf::Texture texture;
	if (!texture.loadFromFile("test_img/01.png"))
	{
		std::cerr << "ERROR!\n";
		exit(1);
	}

	sf::Font font;
	if (!font.loadFromFile("font/ONESIZE_.TTF"))
	{
		std::cerr << "ERROR!\n";
		exit(1);
	}

	sf::RenderWindow window(sf::VideoMode(800,800), "Atlas_Preview");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float spriteScale = 100.f / texture.getSize().x;
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setScale(spriteScale, spriteScale);
		// sprite.setPosition(100, 100);


		sf::Text text;
		text.setString("Hello!");
		text.setFont(font);
		text.setPosition(400, 400);
		text.setCharacterSize(14);
		text.setFillColor(sf::Color(255, 255, 255));

		std::cout << spriteScale << "\n";
		std::cout << texture.getSize().x << "\t" << texture.getSize().y << "\n";

		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.draw(text);
		window.display();
	}

	return 0;
}
