# 代码结构

```
.
├── CMakeLists.txt
├── inc
├── lilos_config.h
├── README.md
├── sample
└── src
```

# 配置config

```c
#define LILOS_MAX_TASK 32
#define LILOS_MAX_CALL_BACK 32

#define LILOS_MAX_SWTIMER_TASK 10

#define LILOS_MAX_QUEUE_NUM 10

#define LILOS_LOWPOWER_ON 0
#define LILOS_LOWPOWER_OFF 1
#define LILOS_LOWPOER_MODE LILOS_LOWPOWER_OFF

//#define LILOS_NO_INIT_CALL
//#define BUILD_DEBUG
```

## LILOS_NO_INIT_CALL

对应init call的开关

如果使用init call需要在对应的LD文件中增加

以下以RSIC-V的LD文件为例

```
	.initcalls :
	{
		. = ALIGN(8);
		__initcall_start = .;
		KEEP(*(initcall0init))
		KEEP(*(initcall1init))
		KEEP(*(initcall2init))
		__initcall_end = .;
		. = ALIGN(8);
	} >FLASH
```

## BUILD_DEBUG

对应的是打印级别默认打印只打印ERR log以上的级别

配置了BUILD_DEBUG可以打印对应DEBUG级别以上的log

# 使用方式

通用步骤为包含头文件

```c
#include "lilos_init.h"
```

把时钟放入滴答定时器

滴答定时器需要设置一个1ms的滴答定时器

lilos的时钟基于1ms的定时器

```c
lil_os_systick();
```

启动入口

```c
lilos_Start();
```

详情见sample
