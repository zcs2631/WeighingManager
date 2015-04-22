//���ڽ���VZ�ĳ���ʶ���豸����������ʶ��һ���������ʶ���ն˵ȣ���Ӧ�ó���ӿ�
#ifndef _VZ_LPRC_SDK_H_
#define _VZ_LPRC_SDK_H_
#include <VzLPRClientSDKDefine.h>

#ifdef _DEV_API_
#define VZ_LPRC_API extern "C" __declspec(dllexport)
#else
#define VZ_LPRC_API extern "C" __declspec(dllimport)
#endif

#define VZ_DEPRECATED __declspec(deprecated)

/**
* @defgroup group_global ȫ�ֲ�������
* @defgroup group_device �����豸��������
* @defgroup group_callback �ص�����
*/

/**
*  @brief ȫ�ֳ�ʼ��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note �����нӿڵ���֮ǰ����
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VzLPRClient_Setup();

/**
*  @brief ȫ���ͷ�
*  @note �ڳ������ʱ���ã��ͷ�SDK����Դ
*  @ingroup group_global
*/
VZ_LPRC_API void __stdcall VzLPRClient_Cleanup();

/**
*  @brief ͨ���ûص���������ҵ����豸������Ϣ
*  @param  [IN] pStrDevName �豸����
*  @param  [IN] pStrIPAddr	�豸IP��ַ
*  @param  [IN] usPort1		�豸�˿ں�
*  @param  [IN] usPort2		Ԥ��
*  @param  [IN] pUserData	�ص�����������
*  @ingroup group_callback
*/
typedef void (__stdcall *VZLPRC_FIND_DEVICE_CALLBACK)(const char *pStrDevName, const char *pStrIPAddr, WORD usPort1, WORD usPort2, void *pUserData);

/**
*  @brief ��ʼ�����豸
*  @param  [IN] func �ҵ����豸ͨ���ûص���������
*  @param  [IN] pUserData �ص������е�������
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VZLPRClient_StartFindDevice(VZLPRC_FIND_DEVICE_CALLBACK func, void *pUserData);

/**
*  @brief ֹͣ�����豸
*  @ingroup group_global
*/
VZ_LPRC_API void __stdcall VZLPRClient_StopFindDevice();

/**
*  @brief ͨ���ûص���������豸��һ��״̬��Ϣ
*  @param  [IN] handle		��VzLPRClient_Open������õľ��
*  @param  [IN] pUserData	�ص�����������
*  @param  [IN] eNotify		ͨ����Ϣ��������
*  @param  [IN] pStrDetail	��ϸ�����ַ���
*  @ingroup group_callback
*/
typedef void (__stdcall *VZLPRC_COMMON_NOTIFY_CALLBACK)(VzLPRClientHandle handle, void *pUserData,
													   VZ_LPRC_COMMON_NOTIFY eNotify, const char *pStrDetail);

/**
*  @brief �����豸���ӷ��������صĻص�����
*  @param  [IN] func �豸���ӽ����״̬��ͨ���ûص���������
*  @param  [IN] pUserData �ص������е�������
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VZLPRClient_SetCommonNotifyCallBack(VZLPRC_COMMON_NOTIFY_CALLBACK func, void *pUserData);

/**
*  @brief ��һ���豸
*  @param  [IN] pStrIP �豸��IP��ַ
*  @param  [IN] wPort �豸�Ķ˿ں�
*  @param  [IN] pStrUserName �����豸�����û���
*  @param  [IN] pStrPassword �����豸��������
*  @return �����豸�Ĳ������������ʧ��ʱ������0
*  @ingroup group_device
*/
VZ_LPRC_API VzLPRClientHandle __stdcall VzLPRClient_Open(const char *pStrIP, WORD wPort, const char *pStrUserName, const char *pStrPassword);

/**
*  @brief �ر�һ���豸
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_Close(VzLPRClientHandle handle);

/**
*  @brief ͨ��IP��ַ�ر�һ���豸
*  @param  [IN] pStrIP �豸��IP��ַ
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_CloseByIP(const char *pStrIP);

/**
*  @brief ��ȡ����״̬
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN/OUT] pStatus �����ȡ״̬�ı�����ַ���������Ϊ 1�����ϣ�0δ����
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note   �û��������ڵ��øú�����������ѯ�豸�Ƿ���ߣ��Լ����ߺ��Ƿ�ָ�����
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_IsConnected(VzLPRClientHandle handle, BYTE *pStatus);

/**
*  @brief ����ʵʱ��Ƶ
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] hWnd ���ڵľ��
*  @return ���ŵľ����-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_StartRealPlay(VzLPRClientHandle handle, void *hWnd);

/**
*  @brief ֹͣ����ָ���Ĳ��ž��
*  @param  [IN] nPlayHandle ���ŵľ��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note   ������ֹͣ�������Ժ���VzLPRClient_StartRealPlay��VzLPRClient_StartRealPlayFrameCallBack�Ĳ��ž��
*  @note   ֹͣ�����Ժ󣬸ò��ž����ʧЧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_StopRealPlay(int nPlayHandle);

/**
*  @brief  ͨ���ûص��������ʵʱͼ������
*  @param  [IN] handle		��VzLPRClient_Open������õľ��
*  @param  [IN] pUserData	�ص�������������
*  @param  [IN] pFrame		ͼ��֡��Ϣ������ṹ�嶨��VzYUV420P
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_callback
*/
typedef void (__stdcall *VZLPRC_VIDEO_FRAME_CALLBACK)(VzLPRClientHandle handle, void *pUserData,
													  const VzYUV420P *pFrame);
/**
*  @brief ����ʵʱͼ�����ݵĻص�����
*  @param  [IN] handle		��VzLPRClient_Open������õľ��
*  @param  [IN] func		ʵʱͼ�����ݺ���
*  @param  [IN] pUserData	�ص������е�������
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note   DEPRECATED: ��ת��Ϊʹ��VzLPRClient_StartRealPlayFrameCallBack(handle, NULL, func, pUserData);
*  @ingroup group_device
*/
VZ_DEPRECATED VZ_LPRC_API int __stdcall VzLPRClient_SetVideoFrameCallBack(VzLPRClientHandle handle, VZLPRC_VIDEO_FRAME_CALLBACK func, void *pUserData);

/**
*  @brief  ͨ���ûص��������ʵʱͼ������
*  @param  [IN] handle		��VzLPRClient_Open������õľ��
*  @param  [IN] pUserData	�ص�������������
*  @param  [IN] pFrame		ͼ��֡��Ϣ������ṹ�嶨��VZ_LPRC_IMAGE_INFO
*  @ingroup group_callback
*/
typedef void (__stdcall *VZLPRC_VIDEO_FRAME_CALLBACK_EX)(VzLPRClientHandle handle, void *pUserData,
														 const VZ_LPRC_IMAGE_INFO *pFrame);
/**
*  @brief ��ȡʵʱ��Ƶ֡��ͼ������ͨ���ص��������û��㣬�û��ɸĶ�ͼ�����ݣ�������ʾ������
*  @param  [IN] handle		��VzLPRClient_Open������õľ��
*  @param  [IN] hWnd		���ڵľ�������Ϊ��Чֵ������Ƶͼ�����ʾ���ô����ϣ����Ϊ�գ�����ʾ��Ƶͼ��
*  @param  [IN] func		ʵʱͼ�����ݺ���
*  @param  [IN] pUserData	�ص������е�������
*  @return ���ŵľ����-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_StartRealPlayFrameCallBack(VzLPRClientHandle handle, void *hWnd,
												  VZLPRC_VIDEO_FRAME_CALLBACK_EX func, void *pUserData);

/**
*  @brief  ͨ���ûص�������ñ�������
*  @param  [IN] handle		��VzLPRClient_Open������õľ��
*  @param  [IN] pUserData	�ص�������������
*  @param  [IN] eDataType	�������ͣ����ö��VZ_LPRC_DATA_TYPE
*  @param  [IN] pData		����֡��Ϣ������ṹ�嶨��VZ_LPRC_DATA_INFO
*  @ingroup group_callback
*/
typedef void (__stdcall *VZLPRC_VIDEO_DATA_CALLBACK)(VzLPRClientHandle handle, void *pUserData,
													 VZ_LPRC_DATA_TYPE eDataType, const VZ_LPRC_DATA_INFO *pData);

/**
*  @brief ��ȡʵʱ��������
*  @param  [IN] handle		��VzLPRClient_Open������õľ��
*  @param  [IN] func		�ص�����
*  @param  [IN] pUserData	�ص������е�������
*  @return ���ŵľ����-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetRealDataCallBack(VzLPRClientHandle handle,
												  VZLPRC_VIDEO_DATA_CALLBACK func, void *pUserData);

/**
*  @brief ͨ���ûص�������ó���ʶ����Ϣ
*  @param  [IN] handle			��VzLPRClient_Open������õľ��
*  @param  [IN] pUserData		�ص�������������
*  @param  [IN] pResult			������Ϣ�����׵�ַ������ṹ�嶨�� TH_PlateResult
*  @param  [IN] uNumPlates		���������еĳ��Ƹ���
*  @param  [IN] eResultType		����ʶ�������ͣ����ö�����Ͷ���VZ_LPRC_RESULT_TYPE
*  @param  [IN] pImgFull		��ǰ֡��ͼ�����ݣ�����ṹ�嶨��VZ_LPRC_IMAGE_INFO
*  @param  [IN] pImgPlateClip	��ǰ֡�г��������ͼ���������飬���е�Ԫ���복����Ϣ�����еĶ�Ӧ
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note   �����Ҫ�ûص��������ؽ�ͼ���� pImgFull ��pImgPlateClip����Ҫ�����ûص�������VzLPRClient_SetPlateInfoCallBack��ʱ�����ͼ���ݣ�����ûص��������ص�������ָ��Ϊ�գ�
*  @note   ʵʱ�����VZ_LPRC_RESULT_REALTIME���Ļص��ǲ�����ͼ���ݵ�
*  @ingroup group_callback
*/
typedef int (__stdcall *VZLPRC_PLATE_INFO_CALLBACK)(VzLPRClientHandle handle, void *pUserData,
													const TH_PlateResult *pResult, unsigned uNumPlates,
													VZ_LPRC_RESULT_TYPE eResultType,
													const VZ_LPRC_IMAGE_INFO *pImgFull,
													const VZ_LPRC_IMAGE_INFO *pImgPlateClip);

/**
*  @brief ����ʶ�����Ļص�����
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] func ʶ�����ص����������ΪNULL�����ʾ�رոûص������Ĺ���
*  @param  [IN] pUserData �ص������е�������
*  @param  [IN] bEnableImage ָ��ʶ�����Ļص��Ƿ���Ҫ������ͼ��Ϣ��1Ϊ��Ҫ��0Ϊ����Ҫ
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetPlateInfoCallBack(VzLPRClientHandle handle, VZLPRC_PLATE_INFO_CALLBACK func, void *pUserData, int bEnableImage);


/**
*  @brief �����ѻ�����Ļص�����
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] func ʶ�����ص����������ΪNULL�����ʾ�رոûص������Ĺ���
*  @param  [IN] pUserData �ص������е�������
*  @param  [IN] bEnableImage ָ��ʶ�����Ļص��Ƿ���Ҫ������ͼ��Ϣ��1Ϊ��Ҫ��0Ϊ����Ҫ
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetOfflinePlateInfoCallBack(VzLPRClientHandle handle, VZLPRC_PLATE_INFO_CALLBACK func, void *pUserData, int bEnableImage);


/**
*  @brief ������������źţ�ǿ�ƴ���ǰʱ�̵����ݲ�������
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note   ����ʶ����ͨ���ص������ķ�ʽ���أ������ǰ��Ƶ�������޳��ƣ���ص��������ᱻ����
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_ForceTrigger(VzLPRClientHandle handle);

/**
*  @brief ����������Ȧ
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pVirtualLoops ������Ȧ�Ľṹ��ָ��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetVirtualLoop(VzLPRClientHandle handle, const VZ_LPRC_VIRTUAL_LOOPS *pVirtualLoops);

/**
*  @brief ��ȡ�����õ�������Ȧ
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pVirtualLoops ������Ȧ�Ľṹ��ָ��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetVirtualLoop(VzLPRClientHandle handle,  VZ_LPRC_VIRTUAL_LOOPS *pVirtualLoops);

/**
*  @brief ��ȡ�����õ�Ԥ��ʡ��
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pProvInfo Ԥ��ʡ����Ϣָ��
*  @return 0��ʾ�ɹ�����0��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetSupportedProvinces(VzLPRClientHandle handle, VZ_LPRC_PROVINCE_INFO *pProvInfo);

/**
*  @brief ����Ԥ��ʡ��
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] nIndex ����Ԥ��ʡ�ݵ���ţ������Ҫ�ο�VZ_LPRC_PROVINCE_INFO::strProvinces�е�˳�򣬴�0��ʼ�����С��0�����ʾ������Ԥ��ʡ��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_PresetProvinceIndex(VzLPRClientHandle handle, int nIndex);

/**
*  @brief ��ͼ�񱣴�ΪJPEG��ָ��·��
*  @param  [IN] pImgInfo ͼ��ṹ�壬Ŀǰֻ֧��Ĭ�ϵĸ�ʽ����ImageFormatRGB
*  @param  [IN] pFullPathName �������·����JPG��׺�����ļ����ַ���
*  @param  [IN] nQuality JPEGѹ����������ȡֵ��Χ1~100��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note   �������ļ����е�·����Ҫ����
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VzLPRClient_ImageSaveToJpeg(const VZ_LPRC_IMAGE_INFO *pImgInfo, const char *pFullPathName, int nQuality);

/**
*  @brief ��ͼ�����ΪJPEG�����浽ָ���ڴ�
*  @param  [IN] pImgInfo ͼ��ṹ�壬Ŀǰֻ֧��Ĭ�ϵĸ�ʽ����ImageFormatRGB
*  @param  [IN/OUT] pDstBuf JPEG���ݵ�Ŀ�Ĵ洢�׵�ַ
*  @param  [IN] uSizeBuf JPEG���ݵ�ַ���ڴ�����ߴ磻
*  @param  [IN] nQuality JPEGѹ����������ȡֵ��Χ1~100��
*  @return >0��ʾ�ɹ����������ĳߴ磬-1��ʾʧ�ܣ�-2��ʾ������ѹ�����ݵ��ڴ�ߴ粻����
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VzLPRClient_ImageEncodeToJpeg(const VZ_LPRC_IMAGE_INFO *pImgInfo, void *pDstBuf, unsigned uSizeBuf, int nQuality);
/**
*  @brief �������ڲ��ŵ���Ƶ�ĵ�ǰ֡�Ľ�ͼ��ָ��·��
*  @param  [IN] hWnd ���ڲ�����Ƶ�Ĵ��ڵľ��
*  @param  [IN] pFullPathName �������·����JPG��׺�����ļ����ַ���
*  @param  [IN] nQuality JPEGѹ����������ȡֵ��Χ1~100��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note   ǰ��������ָ����hWnd�Ĵ����Ѿ�������VzLPRClient_StartRealPlay����ʵʱ��Ƶ
*  @note   ʹ�õ��ļ����е�·����Ҫ����
*  @note   DEPRECATED: ��תΪʹ��VzLPRClient_GetSnapShootToJpeg2
*  @ingroup group_device
*/
VZ_DEPRECATED VZ_LPRC_API int __stdcall VzLPRClient_GetSnapShootToJpeg(void *hWnd, const char *pFullPathName, int nQuality);

/**
*  @brief �������ڲ��ŵ���Ƶ�ĵ�ǰ֡�Ľ�ͼ��ָ��·��
*  @param  [IN] nPlayHandle ���ŵľ��
*  @param  [IN] pFullPathName �������·����JPG��׺�����ļ����ַ���
*  @param  [IN] nQuality JPEGѹ����������ȡֵ��Χ1~100��
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @note   ʹ�õ��ļ����е�·����Ҫ����
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetSnapShootToJpeg2(int nPlayHandle, const char *pFullPathName, int nQuality);

/**
*  @brief ��ȡIO�����״̬
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] uChnId IO�����ͨ���ţ���0��ʼ
*  @param  [OUT] pOutput IO�����״̬��0��ʾ�̵�����·��1��ʾ�̵�����·
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetIOOutput(VzLPRClientHandle handle, unsigned uChnId, int *pOutput);

/**
*  @brief ����IO�����״̬
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] uChnId IO�����ͨ���ţ���0��ʼ
*  @param  [OUT] nOutput ��Ҫ���õ�IO�����״̬��0��ʾ�̵�����·��1��ʾ�̵�����·
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetIOOutput(VzLPRClientHandle handle, unsigned uChnId, int nOutput);

/**
*  @brief ���ô��ڲ���
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] nSerialPort ָ��ʹ���豸�Ĵ�����ţ�0��ʾ��һ�����ڣ�1��ʾ�ڶ�������
*  @param  [IN] pParameter ��Ҫ���õĴ��ڲ������������ VZ_SERIAL_PARAMETER
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetSerialParameter(VzLPRClientHandle handle, int nSerialPort,
														 const VZ_SERIAL_PARAMETER *pParameter);

/**
*  @brief ��ȡ���ڲ���
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] nSerialPort ָ��ʹ���豸�Ĵ�����ţ�0��ʾ��һ�����ڣ�1��ʾ�ڶ�������
*  @param  [OUT] pParameter ��Ҫ��ȡ�Ĵ��ڲ������������ VZ_SERIAL_PARAMETER
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetSerialParameter(VzLPRClientHandle handle, int nSerialPort,
														 VZ_SERIAL_PARAMETER *pParameter);
/**
*  @brief ͨ���ûص��������͸��ͨ�����յ�����
*  @param  [IN] nSerialHandle VzLPRClient_SerialStart���صľ��
*  @param  [IN] pRecvData	���յ����ݵ��׵�ַ
*  @param  [IN] uRecvSize	���յ����ݵĳߴ�
*  @param  [IN] pUserData	�ص�����������
*  @ingroup group_callback
*/
typedef void (__stdcall *VZDEV_SERIAL_RECV_DATA_CALLBACK)(int nSerialHandle, const unsigned char *pRecvData, unsigned uRecvSize, void *pUserData);

/**
*  @brief ����͸��ͨ��
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] nSerialPort ָ��ʹ���豸�Ĵ�����ţ�0��ʾ��һ�����ڣ�1��ʾ�ڶ�������
*  @param  [IN] func �������ݵĻص�����
*  @param  [IN] pUserData �������ݻص�������������
*  @return ����͸��ͨ�������0��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SerialStart(VzLPRClientHandle handle, int nSerialPort,
												  VZDEV_SERIAL_RECV_DATA_CALLBACK func, void *pUserData);
/**
*  @brief ͸��ͨ����������
*  @param [IN] nSerialHandle ��VzLPRClient_SerialStart������õľ��
*  @param [IN] pData ��Ҫ��������ݿ���׵�ַ
*  @param [IN] uSizeData ��Ҫ��������ݿ���ֽ���
*  @return 0��ʾ�ɹ�������ֵ��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SerialSend(int nSerialHandle, const unsigned char *pData, unsigned uSizeData);

/**
*  @brief ͸��ͨ��ֹͣ��������
*  @param [IN] nSerialHandle ��VzLPRClient_SerialStart������õľ��
*  @return 0��ʾ�ɹ�������ֵ��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SerialStop(int nSerialHandle);

/**
*  @brief �����豸��ͷ�ı䱶�;۽�
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN] eOPT �������ͣ��������VZ_LENS_OPT
*  @return 0��ʾ�ɹ�������ֵ��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_CtrlLens(VzLPRClientHandle handle, VZ_LENS_OPT eOPT);

/**
*  @brief ��ȡLED��ǰ���ȵȼ���������ȵȼ�
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [OUT] pLevelNow ���������ǰ���ȵȼ��ĵ�ַ
*  @param [OUT] pLevelMax �������������ȵȼ��ĵ�ַ
*  @return 0��ʾ�ɹ�������ֵ��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetLEDLightStatus(VzLPRClientHandle handle, int *pLevelNow, int *pLevelMax);

/**
*  @brief ����LED���ȵȼ�
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN] nLevel��LED���ȵȼ�
*  @return 0��ʾ�ɹ�������ֵ��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetLEDLightLevel(VzLPRClientHandle handle, int nLevel);

/**
*  @brief ��ȡLED��ǰ����ģʽ
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [OUT] pCtrl ���������ǰLED���ؿ���ģʽ�ĵ�ַ��������� VZ_LED_CTRL
*  @return 0��ʾ�ɹ�������ֵ��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetLEDLightControlMode(VzLPRClientHandle handle, VZ_LED_CTRL *pCtrl);

/**
*  @brief ����LED����ģʽ
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN] eCtrl ����LED����ģʽ��������� VZ_LED_CTRL
*  @return ����ֵΪ0��ʾ�ɹ�����������ֵ��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetLEDLightControlMode(VzLPRClientHandle handle, VZ_LED_CTRL eCtrl);

/**
*  @brief д���û�˽�����ݣ������ڶ��μ���
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN] pUserData �û�����
*  @param [IN] uSizeData �û����ݵĳ��ȣ����128�ֽ�
*  @return ����ֵΪ0��ʾ�ɹ�����������ֵ��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_WriteUserData(VzLPRClientHandle handle, const unsigned char *pUserData, unsigned uSizeData);

/**
*  @brief �����û�˽�����ݣ������ڶ��μ���
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN/OUT] pBuffer ���ڴ�Ŷ������û�����
*  @param [IN] uSizeBuf �û����ݻ���������С�ߴ磬��С��128�ֽ�
*  @return ����ֵΪʵ���û����ݵ��ֽ���������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_ReadUserData(VzLPRClientHandle handle, unsigned char *pBuffer, unsigned uSizeBuf);

/**
*  @brief �����豸���кţ������ڶ��μ���
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN/OUT] pSN ���ڴ�Ŷ������豸���кţ�������� VZ_DEV_SERIAL_NUM
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetSerialNumber(VzLPRClientHandle handle, VZ_DEV_SERIAL_NUM *pSN);

/**
*  @brief ��ȡ�豸������ʱ��
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN/OUT] pDTInfo ���ڴ�Ż�ȡ�����豸����ʱ����Ϣ��������� VZ_DATE_TIME_INFO
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetDateTime(VzLPRClientHandle handle, VZ_DATE_TIME_INFO *pDTInfo);

/**
*  @brief �����豸������ʱ��
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN] pDTInfo ��Ҫ���õ��豸����ʱ����Ϣ��������� VZ_DATE_TIME_INFO
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetDateTime(VzLPRClientHandle handle, const VZ_DATE_TIME_INFO *pDTInfo);

/**
*  @brief ��ȡ�豸�Ĵ洢��Ϣ
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN/OUT] pDTInfo ���ڴ�Ż�ȡ�����豸����ʱ����Ϣ��������� VZ_DATE_TIME_INFO
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetStorageDeviceInfo(VzLPRClientHandle handle, VZ_STORAGE_DEVICES_INFO *pSDInfo);

/**
*  @brief ��ʼ¼����
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @param [IN] sFileName ¼���ļ���·��
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SaveRealData(VzLPRClientHandle handle,char *sFileName);

/**
*  @brief ֹͣ¼��
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_StopSaveRealData(VzLPRClientHandle handle);

/**
*  @brief ������ƵOSD������
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetOsdParam(VzLPRClientHandle handle, VZ_LPRC_OSD_Param *pParam);

/**
*  @brief ��ȡ��ƵOSD������
*  @param [IN] handle ��VzLPRClient_Open������õľ��
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetOsdParam(VzLPRClientHandle handle, VZ_LPRC_OSD_Param *pParam);

/**
*  @brief �����ѻ�����
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pUserData �������ݻص�������������
*   @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetOfflineCheck(VzLPRClientHandle handle);

/**
*  @brief �ر��ѻ�����
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pUserData �������ݻص�������������
*   @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_CancelOfflineCheck(VzLPRClientHandle handle);

/**
*  @brief ����ID��ѯ��¼
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] nID ���Ƽ�¼�������е�ID
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_QueryPlateRecordByID(VzLPRClientHandle handle, int nID);

/**
*  @brief ������ʼʱ��ͳ��ƹؼ��ֲ�ѯ��¼
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pStartTime ��ʼʱ�䣬��ʽ��"2015-01-02 12:20:30"
*  @param  [IN] pEndTime   ��ʼʱ�䣬��ʽ��"2015-01-02 19:20:30"
*  @param  [IN] keyword    ���ƺŹؼ���, ��"��"
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @˵��   ͨ���ص��������ݣ���෵��100�����ݣ�����ʱ����÷�ҳ��ѯ�Ľӿ�
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_QueryRecordByTimeAndPlate(VzLPRClientHandle handle, const char *pStartTime, const char *pEndTime, const char *keyword);


/**
*  @brief ����ʱ��ͳ��ƺŲ�ѯ��¼����
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pStartTime ��ʼʱ�䣬��ʽ��"2015-01-02 12:20:30"
*  @param  [IN] pEndTime   ��ʼʱ�䣬��ʽ��"2015-01-02 19:20:30"
*  @param  [IN] keyword    ���ƺŹؼ���, ��"��"
*  @return ����ֵΪ0��ʾʧ�ܣ�����0��ʾ��¼����
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_QueryCountByTimeAndPlate(VzLPRClientHandle handle, const char *pStartTime, const char *pEndTime, const char *keyword);

/**
*  @brief ����ʱ��ͳ��ƺŲ�ѯ��ҳ��¼
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pStartTime ��ʼʱ�䣬��ʽ��"2015-01-02 12:20:30"
*  @param  [IN] pEndTime   ��ʼʱ�䣬��ʽ��"2015-01-02 19:20:30"
*  @param  [IN] keyword    ���ƺŹؼ���, ��"��"
*  @param  [IN] start      ��ʼλ�ô���0,С�ڽ���λ��
*  @param  [IN] end        ����λ�ô���0,������ʼλ�ã���ȡ��¼�������ܴ���100
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_QueryPageRecordByTimeAndPlate(VzLPRClientHandle handle, const char *pStartTime, const char *pEndTime, const char *keyword, int start, int end);


/**
*  @brief ���ò�ѯ���Ƽ�¼�Ļص�����
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] func ʶ�����ص����������ΪNULL�����ʾ�رոûص������Ĺ���
*  @param  [IN] pUserData �ص������е�������
*  @param  [IN] bEnableImage ָ��ʶ�����Ļص��Ƿ���Ҫ������ͼ��Ϣ��1Ϊ��Ҫ��0Ϊ����Ҫ
*  @return 0��ʾ�ɹ���-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetQueryPlateCallBack(VzLPRClientHandle handle, VZLPRC_PLATE_INFO_CALLBACK func, void *pUserData);


/**
*  @brief ����ID��ȡ����ͼƬ
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] id     ���Ƽ�¼��ID
*  @param  [IN] pdata  �洢ͼƬ���ڴ�
*  @param  [IN][OUT] size Ϊ���봫��ֵ������ΪͼƬ�ڴ�Ĵ�С�����ص��ǻ�ȡ��jpgͼƬ�ڴ�Ĵ�С
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_LoadImageById(VzLPRClientHandle handle, int id, void *pdata, int* size);

/**
*  @brief ��ȡ��Ƶ�Ŀ�Ⱥ͸߶�
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [OUT] pWidth		��Ƶͼ���ȱ����ĵ�ַ
*  @param  [OUT] pHeight	��Ƶͼ��߶ȱ����ĵ�ַ
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetVideoFrameSize(VzLPRClientHandle handle, int *pWidth, int *pHeight);

/**
*  @brief ��ȡ��Ƶ�ı��뷽ʽ
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [OUT] pEncType	���صı��뷽ʽ, 0:H264  1:MPEG4  2:JPEG  ����:����
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetVideoEncodeType(VzLPRClientHandle handle, int *pEncType);

/**
*  @brief ��ȡGPIO��״̬
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] gpioIn ����Ϊ0��1
*  @param  [OUT] value 0�����·��1����·
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetGPIOValue(VzLPRClientHandle handle, int gpioIn, int *value);

/**
*  @brief ����ʱ���ѯ�ѻ���¼����
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pStartTime ��ʼʱ�䣬��ʽ��"2015-01-02 12:20:30"
*  @param  [IN] pEndTime   ��ʼʱ�䣬��ʽ��"2015-01-02 19:20:30"
*  @return ����ֵΪ0��ʾʧ�ܣ�����0��ʾ��¼����
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_QueryOfflineCountByTime(VzLPRClientHandle handle, const char *pStartTime, const char *pEndTime);

/**
*  @brief ����ʱ��ͳ��ƺŷ�ҳ��ѯ�ѻ���¼
*  @param  [IN] handle ��VzLPRClient_Open������õľ��
*  @param  [IN] pStartTime ��ʼʱ�䣬��ʽ��"2015-01-02 12:20:30"
*  @param  [IN] pEndTime   ��ʼʱ�䣬��ʽ��"2015-01-02 19:20:30"
*  @param  [IN] start      ��ʼλ�ô���0,С�ڽ���λ��
*  @param  [IN] end        ����λ�ô���0,������ʼλ�ã���ȡ��¼�������ܴ���100
*  @return ����ֵΪ0��ʾ�ɹ�������-1��ʾʧ��
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_QueryPageOfflineRecordByTime(VzLPRClientHandle handle, const char *pStartTime, const char *pEndTime, int start, int end);

#endif
