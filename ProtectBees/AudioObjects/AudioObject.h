#pragma once

class AudioObject
{
public:
	AudioObject();
	virtual ~AudioObject();

	virtual void load(std::string filename);
	virtual void setLoop(bool isLooping);
	virtual void setVolume(float volume);
	virtual void play();
	virtual void pause();
	virtual void stop();

	enum Status {
		Stopped,
		Paused,
		Playing
	};

private:
	std::string _filename;
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	bool _isLoaded;
	Status _status;
};
