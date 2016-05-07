#pragma once

class PauseUI
{
public:
	PauseUI(std::string filepath);
	~PauseUI();

	void draw(sf::RenderWindow& window);
	void update(sf::Time& deltaTime);

private:
	std::map<std::string, sf::Text*> _texts;
	sf::Font _font;
	bool _isLoaded;
	sf::RectangleShape _overlay;

	// Deallocator function for deleting texts (I like this snippet)
	struct TextDeallocator
	{
		void operator()(const std::pair<std::string, sf::Text* > & p) const {
			delete p.second;
		}
	};
};