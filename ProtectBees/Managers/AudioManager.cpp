#include "../stdafx.h"
#include "AudioManager.h"
#include "../Game.h"

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	// Delete all audio objects when the audiomanager is being deconstructed
	std::for_each(_audioObjects.begin(), _audioObjects.end(), AudioObjectDeallocator());
}

// Add audio object
void AudioManager::add(std::string name, AudioObject* audioObject)
{
	_audioObjects.insert(std::pair<std::string, AudioObject*>(name, audioObject));
}

// Remove audio object
void AudioManager::remove(std::string name)
{
	std::map<std::string, AudioObject*>::iterator results = _audioObjects.find(name);
	if (results != _audioObjects.end()) {
		delete results->second;
		_audioObjects.erase(results);
	}
}

// Get audio object
AudioObject* AudioManager::get(std::string name) const
{
	std::map<std::string, AudioObject*>::const_iterator results = _audioObjects.find(name);
	if (results == _audioObjects.end()) {
		return NULL;
	}
	return results->second;
}

// Play audio
void AudioManager::play(std::string name)
{
	std::map<std::string, AudioObject*>::const_iterator results = _audioObjects.find(name);
	if (results != _audioObjects.end()) {
		results->second->play();
	}
}

// Pause audio
void AudioManager::pause(std::string name)
{
	std::map<std::string, AudioObject*>::const_iterator results = _audioObjects.find(name);
	if (results != _audioObjects.end()) {
		results->second->pause();
	}
}

// Stop audio
void AudioManager::stop(std::string name)
{
	std::map<std::string, AudioObject*>::const_iterator results = _audioObjects.find(name);
	if (results != _audioObjects.end()) {
		results->second->stop();
	}
}