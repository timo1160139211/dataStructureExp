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

//���� ���Ľṹ��.
typedef struct treeNode{
    int num;//��¼��Ů�ĸ���
    char name[20];//����
    char sex;//�Ա� �� = m/M ,Ů = f/F
    char isMarried;//���, y/Y  n/N  .

    struct treeNode * nextNode[20];//��¼����˵Ķ�Ů,[0] ��Ϊ��ż
    //struct treeNode * parent;//��¼����ڵ�ĸ��ڵ�====
    //��ɾ,������Ϊ����Ҫ���ָ��.ֻ��Ҫ�޸��ж���伴��   ��һ��ָ�� ������
}treeNode,*treePoint;


/*һϵ�в���*/
void welcomeMorpheus();//��ӭ����
void showMenu();//��ʾ�˵�
void backMenu();//��ӡ����
void printPerson(treePoint tp,int type);//��ӡ����˵���Ϣ

treePoint createTree();//������,
void visit(treePoint tp);//������
treePoint search(treePoint tp,char s[]);//����
void add(treePoint tp);//���    ������  1 ��Ȣ������2 ��������
void edit(treePoint mt);//�޸����� 


//ȫ�ֱ���
int type=-2;//�������ֲ��ҵ��ǲ���  �����-1  �� ��Ȣ��ϵ�� ��ż  0  ���ڼ������� ���Ǽ�
int count=0;

int main() {
    char c;

    char s[20];//���Ҵ� ���֡�
    treePoint st;//���ҵ�����
    treePoint mainTree=NULL;//����һ��ָ������ָ��

	/* ��ӭ���� */
    welcomeMorpheus();
    while(1)
    {
        showMenu();//��ʾѡ��˵�
		    c = getchar();//����ѡ����ת
		    switch(c)
		    {
		    	  case 'a':
			      case 'A':
				        printf("\n----------���ڴ���������ing...----------\n\n");

                		mainTree=createTree();//���� ��
						printf("\n\n----------�������������! ^_^ ----------\n\n\n");
						backMenu();
			            break;
				  case 'b':
			      case 'B':
				        printf("\n----------���ڷ��ļ���ing...  ----------\n\n");
				        if(mainTree==NULL){printf("! ����Ϊ��,���Ƚ�������\n\n");break;}//����swich ����ѡ�����
				        visit(mainTree);//����
				        printf("\n----------  ���ϼ���   ^_^    ----------\n\n\n");
				        backMenu();
			            break;

				  case 'c':
			      case 'C':
			      		//�п�
				        if(mainTree==NULL){printf("! ����Ϊ��,���Ƚ�������\n\n");break;}//����swich ����ѡ�����

				        printf("---------- ���������������   ----------\n\n");
				        //gets(s);
				        scanf("%s",s);
				        if(s==NULL){printf("������������Ϊ�գ�");break;	}

				        printf("----------���ڷ��ļ���ing...  ----------\n\n\n");
				        st=search(mainTree,s);



				        backMenu();
			            break;

				  case 'd':
			      case 'D':
				        

						add(mainTree);

				        printf("----------��ӵ����� ��ɣ�^_^ ----------\n");
				        backMenu();
			              break;

				  case 'e':
			      case 'E':
			      		edit(mainTree);
                		backMenu();
			            break;

				  case 'q':
			      case 'Q':
				        printf("ѡ�����˳�\n");
			              //break;
                   		exit(0);//ֱ���˳�

		      }//switch
		  //if(c == 'Q') break;
		  getchar();
	  }


    return 1;
}


//ϵͳ��ӭҳ��
void welcomeMorpheus(){
    printf("\n");
    printf("#################  Loading  ######################\n");
    printf("##                                              ##\n");
    printf("##                ��ӭʹ�ü���ϵͳ              ##\n");
    printf("##                                              ##\n");
    printf("##                        designed by Morpheus  ##\n");
    printf("##################################################\n\n");

}

//��ʾѡ��˵�
void showMenu(){

    printf("\n");
    printf("----------#########  ��ѡ�����  #########----------\n");
    printf("   Aa : ���뽨��������Ϣ\n");
    printf("   Bb : �����ӡ����������Ϣ\n");
    printf("   Cc : �ڼ����в���ĳ��\n");
    printf("   Dd : ����µĳ�Ա\n");
    printf("   Ee : �޸�ĳ�˵���Ϣ\n");
    printf("   Qq : �˳�ϵͳ\n");
    printf("\n\n");
}

//��ӡ���ؽ���
void backMenu(){
	printf("\n>>>>>����ѡ�����>>>>>\n\n\n");
}

//��ӡ����˵���Ϣ  //����type ���ֱ��ӡ
void printPerson(treePoint tp){

			if(type<-2&&type>20) return;
	   		if(type==-1){
	   	  		printf(">>������%s ���Ա�",tp->name);
		 		if((tp->sex) == 'M' || (tp->sex) == 'm'){printf("��");}
				else{printf("Ů");}
					printf(" �����");
		 		if((tp->isMarried) == 'n' || (tp->isMarried) == 'N'){printf("δ��\n");}
		 		else{printf("�ѻ�\n");
		 			//�ѻ飺
					//�ȴ�ӡ���  ����/�ɷ����Ϣ��
		 			if((tp->sex) == 'M' || (tp->sex) == 'm'){
						printf("\t%s ������ %s ���� %d ����Ů:\n",tp->name,tp->nextNode[0]->name,tp->num);}
					else{
						printf("\t%s ���ɷ� %s ���� %d ����Ů:\n",tp->name,tp->nextNode[0]->name,tp->num);}

					//�ȴ�ӡ���к��� ����
					for(int i=1;i<=(tp->num)&&i<20;i++){//��Ϊnum������,�ֿճ�һ������ż,����<=
              			printf("\t\t�� %d ������: %s \n ",i,tp->nextNode[i]->name);
       				}//for

	   			}
	   		}//  type=-1

			if(type==0){//��ż 
	   	  	    printf(">>������%s ���Ա�",tp->nextNode[0]->name);
                    if((tp->nextNode[0]->sex) == 'M' || (tp->nextNode[0]->sex) == 'm'){printf("��");}
                    else{printf("Ů");}
                printf(" , �ѻ�     (�Ǳ�ϵ)\n");

                    if((tp->nextNode[0]->sex) == 'M' || (tp->nextNode[0]->sex) == 'm'){
                        printf("\t%s �� %s ���ɷ�.\n",tp->nextNode[0]->name,tp->name);}
                    else{
                        printf("\t%s �� %s ������.\n",tp->nextNode[0]->name,tp->name);
                	    }


                    if((tp->nextNode[0]->sex) == 'M' || (tp->nextNode[0]->sex) == 'm'){
                        printf("\t%s ������ %s ���� %d ����Ů:\n",tp->nextNode[0]->name,tp->name,tp->nextNode[0]->num);}
                    else{
                        printf("\t%s ���ɷ� %s ���� %d ����Ů:\n",tp->nextNode[0]->name,tp->name,tp->nextNode[0]->num);
                        }

                    //�ȴ�ӡ���к��� ����
                    for(int i=1;i<=(tp->num)&&i<20;i++){//��Ϊnum������,�ֿճ�һ������ż,����<=
                        printf("\t\t�� %d ������: %s \n ",i,tp->nextNode[i]->name);
                    }

	   	  		}



	      	if(type>=1){
	      					printf(">>������%s ���Ա�",tp->nextNode[type]->name);
		 						if((tp->nextNode[type]->sex) == 'M' || (tp->nextNode[type]->sex) == 'm'){printf("��");}
								else{printf("Ů");}
									printf(" �����");
		 						if((tp->nextNode[type]->isMarried) == 'n' || (tp->nextNode[type]->isMarried) == 'N'){printf("δ��\n");}
		 						else{printf("�ѻ�\n");
		 							//�ѻ飺
									//�ȴ�ӡ���  ����/�ɷ����Ϣ��
		 							if((tp->nextNode[type]->sex) == 'M' || (tp->nextNode[type]->sex) == 'm'){
										printf("\t%s ������ %s ���� %d ����Ů:\n",tp->nextNode[type]->name,tp->nextNode[type]->nextNode[0]->name,tp->nextNode[type]->num);}
									else{
										printf("\t%s ���ɷ� %s ���� %d ����Ů:\n",tp->nextNode[type]->name,tp->nextNode[type]->nextNode[0]->name,tp->nextNode[type]->num);}

									//�ȴ�ӡ���к��� ����
									for(int k=1;k<=(tp->nextNode[type]->num)&&k<20;k++){//��Ϊnum������,�ֿճ�һ������ż,����<=
              							printf("\t\t�� %d ������: %s \n ",k,tp->nextNode[type]->nextNode[k]->name);
       								}//for
       							}
	      	}//if(type>0)
	    }


//������   ���򴴽�
treePoint createTree(){
        treePoint tp;//����һ�� ָ������ ָ��
        tp=(treePoint)malloc(sizeof(treeNode));//����һ�������ڴ�

        printf("\n����������:\n");
        scanf("%s",tp->name);
			//printf("\n%s \n",tp->name);   debug
        printf("\n������ %s ���Ա���ĸ����, �� => m/M  |  Ů => f/F : \n",tp->name);
		scanf("%s",&(tp->sex));
			//printf("\n%s \n",tp->sex);   DEBUG
        printf("������ %s �Ƿ��ѻ�: �ѻ����� y/Y, δ������ n/N : \n",tp->name);
        scanf("%s",&(tp->isMarried));

        if(tp->isMarried == 'Y' ||tp->isMarried == 'y' ){//����ѻ�
            printf("\n\n������ %s �ĺ��Ӹ���(����):\n",tp->name);
            scanf("%d",&(tp->num));

            /******ϵ�� : �Զ�ȡ���ýڵ�� nextNode[]ָ������ ,,,������ֵ Ϊ null***/
            /******��ż��Ϣ �Զ� ��ֵ ******/
            tp->nextNode[0]=(treePoint)malloc(sizeof(treeNode));
            (tp->nextNode[0]->num)=(tp->num);//�Զ���ֵ ���Ӹ���
            (tp->nextNode[0]->isMarried)='Y';//�Զ���ֵ �ѻ�
            /***�Զ���ֵ �� Ů  *****/
            if((tp->sex) == 'M' || (tp->sex) == 'm'){tp->nextNode[0]->sex = 'F';}
            else{tp->nextNode[0]->sex = 'M';}
            //ȡ�� /*����˫�׽ڵ�ָ����ż:*/
            //    (tp->nextNode[0]->parent) = tp;

            /*** �ڴ�ֻ��Ҫ���� ��ż���������� *****/
            //������еģ��Զ����������� ����
            if((tp->sex) == 'M' || (tp->sex) == 'm'){
				printf("������ %s �����ӵ�����:\n",tp->name);
			}else{
				printf("������ %s ���ɷ������:\n",tp->name);
			}

            scanf("%s",tp->nextNode[0]->name);  printf("\n\n");

            /* ������Ϣ��ֵ :��1��ʼѭ��,��һ��. && ˫�ж� ��֤���鲻��Խ��*/
            for(int i=1;i<=(tp->num)&&i<20;i++){//��Ϊnum������,�ֿճ�һ������ż,����<=
              printf("** ����¼�� %s �ĵ� %d ��������Ϣ(��%d��):\n",tp->name,i,tp->num);
              tp->nextNode[i]= createTree();
            }
        }else{tp->num=0;}
        return tp;
}

//����
void visit(treePoint tp){

		 printf(">>������%s ���Ա�",tp->name);
		 	if((tp->sex) == 'M' || (tp->sex) == 'm'){printf("��");}
			else{printf("Ů");}
		 printf(" �����");
		 	if((tp->isMarried) == 'n' || (tp->isMarried) == 'N'){printf("δ��\n");}
		 	else{printf("�ѻ�\n");
		 		//�ѻ飺
				//�ȴ�ӡ���  ����/�ɷ����Ϣ��
		 		if((tp->sex) == 'M' || (tp->sex) == 'm'){
					printf("\t%s ������ %s ���� %d ����Ů:\n",tp->name,tp->nextNode[0]->name,tp->num);}
				else{
					printf("\t%s ���ɷ� %s ���� %d ����Ů:\n",tp->name,tp->nextNode[0]->name,tp->num);}


				//�ȴ�ӡ���к��� ����
				for(int i=1;i<=(tp->num)&&i<20;i++){//��Ϊnum������,�ֿճ�һ������ż,����<=
              		printf("\t\t�� %d ������: %s \n ",i,tp->nextNode[i]->name);
            	}

            	printf("\n");
            	//�ڷֱ�������к���������
				for(int i=1;i<=(tp->num)&&i<20;i++){//��Ϊnum������,�ֿճ�һ������ż,����<=
             		visit(tp->nextNode[i]);
            	}

			 }


}

//���� //���ص��� �� ��ָ��
treePoint search(treePoint tp,char s[]){
	
	if(strcmp(tp->name,s)==0&&count==0){//ֻ�� ���ڵ���Ч
			type=-1;//�����
			printPerson(tp);//����type
			count++;
			return tp;//�ҵ��󷵻����ָ��

	}else{// strcmp(tp->name,s)!=0 ������ֲ����,�����ݹ����
        if(strcmp(tp->nextNode[0]->name,s)==0){//�������ż������
                    //
            type=0;//��ż
			printPerson(tp);

            return tp;//������ ����� ָ��   ���type ʹ��
        }else{		
        			type=-2;//��ǰ��λ 
                    for(int i=1;i<=(tp->num)&&i<20;i++){//��Ϊnum������,�ֿճ�һ������ż,����<=
                        if(strcmp(tp->nextNode[i]->name,s)==0){
                        	type=i;//�ڼ������� ���Ǽ�

                        	printPerson(tp);

                           	return tp;//������ ����� ָ��   ���type ʹ��
                            break;//�ҵ�,�˳�ѭ����

                        }else{
                            search(tp->nextNode[i],s);
                            return NULL; 
                            }//ifelse
                    }//for
                }//if
		}
	return NULL;
}

//���    ������  1 ��Ȣ������2 ��������
void add(treePoint mt){
	int t=0;
	char s[20];
	treePoint tpp;
	tpp=(treePoint)malloc(sizeof(treeNode));//����һ�������ڴ�
	
	printf("-----ѡ���������  1 : ��Ȣ�������ż����2 : �����������Ů��\n");
	//printf("\n���������ͣ�1 -> ��Ȣ�� 2 -> ������\n");
	scanf("%d",&t);

	//��Ȣ
	if(t==1){//һ���� �������  ĳ������  (���߸�)���Ż��Ȣ (��������ĳ�˵���ż)
        printf("---------- ������ ������Ҫ�����˵�������   ----------\n\n");
        scanf("%s",s);

		type=-2;//type�ȸ�ԭ
		tpp=search(mt,s);//���ʹ浽�� int type ����:  -1 root    ���� n Ϊ�� n ������
		
			//����Ǹ�
			if(type==-1){
                //�ȰѸ��û�isMarried ��Ϊ Y  �ѻ�.
                tpp->isMarried = 'Y';
                tpp->num = 0;
				//������еģ�ҪȢ˭
				if(tpp->sex=='M'||tpp->sex=='m'){


					printf("---------- ������ %s ���ӵ����� ��   ----------\n\n",tpp->name);
					tpp->nextNode[0]=(treePoint)malloc(sizeof(treeNode));//����һ�������ڴ�

                    printf("\n����������:\n");
                    scanf("%s",tpp->nextNode[0]->name);

                    (tpp->nextNode[0]->sex) = 'F';
                    (tpp->nextNode[0]->num) = (tpp->num);//�Զ���ֵ ���Ӹ���
                    (tpp->nextNode[0]->isMarried) = 'Y';//�Զ���ֵ �ѻ�
                    printf("\n������! ^_^  \n");

				}else{
					printf("---------- ������ %s �ɷ������ ��   ----------\n\n",tpp->name);
					tpp->nextNode[0]=(treePoint)malloc(sizeof(treeNode));//����һ�������ڴ�
					
					
                    printf("\n����������:\n");
                    scanf("%s",tpp->nextNode[0]->name);

                    (tpp->nextNode[0]->sex) = 'M';
                    (tpp->nextNode[0]->num) = (tpp->num);//�Զ���ֵ ���Ӹ���
                    (tpp->nextNode[0]->isMarried) = 'Y';//�Զ���ֵ �ѻ�

				}
                }
			//������Ǹ�
			if(type>0){
                //�ȰѸ��û�isMarried ��Ϊ Y  �ѻ�.
                tpp->nextNode[type]->isMarried = 'Y';
                tpp->nextNode[type]->num = 0;
				//������еģ�ҪȢ˭
				if(tpp->nextNode[type]->sex=='M'||tpp->nextNode[type]->sex=='m'){
				
				
					
                    printf("---------- ������ %s ���ӵ����� ��   ----------\n\n",tpp->nextNode[type]->name);
					tpp->nextNode[type]->nextNode[0]=(treePoint)malloc(sizeof(treeNode));//����һ�������ڴ�

                    printf("\n����������:\n");
                    scanf("%s",tpp->nextNode[type]->nextNode[0]->name);

                    (tpp->nextNode[type]->nextNode[0]->sex) = 'F';
                    (tpp->nextNode[type]->nextNode[0]->num) = (tpp->nextNode[type]->num);//�Զ���ֵ ���Ӹ���
                    (tpp->nextNode[type]->nextNode[0]->isMarried) = 'Y';//�Զ���ֵ �ѻ�
                    printf("\n������! ^_^  \n");

				}else{
					printf("---------- ������ %s �ɷ������ ��   ----------\n\n",tpp->nextNode[type]->name);

					tpp->nextNode[type]->nextNode[0]=(treePoint)malloc(sizeof(treeNode));//����һ�������ڴ�

                    printf("\n����������:\n");
                    scanf("%s",tpp->nextNode[type]->nextNode[0]->name);

                    (tpp->nextNode[type]->nextNode[0]->sex) = 'F';
                    (tpp->nextNode[type]->nextNode[0]->num) = (tpp->nextNode[type]->num);//�Զ���ֵ ���Ӹ���
                    (tpp->nextNode[type]->nextNode[0]->isMarried) = 'Y';//�Զ���ֵ �ѻ�
                    printf("\n������! ^_^  \n");

				}
			}
	}

	//����
	if(t==2){
        printf("\n----------  ������˭���� (��ϵ)----------\n\n");
        scanf("%s",s);

		type=-2;//type�ȸ�ԭ
		tpp=search(mt,s);//���ʹ浽�� int type ����:  -1 root    ���� n Ϊ�� n ������

        //����Ǹ�
        if(type==-1){
            tpp->nextNode[tpp->num+1]=(treePoint)malloc(sizeof(treeNode));//����һ�������ڴ�

            printf("\n==>����¼��%s�� ��������Ϣ:\n",tpp->nextNode[(tpp->num)+1]->name);
            printf("\n������������ ����:\n");
            scanf("%s",tpp->nextNode[(tpp->num)+1]->name);
			//printf("\n%s \n",tp->name);   debug
            printf("\n������ %s ���Ա���ĸ����, �� => m/M  |  Ů => f/F : \n",tpp->nextNode[(tpp->num)+1]->name);
            scanf("%s",&(tpp->nextNode[(tpp->num)+1]->sex));
            //�Զ���ֵ
            tpp->nextNode[(tpp->num)+1]->num=0;
            tpp->nextNode[(tpp->num)+1]->isMarried='N';
            
            //������ +1
			tpp->num++; 
			printf("\n������ %s ������! ^_^  \n",tpp->nextNode[(tpp->num)]->name);
        }
        if(type>0){
            tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]=(treePoint)malloc(sizeof(treeNode));//����һ�������ڴ�

            printf("\n==>����¼��%s�� ��������Ϣ:\n",tpp->nextNode[type]->name);
            printf("\n������������ ����:\n");
            scanf("%s",tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->name);
            
		
            printf("\n������ %s ���Ա���ĸ����, �� => m/M  |  Ů => f/F : \n",tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->name);
            scanf("%s",&(tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->sex));
            //�Զ���ֵ
            tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->num=0;
            tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)+1]->isMarried='N';
            
            //������ +1
			tpp->nextNode[type]->num++; 
			
			printf("\n������ %s ������! ^_^  \n",tpp->nextNode[type]->nextNode[(tpp->nextNode[type]->num)]->name);
        }
	}

}

//�޸�    xxx �޸ĸ�����Ϣ
void edit(treePoint mt){
        char s[20];
        treePoint tpp;

        printf("---------- ������ Ҫ�޸ĵ��˵�������   ----------\n\n");
        scanf("%s",s);

		tpp=search(mt,s);//���ʹ浽�� int type ����:  -1 root    ���� n Ϊ�� n ������
			//����Ǹ�
			if(type==-1){
                printf("�����������֣�");
                scanf("%s",tpp->name);

                printf("\n�޸����! ^_^  \n");
                }
			//������Ǹ�
			if(type>0){
                printf("�����������֣�");
                scanf("%s",tpp->nextNode[type]->name);

                printf("\n�޸����! ^_^  \n");
				}
}

