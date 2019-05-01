#include "pch.h"
#include "AudioManager.h"

#include "Utility.h"

namespace FieaGameEngine
{
	HashMap<std::string, HSAMPLE*> AudioManager::mAudioList;

	const std::string AudioManager::directory = "content/Audio/";

	const std::string AudioManager::UtsabBork = "UtsabBork.wav";
	const std::string AudioManager::JenBaa = "JenniferBaaahh.wav";
	const std::string AudioManager::GameMusic = "GameThemeFinal.wav";
	const std::string AudioManager::InstructionScreenMusic = "Tutorial.wav";
	const std::string AudioManager::TitleScreenMusic = "MenuTheme.wav";
	const std::string AudioManager::EndScreenMusic =  "EndGame.wav";
	const std::string AudioManager::WolfBork = "SFXWolf.wav";

	HCHANNEL AudioManager::mMusicChannel;
	HCHANNEL AudioManager::mSoundEffectChannel;

	void AudioManager::Init()
	{
		assert(BASS_Init(-1, 44100, 0, 0, NULL));

		AudioManager::LoadAudio(UtsabBork, true);
		AudioManager::LoadAudio(JenBaa, true);
		AudioManager::LoadAudio(GameMusic, false);
		AudioManager::LoadAudio(InstructionScreenMusic, false);
		AudioManager::LoadAudio(TitleScreenMusic, false);
		AudioManager::LoadAudio(EndScreenMusic, false);
		AudioManager::LoadAudio(WolfBork, true);
	}

	HSAMPLE& AudioManager::GetSample(const std::string& filePath)
	{
		std::string directoryPath = directory + filePath;
		return *mAudioList[directoryPath];
	}

	void AudioManager::LoadAudio(const std::string& filePath, bool isSoundEffect)
	{
		HSAMPLE* sample = new HSAMPLE();

		std::string directoryPath = directory + filePath;

		if (isSoundEffect)
		{
			*sample = BASS_SampleLoad(FALSE, directoryPath.c_str(), 0, 0, 1, BASS_SAMPLE_MONO);
		}
		else
		{
			*sample = BASS_SampleLoad(FALSE, directoryPath.c_str(), 0, 0, 1, BASS_SAMPLE_LOOP);
		}

		mAudioList.Insert(std::make_pair(directoryPath, sample));
	}

	void AudioManager::PlayAduio(HSAMPLE& sample, bool isSoundEffect)
	{
		if (isSoundEffect)
		{
			mSoundEffectChannel = BASS_SampleGetChannel(sample, FALSE);
			BASS_ChannelPlay(mSoundEffectChannel, TRUE);
		}
		else
		{
			mMusicChannel = BASS_SampleGetChannel(sample, FALSE);
			BASS_ChannelPlay(mMusicChannel, TRUE);
		}
	}

	void AudioManager::StopAudio(bool isSoundEffect)
	{
		if (isSoundEffect)
		{
			BASS_ChannelStop(mSoundEffectChannel);
		}
		else
		{
			BASS_ChannelStop(mMusicChannel);
		}
	}

	void AudioManager::PauseAudio(bool isSoundEffect)
	{
		if (isSoundEffect)
		{
			BASS_ChannelPause(mSoundEffectChannel);
		}
		else
		{
			BASS_ChannelPause(mMusicChannel);
		}
	}

	void AudioManager::UnPauseAudio(bool isSoundEffect)
	{
		if (isSoundEffect)
		{
			BASS_ChannelPlay(mSoundEffectChannel, FALSE);
		}
		else
		{
			BASS_ChannelPlay(mMusicChannel, FALSE);
		}
	}

	void AudioManager::DestroyAudio()
	{
		for (auto& it : mAudioList)
		{
			BASS_SampleFree(*it.second);
			delete(it.second);
		}
	}

}
