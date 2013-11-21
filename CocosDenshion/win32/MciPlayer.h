#ifndef _MCI_PLAYER_WIN32_H_
#define _MCI_PLAYER_WIN32_H_

#include "CCStdC.h"
#include <mmsystem.h>

#define MCI_MAX_VOLUME_VALUE    (1000.0)

namespace CocosDenshion {

class MciPlayer
{
public:
    MciPlayer();
    ~MciPlayer();

    void Close();

    /**
    @brief 打开声音文件(使用mciSendCommand方法)
    @param pFileName 播放的声音文件名称，需要包含文件的路径
    @param uId       播放声音文件路径的hash值, nSoundID
    */
    void Open(const char* pFileName, UINT uId);

    /**
    @brief 打开声音文件(使用mciSendStringA方法)
    @param pFileName 播放的声音文件名称，需要包含文件的路径
    @param uId       播放声音文件路径的hash值, nSoundID
    */
    void OpenA(const char* pFileName, UINT uId);

    /**
    @brief 播放声音文件(使用mciSendCommand方法)
    @param nTimes    播放声音文件的循环次数，默认值为 1，即播放一次
    */
    void Play(UINT uTimes = 1);

    /**
    @brief 播放声音文件(使用mciSendStringA方法)
    @param nTimes    播放声音文件的循环次数，默认值为 1，即播放一次
    */
    void PlayA(UINT uTimes = 1);

    /**
    @brief 暂停播放声音
    */
    void Pause();

    /**
    @brief 继续播放声音
    */
    void Resume();

    /**
    @brief 停止播放声音
    */
    void Stop();

    /**
    @brief 重新播放
    */
    void Rewind();

    /**
    @brief 获取播放器当前是否正在播放中
    */
    bool IsPlaying();

    /**
    @brief 获取当前播放的音效 ID
    @return 当前播放的音效ID
    */
    UINT GetSoundID();

    /**
     * added by shines77(gz_shines@msn.com), 2013-11-16
     */

    /**
    @brief 获取当前播放的音效 AliasName
    @return 当前播放的音效别名
    */
    char* GetAliasName();

    /**
    @brief 获取声音文件的音量
    */
    float GetVolume(const char* pFileName, UINT uId = 0);

    /**
    @brief 设置声音文件的音量
    */
    bool SetVolume(float volume);

    /**
    @brief 设置声音文件的音量(使用mciSendStringA方法)
    */
    bool SetVolume(float volume, const char* pFileName);

    /**
    @brief 生成声音文件的别名, 用于控制声音文件的音量
    @return 声音文件的别名
    */
    char* GenMciAliasName(UINT uId, char* pszAliasName = NULL, size_t dwAliasSize = 0);

    /**
     * added by shines77(gz_shines@msn.com), 2013-11-16
     */

private:
    friend LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    DWORD _SendGenericCommand(int nCommand, DWORD_PTR dwParam1 = NULL, DWORD_PTR dwParam2 = NULL);

    HWND        m_hWnd;
    MCIDEVICEID m_hDev;
    UINT        m_nSoundID;
    UINT        m_uTimes;
    bool        m_bPlaying;

    /**
     * added by shines77(gz_shines@msn.com), 2013-11-16
     * 声音文件的别名, 用于控制声音文件的音量
     */
    char        m_szAliasName[MAX_PATH];
    UINT        m_uAliasCount;
};

} // end of namespace CocosDenshion

#endif  // !_MCI_PLAYER_WIN32_H_
