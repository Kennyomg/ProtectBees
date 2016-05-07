#pragma once

class GUI
{
public:
	GUI(std::string filename);
	~GUI();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& renderWindow);
	
	void addText(std::string name, sf::Text* text);
	void removeText(std::string name);

	sf::Text* getText(std::string name);
private:
	std::map<std::string, sf::Text*> _texts;

	sf::Font _font;
	bool _isLoaded;

	struct TextDeallocator
	{
		void operator()(const std::pair<std::string, sf::Text* > & p) const {
			delete p.second;
		}
	};
};