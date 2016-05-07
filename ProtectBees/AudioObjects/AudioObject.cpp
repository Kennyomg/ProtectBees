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
	// Only play when it's not playing
	if (_status != AudioObject::Status::Playing) {
		_sound.play();
		_status = AudioObject::Status::Playing;
	}
}

void AudioObject::pause() {
	// Only pause when it's actually playing
	if (_status == AudioObject::Status::Playing) {
		_sound.pause();
		_status = AudioObject::Status::Paused;
	}
}

void AudioObject::stop() {
	// Only stop when it's actually playing or paused
	if (_status == AudioObject::Status::Playing || _status == AudioObject::Status::Paused) {
		_sound.stop();
		_status = AudioObject::Status::Stopped;
	}
}