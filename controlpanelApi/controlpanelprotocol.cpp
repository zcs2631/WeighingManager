#include "stdafx.h"
#include "controlpanelprotocol.h"

//У����

int opendoor(char * data, int lenth)
{
	//FC2 = 0x40��DATA = 0x0e����ʾ���ֹ���բ������Ч�����ܣ�
	data[0] = 0x01;
	data[1] = 0x43;
	data[2] = 0x40;
	data[3] = 0x0e;
	data[4] = 0x0e;
	data[5] = 0x0e;
	data[6] = 0x02;

	lenth = 7;
	return 0;
}

int closedoor()
{
	return 0;
}