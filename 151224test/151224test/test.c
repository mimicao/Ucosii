#include "SystemConfig.h"

/* 定义堆栈*/
OS_STK MainTask_Stk[MainTask_StkSize];
OS_STK App1Task_Stk[App1Task_StkSize];
OS_STK App2Task_Stk[App2Task_StkSize];

OS_EVENT *Sem1;
INT8U    err;

int main(void)
{
	OSInit(); /* 系统初始化*/
			  /* 创建主任务*/
	OSTaskCreate(MainTask, (void *)0, &MainTask_Stk[MainTask_StkSize - 1], MainTask_Prio);
	OSStart(); /* 开始任务调度*/
	return 0;
}
/* 主任务*/
void MainTask(void *p_arg)
{
	p_arg = p_arg;
	OSStatInit(); /* 统计任务初始化*/
	OSSemCreate(1);
	while (1)
	{
		/* 创建其他任务*/
		OSTaskCreate(App1Task, (void *)0, &App1Task_Stk[App1Task_StkSize - 1], App1Task_Prio);
		OSTaskCreate(App2Task, (void *)0, &App2Task_Stk[App2Task_StkSize - 1], App2Task_Prio);

		OSTimeDlyHMSM(0, 0, 1, 0); /* 任务调度*/
								   //OSTaskDel(MainTask_Prio); /* 删除主任务*/
	}
}
/* App1Task */
void App1Task(void *p_arg)
{
	p_arg = p_arg;
	while (1)
	{
	    OSSemPend(Sem1, 0, &err)
		printf("App1 get time: %d!\n", GetCount() );
		OSSemPost(Sem1);

		OSTimeDlyHMSM(0, 0, 1, 0); /* 任务调度*/
	}
}
/* App2Task */
void App2Task(void *p_arg)
{
	p_arg = p_arg;
	while (1)
	{

	    OSSemPend(Sem1, 0, &err)
		printf("App2 get time: %d!\n", GetCount() );
		OSSemPost(Sem1);

		OSTimeDlyHMSM(0, 0, 2, 0); /* 任务调度*/
	}
}

INT32U GetCount(void)
{
    INT32U i;

    i = OSTimeGet();

    return i;

}
