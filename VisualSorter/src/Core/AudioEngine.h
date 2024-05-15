#pragma once
#include <fmod.hpp>

struct AudioEngineData
{
	FMOD::System* pSystem = nullptr;

	FMOD::Sound* pS1 = nullptr;
	FMOD::Sound* pS2 = nullptr;

	FMOD::Channel* pChannel = nullptr;

	FMOD_RESULT result;
};

class AudioEngine
{
public:
	static void Init();
	static void Shutdown();

	static void OnUpdate();

	static void Play(int index);
private:
	static void ErrorCheck();
private:
	static AudioEngineData s_EngineData;
};