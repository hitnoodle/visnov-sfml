#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "Dialogue.hpp"
#include "Background.hpp"

// Variable declarations
std::vector<sf::Texture*> g_Textures;
std::unordered_map<std::string, sf::Sprite*>* g_Backgrounds;
std::unordered_map<std::string, sf::Sprite*>* g_Actors;

// Function declarations
sf::Texture* loadTexture(const std::string& texturePath);
std::unordered_map<std::string, sf::Sprite*>* loadBackgrounds(const std::unordered_map<std::string, std::string>& backgroundToLoad);
std::unordered_map<std::string, sf::Sprite*>* loadActors(const std::unordered_map<std::string, std::string>& actorToLoad);
void DestroyResources();

int main()
{
	/// Main application window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Visual Novel Framework", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	/// Resources

	// Load our font
	sf::Font g_Font;
	if (!g_Font.loadFromFile("fonts/Stellar-Regular.otf"))
		std::cout << "error loading font." << std::endl;
	
	// Load background and create the background map
	std::unordered_map<std::string, std::string> backgroundToLoad;
	backgroundToLoad["Background1"] = "bg/par_1a.bmp";
	backgroundToLoad["Background2"] = "bg/par_1b.bmp";

	g_Backgrounds = loadBackgrounds(backgroundToLoad);
	backgroundToLoad.clear();

	// Create our text box
	sf::RectangleShape g_TextBox(sf::Vector2f(800.0f, 600.0f));
	g_TextBox.setFillColor(sf::Color(0, 0, 0, 100));

	// Load actor and create the actor map
	std::unordered_map<std::string, std::string> actorToLoad;
	actorToLoad["bea_def_1"] = "actor/bea/bea_defa1.png";
	actorToLoad["bea_def_2"] = "actor/bea/bea_defa2.png";
	actorToLoad["but_def_1"] = "actor/but/but_futekia1.png";
	actorToLoad["but_def_2"] = "actor/but/but_futekia2.png";

	g_Actors = loadActors(actorToLoad);
	actorToLoad.clear();

	// Create our position array for our actor
	sf::Vector2f* g_Position[2];

	sf::Vector2f posLeft(200.0f, 600.f);
	sf::Vector2f posRight(600.0f, 600.f);

	g_Position[0] = &posLeft;
	g_Position[1] = &posRight;

	/// VN Data

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
	
	/// VN Setup

	int currentBlockIndex = -1;

	vn::Background* background = NULL;

	std::stringstream ss;
	sf::Text text;

	text.setFont(g_Font);
	text.setCharacterSize(24);
	text.setPosition(10, 5);
	text.setString(ss.str());

	bool isWriting = false;

	/// Main application loop

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
		{
			sf::Sprite* currentBackground = g_Backgrounds->at(background->GetBackgroundID());
			window.draw(*currentBackground);
		}

		(*g_Actors)["but_def_1"]->setPosition(*g_Position[0]);
		window.draw(*(*g_Actors)["but_def_1"]);

		(*g_Actors)["bea_def_1"]->setPosition(*g_Position[1]);
		window.draw(*(*g_Actors)["bea_def_1"]);

		if (isWriting)
		{
			window.draw(g_TextBox);
			window.draw(text);
		}

		window.display();
	}

	/// Unload all resources 
	DestroyResources();

	return 0;
}

sf::Texture* loadTexture(const std::string & texturePath)
{
	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(texturePath))
		std::cout << "error loading texture " << texturePath << std::endl;

	return texture;
}

std::unordered_map<std::string, sf::Sprite*>* loadBackgrounds(const std::unordered_map<std::string, std::string>& backgroundToLoad)
{
	// Create the background map, remember to DELETE this
	std::unordered_map<std::string, sf::Sprite*>* backgrounds = new std::unordered_map<std::string, sf::Sprite*>();

	for (auto it = backgroundToLoad.begin(); it != backgroundToLoad.end(); it++)
	{
		// Load the texture
		sf::Texture* bgTexture = loadTexture(it->second);
		g_Textures.push_back(bgTexture);

		// Make and process the sprite
		sf::Sprite* bgSprite = new sf::Sprite(*bgTexture); 
		bgSprite->setScale(1.25f, 1.25f);

		(*backgrounds)[it->first] = bgSprite;
	}

	return backgrounds;
}

std::unordered_map<std::string, sf::Sprite*>* loadActors(const std::unordered_map<std::string, std::string>& actorToLoad)
{
	// Create the actor map, remember to DELETE this
	std::unordered_map<std::string, sf::Sprite*>* actors = new std::unordered_map<std::string, sf::Sprite*>();

	for (auto it = actorToLoad.begin(); it != actorToLoad.end(); it++)
	{
		// Load the texture
		sf::Texture* actorTexture = loadTexture(it->second);
		actorTexture->setSmooth(true);

		g_Textures.push_back(actorTexture);
	
		// Make and process the sprite
		sf::Sprite* actorSprite = new sf::Sprite(*actorTexture);
		actorSprite->setOrigin(actorTexture->getSize().x / 2.0f, actorTexture->getSize().y); // Origin = lower center
		actorSprite->setScale(0.5f, 0.5f);

		(*actors)[it->first] = actorSprite;
	}

	return actors;
}

void DestroyResources()
{
	// Delete all the background sprites
	for (auto it = g_Backgrounds->begin(); it != g_Backgrounds->end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}

	// Clear the background map
	g_Backgrounds->clear();
	delete g_Backgrounds;
	g_Backgrounds = NULL;

	// Delete all the actor sprites
	for (auto it = g_Actors->begin(); it != g_Actors->end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}

	// Clear the actor map
	g_Actors->clear();
	delete g_Actors;
	g_Actors = NULL;

	// Delete all the textures
	for (auto it = g_Textures.begin(); it != g_Textures.end(); it++)
	{
		delete (*it);
		*it = NULL;
	}

	// Clear the texture array
	g_Textures.clear();
}