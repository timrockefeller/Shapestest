#pragma once 

#include <string>
#include "fmod_inc\fmod.hpp"

#define OUTPUTRATE 48000
enum SOUND_FX {
	SOUND_FX_CLICK,
	SOUND_FX_MISS
};
class SoundSystem {
public:

	SoundSystem();
	~SoundSystem();


	bool playMusic(std::string song_name);
	bool playFX(SOUND_FX fx);
	void killPlaying();
	void update();
	unsigned int getPositionInMs();
	unsigned int getSongLengthInMs();
	float getSpectrumCurruentTime(int index);
private:
	//“Ù–ß
	FMOD::Sound *fxs = NULL;
	//“Ù–ß∆µµ¿
	FMOD::Channel *fxc = NULL;
	FMOD::Sound *music=NULL;
	FMOD::DSP * dspSpectrum=NULL;
	FMOD::Channel *channel=0;

	FMOD::System *fmod_system=NULL;

	inline void ERRCHECK(FMOD_RESULT result);

	
};