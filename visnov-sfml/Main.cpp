#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "Dialogue.hpp"
#include "Background.hpp"

// Function declarations
sf::Texture* loadTexture(const std::string& texturePath);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Visual Novel Framework", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Resources

	sf::Font g_Font;
	if (!g_Font.loadFromFile("fonts/Stellar-Regular.otf"))
		std::cout << "error loading font." << std::endl;
	
	sf::Texture* bgTexture1 = loadTexture("bg/par_1a.bmp");
	sf::Texture* bgTexture2 = loadTexture("bg/par_1b.bmp");

	std::vector<sf::Texture*> g_Textures;
	g_Textures.push_back(bgTexture1);
	g_Textures.push_back(bgTexture2);

	sf::Sprite bgSprite1 = sf::Sprite(*bgTexture1);
	bgSprite1.setScale(1.25f, 1.25f);

	sf::Sprite bgSprite2 = sf::Sprite(*bgTexture2);
	bgSprite2.setScale(1.25f, 1.25f);

	std::unordered_map<std::string, sf::Sprite*> g_Backgrounds;
	g_Backgrounds["Background1"] = &bgSprite1;
	g_Backgrounds["Background2"] = &bgSprite2;

	sf::RectangleShape g_TextBox(sf::Vector2f(800.0f, 600.0f));
	g_TextBox.setFillColor(sf::Color(0, 0, 0, 100));

	//std::unordered_map<std::string, sf::Sprite*> g_Actors;
	//std::unordered_map<int, sf::Vector2f*> g_Position;

	// VN Data

	vn::Background bg1("Background1");
	vn::Background bg2("Background2");

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

	text.setFont(g_Font);
	text.setCharacterSize(24);
	text.setPosition(10, 5);
	text.setString(ss.str());

	bool isWriting = false;

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
						isWriting = false;

						vn::Block* currentBlock = blocks[currentBlockIndex];
						std::string currentCommand = currentBlock->GetCommand();
						if (currentCommand == "bg")
						{
							background = (static_cast<vn::Background*>(currentBlock));
						}
						else if (currentCommand == "d")
						{
							ss << (static_cast<vn::Dialogue*>(currentBlock)->GetLine());
							text.setString(ss.str());
							isWriting = true;
						}
						else if (currentCommand == "a")
						{
						
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
			window.draw(*g_Backgrounds[background->GetBackgroundID()]);

		if (isWriting)
		{
			window.draw(g_TextBox);
			window.draw(text);
		}

		window.display();
	}

	// Unload resources here 
	for (auto it = g_Textures.begin(); it != g_Textures.end(); it++)
	{
		delete (*it);
		*it = NULL;
	}

	g_Textures.clear();

	return 0;
}

sf::Texture* loadTexture(const std::string & texturePath)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath))
		std::cout << "error loading texture " << texturePath << std::endl;

	return texture;
}
