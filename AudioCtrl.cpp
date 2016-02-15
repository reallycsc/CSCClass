#include "AudioCtrl.h"

NS_CSC_BEGIN
static AudioCtrl _sharedContext;

AudioCtrl* AudioCtrl::getInstance()
{
	static bool s_bFirstUse = true;
	if (s_bFirstUse)
	{
		_sharedContext.init();
		s_bFirstUse = false;
	}
	return &_sharedContext;
}

AudioCtrl::AudioCtrl(): m_pSimpleAudioEngine(nullptr), m_nCurBackgroundMusicIndex(0), m_bIsListPlaying(false), m_bIsPause(false), m_bIsMute(false), m_bIsRandom(false), m_bIsMusicTitleShown(false)
{
	m_vBackgroundMusics.clear();
}

AudioCtrl::~AudioCtrl()
{
	m_vBackgroundMusics.clear();
	Director::getInstance()->getScheduler()->unschedule("update", this);
}

bool AudioCtrl::init()
{
	bool bRet = false;
	do
	{
		m_pSimpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

		bRet = true;
	} while (false);
	return bRet;
}

void AudioCtrl::addBackgroundMusic(const char* pszFilePath)
{
	m_pSimpleAudioEngine->preloadBackgroundMusic(pszFilePath);
	m_vBackgroundMusics.push_back(pszFilePath);
}

void AudioCtrl::playBackgroundMusicList(bool isRandom)
{
	int listSize = (int)m_vBackgroundMusics.size();
	CS_RETURN_IF(listSize == 0);

	// stop the background music which is playing
	if (m_pSimpleAudioEngine->isBackgroundMusicPlaying())
		m_pSimpleAudioEngine->stopBackgroundMusic();

	// start play in list
	m_bIsListPlaying = true;
	m_bIsPause = false;
	m_bIsRandom = isRandom;
	if (m_bIsRandom)
		m_nCurBackgroundMusicIndex = random(0, listSize - 1);
	else
		m_nCurBackgroundMusicIndex = 0;
	auto music_fullname = m_vBackgroundMusics.at(m_nCurBackgroundMusicIndex);
	m_pSimpleAudioEngine->playBackgroundMusic(music_fullname.c_str(), false);
	this->showMusicTitle(music_fullname);
	auto director = Director::getInstance();
	director->getScheduler()->schedule(CC_CALLBACK_1(AudioCtrl::update, this), this, director->getAnimationInterval(), CC_REPEAT_FOREVER, 0, false, "update");
}

void AudioCtrl::stopBackgroundMusic()
{
	m_bIsListPlaying = false;
	m_bIsPause = false;
	m_bIsRandom = false;
	m_pSimpleAudioEngine->stopBackgroundMusic();
	Director::getInstance()->getScheduler()->unschedule("update", this);
}

void AudioCtrl::pauseBackgroundMusic()
{
	m_bIsPause = true;
	m_pSimpleAudioEngine->pauseBackgroundMusic();
}

void AudioCtrl::resumeBackgroundMusic()
{
	m_bIsPause = false;
	m_pSimpleAudioEngine->resumeBackgroundMusic();
}

void AudioCtrl::muteBackgroundMusic()
{
	if (m_bIsMute)
	{
		this->resumeBackgroundMusic();
		this->showMusicTitle(m_vBackgroundMusics.at(m_nCurBackgroundMusicIndex));
	}
	else
		this->pauseBackgroundMusic();
	m_bIsMute = !m_bIsMute;
}

void AudioCtrl::update(float dt)
{
	CS_RETURN_IF(!m_bIsListPlaying || m_bIsPause || m_bIsMute);

	if (!m_pSimpleAudioEngine->isBackgroundMusicPlaying())
	{
		if (m_bIsRandom)
			m_nCurBackgroundMusicIndex = random(0, static_cast<int>(m_vBackgroundMusics.size() - 1));
		else
			m_nCurBackgroundMusicIndex++;
		auto music_fullname = m_vBackgroundMusics.at(m_nCurBackgroundMusicIndex);
		m_pSimpleAudioEngine->playBackgroundMusic(music_fullname.c_str(), false);
		this->showMusicTitle(music_fullname);
	}
}

void AudioCtrl::showMusicTitle(const string &music_fullname)
{
	auto scene = Director::getInstance()->getRunningScene();
	CS_RETURN_IF(!scene || m_bIsMusicTitleShown);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto music_name = music_fullname.substr(0, music_fullname.find_last_of("."));
	auto music_title = Label::createWithTTF(music_name, "fonts/fzzj.ttf", 32);
	Size titleSize = music_title->getContentSize();
	music_title->enableShadow();
	
	LayerColor* bg = LayerColor::create(Color4B(0, 0, 0, 128), visibleSize.width, titleSize.height);
	music_title->setPosition(visibleSize.width / 2, titleSize.height / 2);
	bg->addChild(music_title);
	auto pos_x = 0;
	auto pos_start = Point(pos_x, visibleSize.height + titleSize.height);
	bg->setPosition(pos_start);
	bg->runAction(Sequence::create(
		MoveTo::create(0.5f, Point(pos_x, visibleSize.height - titleSize.height)),
		DelayTime::create(2.0f),
		MoveTo::create(0.5f, pos_start),
		CallFunc::create([=]()->void 
	{
		music_title->removeFromParent();
		m_bIsMusicTitleShown = false;
	}),
		NULL));

	scene->addChild(bg);
	m_bIsMusicTitleShown = true;
}

NS_CSC_END
