#pragma once

#include <string>

#include "bass.h"

#include "HashMap.h"

namespace FieaGameEngine
{
	class AudioManager
	{
	public:

		static const std::string UtsabBork;
		static const std::string JenBaa;
		static const std::string GameMusic;
		static const std::string InstructionScreenMusic;
		static const std::string TitleScreenMusic;
		static const std::string EndScreenMusic;
		static const std::string WolfBork;

		/// <summary>
		/// Frees up all the audio that was created
		/// </summary>
		~AudioManager() = default;

		static HSAMPLE& GetSample(const std::string& filePath);

		/// <summary>
		/// Initalize the Audio
		/// </summary>
		/// <returns></returns>
		static void Init();

		/// <summary>
		/// Destroys all the audio that was initialzed for the
		/// HSAMPLE
		/// </summary>
		static void DestroyAudio();

		/// <summary>
		/// Loads the audio with a file path and then returns the sample so it can 
		/// that object that called the load can have a refernce to the audio
		/// </summary>
		/// <param name="filePath">
		/// String that represents the file path
		/// </param>
		/// <param name="isSoundEffect">
		/// Boolean that represents if the file path represents a sound effect or not
		/// </param>
		/// <returns></returns>
		static void LoadAudio(const std::string& filePath, bool isSoundEffect = true);

		/// <summary>
		/// Plays and audio file on a specific channel depening
		/// if the audio is a sound effect or not
		/// </summary>
		/// <param name="sample">
		/// The aduio source
		/// \/param>
		/// <param name="isSoundEffect">
		/// Boolean that represents the audio type
		/// </param>
		static void PlayAduio(HSAMPLE& sample, bool isSoundEffect = true);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="isSoundEffect"></param>
		static void PauseAudio(bool isSoundEffect = true);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="isSoundEffect"></param>
		static void StopAudio(bool isSoundEffect = true);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="isSoundEffect"></param>
		static void UnPauseAudio(bool isSoundEffect = true);
	private:

		AudioManager() = default;

		static HashMap<std::string, HSAMPLE*> mAudioList;

		static const std::string directory;

		static HCHANNEL mMusicChannel;
		static HCHANNEL mSoundEffectChannel;
	};
}

