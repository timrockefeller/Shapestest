#pragma once 

#include <string>
#include "fmod_inc\fmod.hpp"

#define OUTPUTRATE 48000

class SoundSystem {
public:

	SoundSystem();
	~SoundSystem();


	void playMusic(std::string song_name);
	void killPlaying();
	void update();
	unsigned int getPositionInMs();
	unsigned int getSongLengthInMs();
	float getSpectrumCurruentTime();
private:
	FMOD::Sound *music=NULL;
	FMOD::DSP * dspSpectrum=NULL;
	FMOD::Channel *channel=0;

	FMOD::System *fmod_system=NULL;

	inline void ERRCHECK(FMOD_RESULT result);

	
};