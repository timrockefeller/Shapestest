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

bool SoundSystem::playMusic(std::string song_name) {
	ERRCHECK(fmod_system->createStream(	song_name.c_str(),
										FMOD_LOOP_OFF | FMOD_3D | FMOD_UNIQUE, 
										0, 
										&music
	));
	if (music == NULL) return false;
	ERRCHECK(fmod_system->playSound(music,
									FMOD_DEFAULT,
									false,
									&channel
	));
	channel->addDSP(0, dspSpectrum);
	return true;
}
bool SoundSystem::playFX(SOUND_FX fx)
{
	//play sound
	char * source = NULL;
	switch (fx) {
	case SOUND_FX_CLICK:
		source = "../SourceCode/Assets/FX/normal-hitfinish.wav";
		break;
	case SOUND_FX_MISS:
		source = "../SourceCode/Assets/FX/combobreak.wav";
		break;
	default:
		return false;
	}
	ERRCHECK(fmod_system->createSound(
		source,
		FMOD_DEFAULT | FMOD_3D,
		false,
		&fxs
	));
	ERRCHECK(fmod_system->playSound(
		fxs,
		FMOD_DEFAULT,
		false,
		&fxc
	));
	return true;
}
void SoundSystem::killPlaying()
{
	if (channel != NULL && music != NULL) {
		ERRCHECK(channel->stop());
		ERRCHECK(music->release());
	}
}
void SoundSystem::update () {
	ERRCHECK(fmod_system->update());
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

float SoundSystem::getSpectrumCurruentTime(int index)
{
	if (channel != NULL&&music != NULL) {
		FMOD_DSP_PARAMETER_FFT *fft=NULL;

		char* ts = new char[40];
		ERRCHECK(dspSpectrum->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&fft, 0, 0, 0));
		/*for (int channel = 0; channel < fft->numchannels; channel++) {
			for (int bin = 0; bin < fft->length; bin++)
			{
				float val = fft->spectrum[channel][bin];
				printf(ts, "> spec: %f \n", val);
			}
		}*/
		int channel = 0;
		int bin = fft->length / 512;
		float temp = 0;
		if (fft != NULL) {
			if (fft->spectrum[channel] != NULL) {
				temp = fft->spectrum[channel][index];
			}
		}
		return temp;
	}
	return 0;
}

inline void SoundSystem::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		printf(FMOD_ErrorString(result));
	}
	
}
