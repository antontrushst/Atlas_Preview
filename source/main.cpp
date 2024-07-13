#include <iostream>
#include <string>
#include <filesystem>
#include <SFML\Graphics.hpp>
#include "vec2.h"

std::string    win_title   = "Atlas Preview";
unsigned short win_min_x   = 800,
			   win_min_y   = 800,
			   frame_count = 0,
			   anim_speed  = 10;

sf::Color background_color = {235, 235, 235},
		  text_color       = {  0,   0,   0},
		  borders_color    = {  0,   0,   0};

std::filesystem::path dir_path = "./test_img";
sf::RenderWindow window(sf::VideoMode(win_min_x, win_min_y), win_title);

std::vector<sf::Texture> frames;
std::vector<sf::Sprite>  sprites;

void Set_Borders();
void Get_Frames();
void Set_Sprites();
void Update();
void Render();

int main()
{
	window.setFramerateLimit(anim_speed);
	Update();
	// sf::Texture texture;
	// if (!texture.loadFromFile("test_img/01.png")) { exit(1); }

	// sf::Font font;
	// if (!font.loadFromFile("font/ONESIZE_.TTF")) { exit(1); }
	int pos = 110;
	int frame = 0;
	
	while (window.isOpen())
	{
		window.clear(sf::Color(background_color));

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::U: Update(); break;
					default: continue;
				}
			}
		}

		Set_Borders();

		// float spriteScale = 100.f / texture.getSize().x;
		// sf::Sprite sprite;
		// sprite.setTexture(texture);
		// sprite.setScale(spriteScale, spriteScale);




		int counter = 1;
		for (auto& sprite : sprites)
		{
			sprite.setPosition(pos * counter, 50);
			counter++;
		}

		for (auto& sprite : sprites)
		{
			window.draw(sprite);
		}
		
		for (const auto& sprite : sprites)
		{
			sf::Sprite temp = sprite;
			temp.setScale(sprite.getScale().x * 4, sprite.getScale().y * 4);
			temp.setOrigin(temp.getTextureRect().width/2, temp.getTextureRect().height/2);
			temp.setPosition(window.getSize().x/2, 500);
			window.draw(temp);
		}

		if (frame > 6)
			frame = 0;

		sf::Sprite temp = sprites[frame];
		temp.setScale(sprites[frame].getScale().x * 4, sprites[frame].getScale().y * 4);
		temp.setOrigin(temp.getTextureRect().width/2, temp.getTextureRect().height/2);
		temp.setPosition(window.getSize().x/2, 500);
		window.draw(temp);

		window.draw(temp);
		
		
		// sf::Text text;
		// text.setString("Hello!");
		// text.setFont(font);
		// text.setPosition(400, 400);
		// text.setCharacterSize(14);
		// text.setFillColor(sf::Color(255, 255, 255));

		// window.draw(sprite);
		// window.draw(text);
		window.display();
		frame++;
	}

	return 0;
}

void Set_Borders()
{
	float offset        = 30.f,
		  right_offset  = window.getSize().x - offset,
		  bottom_offset = window.getSize().y - offset,

		  horY_1        = 20.f,
		  horY_2        = 200.f,
		  horY_3        = 250.f;

	sf::Vertex horizontal[4][2];

	horizontal[0][0] = sf::Vertex(sf::Vector2f(offset, horY_1));
	horizontal[0][1] = sf::Vertex(sf::Vector2f(right_offset, horY_1));

	horizontal[1][0] = sf::Vertex(sf::Vector2f(offset, horY_2));
	horizontal[1][1] = sf::Vertex(sf::Vector2f(right_offset, horY_2));

	horizontal[2][0] = sf::Vertex(sf::Vector2f(offset, horY_3));
	horizontal[2][1] = sf::Vertex(sf::Vector2f(right_offset, horY_3));

	horizontal[2][0] = sf::Vertex(sf::Vector2f(offset, bottom_offset));
	horizontal[2][1] = sf::Vertex(sf::Vector2f(right_offset, bottom_offset));

	for (auto& line : horizontal)
	{
		for (auto& vert : line)
		{
			vert.color = borders_color;
		}
	}

	for (auto& line : horizontal)
	{
		window.draw(line, 2, sf::Lines);
	}
}

void Get_Frames()
{
	if (!frames.empty())
		frames.clear();

	for (const auto& file : std::filesystem::directory_iterator(dir_path))
	{
		std::string name = file.path().string();
		std::string extension = name.substr(name.length() - 3, 3);
		if (extension == "png")
		{
			sf::Texture texture;
			if (!texture.loadFromFile(file.path().string())) { exit(1); }
			frames.push_back(texture);
		}
	}

	frame_count = frames.size();
}

void Set_Sprites()
{
	if (!sprites.empty())
		sprites.clear();

	for (const auto& frame : frames)
	{
		sf::Sprite sprite;
		sprite.setTexture(frame);

		unsigned short frame_side;
		if (frame.getSize().x > frame.getSize().y)
			frame_side = frame.getSize().x;
		else
			frame_side = frame.getSize().y;

		float sprite_scale = 100.f / frame_side;
		sprite.setScale(sprite_scale, sprite_scale);

		sprites.push_back(sprite);
	}
}

void Update()
{
	Get_Frames();
	Set_Sprites();
}

void Render()
{

}
