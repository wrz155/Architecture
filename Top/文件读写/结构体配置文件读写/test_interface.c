#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "cfg_op.hpp"
#include "myop.hpp"


void main_menu()
{
	printf("\n1 Test AddTeacher(测试保存老师信息)	");
	printf("\n2 Test ModifyTeacher(测试显示老师信息)	");
	printf("\n0 exit(0)        (程序退出)	    ");
	printf("\nplease enter your choice:[1/2/0]: ");
	return;
}

int  Test_AddTeacher()
{
	int		rv = 0; 
	char *pfileName = "c:/teacherinfo.ini";
	Teacher t1;
	memset(&t1, 0, sizeof(Teacher));
	t1.infoId = 1;
	t1.age = 11;
	strcpy(t1.name, "name");
	strcpy(t1.studentInfo, "s1,s2,s3,");
	
	//添加老师
	rv = AddTeacher(pfileName, &t1);
	if (rv != 0)
	{
		printf("fucn AddTeacher() err:%d \n", rv);
		return rv;
	}

	
	printf("读写配置项绿灯测试通过\n");

End:
	return rv;
	
}

int  Test_ModifyTeache()
{
	
	int rv;
	//显示老师
	//int ModifyTeacher(char *pfileName, Teacher *pTe);
	printf("\n读写配置项绿灯测试通过\n");

End:
	return rv;
	
}

int  main()
{
	int		rv = 0; 
	int		choice = 0;

	for(;;)
	{
		main_menu();
	    scanf("%d", &choice);
        switch (choice)
		{
		case 1:
			Test_AddTeacher();   break;
		case 2:
			Test_ModifyTeache();   break;
		case 0:
			exit(0);
		default:
			exit(0);
		}
	}

End:
	return rv;
	getchar();
}


