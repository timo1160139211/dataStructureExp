/*
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, GaoYisheng  <gaoyisheng.site>
 * All rights reserved.
 * Distributed under GPL license.
 * ----------------------------------------------------------------------------
 */
#include <iostream>
#include <stdio.h>

//定义 树的结构体.
typedef struct TreeNode{
  int num;//记录子女的个数
  char name[20];//姓名
  char sex[3];//性别
  bool isMarried;//婚否, true false.

  struct TreeNode * nextNode[20];//记录这个人的儿女,[0] 号为配偶
  struct TreeNode * parent;//记录这个节点的父节点
}TreeNode;


/*一系列操作*/
void welcomeMorpheus();//欢迎界面
void showMenu();//显示菜单
TreeNode * createTree(TreeNode * tree);//创建树



int main() {
    /* 欢迎界面 */
    void welcomeMorpheus();
    void showMenu();

    char c;
    while(1)
    {
		    c = getchar();
		      switch(c)
		      {
			         case 'A':
				           printf("选择了A\n");
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
			         case 'F':
				           printf("选择了退出\n");
			                break;
		      }//switch

		  if(c == 'F')
			break;

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
  printf("     1 : 输入建立家谱信息\n");
  printf("     2 : 输出打印整个家谱信息\n");
  printf("     3 : 在家谱中查找某人\n");
  printf("     4 : 添加新的成员\n");
  printf("     5 : 修改某人的信息\n");
  printf("     9 : 退出系统\n");
  printf("\n\n");
}

//创建树
TreeNode * createTree(TreeNode * tree){
  TreeNode * t;



}
