#include "Schedule.h"
#include <stdint.h>
#include "bq7695202_drive.h"
#include  "Can_Exchange.h"
#include  "RS485_exchange.h"
#include "GPIO_Par_Inter.h"
#include "ALarm_EXit_inter.h" 
#include "Usart_interface.h"
// 任务队列和状态变量
 t_EVENTION *EVE_queue[EVE_MAX];
static uint8_t TASK_MAX = 0;
static uint8_t active_task_count = 0;


static SchedulerDebugInfo debug_info = {0};

/*
static t_EVENTION Task_Gauge[EVE_MAX]=
{
	{   
    BQ769x2_ReadSafetyStatus,  //任务函数指针
    0,           //延迟计数器
    TASK_READY,   //任务状态
    PRIORITY_MEDIUM,  //任务优先级
    0,              //周期任务的时间间隔
    0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
    BQ769x2_ReadAllVoltages,  //任务函数指针
    0,           //延迟计数器
    TASK_READY,   //任务状态
    PRIORITY_MEDIUM,  //任务优先级
    0,              //周期任务的时间间隔
    0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
    BQ769x2_ReadCurrent,  //任务函数指针
    0,           //延迟计数器
    TASK_READY,   //任务状态
    PRIORITY_MEDIUM,  //任务优先级
    0,              //周期任务的时间间隔
    0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		BQ769x2_ReadCurrent,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		BQ769x2_ReadPassQ,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		BQ769x2_ReadAlarmStatus,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		CAN_SendControlFaultAlarms,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		CAN_SendComprehensiveAlarms,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		CAN_SendTempAlarms,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		CAN_SendCellAlarms,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		CAN_SendPackConfig,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		CAN_SendPackInfo,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		CAN_SendCellVoltages,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	{   
		CAN_SendTemperatures,  //任务函数指针
		0,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		0,              //周期任务的时间间隔
		0,	           //周期任务计时器
		0,               //任务ID，自由分配
	},
	


};

*/

 t_EVENTION Task_Gauge[Init_Task]=
{
	{
	  RS485_Response_Data,  //任务函数指针   //0
		0,                  //延迟计数器
		TASK_READY,           //任务状态
		PRIORITY_MEDIUM,      //任务优先级
		0,                  //周期任务的时间间隔 //period
		2,	                //周期任务计时器
		0,                    //任务ID，自由分配
		RS485_Response_Data_Task,
	},
	{
	  CAN_Send_Analog_Data,  //任务函数指针   //1
		400,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		500,              //周期任务的时间间隔 //period
		500,	           //周期任务计时器
		0,               //任务ID，自由分配
		CAN_SendCellVoltages_Task,
	},
//	{
//	  BQ769x2_ReadAllVoltages,  //任务函数指针   //若中断已经
//		0,                        //延迟计数器
//		TASK_READY,               //任务状态
//		PRIORITY_MEDIUM,          //任务优先级
//		500,                      //周期任务的时间间隔 //period
//		500,	                    //周期任务计时器
//		0,                        //任务ID，自由分配
//		BQ769x2_ReadAllVoltages_Task,
//	},
	{
		Period_Manage_Battery_Sta,    //轮回处理
		0,
		TASK_READY,
		PRIORITY_HIGH,
		2000,
		2000,
		0,
		Period_Manage_Battery_Sta_Task,
	},
//	{
//	  BQ769x2_ReadCurrent,  //任务函数指针
//		1000,           //延迟计数器
//		TASK_DELAYED,   //任务状态
//		PRIORITY_MEDIUM,  //任务优先级
//		1000,              //周期任务的时间间隔 //period
//		1000,	           //周期任务计时器
//		0,               //任务ID，自由分配
//		BQ769x2_ReadCurrent_Task,
//	},
	{
	  Read_BQ76952_Abnormal_Status,  //任务函数指针
		200,           //延迟计数器
		TASK_READY,   //任务状态
		PRIORITY_MEDIUM,  //任务优先级
		2000,              //周期任务的时间间隔 //period
		2000,	           //周期任务计时器
		0,               //任务ID，自由分配
		Read_BQ76952_Abnormal_Status_Task,
	},
	{
		Bq76952_Interrupt_processing,
		0,
		TASK_SUSPENDED,
		PRIORITY_HIGH,
		0,
		0,
		0,
		Bq76952_Interrupt_processing_Task,
	},
};



/*===========================================
              核心调度函数
===========================================*/

// 初始化调度器//初始化任务
void EVE_Init(void) {
	  uint8_t i=0; 
    for(i = 0; i < EVE_MAX; i++) {
        EVE_queue[i]= NULL;
    }
    TASK_MAX = 0;
    active_task_count = 0;
    
    // 初始化调试信息
    debug_info.max_task_count = 0;
    debug_info.current_tasks = 0;
    debug_info.dispatch_count = 0;
		for(i = 0; i < Init_Task; i++)
		{
			EVE_add(&Task_Gauge[i]);   //执行赋值函数  //存在数组溢出风险
		}		
}

// 更新任务状态(在定时器中断中调用，1ms一次)
void EVE_update(void) {
 	uint8_t i=0;
  for(i = 0; i <EVE_MAX; i++) 
	{
		if(EVE_queue[i] != NULL && EVE_queue[i]->state == TASK_DELAYED)
		{  
			if(EVE_queue[i]->delay > 0) 
			{
				 EVE_queue[i]->delay--;  // 任务等待延迟//延迟计数器
			} 
			// 延迟结束且是周期任务  /或者是定时任务
			if(EVE_queue[i]->delay == 0 && EVE_queue[i]->time_cnt>0)
			{
				EVE_queue[i]->state = TASK_READY;
				//如果是最高级别的函数  //需要直接进行执行
				//任务不能是周期任务
				if(EVE_queue[i]->priority==Highest_Mode)
				{
					EVE_queue[i]->func();   //执行任务
					EVE_queue[i]->state=TASK_SUSPENDED;  //任务直接挂起
				}
			}
		}
  }
}

// 添加任务到调度器
uint8_t EVE_add(t_EVENTION *eve) {
	 uint8_t index=0;
	 uint8_t  i=0;
    // 参数检查
    if(eve == NULL || eve->func == NULL) {
        return INVALID_ID;  //返回无效任务
    }
    
    index = INVALID_ID;
    
    // 查找空闲位置
    for( i = 0; i < EVE_MAX; i++) {
        if(EVE_queue[i] == NULL) {
            index = i;
            break;
        }
    }
    
    if(index == INVALID_ID) {
        return INVALID_ID; // 队列已满  //返回无效任务
    }
    
    // 设置任务初始状态
		if((eve->delay>0)&&(eve->period>0))
		{
			eve->state=TASK_DELAYED;
		}
		else if((eve->delay==0)&&(eve->period>0))
		{
			eve->state=TASK_READY;
		}
    eve->id = index;
    EVE_queue[index] = eve;
    
    // 更新任务计数
    active_task_count++;
    if(active_task_count > debug_info.max_task_count) {
        debug_info.max_task_count = active_task_count;
    }
    
    // 更新最大索引
    if(index > TASK_MAX) {
        TASK_MAX = index;
    }
    return index;
}

// 删除任务(通过ID)
bool EVE_del_by_id(uint8_t id)
{
	  int8_t i=0;         //???有符号i
    if(id >= EVE_MAX || EVE_queue[id] == NULL) {
        return false;
    }
    
    EVE_queue[id]->state = TASK_DELETED;
    EVE_queue[id] = NULL;
    active_task_count--;
    
    // 更新TASK_MAX
    if(id == TASK_MAX) {
        for(i = id-1; i >= 0; i--) {
            if(EVE_queue[i] != NULL) {
                TASK_MAX = i;
                break;
            }
        }
    }
    
    return true;
}

// 删除任务(通过指针)
bool EVE_del_by_ptr(t_EVENTION *eve) {
    if(eve == NULL) {
        return false;
    }
    
    return EVE_del_by_id(eve->id);
}

// 挂起任务
bool EVE_suspend(uint8_t id) {
    if(id >= EVE_MAX || EVE_queue[id] == NULL) {
        return false;
    }
    
    EVE_queue[id]->state = TASK_SUSPENDED;
    return true;
}





// 添加任务到调度器
// 通过任务指针挂起
bool EVE_Suspend_By_Ptr(t_EVENTION *task) {
	  bool task_found = false;
	  uint8_t i=0;
    if(task == NULL) return false;
    // 确保任务在队列中
    for(i = 0; i <= TASK_MAX; i++) {
        if(EVE_queue[i] == task) {
            task_found = true;
            break;
        }
    }
    if(!task_found) return false;
    // 挂起任务
    task->state = TASK_SUSPENDED;
    return true;
}








// 通过任务指针恢复
bool EVE_Resume_By_Ptr(t_EVENTION *task) {
	  bool      task_found = false;
	  uint8_t   i=0;
    if(task == NULL) return false;
    // 检查任务是否在队列中
   
    for(i = 0; i <= TASK_MAX; i++) {
        if(EVE_queue[i] == task) {
            task_found = true;
            break;
        }
    }
    if(!task_found) return false;
    // 恢复任务（保留原状态逻辑）
    if(task->delay > 0) {
        task->state = TASK_DELAYED;
    } else {
        task->state = TASK_READY;
    }
    return true;
}



uint8_t Filter_task_number(Task_Name_Enum  Task_Index_A)
{
	uint8_t i;
	for(i = 0; i <= TASK_MAX; i++) 
	{		
		if(EVE_queue[i]->func!=NULL)
		{
			if(EVE_queue[i]->Task_Name_Index == Task_Index_A) 
			{
				return EVE_queue[i]->id;
			}
		}	
  }
	//表示没有找到
  return 0;
}





// 恢复任务  //
//如果 period 大于 0，代表不是循环任务
bool EVE_resume(uint8_t id) {
    if(id >= EVE_MAX || EVE_queue[id] == NULL) {
        return false;
    }
		//如果 任务 是周期任务
    if(EVE_queue[id]->time_cnt>0)
		{
			EVE_queue[id]->delay=EVE_queue[id]->time_cnt;  //时间是0
			EVE_queue[id]->state=TASK_DELAYED;
		}
		//如果 任务 不是周期任务
		else
		{
			EVE_queue[id]->state = TASK_READY;
		}
    return true;
}

// 任务调度分发(按优先级)
void EVE_dispatch(void)
{
	TaskPriority p = PRIORITY_HIGH;
	uint8_t i = 0;
	debug_info.dispatch_count++;
	debug_info.current_tasks = active_task_count;

	// 按优先级从高到低执行任务
	for (p = PRIORITY_HIGH; p < PRIORITY_COUNT; p++)
	{
		for (i = 0; i <= TASK_MAX; i++)
		{
			if (EVE_queue[i] != NULL &&
				EVE_queue[i]->state == TASK_READY &&
				EVE_queue[i]->priority == p)
			{
				// 周期任务
				if (EVE_queue[i]->period > 0)
				{
					EVE_queue[i]->delay = EVE_queue[i]->time_cnt;
					EVE_queue[i]->state = TASK_DELAYED;
				}
				////非周期任务1.任务状态挂起
				else
				{
					// 任务挂起
					EVE_queue[i]->state = TASK_SUSPENDED;
				}
				// 执行任务
				EVE_queue[i]->func(); // 执行任务
				// 外发执行函数名称
				// Print_Func_Name(EVE_queue[i]->func);
				// 打印函数其他信息.
				// 处理周期任务
			}
		}
	}
}

void Print_Func_Name(void (*func_ptr)(void)) {
    //uint32_t func_addr = (uint32_t)func_ptr;
    //printf("Executing function at 0x%08X\r\n", func_addr);
    // 需要配合.map文件或调试符号表解析
}





// 获取调度器调试信息
SchedulerDebugInfo EVE_get_debug_info(void) {
    return debug_info;
}

//只有当一次执行任务的时候才可以触发执行
//用于满足条件触发的情况
//1.  RS485的等待延时
void Task_Wait_Trigger(uint8_t Time_Set,Task_Name_Enum Task_Name)
{
	uint8_t ID_Data=0;
	ID_Data=Filter_task_number(Task_Name);
	EVE_queue[ID_Data]->delay = Time_Set;      //时间延后             
  EVE_queue[ID_Data]->state = TASK_DELAYED;   //任务等待
}


// 任务添加函数
TaskAddResult EVE_Add_Enhanced(t_EVENTION *eve, uint8_t *assigned_id) {
    // 参数检查
	  uint8_t id=0;
	  uint8_t lowest_pri_idx=0;
  	uint8_t  i=0;
	  TaskPriority lowest_pri=PRIORITY_COUNT;
    if(eve == NULL || eve->func == NULL) {
        return TASK_ADD_INVALID_ARG;
    }
    
    // 尝试正常添加
    id = EVE_add(eve);
    if(id != INVALID_ID) {
        if(assigned_id) *assigned_id = id;
        return TASK_ADD_SUCCESS;
    }
    
    // 队列满时尝试替换最低优先级任务
    lowest_pri_idx = INVALID_ID;
    lowest_pri = PRIORITY_HIGH;
    
    for( i = 0; i <= TASK_MAX; i++) {
        if(EVE_queue[i] != NULL && 
           EVE_queue[i]->priority >= lowest_pri && //数值越大，优先级越低。挑选优先级最低任务
           EVE_queue[i]->period == 0) {  // 只替换非周期任务
            lowest_pri = EVE_queue[i]->priority;
            lowest_pri_idx = i;
        }
    }
    
    // 只有新任务优先级更高时才替换
    if(lowest_pri_idx != INVALID_ID && eve->priority < lowest_pri) {
        EVE_del_by_id(lowest_pri_idx);
        id = EVE_add(eve);
        if(id != INVALID_ID) {
            if(assigned_id) *assigned_id = id;
            return TASK_ADD_REPLACED_LOW_PRIO;
        }
    }
    
    return TASK_ADD_QUEUE_FULL;
}





void Monitor_Task(void) {
   // float usage = (float)active_task_count / EVE_MAX * 100;
   // printf("Task queue usage: %.1f%%\n", usage);
}





