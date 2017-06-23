/**
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
void printPerson(treePoint tp,int type);//打印这个人的信息

treePoint createTree();//创建树,
void visit(treePoint tp);//遍历树
treePoint search(treePoint tp,char s[]);//查找
void add(treePoint tp);//添加    依类型  1 嫁娶（），2 生育（）
void edit(treePoint mt);//修改姓名 


//全局变量
int type=-2;//用来区分查找的是不是  根结点-1  、 嫁娶的系外 配偶  0  、第几个孩子 就是几
int count=0;

int main() {
    char c;

    char s[20];//查找串 名字‘
    treePoint st;//查找到的树
    treePoint mainTree=NULL;//定义一个指向树的指针

	/* 欢迎界面 */
    welcomeMorpheus();
    while(1)
    {
        showMenu();//显示选择菜单
		    c = getchar();//进行选择跳转
		    switch(c)
		    {
		    	  case 'a':
			      case 'A':
				        printf("\n----------正在创建家谱树ing...----------\n\n");

                		mainTree=createTree();//创建 树
						printf("\n\n----------创建家谱树完成! ^_^ ----------\n\n\n");
						backMenu();
			            break;
				  case 'b':
			      case 'B':
				        printf("\n----------正在翻阅家谱ing...  ----------\n\n");
				        if(mainTree==NULL){printf("! 家谱为空,请先建立家谱\n\n");break;}//跳出swich 进入选择界面
				        visit(mainTree);//遍历
				        printf("\n----------  合上家谱   ^_^    ----------\n\n\n");
				        backMenu();
			            break;

				  case 'c':
			      case 'C':
			      		//判空
				        if(mainTree==NULL){printf("! 家谱为空,请先建立家谱\n\n");break;}//跳出swich 进入选择界面

				        printf("---------- 请输入查找姓名：   ----------\n\n");
				        //gets(s);
				        scanf("%s",s);
				        if(s==NULL){printf("查找姓名不能为空！");break;	}

				        printf("----------正在翻阅家谱ing...  ----------\n\n\n");
				        st=search(mainTree,s);



				        backMenu();
			            break;

				  case 'd':
			      case 'D':
				        

						add(mainTree);

				        printf("----------添加到家谱 完成！^_^ ----------\n");
				        backMenu();
			              break;

				  case 'e':
			      case 'E':
			      		edit(mainTree);
                		backMenu();
			            break;

				  case 'q':
			      case 'Q':
				        printf("选择了退出\n");
			              //break;
                   		exit(0);//直接退出

		      }//switch
		  //if(c == 'Q') break;
		  getchar();
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
    printf("   Aa : 输入建立家谱信息\n");
    printf("   Bb : 输出打印整个家谱信息\n");
    printf("   Cc : 在家谱中查找某人\n");
    printf("   Dd : 添加新的成员\n");
    printf("   Ee : 修改某人的信息\n");
    printf("   Qq : 退出系统\n");
    printf("\n\n");
}

//打印返回界面
void backMenu(){
	printf("\n>>>>>返回选择界面>>>>>\n\n\n");
}

//打印这个人的信息  //根据type ，分别打印
void printPerson(treePoint tp){

			if(type<-2&&type>20) return;
	   		if(type==-1){
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
              			printf("\t\t第 %d 个孩子: %s \n ",i,tp->nextNode[i]->name);
       				}//for

	   			}
	   		}//  type=-1

			if(type==0){//配偶 
	   	  	    printf(">>姓名：%s ，性别：",tp->nextNode[0]->name);
                    if((tp->nextNode[0]->sex) == 'M' || (tp->nextNode[0]->sex) == 'm'){printf("男");}
                    else{printf("女");}
                printf(" , 已婚     (非本系)\n");

                    if((tp->nextNode[0]->sex) == 'M' || (tp->nextNode[0]->sex) == 'm'){
                        printf("\t%s 是 %s 的丈夫.\n",tp->nextNode[0]->name,tp->name);}
                    else{
                        printf("\t%s 是 %s 的妻子.\n",tp->nextNode[0]->name,tp->name);
                	    }


                    if((tp->nextNode[0]->sex) == 'M' || (tp->nextNode[0]->sex) == 'm'){
                        printf("\t%s 和妻子 %s 育有 %d 个子女:\n",tp->nextNode[0]->name,tp->name,tp->nextNode[0]->num);}
                    else{
                        printf("\t%s 和丈夫 %s 育有 %d 个子女:\n",tp->nextNode[0]->name,tp->name,tp->nextNode[0]->num);
                        }

                    //先打印所有孩子 姓名
                    for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
                        printf("\t\t第 %d 个孩子: %s \n ",i,tp->nextNode[i]->name);
                    }

	   	  		}



	      	if(type>=1){
	      					printf(">>姓名：%s ，性别：",tp->nextNode[type]->name);
		 						if((tp->nextNode[type]->sex) == 'M' || (tp->nextNode[type]->sex) == 'm'){printf("男");}
								else{printf("女");}
									printf(" ，婚否：");
		 						if((tp->nextNode[type]->isMarried) == 'n' || (tp->nextNode[type]->isMarried) == 'N'){printf("未婚\n");}
		 						else{printf("已婚\n");
		 							//已婚：
									//先打印输出  妻子/丈夫的信息：
		 							if((tp->nextNode[type]->sex) == 'M' || (tp->nextNode[type]->sex) == 'm'){
										printf("\t%s 和妻子 %s 育有 %d 个子女:\n",tp->nextNode[type]->name,tp->nextNode[type]->nextNode[0]->name,tp->nextNode[type]->num);}
									else{
										printf("\t%s 和丈夫 %s 育有 %d 个子女:\n",tp->nextNode[type]->name,tp->nextNode[type]->nextNode[0]->name,tp->nextNode[type]->num);}

									//先打印所有孩子 姓名
									for(int k=1;k<=(tp->nextNode[type]->num)&&k<20;k++){//因为num个孩子,又空出一个给配偶,所以<=
              							printf("\t\t第 %d 个孩子: %s \n ",k,tp->nextNode[type]->nextNode[k]->name);
       								}//for
       							}
	      	}//if(type>0)
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
        }else{tp->num=0;}
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
              		printf("\t\t第 %d 个孩子: %s \n ",i,tp->nextNode[i]->name);
            	}

            	printf("\n");
            	//在分别遍历所有孩子子树：
				for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
             		visit(tp->nextNode[i]);
            	}

			 }


}

//查找 //返回的是 其 父指针
treePoint search(treePoint tp,char s[]){
	
	if(strcmp(tp->name,s)==0&&count==0){//只对 根节点有效
			type=-1;//根结点
			printPerson(tp);//根据type
			count++;
			return tp;//找到后返回这个指针

	}else{// strcmp(tp->name,s)!=0 如果名字不相等,继续递归查找
        if(strcmp(tp->nextNode[0]->name,s)==0){//如果是配偶的名字
                    //
            type=0;//配偶
			printPerson(tp);

            return tp;//返回其 父结点 指针   配合type 使用
        }else{		
        			type=-2;//用前复位 
                    for(int i=1;i<=(tp->num)&&i<20;i++){//因为num个孩子,又空出一个给配偶,所以<=
                        if(strcmp(tp->nextNode[i]->name,s)==0){
                        	type=i;//第几个孩子 就是几

                        	printPerson(tp);

                           	return tp;//返回其 父结点 指针   配合type 使用
                            break;//找到,退出循环。

                        }else{
                            search(tp->nextNode[i],s);
                            return NULL; 
                            }//ifelse
                    }//for
                }//if
		}
	return NULL;
}

//添加    依类型  1 嫁娶（），2 生育（）
void add(treePoint mt){
	int t=0;
	char s[20];
	treePoint tpp;
	tpp=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存
	
	printf("-----选择添加类型  1 : 嫁娶（添加配偶），2 : 生育（添加子女）\n");
	//printf("\n请输入类型：1 -> 嫁娶、 2 -> 生育。\n");
	scanf("%d",&t);

	//嫁娶
	if(t==1){//一定是 家谱里的  某个孩子  (或者根)，才会嫁娶 (不可能是某人的配偶)
        printf("---------- 请输入 家谱中要结婚的人的姓名：   ----------\n\n");
        scanf("%s",s);

		type=-2;//type先复原
		tpp=search(mt,s);//类型存到了 int type 中了:  -1 root    正数 n 为第 n 个孩子
		
			//如果是根
			if(type==-1){
                //先把该用户isMarried 置为 Y  已婚.
                tpp->isMarried = 'Y';
                tpp->num = 0;
				//如果是男的，要娶谁
				if(tpp->sex=='M'||tpp->sex=='m'){


					printf("---------- 请输入 %s 妻子的资料 ：   ----------\n\n",tpp->name);
					tpp->nextNode[0]=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存

                    printf("\n请输入名字:\n");
                    scanf("%s",tpp->nextNode[0]->name);

                    (tpp->nextNode[0]->sex) = 'F';
                    (tpp->nextNode[0]->num) = (tpp->num);//自动赋值 孩子个数
                    (tpp->nextNode[0]->isMarried) = 'Y';//自动赋值 已婚
                    printf("\n添加完成! ^_^  \n");

				}else{
					printf("---------- 请输入 %s 丈夫的资料 ：   ----------\n\n",tpp->name);
					tpp->nextNode[0]=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存
					
					
                    printf("\n请输入名字:\n");
                    scanf("%s",tpp->nextNode[0]->name);

                    (tpp->nextNode[0]->sex) = 'M';
                    (tpp->nextNode[0]->num) = (tpp->num);//自动赋值 孩子个数
                    (tpp->nextNode[0]->isMarried) = 'Y';//自动赋值 已婚

				}
                }
			//如果不是根
			if(type>0){
                //先把该用户isMarried 置为 Y  已婚.
                tpp->nextNode[type]->isMarried = 'Y';
                tpp->nextNode[type]->num = 0;
				//如果是男的，要娶谁
				if(tpp->nextNode[type]->sex=='M'||tpp->nextNode[type]->sex=='m'){
				
				
					
                    printf("---------- 请输入 %s 妻子的资料 ：   ----------\n\n",tpp->nextNode[type]->name);
					tpp->nextNode[type]->nextNode[0]=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存

                    printf("\n请输入名字:\n");
                    scanf("%s",tpp->nextNode[type]->nextNode[0]->name);

                    (tpp->nextNode[type]->nextNode[0]->sex) = 'F';
                    (tpp->nextNode[type]->nextNode[0]->num) = (tpp->nextNode[type]->num);//自动赋值 孩子个数
                    (tpp->nextNode[type]->nextNode[0]->isMarried) = 'Y';//自动赋值 已婚
                    printf("\n添加完成! ^_^  \n");

				}else{
					printf("---------- 请输入 %s 丈夫的资料 ：   ----------\n\n",tpp->nextNode[type]->name);

					tpp->nextNode[type]->nextNode[0]=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存

                    printf("\n请输入名字:\n");
                    scanf("%s",tpp->nextNode[type]->nextNode[0]->name);

                    (tpp->nextNode[type]->nextNode[0]->sex) = 'F';
                    (tpp->nextNode[type]->nextNode[0]->num) = (tpp->nextNode[type]->num);//自动赋值 孩子个数
                    (tpp->nextNode[type]->nextNode[0]->isMarried) = 'Y';//自动赋值 已婚
                    printf("\n添加完成! ^_^  \n");

				}
			}
	}

	//生育
	if(t==2){
        printf("\n----------  请输入谁家添丁 (本系)----------\n\n");
        scanf("%s",s);

		type=-2;//type先复原
		tpp=search(mt,s);//类型存到了 int type 中了:  -1 root    正数 n 为第 n 个孩子

        //如果是根
        if(type==-1){
            tpp->nextNode[tpp->num+1]=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存

            printf("\n==>正在录入%s家 新生儿信息:\n",tpp->nextNode[(tpp->num)+1]->name);
            printf("\n请输入新生儿 名字:\n");
            scanf("%s",tpp->nextNode[(tpp->num)+1]->name);
			//printf("\n%s \n",tp->name);   debug
            printf("\n请输入 %s 的性别字母代号, 男 => m/M  |  女 => f/F : \n",tpp->nextNode[(tpp->num)+1]->name);
            scanf("%s",&(tpp->nextNode[(tpp->num)+1]->sex));
            //自动赋值
            tpp->nextNode[(tpp->num)+1]->num=0;
            tpp->nextNode[(tpp->num)+1]->isMarried='N';
            
            //孩子数 +1
			tpp->num++; 
			printf("\n新生儿 %s 添加完成! ^_^  \n",tpp->nextNode[(tpp->num)]->name);
        }
        if(type>0){
            tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存

            printf("\n==>正在录入%s家 新生儿信息:\n",tpp->nextNode[type]->name);
            printf("\n请输入新生儿 名字:\n");
            scanf("%s",tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->name);
            
		
            printf("\n请输入 %s 的性别字母代号, 男 => m/M  |  女 => f/F : \n",tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->name);
            scanf("%s",&(tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->sex));
            //自动赋值
            tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->num=0;
            tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->isMarried='N';
            
            //孩子数 +1
			tpp->nextNode[type]->num++; 
			
			printf("\n新生儿 %s 添加完成! ^_^  \n",tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)]->name);
        }
	}

}

//修改    xxx 修改个人信息
void edit(treePoint mt){
        char s[20];
        treePoint tpp;

        printf("---------- 请输入 要修改的人的姓名：   ----------\n\n");
        scanf("%s",s);

		tpp=search(mt,s);//类型存到了 int type 中了:  -1 root    正数 n 为第 n 个孩子
			//如果是根
			if(type==-1){
                printf("请输入新名字：");
                scanf("%s",tpp->name);

                printf("\n修改完成! ^_^  \n");
                }
			//如果不是根
			if(type>0){
                printf("请输入新名字：");
                scanf("%s",tpp->nextNode[type]->name);

                printf("\n修改完成! ^_^  \n");
				}
}

