#pragma once

// This class is intended for extending but can also be used for game objects
class VisibleGameObject
{
public:
	VisibleGameObject();
	// Overload for the constructor. Argument is the file path for a image
	VisibleGameObject(std::string filename);
	virtual ~VisibleGameObject();

	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow& window);
	virtual void update(sf::Time elapsedTime);

	virtual void setPosition(float x, float y);
	virtual sf::Vector2f getPosition() const;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual std::string getName() const;
	virtual void setName(std::string name);

	virtual bool isLoaded() const;
	virtual sf::Rect<float> getBoundingRect() const;

protected:
	sf::Sprite& getSprite();
	
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	std::string _name;
	bool _isLoaded;

};
