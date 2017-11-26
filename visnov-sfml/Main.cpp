#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Dialogue.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Visual Novel Framework", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("fonts/Stellar-Regular.otf")) 
		std::cout << "error loading font." << std::endl;

	sf::Texture bgTexture1;
	if (!bgTexture1.loadFromFile("bg/par_1a.bmp"))
		std::cout << "error loading texture." << std::endl;
	sf::Sprite bgSprite1 = sf::Sprite(bgTexture1);
	bgSprite1.setScale(1.25f, 1.25f);

	sf::Texture bgTexture2;
	if (!bgTexture2.loadFromFile("bg/par_1b.bmp"))
		std::cout << "error loading texture." << std::endl;
	sf::Sprite bgSprite2 = sf::Sprite(bgTexture2);
	bgSprite2.setScale(1.25f, 1.25f);

	std::unordered_map<std::string, sf::Sprite*> spriteAssets;
	spriteAssets["par_1a"] = &bgSprite1;
	spriteAssets["par_1b"] = &bgSprite2;

	sf::RectangleShape textBox(sf::Vector2f(800.0f, 600.0f));
	textBox.setFillColor(sf::Color(0, 0, 0, 100));

	vn::Dialogue dialogue1;
	dialogue1.setLine("Lorem ipsum dolor sit amet,");

	vn::Dialogue dialogue2;
	dialogue2.setLine(" consectetur adipiscing elit, ");

	vn::Dialogue dialogue3;
	dialogue3.setLine("sed do eiusmod\ntempor incididunt ut labore et dolore magna aliqua.");

	vn::Block* blocks[3];
	blocks[0] = &dialogue1;
	blocks[1] = &dialogue2;
	blocks[2] = &dialogue3;

	int currentBlock = 0;

	std::stringstream ss;
	ss << (static_cast<vn::Dialogue*>(blocks[currentBlock])->GetLine());

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(10, 5);
	text.setString(ss.str());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "Left mouse clicked." << std::endl;
					if (currentBlock < 2)
					{
						currentBlock++;
						ss << (static_cast<vn::Dialogue*>(blocks[currentBlock])->GetLine());
						text.setString(ss.str());
					}
					else
					{
						currentBlock = -1;
						ss.str(std::string());
						text.setString(ss.str());
					}
				}
			}
		}
		
		window.clear();
		window.draw(*spriteAssets["par_1b"]);
		window.draw(textBox);
		window.draw(text);
		window.display();
	}

	return 0;
}