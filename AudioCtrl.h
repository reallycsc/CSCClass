#pragma once
#include "CommonDefinition.h"
#include <SimpleAudioEngine.h>

NS_CSC_BEGIN
class AudioCtrl : public Ref
{
public:
	AudioCtrl();
	~AudioCtrl();

	// singlar
	static AudioCtrl* getInstance();
	bool init();

	// audio functions
	void addBackgroundMusic(const char* pszFilePath);
	void playBackgroundMusicList(bool isRandom);
	void stopBackgroundMusic();
	void pauseBackgroundMusic();
	void resumeBackgroundMusic();
	void muteBackgroundMusic();

	// getter
	vector<string>* getBackgroundMusicList() {return &m_vBackgroundMusics;}

private:
	void update(float dt);
	inline void showMusicTitle(const string &music_fullname);

public:
	CC_SYNTHESIZE(bool, m_bIsListPlaying, IsListPlaying);
	CC_SYNTHESIZE(bool, m_bIsPause, IsPause);
	CC_SYNTHESIZE(bool, m_bIsMute, IsMute);

private:
	CocosDenshion::SimpleAudioEngine*	m_pSimpleAudioEngine;

	vector<string>	m_vBackgroundMusics;
	int	m_nCurBackgroundMusicIndex;

	bool	m_bIsRandom;
};
NS_CSC_END