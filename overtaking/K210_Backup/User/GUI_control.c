#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "OLED.h"
#include "GUI_control.h"
#define canshu_num 3
 uint32_t *p1,*p2,*p3;
 uint32_t *i1,*i2,*i3;
 uint32_t *d1,*d2,*d3;
 

 uint32_t P1,P2,P3;
 uint32_t I1,I2,I3;
 uint32_t D1,D2,D3;
 uint8_t mod=1;
 uint8_t page=1;

 uint8_t  topic_num;

//#define KEY_add 1 //+
//#define KEY_sub 2 //- 
//#define KEY_mod 3 //mod
//#define KEY_ok  4 //ok
//#define KEY_x10 5// 切换倍数

void GUI_control_PID()
{
	
	
if(KEY_Scan(1)==5)
{
	page ++;
	
	if(page >3)
		{
			
			page =page%3;
		}
		
}
/********************************************************
                第一组PID参数
********************************************************/
if(page==1)
{
	
	
	OLED_ShowChar(112,3,'1',16,1);//1608字体
	
	if(KEY_Scan(1)==3)
	{
		mod++;
		if(mod>canshu_num)
		{
			
			mod=mod%canshu_num;
		}
		
		
	}

   

//*****************************
  if(mod==1)//调节第一个参数p
{
	OLED_ShowChar(48,0,'<',16,1);//1608字体
	OLED_clearare(48,16,56,32);
	OLED_clearare(48,32,56,48);
	if(KEY_Scan(1)==1)
	{
		P1++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*50);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*50,P1);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	 else if(KEY_Scan(1)==2)
	{
		P1--;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*50);//   已用地址0x800 0000+已用flash  C8T6 1KB每页 RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*50,P1);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}

}
////****************************
  else if(mod==2)//调节第二个参数i
{
	 OLED_clearare(48,0,56,16);
	 OLED_ShowChar(48,16,'<',16,1);//1608字体
	 OLED_clearare(48,32,56,48);
	if(KEY_Scan(1)==1)
	{
		I1++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*51);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*51,I1);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	else if(KEY_Scan(1)==2)
	{
		I1--;
		FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*51);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*51,I1);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	 

} 

//****************************
  else if(mod==3)//调节第二个参数d
{
	 OLED_clearare(48,0,56,16);
	 OLED_clearare(48,16,56,32);
   OLED_ShowChar(48,32,'<',16,1);//1608字体
	
	if(KEY_Scan(1)==1)
	{
		 D1++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*52);//   已用地址0x800 0000+已用flash  C8T6 1KB每页 RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*52,D1);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	else if(KEY_Scan(1)==2)
	{
		D1--;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*52);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*52,D1);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	
}
//*****************************
  OLED_ShowChar(1,0,'P',16,1);//1608字体
	OLED_ShowChar(1,16,'I',16,1);//1608字体
  OLED_ShowChar(1,32,'D',16,1);//1608字体
  OLED_ShowNum(9,0,*p1,4,16,1);
  OLED_ShowNum(9,16,*i1,4,16,1);
  OLED_ShowNum(9,32,*d1,4,16,1);
//	OLED_Refresh();
//****************************
	}

/********************************************************
                	第二组PID参数
*********************************************************/
	
else if(page==2)
{
	 
	OLED_ShowChar(112,3,'2',16,1);//1608字体
	
	if(KEY_Scan(1)==3)
	{
		mod++;
		if(mod>canshu_num)
		{
			
			mod=mod%canshu_num;
		}
		
		
	}

   

//*****************************
  if(mod==1)//调节第一个参数p
{
	OLED_ShowChar(48,0,'<',16,1);//1608字体
	OLED_clearare(48,16,56,32);
	OLED_clearare(48,32,56,48);
	if(KEY_Scan(1)==1)
	{
		P2++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*53);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*53,P2);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	 else if(KEY_Scan(1)==2)
	{
		P2--;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*53);//   已用地址0x800 0000+已用flash  C8T6 1KB每页 RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*53,P2);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}

}
////****************************
  else if(mod==2)//调节第二个参数i
{
	 OLED_clearare(48,0,56,16);
	 OLED_ShowChar(48,16,'<',16,1);//1608字体
	 OLED_clearare(48,32,56,48);
	if(KEY_Scan(1)==1)
	{
		I2++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*54);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*54,I1);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	else if(KEY_Scan(1)==2)
	{
		I2--;
		FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*54);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*54,I1);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	 

} 

//****************************
  else if(mod==3)//调节第二个参数d
{
	 OLED_clearare(48,0,56,16);
	 OLED_clearare(48,16,56,32);
   OLED_ShowChar(48,32,'<',16,1);//1608字体
	
	if(KEY_Scan(1)==1)
	{
		 D2++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*55);//   已用地址0x800 0000+已用flash  C8T6 1KB每页 RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*55,D2);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	else if(KEY_Scan(1)==2)
	{
		D2--;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*55);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*55,D2);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	
}
//*****************************
  OLED_ShowChar(1,0,'P',16,1);//1608字体
	OLED_ShowChar(1,16,'I',16,1);//1608字体
  OLED_ShowChar(1,32,'D',16,1);//1608字体
  OLED_ShowNum(9,0,*p2,4,16,1);
  OLED_ShowNum(9,16,*i2,4,16,1);
  OLED_ShowNum(9,32,*d2,4,16,1);
//	OLED_Refresh();
//****************************
	}
	
/****************************************************************
                    第三组PID参数
******************************************************************/	
	if(page==3)
{
	OLED_ShowChar(112,3,'3',16,1);//1608字体
	
	if(KEY_Scan(1)==3)
	{
		mod++;
		if(mod>canshu_num)
		{
			
			mod=mod%canshu_num;
		}
		
		
	}

   

//*****************************
  if(mod==1)//调节第一个参数p
{
	OLED_ShowChar(48,0,'<',16,1);//1608字体
	OLED_clearare(48,16,56,32);
	OLED_clearare(48,32,56,48);
	if(KEY_Scan(1)==1)
	{
		P3++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*56);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*56,P3);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	 else if(KEY_Scan(1)==2)
	{
		P3--;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*56);//   已用地址0x800 0000+已用flash  C8T6 1KB每页 RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*56,P3);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}

}
////****************************
  else if(mod==2)//调节第二个参数i
{
	 OLED_clearare(48,0,56,16);
	 OLED_ShowChar(48,16,'<',16,1);//1608字体
	 OLED_clearare(48,32,56,48);
	if(KEY_Scan(1)==1)
	{
		I3++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*57);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*57,I3);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	else if(KEY_Scan(1)==2)
	{
		I3--;
		FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*57);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*57,I3);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	 

} 

//****************************
  else if(mod==3)//调节第二个参数d
{
	 OLED_clearare(48,0,56,16);
	 OLED_clearare(48,16,56,32);
   OLED_ShowChar(48,32,'<',16,1);//1608字体
	
	if(KEY_Scan(1)==1)
	{
		 D3++;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*58);//   已用地址0x800 0000+已用flash  C8T6 1KB每页 RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*58,D3);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	else if(KEY_Scan(1)==2)
	{
		D3--;
	 FLASH_Unlock();// 解锁flash
	 FLASH_ErasePage(0x08000000+1*1024*58);//   已用地址0x800 0000+已用flash  C8T6 1KB每页  RCT6 2KB每页
	 FLASH_ProgramWord(0x08000000+1*1024*58,D3);//写入一个32位数据
	 FLASH_Lock();//flash上锁 
	}
	
	
}
//*****************************
  OLED_ShowChar(1,0,'P',16,1);//1608字体
	OLED_ShowChar(1,16,'I',16,1);//1608字体
  OLED_ShowChar(1,32,'D',16,1);//1608字体
  OLED_ShowNum(9,0,*p3,4,16,1);
  OLED_ShowNum(9,16,*i3,4,16,1);
  OLED_ShowNum(9,32,*d3,4,16,1);
//	OLED_Refresh();
//****************************
	}
	
	
	
	
	
	
}


void topic_select(void)
{
	
	static  uint8_t mod=1;
	
	if(KEY_Scan(1)==3)
	{
		mod++;
		if(mod>canshu_num)
		{
			
			mod=mod%canshu_num;
		}
			
	}
if(mod ==1)
	{ 
	OLED_printf(1,1,"%s","Toptic1");
	topic_num =1;	
  }		
	
	else if(mod ==2)
	{
  
	OLED_printf(1,1,"%s","Toptic2");
	topic_num =2;	
  }		
	
	else if(mod ==3)
	{
	OLED_printf(1,1,"%s","Toptic3");
	topic_num =3;	
  }		
	
	
	
}







