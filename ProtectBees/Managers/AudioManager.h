#pragma once
#include "../AudioObjects/AudioObject.h"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void add(std::string name, AudioObject* audioObject);
	void remove(std::string name);
	AudioObject* get(std::string name) const;

	void play(std::string name);
	void pause(std::string name);
	void stop(std::string name);

private:
	std::map<std::string, AudioObject*> _audioObjects;

	struct AudioObjectDeallocator
	{
		void operator()(const std::pair<std::string, AudioObject* > & p) const {
			delete p.second;
		}
	};

};

