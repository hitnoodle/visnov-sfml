#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "Dialogue.hpp"
#include "Background.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Visual Novel Framework", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Resources

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

	// VN Data

	vn::Background bg1("par_1a");
	vn::Background bg2("par_1b");

	vn::Dialogue dialogue1;
	dialogue1.setLine("Lorem ipsum dolor sit amet,");

	vn::Dialogue dialogue2;
	dialogue2.setLine(" consectetur adipiscing elit, ");

	vn::Dialogue dialogue3;
	dialogue3.setLine("sed do eiusmod\ntempor incididunt ut labore et dolore magna aliqua.");

	vn::Block* blocks[5];
	blocks[0] = &bg1;
	blocks[1] = &dialogue1;
	blocks[2] = &dialogue2;
	blocks[3] = &bg2;
	blocks[4] = &dialogue3;
	
	// VN Setup

	int currentBlockIndex = -1;

	vn::Background* background = NULL;

	std::stringstream ss;
	sf::Text text;

	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(10, 5);
	text.setString(ss.str());

	// Update loop

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
					if (currentBlockIndex < 4)
					{
						currentBlockIndex++;

						vn::Block* currentBlock = blocks[currentBlockIndex];
						if (currentBlock->GetCommand() == "bg")
						{
							background = (static_cast<vn::Background*>(currentBlock));
						}
						else if (currentBlock->GetCommand() == "d")
						{
							ss << (static_cast<vn::Dialogue*>(currentBlock)->GetLine());
							text.setString(ss.str());
						}
					}
					else
					{
						currentBlockIndex = -1;
						ss.str(std::string());
						text.setString(ss.str());
					}
				}
			}
		}
		
		window.clear();

		if (background != NULL) 
			window.draw(*spriteAssets[background->GetBackgroundID()]);

		window.draw(textBox);
		window.draw(text);
		window.display();
	}

	return 0;
}