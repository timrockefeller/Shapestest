#include <stdio.h>
#include "SoundSystem.h"
#include "fmod_inc\fmod_errors.h"

SoundSystem::SoundSystem() {
	ERRCHECK(FMOD::System_Create(&fmod_system));
	
	ERRCHECK(fmod_system->setSoftwareFormat(OUTPUTRATE, 
											FMOD_SPEAKERMODE_RAW,
											2
	));
											
	ERRCHECK(fmod_system->init( 32, FMOD_INIT_NORMAL, 0));
	
	ERRCHECK(fmod_system->createDSPByType(FMOD_DSP_TYPE_FFT, &dspSpectrum));
}
SoundSystem::~SoundSystem() {
	ERRCHECK(music->release());
	ERRCHECK(fmod_system->close());
	ERRCHECK(fmod_system->release());
}

void SoundSystem::playMusic(std::string song_name) {
	ERRCHECK(fmod_system->createStream(	song_name.c_str(),
										FMOD_LOOP_OFF | FMOD_3D | FMOD_UNIQUE, 
										0, 
										&music
	));
	ERRCHECK(fmod_system->playSound(music,
									0,
									false,
									&channel
	));
	channel->addDSP(0, dspSpectrum);
}
void SoundSystem::killPlaying()
{
	ERRCHECK(channel->stop());
}
void SoundSystem::update () {
	ERRCHECK(fmod_system->update());
	getSpectrumCurruentTime();
}

unsigned int SoundSystem::getPositionInMs()
{
	unsigned int pos=0;
	channel->getPosition(&pos, FMOD_TIMEUNIT_MS);
	return pos;
}

unsigned int SoundSystem::getSongLengthInMs()
{
	unsigned int length=0;
	ERRCHECK(music->getLength(&length, FMOD_TIMEUNIT_MS));
	return length;
}

float SoundSystem::getSpectrumCurruentTime()
{
	FMOD_DSP_PARAMETER_FFT *fft;

	char* ts = new char[40];
	dspSpectrum->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&fft, 0, 0, 0);
	/*for (int channel = 0; channel < fft->numchannels; channel++) {
		for (int bin = 0; bin < fft->length; bin++)
		{
			float val = fft->spectrum[channel][bin];
			printf(ts, "> spec: %f \n", val);
		}
	}*/
	float temp = fft->spectrum[0][4];
	return temp;
}

inline void SoundSystem::ERRCHECK(FMOD_RESULT result)
{
	printf(FMOD_ErrorString(result));
}
