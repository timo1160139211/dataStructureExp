/*
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, GaoYisheng  <gaoyisheng.site>
 * All rights reserved.
 * Distributed under GPL license.
 * ----------------------------------------------------------------------------
 */
#include <iostream>
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

//定义 树的结构体.
typedef struct treeNode{
    int num;//记录子女的个数
    char name[20];//姓名
    char sex;//性别 男 = m/M ,女 = f/F
    char isMarried;//婚否, y/Y  n/N  .

    struct treeNode * nextNode[20];//记录这个人的儿女,[0] 号为配偶
    //struct treeNode * parent;//记录这个节点的父节点====
    //后删,个人认为不需要这个指针.只需要修改判断语句即可   多一层指针 来查找
}treeNode,*treePoint;


/*一系列操作*/
void welcomeMorpheus();//欢迎界面
void showMenu();//显示菜单
void backMenu();//打印返回
 
treePoint createTree();//创建树,
void visit(treePoint tp);//遍历树 
treePoint search(treePoint tp,char s[]);//查找 
void add(treePoint tp,int type,char *s);//添加    依类型  1 嫁娶（），2 生育（） 


int main() {
    char c;
    char s[20];//查找串 名字‘ 
    treePoint st;//查找到的树 
    treePoint mainTree;//定义一个指向树的指针
    
	/* 欢迎界面 */
    welcomeMorpheus();
    while(1)
    {
        showMenu();//显示选择菜单
		    c = getchar();//进行选择跳转
		    switch(c)
		    {
			      case 'A':
				        printf("----------正在创建家谱树ing...----------\n");
				        
                		mainTree=createTree();//创建 树
						printf("----------创建家谱树完成! ^_^ ----------\n");
						backMenu();
			            break;
			            
			      case 'B':
				        printf("----------正在翻阅家谱ing...  ----------\n");
				        if(mainTree==NULL){printf("请先建立家谱");break;}//跳出swich 进入选择界面 
				        visit(mainTree);//遍历 
				        printf("----------  合上家谱   ^_^    ----------\n");
				        backMenu();
			            break;

			      case 'C':
				        printf("---------- 请输入查找姓名：   ----------\n");
				        //gets(s);
				        scanf("%s",s);
				        if(s==NULL){printf("查找姓名不能为空！");break;	}
				        
				        printf("----------正在翻阅家谱ing...  ----------\n");
				        st=search(mainTree,s); 
				        
				        if(st==NULL){
				        	printf("查询不到 %s 的信息  :-(  \n",s);
						}else{
							printf("查询成功！  :-)  \n");
							//打印该用户信息 	
						}
				        
				        backMenu();
			            break;


			      case 'D':
				        printf("-----选择添加类型  A : 嫁娶（添加配偶），B : 生育（添加子女）\n");
				        
				        
				        
				        
				        
				        printf("----------添加到家谱 完成！^_^ ----------\n");
				        backMenu();
			              break;


			      case 'E':
                		printf("选择了E\n");
			              break;


			      case 'Q':
				        printf("选择了退出\n");
			              //break;
                   		exit(0);//直接退出

		      }//switch
		  //if(c == 'Q') break;
	  }


    return 1;
}


//系统欢迎页面
void welcomeMorpheus(){
    printf("\n");
    printf("#################  Loading  ######################\n");
    printf("##                                              ##\n");
    printf("##                欢迎使用家谱系统              ##\n");
    printf("##                                              ##\n");
    printf("##                        designed by Morpheus  ##\n");
    printf("##################################################\n\n");

}

//显示选择菜单
void showMenu(){
	
    printf("\n");
    printf("----------#########  请选择操作  #########----------\n");
    printf("     A : 输入建立家谱信息\n");
    printf("     B : 输出打印整个家谱信息\n");
    printf("     C : 在家谱中查找某人\n");
    printf("     D : 添加新的成员\n");
    printf("     E : 修改某人的信息\n");
    printf("     Q : 退出系统\n");
    printf("\n\n");
}

//打印返回界面 
void backMenu(){
	printf("\n>>>>>返回选择界面>>>>>\n");
}

//创建树   先序创建
treePoint createTree(){
        treePoint tp;//创建一个 指向树的 指针
        tp=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存

        printf("\n请输入名字:\n");
        scanf("%s",tp->name);
			//printf("\n%s \n",tp->name);   debug
        printf("\n请输入 %s 的性别字母代号, 男 => m/M  |  女 => f/F : \n",tp->name);
		scanf("%s",&(tp->sex));
			//printf("\n%s \n",tp->sex);   DEBUG
        printf("请输入 %s 是否已婚: 已婚输入 y/Y, 未婚输入 n/N : \n",tp->name);
        scanf("%s",&(tp->isMarried));

        if(tp->isMarried == 'Y' ||tp->isMarried == 'y' ){//如果已婚
            printf("\n\n请输入 %s 的孩子个数(整数):\n",tp->name);
            scanf("%d",&(tp->num));

            /******系外 : 自动取消该节点的 nextNode[]指针数组 ,,,即不赋值 为 null***/
            /******配偶信息 自动 赋值 ******/
            tp->nextNode[0]=(treePoint)malloc(sizeof(treeNode));
            (tp->nextNode[0]->num)=(tp->num);//自动赋值 孩子个数
            (tp->nextNode[0]->isMarried)='Y';//自动赋值 已婚
            /***自动赋值 男 女  *****/
            if((tp->sex) == 'M' || (tp->sex) == 'm'){tp->nextNode[0]->sex = 'F';}
            else{tp->nextNode[0]->sex = 'M';}
            //取消 /*将其双亲节点指向配偶:*/
            //    (tp->nextNode[0]->parent) = tp;

            /*** 在此只需要输入 配偶的姓名即可 *****/
            //如果是男的，自动调整成输入 妻子 
            if((tp->sex) == 'M' || (tp->sex) == 'm'){
				printf("请输入 %s 的妻子的姓名:\n",tp->name);
			}else{
				printf("请输入 %s 的丈夫的姓名:\n",tp->name);
			}
			
            scanf("%s",tp->nextNode[0]->name);  printf("\n\n");

            /* 孩子信息赋值 :从1开始循环,空一个. && 双判定 保证数组不会越界*/
            for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
              printf("** 正在录入 %s 的第 %d 个孩子信息(共%d个):\n",tp->name,i,tp->num);
              tp->nextNode[i]= createTree();
            }
        }//else{
          //如果未婚,直接返回
          //return tp;
        //}
        return tp;
    }

//遍历     
void visit(treePoint tp){

		 printf(">>姓名：%s ，性别：",tp->name);
		 	if((tp->sex) == 'M' || (tp->sex) == 'm'){printf("男");}
			else{printf("女");}
		 printf(" ，婚否：");
		 	if((tp->isMarried) == 'n' || (tp->isMarried) == 'N'){printf("未婚\n");}
		 	else{printf("已婚\n");
		 		//已婚：
				//先打印输出  妻子/丈夫的信息： 
		 		if((tp->sex) == 'M' || (tp->sex) == 'm'){
					printf("\t%s 和妻子 %s 育有 %d 个子女:\n",tp->name,tp->nextNode[0]->name,tp->num);}
				else{
					printf("\t%s 和丈夫 %s 育有 %d 个子女:\n",tp->name,tp->nextNode[0]->name,tp->num);}
				
				
				//先打印所有孩子 姓名 
				for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
              		printf("\t\t第 %d 个孩子: %s \n ",tp->nextNode[i]->name);
            	}
            	
            	printf("\n");
            	//在分别遍历所有孩子子树：
				for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
              		
             		visit(tp->nextNode[i]);
            	} 
				
											 
			 }
		 	

} 

//查找
treePoint search(treePoint tp,char s[]){
	if(strcmp(tp->name,s)==0){
		 printf(">>姓名：%s ，性别：",tp->name);
		 	if((tp->sex) == 'M' || (tp->sex) == 'm'){printf("男");}
			else{printf("女");}
		 printf(" ，婚否：");
		 	if((tp->isMarried) == 'n' || (tp->isMarried) == 'N'){printf("未婚\n");}
		 	else{printf("已婚\n");
		 		//已婚：
				//先打印输出  妻子/丈夫的信息： 
		 		if((tp->sex) == 'M' || (tp->sex) == 'm'){
					printf("\t%s 和妻子 %s 育有 %d 个子女:\n",tp->name,tp->nextNode[0]->name,tp->num);}
				else{
					printf("\t%s 和丈夫 %s 育有 %d 个子女:\n",tp->name,tp->nextNode[0]->name,tp->num);}
				
				
				//先打印所有孩子 姓名 
				for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
              		printf("\t\t第 %d 个孩子: %s \n ",tp->nextNode[i]->name);
        
			return tp;
		}else{
			
				for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
              		
              		search(tp->nextNode[i],s);
             		
            	} 
			
			
			
			
			
			
			
			
			
			
			
			
		}
        
	}
	
	
	
	
			 printf(">>姓名：%s ，性别：",tp->name);
		 	if((tp->sex) == 'M' || (tp->sex) == 'm'){printf("男");}
			else{printf("女");}
		 printf(" ，婚否：");
		 	if((tp->isMarried) == 'n' || (tp->isMarried) == 'N'){printf("未婚\n");}
		 	else{printf("已婚\n");
		 		//已婚：
				//先打印输出  妻子/丈夫的信息： 
		 		if((tp->sex) == 'M' || (tp->sex) == 'm'){
					printf("\t%s 和妻子 %s 育有 %d 个子女:\n",tp->name,tp->nextNode[0]->name,tp->num);}
				else{
					printf("\t%s 和丈夫 %s 育有 %d 个子女:\n",tp->name,tp->nextNode[0]->name,tp->num);}
				
				
				//先打印所有孩子 姓名 
				for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
              		printf("\t\t第 %d 个孩子: %s \n ",tp->nextNode[i]->name);
            	}
            	
            	printf("\n");
            	//在分别遍历所有孩子子树：
				for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
              		
             		visit(tp->nextNode[i]);
            	} 
				
											 
			 }
		 	
	
	return NULL;
}

//添加    依类型  1 嫁娶（），2 生育（）
void add(){
	
	
}


//修改    xxx 修改个人信息 
void edit(treePoint tp,char *s){
	//search();
}

