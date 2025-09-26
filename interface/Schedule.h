#ifndef    _SCHEDULE_H
#define    _SCHEDULE_H
#include   "stm32f10x.h"
#include   <stdbool.h>

#define Init_Task   5
#define EVE_MAX 35        // 最大任务数量
#define NULL 0            // 空指针定义
#define INVALID_ID 0xFF   // 无效任务ID


typedef enum {
  NULL_ID_Task=0,
  RS485_Response_Data_Task,
  CAN_SendCellVoltages_Task,
// BQ769x2_ReadAllVoltages_Task,
  Period_Manage_Battery_Sta_Task,
// BQ769x2_ReadCurrent_Task,
  Read_BQ76952_Abnormal_Status_Task,
  Bq76952_Interrupt_processing_Task,
 	RS485_Stop_SendData_Task,
} Task_Name_Enum;



// 在scheduler.h中增加错误类型定义
typedef enum {
    TASK_ADD_SUCCESS = 0,     //添加成功
    TASK_ADD_QUEUE_FULL,      //队列已满无法添加
    TASK_ADD_INVALID_ARG,    //添加了无效的任务
    TASK_ADD_REPLACED_LOW_PRIO   //通过替换低优先级，非循环的任务
} TaskAddResult;


// 任务状态定义
typedef enum {
    TASK_READY,          // 任务就绪
    TASK_DELAYED,        // 任务等待延迟
    TASK_SUSPENDED,      // 任务挂起
    TASK_DELETED         // 任务已删除
} TaskState;

// 任务优先级定义
typedef enum {
	  Highest_Mode=0,   //在中断中执行！  //注意函数的互串
    PRIORITY_HIGH,   // 高优先级(数值越小优先级越高)
    PRIORITY_MEDIUM,
    PRIORITY_LOW,
    PRIORITY_COUNT
} TaskPriority;

// 任务结构体
typedef struct {
    void (*func)(void);  // 任务函数指针
    uint16_t delay;       // 延迟计数器(ms)
    TaskState state;      // 任务状态
    TaskPriority priority;// 任务优先级
    uint16_t period;      // 周期任务的时间间隔(0表示非周期任务)
    uint16_t time_cnt;    // 周期任务计时器
    uint8_t id;           // 任务ID
	  Task_Name_Enum  Task_Name_Index;   //任务引索序号
} t_EVENTION; 






// 调试信息结构体
typedef struct {
    uint8_t max_task_count;   // 历史最大任务数
    uint8_t current_tasks;    // 当前任务数
    uint16_t dispatch_count;  // 调度器运行计数
} SchedulerDebugInfo;


extern  t_EVENTION *EVE_queue[EVE_MAX];
extern  t_EVENTION Task_Gauge[Init_Task];

void EVE_Init(void); 

void EVE_update(void);

uint8_t EVE_add(t_EVENTION *eve);

bool EVE_del_by_id(uint8_t id);

bool EVE_del_by_ptr(t_EVENTION *eve);
	
bool EVE_Suspend_By_Ptr(t_EVENTION *task);


bool EVE_suspend(uint8_t id);

bool EVE_Resume_By_Ptr(t_EVENTION *task);

bool EVE_resume(uint8_t id);
	
void EVE_dispatch(void);

SchedulerDebugInfo EVE_get_debug_info(void);

void Monitor_Task(void);

void Print_Func_Name(void (*func_ptr)(void));

uint8_t Filter_task_number(Task_Name_Enum  Task_Index_A);


void Task_Wait_Trigger(uint8_t Time_Set,Task_Name_Enum Task_Name);
#endif
































