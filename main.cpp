/*
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, GaoYisheng  <gaoyisheng.site>
 * All rights reserved.
 * Distributed under GPL license.
 * ----------------------------------------------------------------------------
 */
#include <iostream>
#include <stdio.h>
#include <string.h>

//定义 树的结构体.
typedef struct treeNode{
    int num;//记录子女的个数
    char name[20];//姓名
    char sex[2];//性别
    char isMarried;//婚否, y/Y  n/N  .

    struct treeNode * nextNode[20];//记录这个人的儿女,[0] 号为配偶
    //struct treeNode * parent;//记录这个节点的父节点====
    //后删,个人认为不需要这个指针.只需要修改判断语句即可   多一层指针 来查找
}treeNode,*treePoint;


/*一系列操作*/
void welcomeMorpheus();//欢迎界面
void showMenu();//显示菜单
treePoint createTree();//创建树,



int main() {
    char c;
    treePoint mainTree;//定义一个指向树的指针



    void welcomeMorpheus();/* 欢迎界面 */
    while(1)
    {
        showMenu();//显示选择菜单
		    c = getchar();//进行选择跳转
		    switch(c)
		    {
			      case 'A':
				        printf("选择了A : 正在创建家谱树ing...\n");
                mainTree=createTree(0);//创建 树

			              break;
			      case 'B':
				        printf("选择了B\n");
			              break;


			      case 'C':
				        printf("选择了C\n");
			              break;


			      case 'D':
				        printf("选择了D\n");
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
    printf("##                欢迎使用家谱系统                ##\n");
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

//创建树   先序创建
treePoint createTree(){
        treePoint tp;//创建一个 指向树的 指针

        printf("\n请输入名字:\n");
        scanf("%s",tp->name);

        tp=(treePoint)malloc(sizeof(treeNode));//申请一棵树的内存

        //strcpy(tp->name,ch);//名字赋值
        printf("\n请输入性别, '男' '女' \n");
        scanf("%s",tp->sex);
        printf("请输入Ta是否已婚: 已婚输入 y/Y, 未婚输入 n/N : \n");
        scanf("%c",&(tp->isMarried));

        if(tp->isMarried == 'Y' ||tp->isMarried == 'y' ){//如果已婚
            printf("\n\n请输入Ta的孩子个数(整数):\n");
            scanf("%d",&(tp->num));

            /******系外 : 自动取消该节点的 nextNode[]指针数组 ,,,即不赋值 为 null***/
            /******配偶信息 自动 赋值 ******/
            tp->nextNode[0]=(treePoint)malloc(sizeof(treeNode));
            (tp->nextNode[0]->num)=(tp->num);//自动赋值 孩子个数
            (tp->nextNode[0]->isMarried)='Y';//自动赋值 已婚
            /***自动赋值 男 女  *****/
            if((tp->sex) == '男'){strcpy(tp->nextNode[0]->sex,'女');}
            else{strcpy(tp->nextNode[0]->sex,'男');}
            //取消 /*将其双亲节点指向配偶:*/
            //    (tp->nextNode[0]->parent) = tp;

            /*** 在此只需要输入 配偶的姓名即可 *****/
            printf("请输入配偶姓名:\n");
            scanf("%s",tp->nextNode[0]->name);  printf("\n\n");

            /* 孩子信息赋值 :从1开始循环,空一个. && 双判定 保证数组不会越界*/
            for(int i=1;i<=(tp->num)&&i<10;i++){//因为num个孩子,又空出一个给配偶,所以<=
              printf("** 正在录入第 %d 个孩子信息:\n",i);
              tp->nextNode[i]= createTree();
            }
        }//else{
          //如果未婚,直接返回
          //return tp;
        //}
    }
    return tp;
}
