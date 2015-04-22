// �������̣߳�������Ӵ��п�
UINT CommProc(LPVOID pParam)
{
	OVERLAPPED os;
	DWORD dwMask, dwTrans;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	CTTYDoc *pDoc = (CTTYDoc*)pParam;

	memset(&os, 0, sizeof(OVERLAPPED));
	os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (os.hEvent == NULL)
	{
		AfxMessageBox("Can't create event object!");
		return (UINT)-1;
	}

	while (pDoc->m_bConnected)
	{
		ClearCommError(pDoc->m_hCom, &dwErrorFlags, &ComStat);

		if (ComStat.cbInQue)
		{
			// ���޵ȴ�WM_COMMNOTIFY��Ϣ��������
			WaitForSingleObject(pDoc->m_hPostMsgEvent, INFINITE);
			ResetEvent(pDoc->m_hPostMsgEvent);

			// ֪ͨ��ͼ
			PostMessage(pDoc->m_hTermWnd, WM_COMMNOTIFY, EV_RXCHAR, 0);

			continue;
		}

		dwMask = 0;

		if (!WaitCommEvent(pDoc->m_hCom, &dwMask, &os)) // �ص�����
		{

			if (GetLastError() == ERROR_IO_PENDING)
				// ���޵ȴ��ص��������
				GetOverlappedResult(pDoc->m_hCom, &os, &dwTrans, TRUE);
			else
			{
				CloseHandle(os.hEvent);
				return (UINT)-1;
			}
		}
	}

	CloseHandle(os.hEvent);
	return 0;
}

// ��ָ���������ַ��Ӵ��п����
DWORD CTTYDoc::WriteComm(char *buf, DWORD dwLength)
{
	BOOL fState;
	DWORD length = dwLength;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	ClearCommError(m_hCom, &dwErrorFlags, &ComStat);
	fState = WriteFile(m_hCom, buf, length, &length, &m_osWrite);

	if (!fState)
	{

		if (GetLastError() == ERROR_IO_PENDING)
		{
			GetOverlappedResult(m_hCom, &m_osWrite, &length, TRUE);// �ȴ�
		}
		else
			length = 0;
	}

	return length;
}

// �Ӵ��п����뻺�����ж���ָ���������ַ�
DWORD CTTYDoc::ReadComm(char *buf, DWORD dwLength)
{
	DWORD length = 0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	ClearCommError(m_hCom, &dwErrorFlags, &ComStat);
	length = min(dwLength, ComStat.cbInQue);
	ReadFile(m_hCom, buf, length, &length, &m_osRead);

	return length;
}

// �򿪲����ô��пڣ������������߳�
BOOL CTTYDoc::OpenConnection()
{
	COMMTIMEOUTS TimeOuts;
	POSITION firstViewPos;
	CView *pView;

	firstViewPos = GetFirstViewPosition();
	pView = GetNextView(firstViewPos);

	m_hTermWnd = pView->GetSafeHwnd();

	if (m_bConnected)
		return FALSE;

	m_hCom = CreateFile(m_sPort, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL); // �ص���ʽ

	if (m_hCom == INVALID_HANDLE_VALUE)
		return FALSE;

	SetupComm(m_hCom, MAXBLOCK, MAXBLOCK);
	SetCommMask(m_hCom, EV_RXCHAR);


	// �Ѽ����ʱ��Ϊ��󣬰��ܳ�ʱ��Ϊ0������ReadFile�������ز���ɲ���
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;

	/* ����д��ʱ��ָ��WriteComm��Ա�����е�GetOverlappedResult�����ĵȴ�ʱ��*/
	TimeOuts.WriteTotalTimeoutMultiplier = 50;
	TimeOuts.WriteTotalTimeoutConstant = 2000;

	SetCommTimeouts(m_hCom, &TimeOuts);

	if (ConfigConnection())
	{

		m_pThread = AfxBeginThread(CommProc, this, THREAD_PRIORITY_NORMAL,
			0, CREATE_SUSPENDED, NULL); // �����������߳�

		if (m_pThread == NULL)
		{
			CloseHandle(m_hCom);
			return FALSE;
		}
		else

		{
			m_bConnected = TRUE;
			m_pThread->ResumeThread(); // �ָ��߳�����
		}
	}
	else
	{
		CloseHandle(m_hCom);
		return FALSE;
	}

	return TRUE;
}

//�ر����ӣ��رչ����߳�
void CloseConnection()
{
	if (!m_bConnected)
		return;

	m_bConnected = FALSE;

	//����CommProc�߳���WaitSingleObject�����ĵȴ�
	SetEvent(m_hPostMsgEvent);

	//����CommProc�߳���WaitCommEvent�ĵȴ�
	SetCommMask(m_hCom, 0);

	//�ȴ������߳���ֹ
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	m_pThread = NULL;
	CloseHandle(m_hCom);

}






#include "stdafx.h"

#include "SerialPort.h"

#include "assert.h"

CSerialPort::CSerialPort()

{

	memset(&m_OverlappedRead, 0, sizeof(m_OverlappedRead));

	memset(&m_OverlappedWrite, 0, sizeof(m_OverlappedWrite));

	m_bOpened = false;

	m_ReadComThread = NULL;

	m_hIDCom = NULL;

	m_dwReadLen = 0;

}

CSerialPort::~CSerialPort()

{

}

BOOL CSerialPort::OpenPort(UINT nPort, UINT nBaud)

{

	ASSERT(nPort > 0 && nPort < 5);

	if (m_bOpened)

		return true;



	TCHAR szPort[15];

	TCHAR szComParams[50];

	DCB dcb;

	wsprintf(szPort, _T("COM%d"), nPort);

	m_hIDCom = ::CreateFile(szPort,

		GENERIC_READ | GENERIC_WRITE,

		0,

		NULL,

		OPEN_EXISTING,

		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,

		NULL);

	if (m_hIDCom == NULL)

		return false;

	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));

	memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));

	COMMTIMEOUTS CommTimeOuts;

	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;

	CommTimeOuts.ReadTotalTimeoutConstant = 0;

	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;

	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;

	CommTimeOuts.WriteTotalTimeoutConstant = 5000;

	::SetCommTimeouts(m_hIDCom, &CommTimeOuts);

	wsprintf(szComParams, _T("COM%d:%d,N,8,1"), nPort, nBaud);

	m_OverlappedRead.Offset = 0;

	m_OverlappedRead.OffsetHigh = 0;

	m_OverlappedRead.hEvent = ::CreateEvent(NULL, true, false, NULL);

	m_OverlappedWrite.Offset = 0;

	m_OverlappedWrite.OffsetHigh = 0;

	m_OverlappedWrite.hEvent = ::CreateEvent(NULL, true, false, NULL);

	dcb.DCBlength = sizeof(DCB);

	::GetCommState(m_hIDCom, &dcb);

	dcb.BaudRate = nBaud;

	dcb.ByteSize = 8;

	dcb.Parity = 0;

	if (!SetCommState(m_hIDCom, &dcb) || !SetupComm(m_hIDCom, 4096, 4096) ||

		m_OverlappedRead.hEvent == NULL || m_OverlappedWrite.hEvent == NULL)

	{

		DWORD dwError = ::GetLastError();

		if (m_OverlappedRead.hEvent != NULL)

			::CloseHandle(m_OverlappedRead.hEvent);

		if (m_OverlappedWrite.hEvent != NULL)

			::CloseHandle(m_OverlappedWrite.hEvent);

		::CloseHandle(m_hIDCom);

		return false;

	}

	::SetCommMask(m_hIDCom, EV_RXCHAR);

	::PurgeComm(m_hIDCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	::EscapeCommFunction(m_hIDCom, SETDTR);

	m_bOpened = true;

	m_bExitThread = false;

	StartMonitoring();

	return m_bOpened;

}

BOOL CSerialPort::Close()

{

	if (!m_bOpened || m_hIDCom == NULL)

		return true;

	m_bExitThread = true;

	::SetCommMask(m_hIDCom, 0);

	StopMonitoring();



	if (m_OverlappedRead.hEvent != NULL)

		::CloseHandle(m_OverlappedRead.hEvent);

	if (m_OverlappedWrite.hEvent != NULL)

		::CloseHandle(m_OverlappedWrite.hEvent);

	::CloseHandle(m_hIDCom);

	m_bOpened = false;

	m_hIDCom = NULL;

	return true;

}

//�򴮿�д����

void CSerialPort::WriteToPort(BYTE *Byte, int Len)

{

	if (!m_bOpened || m_hIDCom == NULL)

		return;

	BOOL bWriteStat;

	DWORD dwBytesWritten;

	ClearReadBuf();

	bWriteStat = ::WriteFile(m_hIDCom, Byte, Len, &dwBytesWritten, &m_OverlappedWrite);

	if (!bWriteStat && (::GetLastError() == ERROR_IO_PENDING))

	{

		//WaitForSingleObject�����������hHandle�¼����ź�״̬����������ִ��ʱ�䳬��dwMilliseconds��

		//���أ����������dwMillisecondsΪINFINITEʱ������ֱ����Ӧʱ���¼�������ź�״̬�ŷ��أ�

		//�����һֱ�ȴ���ȥ��ֱ��WaitForSingleObject�з���ֱ��ִ�к���Ĵ��롣

		DWORD dw = ::WaitForSingleObject(m_OverlappedWrite.hEvent, INFINITE);

		if (dw == WAIT_TIMEOUT)

		{

			dwBytesWritten = 0;

			DCB dcb;

			::GetCommState(m_hIDCom, &dcb);

			::PurgeComm(m_hIDCom, PURGE_TXCLEAR);

			return;

		}

		else

		{

			::GetOverlappedResult(m_hIDCom, &m_OverlappedWrite, &dwBytesWritten, false);//�ȴ����������IO����

			m_OverlappedWrite.Offset += dwBytesWritten;

		}

	}

	return;

}

//�Ӵ��ڶ�ȡ����

int CSerialPort::ReadFromPort(BYTE *lpszBlock, int nRLen)

{

	if (!m_bOpened || m_hIDCom == NULL)

		return 0;

	BOOL bReadStat;

	DWORD dwBytesRead, dwErrorFlags;

	COMSTAT ComStat;

	::ClearCommError(m_hIDCom, &dwErrorFlags, &ComStat);

	if (!ComStat.cbInQue)

		return 0;

	dwBytesRead = (DWORD)ComStat.cbInQue;

	if (nRLen < (int)dwBytesRead)

		dwBytesRead = (DWORD)nRLen;

	bReadStat = ::ReadFile(m_hIDCom, lpszBlock, dwBytesRead, &dwBytesRead, &m_OverlappedRead);

	if (!bReadStat)

	{

		if (::GetLastError() == ERROR_IO_PENDING)

		{

			::WaitForSingleObject(m_OverlappedRead.hEvent, INFINITE);

			return (int)dwBytesRead;

		}

		return 0;

	}

	return (int)dwBytesRead;

}

UINT CSerialPort::CommThread(LPVOID pParam)

{

	CSerialPort* pSerialPort = (CSerialPort*)pParam;

	BYTE Buffer[4096];

	DWORD dwEvent, dwError;

	COMSTAT ComStat;

	int ReadLen = 0;

	memset(pSerialPort->m_ReadBuf, '\0', sizeof(pSerialPort->m_ReadBuf));

	::SetCommMask(pSerialPort->m_hIDCom, EV_RXCHAR);

	while (!pSerialPort->m_bExitThread)

	{

		memset(Buffer, '\0', 4096);

		::WaitCommEvent(pSerialPort->m_hIDCom, &dwEvent, NULL);

		::ClearCommError(pSerialPort->m_hIDCom, &dwError, &ComStat);

		if ((dwEvent & EV_RXCHAR) && ComStat.cbInQue)

		{

			pSerialPort->m_dwReadLen = pSerialPort->ReadFromPort(Buffer, 4096);

			pSerialPort->m_dwReadLen = ReadLen >4096 ? 4096 : ReadLen;

			if (pSerialPort->m_dwReadLen > 0)

			{

				memcpy(pSerialPort->m_ReadBuf, Buffer, pSerialPort->m_dwReadLen);

			}

		}

		::PurgeComm(pSerialPort->m_hIDCom, PURGE_RXCLEAR);

	}

	return 0;

}

BOOL CSerialPort::StartMonitoring()

{

	if (m_ReadComThread == NULL)

	{

		if (!(m_ReadComThread = ::AfxBeginThread(CommThread, this)))

			return false;

	}

	return true;

}

BOOL CSerialPort::StopMonitoring()

{

	if (m_ReadComThread != NULL)

	{

		::TerminateThread(m_ReadComThread->m_hThread, 0); //�ս��߳�

		m_ReadComThread = NULL;

	}

	return true;

}

void CSerialPort::ClearReadBuf()

{

	memset(m_ReadBuf, '\0', sizeof(m_ReadBuf));

	m_dwReadLen = 0;

}