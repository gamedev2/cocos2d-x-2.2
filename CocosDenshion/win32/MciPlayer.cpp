#include "MciPlayer.h"
#include <stdio.h>
#include <tchar.h>
#include <digitalv.h>
#include <excpt.h>

#define WIN_CLASS_NAME      "CocosDenshionCallbackWnd"
#define BREAK_IF(cond)      if (cond) break;

namespace CocosDenshion {

static HINSTANCE s_hInstance = NULL;
static MCIERROR  s_mciError  = 0;

/**
 * added by shines77(gz_shines@msn.com), 2013-11-16
 * 记录声音文件构造的次数, 用于区别不同的声音文件, 保证每一个声音文件有一个"唯一"的别名
 */
static UINT      s_uAliasCount = 0;

static LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

MciPlayer::MciPlayer()
: m_hWnd(NULL)
, m_hDev(NULL)
, m_nSoundID(0)
, m_uTimes(0)
, m_bPlaying(false)
, m_uAliasCount(0)
{
    /**
     * added by shines77(gz_shines@msn.com), 2013-11-16
     * 每构造一次计数一次, 保证每个不同的声音文件有一个唯一的别名
     */
    s_uAliasCount++;

    // 别名(Alias)初始化
    m_szAliasName[0] = '\0';
    m_uAliasCount = s_uAliasCount;

    if (! s_hInstance)
    {
        s_hInstance = GetModuleHandle( NULL );              // Grab An Instance For Our Window

        WNDCLASS  wc;        // Windows Class Structure

        // Redraw On Size, And Own DC For Window.
        wc.style          = 0;
        wc.lpfnWndProc    = _SoundPlayProc;                 // WndProc Handles Messages
        wc.cbClsExtra     = 0;                              // No Extra Window Data
        wc.cbWndExtra     = 0;                              // No Extra Window Data
        wc.hInstance      = s_hInstance;                    // Set The Instance
        wc.hIcon          = 0;                              // Load The Default Icon
        wc.hCursor        = LoadCursor( NULL, IDC_ARROW );  // Load The Arrow Pointer
        wc.hbrBackground  = NULL;                           // No Background Required For GL
        wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
        wc.lpszClassName  = WIN_CLASS_NAME;                 // Set The Class Name

        if (! RegisterClass(&wc)
            && 1410 != GetLastError())
        {
            return;
        }
    }

    m_hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,                                    // Extended Style For The Window
        WIN_CLASS_NAME,                                     // Class Name
        NULL,                                               // Window Title
        WS_POPUPWINDOW, /*WS_OVERLAPPEDWINDOW*/             // Defined Window Style
        0, 0,                                               // Window Position
        0,                                                  // Window Width
        0,                                                  // Window Height
        NULL,                                               // No Parent Window
        NULL,                                               // No Menu
        s_hInstance,                                        // Instance
        NULL );
    if (m_hWnd)
    {
        SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
    }
}

MciPlayer::~MciPlayer()
{
    Close();

    if (m_hWnd != NULL)
    {
        DestroyWindow(m_hWnd);
        m_hWnd = NULL;
    }
}

/**
 * added by shines77(gz_shines@msn.com), 2013-11-16
 * 生成声音文件的别名, 用于控制声音文件的音量
 */
char* MciPlayer::GenMciAliasName(UINT uId, char* pszAliasName /* =NULL */,
                                   size_t dwAliasSize /* =0 */)
{
    if (m_uAliasCount == 0)
        return NULL;

    char szAliasName[MAX_PATH];
    // 声音文件的别名格式为: "mci_XX_uId", XX为MciPlayer全局构造次数
    sprintf_s(szAliasName, sizeof(szAliasName), "mci_%d_%d", m_uAliasCount, uId);
    strcpy_s(m_szAliasName, szAliasName);

    if (NULL != pszAliasName && 0 != dwAliasSize)
    {
        strcpy_s(pszAliasName, dwAliasSize, szAliasName);
        return pszAliasName;
    }
    else
    {
        return m_szAliasName;
    }
}

/**
 * 打开声音文件(使用mciSendCommand方法)
 */
void MciPlayer::Open(const char* pFileName, UINT uId)
{
    // WCHAR * pBuf = NULL;
    do
    {
        BREAK_IF(! pFileName || ! m_hWnd);
        int nLen = (int)strlen(pFileName);
        BREAK_IF(! nLen);
//         pBuf = new WCHAR[nLen + 1];
//         BREAK_IF(! pBuf);
//         MultiByteToWideChar(CP_ACP, 0, pFileName, nLen + 1, pBuf, nLen + 1);

        Close();

        MCI_OPEN_PARMS mciOpen = {0};
        MCIERROR mciError;
        mciOpen.lpstrDeviceType = (LPCTSTR)MCI_ALL_DEVICE_ID;
        mciOpen.lpstrElementName = pFileName;
        // 根据uId生成声音文件的别名, 音量控制必须通过别名进行
        mciOpen.lpstrAlias = GenMciAliasName(uId);

        mciError = mciSendCommand(0, MCI_OPEN, MCI_WAIT | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
        BREAK_IF(mciError);

        m_hDev = mciOpen.wDeviceID;
        m_nSoundID = uId;
        m_bPlaying = false;
    } while (0);
}

/**
 * added by shines77(gz_shines@msn.com), 2013-11-16
 * 打开声音文件(使用mciSendStringA方法)
 */
void MciPlayer::OpenA(const char* pFileName, UINT uId)
{
    // WCHAR * pBuf = NULL;
    do
    {
        BREAK_IF(! pFileName || ! m_hWnd);
        int nLen = (int)strlen(pFileName);
        BREAK_IF(! nLen);
        /*
        pBuf = new WCHAR[nLen + 1];
        BREAK_IF(! pBuf);
        MultiByteToWideChar(CP_ACP, 0, pFileName, nLen + 1, pBuf, nLen + 1);
        //*/

        Close();

        char szCommand[512];
        szCommand[0] = 0;
        sprintf_s(szCommand, sizeof(szCommand), "open \"%s\" alias %s", pFileName, GenMciAliasName(uId));

        MCIERROR mciError;
        mciError = mciSendStringA(szCommand, NULL, 0, 0);
        BREAK_IF(mciError);

        m_nSoundID = uId;
        m_bPlaying = false;
    } while (0);
}

/**
 * 播放声音文件(使用mciSendCommand方法)
 */
void MciPlayer::Play(UINT uTimes /* = 1 */)
{
    if (! m_hDev)
    {
        return;
    }
    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = (DWORD_PTR)m_hWnd;
    s_mciError = mciSendCommand(m_hDev, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)&mciPlay);
    if (! s_mciError)
    {
        m_bPlaying = true;
        m_uTimes = uTimes;
    }
}

/**
 * added by shines77(gz_shines@msn.com), 2013-11-16
 * 播放声音文件(使用mciSendStringA方法)
 */
void MciPlayer::PlayA(UINT uTimes /* = 1 */)
{
    char szCommand[512];
    if (strlen(m_szAliasName) != 0)
    {
        szCommand[0] = '\0';
        if (uTimes <= 0)
            sprintf_s(szCommand, sizeof(szCommand), "play %s from 0 repeat notify", m_szAliasName);
        else
            sprintf_s(szCommand, sizeof(szCommand), "play %s from 0 notify", m_szAliasName);

        // 参考: http://msdn.microsoft.com/en-us/library/windows/desktop/dd743667%28v=vs.85%29.aspx
        // "play mysound from 0 to 2000 notify"
        if (szCommand[0] != 0)
        {
            s_mciError = mciSendStringA(szCommand, NULL, 0, 0);
            if (!s_mciError)
            {
                m_bPlaying = true;
                m_uTimes = uTimes;
            }
        }
    }
}

void MciPlayer::Close()
{
    if (m_bPlaying)
    {
        Stop();
    }
    if (m_hDev)
    {
        _SendGenericCommand(MCI_CLOSE);
        m_hDev = 0;
    }
    m_bPlaying = false;
}

void MciPlayer::Pause()
{
    _SendGenericCommand(MCI_PAUSE);
}

void MciPlayer::Resume()
{
    _SendGenericCommand(MCI_RESUME);
}

void MciPlayer::Stop()
{
    MCI_GENERIC_PARMS mciStop = {0};
    mciStop.dwCallback = (DWORD)m_hWnd;
    _SendGenericCommand(MCI_STOP, NULL, (DWORD)(LPVOID)&mciStop);
    m_bPlaying = false;
}

void MciPlayer::Rewind()
{
    if (! m_hDev)
    {
        return;
    }
    mciSendCommand(m_hDev, MCI_SEEK, MCI_SEEK_TO_START, 0);

    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = (DWORD)m_hWnd;
    m_bPlaying = mciSendCommand(m_hDev, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlay) ? false : true;
}

bool MciPlayer::IsPlaying()
{
    return m_bPlaying;
}

UINT MciPlayer::GetSoundID()
{
    return m_nSoundID;
}

char* MciPlayer::GetAliasName()
{
    return &m_szAliasName[0];
}

float MciPlayer::GetVolume(const char* pFileName, UINT uId /*= 0*/)
{
    UINT nVolume = (UINT)MCI_MAX_VOLUME_VALUE;  // 1000.0
    if (nVolume > (UINT)MCI_MAX_VOLUME_VALUE)
        nVolume = (UINT)MCI_MAX_VOLUME_VALUE;
    return (float)((float)(nVolume) / (float)MCI_MAX_VOLUME_VALUE);
}

bool MciPlayer::SetVolume(float volume)
{
    if (!m_hDev)
        return false;

    UINT nVolume = (UINT)(volume * (float)MCI_MAX_VOLUME_VALUE);  // 1000.0
    if (nVolume > (UINT)MCI_MAX_VOLUME_VALUE)
        nVolume = (UINT)MCI_MAX_VOLUME_VALUE;

    MCI_DGV_SETAUDIO_PARMS mciSetAudioPara = {0};
    mciSetAudioPara.dwCallback = (DWORD)m_hWnd;
    mciSetAudioPara.dwItem = MCI_DGV_SETAUDIO_VOLUME;
    // 此处就是音量大小 (0--1000)
    mciSetAudioPara.dwValue = nVolume;

    MCIERROR mciError = mciSendCommand(m_hDev, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM,
        (DWORD)(LPVOID)&mciSetAudioPara);
    if (0 != mciError)
    {
        return false;
    }

    return true;
}

/**
 * 通过别名设置音量, 如果别名不存在, 则使用文件名, 如果无法播放, 返回错误
 */
bool MciPlayer::SetVolume(float volume, const char* pFileName)
{
    UINT nVolume = (UINT)(volume * (float)MCI_MAX_VOLUME_VALUE);   // 1000.0
    if (nVolume > (UINT)MCI_MAX_VOLUME_VALUE)
        nVolume = (UINT)MCI_MAX_VOLUME_VALUE;

    char szCommand[512];
    szCommand[0] = '\0';
    if (strlen(m_szAliasName) != 0)
    {
        sprintf_s(szCommand, sizeof(szCommand), "setaudio %s volume to %d", m_szAliasName, nVolume);
    }
    else
    {
        if (pFileName != NULL)
            sprintf_s(szCommand, sizeof(szCommand), "setaudio %s volume to %d", pFileName, nVolume);
    }

    if (strlen(szCommand) == 0)
        return false;

    MCIERROR mciError = mciSendStringA(szCommand, NULL, 0, 0);
    if (0 != mciError)
    {
        // MCIERR_UNRECOGNIZED_COMMAND
        mciError = MCIERR_UNRECOGNIZED_COMMAND;
        return false;
    }

    return true;
}

int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep)
{
    // puts("in filter.");
    if (code == EXCEPTION_ACCESS_VIOLATION) {
        // puts("caught AV as expected.");
        return EXCEPTION_EXECUTE_HANDLER;
    }
    else {
        // puts("didn't catch AV, unexpected.");
        return EXCEPTION_CONTINUE_SEARCH;
    };
}

//////////////////////////////////////////////////////////////////////////
// private member
//////////////////////////////////////////////////////////////////////////

DWORD MciPlayer::_SendGenericCommand(int nCommand, DWORD_PTR dwParam1 /*= NULL*/,
                                    DWORD_PTR dwParam2 /*= NULL*/)
{
    if (! m_hDev)
    {
        return (DWORD)(-1);
    }

    MCIERROR mciError = 0;
    char szErr[256] = {0};
    size_t nBufSize = _countof(szErr) - 1;
    BOOL bRet = 0;
    DWORD dwErrCode = 0;
    //__try
    {
        mciError = mciSendCommand(m_hDev, nCommand, dwParam1, dwParam2);
    }
    /*
    __except(filter(GetExceptionCode(), GetExceptionInformation())) {
        bRet = mciGetErrorStringA(mciError, szErr, nBufSize);
        dwErrCode = GetLastError();
    }
    //*/

    return (DWORD)mciError;
}

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    MciPlayer * pPlayer = NULL;
    if (MM_MCINOTIFY == Msg
        && MCI_NOTIFY_SUCCESSFUL == wParam
        &&(pPlayer = (MciPlayer *)GetWindowLong(hWnd, GWL_USERDATA)))
    {
        if (pPlayer->m_uTimes)
        {
            --pPlayer->m_uTimes;
        }

        if (pPlayer->m_uTimes)
        {
            mciSendCommand(lParam, MCI_SEEK, MCI_SEEK_TO_START, 0);

            MCI_PLAY_PARMS mciPlay = {0};
            mciPlay.dwCallback = (DWORD)hWnd;
            mciSendCommand(lParam, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlay);
        }
        else
        {
            pPlayer->m_bPlaying = false;
        }
        return 0;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

}  // end of namespace CocosDenshion
