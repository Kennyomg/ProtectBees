#include "../stdafx.h"
#include "AudioManager.h"
#include "../Game.h"

AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{
	std::for_each(_audioObjects.begin(), _audioObjects.end(), AudioObjectDeallocator());
}

void AudioManager::add(std::string name, AudioObject* audioObject)
{
	_audioObjects.insert(std::pair<std::string, AudioObject*>(name, audioObject));
}

void AudioManager::remove(std::string name)
{
	std::map<std::string, AudioObject*>::iterator results = _audioObjects.find(name);
	if (results != _audioObjects.end()) {
		delete results->second;
		_audioObjects.erase(results);
	}
}

AudioObject* AudioManager::get(std::string name) const
{
	std::map<std::string, AudioObject*>::const_iterator results = _audioObjects.find(name);
	if (results == _audioObjects.end()) {
		return NULL;
	}
	return results->second;
}

void AudioManager::play(std::string name)
{
	std::map<std::string, AudioObject*>::const_iterator results = _audioObjects.find(name);
	if (results != _audioObjects.end()) {
		results->second->play();
	}
}

void AudioManager::pause(std::string name)
{
	std::map<std::string, AudioObject*>::const_iterator results = _audioObjects.find(name);
	if (results != _audioObjects.end()) {
		results->second->pause();
	}
}

void AudioManager::stop(std::string name)
{
	std::map<std::string, AudioObject*>::const_iterator results = _audioObjects.find(name);
	if (results != _audioObjects.end()) {
		results->second->stop();
	}
}

void AudioManager::pauseAll()
{

}

void AudioManager::resumeAll()
{

}
