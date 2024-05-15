#include "Core/AudioEngine.h"
#include <iostream>
#include <fmod_errors.h>

AudioEngineData AudioEngine::s_EngineData;

void AudioEngine::Init()
{
	s_EngineData.result = FMOD::System_Create(&s_EngineData.pSystem);
	ErrorCheck();

	s_EngineData.result = s_EngineData.pSystem->init(32, FMOD_INIT_NORMAL, 0);
	ErrorCheck();

	s_EngineData.pSystem->createSound("assets/sfx/bababooey.mp3", FMOD_DEFAULT, NULL, &s_EngineData.pS1);
	s_EngineData.pSystem->createSound("assets/sfx/charlie.mp3", FMOD_DEFAULT, NULL, &s_EngineData.pS2);
}

void AudioEngine::Shutdown()
{
	s_EngineData.pS1->release();
	s_EngineData.pS2->release();

	s_EngineData.pSystem->close();
	s_EngineData.pSystem->release();
}

void AudioEngine::OnUpdate()
{
	s_EngineData.pSystem->update();
}

void AudioEngine::Play(int index)
{
	//if (index == 0) s_EngineData.result = s_EngineData.pSystem->playSound(s_EngineData.pS1, NULL, false, &s_EngineData.pChannel);
	//else if(index == 1) s_EngineData.result = s_EngineData.pSystem->playSound(s_EngineData.pS2, NULL, false, &s_EngineData.pChannel);

	//ErrorCheck();
}

void AudioEngine::ErrorCheck()
{
	if (s_EngineData.result != FMOD_OK) printf("FMOD error! (%d) %s\n", s_EngineData.result, FMOD_ErrorString(s_EngineData.result));
}