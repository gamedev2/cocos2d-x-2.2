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
    @brief �������ļ�(ʹ��mciSendCommand����)
    @param pFileName ���ŵ������ļ����ƣ���Ҫ�����ļ���·��
    @param uId       ���������ļ�·����hashֵ, nSoundID
    */
    void Open(const char* pFileName, UINT uId);

    /**
    @brief �������ļ�(ʹ��mciSendStringA����)
    @param pFileName ���ŵ������ļ����ƣ���Ҫ�����ļ���·��
    @param uId       ���������ļ�·����hashֵ, nSoundID
    */
    void OpenA(const char* pFileName, UINT uId);

    /**
    @brief ���������ļ�(ʹ��mciSendCommand����)
    @param nTimes    ���������ļ���ѭ��������Ĭ��ֵΪ 1��������һ��
    */
    void Play(UINT uTimes = 1);

    /**
    @brief ���������ļ�(ʹ��mciSendStringA����)
    @param nTimes    ���������ļ���ѭ��������Ĭ��ֵΪ 1��������һ��
    */
    void PlayA(UINT uTimes = 1);

    /**
    @brief ��ͣ��������
    */
    void Pause();

    /**
    @brief ������������
    */
    void Resume();

    /**
    @brief ֹͣ��������
    */
    void Stop();

    /**
    @brief ���²���
    */
    void Rewind();

    /**
    @brief ��ȡ��������ǰ�Ƿ����ڲ�����
    */
    bool IsPlaying();

    /**
    @brief ��ȡ��ǰ���ŵ���Ч ID
    @return ��ǰ���ŵ���ЧID
    */
    UINT GetSoundID();

    /**
     * added by shines77(gz_shines@msn.com), 2013-11-16
     */

    /**
    @brief ��ȡ��ǰ���ŵ���Ч AliasName
    @return ��ǰ���ŵ���Ч����
    */
    char* GetAliasName();

    /**
    @brief ��ȡ�����ļ�������
    */
    float GetVolume(const char* pFileName, UINT uId = 0);

    /**
    @brief ���������ļ�������
    */
    bool SetVolume(float volume);

    /**
    @brief ���������ļ�������(ʹ��mciSendStringA����)
    */
    bool SetVolume(float volume, const char* pFileName);

    /**
    @brief ���������ļ��ı���, ���ڿ��������ļ�������
    @return �����ļ��ı���
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
     * �����ļ��ı���, ���ڿ��������ļ�������
     */
    char        m_szAliasName[MAX_PATH];
    UINT        m_uAliasCount;
};

} // end of namespace CocosDenshion

#endif  // !_MCI_PLAYER_WIN32_H_
