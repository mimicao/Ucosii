#include "SystemConfig.h"

/* �����ջ*/
OS_STK MainTask_Stk[MainTask_StkSize];
OS_STK App1Task_Stk[App1Task_StkSize];
OS_STK App2Task_Stk[App2Task_StkSize];

OS_EVENT *Sem1;
OS_EVENT *Sem2;
INT8U    err;

int main(void)
{
	OSInit(); /* ϵͳ��ʼ��*/
			  /* ����������*/
	OSTaskCreate(MainTask, (void *)0, &MainTask_Stk[MainTask_StkSize - 1], MainTask_Prio);
	OSStart(); /* ��ʼ�������*/
	return 0;
}
/* ������*/
void MainTask(void *p_arg)
{
	p_arg = p_arg;
	OSStatInit(); /* ͳ�������ʼ��*/
	Sem1 = OSSemCreate(1);
	Sem2 = OSSemCreate(2);
	while (1)
	{
		/* ������������*/
		OSTaskCreate(App1Task, (void *)0, &App1Task_Stk[App1Task_StkSize - 1], App1Task_Prio);
		OSTaskCreate(App2Task, (void *)0, &App2Task_Stk[App2Task_StkSize - 1], App2Task_Prio);

		OSTimeDlyHMSM(0, 0, 5, 0); /* �������*/
								   //OSTaskDel(MainTask_Prio); /* ɾ��������*/
	}
}
/* App1Task */
void App1Task(void *p_arg)
{
	p_arg = p_arg;
	while (1)
	{
	    OSSemPend(Sem1, 0, &err);
		printf("App1 get time: %d!\n", GetCount() );

		OSTimeDlyHMSM(0, 0, 1, 0); /* �������*/

		OSSemPost(Sem1);

	}
}

/* App2Task */
void App2Task(void *p_arg)
{
	p_arg = p_arg;
	while (1)
	{

	    OSSemPend(Sem1, 0, &err);
		printf("App2 get time: %d!\n", GetCount() );
		OSTimeDlyHMSM(0, 0, 1, 0); /* �������*/
		OSSemPost(Sem1);

	}
}

INT32U GetCount(void)
{
    INT32U i;

    i = OSTimeGet();

    return i;

}
