#ifndef __CONTROLPANELPROTOCL_H__
#define __CONTROLPANELPROTOCL_H__

//FC2 = 0x40��DATA = 0x0e����ʾ���ֹ���բ������Ч�����ܣ�
//FC2 = 0x41��DATA = 0x0e����ʾ���ֹ���բ
int opendoor(char * data,int lenth);
int closedoor(char * data, int lenth);

#endif