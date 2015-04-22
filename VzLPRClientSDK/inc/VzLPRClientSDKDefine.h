//VZ����ʶ���豸SDK�Ľṹ��ȶ���
#ifndef _VZ_LPR_CLIENT_SDK_DEFINE_H_
#define _VZ_LPR_CLIENT_SDK_DEFINE_H_

#include <VzClientSDK_CommonDefine.h>
#include <VzClientSDK_LPDefine.h>

/**�豸�������VzLPRClient_Open��ã��豸������صĺ�������Ҫ*/
typedef int VzLPRClientHandle;

/**���ûص�����ʱ��Ҫָ��������*/
typedef enum
{
	VZ_LPRC_CALLBACK_COMMON_NOTIFY,	/**<SDKͨ����Ϣ������Ԥ����*/
	VZ_LPRC_CALLBACK_PLATE_STR,		/**<���ƺ����ַ���Ԥ����*/
	VZ_LRPC_CALLBACK_FULL_IMAGE,	/**<����ͼ��*/
	VZ_LPRC_CALLBACK_CLIP_IMAGE,	/**<��ȡͼ��*/
	VZ_LPRC_CALLBACK_PLATE_RESULT,	/**<ʵʱʶ����*/
	VZ_LPRC_CALLBACK_PLATE_RESULT_STABLE,	/**<�ȶ�ʶ����*/
	VZ_LPRC_CALLBACK_PLATE_RESULT_TRIGGER,	/**<������ʶ����������API���������IO��Ӳ������ʽ��*/
	VZ_LPRC_CALLBACK_VIDEO,			/**<��Ƶ֡�ص�*/
}
VZ_LPRC_CALLBACK_TYPE;

/**ͨ����Ϣ��������*/
typedef enum
{
	VZ_LPRC_NO_ERR = 0,		/**<�޴���*/
	VZ_LPRC_ACCESS_DENIED,	/**<�û����������*/
	VZ_LPRC_NETWORK_ERR,	/**<�������ӹ���*/
	VZ_LPRC_IO_INPUT = 100, /**<IO�������ź�*/
}
VZ_LPRC_COMMON_NOTIFY;

/**ʶ����������*/
typedef enum
{
	VZ_LPRC_RESULT_REALTIME,		/**<ʵʱʶ����*/
	VZ_LPRC_RESULT_STABLE,			/**<�ȶ�ʶ����*/
	VZ_LPRC_RESULT_FORCE_TRIGGER,	/**<���á�VzLPRClient_ForceTrigger��������ʶ����*/
	VZ_LPRC_RESULT_IO_TRIGGER,		/**<�ⲿIO�źŴ�����ʶ����*/
	VZ_LPRC_RESULT_VLOOP_TRIGGER,	/**<������Ȧ������ʶ����*/
	VZ_LPRC_RESULT_MULTI_TRIGGER,	/**<��_FORCE_\_IO_\_VLOOP_�е�һ�ֻ����ͬʱ������������Ҫ����ÿ��ʶ������TH_PlateResult::uBitsTrigType���ж�*/
	VZ_LPRC_RESULT_TYPE_NUM			/**<����������*/
}
VZ_LPRC_RESULT_TYPE;

/**���㶨��
  *X_1000��Y_1000��ȡֵ��ΧΪ[0, 1000]��
  *��λ����ϢΪʵ��ͼ��λ��������ͼ��λ�õ���Գߴ磻
  *����X_1000 = x*1000/win_width������xΪ����ͼ���е�ˮƽ����λ�ã�win_widthΪͼ����
*/
typedef struct
{
	unsigned X_1000;	/**<ˮƽ�����������*/
	unsigned Y_1000;	/**<��ֱ�����������*/
}
VZ_LPRC_VERTEX;

/**��Խ����ö��*/
typedef enum
{
	VZ_LPRC_BIDIR,		/**˫�򴥷�*/
	VZ_LPRC_UP2DOWN,	/**���ϵ��·���ĳ�������*/
	VZ_LPRC_DOWN2UP,	/**���µ��Ϸ���ĳ�������*/
}
VZ_LPRC_DIR;
/**������Ȧ����*/
#define VZ_LPRC_VIRTUAL_LOOP_NAME_LEN	32

/**������Ȧ�������*/
#define VZ_LPRC_VIRTUAL_LOOP_VERTEX_NUM	4

/**������Ȧ��Ϣ����*/
typedef struct
{
	BYTE			byID;		/**<���*/
	BYTE			byEnable;	/**<�Ƿ���Ч*/
	BYTE			byDraw;		/**<�Ƿ����*/
	BYTE			byRes[1];	/**<Ԥ��*/
	char			strName[VZ_LPRC_VIRTUAL_LOOP_NAME_LEN];			/**<�Զ�������*/
	VZ_LPRC_VERTEX	struVertex[VZ_LPRC_VIRTUAL_LOOP_VERTEX_NUM];	/**<��������*/
	VZ_LPRC_DIR		eCrossDir;	/**<��Խ��������*/
	unsigned		uTriggerTimeGap;	/**����ͬ���ƵĴ���ʱ���������ƣ���λΪ��*/
	unsigned		uMaxLPWidth;		/**����Ƴߴ�����*/
	unsigned		uMinLPWidth;		/**��С���Ƴߴ�����*/
}
VZ_LPRC_VIRTUAL_LOOP;

/**���������Ȧ����*/
#define VZ_LPRC_VIRTUAL_LOOP_MAX_NUM	8

/**������Ȧ����*/
typedef struct
{
	unsigned				uNumVirtualLoop;	/**<ʵ�ʸ���*/
	VZ_LPRC_VIRTUAL_LOOP	struLoop[VZ_LPRC_VIRTUAL_LOOP_MAX_NUM];	/**<������Ȧ����*/
}
VZ_LPRC_VIRTUAL_LOOPS;

/**ʡ���ַ��������ߴ�*/
#define VZ_LPRC_PROVINCE_STR_LEN	128

/**Ԥ��ʡ����Ϣ*/
typedef struct
{
	char strProvinces[VZ_LPRC_PROVINCE_STR_LEN];	/**<����֧�ֵ�ʡ�ݼ�ƹ��ɵ��ַ���*/
	int nCurrIndex;	/**<��ǰ��Ԥ��ʡ�ݵ���ţ���strProvinces�еģ�-1Ϊδ����*/
}
VZ_LPRC_PROVINCE_INFO;

/**ͼ����Ϣ*/
typedef struct
{
	unsigned		uWidth;			/**<���*/
	unsigned		uHeight;		/**<�߶�*/
	unsigned		uPitch;			/**<ͼ���ȵ�һ��������ռ�ڴ��ֽ���*/
	unsigned		uPixFmt;		/**<ͼ�����ظ�ʽ���ο�ö�ٶ���ͼ���ʽ��ImageFormatXXX��*/
	unsigned char	*pBuffer;	/**<ͼ���ڴ���׵�ַ*/
}
VZ_LPRC_IMAGE_INFO;

/**����֡����*/
typedef enum
{
	VZ_LPRC_DATA_ENC_VIDEO,		/**<��Ƶ֡��������*/
	VZ_LPRC_DATA_ENC_AUDIO,		/**<��Ƶ֡��������*/
}
VZ_LPRC_DATA_TYPE;

/**����֡��Ϣ*/
typedef struct
{
	unsigned char	*pBuffer;	/**<�����ڴ���׵�ַ*/
	unsigned		uDataSize;	/**<����֡�ߴ磬�ֽ���*/
	unsigned		uPTS_Sec;	/**<֡ʱ���_��*/
	unsigned		uPTS_USec;	/**<֡ʱ���_΢��*/
	unsigned char	uIsKeyFrame;/**<�ؼ�֡��־λ��1Ϊ�ؼ�֡��0Ϊ�ǹؼ�֡*/
	unsigned char	reserved[7];	/**<Ԥ��*/
}
VZ_LPRC_DATA_INFO;

/**��ͷ�䱶�佹����*/
typedef enum
{
	VZ_LENS_OPT_STOP,		/**<ֹͣ����*/
	VZ_LENS_FOCUS_FAR,		/**<��Զ���۽�*/
	VZ_LENS_FOCUS_NEAR,		/**<�������۽�*/
	VZ_LENS_ZOOM_TELE,		/**<�������䱶*/
	VZ_LENS_ZOOM_WIDE,		/**<���̽��䱶*/
}
VZ_LENS_OPT;

/**LED���������*/
typedef enum
{
	VZ_LED_AUTO,		/**<�Զ�����LED�Ŀ��͹�*/
	VZ_LED_MANUAL_ON,	/**<�ֶ�����LED����*/
	VZ_LED_MANUAL_OFF,	/**<�ֶ�����LED�ر�*/
}
VZ_LED_CTRL;

/**�û�˽�����ݵ�����ֽ���*/
#define VZ_LPRC_USER_DATA_MAX_LEN	128

/**�豸Ψһ���к�*/
typedef struct
{
	unsigned uHi;	/**<��λ*/
	unsigned uLo;	/**<��λ*/
}
VZ_DEV_SERIAL_NUM;

/**�豸����ʱ�����*/
typedef struct
{
	unsigned uYear;		/**<��*/
	unsigned uMonth;	/**<�� [1, 12]*/
	unsigned uMDay;		/**<���е����� [1, 31]*/
	unsigned uHour;		/**<ʱ*/
	unsigned uMin;		/**<��*/
	unsigned uSec;		/**<��*/
}
VZ_DATE_TIME_INFO;

/**���ڲ���*/
typedef struct
{
	unsigned uBaudRate;		/**<������*/
	unsigned uParity;		/**<У��λ ��ֵΪ0-4=no,odd,even,mark,space*/
	unsigned uDataBits;		/**<����λ ��ֵΪ4-8=4,5,6,7,8 λ����λ*/
	unsigned uStopBit;		/**<ֹͣλ ��ֵΪ0,1,2 = 1, 1.5, 2 λֹͣλ*/
}
VZ_SERIAL_PARAMETER;

/**�洢�豸����*/
typedef enum
{
	VZ_STORAGE_DEV_SD = 0,	/**<SD��*/
	VZ_STORAGE_DEV_HD		/**<Ӳ��*/
}
VZ_STORAGE_DEV_TYPE;

/**�洢�豸״̬*/
typedef enum
{
	VZ_STORAGE_DEV_NO_PART = 0, /**<δ����*/
	VZ_STORAGE_DEV_PART_OK,		/**<�ѷ���*/
}
VZ_STORAGE_DEV_STATUS;

/**�洢�豸�����Ĺ���״̬*/
typedef enum
{
	VZ_STORAGE_DEV_PART_ERROR = 0,	/**<�쳣*/
	VZ_STORAGE_DEV_PART_NOT_FORMAT,	/**<δ��ʽ��*/
	VZ_STORAGE_DEV_PART_NOT_MOUNT,	/**<δ����*/
	VZ_STORAGE_DEV_PART_FORMATING,	/**<���ڸ�ʽ��*/
	VZ_STORAGE_DEV_PART_DELETING,	/**<����ɾ���ļ�*/
	VZ_STORAGE_DEV_PART_NORMAL,		/**<��������״̬*/
}
VZ_STORAGE_DEV_PART_STATUS;

/**�洢�豸������Ϣ*/
typedef struct
{
	VZ_STORAGE_DEV_PART_STATUS	eStatus;	/**<����״̬*/
	unsigned	uUsed;			/**<���ÿռ䣨MB)*/
	unsigned	uLeft;			/**<���ÿռ䣨MB)*/
	unsigned	uTotal;			/**<��������MB��*/
	int			nFormatPercent;	/**<��ʽ���ٷֱ�*/
}
VZ_STORAGE_DEV_PART_INFO;

#define VZ_MAX_NUM_STORAGE_DEV_PART_NUM	4
/**�����洢�豸��Ϣ*/
typedef struct
{
	char reserved[32];
	VZ_STORAGE_DEV_TYPE		eType;					/**<�洢�豸����*/
	VZ_STORAGE_DEV_STATUS	eStatus;				/**<�洢�豸״̬*/
	unsigned				uPartNum;				/**<��������*/
	VZ_STORAGE_DEV_PART_INFO	struPartInfo[VZ_MAX_NUM_STORAGE_DEV_PART_NUM];		/**<��������Ϣ*/
}
VZ_STORAGE_DEVICE_INFO;

#define VZ_MAX_NUM_STORAGE_DEVICE	4
/**�洢�豸��Ϣ*/
typedef struct
{
	int nDevCount;		/**<�洢�豸����*/
	VZ_STORAGE_DEVICE_INFO	struSDI[VZ_MAX_NUM_STORAGE_DEVICE];	/**<���洢�豸��Ϣ*/
}
VZ_STORAGE_DEVICES_INFO;

#define LPRC_OSDTEXTLEN				16

typedef struct
{
	unsigned char	dstampenable;					// 0 off 1 on
	int				dateFormat;						// 0:YYYY/MM/DD;1:MM/DD/YYYY;2:DD/MM/YYYY
	int				datePosX;
	int				datePosY;
	unsigned char	tstampenable;   				// 0 off 1 on
	int				timeFormat;						// 0:12Hrs;1:24Hrs
	int				timePosX;
	int				timePosY;
	unsigned char	nLogoEnable;					// 0 off 1 on
	int				nLogoPositionX;   				///<  logo position
	int				nLogoPositionY;   				///<  logo position
	unsigned char	nTextEnable;					///0 off 1 on
	int				nTextPositionX;   				///<  text position
	int				nTextPositionY;   				///<  text position
	char			overlaytext[LPRC_OSDTEXTLEN];	///user define text
}VZ_LPRC_OSD_Param;

#endif
