#include "../stdafx.h"
#include "AudioObject.h"

AudioObject::AudioObject()
	: _isLoaded(false), _status(AudioObject::Status::Stopped)
{
}


AudioObject::~AudioObject()
{
}

void AudioObject::load(std::string filename) {
	if (_buffer.loadFromFile(filename) == false) {
		_filename = "";
		_isLoaded = false;
	}
	else {
		_filename = filename;
		_sound.setBuffer(_buffer);
		_isLoaded = true;
	}
}
void AudioObject::setLoop(bool isLooping) {
	_sound.setLoop(isLooping);
}

void AudioObject::setVolume(float volume) {
	_sound.setVolume(volume);
}

void AudioObject::play() {
	if (_status != AudioObject::Status::Playing) {
		_sound.play();
		_status = AudioObject::Status::Playing;
	}
}

void AudioObject::pause() {
	if (_status == AudioObject::Status::Playing) {
		_sound.pause();
		_status = AudioObject::Status::Paused;
	}
}

void AudioObject::stop() {
	if (_status == AudioObject::Status::Playing) {
		_sound.stop();
		_status = AudioObject::Status::Stopped;
	}
}