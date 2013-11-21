#include "SimpleAudioEngine.h"

#include <map>
#include <cstdlib>

#include "MciPlayer.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

#define USE_MCI_SEND_COMMAND        1

namespace CocosDenshion {

typedef map<unsigned int, MciPlayer *> EffectList;
typedef pair<unsigned int, MciPlayer *> Effect;

static char     s_szRootPath[MAX_PATH];
static DWORD    s_dwRootLen;
static char     s_szFullPath[MAX_PATH];

/**
 * added by shines77(gz_shines@msn.com), 2013-11-16
 * For setting the volume of the background music and the effects sound
 * on Windows use mciSendStringA(),
 * we must transfer the path name to the short path name.
 */
static char     s_szFullPath_Short[MAX_PATH];

static std::string _FullPath(const char * szPath);
static std::string _FullPath_Short(const char * szPath);
static unsigned int _Hash(const char *key);

#define BREAK_IF(cond)  if (cond) break;

static EffectList& sharedList()
{
    static EffectList s_List;
    return s_List;
}

static MciPlayer& sharedMusic()
{
    static MciPlayer s_Music;
    return s_Music;
}

SimpleAudioEngine::SimpleAudioEngine()
: m_fBgMusicVolume(DEFAULT_BGMUSIC_VOLUME)      // 0.5
, m_fEffectsVolume(DEFAULT_EFFECTS_VOLUME)      // 0.5
{
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}

void SimpleAudioEngine::end()
{
    sharedMusic().Close();

    EffectList::iterator p = sharedList().begin();
    while (p != sharedList().end())
    {
        MciPlayer *pPlayer = p->second;
        if (pPlayer)
            pPlayer->Close();
        delete p->second;
        p->second = NULL;
        p++;
    }
    sharedList().clear();
    return;
}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    if (! pszFilePath)
    {
        return;
    }

#if defined(USE_MCI_SEND_COMMAND) && (USE_MCI_SEND_COMMAND != 0)
    sharedMusic().Open(_FullPath(pszFilePath).c_str(), _Hash(pszFilePath));
    sharedMusic().SetVolume(m_fBgMusicVolume);
    sharedMusic().Play((bLoop) ? -1 : 1);
#else
    sharedMusic().OpenA(_FullPath(pszFilePath).c_str(), _Hash(pszFilePath));
    sharedMusic().SetVolume(m_fBgMusicVolume, _FullPath_Short(pszFilePath).c_str());
    sharedMusic().PlayA((bLoop) ? -1 : 1);
#endif
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    if (bReleaseData)
    {
        sharedMusic().Close();
    }
    else
    {
        sharedMusic().Stop();
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    sharedMusic().Pause();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    sharedMusic().Resume();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    sharedMusic().Rewind();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return false;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return sharedMusic().IsPlaying();
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    unsigned int nRet = _Hash(pszFilePath);

    preloadEffect(pszFilePath);

    EffectList::iterator p = sharedList().find(nRet);
    if (p != sharedList().end())
    {
#if defined(USE_MCI_SEND_COMMAND) && (USE_MCI_SEND_COMMAND != 0)
        p->second->SetVolume(m_fEffectsVolume);
        p->second->Play((bLoop) ? -1 : 1);
#else
        p->second->SetVolume(m_fEffectsVolume, pszFilePath);
        p->second->PlayA((bLoop) ? -1 : 1);
#endif
    }

    return nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Stop();
    }
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    int nRet = 0;
    do
    {
        BREAK_IF(! pszFilePath);

        nRet = _Hash(pszFilePath);

        BREAK_IF(sharedList().end() != sharedList().find(nRet));

        sharedList().insert(Effect(nRet, new MciPlayer()));
        MciPlayer * pPlayer = sharedList()[nRet];
        if (pPlayer != NULL)
        {
            pPlayer->Open(_FullPath(pszFilePath).c_str(), nRet);

            BREAK_IF(nRet == pPlayer->GetSoundID());

            delete pPlayer;
        }
        sharedList().erase(nRet);
        nRet = 0;
    } while (0);
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Pause();
    }
}

void SimpleAudioEngine::pauseAllEffects()
{
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Pause();
    }
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Resume();
    }
}

void SimpleAudioEngine::resumeAllEffects()
{
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Resume();
    }
}

void SimpleAudioEngine::stopAllEffects()
{
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Stop();
    }
}

void SimpleAudioEngine::stopAll()
{
    stopAllEffects();
    stopBackgroundMusic();
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{

}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    unsigned int nID = _Hash(pszFilePath);

    EffectList::iterator p = sharedList().find(nID);
    if (p != sharedList().end())
    {
        delete p->second;
        p->second = NULL;
        sharedList().erase(nID);
    }
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return m_fBgMusicVolume;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    m_fBgMusicVolume = volume;
}

float SimpleAudioEngine::getEffectsVolume()
{
    return m_fEffectsVolume;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    m_fEffectsVolume = volume;
}

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

static std::string _FullPath(const char * szPath)
{
    return CCFileUtils::sharedFileUtils()->fullPathForFilename(szPath);
}

/**
 * added by shines77(gz_shines@msn.com), 2013-11-16
 * Get the DOS's short path name through a filename
 */
static std::string _FullPath_Short(const char * szPath)
{
    //return CCFileUtils::sharedFileUtils()->fullPathForFilename_Short(szPath);

    std::string fullpath_short = "";
    std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(szPath);
    if (fullpath.length() > 0)
    {
        char szShortFullPath[MAX_PATH];
        DWORD dwShortLen;
        szShortFullPath[0] = '\0';
        dwShortLen = GetShortPathNameA(fullpath.c_str(), szShortFullPath, sizeof(szShortFullPath));
        if (0 != dwShortLen)
        {
            fullpath_short = szShortFullPath;
        }
        else
        {
            // if dwShortLen == 0, then Handle an error condition.
            // printf ("GetShortPathNameA failed (%d)\n", GetLastError());
        }
    }
    return fullpath_short;
}

unsigned int _Hash(const char *key)
{
    unsigned int len = strlen(key);
    const char *end = key + len;
    unsigned int hash;

    for (hash = 0; key < end; key++)
    {
        hash *= 16777619;
        hash ^= (unsigned int)(unsigned char)toupper(*key);
    }
    return (hash);
}

} // end of namespace CocosDenshion
