
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "WOXCRYPT.H"
#include <ctype.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h> 
#include "md5.h"
#pragma warning (disable : 4018) 
#pragma warning (disable : 4305) 
#pragma warning (disable : 4309) 
#pragma warning (disable : 4715)
#pragma warning (disable : 4101)
#pragma warning (disable : 4518)
#pragma warning (disable : 4228)
#pragma warning (disable : 4244)
#pragma warning (disable : 4390) 
#pragma warning (disable : 4005)
#pragma warning (disable : 4065)



# define MAX_MAP 3000
# define MAXREC 3000 /* �ִ� ���ڵ� �� */
# define MAXMAP 3000 /* �ִ� ���Ǽ�  */
# define PORT 3333 
# define MAXCLIENT 5000
#define BUFSIZE 200
# define AUTO_SAVE 600000
# define AUTO_RESET 

int auto_reset=1810000;
int auto_save=600000;
HANDLE die_event;
HANDLE monster_event; 

CRITICAL_SECTION port,monster_cs,save,id;

char *ip_scan;
char ip_scan2[100];
char domain_name[40];
int bong_client;

//#domain

char check_msg[100];

WSADATA wsaData;
WSADATA wsaData2;
PHOSTENT phi;
PHOSTENT phi2;
char FAR strHostName[100];
char *ip;
char ip2[100];
SYSTEMTIME  st;    
int max_client=150;    
int max_id=2500;
int mon_imsi_c[2000]={0};
int client[MAXCLIENT];
int now=0;
int mimsi=0;
int last_head;
int unsigned thread_imsi[2000];
int unsigned monster_default=1000000;
int test_number=0;
int ips_count=0;
int frecnum=0,choice=0,flag=0,item_frec=0,monster_frec=0,port_frec=0,map_frec=0,rezen_frec=0,npc_frec=0,npc_item_frec=0;;//����������
char *korea;
int imsi_plus;
int mcount_plus;
// int testimsi2[1000];
/* ����ü, �������� ���� */ 
struct student
{
	char id[50], pass[50], title[30],change[100];
	int kaflag;
	int level; 
	int unsigned hel;
	int unsigned mana;
	int unsigned max_hel;
	int unsigned max_hel_body;
	int unsigned max_mana;
	int unsigned max_mana_body;
	int unsigned need_exp; // �ʰ�
	int unsigned him;
	int unsigned him_body;
	int unsigned min;
	int unsigned min_body;
	int unsigned ji;
	int unsigned ji_body;
	int unsigned exp;
	int unsigned money;
	int map_x;
	int map_y;
	char map[20];
	int unsigned thread;
	int banghyang;
	int head;
	int headcolor;
	int dress;
	int dresscolor;
	int sword;
	int swordcolor;
	int sword_item;
	int bangpae;
	int bangpaecolor;
	int unsigned realmap;
	int delay[100];
	int short nop3[200];
	int magic[52];
	int short nop1[200];
	int item[26][2];
	int short nop2[200];
	int im_si;
	char job[20];
	int sex;
	int group;
	int pk;
	int head_gear;
	int earing[2];
	int ring[2];
	int ac;
	int new_head;
	int sangtae;
	//	int ip;
	int himsi;
	int s_number;
	char ip[30];
	int change_flag;
	int hidden_msg_flag;
	
};

struct st_johap
{
	int p_item[100];
	int percent;
	int n_item;
	int count;
};

struct mon
{
	char name[30]; //�̸�
	int number; // ���͹�ȣ
	int real_number;
	int color; // ����
	int unsigned hel; //ü��
	int ac; //����
	int type; // Ÿ��
	int unsigned power; //���ݷ�
	int attack_speed; //���ݼӵ�
	int move_speed; //�̵��ӵ�
	int magic[3]; //���� ��ȣ
	int magic_percent[3]; // ����Ȯ��
	int unsigned exp; // ����ġ
	char item[30]; // �ִ� ������
	int item_percent; // ������ �� Ȯ��
	int money;  // �ִ� ����
	int money_percent; // ������ Ȯ��
	int skil; // ���� ��ų
	int run; // ���� ����
};

struct st_port
{
	int map_count;
	int x1[200];
	int y1[200];
	int map1[200];
	int x2[200];
	int y2[200];
	int map2[200];
	int level[200];
};

struct st_rezen
{
	int mapnumber;
	int time;
	int monster_number;
	int monster_count;
};

struct st_npc
{
	int mapnumber;
	int time;
	int monster_number;
	int monster_count;
	int x;
	int y;
};

struct st_npc_item
{
	char name[40];
	int number;
	int user_sell;
	int npc_sell;
	int mapnumber;
};


struct st_item
{
	
	int number;
	char name[40];
	int select;
	int life;
	int hel_up;
	int mana_up;
	int him_up;
	int min_up;
	int ji_up;
	int level_jehan;
	int him_jehan;
	int min_jehan;
	int ji_jehan;
	int sex;
	int ac;
	int ggajim;
	int drop;
	int repair;
	int repair_expense;
	int job;
	int dress_number;
	int dress_color;
	int sword_number;
	int sword_color;
	int unsigned sword_min_power;
	int unsigned sword_max_power;
	int unsigned sword_gyuk_effect;
	int unsigned sword_gyuk_power;
	int sword_gyuk_percent;
	int sword_delay[2];
	int sword_magic;
	int sword_magic_percent;
	int bangpae_number;
	int bangpae_color;
	int head_number;
	int ring_number;
	int ring_magic;
	int earing_number;
	int earing_magic;
	int unsigned food_hel_up;
	int unsigned food_mana_up;
	int unsigned food_hel_forever_up;
	int unsigned food_mana_forever_up;
	int teleport[3];
};

struct sip
{
	char ip_chadan[20];
};

struct ssort
{
	int lv,job,map,mana,hel,imsi;
};


struct worldmap
{
	int count;
	int threadlist[200];
	int chrnumber[200];
	int map_x_len;
	int map_y_len;
	int item;
	int item_thread[1000];
	int item_number[1000];
	int item_x[1000];
	int item_y[1000];
	int item_count;
	int moster;
	int unsigned monster_thread[1000];
	int monster_number[1000];
	int monster_x[1000];
	int monster_y[1000];
	int monster_count;
	int monster_max;
	int unsigned monster_target[1000];
	int dont_move_x[999];
	int dont_move_y[999];
	int dont_move_thread[999];
	int dont_move_count;
	int dont_rezen_x[999];
	int dont_rezen_y[999];
	int dont_rezen_thread[999];
	int dont_rezen_count;
	int monster_banghyang[1000];
	int monster_move_flag[1000];
	int monster_last_attack[1000];
	int monster_ac[1000];
	int monster_honma[1000];
	int unsigned monster_hel[1000];
	int unsigned monster_max_hel[1000];
	char name[40];
	int sound;
	int parent;
	int sohwan_on;
	int chooldo_on;
	int pk_on;
	int magic_on;
	int min_level;
	int max_level;
	
	
	
	
	
};



struct setting
{
	int unsigned exp;
	int unsigned heal;
	int unsigned exp_mana;
	int unsigned mana;
	int unsigned magic19_hel;
	int unsigned magic19_mana;
	int unsigned magic30_hel;
	int unsigned magic30_mana;
	int unsigned magic31_hel;
	int unsigned magic31_mana;
	int unsigned magic32_hel;
	int unsigned magic32_mana;
	int unsigned magic33_hel;
	int unsigned magic33_mana;
	int unsigned magic34_hel;
	int unsigned magic34_mana;
	int unsigned magic35_hel;
	int unsigned magic35_mana;
	int rezen;
};


struct level_st
{
	char unsigned level;
	int unsigned heal_up;
	int unsigned mana_up;
	int unsigned need_exp;
	
};

struct junsa_st
{
	int level;
	int magic_number;
	int number_need_item;
	char magic_name[50];
	char magic_need_item[50];
};
struct junsa2_st
{
	int number;
	int need_level;
	char hasa_item[50];
	int hasa_item_number;
	char need_item[50];
	int need_item_number;
	char ching_ho[20];
};


int junsa_level,soolsa_level,dosa_level,dojuk_level;
int client_map_x(int imsi,int mapx);
int client_map_y(int imsi,int mapy);
void magic_05(int imsi,char *msg); //   â��	
void monster_item_drop(int imsi,char *msg,int x,int y); // 
int monster_die(int i,int j,int imsi);
void packet_dump(char* buf, int size, int unit);
void exp_money(int imsi,int target);
void file_read();
void ctrl_r(int imsi);
void ctrl_r2(int imsi);
void npc();
void menu_add(char *user,char *pass);
int che_bar(int imsi,int target,int per);
int monster_hel_percent(int map,int k);
void monster_che_bar(int imsi,int target2,int per);
int hel_percent(int imsi);
int monster_move_check(int map,int monster,int x,int y);
int loginchr(int imsi,char *sendmsg);
int loginchr2(int imsi,int color,char *sendmsg);
int move_map(int map,int imsi,int kaflag);

struct student mid[MAXREC];
struct student mid2[MAXREC];
struct student deflt;
struct worldmap taijimap[MAXMAP]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
struct st_item item_st[2500]={NULL};
struct mon monster[700];
struct st_port port_st[1500];
struct st_rezen rezen_st[5000];
struct st_npc npc_st[100];
struct st_npc_item npc_item_st[1000];
struct setting setting_st;
struct level_st level_up[256];
struct junsa_st junsas[255],dojuks[255],soolsas[255],dosas[255];
struct junsa2_st junsas2[255],dojuks2[255],soolsas2[255],dosas2[255];;
struct st_johap johap_st[1000];
struct sip ips[1000];
struct ssort sorts[2000],temps;






xCrypt *Xc;
void sangtae(int imsi,char *msg)
{
				char imsichar[100];
				sprintf(imsichar,"%c%c%c%s",0x03,0x00,strlen(msg),msg);
				int len=Xc->Enc_Pack(imsi,imsichar,strlen(msg)+3,0x0a,1);
				send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
}


void sangtae2(int imsi,int target,char *msg)
{
				char imsichar[100];
				sprintf(imsichar,"%c%c%c%s",0x03,0x00,strlen(msg),msg);
				int len=Xc->Enc_Pack(imsi,imsichar,strlen(msg)+3,0x0a,1);
				send(client[mid2[target].thread],Encrypted_Messages[imsi],len, 0);
}
void msg_line_blue(int imsi,int target,char *msg)
{
				char imsichar[100];
				sprintf(imsichar,"%c%c%c%s",0x00,0x00,strlen(msg),msg);
				int len=Xc->Enc_Pack(imsi,imsichar,strlen(msg)+3,0x0a,1);
				send(client[mid2[target].thread],Encrypted_Messages[imsi],len, 0);
}
void msg_line(int imsi,int target,char *msg)
{
				char imsichar[100];
				sprintf(imsichar,"%c%c%c%s",0x03,0x00,strlen(msg),msg);
				int len=Xc->Enc_Pack(imsi,imsichar,strlen(msg)+3,0x0a,1);
				send(client[mid2[target].thread],Encrypted_Messages[imsi],len, 0);
}



int strcmp2(char *a,char *b,int len)
{
	for(int i=0;i<len;i++)
	{
		if(a[i]!=b[i])
			return 1;
	}
	
	return 0;
	
}



int port_check(int imsi,int *kaflag)
{
	
	int len,retval,mapcount,imsi_count;
	char sendmsg[100];
	// printf("ī��Ʈ : %d\n",port_st[mid2[imsi].realmap].map_count);
	for(int i=0;i<port_st[mid2[imsi].realmap].map_count;i++)
	{
		// printf("�� x:  �� y:   �̵��ϴ°� x,y: %d %d \n",mid2[imsi].map_x,mid2[imsi].map_y,port_st[mid2[imsi].realmap].x1[i],port_st[mid2[imsi].realmap].y1[i]);
		if(port_st[mid2[imsi].realmap].x1[i]==mid2[imsi].map_x
			&& port_st[mid2[imsi].realmap].y1[i]==mid2[imsi].map_y)
		{			
			// �ּҷ������� �˻�
			if(taijimap[port_st[mid2[imsi].realmap].map2[i]].min_level!=0)
			{
				if(mid2[imsi].level<taijimap[port_st[mid2[imsi].realmap].map2[i]].min_level)
				{
					{
						sprintf(sendmsg,"%c%c%c���� %d�̻� ���� �����մϴ�.",'\x03','\x01','\x01',taijimap[port_st[mid2[imsi].realmap].map2[i]].min_level);
						
						len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					}
					return 0;
				}
				
				
			}
			if(taijimap[port_st[mid2[imsi].realmap].map2[i]].max_level!=0)
			{
				if(mid2[imsi].level>taijimap[port_st[mid2[imsi].realmap].map2[i]].max_level)
				{
					sprintf(sendmsg,"%c%c%c���� %d���ϸ� ���� �����մϴ�.",'\x03','\x01','\x01',taijimap[port_st[mid2[imsi].realmap].map2[i]].max_level);
					
					len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
					retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
				}
				
				
			}
			
			// printf("realmap:%d\n",mid2[imsi].realmap);
			char sendmsg[80];
			// printf("realmap:%d\n",mid2[imsi].realmap);
			mid2[imsi].map_y=port_st[mid2[imsi].realmap].y2[i];
			mid2[imsi].map_x=port_st[mid2[imsi].realmap].x2[i];
			// printf("realmap:%d\n",mid2[imsi].realmap);
			move_map(port_st[mid2[imsi].realmap].map2[i],imsi,*kaflag);
			// printf("realmap:%d\n",mid2[imsi].realmap);
			int sendmsg_byte=loginchr(imsi,sendmsg);
			// printf("realmap:%d\n",mid2[imsi].realmap);
			len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			// printf("realmap:%d\n",mid2[imsi].realmap);
			int kimsi=port_st[mid2[imsi].realmap].map2[i];
			
			mid2[imsi].realmap=kimsi;
			// printf("port_st[mid2[imsi].realmap].map2[i]: %d , i :%d  realmap:%d \n",port_st[mid2[imsi].realmap].map2[i],i,mid2[imsi].realmap);
			// printf("port_st[mid2[imsi].realmap].map1[i]: %d\n",port_st[mid2[imsi].realmap].map1[i]);
			//EnterCriticalSection(&port);
			taijimap[mid2[imsi].realmap].count++;
			// printf("realmap:%d\n",mid2[imsi].realmap);
			for(int ka=0;ka<taijimap[mid2[imsi].realmap].count;ka++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[ka]==0)
				{
					taijimap[mid2[imsi].realmap].threadlist[ka]=mid2[imsi].thread;
					taijimap[mid2[imsi].realmap].chrnumber[ka]=imsi;
					mid2[imsi].kaflag=ka;
					
					// printf("%d �ʿ� ��� �߰� \n",mid[imsi].realmap);
					// printf("%d ��° ������ ����Ʈ�� �ִ� ������ : %d\n",ka,taijimap[mid2[imsi].realmap].threadlist[ka]);
					ka = taijimap[mid2[imsi].realmap].count;
				}
			}
			//LeaveCriticalSection(&port);
			
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� ������ ������ �޽��ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[mapcount],sendmsg);  //�ٸ� Ŭ���̾�Ʈ�� ��ġ�� ������
					len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
					
					retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
					
				}
				else 
				{
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			
			// char sendmsg[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
			sendmsg_byte=loginchr(imsi,sendmsg);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					
					// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					
					len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					
				}
				else 
				{
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			for(int count=0,item_count=taijimap[mid2[imsi].realmap].item_count;count<item_count;count++)
			{
				
				if(taijimap[mid2[imsi].realmap].item_thread[count] != 0)
				{
					
					char item[19];
					item[0]='\x00';
					item[1]='\x01';
					item[2]='\x00';
					item[3]=taijimap[mid2[imsi].realmap].item_x[count];
					item[4]='\x00';
					item[5]=taijimap[mid2[imsi].realmap].item_y[count];
					item[6]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x0000ff00 ) >> 8;
					item[7]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x000000ff ) ;
					item[8]='\x00';
					item[9]='\x00';
					item[10]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
					item[11]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
					item[12]='\x00';
					
					len = Xc->Enc_Pack(imsi,item,13,0x07,1);
					retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
					
				}
				
				else imsi_count++;
				
			}
			ctrl_r2(imsi);
			
			char mapmsg2[15];
			mapmsg2[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
			// printf("mapx : %d\n",mid2[imsi].map_x);
			mapmsg2[1]=( mid2[imsi].map_x & 0x000000ff ) ;
			mapmsg2[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
			mapmsg2[3]=( mid2[imsi].map_y & 0x000000ff ) ;
			mapmsg2[4]=( client_map_x(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
			// printf("clien mapx : %d\n",client_map_x(imsi,mid2[imsi].map_x));
			mapmsg2[5]=( client_map_x(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
			mapmsg2[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
			mapmsg2[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
			mapmsg2[8]='\x00';
			mapmsg2[9]='\x00';
			len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
			
			for(int j=0,int imsi_monster_count=taijimap[mid2[imsi].realmap].monster_count;j<imsi_monster_count;j++)
			{
				if(taijimap[mid2[imsi].realmap].monster_x[j]+10 > mid2[imsi].map_x ||
					taijimap[mid2[imsi].realmap].monster_y[j]+10 > mid2[imsi].map_y ||
					taijimap[mid2[imsi].realmap].monster_x[j]-10 < mid2[imsi].map_x ||
					taijimap[mid2[imsi].realmap].monster_y[j]-10 < mid2[imsi].map_y) // ���Ͱ� ���� ȭ�鿡 ���̸�
				{
					int i = mid2[imsi].realmap;
					char peer0_2[15];
					peer0_2[0]='\x00';
					peer0_2[1]='\x01';
					peer0_2[2]=(taijimap[i].monster_x[j] & 0x0000ff00 ) >> 8;
					peer0_2[3]=(taijimap[i].monster_x[j] & 0x000000ff ) ;
					peer0_2[4]=(taijimap[i].monster_y[j] & 0x0000ff00 ) >> 8;
					peer0_2[5]=(taijimap[i].monster_y[j] & 0x000000ff ) ;
					peer0_2[6]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
					peer0_2[7]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
					peer0_2[8]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
					peer0_2[9]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
					peer0_2[10]=(taijimap[i].monster_number[j]+32767 & 0x0000ff00 ) >> 8;
					peer0_2[11]=(taijimap[i].monster_number[j]+32767 & 0x000000ff ) ;
					peer0_2[12]=monster[taijimap[i].monster_number[j]].color;
					peer0_2[13]=taijimap[i].monster_banghyang[j];
					peer0_2[14]='\x00';
					
					
					int len = Xc->Enc_Pack(imsi,peer0_2,15,0x07,1);	
					for(int mapcount=0,imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[i].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����.\n",taijimap[i].threadlist[mapcount]);
							//int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							
						}
						else imsi_count++;
					}
					
					
				}
				
				
			}
			
			
			
			
			
		}
	}
	
	
}

void teleport(int imsi,int *kaflag,int x,int y,int map)
{
	//EnterCriticalSection(&port);
	
	int len,retval,mapcount,imsi_count;
	// printf("ī��Ʈ : %d\n",port_st[mid2[imsi].realmap].map_count);
	
	// printf("realmap:%d\n",mid2[imsi].realmap);
	char sendmsg[80];
	
	mid2[imsi].map_y=y;
	mid2[imsi].map_x=x;
	
	move_map(map,imsi,*kaflag);
	
	int sendmsg_byte=loginchr(imsi,sendmsg);
	
	len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
	
	int kimsi=map;
	mid2[imsi].realmap=kimsi;
	
	
	taijimap[mid2[imsi].realmap].count++;
	
	for(int ka=0;ka<taijimap[mid2[imsi].realmap].count;ka++)
	{
		// printf("%d ��° ������ ����Ʈ�� �ִ� ������ : %d\n",ka,taijimap[14].threadlist[0]);
		if(taijimap[mid2[imsi].realmap].threadlist[ka]==0)
		{
			taijimap[mid2[imsi].realmap].threadlist[ka]=mid2[imsi].thread;
			taijimap[mid2[imsi].realmap].chrnumber[ka]=imsi;
			mid2[imsi].kaflag=ka;
			
			// printf("%d �ʿ� ��� �߰� \n",mid[imsi].realmap);
			// printf("%d ��° ������ ����Ʈ�� �ִ� ������ : %d\n",ka,taijimap[mid2[imsi].realmap].threadlist[ka]);
			// printf("%d ��° �ʿ� �ִ� ��� �� :%d\n",mid[imsi].realmap,taijimap[mid2[imsi].realmap].count);
			ka = taijimap[mid2[imsi].realmap].count;
		}
	}
	
	
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� ������ ������ �޽��ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[mapcount],sendmsg);  //�ٸ� Ŭ���̾�Ʈ�� ��ġ�� ������
			len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	// char sendmsg[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
	sendmsg_byte=loginchr(imsi,sendmsg);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			
			len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	for(int count=0,item_count=taijimap[mid2[imsi].realmap].item_count;count<item_count;count++)
	{
		
		if(taijimap[mid2[imsi].realmap].item_thread[count] != 0)
		{
			
			char item[19];
			item[0]='\x00';
			item[1]='\x01';
			item[2]='\x00';
			item[3]=taijimap[mid2[imsi].realmap].item_x[count];
			item[4]='\x00';
			item[5]=taijimap[mid2[imsi].realmap].item_y[count];
			item[6]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x0000ff00 ) >> 8;
			item[7]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x000000ff ) ;
			item[8]='\x00';
			item[9]='\x00';
			item[10]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
			item[11]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
			item[12]='\x00';
			
			len = Xc->Enc_Pack(imsi,item,13,0x07,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			
		}
		
		else imsi_count++;
		
	}
	ctrl_r2(imsi);
	
	char mapmsg2[15];
	mapmsg2[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
	// printf("mapx : %d\n",mid2[imsi].map_x);
	mapmsg2[1]=( mid2[imsi].map_x & 0x000000ff ) ;
	mapmsg2[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
	mapmsg2[3]=( mid2[imsi].map_y & 0x000000ff ) ;
	mapmsg2[4]=( client_map_x(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
	// printf("clien mapx : %d\n",client_map_x(imsi,mid2[imsi].map_x));
	mapmsg2[5]=( client_map_x(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
	mapmsg2[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
	mapmsg2[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
	mapmsg2[8]='\x00';
	mapmsg2[9]='\x00';
	len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
	
	
	
	
	
	
	
	
	
	
	//LeaveCriticalSection(&port);
}

void ctrl_r(int imsi)
{
	char sendmsg[80];
	int sendmsg_byte=loginchr(imsi,sendmsg);
	int len,retval,mapcount,imsi_count;	
	
	char mapmsg[40];
	mapmsg[0]=0;
	mapmsg[1]=-1;
	mapmsg[2]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x0000ff00 ) >> 8;
	mapmsg[3]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x000000ff ) ;
	mapmsg[4]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x0000ff00 ) >> 8;
	mapmsg[5]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x000000ff ) ;
	mapmsg[6]='\x04';
	mapmsg[7]='\x00';
	mapmsg[8]=strlen(taijimap[mid2[imsi].realmap].name);
	strcpy(mapmsg+9,taijimap[mid2[imsi].realmap].name);
	
	char mapmsg2[15];
	mapmsg2[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
	// printf("mapx : %d\n",mid2[imsi].map_x);
	mapmsg2[1]=( mid2[imsi].map_x & 0x000000ff ) ;
	mapmsg2[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
	mapmsg2[3]=( mid2[imsi].map_y & 0x000000ff ) ;
	mapmsg2[4]=( client_map_x(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
	// printf("clien mapx : %d\n",client_map_x(imsi,mid2[imsi].map_x));
	mapmsg2[5]=( client_map_x(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
	mapmsg2[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
	mapmsg2[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
	mapmsg2[8]='\x00';
	mapmsg2[9]='\x00';
	
	char mapmsg3[20];
	mapmsg3[0]='\x01';
	mapmsg3[1]='\x00';
	mapmsg3[2]='\x00';
	mapmsg3[3]='\x01';
	mapmsg3[4]='\x00';
	mapmsg3[5]='\x00';
	mapmsg3[6]='\xc0';
	mapmsg3[7]='\x00';
	mapmsg3[8]='\x00';
	mapmsg3[9]='\x00';
	mapmsg3[10]='\x03';
	mapmsg3[11]='\x01';
	mapmsg3[12]='\x00';
	mapmsg3[13]='\x02';
	mapmsg3[14]='\x02';
	mapmsg3[15]='\x00';
	mapmsg3[16]='\x04';
	mapmsg3[17]='\x00';
	
	
	
	
	char peer1_0[] = {
		0xaa, 0x00, 0x14, 0x19, 
			0x4c, 0x03, 0x29, 0x34, 0x22, 0x22, 0x05, 0xe2, 
			0x2f, 0x62, 0x03, 0x2b, 0x34, 0x22, 0x21, 0x06, 
			0x23, 0x2a, 0x63,  };
		
		
		
		len = Xc->Enc_Pack(imsi,mapmsg,23,0x15,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,mapmsg3,18,0x19,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		//retval = send(client[mid2[imsi].thread],peer1_0, 23, 0);
		len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		
		
		
		len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		
		// �ٽ� ����ġ
		mapmsg[0]=( mid2[imsi].realmap & 0x0000ff00 ) >> 8;
		mapmsg[1]=( mid2[imsi].realmap & 0x000000ff ) ;
		mapmsg[2]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x0000ff00 ) >> 8;
		mapmsg[3]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x000000ff ) ;
		mapmsg[4]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x0000ff00 ) >> 8;
		mapmsg[5]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x000000ff ) ;
		mapmsg[6]='\x04';
		mapmsg[7]='\x00';
		mapmsg[8]=strlen(taijimap[mid2[imsi].realmap].name);
		strcpy(mapmsg+9,taijimap[mid2[imsi].realmap].name);
		
		
		mapmsg2[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
		// printf("mapx : %d\n",mid2[imsi].map_x);
		mapmsg2[1]=( mid2[imsi].map_x & 0x000000ff ) ;
		mapmsg2[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
		mapmsg2[3]=( mid2[imsi].map_y & 0x000000ff ) ;
		mapmsg2[4]=( client_map_x(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
		// printf("clien mapx : %d\n",client_map_x(imsi,mid2[imsi].map_x));
		mapmsg2[5]=( client_map_x(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
		mapmsg2[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
		mapmsg2[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
		mapmsg2[8]='\x00';
		mapmsg2[9]='\x00';
		
		
		mapmsg3[0]='\x01';
		mapmsg3[1]='\x00';
		mapmsg3[2]='\x00';
		mapmsg3[3]='\x01';
		mapmsg3[4]='\x00';
		mapmsg3[5]='\x00';
		mapmsg3[6]='\xc0';
		mapmsg3[7]='\x00';
		mapmsg3[8]='\x00';
		mapmsg3[9]='\x00';
		mapmsg3[10]='\x03';
		mapmsg3[11]='\x01';
		mapmsg3[12]='\x00';
		mapmsg3[13]='\x02';
		mapmsg3[14]='\x02';
		mapmsg3[15]='\x00';
		mapmsg3[16]='\x04';
		mapmsg3[17]='\x00';
		
		
		
		
		
		
		len = Xc->Enc_Pack(imsi,mapmsg,23,0x15,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,mapmsg3,18,0x19,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		//retval = send(client[mid2[imsi].thread],peer1_0, 23, 0);
		len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� ������ ������ �޽��ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[mapcount],sendmsg);  //�ٸ� Ŭ���̾�Ʈ�� ��ġ�� ������
				len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
				
			}else {
				
				// printf("0 �̹Ƿ� imsi_count ����\n");
				imsi_count++;
			}
		}
		
		// char sendmsg[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
		sendmsg_byte=loginchr(imsi,sendmsg);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				
				// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				
				len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				
			}else {
				
				// printf("0 �̹Ƿ� imsi_count ����\n");
				imsi_count++;
			}
		}
		for(int count=0,item_count=taijimap[mid2[imsi].realmap].item_count;count<item_count;count++)
		{
			
			if(taijimap[mid2[imsi].realmap].item_thread[count] != 0)
			{
				
				char item[19];
				item[0]='\x00';
				item[1]='\x01';
				item[2]='\x00';
				item[3]=taijimap[mid2[imsi].realmap].item_x[count];
				item[4]='\x00';
				item[5]=taijimap[mid2[imsi].realmap].item_y[count];
				item[6]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x0000ff00 ) >> 8;
				item[7]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x000000ff ) ;
				item[8]='\x00';
				item[9]='\x00';
				item[10]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
				item[11]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
				item[12]='\x00';
				
				len = Xc->Enc_Pack(imsi,item,13,0x07,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
				
			}
			
			else imsi_count++;
			
		}
		
}

void ctrl_r2(int imsi)
{
	char sendmsg[80];
	int sendmsg_byte=loginchr(imsi,sendmsg);
	int len,retval,mapcount,imsi_count;	
	
	char mapmsg[60];
	memset(mapmsg,0,60);
	mapmsg[0]=0;
	mapmsg[1]=-1;
	mapmsg[2]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x0000ff00 ) >> 8;
	mapmsg[3]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x000000ff ) ;
	mapmsg[4]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x0000ff00 ) >> 8;
	mapmsg[5]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x000000ff ) ;
	mapmsg[6]='\x04';
	mapmsg[7]='\x00';
	mapmsg[8]=strlen(taijimap[mid2[imsi].realmap].name);
	strcpy(mapmsg+9,taijimap[mid2[imsi].realmap].name);
	
	char mapmsg2[15];
	mapmsg2[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
	// printf("mapx : %d\n",mid2[imsi].map_x);
	mapmsg2[1]=( mid2[imsi].map_x & 0x000000ff ) ;
	mapmsg2[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
	mapmsg2[3]=( mid2[imsi].map_y & 0x000000ff ) ;
	mapmsg2[4]=( client_map_x(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
	// printf("clien mapx : %d\n",client_map_x(imsi,mid2[imsi].map_x));
	mapmsg2[5]=( client_map_x(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
	mapmsg2[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
	mapmsg2[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
	mapmsg2[8]='\x00';
	mapmsg2[9]='\x00';
	
	char mapmsg3[20];
	mapmsg3[0]='\x01';
	mapmsg3[1]='\x00';
	mapmsg3[2]='\x00';
	mapmsg3[3]='\x01';
	mapmsg3[4]='\x00';
	mapmsg3[5]='\x00';
	mapmsg3[6]='\xc0';
	mapmsg3[7]='\x00';
	mapmsg3[8]='\x00';
	mapmsg3[9]='\x00';
	mapmsg3[10]='\x03';
	mapmsg3[11]='\x01';
	mapmsg3[12]='\x00';
	mapmsg3[13]='\x02';
	mapmsg3[14]='\x02';
	mapmsg3[15]='\x00';
	mapmsg3[16]='\x04';
	mapmsg3[17]='\x00';
	
	
	
	
	char peer1_0[] = {
		0xaa, 0x00, 0x14, 0x19, 
			0x4c, 0x03, 0x29, 0x34, 0x22, 0x22, 0x05, 0xe2, 
			0x2f, 0x62, 0x03, 0x2b, 0x34, 0x22, 0x21, 0x06, 
			0x23, 0x2a, 0x63,  };
		
		
		
		len = Xc->Enc_Pack(imsi,mapmsg,23,0x15,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,mapmsg3,18,0x19,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		//retval = send(client[mid2[imsi].thread],peer1_0, 23, 0);
		len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		
		
		
		len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		//Sleep(300);
		
		// �ٽ� ����ġ
		mapmsg[0]=( mid2[imsi].realmap & 0x0000ff00 ) >> 8;
		mapmsg[1]=( mid2[imsi].realmap & 0x000000ff ) ;
		mapmsg[2]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x0000ff00 ) >> 8;
		mapmsg[3]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x000000ff ) ;
		mapmsg[4]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x0000ff00 ) >> 8;
		mapmsg[5]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x000000ff ) ;
		mapmsg[6]='\x04';
		mapmsg[7]='\x00';
		mapmsg[8]=strlen(taijimap[mid2[imsi].realmap].name);
		strcpy(mapmsg+9,taijimap[mid2[imsi].realmap].name);
		/*
		mapmsg[9]='\xc3';
		
		  mapmsg[8]='\x0e';
		  mapmsg[9]='\xc3';
		  mapmsg[10]='\xca';
		  mapmsg[11]='\xba';
		  mapmsg[12]='\xb8';
		  mapmsg[13]='\xb8';
		  mapmsg[14]='\xbb';
		  mapmsg[15]='\xc7';																	
		  mapmsg[16]='\xcf';
		  mapmsg[17]='\xb1';
		  mapmsg[18]='\xe2';
		  mapmsg[19]='\xc0';
		  mapmsg[20]='\xc7';
		  mapmsg[21]='\xb1';
		mapmsg[22]='\xe6';*/
		
		
		mapmsg2[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
		// printf("mapx : %d\n",mid2[imsi].map_x);
		mapmsg2[1]=( mid2[imsi].map_x & 0x000000ff ) ;
		mapmsg2[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
		mapmsg2[3]=( mid2[imsi].map_y & 0x000000ff ) ;
		mapmsg2[4]=( client_map_x(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
		// printf("clien mapx : %d\n",client_map_x(imsi,mid2[imsi].map_x));
		mapmsg2[5]=( client_map_x(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
		mapmsg2[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
		mapmsg2[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
		mapmsg2[8]='\x00';
		mapmsg2[9]='\x00';
		
		
		mapmsg3[0]='\x01';
		mapmsg3[1]='\x00';
		mapmsg3[2]='\x00';
		mapmsg3[3]='\x01';
		mapmsg3[4]='\x00';
		mapmsg3[5]='\x00';
		mapmsg3[6]='\xc0';
		mapmsg3[7]='\x00';
		mapmsg3[8]='\x00';
		mapmsg3[9]='\x00';
		mapmsg3[10]='\x03';
		mapmsg3[11]='\x01';
		mapmsg3[12]='\x00';
		mapmsg3[13]='\x02';
		mapmsg3[14]='\x02';
		mapmsg3[15]='\x00';
		mapmsg3[16]='\x04';
		mapmsg3[17]='\x00';
		
		
		
		
		
		
		len = Xc->Enc_Pack(imsi,mapmsg,60,0x15,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,mapmsg3,18,0x19,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		//retval = send(client[mid2[imsi].thread],peer1_0, 23, 0);
		len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		int color=3;
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� ������ ������ �޽��ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				
				if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
					color=2;
				else color=3;
				int sendmsg_byte=loginchr2(taijimap[mid2[imsi].realmap].chrnumber[mapcount],color,sendmsg);  //�ٸ� Ŭ���̾�Ʈ�� ��ġ�� ������
				len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
				
			}else {
				
				// printf("0 �̹Ƿ� imsi_count ����\n");
				imsi_count++;
			}
		}
		
		// char sendmsg[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
		
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				
				// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
					color=2;
				else color=3;
				sendmsg_byte=loginchr2(imsi,color,sendmsg);
				len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				
			}else {
				
				// printf("0 �̹Ƿ� imsi_count ����\n");
				imsi_count++;
			}
		}
		for(int count=0,item_count=taijimap[mid2[imsi].realmap].item_count;count<item_count;count++)
		{
			
			if(taijimap[mid2[imsi].realmap].item_thread[count] != 0)
			{
				
				char item[19];
				item[0]='\x00';
				item[1]='\x01';
				item[2]='\x00';
				item[3]=taijimap[mid2[imsi].realmap].item_x[count];
				item[4]='\x00';
				item[5]=taijimap[mid2[imsi].realmap].item_y[count];
				item[6]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x0000ff00 ) >> 8;
				item[7]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x000000ff ) ;
				item[8]='\x00';
				item[9]='\x00';
				item[10]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
				item[11]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
				item[12]='\x00';
				
				len = Xc->Enc_Pack(imsi,item,13,0x07,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
				
			}
			
			else imsi_count++;
			
		}
		Sleep(300);
		len = Xc->Enc_Pack(imsi,mapmsg,23,0x15,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,mapmsg3,18,0x19,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		//retval = send(client[mid2[imsi].thread],peer1_0, 23, 0);
		len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		
		
		
}





int move_map(int map,int imsi,int kaflag)
{
	
	int len,retval;	
	
	char mapmsg[40];
	if(map > 10000 || map < 0)
		return 0;
	mapmsg[0]=( map & 0x0000ff00 ) >> 8;
	mapmsg[1]=( map & 0x000000ff ) ;
	// printf("map : %d\n",map);
	mapmsg[2]=( taijimap[map].map_x_len+1 & 0x0000ff00 ) >> 8;
	mapmsg[3]=( taijimap[map].map_x_len+1 & 0x000000ff ) ;
	// printf("len : %d\n",taijimap[map].map_y_len);
	mapmsg[4]=( taijimap[map].map_y_len+1 & 0x0000ff00 ) >> 8;
	mapmsg[5]=( taijimap[map].map_y_len+1 & 0x000000ff ) ;
	mapmsg[6]='\x04';
	mapmsg[7]='\x00';
	mapmsg[8]=strlen(taijimap[mid2[imsi].realmap].name);
	strcpy(mapmsg+9,taijimap[mid2[imsi].realmap].name);
	
	char mapmsg2[15];
	mapmsg2[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
	// printf("mapx : %d\n",mid2[imsi].map_x);
	mapmsg2[1]=( mid2[imsi].map_x & 0x000000ff ) ;
	mapmsg2[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
	mapmsg2[3]=( mid2[imsi].map_y & 0x000000ff ) ;
	mapmsg2[4]=( client_map_x(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
	// printf("clien mapx : %d\n",client_map_x(imsi,mid2[imsi].map_x));
	mapmsg2[5]=( client_map_x(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
	mapmsg2[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
	mapmsg2[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
	mapmsg2[8]='\x00';
	mapmsg2[9]='\x00';
	
	char mapmsg3[20];
	mapmsg3[0]='\x01';
	mapmsg3[1]='\x00';
	mapmsg3[2]='\x00';
	mapmsg3[3]='\x01';
	mapmsg3[4]='\x00';
	mapmsg3[5]='\x00';
	mapmsg3[6]='\xc0';
	mapmsg3[7]='\x00';
	mapmsg3[8]='\x00';
	mapmsg3[9]='\x00';
	mapmsg3[10]='\x03';
	mapmsg3[11]='\x01';
	mapmsg3[12]='\x00';
	mapmsg3[13]='\x02';
	mapmsg3[14]='\x02';
	mapmsg3[15]='\x00';
	mapmsg3[16]='\x04';
	mapmsg3[17]='\x00';
	
	
	
	
	char peer1_0[] = {
		0xaa, 0x00, 0x14, 0x19, 
			0x4c, 0x03, 0x29, 0x34, 0x22, 0x22, 0x05, 0xe2, 
			0x2f, 0x62, 0x03, 0x2b, 0x34, 0x22, 0x21, 0x06, 
			0x23, 0x2a, 0x63,  };
		
		
		
		len = Xc->Enc_Pack(imsi,mapmsg,23,0x15,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		len = Xc->Enc_Pack(imsi,mapmsg3,18,0x19,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		//retval = send(client[mid2[imsi].thread],peer1_0, 23, 0);
		len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		//Sleep(100);
		/*	Sleep(3000);
		
		  char peer1_1[] = {
		  0xaa, 0x00, 0x19, 0x15, 0x4b, 0x05, 0x2e, 0x33, 
		  0x30, 0x25, 0x16, 0x21, 0x28, 0x6b, 0xc7, 0xe5, 
		  0x88, 0x9d, 0x9c, 0xb8, 0xe3, 0xe6, 0xd5, 0xe5, 
		  0xec, 0xf6, 0x97, 0xc1, 0xaa, 0x00, 0x14, 0x19, 
		  0x4c, 0x03, 0x29, 0x34, 0x22, 0x22, 0x05, 0xe2, 
		  0x2f, 0x62, 0x03, 0x2b, 0x34, 0x22, 0x21, 0x06, 
		  0x23, 0x2a, 0x63, 0xaa, 0x00, 0x0c, 0x04, 0x4d, 
		  0x03, 0x21, 0x35, 0x30, 0x23, 0x0c, 0x23, 0x23, 
		  0x63, 0x02, 0xaa, 0x00, 0x20, 0x33, 0x4e, 0x00, 
		  0x22, 0x36, 0x33, 0x20, 0x07, 0x20, 0x2d, 0x63, 
		  0x01, 0x2a, 0x37, 0x20, 0x25, 0x06, 0x26, 0x2e, 
		  0x61, 0x0a, 0x29, 0x3d, 0x23, 0x21, 0x03, 0x9d, 
		  0xcb, 0xa7, 0xc1, 0xe9, 0xc3, 0xaa, 0x00, 0x20, 
		  0x33, 0x4f, 0x01, 0x23, 0x37, 0x32, 0x21, 0x06, 
		  0x21, 0x2c, 0x62, 0x00, 0x2b, 0x36, 0x21, 0x24, 
		  0x07, 0x27, 0x2f, 0x60, 0x0b, 0x28, 0x3c, 0x22, 
		  0x20, 0x02, 0x9c, 0xca, 0xa6, 0xc0, 0xe8, 0xc2 };
		  
		retval = send(client[mid2[imsi].thread],peer1_1, 136, 0);*/
		char sendmsg2[20];
		sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
		sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
		sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
		sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
		sendmsg2[4]='\x00';
		
		
		
		
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				
				
				int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
				// printf("len = %d\n",len);
				packet_dump(sendmsg2,5,16);
				packet_dump(Encrypted_Messages[imsi],10,16);
				// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				
			}else {
				
				// printf("0 �̹Ƿ� imsi_count ����\n");
				imsi_count++;
			}
		}
		//EnterCriticalSection(&port);									
		taijimap[mid2[imsi].realmap].count--;
		// printf("mid2 realmap : %d\n",mid2[imsi].realmap);
		taijimap[mid2[imsi].realmap].threadlist[mid2[imsi].kaflag]=0;
		taijimap[mid2[imsi].realmap].chrnumber[mid2[imsi].kaflag]=0;
		//LeaveCriticalSection(&port);
		
		
		
		
		
		
}


void magic_name(char *sendmagic,int magic_number,int i) // #�����̸��� ����
{
	
	
	
	sendmagic[0]=i;
	// printf("�ѹ����� \n");
	
	switch(magic_number)
	{
	case 0:
		{
			char im[]="\x05\x0a(�������)\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 1: //��ȥ��
		{
			char im[]="\x05\x08��ȥ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 2:
		{
			char im[]="\x05\x08��ȥ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
		
	case 3: // ��õ�˹�
		{
			char im[]="\x05\x08��õ�˹�\x00";	
			strcpy(sendmagic+1,im);
			break;
		}
	case 4: // �ع�ȣ��
		{
			char im[]="\x05\x08�ع�ȣ��\x00";	
			strcpy(sendmagic+1,im);
			break;
		}
	case 5: // â��
		{
			char im[]="\x01\x08â��    \x06â��? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 6: // ����
		{
			char im[]="\x01\x08����    \x06����? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 7: // ��ȯ
		{
			char im[]="\x05\x08��ȯ    \x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 8: // �񿵻�õ��
		{
			char im[]="\x01\x0a�񿵻�õ��\x0f(��,��,��,��)? ";
			strcpy(sendmagic+1,im);
			break;
			
		}
	case 9: // ��ȯ
		{
			char im[]="\x01\x04��ȯ\x0a(�����)? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 10: // ���
		{
			char im[]="\x01\x04���\x0a(�����)? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 11: // ��ȯ
		{
			char im[]="\x01\x08���Ǽ�ȯ\x0a(�����)? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 12: // ��Ȳ��
		{
			char im[]="\x05\x08��Ȳ��  \x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 13: // �����Ǳ��
		{
			char im[]="\x05\x0a�����Ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 14: // ��������
		{
			char im[]="\x05\x08��������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 15: // ������
		{
			char im[]="\x01\x06������\x06����? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 16: // ü�»��
		{
			char im[]="\x05\x08ü�»��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 17: // ��ȣ��
		{
			char im[]="\x05\x08��ȣ�� \x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 18: // ���»��
		{
			char im[]="\x05\x08���»��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 19: // �����Ǳ��
		{
			char im[]="\x02\x0a�����Ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 20: // ��������
		{
			char im[]="\x05\x08��������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 21: // ��ȣ�����
		{
			char im[]="\x02\x0a��ȣ�����\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 22: // �����̾�
		{
			char im[]="\x02\x0a�����̾�  \x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 23: // ��������
		{
			char im[]="\x05\x08��������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 24: // ��ȣ�����'÷
		{
			char im[]="\x05\x0e��ȣ�����'÷ \x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 25: // ��Ȱ
		{
			char im[]="\x02\x04��Ȱ\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 26: // ����������
		{
			char im[]="\x05\x0a����������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 27: // ������
		{
			char im[]="\x05\x06������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 28: // ����������
		{
			char im[]="\x05\x0a����������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 29: // �����̵�
		{
			char im[]="\x01\x08�����̵�\x17(����>�� x��ǥ y��ǥ)? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 30: // �����Ǳ��
		{
			char im[]="\x02\x0a�����Ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 31: // �¾��Ǳ��
		{
			char im[]="\x02\x0a�¾��Ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 32: // �����Ǳ��
		{
			char im[]="\x02\x0a�����Ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 33: // �����Ǳ��
		{
			char im[]="\x02\x0a�����Ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 34: // �ŷ��Ǳ��
		{
			char im[]="\x02\x0a�ŷ��Ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 35: // ��Ȳ�Ǳ��
		{
			char im[]="\x02\x0a��Ȳ�Ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 36: // ��ȯ(�ڸ��̵�)
		{
			char im[]="\x01\x0e��ȯ(�ڸ��̵�)\x0f��ȯ�� ���̵�?>";
			strcpy(sendmagic+1,im);
			break;
		}
	case 37: // �������
		{
			char im[]="\x01\x08�������\x0a(�����)? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 38: // ������
		{
			char im[]="\x01\x06������\x06����? ";
			strcpy(sendmagic+1,im);
			break;
		}
	case 39: // �ǰ�볪��
		{
			char im[]="\x05\x0a�ǰ�볪��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 40: // ���;���
		{
			char im[]="\x05\x08���;���\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 41: // �񿵽º�
		{
			char im[]="\x05\x08�񿵽º�\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 42: // ��ȣ�˹�
		{
			char im[]="\x05\x08��ȣ�˹�\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 43: // �̱���
		{
			char im[]="\x05\x08�̱���\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 44: // ������
		{
			char im[]="\x05\x06������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 45: // ��ȿ��Ȳ
		{
			char im[]="\x05\x08��ȿ��Ȳ\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 46: // ��������
		{
			char im[]="\x05\x08��������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 47: // ���̸���
		{
			char im[]="\x05\x08���̸���\x00";
			strcpy(sendmagic+1,im);
			break;
			
		}
	case 48: // ��ȥ��õ
		{
			char im[]="\x05\x08��ȥ��õ\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 49: // �鿭��
		{
			char im[]="\x02\x06�鿭��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 50: // ��ǳ��
		{
			char im[]="\x02\x06��ǳ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 51: // �����ȭ
		{
			char im[]="\x02\x08�����ȭ\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 52: // ȥ����
		{
			char im[]="\x02\x06ȥ����\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 53: // ����
		{
			char im[]="\x02\x04����\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 54: // �Ϳ���ȥ��
		{
			char im[]="\x05\x0a�Ϳ���ȥ��\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 55: // ����������
		{
			char im[]="\x05\x0a����������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 56: // ������
		{
			char im[]="\x05\x06������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 57: // ����������
		{
			char im[]="\x05\x0a����������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 58: // �����̵�(��)
		{
			char im[]="\x05\x0c�����̵�(��)\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 59: // �����̵�(��)
		{
			char im[]="\x05\x0c�����̵�(��)\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 60: // �����̵�(��)
		{
			char im[]="\x05\x0c�����̵�(��)\x00";
			strcpy(sendmagic+1,im);
			break;
		}
	case 61: // �����̵�(��)
		{
			char im[]="\x05\x0c�����̵�(��)\x00";
			strcpy(sendmagic+1,im);
			break;
		}
		
		
		
	default:
		{
			char im[]="\x00\x08��������\x00";
			strcpy(sendmagic+1,im);
			break;
		}
		
		
		
	}
}



int attack_user(int imsi,int target,int socketnow)
{
	
	int retval,len,imsi_count,mapcount;	
	int rand1=rand();
	
	
	// printf("sword:%d\n",mid2[imsi].sword);
	// printf("sword_item:%d\n",mid2[imsi].sword_item);
	if(item_st[mid2[imsi].sword_item].sword_gyuk_percent!=0)
	{
		rand1=(rand1%item_st[mid2[imsi].sword_item].sword_gyuk_percent); 
		
		if(rand1==0)
		{
			char sendmsg5[5];
			//EnterCriticalSection(&monster_cs);
			if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].thread != 0) 
			{
				sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].thread & 0xff000000 ) >> 24;
				sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].thread & 0x00ff0000 ) >> 16;
				sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].thread & 0x0000ff00 ) >> 8;
				sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].thread & 0x000000ff ) ;;
				sendmsg5[4]=item_st[mid2[imsi].sword_item].sword_gyuk_effect;
				int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
			}
			else printf("�ݿ��� \n\n\n\n");
			len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� ���մϴ�.",36,0x0a,1);
			retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			//LeaveCriticalSection(&monster_cs);
			return item_st[mid2[imsi].sword_item].sword_gyuk_power;
		}
	}
	if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].ac>0)
	{
		return item_st[mid2[imsi].sword_item].sword_max_power+
			(float(mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].ac*0.01)*item_st[mid2[imsi].sword_item].sword_max_power);
	}
	if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].ac<0)
	{
		return item_st[mid2[imsi].sword_item].sword_max_power+
			(float(mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].ac*0.01)*item_st[mid2[imsi].sword_item].sword_max_power);
	}
	if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target]].ac==0)
	{
		return item_st[mid2[imsi].sword_item].sword_max_power;
	}
	
}

int attack_monster(int imsi,int target,int socketnow)
{
	
	int retval,len,imsi_count,mapcount;	
	int rand1=rand();
	
	// printf("sword:%d\n",mid2[imsi].sword);
	// printf("sword_item:%d\n",mid2[imsi].sword_item);
	if(item_st[mid2[imsi].sword_item].sword_gyuk_percent!=0)
	{
		rand1=(rand1%item_st[mid2[imsi].sword_item].sword_gyuk_percent); 
		
		if(rand1==0)
		{
			
			char sendmsg5[5];
			sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target] & 0xff000000 ) >> 24;
			sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target] & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target] & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target] & 0x000000ff ) ;;
			sendmsg5[4]=item_st[mid2[imsi].sword_item].sword_gyuk_effect;
			int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					
					if(taijimap[mid2[imsi].realmap].monster_thread[target]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			
			
			len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� ���մϴ�.",36,0x0a,1);
			retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			
			return item_st[mid2[imsi].sword_item].sword_gyuk_power;
		}
	}
	
	if(monster[taijimap[mid2[imsi].realmap].monster_number[target]].ac>0)
	{
		return item_st[mid2[imsi].sword_item].sword_max_power+
			(float(monster[taijimap[mid2[imsi].realmap].monster_number[target]].ac*0.01)*item_st[mid2[imsi].sword_item].sword_max_power);
	}
	if(monster[taijimap[mid2[imsi].realmap].monster_number[target]].ac<0)
	{
		return item_st[mid2[imsi].sword_item].sword_max_power+
			(float(monster[taijimap[mid2[imsi].realmap].monster_number[target]].ac*0.01)*item_st[mid2[imsi].sword_item].sword_max_power);
	}
	if(monster[taijimap[mid2[imsi].realmap].monster_number[target]].ac==0)
	{
		return item_st[mid2[imsi].sword_item].sword_max_power;
	}
}


int sword49(int imsi,int target,int socketnow)
{
	
	
	int retval,len,imsi_count,mapcount;	
	int rand1=rand();	
	rand1=(rand1%5);
	if(rand1==0)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[target].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[target].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[target].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[target].thread & 0x000000ff ) ;;
		sendmsg5[4]=51;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� ���մϴ�.",36,0x0a,1);
		retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
		return 100;
	}
	
	return 5;
}





int attack(int imsi,int socketnow) // #������
{
	
	int target1=9999,target2=8888;
	int k,imsi_magic;
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				
			}
		} else imsi_magic++;
	}
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y-1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x-1) target2 = k;
				
			}
		} else imsi_magic++;
		// printf("target = %d k = %d\n",target2,k);
	}
	
	
	
	if(target1!=9999 && taijimap[mid2[imsi].realmap].pk_on==1 ) // �ΰ��� ���
	{
		
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[target1].group)
				return 0;
		}
		
		
		int dam=5;  // �⺻ ������ 5
		
		dam = attack_user(imsi,target1,socketnow);
		
		
		
		
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel != 0)
		{
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel-dam;
			if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel>mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel || 
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel == 0)
			{
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel=0;
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].sangtae=1;
				char sendmsg2[90]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
				int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[target1],sendmsg2);
				
				int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
			}
			
			che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target1],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target1]));	
			
		}
		
		
		
		
	}
	if(target2!=8888) // �����ϰ��
	{
		
		//EnterCriticalSection(&monster_cs);		
		int dam = attack_monster(imsi,target2,socketnow);
		taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
			taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
		//LeaveCriticalSection(&monster_cs);
		
		
	}
	
	
}


int levelup_check(int imsi,int target,int exp_namuji)
{
	
	if(mid2[target].level==255 || mid2[target].need_exp==0) 
	{
		mid2[target].need_exp=0;
		exp_money(imsi,target);
		return 0;
	}
	mid2[target].need_exp=level_up[mid2[target].level].need_exp;
	mid2[target].max_hel=mid2[target].max_hel+level_up[mid2[target].level].heal_up;
	mid2[target].max_mana=mid2[target].max_mana+level_up[mid2[target].level].mana_up;
	mid2[target].level++;
	char sendmsg5[5];
	sendmsg5[0]=( mid2[target].thread & 0xff000000 ) >> 24;
	sendmsg5[1]=( mid2[target].thread & 0x00ff0000 ) >> 16;
	sendmsg5[2]=( mid2[target].thread & 0x0000ff00 ) >> 8;
	sendmsg5[3]=( mid2[target].thread & 0x000000ff ) ;;
	sendmsg5[4]=2;
	int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[target].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[target].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[target].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	len = Xc->Enc_Pack(imsi,"\x03\00\x1a������ �Ͽ����ϴ�.",36,0x0a,1);
	
	int retval = send(client[mid2[target].thread],Encrypted_Messages[imsi],len, 0);
	exp_money(imsi,target);
	if(mid2[target].need_exp<=exp_namuji)
	{
		levelup_check(imsi,target,exp_namuji-mid2[target].need_exp);
	}
	
}

int monster_die(int i,int j,int imsi) // #���ʹ���
{
	
	
	//WaitForSingleObject(monster_event,INFINITE);
	
	if(taijimap[i].monster_thread[j]==0) return 0;
	ResetEvent(die_event);
	char sendmsg2[20];
	sendmsg2[0]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
	sendmsg2[1]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
	sendmsg2[2]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
	sendmsg2[3]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
	sendmsg2[4]='\x01';
	sendmsg2[5]='\x00';
	sendmsg2[6]='\x00';
	
	// printf(" ���� ������ ������ %d \n",taijimap[i].monster_thread[j]);
	
	
	
	int len = Xc->Enc_Pack(imsi,sendmsg2,7,0x5f,1);
	for(int mapcount=0,imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
		
	{
		if(taijimap[i].threadlist[mapcount] != 0)
		{
			
			// printf(" %d��° �������� �������� ���� ������ ����.\n",taijimap[i].threadlist[mapcount]);
			
			if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
				int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);
			
		}
		
		else imsi_count++;
	}
	
	
	
	char iim[20]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	int random=rand();
	if(monster[taijimap[i].monster_number[j]].item_percent!=0)
	{
		random=random%monster[taijimap[i].monster_number[j]].item_percent;
		if(random==0)
		{
			
			strcpy(iim+1,monster[taijimap[i].monster_number[j]].item);
			monster_item_drop(imsi,iim,taijimap[i].monster_x[j],taijimap[i].monster_y[j]);
		}
	}
	char sss[3];
	char sendmsg3[80];
	memset(sendmsg3,0,80);
	if(mid2[imsi].group==0 || mid2[imsi].group==-1)
	{
		mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].exp=mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].exp+
			monster[taijimap[i].monster_number[j]].exp;
		sprintf(sendmsg3,"%c%c%c����ġ�� %u �ö����ϴ�.",'\x03','\x01','\x01',monster[taijimap[i].monster_number[j]].exp);
		mid2[imsi].exp=mid2[imsi].exp+monster[taijimap[i].monster_number[j]].exp;
		if(mid2[imsi].need_exp<=monster[taijimap[i].monster_number[j]].exp)
		{
			levelup_check(imsi,imsi,monster[taijimap[i].monster_number[j]].exp-mid2[imsi].need_exp);
		}
		else
			mid2[imsi].need_exp=mid2[imsi].need_exp-monster[taijimap[i].monster_number[j]].exp;
		
		exp_money(imsi,imsi);
		sendmsg3[2]=strlen(sendmsg3)-3;
		packet_dump(sendmsg3,3+strlen(sendmsg3+3),16);
		len = Xc->Enc_Pack(imsi,sendmsg3,80,0x0a,1);
		// printf("����ġ ȹ�� \n");
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
		
	}
	else
	{
		
		int member_count;
		
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count,member_count=0;mapcount<imsi_count;mapcount++) // �ٸ� Ŭ���̾�Ʈ ��ġ ����
		{
			
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				
				if(	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group == mid2[imsi].group)
				{
					
					
					if(mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x > mid2[imsi].map_x+8 || 
						mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y > mid2[imsi].map_y+8 ||
						mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x < mid2[imsi].map_x-8 ||
						mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y < mid2[imsi].map_y-8)
					{
						
					}
					
					else
					{
						// printf("���� ���� ����� ���� �ȿ� �����Ƿ� ����ġ ȹ��\n");
						member_count++;
					}
					
					
				}
				else 
				{
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
		}
		int unsigned exp;
		if(member_count!=0)
		{
			if(member_count==1) exp = monster[taijimap[i].monster_number[j]].exp;
			else
				exp = ( monster[taijimap[i].monster_number[j]].exp / member_count ) * 1.6;
		}
		else
		{
			exp=monster[taijimap[i].monster_number[j]].exp;
		}
		
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++) // �ٸ� Ŭ���̾�Ʈ ��ġ ����
		{
			
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				
				if(	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group == mid2[imsi].group)
				{
					if(mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x > mid2[imsi].map_x+8 || 
						mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y > mid2[imsi].map_y+8 ||
						mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x < mid2[imsi].map_x-8 ||
						mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y < mid2[imsi].map_y-8)
					{
						
					}	
					else
					{
						
						if(mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].sangtae==0)
						{
							mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].exp=mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].exp+
								exp;
							exp_money(imsi,taijimap[mid2[imsi].realmap].chrnumber[mapcount]);
							
							sprintf(sendmsg3,"%c%c%c����ġ�� %u �ö����ϴ�.",'\x03','\x01','\x01',exp);
							
							//mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].exp=mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].exp+exp;
							if(mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].need_exp<=exp)
							{
								levelup_check(imsi,taijimap[mid2[imsi].realmap].chrnumber[mapcount],exp-mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].need_exp);
							}
							else
								mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].need_exp=mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].need_exp-exp;
							sendmsg3[2]=strlen(sendmsg3)-3;
							packet_dump(sendmsg3,3+strlen(sendmsg3+3),16);
							len = Xc->Enc_Pack(imsi,sendmsg3,80,0x0a,1);
							// printf("����ġ ȹ��2 \n");
							int retval = send(client[mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].thread],Encrypted_Messages[imsi],len, 0);
						}
					}
					
				}
				else 
				{
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
		}
	}
	
	taijimap[i].monster_thread[j]=0;
	taijimap[i].monster_count--;
	mon_imsi_c[i]--;
	SetEvent(die_event);
	
	
	
	
	
	
	
	
	
	
	
	
}

int hel_percent(int imsi)
{
	float max_hel=(float)mid2[imsi].max_hel;
	float hel=(float)mid2[imsi].hel;
	// printf("����ü�� : %d\n",mid2[imsi].hel);
	// printf("�ִ�ü�� : %d\n",mid2[imsi].max_hel);
	float per;
	per = (hel / max_hel) * 100;
	// printf("����ü�� %d\n",per);
	if((int)per==0)
	{
		if(mid2[imsi].hel==0)
			return 0;
		else return 1;
	}
	return (int)per;
	
}

int monster_hel_percent(int map,int k)
{
	float max_hel=(float)taijimap[map].monster_max_hel[k];
	float hel=(float)taijimap[map].monster_hel[k];
	float per;
	per = (hel / max_hel) * 100;
	// printf("����ü�� %d\n",per);
	if((int)per==0)
	{
		if(taijimap[map].monster_hel[k]==0)
			return 0;
		else return 1;
	}
	return (int)per;
	
	
}

void monster_che_bar(int imsi,int target2,int per)
{
	int retval,mapcount,imsi_count,len;
	char sendmsg[6];
	sendmsg[0]=(taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
	sendmsg[1]=(taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
	sendmsg[2]=(taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
	sendmsg[3]=(taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
	sendmsg[4]='\x00';
	sendmsg[5]=per;
	int color=0;
	len = Xc->Enc_Pack(imsi,sendmsg,6,0x13,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
			{
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else
			{
				if(taijimap[mid2[imsi].realmap].chrnumber[mapcount]==imsi)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				
			}
		}
		else imsi_count++;
	}
	
	
}

void exp_money(int imsi,int target) // ü��, �� ��ġ ����� ����
{
	
	char sendmsg8[50];
	sendmsg8[0]='\x78';
	sendmsg8[1]='\x01';
	sendmsg8[2]='\x01';
	sendmsg8[3]='\x01';
	sendmsg8[4]=mid2[target].level;
	sendmsg8[5]=( mid2[target].max_hel & 0xff000000 ) >> 24;
	sendmsg8[6]=( mid2[target].max_hel & 0x00ff0000 ) >> 16;
	sendmsg8[7]=( mid2[target].max_hel & 0x0000ff00 ) >> 8;
	sendmsg8[8]=( mid2[target].max_hel & 0x000000ff ) ;
	sendmsg8[9]=( mid2[target].max_mana & 0xff000000 ) >> 24;
	sendmsg8[10]=( mid2[target].max_mana & 0x00ff0000 ) >> 16;
	sendmsg8[11]=( mid2[target].max_mana & 0x0000ff00 ) >> 8;
	sendmsg8[12]=( mid2[target].max_mana & 0x000000ff ) ;
	sendmsg8[13]=mid2[target].him;
	sendmsg8[14]=mid2[target].min;
	sendmsg8[15]='\x03';
	sendmsg8[16]='\x03';
	sendmsg8[17]=mid2[target].ji;
	sendmsg8[18]='\x01';
	sendmsg8[19]='\x01';
	sendmsg8[20]='\x63';
	sendmsg8[21]='\x6d';
	sendmsg8[22]='\x15';
	sendmsg8[23]='\xb9';
	sendmsg8[24]=( mid2[target].hel & 0xff000000 ) >> 24;
	sendmsg8[25]=( mid2[target].hel & 0x00ff0000 ) >> 16;
	sendmsg8[26]=( mid2[target].hel & 0x0000ff00 ) >> 8;
	sendmsg8[27]=( mid2[target].hel & 0x000000ff ) ;
	sendmsg8[28]=( mid2[target].mana & 0xff000000 ) >> 24;
	sendmsg8[29]=( mid2[target].mana & 0x00ff0000 ) >> 16;
	sendmsg8[30]=( mid2[target].mana & 0x0000ff00 ) >> 8;
	sendmsg8[31]=( mid2[target].mana & 0x000000ff ) ;
	sendmsg8[32]=( mid2[target].exp & 0xff000000 ) >> 24;
	sendmsg8[33]=( mid2[target].exp & 0x00ff0000 ) >> 16;
	sendmsg8[34]=( mid2[target].exp & 0x0000ff00 ) >> 8;
	sendmsg8[35]=( mid2[target].exp & 0x000000ff ) ;
	sendmsg8[36]=( mid2[target].money & 0xff000000 ) >> 24;
	sendmsg8[37]=( mid2[target].money & 0x00ff0000 ) >> 16;
	sendmsg8[38]=( mid2[target].money & 0x0000ff00 ) >> 8;
	sendmsg8[39]=( mid2[target].money & 0x000000ff ) ;
	sendmsg8[40]='\x00';
	sendmsg8[41]='\x00';
	sendmsg8[42]='\x00';
	sendmsg8[43]='\x00';
	sendmsg8[44]='\x01';
	sendmsg8[45]='\x00';
	sendmsg8[46]='\x01';
	sendmsg8[47]='\x01';
	
	
	int len = Xc->Enc_Pack(imsi,sendmsg8,48,0x08,1);
	int retval = send(client[mid2[target].thread],Encrypted_Messages[imsi],len, 0);  
	
	
}

int che_bar(int imsi,int target,int per)
{
	int retval,mapcount,imsi_count,len;
	char sendmsg[6];
	if(mid2[target].thread == 0) return 0;
	sendmsg[0]=(mid2[target].thread & 0xff000000 ) >> 24;
	sendmsg[1]=(mid2[target].thread & 0x00ff0000 ) >> 16;
	sendmsg[2]=(mid2[target].thread & 0x0000ff00 ) >> 8;
	sendmsg[3]=(mid2[target].thread & 0x000000ff ) ;;
	sendmsg[4]='\x00';
	sendmsg[5]=per;
	len = Xc->Enc_Pack(imsi,sendmsg,6,0x13,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �ڽ��� ü�¹� ����\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	
	char sendmsg8[50];
	sendmsg8[0]='\x78';
	sendmsg8[1]='\x01';
	sendmsg8[2]='\x01';
	sendmsg8[3]='\x01';
	sendmsg8[4]=mid2[target].level;
	sendmsg8[5]=( mid2[target].max_hel & 0xff000000 ) >> 24;
	sendmsg8[6]=( mid2[target].max_hel & 0x00ff0000 ) >> 16;
	sendmsg8[7]=( mid2[target].max_hel & 0x0000ff00 ) >> 8;
	sendmsg8[8]=( mid2[target].max_hel & 0x000000ff ) ;
	sendmsg8[9]=( mid2[target].max_mana & 0xff000000 ) >> 24;
	sendmsg8[10]=( mid2[target].max_mana & 0x00ff0000 ) >> 16;
	sendmsg8[11]=( mid2[target].max_mana & 0x0000ff00 ) >> 8;
	sendmsg8[12]=( mid2[target].max_mana & 0x000000ff ) ;
	sendmsg8[13]=mid2[target].him;
	sendmsg8[14]=mid2[target].min;
	sendmsg8[15]='\x03';
	sendmsg8[16]='\x03';
	sendmsg8[17]=mid2[target].ji;
	sendmsg8[18]='\x01';
	sendmsg8[19]='\x01';
	sendmsg8[20]='\x63';
	sendmsg8[21]='\x6d';
	sendmsg8[22]='\x15';
	sendmsg8[23]='\xb9';
	sendmsg8[24]=( mid2[target].hel & 0xff000000 ) >> 24;
	sendmsg8[25]=( mid2[target].hel & 0x00ff0000 ) >> 16;
	sendmsg8[26]=( mid2[target].hel & 0x0000ff00 ) >> 8;
	sendmsg8[27]=( mid2[target].hel & 0x000000ff ) ;
	sendmsg8[28]=( mid2[target].mana & 0xff000000 ) >> 24;
	sendmsg8[29]=( mid2[target].mana & 0x00ff0000 ) >> 16;
	sendmsg8[30]=( mid2[target].mana & 0x0000ff00 ) >> 8;
	sendmsg8[31]=( mid2[target].mana & 0x000000ff ) ;
	sendmsg8[32]=( mid2[target].exp & 0xff000000 ) >> 24;
	sendmsg8[33]=( mid2[target].exp & 0x00ff0000 ) >> 16;
	sendmsg8[34]=( mid2[target].exp & 0x0000ff00 ) >> 8;
	sendmsg8[35]=( mid2[target].exp & 0x000000ff ) ;
	sendmsg8[36]=( mid2[target].money & 0xff000000 ) >> 24;
	sendmsg8[37]=( mid2[target].money & 0x00ff0000 ) >> 16;
	sendmsg8[38]=( mid2[target].money & 0x0000ff00 ) >> 8;
	sendmsg8[39]=( mid2[target].money & 0x000000ff ) ;
	sendmsg8[40]='\x00';
	sendmsg8[41]='\x00';
	sendmsg8[42]='\x00';
	sendmsg8[43]='\x00';
	sendmsg8[44]='\x01';
	sendmsg8[45]='\x00';
	sendmsg8[46]='\x01';
	sendmsg8[47]='\x01';
	
	
	len = Xc->Enc_Pack(imsi,sendmsg8,48,0x08,1);
	retval = send(client[mid2[target].thread],Encrypted_Messages[imsi],len, 0);  
	
	
	
	
	
	
}

int che_bar_attack(int imsi,int target,int per)  // ���Ͱ� �ΰ� ������ ü��
{
	int retval,mapcount,imsi_count,len;
	char sendmsg[6];
	if(mid2[target].thread == 0) return 0;
	sendmsg[0]=(mid2[target].thread & 0xff000000 ) >> 24;
	sendmsg[1]=(mid2[target].thread & 0x00ff0000 ) >> 16;
	sendmsg[2]=(mid2[target].thread & 0x0000ff00 ) >> 8;
	sendmsg[3]=(mid2[target].thread & 0x000000ff ) ;;
	sendmsg[4]='\x00';
	sendmsg[5]=per;
	len = Xc->Enc_Pack(imsi,sendmsg,6,0x13,1);
	for(mapcount=0,imsi_count=taijimap[mid2[target].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[target].realmap].threadlist[mapcount] != 0)
		{
			retval = send(client[taijimap[mid2[target].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	
	char sendmsg8[50];
	sendmsg8[0]='\x78';
	sendmsg8[1]='\x01';
	sendmsg8[2]='\x01';
	sendmsg8[3]='\x01';
	sendmsg8[4]=mid2[target].level;
	sendmsg8[5]=( mid2[target].max_hel & 0xff000000 ) >> 24;
	sendmsg8[6]=( mid2[target].max_hel & 0x00ff0000 ) >> 16;
	sendmsg8[7]=( mid2[target].max_hel & 0x0000ff00 ) >> 8;
	sendmsg8[8]=( mid2[target].max_hel & 0x000000ff ) ;
	sendmsg8[9]=( mid2[target].max_mana & 0xff000000 ) >> 24;
	sendmsg8[10]=( mid2[target].max_mana & 0x00ff0000 ) >> 16;
	sendmsg8[11]=( mid2[target].max_mana & 0x0000ff00 ) >> 8;
	sendmsg8[12]=( mid2[target].max_mana & 0x000000ff ) ;
	sendmsg8[13]=mid2[target].him;
	sendmsg8[14]=mid2[target].min;
	sendmsg8[15]='\x03';
	sendmsg8[16]='\x03';
	sendmsg8[17]=mid2[target].ji;
	sendmsg8[18]='\x01';
	sendmsg8[19]='\x01';
	sendmsg8[20]='\x63';
	sendmsg8[21]='\x6d';
	sendmsg8[22]='\x15';
	sendmsg8[23]='\xb9';
	sendmsg8[24]=( mid2[target].hel & 0xff000000 ) >> 24;
	sendmsg8[25]=( mid2[target].hel & 0x00ff0000 ) >> 16;
	sendmsg8[26]=( mid2[target].hel & 0x0000ff00 ) >> 8;
	sendmsg8[27]=( mid2[target].hel & 0x000000ff ) ;
	sendmsg8[28]=( mid2[target].mana & 0xff000000 ) >> 24;
	sendmsg8[29]=( mid2[target].mana & 0x00ff0000 ) >> 16;
	sendmsg8[30]=( mid2[target].mana & 0x0000ff00 ) >> 8;
	sendmsg8[31]=( mid2[target].mana & 0x000000ff ) ;
	sendmsg8[32]=( mid2[target].exp & 0xff000000 ) >> 24;
	sendmsg8[33]=( mid2[target].exp & 0x00ff0000 ) >> 16;
	sendmsg8[34]=( mid2[target].exp & 0x0000ff00 ) >> 8;
	sendmsg8[35]=( mid2[target].exp & 0x000000ff ) ;
	sendmsg8[36]=( mid2[target].money & 0xff000000 ) >> 24;
	sendmsg8[37]=( mid2[target].money & 0x00ff0000 ) >> 16;
	sendmsg8[38]=( mid2[target].money & 0x0000ff00 ) >> 8;
	sendmsg8[39]=( mid2[target].money & 0x000000ff ) ;
	sendmsg8[40]='\x00';
	sendmsg8[41]='\x00';
	sendmsg8[42]='\x00';
	sendmsg8[43]='\x00';
	sendmsg8[44]='\x01';
	sendmsg8[45]='\x00';
	sendmsg8[46]='\x01';
	sendmsg8[47]='\x01';
	
	
	len = Xc->Enc_Pack(imsi,sendmsg8,48,0x08,1);
	retval = send(client[mid2[target].thread],Encrypted_Messages[imsi],len, 0);  
	
	
	
	
	
}



int client_map_x(int imsi,int mapx)
{
	
	int k;
	if(mapx<8)
	{
		// printf("\n8������ \n");
		return mapx;
	}
	if(mapx<=8+taijimap[mid2[imsi].realmap].map_x_len-16)
	{
		// printf("\n�߰���\n");
		return 8;
	}
	// printf("\n�̻��� \n");
	return mapx-taijimap[mid2[imsi].realmap].map_x_len+16;
}

int client_map_y(int imsi,int mapy)
{
	
	int k;
	if(mapy<7)
	{
		return mapy;
	}
	if(mapy<=7+taijimap[mid2[imsi].realmap].map_y_len-14)
	{
		return 7;
	}
	return mapy-taijimap[mid2[imsi].realmap].map_y_len+14;
}


int finduser(char *s,int from){
	char s2[200];
	char s3[200];
	char t;
	char k;
	int a;
	int b;
	t=s[0];
	a=(int)t;
	strncpy(s2,s+1,a);
	s2[a]=NULL;
	// printf("user :%s \n",s2);
	k=s[a+1];
	b=(int)k;
	strncpy(s3,s+a+2,b);
	s3[b]=NULL;
	// printf("pass :%s \n",s3);
	//file_read();
	if(strcmp(s2,"!!")==0)
	{
		if(mid2[from].group==0 || mid2[from].group==0)
		{
			msg_line_blue(from,from,"�׷��� �ƴ� ���¿����� ���� �����ϴ�.");
			return -3;
			
		}
		char msg[100];
		memset(msg,0,100);
		sprintf(msg,"�׷������> %s",s3);
		msg_line_blue(from,from,msg);
		
		for(int i=0;i<frecnum;i++)
		{
			if(mid2[i].thread!=0 && mid2[i].group==mid2[from].group && i!=from)
			{
				memset(msg,0,100);
				sprintf(msg,"!!\"%s(%s) %s",mid2[from].id,taijimap[mid2[from].realmap].name,s3);
				msg_line_blue(from,i,msg);
				
			}
			
		}
		return -3;
		
	}
	
	
	if(strcmp(s3,"�Ծ�")==0)
	{
		
		return -2;
	}
	if(strcmp(s3,"�Ե��")==0)
	{
		
		return -2;
	}
	if(strcmp(s3,"����")==0)
	{
		
		return -2;
	}
	if(strcmp(s2,"���")==0 && s3[0]!=0x01 )
	{
		printf("\n\"%s:%s\"\n",mid2[from].id,s3);
		printf("�Է�:");
		return -1;
	}
	
	
	
	
	
    unsigned char buf[1000];
	memset(buf,4,1000);
	//printf("domain:%s\n",domain_name);
	
	
	for(int p=0;p<strlen(s2);p++)
	{
		buf[p]=s2[p];
	}
	
	
	for(int i=0;i<frecnum;i++)
	{
		// printf("�ӼӸ� ���̵� : %s\n",s2);
		// printf("�ҷ��� ���̵� : %s\n",mid[i].id);
		if(strcmp(s2,mid2[i].id)==0)
		{
			return mid2[i].thread;
		}
	}
	return 0;
	
}

int finduser_group(char *s){
	char s2[200];
	char s3[200];
	char t;
	char k;
	int a;
	int b;
	t=s[0];
	a=(int)t;
	strncpy(s2,s+1,a);
	s2[a]=NULL;
	// printf("user :%s \n",s2);
	k=s[a+1];
	b=(int)k;
	strncpy(s3,s+a+2,b);
	s3[b]=NULL;
	// printf("pass :%s \n",s3);
	//file_read();
	for(int i=0;i<frecnum;i++)
	{
		// printf("�ӼӸ� ���̵� : %s\n",s2);
		// printf("�ҷ��� ���̵� : %s\n",mid[i].id);
		if(strcmp(s2,mid2[i].id)==0)
		{
			return i;
		}
	}
	return 0;
}



void fwrite(){
	
	//npc();
	EnterCriticalSection(&save);
	FILE *fp;
	fp=fopen("chr.txt","w");
	fseek(fp,0,SEEK_SET);
	for(int i=0; i < frecnum; i++)
		// if(mid[i].hakbun != 0)  ���̵� ������ �ʿ䰡 ���� ������ �ʿ����
	{
		fprintf(fp,"{\n");
		fprintf(fp,"���̵�:%s\n",mid[i].id);
		fprintf(fp,"��й�ȣ:%s\n",mid[i].pass);
		fprintf(fp,"����:%s\n",mid[i].job);
		fprintf(fp,"�±޹�ȣ:%d\n",mid[i].s_number);
		fprintf(fp,"����:%d\n",mid[i].level);
		fprintf(fp,"ü��:%u\n",mid[i].hel);
		fprintf(fp,"����:%u\n",mid[i].mana);
		fprintf(fp,"�ִ�ü��:%u\n",mid[i].max_hel);
		fprintf(fp,"�ִ븶��:%u\n",mid[i].max_mana);
		fprintf(fp,"����ġ:%u\n",mid[i].exp);
		fprintf(fp,"�ʿ����ġ:%u\n",mid[i].need_exp);
		fprintf(fp,"��:%u\n",mid[i].money);
		fprintf(fp,"��ǥX:%d\n",mid[i].map_x);
		fprintf(fp,"��ǥY:%d\n",mid[i].map_y);
		//fprintf(fp,"���̸�:%s\n",mid[i].map);
		fprintf(fp,"��:%d\n",mid[i].him);
		fprintf(fp,"��:%d\n",mid[i].min);
		fprintf(fp,"��:%d\n",mid[i].ji);
		fprintf(fp,"������:%d\n",mid[i].thread);
		fprintf(fp,"����:%d\n",mid[i].banghyang);
		fprintf(fp,"�Ӹ����:%d\n",mid[i].head);
		fprintf(fp,"�Ӹ�����:%d\n",mid[i].headcolor);
		fprintf(fp,"��:%d\n",mid[i].dress);
		fprintf(fp,"�ʻ���:%d\n",mid[i].dresscolor);
		fprintf(fp,"����:%d\n",mid[i].sword);
		fprintf(fp,"�������:%d\n",mid[i].swordcolor);
		fprintf(fp,"����:%d\n",mid[i].bangpae);
		fprintf(fp,"���л���:%d\n",mid[i].bangpaecolor);
		fprintf(fp,"����:%d\n",mid[i].head_gear);
		fprintf(fp,"����1:%d\n",mid[i].ring[0]);
		fprintf(fp,"����2:%d\n",mid[i].ring[1]);
		fprintf(fp,"�Ͱ���1:%d\n",mid[i].earing[0]);
		fprintf(fp,"�Ͱ���2:%d\n",mid[i].earing[1]);
		fprintf(fp,"�ʹ�ȣ:%d\n",mid[i].realmap);
		//fprintf(fp,"������:%d\n",mid[i].realmap);
		fprintf(fp,"����a:%d\n",mid[i].magic[0]);
		fprintf(fp,"����b:%d\n",mid[i].magic[1]);
		fprintf(fp,"����c:%d\n",mid[i].magic[2]);
		fprintf(fp,"����d:%d\n",mid[i].magic[3]);
		fprintf(fp,"����e:%d\n",mid[i].magic[4]);
		fprintf(fp,"����f:%d\n",mid[i].magic[5]);
		fprintf(fp,"����g:%d\n",mid[i].magic[6]);
		fprintf(fp,"����h:%d\n",mid[i].magic[7]);
		fprintf(fp,"����i:%d\n",mid[i].magic[8]);
		fprintf(fp,"����j:%d\n",mid[i].magic[9]);
		fprintf(fp,"����k:%d\n",mid[i].magic[10]);
		fprintf(fp,"����l:%d\n",mid[i].magic[11]);
		fprintf(fp,"����m:%d\n",mid[i].magic[12]);
		fprintf(fp,"����n:%d\n",mid[i].magic[13]);
		fprintf(fp,"����o:%d\n",mid[i].magic[14]);
		fprintf(fp,"����p:%d\n",mid[i].magic[15]);
		fprintf(fp,"����q:%d\n",mid[i].magic[16]);
		fprintf(fp,"����r:%d\n",mid[i].magic[17]);
		fprintf(fp,"����s:%d\n",mid[i].magic[18]);
		fprintf(fp,"����t:%d\n",mid[i].magic[19]);
		fprintf(fp,"����u:%d\n",mid[i].magic[20]);
		fprintf(fp,"����v:%d\n",mid[i].magic[21]);
		fprintf(fp,"����w:%d\n",mid[i].magic[22]);
		fprintf(fp,"����x:%d\n",mid[i].magic[23]);
		fprintf(fp,"����y:%d\n",mid[i].magic[24]);
		fprintf(fp,"����z:%d\n",mid[i].magic[25]);
		fprintf(fp,"����A:%d\n",mid[i].magic[26]);
		fprintf(fp,"����B:%d\n",mid[i].magic[27]);
		fprintf(fp,"����C:%d\n",mid[i].magic[28]);
		fprintf(fp,"����D:%d\n",mid[i].magic[29]);
		fprintf(fp,"����E:%d\n",mid[i].magic[30]);
		fprintf(fp,"����F:%d\n",mid[i].magic[31]);
		fprintf(fp,"����G:%d\n",mid[i].magic[32]);
		fprintf(fp,"����H:%d\n",mid[i].magic[33]);
		fprintf(fp,"����I:%d\n",mid[i].magic[34]);
		fprintf(fp,"����J:%d\n",mid[i].magic[35]);
		fprintf(fp,"����K:%d\n",mid[i].magic[36]);
		fprintf(fp,"����L:%d\n",mid[i].magic[37]);
		fprintf(fp,"����M:%d\n",mid[i].magic[38]);
		fprintf(fp,"����N:%d\n",mid[i].magic[39]);
		fprintf(fp,"����O:%d\n",mid[i].magic[40]);
		fprintf(fp,"����P:%d\n",mid[i].magic[41]);
		fprintf(fp,"����Q:%d\n",mid[i].magic[42]);
		fprintf(fp,"����R:%d\n",mid[i].magic[43]);
		fprintf(fp,"����S:%d\n",mid[i].magic[44]);
		fprintf(fp,"����T:%d\n",mid[i].magic[45]);
		fprintf(fp,"����U:%d\n",mid[i].magic[46]);
		fprintf(fp,"����V:%d\n",mid[i].magic[47]);
		fprintf(fp,"����W:%d\n",mid[i].magic[48]);
		fprintf(fp,"����X:%d\n",mid[i].magic[49]);
		fprintf(fp,"����Y:%d\n",mid[i].magic[50]);
		fprintf(fp,"����Z:%d\n",mid[i].magic[51]);
		
		
		fprintf(fp,"������a:%d %d\n",mid[i].item[0][0],mid[i].item[0][1]);
		fprintf(fp,"������b:%d %d\n",mid[i].item[1][0],mid[i].item[1][1]);
		fprintf(fp,"������c:%d %d\n",mid[i].item[2][0],mid[i].item[2][1]);
		fprintf(fp,"������d:%d %d\n",mid[i].item[3][0],mid[i].item[3][1]);
		fprintf(fp,"������e:%d %d\n",mid[i].item[4][0],mid[i].item[4][1]);
		fprintf(fp,"������f:%d %d\n",mid[i].item[5][0],mid[i].item[5][1]);
		fprintf(fp,"������g:%d %d\n",mid[i].item[6][0],mid[i].item[6][1]);
		fprintf(fp,"������h:%d %d\n",mid[i].item[7][0],mid[i].item[7][1]);
		fprintf(fp,"������i:%d %d\n",mid[i].item[8][0],mid[i].item[8][1]);
		fprintf(fp,"������j:%d %d\n",mid[i].item[9][0],mid[i].item[9][1]);
		fprintf(fp,"������k:%d %d\n",mid[i].item[10][0],mid[i].item[10][1]);
		fprintf(fp,"������l:%d %d\n",mid[i].item[11][0],mid[i].item[11][1]);
		fprintf(fp,"������m:%d %d\n",mid[i].item[12][0],mid[i].item[12][1]);
		fprintf(fp,"������n:%d %d\n",mid[i].item[13][0],mid[i].item[13][1]);
		fprintf(fp,"������o:%d %d\n",mid[i].item[14][0],mid[i].item[14][1]);
		fprintf(fp,"������p:%d %d\n",mid[i].item[15][0],mid[i].item[15][1]);
		fprintf(fp,"������q:%d %d\n",mid[i].item[16][0],mid[i].item[16][1]);
		fprintf(fp,"������r:%d %d\n",mid[i].item[17][0],mid[i].item[17][1]);
		fprintf(fp,"������s:%d %d\n",mid[i].item[18][0],mid[i].item[18][1]);
		fprintf(fp,"������t:%d %d\n",mid[i].item[19][0],mid[i].item[19][1]);
		fprintf(fp,"������u:%d %d\n",mid[i].item[20][0],mid[i].item[20][1]);
		fprintf(fp,"������v:%d %d\n",mid[i].item[21][0],mid[i].item[21][1]);
		fprintf(fp,"������w:%d %d\n",mid[i].item[22][0],mid[i].item[22][1]);
		fprintf(fp,"������x:%d %d\n",mid[i].item[23][0],mid[i].item[23][1]);
		fprintf(fp,"������y:%d %d\n",mid[i].item[24][0],mid[i].item[24][1]);
		fprintf(fp,"������z:%d %d\n",mid[i].item[25][0],mid[i].item[25][1]);
		fprintf(fp,"}\n");
		
	}
	fclose(fp);
	LeaveCriticalSection(&save);
	//   frecnum=0;
}

void fwrite2(){
	
	//npc();
	struct tm *systime; 
	time_t t;
	t = time(NULL);
	systime = localtime(&t);
	struct tm *clock;
	time_t current;						
	time(& current); //���� �ð��� ��� ���� �Լ�							
	clock=localtime(& current); 
	char filename[50];
	sprintf(filename,"%d��%d��%d��%d��.txt",systime->tm_mon+1,systime->tm_mday,clock->tm_hour,clock->tm_min);
	
	EnterCriticalSection(&save);
	FILE *fp;
	fp=fopen(filename,"w");
	fseek(fp,0,SEEK_SET);
	for(int i=0; i < frecnum; i++)
		// if(mid[i].hakbun != 0)  ���̵� ������ �ʿ䰡 ���� ������ �ʿ����
	{
		fprintf(fp,"{\n");
		fprintf(fp,"���̵�:%s\n",mid[i].id);
		fprintf(fp,"��й�ȣ:%s\n",mid[i].pass);
		fprintf(fp,"����:%s\n",mid[i].job);
		fprintf(fp,"�±޹�ȣ:%d\n",mid[i].s_number);
		fprintf(fp,"����:%d\n",mid[i].level);
		fprintf(fp,"ü��:%u\n",mid[i].hel);
		fprintf(fp,"����:%u\n",mid[i].mana);
		fprintf(fp,"�ִ�ü��:%u\n",mid[i].max_hel);
		fprintf(fp,"�ִ븶��:%u\n",mid[i].max_mana);
		fprintf(fp,"����ġ:%u\n",mid[i].exp);
		fprintf(fp,"�ʿ����ġ:%u\n",mid[i].need_exp);
		fprintf(fp,"��:%u\n",mid[i].money);
		fprintf(fp,"��ǥX:%d\n",mid[i].map_x);
		fprintf(fp,"��ǥY:%d\n",mid[i].map_y);
		//fprintf(fp,"���̸�:%s\n",mid[i].map);
		fprintf(fp,"��:%d\n",mid[i].him);
		fprintf(fp,"��:%d\n",mid[i].min);
		fprintf(fp,"��:%d\n",mid[i].ji);
		fprintf(fp,"������:%d\n",mid[i].thread);
		fprintf(fp,"����:%d\n",mid[i].banghyang);
		fprintf(fp,"�Ӹ����:%d\n",mid[i].head);
		fprintf(fp,"�Ӹ�����:%d\n",mid[i].headcolor);
		fprintf(fp,"��:%d\n",mid[i].dress);
		fprintf(fp,"�ʻ���:%d\n",mid[i].dresscolor);
		fprintf(fp,"����:%d\n",mid[i].sword);
		fprintf(fp,"�������:%d\n",mid[i].swordcolor);
		fprintf(fp,"����:%d\n",mid[i].bangpae);
		fprintf(fp,"���л���:%d\n",mid[i].bangpaecolor);
		fprintf(fp,"����:%d\n",mid[i].head_gear);
		fprintf(fp,"����1:%d\n",mid[i].ring[0]);
		fprintf(fp,"����2:%d\n",mid[i].ring[1]);
		fprintf(fp,"�Ͱ���1:%d\n",mid[i].earing[0]);
		fprintf(fp,"�Ͱ���2:%d\n",mid[i].earing[1]);
		fprintf(fp,"�ʹ�ȣ:%d\n",mid[i].realmap);
		//fprintf(fp,"������:%d\n",mid[i].realmap);
		fprintf(fp,"����a:%d\n",mid[i].magic[0]);
		fprintf(fp,"����b:%d\n",mid[i].magic[1]);
		fprintf(fp,"����c:%d\n",mid[i].magic[2]);
		fprintf(fp,"����d:%d\n",mid[i].magic[3]);
		fprintf(fp,"����e:%d\n",mid[i].magic[4]);
		fprintf(fp,"����f:%d\n",mid[i].magic[5]);
		fprintf(fp,"����g:%d\n",mid[i].magic[6]);
		fprintf(fp,"����h:%d\n",mid[i].magic[7]);
		fprintf(fp,"����i:%d\n",mid[i].magic[8]);
		fprintf(fp,"����j:%d\n",mid[i].magic[9]);
		fprintf(fp,"����k:%d\n",mid[i].magic[10]);
		fprintf(fp,"����l:%d\n",mid[i].magic[11]);
		fprintf(fp,"����m:%d\n",mid[i].magic[12]);
		fprintf(fp,"����n:%d\n",mid[i].magic[13]);
		fprintf(fp,"����o:%d\n",mid[i].magic[14]);
		fprintf(fp,"����p:%d\n",mid[i].magic[15]);
		fprintf(fp,"����q:%d\n",mid[i].magic[16]);
		fprintf(fp,"����r:%d\n",mid[i].magic[17]);
		fprintf(fp,"����s:%d\n",mid[i].magic[18]);
		fprintf(fp,"����t:%d\n",mid[i].magic[19]);
		fprintf(fp,"����u:%d\n",mid[i].magic[20]);
		fprintf(fp,"����v:%d\n",mid[i].magic[21]);
		fprintf(fp,"����w:%d\n",mid[i].magic[22]);
		fprintf(fp,"����x:%d\n",mid[i].magic[23]);
		fprintf(fp,"����y:%d\n",mid[i].magic[24]);
		fprintf(fp,"����z:%d\n",mid[i].magic[25]);
		fprintf(fp,"����A:%d\n",mid[i].magic[26]);
		fprintf(fp,"����B:%d\n",mid[i].magic[27]);
		fprintf(fp,"����C:%d\n",mid[i].magic[28]);
		fprintf(fp,"����D:%d\n",mid[i].magic[29]);
		fprintf(fp,"����E:%d\n",mid[i].magic[30]);
		fprintf(fp,"����F:%d\n",mid[i].magic[31]);
		fprintf(fp,"����G:%d\n",mid[i].magic[32]);
		fprintf(fp,"����H:%d\n",mid[i].magic[33]);
		fprintf(fp,"����I:%d\n",mid[i].magic[34]);
		fprintf(fp,"����J:%d\n",mid[i].magic[35]);
		fprintf(fp,"����K:%d\n",mid[i].magic[36]);
		fprintf(fp,"����L:%d\n",mid[i].magic[37]);
		fprintf(fp,"����M:%d\n",mid[i].magic[38]);
		fprintf(fp,"����N:%d\n",mid[i].magic[39]);
		fprintf(fp,"����O:%d\n",mid[i].magic[40]);
		fprintf(fp,"����P:%d\n",mid[i].magic[41]);
		fprintf(fp,"����Q:%d\n",mid[i].magic[42]);
		fprintf(fp,"����R:%d\n",mid[i].magic[43]);
		fprintf(fp,"����S:%d\n",mid[i].magic[44]);
		fprintf(fp,"����T:%d\n",mid[i].magic[45]);
		fprintf(fp,"����U:%d\n",mid[i].magic[46]);
		fprintf(fp,"����V:%d\n",mid[i].magic[47]);
		fprintf(fp,"����W:%d\n",mid[i].magic[48]);
		fprintf(fp,"����X:%d\n",mid[i].magic[49]);
		fprintf(fp,"����Y:%d\n",mid[i].magic[50]);
		fprintf(fp,"����Z:%d\n",mid[i].magic[51]);
		
		
		fprintf(fp,"������a:%d %d\n",mid[i].item[0][0],mid[i].item[0][1]);
		fprintf(fp,"������b:%d %d\n",mid[i].item[1][0],mid[i].item[1][1]);
		fprintf(fp,"������c:%d %d\n",mid[i].item[2][0],mid[i].item[2][1]);
		fprintf(fp,"������d:%d %d\n",mid[i].item[3][0],mid[i].item[3][1]);
		fprintf(fp,"������e:%d %d\n",mid[i].item[4][0],mid[i].item[4][1]);
		fprintf(fp,"������f:%d %d\n",mid[i].item[5][0],mid[i].item[5][1]);
		fprintf(fp,"������g:%d %d\n",mid[i].item[6][0],mid[i].item[6][1]);
		fprintf(fp,"������h:%d %d\n",mid[i].item[7][0],mid[i].item[7][1]);
		fprintf(fp,"������i:%d %d\n",mid[i].item[8][0],mid[i].item[8][1]);
		fprintf(fp,"������j:%d %d\n",mid[i].item[9][0],mid[i].item[9][1]);
		fprintf(fp,"������k:%d %d\n",mid[i].item[10][0],mid[i].item[10][1]);
		fprintf(fp,"������l:%d %d\n",mid[i].item[11][0],mid[i].item[11][1]);
		fprintf(fp,"������m:%d %d\n",mid[i].item[12][0],mid[i].item[12][1]);
		fprintf(fp,"������n:%d %d\n",mid[i].item[13][0],mid[i].item[13][1]);
		fprintf(fp,"������o:%d %d\n",mid[i].item[14][0],mid[i].item[14][1]);
		fprintf(fp,"������p:%d %d\n",mid[i].item[15][0],mid[i].item[15][1]);
		fprintf(fp,"������q:%d %d\n",mid[i].item[16][0],mid[i].item[16][1]);
		fprintf(fp,"������r:%d %d\n",mid[i].item[17][0],mid[i].item[17][1]);
		fprintf(fp,"������s:%d %d\n",mid[i].item[18][0],mid[i].item[18][1]);
		fprintf(fp,"������t:%d %d\n",mid[i].item[19][0],mid[i].item[19][1]);
		fprintf(fp,"������u:%d %d\n",mid[i].item[20][0],mid[i].item[20][1]);
		fprintf(fp,"������v:%d %d\n",mid[i].item[21][0],mid[i].item[21][1]);
		fprintf(fp,"������w:%d %d\n",mid[i].item[22][0],mid[i].item[22][1]);
		fprintf(fp,"������x:%d %d\n",mid[i].item[23][0],mid[i].item[23][1]);
		fprintf(fp,"������y:%d %d\n",mid[i].item[24][0],mid[i].item[24][1]);
		fprintf(fp,"������z:%d %d\n",mid[i].item[25][0],mid[i].item[25][1]);
		fprintf(fp,"}\n");
		
	}
	fclose(fp);
	LeaveCriticalSection(&save);
}

void dont_move_save(){
	
	//npc();
	FILE *fp;
	fp=fopen("dontmove.txt","w");
	fseek(fp,0,SEEK_SET);
	for(int k=0;k<MAXMAP;k++)
	{
		
		if(taijimap[k].dont_move_count!=0)
		{
			for(int i=0; i < taijimap[k].dont_move_count; i++)
			{
				fprintf(fp,"{\n");
				fprintf(fp,"�ʹ�ȣ:%d\n",k);
				fprintf(fp,"���̸�:%s\n",taijimap[k].name);
				fprintf(fp,"x��ǥ:%d\n",taijimap[k].dont_move_x[i]);
				fprintf(fp,"y��ǥ:%d\n",taijimap[k].dont_move_y[i]);
				fprintf(fp,"}\n");
			}
		}
	}
	fclose(fp);
	
}

void dont_rezen_save(){
	
	//npc();
	FILE *fp;
	fp=fopen("dontrezen.txt","w");
	fseek(fp,0,SEEK_SET);
	for(int k=0;k<MAXMAP;k++)
	{
		
		if(taijimap[k].dont_rezen_count!=0)
		{
			for(int i=0; i < taijimap[k].dont_rezen_count; i++)
			{
				fprintf(fp,"{\n");
				fprintf(fp,"�ʹ�ȣ:%d\n",k);
				fprintf(fp,"���̸�:%s\n",taijimap[k].name);
				fprintf(fp,"x��ǥ:%d\n",taijimap[k].dont_rezen_x[i]);
				fprintf(fp,"y��ǥ:%d\n",taijimap[k].dont_rezen_y[i]);
				fprintf(fp,"}\n");
			}
		}
	}
	fclose(fp);
	
}


void test_write(){
	
	//npc();
	FILE *fp;
	fp=fopen("levelup.txt","w");
	fseek(fp,0,SEEK_SET);
	for(int k=0;k<255;k++)
	{
		
		
		fprintf(fp,"{\n");
		fprintf(fp,"����:%d\n",k);
		fprintf(fp,"�ʿ����ġ:%d\n",k*1000);
		fprintf(fp,"���ü��:%d\n",k*2000);
		fprintf(fp,"��¸���:%d\n",k*1000);
		fprintf(fp,"}\n");
		
	}
	fclose(fp);
	
}

void log(char *id,char *ip,char *msg)
{
	struct tm *systime; 
	time_t t;
	t = time(NULL);
	systime = localtime(&t);
	struct tm *clock;
	time_t current;
	
	
	
	
	time(& current); //���� �ð��� ��� ���� �Լ�
	
	clock=localtime(& current); //���� �ð��� ��,��,�ʷ� ���� �ϴ� �ռ�
	
	
	//npc();
	FILE *fp;
	fp=fopen("log.txt","a");
	
	
	fprintf(fp,"%.2d/%.2d/%.2d %.2d�� %.2d�� %.2d�� %10s %s %s\n",systime->tm_mon+1,systime->tm_mday,systime->tm_year + 1900,
		clock->tm_hour,clock->tm_min,clock->tm_sec,id,ip,msg);
	
	
	fclose(fp);
	//   frecnum=0;
}


void threadzero(){       // ��� ���������� �����带 0 ���� �ʱ�ȭ
	
	for(int i=0; i < frecnum-1; i++)
		// if(mid[i].hakbun != 0)  ���̵� ������ �ʿ䰡 ���� ������ �ʿ����
	{
		mid2[i].thread=0;
	}
	
	
}

int search_data(char *user){
	
	int j=0;
	char buff2[100];
	strncpy(buff2,user,strlen(user));
	buff2[(strlen(user))]=NULL;
   	
	char buff[100];
	for(int i=0; i < frecnum; i++) //�ѹ� read�� �ؾ߸��� 
	{
		
		// printf("%d��° id :%s\n",i,mid[i].id);
		if(strcmp(buff2,mid2[i].id)==0)
		{
			// printf("�̹� �ִ� ���̵���\n");
		}
		for(int k=0; k < strlen(mid2[i].id); k++)
		{
			strncpy(buff+k,mid2[i].id+k,2);
		}
		buff[strlen(mid2[i].id)]=NULL;
		// // printf("buff�� �� : %s, mid�� �� : %s buff2�� �� :%s  \n ",buff,mid[i].id,buff2);
		
		int kkkk = strcmp(buff2,buff);
		if(kkkk==0)return 1;
		//// printf(" j�� �� : %d \n",j);
		//// printf(" test[%d]�� mid[%d] �� (��:1) :",i,i); 	
		//if(user[i]==mid[i].id[i]) j++; else j=999;
		
		//   if(j==strlen(user)) return 1;
		//  	int j=0;
								
	}
	return 0;
}

int search_data2(char *user,char *pass){  // �̾��ϱ�� ��ġ ����Ÿ
	
	int j=0;
	char buff2[20];
	strncpy(buff2,user,strlen(user));
	buff2[(strlen(user))]=NULL;
   	
	char buff[20];
	for(int i=0; i < frecnum; i++) //�ѹ� read�� �ؾ߸��� 
	{
		if(strcmp(user,mid2[i].id)==0)
		{
			if(strcmp(pass,mid2[i].pass)==0)
			{
				return i+1;
			}
		}
	}
	return 0;
	   
	
	
	
}


/* ȭ�� �б� �Լ�, �ش� ������ �������� �ʴ°��� ���ϻ���.
���ϳ��� ��� ���ڵ带 �޸𸮷� �о� ����. */
void file_read()        
{
	
	EnterCriticalSection(&save);
	
	int frec_imsi=0;
	
	
	FILE *fp;
	fp=fopen("chr.txt","a");
	fclose(fp);
	fp=fopen("chr.txt","r");
	fseek(fp,0,SEEK_SET);
	
	{
		while(!feof(fp)){
			fscanf(fp,"{\n");
			fscanf(fp,"���̵�:%s\n",mid[frec_imsi].id);
			fscanf(fp,"��й�ȣ:%s\n",mid[frec_imsi].pass);
			fscanf(fp,"����:%s\n",mid[frec_imsi].job);
			fscanf(fp,"�±޹�ȣ:%d\n",&mid[frec_imsi].s_number);
			fscanf(fp,"����:%d\n",&mid[frec_imsi].level);
			fscanf(fp,"ü��:%u\n",&mid[frec_imsi].hel);
			fscanf(fp,"����:%u\n",&mid[frec_imsi].mana);
			fscanf(fp,"�ִ�ü��:%u\n",&mid[frec_imsi].max_hel);
			fscanf(fp,"�ִ븶��:%u\n",&mid[frec_imsi].max_mana);
			fscanf(fp,"����ġ:%u\n",&mid[frec_imsi].exp);
			fscanf(fp,"�ʿ����ġ:%u\n",&mid[frec_imsi].need_exp);
			fscanf(fp,"��:%u\n",&mid[frec_imsi].money);
			fscanf(fp,"��ǥX:%d\n",&mid[frec_imsi].map_x);
			fscanf(fp,"��ǥY:%d\n",&mid[frec_imsi].map_y);
			//fscanf(fp,"���̸�:%s\n",mid[frec_imsi].map);
			fscanf(fp,"��:%d\n",&mid[frec_imsi].him);
			fscanf(fp,"��:%d\n",&mid[frec_imsi].min);
			fscanf(fp,"��:%d\n",&mid[frec_imsi].ji);
			fscanf(fp,"������:%d\n",&mid[frec_imsi].thread);
			fscanf(fp,"����:%d\n",&mid[frec_imsi].banghyang);
			fscanf(fp,"�Ӹ����:%d\n",&mid[frec_imsi].head);
			fscanf(fp,"�Ӹ�����:%d\n",&mid[frec_imsi].headcolor);
			fscanf(fp,"��:%d\n",&mid[frec_imsi].dress);
			fscanf(fp,"�ʻ���:%d\n",&mid[frec_imsi].dresscolor);
			fscanf(fp,"����:%d\n",&mid[frec_imsi].sword);
			fscanf(fp,"�������:%d\n",&mid[frec_imsi].swordcolor);
			fscanf(fp,"����:%d\n",&mid[frec_imsi].bangpae);
			fscanf(fp,"���л���:%d\n",&mid[frec_imsi].bangpaecolor);
			fscanf(fp,"����:%d\n",&mid[frec_imsi].head_gear);
			fscanf(fp,"����1:%d\n",&mid[frec_imsi].ring[0]);
			fscanf(fp,"����2:%d\n",&mid[frec_imsi].ring[1]);
			fscanf(fp,"�Ͱ���1:%d\n",&mid[frec_imsi].earing[0]);
			fscanf(fp,"�Ͱ���2:%d\n",&mid[frec_imsi].earing[1]);
			fscanf(fp,"�ʹ�ȣ:%d\n",&mid[frec_imsi].realmap);
			fscanf(fp,"����a:%d\n",&mid[frec_imsi].magic[0]);
			fscanf(fp,"����b:%d\n",&mid[frec_imsi].magic[1]);
			fscanf(fp,"����c:%d\n",&mid[frec_imsi].magic[2]);
			fscanf(fp,"����d:%d\n",&mid[frec_imsi].magic[3]);
			fscanf(fp,"����e:%d\n",&mid[frec_imsi].magic[4]);
			fscanf(fp,"����f:%d\n",&mid[frec_imsi].magic[5]);
			fscanf(fp,"����g:%d\n",&mid[frec_imsi].magic[6]);
			fscanf(fp,"����h:%d\n",&mid[frec_imsi].magic[7]);
			fscanf(fp,"����i:%d\n",&mid[frec_imsi].magic[8]);
			fscanf(fp,"����j:%d\n",&mid[frec_imsi].magic[9]);
			fscanf(fp,"����k:%d\n",&mid[frec_imsi].magic[10]);
			fscanf(fp,"����l:%d\n",&mid[frec_imsi].magic[11]);
			fscanf(fp,"����m:%d\n",&mid[frec_imsi].magic[12]);
			fscanf(fp,"����n:%d\n",&mid[frec_imsi].magic[13]);
			fscanf(fp,"����o:%d\n",&mid[frec_imsi].magic[14]);
			fscanf(fp,"����p:%d\n",&mid[frec_imsi].magic[15]);
			fscanf(fp,"����q:%d\n",&mid[frec_imsi].magic[16]);
			fscanf(fp,"����r:%d\n",&mid[frec_imsi].magic[17]);
			fscanf(fp,"����s:%d\n",&mid[frec_imsi].magic[18]);
			fscanf(fp,"����t:%d\n",&mid[frec_imsi].magic[19]);
			fscanf(fp,"����u:%d\n",&mid[frec_imsi].magic[20]);
			fscanf(fp,"����v:%d\n",&mid[frec_imsi].magic[21]);
			fscanf(fp,"����w:%d\n",&mid[frec_imsi].magic[22]);
			fscanf(fp,"����x:%d\n",&mid[frec_imsi].magic[23]);
			fscanf(fp,"����y:%d\n",&mid[frec_imsi].magic[24]);
			fscanf(fp,"����z:%d\n",&mid[frec_imsi].magic[25]);
			fscanf(fp,"����A:%d\n",&mid[frec_imsi].magic[26]);
			fscanf(fp,"����B:%d\n",&mid[frec_imsi].magic[27]);
			fscanf(fp,"����C:%d\n",&mid[frec_imsi].magic[28]);
			fscanf(fp,"����D:%d\n",&mid[frec_imsi].magic[29]);
			fscanf(fp,"����E:%d\n",&mid[frec_imsi].magic[30]);
			fscanf(fp,"����F:%d\n",&mid[frec_imsi].magic[31]);
			fscanf(fp,"����G:%d\n",&mid[frec_imsi].magic[32]);
			fscanf(fp,"����H:%d\n",&mid[frec_imsi].magic[33]);
			fscanf(fp,"����I:%d\n",&mid[frec_imsi].magic[34]);
			fscanf(fp,"����J:%d\n",&mid[frec_imsi].magic[35]);
			fscanf(fp,"����K:%d\n",&mid[frec_imsi].magic[36]);
			fscanf(fp,"����L:%d\n",&mid[frec_imsi].magic[37]);
			fscanf(fp,"����M:%d\n",&mid[frec_imsi].magic[38]);
			fscanf(fp,"����N:%d\n",&mid[frec_imsi].magic[39]);
			fscanf(fp,"����O:%d\n",&mid[frec_imsi].magic[40]);
			fscanf(fp,"����P:%d\n",&mid[frec_imsi].magic[41]);
			fscanf(fp,"����Q:%d\n",&mid[frec_imsi].magic[42]);
			fscanf(fp,"����R:%d\n",&mid[frec_imsi].magic[43]);
			fscanf(fp,"����S:%d\n",&mid[frec_imsi].magic[44]);
			fscanf(fp,"����T:%d\n",&mid[frec_imsi].magic[45]);
			fscanf(fp,"����U:%d\n",&mid[frec_imsi].magic[46]);
			fscanf(fp,"����V:%d\n",&mid[frec_imsi].magic[47]);
			fscanf(fp,"����W:%d\n",&mid[frec_imsi].magic[48]);
			fscanf(fp,"����X:%d\n",&mid[frec_imsi].magic[49]);
			fscanf(fp,"����Y:%d\n",&mid[frec_imsi].magic[50]);
			fscanf(fp,"����Z:%d\n",&mid[frec_imsi].magic[51]);
			fscanf(fp,"������a:%d %d\n",&mid[frec_imsi].item[0][0],&mid[frec_imsi].item[0][1]);
			fscanf(fp,"������b:%d %d\n",&mid[frec_imsi].item[1][0],&mid[frec_imsi].item[1][1]);
			fscanf(fp,"������c:%d %d\n",&mid[frec_imsi].item[2][0],&mid[frec_imsi].item[2][1]);
			fscanf(fp,"������d:%d %d\n",&mid[frec_imsi].item[3][0],&mid[frec_imsi].item[3][1]);
			fscanf(fp,"������e:%d %d\n",&mid[frec_imsi].item[4][0],&mid[frec_imsi].item[4][1]);
			fscanf(fp,"������f:%d %d\n",&mid[frec_imsi].item[5][0],&mid[frec_imsi].item[5][1]);
			fscanf(fp,"������g:%d %d\n",&mid[frec_imsi].item[6][0],&mid[frec_imsi].item[6][1]);
			fscanf(fp,"������h:%d %d\n",&mid[frec_imsi].item[7][0],&mid[frec_imsi].item[7][1]);
			fscanf(fp,"������i:%d %d\n",&mid[frec_imsi].item[8][0],&mid[frec_imsi].item[8][1]);
			fscanf(fp,"������j:%d %d\n",&mid[frec_imsi].item[9][0],&mid[frec_imsi].item[9][1]);
			fscanf(fp,"������k:%d %d\n",&mid[frec_imsi].item[10][0],&mid[frec_imsi].item[10][1]);
			fscanf(fp,"������l:%d %d\n",&mid[frec_imsi].item[11][0],&mid[frec_imsi].item[11][1]);
			fscanf(fp,"������m:%d %d\n",&mid[frec_imsi].item[12][0],&mid[frec_imsi].item[12][1]);
			fscanf(fp,"������n:%d %d\n",&mid[frec_imsi].item[13][0],&mid[frec_imsi].item[13][1]);
			fscanf(fp,"������o:%d %d\n",&mid[frec_imsi].item[14][0],&mid[frec_imsi].item[14][1]);
			fscanf(fp,"������p:%d %d\n",&mid[frec_imsi].item[15][0],&mid[frec_imsi].item[15][1]);
			fscanf(fp,"������q:%d %d\n",&mid[frec_imsi].item[16][0],&mid[frec_imsi].item[16][1]);
			fscanf(fp,"������r:%d %d\n",&mid[frec_imsi].item[17][0],&mid[frec_imsi].item[17][1]);
			fscanf(fp,"������s:%d %d\n",&mid[frec_imsi].item[18][0],&mid[frec_imsi].item[18][1]);
			fscanf(fp,"������t:%d %d\n",&mid[frec_imsi].item[19][0],&mid[frec_imsi].item[19][1]);
			fscanf(fp,"������u:%d %d\n",&mid[frec_imsi].item[20][0],&mid[frec_imsi].item[20][1]);
			fscanf(fp,"������v:%d %d\n",&mid[frec_imsi].item[21][0],&mid[frec_imsi].item[21][1]);
			fscanf(fp,"������w:%d %d\n",&mid[frec_imsi].item[22][0],&mid[frec_imsi].item[22][1]);
			fscanf(fp,"������x:%d %d\n",&mid[frec_imsi].item[23][0],&mid[frec_imsi].item[23][1]);
			fscanf(fp,"������y:%d %d\n",&mid[frec_imsi].item[24][0],&mid[frec_imsi].item[24][1]);
			fscanf(fp,"������z:%d %d\n",&mid[frec_imsi].item[25][0],&mid[frec_imsi].item[25][1]);
			fscanf(fp,"}\n");
			
			
			/*       fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",mid[frecnum].id,mid[frecnum].pass,&mid[frecnum].level,
			&mid[frecnum].hel,&mid[frecnum].mana,&mid[frecnum].max_hel,&mid[frecnum].max_mana,&mid[frecnum].exp,&mid[frecnum].money,
			&mid[frecnum].map_x,&mid[frecnum].map_y,mid[frecnum].map,&mid[frecnum].him,
			&mid[frecnum].min,&mid[frecnum].ji,&mid[frecnum].thread,&mid[frecnum].banghyang,
			&mid[frecnum].head,&mid[frecnum].headcolor,&mid[frecnum].dress,&mid[frecnum].dresscolor,
			&mid[frecnum].sword,&mid[frecnum].swordcolor,&mid[frecnum].bangpae,&mid[frecnum].bangpaecolor,
			&mid[frecnum].realmap); */
			
			frec_imsi += 1;
		}
		frecnum=frec_imsi;
	}
	fclose(fp);
	for(int i=0;i<frecnum;i++)
	{
		mid2[i]=mid[i];
	}
	
	LeaveCriticalSection(&save);
}

void file_read_default()        
{
	
	
	FILE *fp;
	fp=fopen("default.txt","a");
	fclose(fp);
	fp=fopen("default.txt","r");
	fseek(fp,0,SEEK_SET);
	
	{
		fscanf(fp,"{\n");
		fscanf(fp,"���̵�:%s\n",deflt.id);
		fscanf(fp,"��й�ȣ:%s\n",deflt.pass);
		fscanf(fp,"����:%s\n",deflt.job);
		fscanf(fp,"�±޹�ȣ:%d\n",&deflt.s_number);
		fscanf(fp,"����:%d\n",&deflt.level);
		fscanf(fp,"ü��:%u\n",&deflt.hel);
		fscanf(fp,"����:%u\n",&deflt.mana);
		fscanf(fp,"�ִ�ü��:%u\n",&deflt.max_hel);
		fscanf(fp,"�ִ븶��:%u\n",&deflt.max_mana);
		fscanf(fp,"����ġ:%u\n",&deflt.exp);
		fscanf(fp,"�ʿ����ġ:%u\n",&deflt.need_exp);
		fscanf(fp,"��:%u\n",&deflt.money);
		fscanf(fp,"��ǥX:%d\n",&deflt.map_x);
		fscanf(fp,"��ǥY:%d\n",&deflt.map_y);
		//fscanf(fp,"���̸�:%s\n",deflt.map);
		fscanf(fp,"��:%d\n",&deflt.him);
		fscanf(fp,"��:%d\n",&deflt.min);
		fscanf(fp,"��:%d\n",&deflt.ji);
		fscanf(fp,"������:%d\n",&deflt.thread);
		fscanf(fp,"����:%d\n",&deflt.banghyang);
		fscanf(fp,"�Ӹ����:%d\n",&deflt.head);
		fscanf(fp,"�Ӹ�����:%d\n",&deflt.headcolor);
		fscanf(fp,"��:%d\n",&deflt.dress);
		fscanf(fp,"�ʻ���:%d\n",&deflt.dresscolor);
		fscanf(fp,"����:%d\n",&deflt.sword);
		fscanf(fp,"�������:%d\n",&deflt.swordcolor);
		fscanf(fp,"����:%d\n",&deflt.bangpae);
		fscanf(fp,"���л���:%d\n",&deflt.bangpaecolor);
		fscanf(fp,"����:%d\n",&deflt.head_gear);
		fscanf(fp,"����1:%d\n",&deflt.ring[0]);
		fscanf(fp,"����2:%d\n",&deflt.ring[1]);
		fscanf(fp,"�Ͱ���1:%d\n",&deflt.earing[0]);
		fscanf(fp,"�Ͱ���2:%d\n",&deflt.earing[1]);
		fscanf(fp,"�ʹ�ȣ:%d\n",&deflt.realmap);
		fscanf(fp,"����a:%d\n",&deflt.magic[0]);
		fscanf(fp,"����b:%d\n",&deflt.magic[1]);
		fscanf(fp,"����c:%d\n",&deflt.magic[2]);
		fscanf(fp,"����d:%d\n",&deflt.magic[3]);
		fscanf(fp,"����e:%d\n",&deflt.magic[4]);
		fscanf(fp,"����f:%d\n",&deflt.magic[5]);
		fscanf(fp,"����g:%d\n",&deflt.magic[6]);
		fscanf(fp,"����h:%d\n",&deflt.magic[7]);
		fscanf(fp,"����i:%d\n",&deflt.magic[8]);
		fscanf(fp,"����j:%d\n",&deflt.magic[9]);
		fscanf(fp,"����k:%d\n",&deflt.magic[10]);
		fscanf(fp,"����l:%d\n",&deflt.magic[11]);
		fscanf(fp,"����m:%d\n",&deflt.magic[12]);
		fscanf(fp,"����n:%d\n",&deflt.magic[13]);
		fscanf(fp,"����o:%d\n",&deflt.magic[14]);
		fscanf(fp,"����p:%d\n",&deflt.magic[15]);
		fscanf(fp,"����q:%d\n",&deflt.magic[16]);
		fscanf(fp,"����r:%d\n",&deflt.magic[17]);
		fscanf(fp,"����s:%d\n",&deflt.magic[18]);
		fscanf(fp,"����t:%d\n",&deflt.magic[19]);
		fscanf(fp,"����u:%d\n",&deflt.magic[20]);
		fscanf(fp,"����v:%d\n",&deflt.magic[21]);
		fscanf(fp,"����w:%d\n",&deflt.magic[22]);
		fscanf(fp,"����x:%d\n",&deflt.magic[23]);
		fscanf(fp,"����y:%d\n",&deflt.magic[24]);
		fscanf(fp,"����z:%d\n",&deflt.magic[25]);
		fscanf(fp,"����A:%d\n",&deflt.magic[26]);
		fscanf(fp,"����B:%d\n",&deflt.magic[27]);
		fscanf(fp,"����C:%d\n",&deflt.magic[28]);
		fscanf(fp,"����D:%d\n",&deflt.magic[29]);
		fscanf(fp,"����E:%d\n",&deflt.magic[30]);
		fscanf(fp,"����F:%d\n",&deflt.magic[31]);
		fscanf(fp,"����G:%d\n",&deflt.magic[32]);
		fscanf(fp,"����H:%d\n",&deflt.magic[33]);
		fscanf(fp,"����I:%d\n",&deflt.magic[34]);
		fscanf(fp,"����J:%d\n",&deflt.magic[35]);
		fscanf(fp,"����K:%d\n",&deflt.magic[36]);
		fscanf(fp,"����L:%d\n",&deflt.magic[37]);
		fscanf(fp,"����M:%d\n",&deflt.magic[38]);
		fscanf(fp,"����N:%d\n",&deflt.magic[39]);
		fscanf(fp,"����O:%d\n",&deflt.magic[40]);
		fscanf(fp,"����P:%d\n",&deflt.magic[41]);
		fscanf(fp,"����Q:%d\n",&deflt.magic[42]);
		fscanf(fp,"����R:%d\n",&deflt.magic[43]);
		fscanf(fp,"����S:%d\n",&deflt.magic[44]);
		fscanf(fp,"����T:%d\n",&deflt.magic[45]);
		fscanf(fp,"����U:%d\n",&deflt.magic[46]);
		fscanf(fp,"����V:%d\n",&deflt.magic[47]);
		fscanf(fp,"����W:%d\n",&deflt.magic[48]);
		fscanf(fp,"����X:%d\n",&deflt.magic[49]);
		fscanf(fp,"����Y:%d\n",&deflt.magic[50]);
		fscanf(fp,"����Z:%d\n",&deflt.magic[51]);
		fscanf(fp,"������a:%d %d\n",&deflt.item[0][0],&deflt.item[0][1]);
		fscanf(fp,"������b:%d %d\n",&deflt.item[1][0],&deflt.item[1][1]);
		fscanf(fp,"������c:%d %d\n",&deflt.item[2][0],&deflt.item[2][1]);
		fscanf(fp,"������d:%d %d\n",&deflt.item[3][0],&deflt.item[3][1]);
		fscanf(fp,"������e:%d %d\n",&deflt.item[4][0],&deflt.item[4][1]);
		fscanf(fp,"������f:%d %d\n",&deflt.item[5][0],&deflt.item[5][1]);
		fscanf(fp,"������g:%d %d\n",&deflt.item[6][0],&deflt.item[6][1]);
		fscanf(fp,"������h:%d %d\n",&deflt.item[7][0],&deflt.item[7][1]);
		fscanf(fp,"������i:%d %d\n",&deflt.item[8][0],&deflt.item[8][1]);
		fscanf(fp,"������j:%d %d\n",&deflt.item[9][0],&deflt.item[9][1]);
		fscanf(fp,"������k:%d %d\n",&deflt.item[10][0],&deflt.item[10][1]);
		fscanf(fp,"������l:%d %d\n",&deflt.item[11][0],&deflt.item[11][1]);
		fscanf(fp,"������m:%d %d\n",&deflt.item[12][0],&deflt.item[12][1]);
		fscanf(fp,"������n:%d %d\n",&deflt.item[13][0],&deflt.item[13][1]);
		fscanf(fp,"������o:%d %d\n",&deflt.item[14][0],&deflt.item[14][1]);
		fscanf(fp,"������p:%d %d\n",&deflt.item[15][0],&deflt.item[15][1]);
		fscanf(fp,"������q:%d %d\n",&deflt.item[16][0],&deflt.item[16][1]);
		fscanf(fp,"������r:%d %d\n",&deflt.item[17][0],&deflt.item[17][1]);
		fscanf(fp,"������s:%d %d\n",&deflt.item[18][0],&deflt.item[18][1]);
		fscanf(fp,"������t:%d %d\n",&deflt.item[19][0],&deflt.item[19][1]);
		fscanf(fp,"������u:%d %d\n",&deflt.item[20][0],&deflt.item[20][1]);
		fscanf(fp,"������v:%d %d\n",&deflt.item[21][0],&deflt.item[21][1]);
		fscanf(fp,"������w:%d %d\n",&deflt.item[22][0],&deflt.item[22][1]);
		fscanf(fp,"������x:%d %d\n",&deflt.item[23][0],&deflt.item[23][1]);
		fscanf(fp,"������y:%d %d\n",&deflt.item[24][0],&deflt.item[24][1]);
		fscanf(fp,"������z:%d %d\n",&deflt.item[25][0],&deflt.item[25][1]);
		fscanf(fp,"}\n");
		// printf("�����߰���\n");
		
		/*       fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",mid[frecnum].id,mid[frecnum].pass,&mid[frecnum].level,
		&mid[frecnum].hel,&mid[frecnum].mana,&mid[frecnum].max_hel,&mid[frecnum].max_mana,&mid[frecnum].exp,&mid[frecnum].money,
		&mid[frecnum].map_x,&mid[frecnum].map_y,mid[frecnum].map,&mid[frecnum].him,
		&mid[frecnum].min,&mid[frecnum].ji,&mid[frecnum].thread,&mid[frecnum].banghyang,
		&mid[frecnum].head,&mid[frecnum].headcolor,&mid[frecnum].dress,&mid[frecnum].dresscolor,
		&mid[frecnum].sword,&mid[frecnum].swordcolor,&mid[frecnum].bangpae,&mid[frecnum].bangpaecolor,
		&mid[frecnum].realmap); */
		
	}   fclose(fp);
}

void file_read_levelup()        
{
	
	
	FILE *fp;
	fp=fopen("levelup.txt","a");
	fclose(fp);
	fp=fopen("levelup.txt","r");
	fseek(fp,0,SEEK_SET);
	
	{
		for(int i=0;i<256;i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"����:%d\n",&level_up[i].level);
			fscanf(fp,"�ʿ����ġ:%d\n",&level_up[i].need_exp);
			fscanf(fp,"���ü��:%d\n",&level_up[i].heal_up);
			fscanf(fp,"��¸���:%u\n",&level_up[i].mana_up);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}

void file_read_junsa()        
{
	
	
	FILE *fp;
	fp=fopen("junsa.txt","a");
	fclose(fp);
	fp=fopen("junsa.txt","r");
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�ʿ䷹��:%d\n",&junsas[i].level);
			fscanf(fp,"������ȣ:%d\n",&junsas[i].magic_number);
			fscanf(fp,"�����̸�:%s\n",&junsas[i].magic_name);
			fscanf(fp,"�繰:%s\n",&junsas[i].magic_need_item);
			fscanf(fp,"�繰��ȣ:%d\n",&junsas[i].number_need_item);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}

void file_read_junsa2()        
{
	
	
	FILE *fp;
	fp=fopen("junsa2.txt","a");
	fclose(fp);
	fp=fopen("junsa2.txt","r");
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�±޹�ȣ:%d\n",&junsas2[i].number);
			fscanf(fp,"�±��� �Ҽ� �ִ� ����:%d\n",&junsas2[i].need_level);
			fscanf(fp,"�±޽� ��ġ�� ������:%s\n",&junsas2[i].need_item);
			fscanf(fp,"�±޽� ��ġ�� �����۹�ȣ:%d\n",&junsas2[i].need_item_number);
			fscanf(fp,"�±޽� �ϻ��ϴ� ������:%s\n",&junsas2[i].hasa_item);
			fscanf(fp,"�±޽� �ϻ��ϴ� �����۹�ȣ:%d\n",&junsas2[i].hasa_item_number);
			fscanf(fp,"�±޽� �ִ� Īȣ(����):%s\n",&junsas2[i].ching_ho);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}

void file_read_dojuk()        
{
	
	
	FILE *fp;
	fp=fopen("dojuk.txt","a");
	fclose(fp);
	fp=fopen("dojuk.txt","r");
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�ʿ䷹��:%d\n",&dojuks[i].level);
			fscanf(fp,"������ȣ:%d\n",&dojuks[i].magic_number);
			fscanf(fp,"�����̸�:%s\n",&dojuks[i].magic_name);
			fscanf(fp,"�繰:%s\n",&dojuks[i].magic_need_item);
			fscanf(fp,"�繰��ȣ:%d\n",&dojuks[i].number_need_item);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}

void file_read_dojuk2()        
{
	
	
	FILE *fp;
	fp=fopen("dojuk2.txt","a");
	fclose(fp);
	fp=fopen("dojuk2.txt","r");
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�±޹�ȣ:%d\n",&dojuks2[i].number);
			fscanf(fp,"�±��� �Ҽ� �ִ� ����:%d\n",&dojuks2[i].need_level);
			fscanf(fp,"�±޽� ��ġ�� ������:%s\n",&dojuks2[i].need_item);
			fscanf(fp,"�±޽� ��ġ�� �����۹�ȣ:%d\n",&dojuks2[i].need_item_number);
			fscanf(fp,"�±޽� �ϻ��ϴ� ������:%s\n",&dojuks2[i].hasa_item);
			fscanf(fp,"�±޽� �ϻ��ϴ� �����۹�ȣ:%d\n",&dojuks2[i].hasa_item_number);
			fscanf(fp,"�±޽� �ִ� Īȣ(����):%s\n",&dojuks2[i].ching_ho);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}

void file_read_soolsa()        
{
	
	
	FILE *fp;
	fp=fopen("soolsa.txt","a");
	fclose(fp);
	fp=fopen("soolsa.txt","r");
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�ʿ䷹��:%d\n",&soolsas[i].level);
			fscanf(fp,"������ȣ:%d\n",&soolsas[i].magic_number);
			fscanf(fp,"�����̸�:%s\n",&soolsas[i].magic_name);
			fscanf(fp,"�繰:%s\n",&soolsas[i].magic_need_item);
			fscanf(fp,"�繰��ȣ:%d\n",&soolsas[i].number_need_item);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}

void file_read_soolsa2()        
{
	
	
	FILE *fp;
	fp=fopen("soolsa2.txt","a");
	fclose(fp);
	fp=fopen("soolsa2.txt","r");
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�±޹�ȣ:%d\n",&soolsas2[i].number);
			fscanf(fp,"�±��� �Ҽ� �ִ� ����:%d\n",&soolsas2[i].need_level);
			fscanf(fp,"�±޽� ��ġ�� ������:%s\n",&soolsas2[i].need_item);
			fscanf(fp,"�±޽� ��ġ�� �����۹�ȣ:%d\n",&soolsas2[i].need_item_number);
			fscanf(fp,"�±޽� �ϻ��ϴ� ������:%s\n",&soolsas2[i].hasa_item);
			fscanf(fp,"�±޽� �ϻ��ϴ� �����۹�ȣ:%d\n",&soolsas2[i].hasa_item_number);
			fscanf(fp,"�±޽� �ִ� Īȣ(����):%s\n",&soolsas2[i].ching_ho);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}

void file_read_dosa()        
{
	
	
	FILE *fp;
	fp=fopen("dosa.txt","a");
	fclose(fp);
	fp=fopen("dosa.txt","r");
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�ʿ䷹��:%d\n",&dosas[i].level);
			fscanf(fp,"������ȣ:%d\n",&dosas[i].magic_number);
			fscanf(fp,"�����̸�:%s\n",&dosas[i].magic_name);
			fscanf(fp,"�繰:%s\n",&dosas[i].magic_need_item);
			fscanf(fp,"�繰��ȣ:%d\n",&dosas[i].number_need_item);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}

void file_read_ip()        
{
	
	
	FILE *fp;
	fp=fopen("ip.txt","a");
	fclose(fp);
	fp=fopen("ip.txt","r");
	char buffer[100];
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�޽���:%s\n",&buffer);
			fscanf(fp,"����IP:%s\n",&ips[i].ip_chadan);
			fscanf(fp,"}\n");
			ips_count++;
		}
		
	}   fclose(fp);
}

void file_read_dosa2()        
{
	
	
	FILE *fp;
	fp=fopen("dosa2.txt","a");
	fclose(fp);
	fp=fopen("dosa2.txt","r");
	fseek(fp,0,SEEK_SET);
	{
		for(int i=0;!feof(fp);i++)
		{
			fscanf(fp,"{\n");
			fscanf(fp,"�±޹�ȣ:%d\n",&dosas2[i].number);
			fscanf(fp,"�±��� �Ҽ� �ִ� ����:%d\n",&dosas2[i].need_level);
			fscanf(fp,"�±޽� ��ġ�� ������:%s\n",&dosas2[i].need_item);
			fscanf(fp,"�±޽� ��ġ�� �����۹�ȣ:%d\n",&dosas2[i].need_item_number);
			fscanf(fp,"�±޽� �ϻ��ϴ� ������:%s\n",&dosas2[i].hasa_item);
			fscanf(fp,"�±޽� �ϻ��ϴ� �����۹�ȣ:%d\n",&dosas2[i].hasa_item_number);
			fscanf(fp,"�±޽� �ִ� Īȣ(����):%s\n",&dosas2[i].ching_ho);
			fscanf(fp,"}\n");
		}
		
	}   fclose(fp);
}


int johap_count=0;
void file_read_johap()        
{
	
	
	FILE *fp;
	fp=fopen("johap.txt","a");
	fclose(fp);
	fp=fopen("johap.txt","r");
	int count=0;
	int j=0;
	char imsi_buffer[100];
	fseek(fp,0,SEEK_SET);
	{
		while(!feof(fp))
		{
			
			
			count=0;
			fscanf(fp,"{\n");
			fscanf(fp,"������ ������ ����:%d\n",&johap_st[j].count);			
			for(int i=0;i<johap_st[j].count;i++)
			{
				fscanf(fp,"������ ������(��ȣ):%d\n",&johap_st[j].p_item[i]);
				fscanf(fp,"������ ������(�̸�):%s\n",&imsi_buffer);
			}
			fscanf(fp,"������:%d\n",&johap_st[j].percent);
			fscanf(fp,"������ ���� ������(��ȣ):%d\n",&johap_st[j].n_item);
			fscanf(fp,"������ ���� ������(�̸�):%s\n",&imsi_buffer);
			fscanf(fp,"}\n");
			j++;
			johap_count++;
			
		}
	}
	
	
	fclose(fp);
	//printf("%d %d\n",johap_st[1].p_item[0],johap_st[1].p_item[1]);
}

void file_read_dontmove()        
{
	
	
	FILE *fp;
	fp=fopen("dontmove.txt","a");
	fclose(fp);
	fp=fopen("dontmove.txt","r");
	int mapnumber;
	char mapname[100];
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			fscanf(fp,"{\n");
			fscanf(fp,"�ʹ�ȣ:%d\n",&mapnumber);
			fscanf(fp,"���̸�:%s\n",mapname);
			fscanf(fp,"x��ǥ:%d\n",&taijimap[mapnumber].dont_move_x[taijimap[mapnumber].dont_move_count]);
			fscanf(fp,"y��ǥ:%d\n",&taijimap[mapnumber].dont_move_y[taijimap[mapnumber].dont_move_count]);
			taijimap[mapnumber].dont_move_count++;
			fscanf(fp,"}\n");
		}
		
		
		
	}   fclose(fp);
}

void file_read_dontrezen()        
{
	
	
	FILE *fp;
	fp=fopen("dontrezen.txt","a");
	fclose(fp);
	fp=fopen("dontrezen.txt","r");
	int mapnumber;
	char mapname[100];
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			fscanf(fp,"{\n");
			fscanf(fp,"�ʹ�ȣ:%d\n",&mapnumber);
			fscanf(fp,"���̸�:%s\n",mapname);
			fscanf(fp,"x��ǥ:%d\n",&taijimap[mapnumber].dont_rezen_x[taijimap[mapnumber].dont_rezen_count]);
			fscanf(fp,"y��ǥ:%d\n",&taijimap[mapnumber].dont_rezen_y[taijimap[mapnumber].dont_rezen_count]);
			taijimap[mapnumber].dont_rezen_count++;
			fscanf(fp,"}\n");
		}
		
		
		
	}   fclose(fp);
}

void file_read_setting()        
{
	
	int autosave;
	int autoreset;
	FILE *fp;
	fp=fopen("setting.txt","a");
	fclose(fp);
	fp=fopen("setting.txt","r");
	fseek(fp,0,SEEK_SET);
	int setting_imsi;
	{
		fscanf(fp,"����ġ ��� ���� ü��(��:10000000 50):%d %d\n",&setting_st.exp,&setting_st.heal);
		fscanf(fp,"����ġ ��� ���� ����(��:10000000 25):%d %d\n",&setting_st.exp_mana,&setting_st.mana);
		fscanf(fp,"�ּ� ���� �ð�(�������� �� ����):%d\n",&setting_imsi);
		fscanf(fp,"�����Ǳ��(����19��) �Ҹ� ����:%d\n",&setting_st.magic19_mana);
		fscanf(fp,"�����Ǳ��(����19��) ȸ�� ü��:%d\n",&setting_st.magic19_hel);
		fscanf(fp,"�����Ǳ��(����30��) �Ҹ� ����:%d\n",&setting_st.magic30_mana);
		fscanf(fp,"�����Ǳ��(����30��) ȸ�� ü��:%d\n",&setting_st.magic30_hel);
		fscanf(fp,"�¾��Ǳ��(����31��) �Ҹ� ����:%d\n",&setting_st.magic31_mana);
		fscanf(fp,"�¾��Ǳ��(����31��) ȸ�� ü��:%d\n",&setting_st.magic31_hel);
		fscanf(fp,"�����Ǳ��(����32��) �Ҹ� ����:%d\n",&setting_st.magic32_mana);
		fscanf(fp,"�����Ǳ��(����32��) ȸ�� ü��:%d\n",&setting_st.magic32_hel);
		fscanf(fp,"�����Ǳ��(����33��) �Ҹ� ����:%d\n",&setting_st.magic33_mana);
		fscanf(fp,"�����Ǳ��(����33��) ȸ�� ü��:%d\n",&setting_st.magic33_hel);
		fscanf(fp,"�ŷ��Ǳ��(����34��) �Ҹ� ����:%d\n",&setting_st.magic34_mana);
		fscanf(fp,"�ŷ��Ǳ��(����34��) ȸ�� ü��:%d\n",&setting_st.magic34_hel);
		fscanf(fp,"�ڵ����½ð�(��):%d\n",&autoreset);
		auto_reset=autoreset*1000;
		fscanf(fp,"�ڵ�����ð�(��):%d\n",&autosave);
		auto_save=autosave*1000;
		char garba[100];
		fscanf(fp,"�������ּ�:%s\n",&domain_name);
		
		fscanf(fp,"�ִ������ڼ�����:%d\n",&max_client);
		fscanf(fp,"�ִ���̵𸸵������:%d\n",&max_id);
		fscanf(fp,"��Ŭ���ӿ���(1:�� 2:�ƴϿ�):%d\n",&bong_client);
		
		
		
		setting_st.rezen=setting_imsi*1000;
		
		
		
		
	}   fclose(fp);
}

void file_read_monster()        
{
	
	monster_frec=0;
	
	FILE *fp;
	fp=fopen("monster.txt","a");
	fclose(fp);
	fp=fopen("monster.txt","r");
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			fscanf(fp,"{\n");
			fscanf(fp,"���� ��ȣ:%d\n",&monster[monster_frec].number);
			fscanf(fp,"���� �̸�:%s\n",monster[monster[monster_frec].number].name);
			monster[monster[monster_frec].number].real_number=monster[monster_frec].number;
			fscanf(fp,"���� ����:%d\n",&monster[monster[monster_frec].number].color);
			fscanf(fp,"���� ü��:%u\n",&monster[monster[monster_frec].number].hel);
			fscanf(fp,"���� ����:%d\n",&monster[monster[monster_frec].number].ac);
			fscanf(fp,"���� Ÿ��(1.����2.�İ�3.����):%d\n",&monster[monster[monster_frec].number].type);
			fscanf(fp,"���� ���ݷ�:%d\n",&monster[monster[monster_frec].number].power);
			fscanf(fp,"���� �̵��ӵ�:%d\n",&monster[monster[monster_frec].number].attack_speed);
			fscanf(fp,"���� ���ݼӵ�:%d\n",&monster[monster[monster_frec].number].move_speed);
			fscanf(fp,"���� ��� ����1(����,Ȯ��):%d %d\n",&monster[monster[monster_frec].number].magic[0],&monster[monster[monster_frec].number].magic_percent[0]);
			fscanf(fp,"���� ��� ����2(����,Ȯ��):%d %d\n",&monster[monster[monster_frec].number].magic[1],&monster[monster[monster_frec].number].magic_percent[1]);
			fscanf(fp,"���� ��� ����3(����,Ȯ��):%d %d\n",&monster[monster[monster_frec].number].magic[2],&monster[monster[monster_frec].number].magic_percent[2]);
			fscanf(fp,"���Ͱ� �ִ¾�����:%s\n",monster[monster[monster_frec].number].item);
			fscanf(fp,"���Ͱ� ������ �� Ȯ��:%d\n",&monster[monster[monster_frec].number].item_percent);
			fscanf(fp,"���Ͱ� �ִ� ����:%d\n",&monster[monster[monster_frec].number].money);
			fscanf(fp,"���Ͱ� ���� �� Ȯ��:%d\n",&monster[monster[monster_frec].number].money_percent);
			fscanf(fp,"���Ͱ� �ִ°���ġ:%d\n",&monster[monster[monster_frec].number].exp);
			fscanf(fp,"���� ������ Ȯ��:%d\n",&monster[monster[monster_frec].number].run);
			fscanf(fp,"���� ��ų�� Ȯ��:%d\n",&monster[monster[monster_frec].number].skil);
			fscanf(fp,"}\n");
			monster_frec++;
		}
		
		
		
		/*       fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",mid[frecnum].id,mid[frecnum].pass,&mid[frecnum].level,
		&mid[frecnum].hel,&mid[frecnum].mana,&mid[frecnum].max_hel,&mid[frecnum].max_mana,&mid[frecnum].exp,&mid[frecnum].money,
		&mid[frecnum].map_x,&mid[frecnum].map_y,mid[frecnum].map,&mid[frecnum].him,
		&mid[frecnum].min,&mid[frecnum].ji,&mid[frecnum].thread,&mid[frecnum].banghyang,
		&mid[frecnum].head,&mid[frecnum].headcolor,&mid[frecnum].dress,&mid[frecnum].dresscolor,
		&mid[frecnum].sword,&mid[frecnum].swordcolor,&mid[frecnum].bangpae,&mid[frecnum].bangpaecolor,
		&mid[frecnum].realmap); */
		
	}   fclose(fp);
}

void file_read_rezen()
{
	
	rezen_frec=0;
	char aaa[100],bbb[100];
	FILE *fp;
	fp=fopen("rezen.txt","a");
	fclose(fp);
	fp=fopen("rezen.txt","r");
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			int iii;
			fscanf(fp,"{\n");
			fscanf(fp,"������ ���̸�:%s\n",aaa);
			fscanf(fp,"������ �ʹ�ȣ:%d\n",&rezen_st[rezen_frec].mapnumber);
			fscanf(fp,"������ �ð�:%d\n",&rezen_st[rezen_frec].time);
			fscanf(fp,"������ �����̸�:%s\n",bbb);
			fscanf(fp,"������ ���͹�ȣ:%d\n",&rezen_st[rezen_frec].monster_number);
			fscanf(fp,"������ ���� ������:%d\n",&rezen_st[rezen_frec].monster_count);
			fscanf(fp,"}\n");
			rezen_frec++;
		}
		
		
		
		/*       fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",mid[frecnum].id,mid[frecnum].pass,&mid[frecnum].level,
		&mid[frecnum].hel,&mid[frecnum].mana,&mid[frecnum].max_hel,&mid[frecnum].max_mana,&mid[frecnum].exp,&mid[frecnum].money,
		&mid[frecnum].map_x,&mid[frecnum].map_y,mid[frecnum].map,&mid[frecnum].him,
		&mid[frecnum].min,&mid[frecnum].ji,&mid[frecnum].thread,&mid[frecnum].banghyang,
		&mid[frecnum].head,&mid[frecnum].headcolor,&mid[frecnum].dress,&mid[frecnum].dresscolor,
		&mid[frecnum].sword,&mid[frecnum].swordcolor,&mid[frecnum].bangpae,&mid[frecnum].bangpaecolor,
		&mid[frecnum].realmap); */
		
	}   fclose(fp);
}

void file_read_npc()
{
	
	npc_frec=0;
	char aaa[100],bbb[100];
	FILE *fp;
	fp=fopen("npc.txt","a");
	fclose(fp);
	fp=fopen("npc.txt","r");
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			int iii;
			fscanf(fp,"{\n");
			fscanf(fp,"npc ���̸�:%s\n",aaa);
			fscanf(fp,"npc �ʹ�ȣ:%d\n",&npc_st[npc_frec].mapnumber);
			fscanf(fp,"npc �̸�:%s\n",bbb);
			fscanf(fp,"npc ���͹�ȣ:%d\n",&npc_st[npc_frec].monster_number);
			fscanf(fp,"npc x��ǥ:%d\n",&npc_st[npc_frec].x);
			fscanf(fp,"npc y��ǥ:%d\n",&npc_st[npc_frec].y);
			fscanf(fp,"}\n");
			npc_frec++;
		}
		
		
		
		/*       fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",mid[frecnum].id,mid[frecnum].pass,&mid[frecnum].level,
		&mid[frecnum].hel,&mid[frecnum].mana,&mid[frecnum].max_hel,&mid[frecnum].max_mana,&mid[frecnum].exp,&mid[frecnum].money,
		&mid[frecnum].map_x,&mid[frecnum].map_y,mid[frecnum].map,&mid[frecnum].him,
		&mid[frecnum].min,&mid[frecnum].ji,&mid[frecnum].thread,&mid[frecnum].banghyang,
		&mid[frecnum].head,&mid[frecnum].headcolor,&mid[frecnum].dress,&mid[frecnum].dresscolor,
		&mid[frecnum].sword,&mid[frecnum].swordcolor,&mid[frecnum].bangpae,&mid[frecnum].bangpaecolor,
		&mid[frecnum].realmap); */
		
	}   fclose(fp);
}


void file_read_npc_item()
{
	
	npc_item_frec=0;
	char aaa[100],bbb[100];
	FILE *fp;
	fp=fopen("npc_item.txt","a");
	fclose(fp);
	fp=fopen("npc_item.txt","r");
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			int iii;
			fscanf(fp,"{\n");
			fscanf(fp,"�̸�:%s\n",npc_item_st[npc_item_frec].name);
			fscanf(fp,"npc�� �Ĵ� ����:%d\n",&npc_item_st[npc_item_frec].npc_sell);
			fscanf(fp,"user�� �Ĵ°���:%d\n",&npc_item_st[npc_item_frec].user_sell);
			fscanf(fp,"�����۳ѹ�:%d\n",&npc_item_st[npc_item_frec].number);
			fscanf(fp,"�Ĵ°���:%d\n",&npc_item_st[npc_item_frec].mapnumber);
			fscanf(fp,"}\n");
			npc_item_frec++;
		}
		
		
	}   fclose(fp);
}


void file_read_port()        
{
	
	port_frec=0;
	char aaa[100],bbb[100];
	FILE *fp;
	fp=fopen("port.txt","a");
	fclose(fp);
	fp=fopen("port.txt","r");
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			int iii;
			fscanf(fp,"{\n");
			fscanf(fp,"���� %s %s\n",aaa,bbb);
			fscanf(fp,"�̵����� %d\n",&iii);
			port_st[iii].map1[port_st[iii].map_count]=iii;
			fscanf(fp,"X1��ǥ %d\n",&port_st[iii].x1[port_st[iii].map_count]);
			fscanf(fp,"Y1��ǥ %d\n",&port_st[iii].y1[port_st[iii].map_count]);
			fscanf(fp,"�̵��ĸ� %d\n",&port_st[iii].map2[port_st[iii].map_count]);
			fscanf(fp,"X2��ǥ %d\n",&port_st[iii].x2[port_st[iii].map_count]);
			fscanf(fp,"Y2��ǥ %d\n",&port_st[iii].y2[port_st[iii].map_count]);
			fscanf(fp,"�������� %d\n",&port_st[iii].level[port_st[iii].map_count]);
			fscanf(fp,"}\n");
			port_frec++;
			port_st[iii].map_count++;
		}
		
		
		
		/*       fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",mid[frecnum].id,mid[frecnum].pass,&mid[frecnum].level,
		&mid[frecnum].hel,&mid[frecnum].mana,&mid[frecnum].max_hel,&mid[frecnum].max_mana,&mid[frecnum].exp,&mid[frecnum].money,
		&mid[frecnum].map_x,&mid[frecnum].map_y,mid[frecnum].map,&mid[frecnum].him,
		&mid[frecnum].min,&mid[frecnum].ji,&mid[frecnum].thread,&mid[frecnum].banghyang,
		&mid[frecnum].head,&mid[frecnum].headcolor,&mid[frecnum].dress,&mid[frecnum].dresscolor,
		&mid[frecnum].sword,&mid[frecnum].swordcolor,&mid[frecnum].bangpae,&mid[frecnum].bangpaecolor,
		&mid[frecnum].realmap); */
		
	}   fclose(fp);
}

void file_read_map()        
{
	
	map_frec=0;
	
	FILE *fp;
	fp=fopen("map.txt","a");
	fclose(fp);
	fp=fopen("map.txt","r");
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			int iii;
			fscanf(fp,"�׸� ��\n");
			fscanf(fp,"{\n");
			fscanf(fp,"�ʹ�ȣ %d\n",&iii);
			fscanf(fp,"���̸� %s\n",taijimap[iii].name);
			fscanf(fp,"x %d\n",&taijimap[iii].map_x_len);
			taijimap[iii].map_x_len--;
			
			fscanf(fp,"y %d\n",&taijimap[iii].map_y_len);
			taijimap[iii].map_y_len--;
			fscanf(fp,"����� %d\n",&taijimap[iii].sound);
			fscanf(fp,"�θ�� %d\n",&taijimap[iii].parent);
			fscanf(fp,"��������(1.���� 2.�Ұ���):%d\n",&taijimap[iii].magic_on);
			fscanf(fp,"��ȯ����(1.���� 2.�Ұ���):%d\n",&taijimap[iii].sohwan_on);
			fscanf(fp,"��ο���(1.���� 2.�Ұ���):%d\n",&taijimap[iii].chooldo_on);
			fscanf(fp,"pk����(1.���� 2.�Ұ���):%d\n",&taijimap[iii].pk_on);
			fscanf(fp,"�����ּҷ���(0����):%d\n",&taijimap[iii].min_level);
			fscanf(fp,"�����ִ뷹��(0����):%d\n",&taijimap[iii].max_level);
			fscanf(fp,"}\n");
			map_frec++;
			
		}
		
		
		
		/*       fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",mid[frecnum].id,mid[frecnum].pass,&mid[frecnum].level,
		&mid[frecnum].hel,&mid[frecnum].mana,&mid[frecnum].max_hel,&mid[frecnum].max_mana,&mid[frecnum].exp,&mid[frecnum].money,
		&mid[frecnum].map_x,&mid[frecnum].map_y,mid[frecnum].map,&mid[frecnum].him,
		&mid[frecnum].min,&mid[frecnum].ji,&mid[frecnum].thread,&mid[frecnum].banghyang,
		&mid[frecnum].head,&mid[frecnum].headcolor,&mid[frecnum].dress,&mid[frecnum].dresscolor,
		&mid[frecnum].sword,&mid[frecnum].swordcolor,&mid[frecnum].bangpae,&mid[frecnum].bangpaecolor,
		&mid[frecnum].realmap); */
		
	}   fclose(fp);
}
void file_read_item()        
{
	
	item_frec=0;
	
	FILE *fp;
	fp=fopen("item.txt","a");
	fclose(fp);
	fp=fopen("item.txt","r");
	fseek(fp,0,SEEK_SET);
    {
		while(!feof(fp)){
			fscanf(fp,"{\n");
			fscanf(fp,"�����۳ѹ�(1~2417):%d\n",&item_st[item_frec].number);
			fscanf(fp,"�������̸�:%s\n",item_st[item_st[item_frec].number].name);
			fscanf(fp,"���������뿩��(1. �� 2. ���� 3. ���� 4. ���� 5. ������ 6. �Ͱ��̷� 7. ���� 8. �����̵�):%d\n",&item_st[item_st[item_frec].number].select);
			fscanf(fp,"������:%d\n",&item_st[item_st[item_frec].number].life);
			fscanf(fp,"ü�»��:%d\n",&item_st[item_st[item_frec].number].hel_up);
			fscanf(fp,"���»��:%d\n",&item_st[item_st[item_frec].number].mana_up);
			fscanf(fp,"�����:%d\n",&item_st[item_st[item_frec].number].him_up);
			fscanf(fp,"�λ��:%d\n",&item_st[item_st[item_frec].number].min_up);
			fscanf(fp,"�����:%d\n",&item_st[item_st[item_frec].number].ji_up);
			fscanf(fp,"��������:%d\n",&item_st[item_st[item_frec].number].level_jehan);
			fscanf(fp,"������:%d\n",&item_st[item_st[item_frec].number].him_jehan);
			fscanf(fp,"������:%d\n",&item_st[item_st[item_frec].number].min_jehan);
			fscanf(fp,"������:%d\n",&item_st[item_st[item_frec].number].ji_jehan);
			fscanf(fp,"�ִ����:%d\n",&item_st[item_st[item_frec].number].sex);
			fscanf(fp,"���ϰ�� ����(1.���� 2.���� 3.����):%d\n",&item_st[item_st[item_frec].number].sex);
			fscanf(fp,"���ϰ�� ����:%d\n",&item_st[item_st[item_frec].number].ac);
			fscanf(fp,"����(1),����x(2):%d\n",&item_st[item_st[item_frec].number].ggajim);
			fscanf(fp,"����(1),����x(2):%d\n",&item_st[item_st[item_frec].number].drop);
			fscanf(fp,"����(1),����x(2):%d\n",&item_st[item_st[item_frec].number].repair);
			fscanf(fp,"���������Ҷ��������(������1��):%d\n",&item_st[item_st[item_frec].number].repair_expense);
			fscanf(fp,"����(1.��� 2.���� 3.���� 4.���� 5.�ּ��� 6.������):%d\n",&item_st[item_st[item_frec].number].job);
			fscanf(fp,"���ϰ�� ����� �� �ѹ�:%d\n",&item_st[item_st[item_frec].number].dress_number);
			fscanf(fp,"���ϰ�� �ڵ�����(2�� �⺻):%d\n",&item_st[item_st[item_frec].number].dress_color);
			fscanf(fp,"������ ��� ����� ���� �ѹ�:%d\n",&item_st[item_st[item_frec].number].sword_number);
			fscanf(fp,"������ ��� ����:%d\n",&item_st[item_st[item_frec].number].sword_color);
			fscanf(fp,"������ ��� �ּ� ������:%d\n",&item_st[item_st[item_frec].number].sword_min_power);
			fscanf(fp,"������ ��� �ִ� ������:%d\n",&item_st[item_st[item_frec].number].sword_max_power);
			fscanf(fp,"������ ��� �� ����Ʈ:%d\n",&item_st[item_st[item_frec].number].sword_gyuk_effect);
			fscanf(fp,"������ ��� �� �Ŀ�:%d\n",&item_st[item_st[item_frec].number].sword_gyuk_power);
			fscanf(fp,"������ ��� �� ���� Ȯ��(��:10���� 1�� ��� 10�̶�� �Է�):%d\n",&item_st[item_st[item_frec].number].sword_gyuk_percent);
			fscanf(fp,"������ ��� �ٿ��ִ� ���� ������(��:1�� ������ �����̸� 1�� ���̷��� 1�Է�):%d %d\n",&item_st[item_st[item_frec].number].sword_delay[0],&item_st[item_st[item_frec].number].sword_delay[1]);
			fscanf(fp,"������ ��� ���濡�� �Ŵ� ����(0������):%d\n",&item_st[item_st[item_frec].number].sword_magic);
			fscanf(fp,"������ ��� ���濡�� �Ŵ� ���� �� Ȯ��:%d\n",&item_st[item_st[item_frec].number].sword_magic_percent);
			fscanf(fp,"�����ϰ�� ����� ���� �ѹ�:%d\n",&item_st[item_st[item_frec].number].bangpae_number);
			fscanf(fp,"�����ϰ�� ����� ���� ����:%d\n",&item_st[item_st[item_frec].number].bangpae_color);
			fscanf(fp,"�����ϰ�� ����� ���� �ѹ�:%d\n",&item_st[item_st[item_frec].number].head_number);
			fscanf(fp,"�������ϰ�� ����� ������ �ѹ�:%d\n",&item_st[item_st[item_frec].number].ring_number);
			fscanf(fp,"�������ϰ�� ����� ������ ������(������ȣ����):%d\n",&item_st[item_st[item_frec].number].ring_magic);
			fscanf(fp,"�Ͱ��̷��ϰ�� ����� ������ �ѹ�:%d\n",&item_st[item_st[item_frec].number].earing_number);
			fscanf(fp,"�Ͱ��̷��ϰ�� ����� ������ ������(������ȣ����):%d\n",&item_st[item_st[item_frec].number].earing_magic);
			fscanf(fp,"������ ��� ���� ü�� ȸ��:%d\n",&item_st[item_st[item_frec].number].food_hel_up);
			fscanf(fp,"������ ��� ���� ���� ȸ��:%d\n",&item_st[item_st[item_frec].number].food_mana_up);
			fscanf(fp,"������ ��� ���� ������ ü�� ����:%d\n",&item_st[item_st[item_frec].number].food_hel_forever_up);
			fscanf(fp,"������ ��� ���� ������ ���� ����:%d\n",&item_st[item_st[item_frec].number].food_mana_forever_up);
			fscanf(fp,"�����̵��������� ��� ���� �̵���ǥ(�ʹ�ȣ x��ǥ y��ǥ):%d %d %d\n",&item_st[item_st[item_frec].number].teleport[0],&item_st[item_st[item_frec].number].teleport[1],&item_st[item_st[item_frec].number].teleport[2]);
			fscanf(fp,"}\n");
			item_frec++;
		}
		
		
		
		/*       fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",mid[frecnum].id,mid[frecnum].pass,&mid[frecnum].level,
		&mid[frecnum].hel,&mid[frecnum].mana,&mid[frecnum].max_hel,&mid[frecnum].max_mana,&mid[frecnum].exp,&mid[frecnum].money,
		&mid[frecnum].map_x,&mid[frecnum].map_y,mid[frecnum].map,&mid[frecnum].him,
		&mid[frecnum].min,&mid[frecnum].ji,&mid[frecnum].thread,&mid[frecnum].banghyang,
		&mid[frecnum].head,&mid[frecnum].headcolor,&mid[frecnum].dress,&mid[frecnum].dresscolor,
		&mid[frecnum].sword,&mid[frecnum].swordcolor,&mid[frecnum].bangpae,&mid[frecnum].bangpaecolor,
		&mid[frecnum].realmap); */
		
	}   fclose(fp);
}



void npc()
{
	mid[0].level=1;
	mid[0].hel=55;
	mid[0].mana=70;
	mid[0].max_hel=55;
	mid[0].max_mana=70;
	mid[0].exp=0;
	mid[0].money=0;
	mid[0].map_x=9;
	mid[0].map_y=9;
	char default_map[]="�ʺ����Ǳ�";
	strcpy(mid[1].map,default_map);
	mid[0].him=3;
	mid[0].min=3;
	mid[0].ji=3;
	mid[0].thread=99;
	mid[0].banghyang=2;
	mid[0].head=1;
	mid[0].headcolor=0;
	mid[0].dress=1;
	mid[0].dresscolor=1;
	mid[0].sword=1;
	mid[0].swordcolor=1;
	mid[0].bangpae=1;
	mid[0].bangpaecolor=0;
	mid[0].realmap=0;
}

void menu_add(char *user,char *pass){     // �����ϱ�� �߰� 
	//EnterCriticalSection(&save);		
	file_read_default();
	int rand1;rand1=rand();
	//file_read();
	struct student add;
	//FILE *fp;
	//fp=fopen("chr.txt","a+");
	strcpy(deflt.id,user);
	strcpy(deflt.pass,pass);
	srand(time(0));
	rand1=(rand1%20)+1;
	add.head=rand1;
	rand1=rand();	rand1=(rand1%20)+1;
	add.headcolor=0;
	rand1=rand();	rand1=(rand1%60)+1;
	add.dress=rand1;
	rand1=rand();	rand1=(rand1%10)+1;
	add.dresscolor=rand1;
	rand1=rand();	rand1=(rand1%3)+49;
	add.sword=rand1;
	rand1=rand();	rand1=(rand1%20)+1;
	add.swordcolor=0;
	rand1=rand();	rand1=(rand1%20)+1;
	add.bangpae=rand1;
	rand1=rand();	rand1=(rand1%20)+1;
	add.bangpaecolor=0;
	rand1=rand();	rand1=(rand1%20)+1;
	add.realmap=0;
	//// printf("id : ");
    //scanf("%s", add.id);
    //getchar();
    // // printf("pass : ");
    //scanf("%s", add.pass);
    // getchar();
	//fprintf(fp,"{\n");
	//fprintf(fp,"���̵�:%s\n",deflt.id);
	//fprintf(fp,"��й�ȣ:%s\n",deflt.pass);
	//fprintf(fp,"����:%s\n",deflt.job);
	//fprintf(fp,"�±޹�ȣ:%d\n",deflt.s_number);
	//fprintf(fp,"����:%d\n",deflt.level);
	//fprintf(fp,"ü��:%u\n",deflt.hel);
	//fprintf(fp,"����:%u\n",deflt.mana);
	//fprintf(fp,"�ִ�ü��:%u\n",deflt.max_hel);
	//fprintf(fp,"�ִ븶��:%u\n",deflt.max_mana);
	//fprintf(fp,"����ġ:%u\n",deflt.exp);
	//fprintf(fp,"�ʿ����ġ:%u\n",deflt.need_exp);
	//fprintf(fp,"��:%u\n",deflt.money);
	//fprintf(fp,"��ǥX:%d\n",deflt.map_x);
	//fprintf(fp,"��ǥY:%d\n",deflt.map_y);
	////fprintf(fp,"���̸�:%s\n",deflt.map);
	//fprintf(fp,"��:%d\n",deflt.him);
	//fprintf(fp,"��:%d\n",deflt.min);
	//fprintf(fp,"��:%d\n",deflt.ji);
	//fprintf(fp,"������:%d\n",deflt.thread);
	//fprintf(fp,"����:%d\n",deflt.banghyang);
	//fprintf(fp,"�Ӹ����:%d\n",deflt.new_head);
	//fprintf(fp,"�Ӹ�����:%d\n",deflt.headcolor);
	//fprintf(fp,"��:%d\n",deflt.dress);
	//fprintf(fp,"�ʻ���:%d\n",deflt.dresscolor);
	//fprintf(fp,"����:%d\n",deflt.sword);
	//fprintf(fp,"�������:%d\n",deflt.swordcolor);
	//fprintf(fp,"����:%d\n",deflt.bangpae);
	//fprintf(fp,"���л���:%d\n",deflt.bangpaecolor);
	//fprintf(fp,"����:%d\n",deflt.head_gear);
	//fprintf(fp,"����1:%d\n",deflt.ring[0]);
	//fprintf(fp,"����2:%d\n",deflt.ring[1]);
	//fprintf(fp,"�Ͱ���1:%d\n",deflt.earing[0]);
	//fprintf(fp,"�Ͱ���2:%d\n",deflt.earing[1]);
	//fprintf(fp,"�ʹ�ȣ:%d\n",deflt.realmap);
	//fprintf(fp,"����a:%d\n",deflt.magic[0]);
	//fprintf(fp,"����b:%d\n",deflt.magic[1]);
	//fprintf(fp,"����c:%d\n",deflt.magic[2]);
	//fprintf(fp,"����d:%d\n",deflt.magic[3]);
	//fprintf(fp,"����e:%d\n",deflt.magic[4]);
	//fprintf(fp,"����f:%d\n",deflt.magic[5]);
	//fprintf(fp,"����g:%d\n",deflt.magic[6]);
	//fprintf(fp,"����h:%d\n",deflt.magic[7]);
	//fprintf(fp,"����i:%d\n",deflt.magic[8]);
	//fprintf(fp,"����j:%d\n",deflt.magic[9]);
	//fprintf(fp,"����k:%d\n",deflt.magic[10]);
	//fprintf(fp,"����l:%d\n",deflt.magic[11]);
	//fprintf(fp,"����m:%d\n",deflt.magic[12]);
	//fprintf(fp,"����n:%d\n",deflt.magic[13]);
	//fprintf(fp,"����o:%d\n",deflt.magic[14]);
	//fprintf(fp,"����p:%d\n",deflt.magic[15]);
	//fprintf(fp,"����q:%d\n",deflt.magic[16]);
	//fprintf(fp,"����r:%d\n",deflt.magic[17]);
	//fprintf(fp,"����s:%d\n",deflt.magic[18]);
	//fprintf(fp,"����t:%d\n",deflt.magic[19]);
	//fprintf(fp,"����u:%d\n",deflt.magic[20]);
	//fprintf(fp,"����v:%d\n",deflt.magic[21]);
	//fprintf(fp,"����w:%d\n",deflt.magic[22]);
	//fprintf(fp,"����x:%d\n",deflt.magic[23]);
	//fprintf(fp,"����y:%d\n",deflt.magic[24]);
	//fprintf(fp,"����z:%d\n",deflt.magic[25]);
	//fprintf(fp,"����A:%d\n",deflt.magic[26]);
	//fprintf(fp,"����B:%d\n",deflt.magic[27]);
	//fprintf(fp,"����C:%d\n",deflt.magic[28]);
	//fprintf(fp,"����D:%d\n",deflt.magic[29]);
	//fprintf(fp,"����E:%d\n",deflt.magic[30]);
	//fprintf(fp,"����F:%d\n",deflt.magic[31]);
	//fprintf(fp,"����G:%d\n",deflt.magic[32]);
	//fprintf(fp,"����H:%d\n",deflt.magic[33]);
	//fprintf(fp,"����I:%d\n",deflt.magic[34]);
	//fprintf(fp,"����J:%d\n",deflt.magic[35]);
	//fprintf(fp,"����K:%d\n",deflt.magic[36]);
	//fprintf(fp,"����L:%d\n",deflt.magic[37]);
	//fprintf(fp,"����M:%d\n",deflt.magic[38]);
	//fprintf(fp,"����N:%d\n",deflt.magic[39]);
	//fprintf(fp,"����O:%d\n",deflt.magic[40]);
	//fprintf(fp,"����P:%d\n",deflt.magic[41]);
	//fprintf(fp,"����Q:%d\n",deflt.magic[42]);
	//fprintf(fp,"����R:%d\n",deflt.magic[43]);
	//fprintf(fp,"����S:%d\n",deflt.magic[44]);
	//fprintf(fp,"����T:%d\n",deflt.magic[45]);
	//fprintf(fp,"����U:%d\n",deflt.magic[46]);
	//fprintf(fp,"����V:%d\n",deflt.magic[47]);
	//fprintf(fp,"����W:%d\n",deflt.magic[48]);
	//fprintf(fp,"����X:%d\n",deflt.magic[49]);
	//fprintf(fp,"����Y:%d\n",deflt.magic[50]);
	//fprintf(fp,"����Z:%d\n",deflt.magic[51]);
	//fprintf(fp,"������a:%d %d\n",deflt.item[0][0],deflt.item[0][1]);
	//fprintf(fp,"������b:%d %d\n",deflt.item[1][0],deflt.item[1][1]);
	//fprintf(fp,"������c:%d %d\n",deflt.item[2][0],deflt.item[2][1]);
	//fprintf(fp,"������d:%d %d\n",deflt.item[3][0],deflt.item[3][1]);
	//fprintf(fp,"������e:%d %d\n",deflt.item[4][0],deflt.item[4][1]);
	//fprintf(fp,"������f:%d %d\n",deflt.item[5][0],deflt.item[5][1]);
	//fprintf(fp,"������g:%d %d\n",deflt.item[6][0],deflt.item[6][1]);
//fprintf(fp,"������h:%d %d\n",deflt.item[7][0],deflt.item[7][1]);
//fprintf(fp,"������i:%d %d\n",deflt.item[8][0],deflt.item[8][1]);
//fprintf(fp,"������j:%d %d\n",deflt.item[9][0],deflt.item[9][1]);
//fprintf(fp,"������k:%d %d\n",deflt.item[10][0],deflt.item[10][1]);
//fprintf(fp,"������l:%d %d\n",deflt.item[11][0],deflt.item[11][1]);
//fprintf(fp,"������m:%d %d\n",deflt.item[12][0],deflt.item[12][1]);
//fprintf(fp,"������n:%d %d\n",deflt.item[13][0],deflt.item[13][1]);
//fprintf(fp,"������o:%d %d\n",deflt.item[14][0],deflt.item[14][1]);
//fprintf(fp,"������p:%d %d\n",deflt.item[15][0],deflt.item[15][1]);
//fprintf(fp,"������q:%d %d\n",deflt.item[16][0],deflt.item[16][1]);
//fprintf(fp,"������r:%d %d\n",deflt.item[17][0],deflt.item[17][1]);
//fprintf(fp,"������s:%d %d\n",deflt.item[18][0],deflt.item[18][1]);
//fprintf(fp,"������t:%d %d\n",deflt.item[19][0],deflt.item[19][1]);
//fprintf(fp,"������u:%d %d\n",deflt.item[20][0],deflt.item[20][1]);
//fprintf(fp,"������v:%d %d\n",deflt.item[21][0],deflt.item[21][1]);
//fprintf(fp,"������w:%d %d\n",deflt.item[22][0],deflt.item[22][1]);
//fprintf(fp,"������x:%d %d\n",deflt.item[23][0],deflt.item[23][1]);
//fprintf(fp,"������y:%d %d\n",deflt.item[24][0],deflt.item[24][1]);
//fprintf(fp,"������z:%d %d\n",deflt.item[25][0],deflt.item[25][1]);
//fprintf(fp,"}\n");

//printf("�����ϱ� frecnum:%d\n",frecnum);
mid2[frecnum]=deflt;
//printf("ü��:%d\n",mid2[frecnum].hel);
frecnum++;
//frecnum++;




/*fprintf(fp,"%s %s %d %d %d %d %d ",add.id,add.pass, add.level, add.hel,add.mana,add.max_hel,add.max_mana);
fprintf(fp,"%d %d %d %d %s ",add.exp,add.money, add.map_x, add.map_y,add.map);
fprintf(fp,"%d %d %d %d ",add.him,add.min, add.ji, add.thread);
fprintf(fp,"%d %d %d %d ",add.banghyang,add.head, add.headcolor, add.dress);
fprintf(fp,"%d %d %d %d ",add.dresscolor,add.sword, add.swordcolor, add.bangpae);
fprintf(fp,"%d %d \n",add.bangpaecolor,add.realmap);*/

//fclose(fp);

//LeaveCriticalSection(&save);

}


//void inputidpw(char *


int loginchr(int imsi,char *sendmsg)
{
	sendmsg[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
	sendmsg[1]=( mid2[imsi].map_x & 0x000000ff ) ;
	sendmsg[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
	sendmsg[3]=( mid2[imsi].map_y & 0x000000ff ) ;
	sendmsg[4]=(char)mid2[imsi].banghyang;
	sendmsg[5]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[6]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[7]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[8]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[9]='\x00';
	sendmsg[10]='\x00';
	sendmsg[11]=mid2[imsi].sangtae;
	sendmsg[12]='\x00';
	sendmsg[13]=(char)mid2[imsi].head;
	sendmsg[14]=(char)mid2[imsi].headcolor;
	sendmsg[15]=(char)mid2[imsi].dress;
	sendmsg[16]=(char)mid2[imsi].dresscolor;
	sendmsg[17]=(mid2[imsi].sword & 0x0000ff00 ) >> 8;
	sendmsg[18]=(mid2[imsi].sword  & 0x000000ff ) ;
	sendmsg[19]=(char)mid2[imsi].swordcolor;
	sendmsg[20]=(char)mid2[imsi].bangpae;
	sendmsg[21]=(char)mid2[imsi].bangpaecolor;
	sendmsg[22]='\x03';
	sendmsg[23]=(char)strlen(mid2[imsi].id);
	strncpy(sendmsg+24,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[24+strlen(mid2[imsi].id)]='\x00';
	// printf("\n");
	// printf("%d ���ڵ��� ���� ���\n",imsi);
	packet_dump(sendmsg,50,16);
	return 25+strlen(mid2[imsi].id);
}

int loginchr2(int imsi,int color,char *sendmsg)
{
	sendmsg[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
	sendmsg[1]=( mid2[imsi].map_x & 0x000000ff ) ;
	sendmsg[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
	sendmsg[3]=( mid2[imsi].map_y & 0x000000ff ) ;
	sendmsg[4]=(char)mid2[imsi].banghyang;
	sendmsg[5]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[6]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[7]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[8]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[9]='\x00';
	sendmsg[10]='\x00';
	sendmsg[11]=mid2[imsi].sangtae;
	sendmsg[12]='\x00';
	sendmsg[13]=(char)mid2[imsi].head;
	sendmsg[14]=(char)mid2[imsi].headcolor;
	sendmsg[15]=(char)mid2[imsi].dress;
	sendmsg[16]=(char)mid2[imsi].dresscolor;
	sendmsg[17]=(mid2[imsi].sword & 0x0000ff00 ) >> 8;
	sendmsg[18]=(mid2[imsi].sword  & 0x000000ff ) ;
	sendmsg[19]=(char)mid2[imsi].swordcolor;
	sendmsg[20]=(char)mid2[imsi].bangpae;
	sendmsg[21]=(char)mid2[imsi].bangpaecolor;
	sendmsg[22]=color;
	sendmsg[23]=(char)strlen(mid2[imsi].id);
	strncpy(sendmsg+24,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[24+strlen(mid2[imsi].id)]='\x00';
	// printf("\n");
	// printf("%d ���ڵ��� ���� ���\n",imsi);
	packet_dump(sendmsg,50,16);
	return 25+strlen(mid2[imsi].id);
}


int loginnpc(int imsi,char *sendmsg)
{
	sendmsg[0]='\x00';
	sendmsg[1]=(char)mid[imsi].map_x;
	sendmsg[2]='\x00';
	sendmsg[3]=(char)mid[imsi].map_y;
	sendmsg[4]=(char)mid[imsi].banghyang;
	sendmsg[5]='\x00';
	sendmsg[6]='\x00';
	sendmsg[7]='\x00';
	sendmsg[8]=(char)mid[imsi].thread;
	sendmsg[9]='\x00';
	sendmsg[10]='\x00';
	sendmsg[11]='\x00';
	sendmsg[12]='\x00';
	sendmsg[13]=(char)mid[imsi].head;
	sendmsg[14]=(char)mid[imsi].headcolor;
	sendmsg[15]=(char)mid[imsi].dress;
	sendmsg[16]=(char)mid[imsi].dresscolor;
	sendmsg[17]='\x00';
	sendmsg[18]=(char)mid[imsi].sword;
	sendmsg[19]=(char)mid[imsi].swordcolor;
	sendmsg[20]=(char)mid[imsi].bangpae;
	sendmsg[21]=(char)mid[imsi].bangpaecolor;
	sendmsg[22]='\x03';
	sendmsg[23]=(char)strlen(mid[imsi].id);
	strncpy(sendmsg+24,mid2[imsi].id,strlen(mid[imsi].id));
	sendmsg[24+strlen(mid[imsi].id)]='\x00';
	// printf("\n");
	// printf("%d ���ڵ��� ���� ���\n",imsi);
	packet_dump(sendmsg,50,16);
	return 25+strlen(mid[imsi].id);
}


int loginfile(char *s)
{
	char s2[50];
	char s3[50];
	char space[1];
	space[0]='\x20';
	
	char t;
	char k;
	int a;
	int b;
	t=s[0];
	a=(int)t;
	strncpy(s2,s+1,a);
	s2[a]=NULL;
	// printf("user :%s \n",s2);
	k=s[a+1];
	b=(int)k;
	strncpy(s3,s+a+2,b);
	s3[b]=NULL;
	// printf("pass :%s \n",s3);
	//FILE *fp2;
	//fp2=fopen("chr.txt","a");
	//fclose(fp2);
	//file_read();
	int c = search_data(s2);
	// printf("c:%d\n",c);
	for(int i=0;i<50;i++)
	{
		if(s2[i]==space[0])
		{
			return 1;
		}
		
	}
	
	
	if(c==0) menu_add(s2,s3); // 0���� ���ω����ÿ� ���� �߰�
	else return 1; // �̹� �ִ� ���̵��� ��� 1 ���� 
	return 0;
	
}

char gmsg(char *id,char *s,char *sendmsg) /// �ͼӸ� ó�� ��Ŷ (�ڱ�ȭ�鿡 �Ѹ��°�
{
	char s2[200];
	char s3[200];
	char t;
	char k;
	int a;
	int b;
	t=s[0];
	a=(int)t;
	strncpy(s2,s+1,a);
	s2[a]=NULL;
	// printf("�����̺� �� ���̵� :%s \n",id);
	k=s[a+1];
	b=(int)k;
	strncpy(s3,s+a+2,b);
	s3[b]=NULL;
	// printf("�޽��� :%s \n",s3);
	sendmsg[0]='\x00';
	sendmsg[1]='\x00';
	sendmsg[2]='\x4d';
	memcpy(sendmsg+3,id,strlen(id));
	sendmsg[3+strlen(id)]='\x22';
	sendmsg[4+strlen(id)]='\x20';
	memcpy(sendmsg+5+strlen(id),s3,strlen(s3));
	sendmsg[5+strlen(id)+strlen(s3)]='\x00';
	packet_dump(sendmsg,60,16);
	return 0;
	
}

char gmsg2(char *s,char *sendmsg)    /// ������ �޾Ƹ�
{
	char s2[200];
	char s3[200];
	char t;
	char k;
	int a;
	int b;
	t=s[0];
	a=(int)t;
	strncpy(s2,s+1,a);
	s2[a]=NULL;
	// printf("���� ���̵� :%s \n",s2);
	k=s[a+1];
	b=(int)k;
	strncpy(s3,s+a+2,b);
	s3[b]=NULL;
	// printf("�޽��� :%s \n",s3);
	
	
	//char sendmsg[100];
	
	sendmsg[0]='\x00';
	sendmsg[1]='\x00';
	sendmsg[2]='\x4d';
	memcpy(sendmsg+3,s2,strlen(s2));
	sendmsg[3+strlen(s2)]='\x3e';
	sendmsg[4+strlen(s2)]='\x20';
	memcpy(sendmsg+5+strlen(s2),s3,strlen(s3));
	sendmsg[5+strlen(s2)+strlen(s3)]='\x00';
	packet_dump(sendmsg,60,16);
	return 0;
	
}

int loginfile2(char *s)   // �̾��ϱ� �α� ����
{
	char s2[200];
	char s3[200];
	char t;
	char k;
	int a;
	int b;
	t=s[0];
	a=(int)t;
	strncpy(s2,s+1,a);
	s2[a]=NULL;
	// printf("user :%s \n",s2);
	k=s[a+1];
	b=(int)k;
	strncpy(s3,s+a+2,b);
	s3[b]=NULL;
	// printf("pass :%s \n",s3);
	FILE *fp2;
	fp2=fopen("chr.txt","a");
	fclose(fp2);
	//file_read();
	int c = search_data2(s2,s3);
	if(c!=0) return c; // ���̵� ����� ��ġ��
	else return 0; // ���̵� ����� ��ġ���� ���� ��� 1����
	// ��� ��ġ ������ c ����
	
}


int magic_01(int imsi,int delay,int socketnow)   // ���� 1���� ��ȥ�񹫰� �������
{
	int magic_flag=0;
	int imsi_k;
	int imsi_magic;
	int len;
	int retval;
	if(mid2[imsi].delay[1]>delay)
	{
		int nam=mid2[imsi].delay[1]-delay+25;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[1]=delay;
	if(mid2[imsi].banghyang==02) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		// printf("�Ʒ� �������� ���� �˻�\n");
 							for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
								{
									// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+2) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+3) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+4) {
										imsi_k=k;
										magic_flag=taijimap[mid2[imsi].realmap].chrnumber[k];
										magic_flag++;
									}
								} else imsi_magic++;
								
							}
							
							if(magic_flag!=0) 
							{
								mid2[taijimap[mid2[imsi].realmap].chrnumber[imsi_k]].map_y=mid2[taijimap[mid2[imsi].realmap].chrnumber[imsi_k]].map_y-3;
								return magic_flag;
							}
							
							return 0;
	}
	
	if(mid2[imsi].banghyang==01) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		// printf("������ �������� ���� �˻�\n");
 							for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
								{
									// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+3 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+4 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) {
										imsi_k=k;
										magic_flag=taijimap[mid2[imsi].realmap].chrnumber[k];
										magic_flag++;
									}
								} else imsi_magic++;
								
							}
							
							if(magic_flag!=0) 
							{
								mid2[taijimap[mid2[imsi].realmap].chrnumber[imsi_k]].map_x=mid2[taijimap[mid2[imsi].realmap].chrnumber[imsi_k]].map_x-3;
								return magic_flag;
							}
							
							return 0;
	}
	
	if(mid2[imsi].banghyang==00) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		// printf("���� �������� ���� �˻�\n");
 							for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
								{
									// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-2) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-3) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-4) {
										imsi_k=k;
										magic_flag=taijimap[mid2[imsi].realmap].chrnumber[k];
										magic_flag++;
									}
								} else imsi_magic++;
								
							}
							
							if(magic_flag!=0) 
							{
								mid2[taijimap[mid2[imsi].realmap].chrnumber[imsi_k]].map_y=mid2[taijimap[mid2[imsi].realmap].chrnumber[imsi_k]].map_y+3;
								return magic_flag;
							}
							
							return 0;
	}
	
	if(mid2[imsi].banghyang==03) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		// printf("���� �������� ���� �˻�\n");
 							for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
								{
									// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-3 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-4 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) 
									{
										imsi_k=k;
										magic_flag=taijimap[mid2[imsi].realmap].chrnumber[k];
										magic_flag++;
									}
								} else imsi_magic++;
								
							}
							
							if(magic_flag!=0) 
							{
								mid2[taijimap[mid2[imsi].realmap].chrnumber[imsi_k]].map_x=mid2[taijimap[mid2[imsi].realmap].chrnumber[imsi_k]].map_x+3;
								return magic_flag;
							}
							
							return 0;
	}
}

void magic_01_bojo(int imsi)
{
	int len,retval,mapcount,imsi_count;
	GetLocalTime( &st );
	int magic=magic_01(imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,mid2[imsi].thread);
	magic--;
	if(magic==-1) 
	{
								
		
								// printf("���� ���� �ȸ���\n");
								len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� ������ ���� �ʽ��ϴ�.",40,0x0a,1);
								//retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
								
								
								
	}
	
	
	else
	{
								char sendmsg1[13];
								sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
								sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
								sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
								sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
								sendmsg1[4]='\x01';
								sendmsg1[5]='\x00';
								sendmsg1[6]='\x4e';
								sendmsg1[7]='\x08';
								
								len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
								for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
									
								}
								
								
								char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
								int sendmsg_byte=loginchr(magic,sendmsg2);
								
								len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
								for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
								}
								
								char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
								sendmsg4[0]='\x00';
								sendmsg4[1]=(int)mid2[magic].map_x;
								sendmsg4[2]='\x00';
								sendmsg4[3]=(int)mid2[magic].map_y;
								sendmsg4[4]='\x00';
								sendmsg4[5]=client_map_x(magic,mid2[magic].map_x);
								sendmsg4[6]='\x00';
								sendmsg4[7]=client_map_y(magic,mid2[magic].map_y);
								
								len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
								retval = send(client[mid2[magic].thread],Encrypted_Messages[imsi],len, 0);  
								
								
								char sendmsg5[5];
								sendmsg5[0]=( mid2[magic].thread & 0xff000000 ) >> 24;
								sendmsg5[1]=( mid2[magic].thread & 0x00ff0000 ) >> 16;
								sendmsg5[2]=( mid2[magic].thread & 0x0000ff00 ) >> 8;
								sendmsg5[3]=( mid2[magic].thread & 0x000000ff ) ;
								sendmsg5[4]='\x69';
								
								len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
								for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
								}
								
								
	}
}


int magic_02(int imsi,int delay,int socketnow)   // ���� 2���� ��ȥ�񹫰� �������
{
	int magic_flag=0;
	int imsi_k;
	int imsi_magic;
	int len;
	int retval;
	if(mid2[imsi].delay[2]>delay)
	{
		int nam=mid2[imsi].delay[2]-delay+25;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[2]=delay;
	if(mid2[imsi].banghyang==02) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		// printf("�Ʒ� �������� ���� �˻�\n");
 							for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
								{
									// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+2) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+3) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+4) {
										imsi_k=k;
										magic_flag=taijimap[mid2[imsi].realmap].chrnumber[k];
										magic_flag++;
									}
								} else imsi_magic++;
								
							}
							
							if(magic_flag!=0) 
							{
								mid2[imsi].map_y=mid2[imsi].map_y+3;
								return magic_flag;
							}
							
							return 0;
	}
	
	if(mid2[imsi].banghyang==01) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		// printf("������ �������� ���� �˻�\n");
 							for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
								{
									// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+3 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+4 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) {
										imsi_k=k;
										magic_flag=taijimap[mid2[imsi].realmap].chrnumber[k];
										magic_flag++;
									}
								} else imsi_magic++;
								
							}
							
							if(magic_flag!=0) 
							{
								mid2[imsi].map_x=mid2[imsi].map_x+3;
								return magic_flag;
							}
							
							return 0;
	}
	
	if(mid2[imsi].banghyang==00) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		// printf("���� �������� ���� �˻�\n");
 							for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
								{
									// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-2) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-3) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-4) {
										imsi_k=k;
										magic_flag=taijimap[mid2[imsi].realmap].chrnumber[k];
										magic_flag++;
									}
								} else imsi_magic++;
								
							}
							
							if(magic_flag!=0) 
							{
								mid2[imsi].map_y=mid2[imsi].map_y-3;
								return magic_flag;
							}
							
							return 0;
	}
	
	if(mid2[imsi].banghyang==03) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		// printf("���� �������� ���� �˻�\n");
 							for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
								{
									// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-3 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) return 0;
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-4 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y) 
									{
										imsi_k=k;
										magic_flag=taijimap[mid2[imsi].realmap].chrnumber[k];
										magic_flag++;
									}
								} else imsi_magic++;
								
							}
							
							if(magic_flag!=0) 
							{
								mid2[imsi].map_x=mid2[imsi].map_x-3;
								return magic_flag;
							}
							
							return 0;
	}
}
void magic_02_bojo(int imsi)
{
	int len,retval,mapcount,imsi_count;
	GetLocalTime( &st );
	int magic=magic_02(imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,mid2[imsi].thread);
	magic--;
	if(magic==-1) 
	{
								
		
								// printf("���� ���� �ȸ���\n");
								len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� ������ ���� �ʽ��ϴ�.",40,0x0a,1);
								//retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
								
								
	}
	
	
	else
	{
		
		
								char sendmsg2[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
								int sendmsg_byte=loginchr(imsi,sendmsg2);
								
								len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
								for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
								}
								
								char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
								sendmsg4[0]='\x00';
								sendmsg4[1]=(int)mid2[imsi].map_x;
								sendmsg4[2]='\x00';
								sendmsg4[3]=(int)mid2[imsi].map_y;
								sendmsg4[4]='\x00';
								sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
								sendmsg4[6]='\x00';
								sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
								
								len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
								retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
								
								
								char sendmsg5[5];
								sendmsg5[0]=( mid2[magic].thread & 0xff000000 ) >> 24;
								sendmsg5[1]=( mid2[magic].thread & 0x00ff0000 ) >> 16;
								sendmsg5[2]=( mid2[magic].thread & 0x0000ff00 ) >> 8;
								sendmsg5[3]=( mid2[magic].thread & 0x000000ff ) ;
								sendmsg5[4]='\x61';
								
								len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
								for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ���� ����Ʈ�� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
								}
								
								char sendmsg1[13];
								sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
								sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
								sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
								sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
								sendmsg1[4]='\x01';
								sendmsg1[5]='\x00';
								sendmsg1[6]='\x4e';
								sendmsg1[7]='\x08';
								
								len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
								for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
								}
								
	}
	
}


int magic_03(int imsi,int delay,int socketnow) // #����3  ��õ�˹�
{
	int imsi_magic;
	int len;
	int imsi_count;
	int mapcount;
	int retval;
	int target1=9999,target2=9999,target3=9999,target4=9999,target5=9999;
	if(mid2[imsi].delay[3]>delay)
	{
		int nam=mid2[imsi].delay[3]-delay+30;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[3]=delay;
	if(mid2[imsi].banghyang==00) //���� ���� ���� �������� �˻�
	{
		for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
			{
				// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
				
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-2) target2 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-3) target3 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-4) target4 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-5) target5 = k;
				
			} else imsi_magic++;
		}
		if(target1!=9999)
		{
			if(target2!=9999)
			{
				if(target3!=9999)
				{
					if(target4!=9999)
					{
						
						if(target5!=9999)
						{
							return 0;
						}
						// printf("target1,2,3,4 = %d %d %d %d �� ��õ����Ʈ�� target4�� y ��ǥ -1�� �̵�\n",target1,target2,target3,target4);
						
						if(mid2[imsi].map_y-5<0) return 0;
						char sendmsg1[13];
						sendmsg1[0]='\x00';
						sendmsg1[1]='\x00';
						sendmsg1[2]='\x00';
						sendmsg1[3]=mid2[imsi].thread;
						sendmsg1[4]='\x01';
						sendmsg1[5]='\x00';
						sendmsg1[6]='\x4e';
						sendmsg1[7]='\x08';
						
						len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
							
						}
						
						
						
						char sendmsg5[5];
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						
						mid2[imsi].map_y=mid2[imsi].map_y-5;
						char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
						int sendmsg_byte=loginchr(imsi,sendmsg2);
						len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
						sendmsg4[0]='\x00';
						sendmsg4[1]=(int)mid2[imsi].map_x;
						sendmsg4[2]='\x00';
						sendmsg4[3]=(int)mid2[imsi].map_y;
						sendmsg4[4]='\x00';
						sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
						sendmsg4[6]='\x00';
						sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
						
						len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
						
						
						
						return 0;
					}
					// printf("target1,2,3 = %d %d %d �� ��õ����Ʈ�� target3�� y ��ǥ -1�� �̵�\n",target1,target2,target3);
					if(mid2[imsi].map_y-4<0) return 0;
					char sendmsg1[13];
					sendmsg1[0]='\x00';
					sendmsg1[1]='\x00';
					sendmsg1[2]='\x00';
					sendmsg1[3]=mid2[imsi].thread;
					sendmsg1[4]='\x01';
					sendmsg1[5]='\x00';
					sendmsg1[6]='\x4e';
					sendmsg1[7]='\x08';
					
					len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
						
					}
					
					
					
					char sendmsg5[5];
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					
					mid2[imsi].map_y=mid2[imsi].map_y-4;
					char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
					int sendmsg_byte=loginchr(imsi,sendmsg2);
					len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
					sendmsg4[0]='\x00';
					sendmsg4[1]=(int)mid2[imsi].map_x;
					sendmsg4[2]='\x00';
					sendmsg4[3]=(int)mid2[imsi].map_y;
					sendmsg4[4]='\x00';
					sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
					sendmsg4[6]='\x00';
					sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
					
					len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
					retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
					return 0;
				}
				if(mid2[imsi].map_y-3<0) return 0;
				// printf("target1,2 = %d %d �� ��õ����Ʈ�� target2�� y ��ǥ -1�� �̵�\n",target1,target2);
				char sendmsg1[13];
				sendmsg1[0]='\x00';
				sendmsg1[1]='\x00';
				sendmsg1[2]='\x00';
				sendmsg1[3]=mid2[imsi].thread;
				sendmsg1[4]='\x01';
				sendmsg1[5]='\x00';
				sendmsg1[6]='\x4e';
				sendmsg1[7]='\x08';
				
				len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
					
				}
				
				
				
				char sendmsg5[5];
				sendmsg5[0]='\x00';
				sendmsg5[1]='\x00';
				sendmsg5[2]='\x00';
				sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
				sendmsg5[4]=167;
				
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				sendmsg5[0]='\x00';
				sendmsg5[1]='\x00';
				sendmsg5[2]='\x00';
				sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
				sendmsg5[4]=167;
				
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				mid2[imsi].map_y=mid2[imsi].map_y-3;
				char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
				int sendmsg_byte=loginchr(imsi,sendmsg2);
				len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
				sendmsg4[0]='\x00';
				sendmsg4[1]=(int)mid2[imsi].map_x;
				sendmsg4[2]='\x00';
				sendmsg4[3]=(int)mid2[imsi].map_y;
				sendmsg4[4]='\x00';
				sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
				sendmsg4[6]='\x00';
				sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
				
				len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
				
				return 0;
			}
			// printf("target1 = %d �� ��õ����Ʈ�� target1�� y ��ǥ -1�� �̵�\n",target1);
			if(mid2[imsi].map_y-2<0) return 0;
			char sendmsg1[13];
			sendmsg1[0]='\x00';
			sendmsg1[1]='\x00';
			sendmsg1[2]='\x00';
			sendmsg1[3]=mid2[imsi].thread;
			sendmsg1[4]='\x01';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]='\x08';
			
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
			
			
			
			char sendmsg5[5];
			sendmsg5[0]='\x00';
			sendmsg5[1]='\x00';
			sendmsg5[2]='\x00';
			sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
			sendmsg5[4]=167;
			
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			
			mid2[imsi].map_y=mid2[imsi].map_y-2;
			char sendmsg2[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
			int sendmsg_byte=loginchr(imsi,sendmsg2);
			len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
			sendmsg4[0]='\x00';
			sendmsg4[1]=(int)mid2[imsi].map_x;
			sendmsg4[2]='\x00';
			sendmsg4[3]=(int)mid2[imsi].map_y;
			sendmsg4[4]='\x00';
			sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
			sendmsg4[6]='\x00';
			sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
			
			len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			
			return 0;
		}
		// printf("%d %d %d %d\n",target1,target2,target3,target4);
		return 0;
	}
	
	
	if(mid2[imsi].banghyang==02) //�Ʒ��� ���� ����
	{
		for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
			{
				// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
				
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+2) target2 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+3) target3 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+4) target4 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+5) target5 = k;
				
			}
			else imsi_magic++;
		}
		if(target1!=9999)
		{
			if(target2!=9999)
			{
				if(target3!=9999)
				{
					if(target4!=9999)
					{
						
						if(target5!=9999)
						{
							return 0;
						}
						// printf("target1,2,3,4 = %d %d %d %d �� ��õ����Ʈ�� target4�� y ��ǥ +1�� �̵�\n",target1,target2,target3,target4);
						
						if(mid2[imsi].map_y+5>taijimap[mid2[imsi].realmap].map_y_len) return 0;
						char sendmsg1[13];
						sendmsg1[0]='\x00';
						sendmsg1[1]='\x00';
						sendmsg1[2]='\x00';
						sendmsg1[3]=mid2[imsi].thread;
						sendmsg1[4]='\x01';
						sendmsg1[5]='\x00';
						sendmsg1[6]='\x4e';
						sendmsg1[7]='\x08';
						
						len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
							
						}
						
						
						
						char sendmsg5[5];
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						
						mid2[imsi].map_y=mid2[imsi].map_y+5;
						char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
						int sendmsg_byte=loginchr(imsi,sendmsg2);
						len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
						sendmsg4[0]='\x00';
						sendmsg4[1]=(int)mid2[imsi].map_x;
						sendmsg4[2]='\x00';
						sendmsg4[3]=(int)mid2[imsi].map_y;
						sendmsg4[4]='\x00';
						sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
						sendmsg4[6]='\x00';
						sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
						
						len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
						
						
						
						return 0;
					}
					// printf("target1,2,3 = %d %d %d �� ��õ����Ʈ�� target3�� y ��ǥ +1�� �̵�\n",target1,target2,target3);
					if(mid2[imsi].map_y+4 > taijimap[mid2[imsi].realmap].map_y_len ) return 0;
					char sendmsg1[13];
					sendmsg1[0]='\x00';
					sendmsg1[1]='\x00';
					sendmsg1[2]='\x00';
					sendmsg1[3]=mid2[imsi].thread;
					sendmsg1[4]='\x01';
					sendmsg1[5]='\x00';
					sendmsg1[6]='\x4e';
					sendmsg1[7]='\x08';
					
					len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
						
					}
					
					
					
					char sendmsg5[5];
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					
					mid2[imsi].map_y=mid2[imsi].map_y+4;
					char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
					int sendmsg_byte=loginchr(imsi,sendmsg2);
					len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
					sendmsg4[0]='\x00';
					sendmsg4[1]=(int)mid2[imsi].map_x;
					sendmsg4[2]='\x00';
					sendmsg4[3]=(int)mid2[imsi].map_y;
					sendmsg4[4]='\x00';
					sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
					sendmsg4[6]='\x00';
					sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
					
					len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
					retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
					return 0;
				}
				if(mid2[imsi].map_y+3>taijimap[mid2[imsi].realmap].map_y_len) return 0;
				// printf("target1,2 = %d %d �� ��õ����Ʈ�� target2�� y ��ǥ +1�� �̵�\n",target1,target2);
				char sendmsg1[13];
				sendmsg1[0]='\x00';
				sendmsg1[1]='\x00';
				sendmsg1[2]='\x00';
				sendmsg1[3]=mid2[imsi].thread;
				sendmsg1[4]='\x01';
				sendmsg1[5]='\x00';
				sendmsg1[6]='\x4e';
				sendmsg1[7]='\x08';
				
				len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
					
				}
				
				
				
				char sendmsg5[5];
				sendmsg5[0]='\x00';
				sendmsg5[1]='\x00';
				sendmsg5[2]='\x00';
				sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
				sendmsg5[4]=167;
				
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				sendmsg5[0]='\x00';
				sendmsg5[1]='\x00';
				sendmsg5[2]='\x00';
				sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
				sendmsg5[4]=167;
				
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				mid2[imsi].map_y=mid2[imsi].map_y+3;
				char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
				int sendmsg_byte=loginchr(imsi,sendmsg2);
				len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
				sendmsg4[0]='\x00';
				sendmsg4[1]=(int)mid2[imsi].map_x;
				sendmsg4[2]='\x00';
				sendmsg4[3]=(int)mid2[imsi].map_y;
				sendmsg4[4]='\x00';
				sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
				sendmsg4[6]='\x00';
				sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
				
				len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
				
				return 0;
			}
			// printf("target1 = %d �� ��õ����Ʈ�� target1�� y ��ǥ +1�� �̵�\n",target1);
			if(mid2[imsi].map_y+2>taijimap[mid2[imsi].realmap].map_y_len) return 0;
			char sendmsg1[13];
			sendmsg1[0]='\x00';
			sendmsg1[1]='\x00';
			sendmsg1[2]='\x00';
			sendmsg1[3]=mid2[imsi].thread;
			sendmsg1[4]='\x01';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]='\x08';
			
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
			
			
			
			char sendmsg5[5];
			sendmsg5[0]='\x00';
			sendmsg5[1]='\x00';
			sendmsg5[2]='\x00';
			sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
			sendmsg5[4]=167;
			
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			
			mid2[imsi].map_y=mid2[imsi].map_y+2;
			char sendmsg2[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
			int sendmsg_byte=loginchr(imsi,sendmsg2);
			len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
			sendmsg4[0]='\x00';
			sendmsg4[1]=(int)mid2[imsi].map_x;
			sendmsg4[2]='\x00';
			sendmsg4[3]=(int)mid2[imsi].map_y;
			sendmsg4[4]='\x00';
			sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
			sendmsg4[6]='\x00';
			sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
			
			len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			
			return 0;
		}
		// printf("%d %d %d %d\n",target1,target2,target3,target4);
	}
	
	
	
	
	
	if(mid2[imsi].banghyang==01) //�Ʒ��� ���� ����
	{
		for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
			{
				// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
				
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+2) target2 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+3) target3 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+4) target4 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+5) target5 = k;
				
			}
			else imsi_magic++;
		}
		if(target1!=9999)
		{
			if(target2!=9999)
			{
				if(target3!=9999)
				{
					if(target4!=9999)
					{
						
						if(target5!=9999)
						{
							return 0;
						}
						// printf("target1,2,3,4 = %d %d %d %d �� ��õ����Ʈ�� target4�� x ��ǥ +1�� �̵�\n",target1,target2,target3,target4);
						
						if(mid2[imsi].map_x+5>taijimap[mid2[imsi].realmap].map_x_len) return 0;
						char sendmsg1[13];
						sendmsg1[0]='\x00';
						sendmsg1[1]='\x00';
						sendmsg1[2]='\x00';
						sendmsg1[3]=mid2[imsi].thread;
						sendmsg1[4]='\x01';
						sendmsg1[5]='\x00';
						sendmsg1[6]='\x4e';
						sendmsg1[7]='\x08';
						
						len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
							
						}
						
						
						
						char sendmsg5[5];
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						
						mid2[imsi].map_x=mid2[imsi].map_x+5;
						char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
						int sendmsg_byte=loginchr(imsi,sendmsg2);
						len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
						sendmsg4[0]='\x00';
						sendmsg4[1]=(int)mid2[imsi].map_x;
						sendmsg4[2]='\x00';
						sendmsg4[3]=(int)mid2[imsi].map_y;
						sendmsg4[4]='\x00';
						sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
						sendmsg4[6]='\x00';
						sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
						
						len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
						
						
						
						return 0;
					}
					// printf("target1,2,3 = %d %d %d �� ��õ����Ʈ�� target3�� x ��ǥ +1�� �̵�\n",target1,target2,target3);
					if(mid2[imsi].map_x+4 > taijimap[mid2[imsi].realmap].map_x_len ) return 0;
					char sendmsg1[13];
					sendmsg1[0]='\x00';
					sendmsg1[1]='\x00';
					sendmsg1[2]='\x00';
					sendmsg1[3]=mid2[imsi].thread;
					sendmsg1[4]='\x01';
					sendmsg1[5]='\x00';
					sendmsg1[6]='\x4e';
					sendmsg1[7]='\x08';
					
					len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
						
					}
					
					
					
					char sendmsg5[5];
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					
					mid2[imsi].map_x=mid2[imsi].map_x+4;
					char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
					int sendmsg_byte=loginchr(imsi,sendmsg2);
					len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
					sendmsg4[0]='\x00';
					sendmsg4[1]=(int)mid2[imsi].map_x;
					sendmsg4[2]='\x00';
					sendmsg4[3]=(int)mid2[imsi].map_y;
					sendmsg4[4]='\x00';
					sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
					sendmsg4[6]='\x00';
					sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
					
					len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
					retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
					return 0;
				}
				if(mid2[imsi].map_x+3>taijimap[mid2[imsi].realmap].map_x_len) return 0;
				// printf("target1,2 = %d %d �� ��õ����Ʈ�� target2�� x ��ǥ +1�� �̵�\n",target1,target2);
				char sendmsg1[13];
				sendmsg1[0]='\x00';
				sendmsg1[1]='\x00';
				sendmsg1[2]='\x00';
				sendmsg1[3]=mid2[imsi].thread;
				sendmsg1[4]='\x01';
				sendmsg1[5]='\x00';
				sendmsg1[6]='\x4e';
				sendmsg1[7]='\x08';
				
				len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
					
				}
				
				
				
				char sendmsg5[5];
				sendmsg5[0]='\x00';
				sendmsg5[1]='\x00';
				sendmsg5[2]='\x00';
				sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
				sendmsg5[4]=167;
				
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				sendmsg5[0]='\x00';
				sendmsg5[1]='\x00';
				sendmsg5[2]='\x00';
				sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
				sendmsg5[4]=167;
				
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				mid2[imsi].map_x=mid2[imsi].map_x+3;
				char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
				int sendmsg_byte=loginchr(imsi,sendmsg2);
				len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
				sendmsg4[0]='\x00';
				sendmsg4[1]=(int)mid2[imsi].map_x;
				sendmsg4[2]='\x00';
				sendmsg4[3]=(int)mid2[imsi].map_y;
				sendmsg4[4]='\x00';
				sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
				sendmsg4[6]='\x00';
				sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
				
				len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
				
				return 0;
			}
			// printf("target1 = %d �� ��õ����Ʈ�� target1�� x ��ǥ +1�� �̵�\n",target1);
			if(mid2[imsi].map_x+2>taijimap[mid2[imsi].realmap].map_x_len) return 0;
			char sendmsg1[13];
			sendmsg1[0]='\x00';
			sendmsg1[1]='\x00';
			sendmsg1[2]='\x00';
			sendmsg1[3]=mid2[imsi].thread;
			sendmsg1[4]='\x01';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]='\x08';
			
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
			
			
			
			char sendmsg5[5];
			sendmsg5[0]='\x00';
			sendmsg5[1]='\x00';
			sendmsg5[2]='\x00';
			sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
			sendmsg5[4]=167;
			
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			
			mid2[imsi].map_x=mid2[imsi].map_x+2;
			char sendmsg2[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
			int sendmsg_byte=loginchr(imsi,sendmsg2);
			len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
			sendmsg4[0]='\x00';
			sendmsg4[1]=(int)mid2[imsi].map_x;
			sendmsg4[2]='\x00';
			sendmsg4[3]=(int)mid2[imsi].map_y;
			sendmsg4[4]='\x00';
			sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
			sendmsg4[6]='\x00';
			sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
			
			len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			
			return 0;
		}
		// printf("%d %d %d %d\n",target1,target2,target3,target4);
	}
	
	
	
	if(mid2[imsi].banghyang==3) //���� ���� ���� �������� �˻�
	{
		for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
			{
				// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
				
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-2) target2 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-3) target3 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-4) target4 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-5) target5 = k;
				
			} else imsi_magic++;
		}
		if(target1!=9999)
		{
			if(target2!=9999)
			{
				if(target3!=9999)
				{
					if(target4!=9999)
					{
						
						if(target5!=9999)
						{
							return 0;
						}
						// printf("target1,2,3,4 = %d %d %d %d �� ��õ����Ʈ�� target4�� x ��ǥ -1�� �̵�\n",target1,target2,target3,target4);
						
						if(mid2[imsi].map_x-5<0) return 0;
						char sendmsg1[13];
						sendmsg1[0]='\x00';
						sendmsg1[1]='\x00';
						sendmsg1[2]='\x00';
						sendmsg1[3]=mid2[imsi].thread;
						sendmsg1[4]='\x01';
						sendmsg1[5]='\x00';
						sendmsg1[6]='\x4e';
						sendmsg1[7]='\x08';
						
						len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
							
						}
						
						
						
						char sendmsg5[5];
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						sendmsg5[0]='\x00';
						sendmsg5[1]='\x00';
						sendmsg5[2]='\x00';
						sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].thread;
						sendmsg5[4]=167;
						
						len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						
						mid2[imsi].map_x=mid2[imsi].map_x-5;
						char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
						int sendmsg_byte=loginchr(imsi,sendmsg2);
						len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
						for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
							}
							else imsi_count++;
						}
						char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
						sendmsg4[0]='\x00';
						sendmsg4[1]=(int)mid2[imsi].map_x;
						sendmsg4[2]='\x00';
						sendmsg4[3]=(int)mid2[imsi].map_y;
						sendmsg4[4]='\x00';
						sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
						sendmsg4[6]='\x00';
						sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
						
						len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
						
						
						
						return 0;
					}
					// printf("target1,2,3 = %d %d %d �� ��õ����Ʈ�� target3�� x ��ǥ -1�� �̵�\n",target1,target2,target3);
					if(mid2[imsi].map_x-4<0) return 0;
					char sendmsg1[13];
					sendmsg1[0]='\x00';
					sendmsg1[1]='\x00';
					sendmsg1[2]='\x00';
					sendmsg1[3]=mid2[imsi].thread;
					sendmsg1[4]='\x01';
					sendmsg1[5]='\x00';
					sendmsg1[6]='\x4e';
					sendmsg1[7]='\x08';
					
					len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
						
					}
					
					
					
					char sendmsg5[5];
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					sendmsg5[0]='\x00';
					sendmsg5[1]='\x00';
					sendmsg5[2]='\x00';
					sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread;
					sendmsg5[4]=167;
					
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					
					mid2[imsi].map_x=mid2[imsi].map_x-4;
					char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
					int sendmsg_byte=loginchr(imsi,sendmsg2);
					len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
					char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
					sendmsg4[0]='\x00';
					sendmsg4[1]=(int)mid2[imsi].map_x;
					sendmsg4[2]='\x00';
					sendmsg4[3]=(int)mid2[imsi].map_y;
					sendmsg4[4]='\x00';
					sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
					sendmsg4[6]='\x00';
					sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
					
					len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
					retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
					return 0;
				}
				if(mid2[imsi].map_x-3<0) return 0;
				// printf("target1,2 = %d %d �� ��õ����Ʈ�� target2�� y ��ǥ -1�� �̵�\n",target1,target2);
				char sendmsg1[13];
				sendmsg1[0]='\x00';
				sendmsg1[1]='\x00';
				sendmsg1[2]='\x00';
				sendmsg1[3]=mid2[imsi].thread;
				sendmsg1[4]='\x01';
				sendmsg1[5]='\x00';
				sendmsg1[6]='\x4e';
				sendmsg1[7]='\x08';
				
				len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
					
				}
				
				
				
				char sendmsg5[5];
				sendmsg5[0]='\x00';
				sendmsg5[1]='\x00';
				sendmsg5[2]='\x00';
				sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
				sendmsg5[4]=167;
				
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				sendmsg5[0]='\x00';
				sendmsg5[1]='\x00';
				sendmsg5[2]='\x00';
				sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread;
				sendmsg5[4]=167;
				
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				mid2[imsi].map_x=mid2[imsi].map_x-3;
				char sendmsg2[50]; // �ٸ� Ŭ���̾�Ʈ�� imsi ��ġ ����
				int sendmsg_byte=loginchr(imsi,sendmsg2);
				len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				char sendmsg4[20];        // �ڱ� Ŭ���̾�Ʈ ��ġ ������ �κ�
				sendmsg4[0]='\x00';
				sendmsg4[1]=(int)mid2[imsi].map_x;
				sendmsg4[2]='\x00';
				sendmsg4[3]=(int)mid2[imsi].map_y;
				sendmsg4[4]='\x00';
				sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
				sendmsg4[6]='\x00';
				sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
				
				len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
				
				return 0;
			}
			// printf("target1 = %d �� ��õ����Ʈ�� target1�� y ��ǥ -1�� �̵�\n",target1);
			if(mid2[imsi].map_x-2<0) return 0;
			char sendmsg1[13];
			sendmsg1[0]='\x00';
			sendmsg1[1]='\x00';
			sendmsg1[2]='\x00';
			sendmsg1[3]=mid2[imsi].thread;
			sendmsg1[4]='\x01';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]='\x08';
			
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
			
			
			
			char sendmsg5[5];
			sendmsg5[0]='\x00';
			sendmsg5[1]='\x00';
			sendmsg5[2]='\x00';
			sendmsg5[3]=mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread;
			sendmsg5[4]=167;
			
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			
			mid2[imsi].map_x=mid2[imsi].map_x-2;
			char sendmsg2[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
			int sendmsg_byte=loginchr(imsi,sendmsg2);
			len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
			sendmsg4[0]='\x00';
			sendmsg4[1]=(int)mid2[imsi].map_x;
			sendmsg4[2]='\x00';
			sendmsg4[3]=(int)mid2[imsi].map_y;
			sendmsg4[4]='\x00';
			sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
			sendmsg4[6]='\x00';
			sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
			
			len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			
			return 0;
		}
		// printf("%d %d %d %d\n",target1,target2,target3,target4);
		return 0;
	}
	
}


int magic_04(int imsi,int delay,int socketnow) // #����4 �ع�ȣ��
{
	int imsi_magic;
	
	int len;
	int imsi_count;
	int mapcount;
	int retval;
	int target1=9999,target2=9999,target3=9999,target4=9999,target5=9999;
	int target6=9999,target7=9999,target8=9999,target9=9999;
	int magic_04_delay=30;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[4]);
	if(mid2[imsi].delay[4]>delay-magic_04_delay)
	{
		int nam=mid2[imsi].delay[4]-delay+magic_04_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[4]=delay;
	if(mid2[imsi].banghyang==00) //���� ���� ���� �������� �˻�
	{
		for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
			{
				// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
				
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-2) target2 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-2) target3 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-2) target4 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-3) target5 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-3) target6 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-3) target7 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-3) target8 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-3) target9 = k;
			} else imsi_magic++;
		}
	}
	if(mid2[imsi].banghyang==01) //������ ���� ����
	{
		for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
			{
				// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
				
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+2) target2 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+2) target3 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+2) target4 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+3) target5 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+3) target6 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+3) target7 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+3) target8 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+3) target9 = k;
			} else imsi_magic++;
		}
	}
	if(mid2[imsi].banghyang==02) //�Ʒ��� ���� ���� �Ʒ������� �˻�
	{
		for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
			{
				// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
				
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+2) target2 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+2) target3 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+2) target4 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+3) target5 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+3) target6 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+3) target7 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+3) target8 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+3) target9 = k;
			} else imsi_magic++;
		}
	}
	if(mid2[imsi].banghyang==03) //���� ���� ����
	{
		for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
			{
				// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
				
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-2) target2 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-2) target3 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-2) target4 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-3) target5 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-3) target6 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-3) target7 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-3) target8 = k;
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+2 && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-3) target9 = k;
			} else imsi_magic++;
		}
	}
	
	
	if(target1!=9999 || target2!=9999 ||target3!=9999 ||target4!=9999 ||target5!=9999 ||
		target6!=9999 ||target7!=9999 ||target8!=9999 ||target9!=9999)
	{
		char sendmsg1[13];
		sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
		sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
		sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
		sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
		sendmsg1[4]='\x06';
		sendmsg1[5]='\x00';
		sendmsg1[6]='\x4e';
		sendmsg1[7]='\x08';
		
		len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	
	
	if(target1!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target1],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target1]));			 
		
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	if(target2!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target2]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target2],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target2]));			 
		
		
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	if(target3!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target3]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target3],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target3]));			 
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	if(target4!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target4]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target4],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target4]));			 
		
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	if(target5!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target5]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target5],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target5]));			 
		
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	if(target6!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target6]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target6],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target6]));			 
		
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	if(target7!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target7]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target7],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target7]));			 
		
							 
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	if(target8!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target8]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target8],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target8]));			 
		
		
		
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	
	if(target9!=9999)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].thread & 0x000000ff ) ;;
		sendmsg5[4]=164;
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].hel<mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].max_hel+1)
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].hel-200;
		else mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target9]].max_hel;
		che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target9],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target9]));			 
		
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	
}


void magic_05(int imsi,char *msg) // #����5  â��		
{
	
	
	int len,retval,mapcount,imsi_count,fflag;	
	int item_number;
	
	item_number=atoi(msg+1);
	item_number=item_number+49151;
	if(item_number>49151 && item_number<49151 + 3000)
	{
		fflag=1;
		taijimap[mid2[imsi].realmap].item_count++;
		// printf("%d\n",item_number);
		char item[19];
		item[0]='\x00';
		item[1]='\x01';
		item[2]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
		item[3]=( mid2[imsi].map_x & 0x000000ff ) ;
		item[4]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
		item[5]=( mid2[imsi].map_y & 0x000000ff ) ;
		item[6]=( taijimap[mid2[imsi].realmap].item & 0x0000ff00 ) >> 8;
		item[7]=( taijimap[mid2[imsi].realmap].item & 0x000000ff ) ;
		item[8]='\x00';
		item[9]='\x00';
		item[10]=( item_number & 0x0000ff00 ) >> 8;
		item[11]=( item_number & 0x000000ff ) ;
		item[12]='\x00';
		
		
		for(int ka=0;ka<taijimap[mid2[imsi].realmap].item_count;ka++)
		{
			if(taijimap[mid2[imsi].realmap].item_thread[ka]==0)
			{
				taijimap[mid2[imsi].realmap].item_thread[ka]=item_number;
				taijimap[mid2[imsi].realmap].item_x[ka]=mid2[imsi].map_x;
				taijimap[mid2[imsi].realmap].item_y[ka]=mid2[imsi].map_y;
				taijimap[mid2[imsi].realmap].item_number[ka]=taijimap[mid2[imsi].realmap].item;
				ka = taijimap[mid2[imsi].realmap].item_count;
			}
		}
		for(ka=0;ka<taijimap[mid2[imsi].realmap].item_count;ka++)
		{
			// printf("������ : %d\n",ka);
			// printf("�����۳ѹ� : %d\n",taijimap[mid2[imsi].realmap].item_thread[ka]);
			// printf("���� x��ǥ : %d\n",taijimap[mid2[imsi].realmap].item_x[ka]);
			// printf("���� y��ǥ: %d\n",taijimap[mid2[imsi].realmap].item_y[ka]);
			// printf("�����ۼ��� : %d\n",taijimap[mid2[imsi].realmap].item_number[ka]);
		}
		
		
		
		taijimap[mid2[imsi].realmap].item++; //���� ��������
		
		
		
		len = Xc->Enc_Pack(imsi,item,13,0x07,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ������ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
			
		}
		
	}
	
	
	
	
	if(fflag!=1)
	{
		
		for(int msgcount=0;msgcount<3000;msgcount++)
		{
			// printf("������ : %s\n",item_st[msgcount].name);
			// printf("â���� ������ : %s\n",msg+1);
			if(strcmp(item_st[msgcount].name,msg+1)==0)
			{
				
				// printf(" ������ �ѹ� : %d\n",item_st[msgcount].number);
				// printf(" msgcount : %d \n",msgcount);
				// printf(" �ִ� �������� : %d \n",item_number);
				
				
				item_number=msgcount+49151;
				//// printf(" ������ �ѹ� : %d\n",item_st[msgcount].number);
				//// printf(" �ִ� �������� : %d \n",item_number);
				taijimap[mid2[imsi].realmap].item_count++;
				// printf("%d\n",item_number);
				char item[19];
				item[0]='\x00';
				item[1]='\x01';
				item[2]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
				item[3]=( mid2[imsi].map_x & 0x000000ff ) ;
				item[4]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
				item[5]=( mid2[imsi].map_y & 0x000000ff ) ;
				item[6]=( taijimap[mid2[imsi].realmap].item & 0x0000ff00 ) >> 8;
				item[7]=( taijimap[mid2[imsi].realmap].item & 0x000000ff ) ;
				item[8]='\x00';
				item[9]='\x00';
				item[10]=( item_number & 0x0000ff00 ) >> 8;
				item[11]=( item_number & 0x000000ff ) ;
				item[12]='\x00';
				
				
				for(int ka=0;ka<taijimap[mid2[imsi].realmap].item_count;ka++)
				{
					if(taijimap[mid2[imsi].realmap].item_thread[ka]==0)
					{
						taijimap[mid2[imsi].realmap].item_thread[ka]=item_number;
						taijimap[mid2[imsi].realmap].item_x[ka]=mid2[imsi].map_x;
						taijimap[mid2[imsi].realmap].item_y[ka]=mid2[imsi].map_y;
						taijimap[mid2[imsi].realmap].item_number[ka]=taijimap[mid2[imsi].realmap].item;
						ka = taijimap[mid2[imsi].realmap].item_count;
					}
				}
				for(ka=0;ka<taijimap[mid2[imsi].realmap].item_count;ka++)
				{
					// printf("������ : %d\n",ka);
					// printf("�����۳ѹ� : %d\n",taijimap[mid2[imsi].realmap].item_thread[ka]);
					// printf("���� x��ǥ : %d\n",taijimap[mid2[imsi].realmap].item_x[ka]);
					// printf("���� y��ǥ: %d\n",taijimap[mid2[imsi].realmap].item_y[ka]);
					// printf("�����ۼ��� : %d\n",taijimap[mid2[imsi].realmap].item_number[ka]);
				}
				
				
				fflag=2;
				taijimap[mid2[imsi].realmap].item++; //���� ��������
				
				
				
				len = Xc->Enc_Pack(imsi,item,13,0x07,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ������ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
					
				}
				msgcount=2700;
				
			}
			
		}
		if(fflag != 1 && fflag !=2)
			
		{
			if(imsi==01)
			{
				for(int k=0;k<2500;k++)
				{
					if(item_st[k].name)
					{
						
						char item_msg[30];
						sprintf(item_msg,"%c%c%c%s",0x03,0x00,0x1a,item_st[k].name);
						len = Xc->Enc_Pack(imsi,item_msg,40,0x0a,1);
						//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
						
					}
				}
			}
			
			len = Xc->Enc_Pack(imsi,"\x03\00\x1a�����۹�ȣ�� 1 ~ 2417",36,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
		}
		
	}
	
	
	
	
	
	//	retval = send(client[socketnow],Encrypted_Messages[2300], len, 1); 						
	/*						char peer0_2[] = {
	0xaa, 0x00, 0x11, 0x07, 0x45, 0x0b, 0x21, 0x3d, 
	0x23, 0x2b, 0x0a, 0x2b, 0x26, 0x7f, 0xe1, 0xe1, 
	0x3c, 0x2b, 0x2a, 0x0d, 0xaa, 0x00, 0x0b, 0x0f, 
	0x46, 0x09, 0xe3, 0x6e, 0x2c, 0x08, 0x3a, 0x11, 
	0x95, 0xdb }; */
	
	/*	char item2[20];
	item2[0]='\x01';
	item2[1]=( item_number & 0x0000ff00 ) >> 8;
	item2[2]=( item_number & 0x000000ff ) ;
	item2[3]='\x00';
	item2[4]='\x20';
	strcpy(item2+5,msg+1);
	item2[5+strlen(msg+1)]='\x00';
	item2[6+strlen(msg+1)]='\x00';
	item2[7+strlen(msg+1)]='\x00';
	
	  
		len = Xc->Enc_Pack(imsi,item2,8+strlen(msg+1),0x0f,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 						*/
		//printf("%s�� â�� ���\n",mid2[imsi].id);
		
		
		
		
		
		
}

void monster_item_drop(int imsi,char *msg,int x,int y) // #���� ������ ���
{
	
	
	int len,retval,mapcount,imsi_count,fflag=0;	
	int item_number;
	
	item_number=atoi(msg+1);
	item_number=item_number+49151;
	if(item_number==0) fflag=1;
	if(item_number>49151 && item_number<49151 + 2418 && fflag==0)
	{
		fflag=1;
		taijimap[mid2[imsi].realmap].item_count++;
		// printf("%d\n",item_number);
		char item[19];
		item[0]='\x00';
		item[1]='\x01';
		item[2]=( x & 0x0000ff00 ) >> 8;
		item[3]=( x & 0x000000ff ) ;
		item[4]=( y & 0x0000ff00 ) >> 8;
		item[5]=( y & 0x000000ff ) ;
		item[6]=( taijimap[mid2[imsi].realmap].item & 0x0000ff00 ) >> 8;
		item[7]=( taijimap[mid2[imsi].realmap].item & 0x000000ff ) ;
		item[8]='\x00';
		item[9]='\x00';
		item[10]=( item_number & 0x0000ff00 ) >> 8;
		item[11]=( item_number & 0x000000ff ) ;
		item[12]='\x00';
		item[13]='\x00';
		item[14]='\x00';
		item[15]='\x00';
		item[16]='\x00';
		
		
		for(int ka=0;ka<taijimap[mid2[imsi].realmap].item_count;ka++)
		{
			if(taijimap[mid2[imsi].realmap].item_thread[ka]==0)
			{
				taijimap[mid2[imsi].realmap].item_thread[ka]=item_number;
				taijimap[mid2[imsi].realmap].item_x[ka]=x;
				taijimap[mid2[imsi].realmap].item_y[ka]=y;
				taijimap[mid2[imsi].realmap].item_number[ka]=taijimap[mid2[imsi].realmap].item;
				ka = taijimap[mid2[imsi].realmap].item_count;
			}
		}
		for(ka=0;ka<taijimap[mid2[imsi].realmap].item_count;ka++)
		{
			// printf("������ : %d\n",ka);
			// printf("�����۳ѹ� : %d\n",taijimap[mid2[imsi].realmap].item_thread[ka]);
			// printf("���� x��ǥ : %d\n",taijimap[mid2[imsi].realmap].item_x[ka]);
			// printf("���� y��ǥ: %d\n",taijimap[mid2[imsi].realmap].item_y[ka]);
			// printf("�����ۼ��� : %d\n",taijimap[mid2[imsi].realmap].item_number[ka]);
		}
		
		
		
		taijimap[mid2[imsi].realmap].item++; //���� ��������
		
		
		
		len = Xc->Enc_Pack(imsi,item,17,0x07,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ������ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
			
		}
		
	}
	
	
	
	
	
	
	
}

void magic_06(int imsi,char *msg) // #����6  ����
{
	
	int len,retval,mapcount,imsi_count,fflag=0;	
	int monster_number;
	
	
	int msgcount = 0;
	monster_default++;	
	int att = atoi(msg+1);
	if(att>0 && 700 > att) 
	{
		fflag=1;
		att=att+32767;
		taijimap[mid2[imsi].realmap].monster_count++;
		for(int ka=0;ka<taijimap[mid2[imsi].realmap].monster_count;ka++)
		{
			if(taijimap[mid2[imsi].realmap].monster_thread[ka]==0)
			{
				
				
				
				taijimap[mid2[imsi].realmap].monster_thread[ka]=monster_default;
				taijimap[mid2[imsi].realmap].monster_x[ka]=mid2[imsi].map_x;
				taijimap[mid2[imsi].realmap].monster_y[ka]=mid2[imsi].map_y;
				taijimap[mid2[imsi].realmap].monster_number[ka]=monster[att-32767].real_number;
				// printf("real : %d\n",taijimap[mid2[imsi].realmap].monster_number[ka]);
				taijimap[mid2[imsi].realmap].monster_banghyang[ka]=2;
				taijimap[mid2[imsi].realmap].monster_honma[ka]=0;
				taijimap[mid2[imsi].realmap].monster_ac[ka]=monster[monster[att-32767].number].ac;
				taijimap[mid2[imsi].realmap].monster_hel[ka]=monster[monster[att-32767].number].hel;
				taijimap[mid2[imsi].realmap].monster_max_hel[ka]=monster[monster[att-32767].number].hel;
				
				ka = taijimap[mid2[imsi].realmap].monster_count;
			}
		}
		// printf(" monster x,y : %d %d\n",taijimap[0].monster_x[0],taijimap[0].monster_y[0]);
		
		char peer0_2[15];
		peer0_2[0]='\x00';
		peer0_2[1]='\x01';
		peer0_2[2]=(mid2[imsi].map_x & 0x0000ff00 ) >> 8;
		
		peer0_2[3]=(mid2[imsi].map_x & 0x000000ff ) ;	
		peer0_2[4]=(mid2[imsi].map_y & 0x0000ff00 ) >> 8;
		peer0_2[5]=(mid2[imsi].map_y & 0x000000ff ) ;
		peer0_2[6]=(monster_default & 0xff000000 ) >> 32;
		peer0_2[7]=(monster_default & 0x00ff0000 ) >> 16;
		peer0_2[8]=(monster_default & 0x0000ff00 ) >> 8;
		peer0_2[9]=(monster_default & 0x000000ff ) ;
		peer0_2[10]=(att & 0x0000ff00 ) >> 8;
		peer0_2[11]=(att & 0x000000ff ) ;
		peer0_2[12]='\x00';
		peer0_2[13]=02;
		peer0_2[14]='\x00';
		// printf("mmimsi:%d\n",mimsi);
		mimsi++;
		char move_monster[11];
		move_monster[0]='\x01';
		move_monster[1]='\x00';
		move_monster[2]='\x04';
		move_monster[3]='\x17';
		move_monster[4]='\x00';
		move_monster[5]='\x0d';
		move_monster[6]='\x00';
		move_monster[7]='\x06';
		move_monster[8]='\x01';
		move_monster[9]='\x00';
		move_monster[10]='\x00';
		
		len = Xc->Enc_Pack(imsi,peer0_2,15,0x07,1);	
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ������ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				
			}
			else imsi_count++;
			
			
			
		}
	}
	
	
	
	
	
	if(fflag==0)
	{
		for(msgcount=0;msgcount<700;msgcount++)
		{
			if(strcmp(monster[monster[msgcount].number].name,msg+1)==0)
			{
				fflag=2;
				monster_default++;	
				taijimap[mid2[imsi].realmap].monster_count++;
				for(int ka=0;ka<taijimap[mid2[imsi].realmap].monster_count;ka++)
				{
					if(taijimap[mid2[imsi].realmap].monster_thread[ka]==0)
					{
						taijimap[mid2[imsi].realmap].monster_thread[ka]=monster_default;
						taijimap[mid2[imsi].realmap].monster_x[ka]=mid2[imsi].map_x;
						taijimap[mid2[imsi].realmap].monster_y[ka]=mid2[imsi].map_y;
						taijimap[mid2[imsi].realmap].monster_number[ka]=monster[msgcount].number;
						// printf("real : %d\n",taijimap[mid2[imsi].realmap].monster_number[ka]);
						taijimap[mid2[imsi].realmap].monster_ac[ka]=monster[monster[msgcount].number].ac;
						taijimap[mid2[imsi].realmap].monster_honma[ka]=0;
						taijimap[mid2[imsi].realmap].monster_banghyang[ka]=2;
						taijimap[mid2[imsi].realmap].monster_hel[ka]=monster[monster[msgcount].number].hel;
						taijimap[mid2[imsi].realmap].monster_max_hel[ka]=monster[monster[msgcount].number].hel;
						
						ka = taijimap[mid2[imsi].realmap].monster_count;
					}
				}
				// printf(" monster x,y : %d %d\n",taijimap[0].monster_x[0],taijimap[0].monster_y[0]);
				// printf("msgcount : %d\n",msgcount);
				char peer0_2[15];
				peer0_2[0]='\x00';
				peer0_2[1]='\x01';
				peer0_2[2]=(mid2[imsi].map_x & 0x0000ff00 ) >> 8;
				
				peer0_2[3]=(mid2[imsi].map_x & 0x000000ff ) ;	
				peer0_2[4]=(mid2[imsi].map_y & 0x0000ff00 ) >> 8;
				peer0_2[5]=(mid2[imsi].map_y & 0x000000ff ) ;
				peer0_2[6]=(monster_default & 0xff000000 ) >> 32;
				peer0_2[7]=(monster_default & 0x00ff0000 ) >> 16;
				peer0_2[8]=(monster_default & 0x0000ff00 ) >> 8;
				peer0_2[9]=(monster_default & 0x000000ff ) ;
				peer0_2[10]=(monster[msgcount].number+32767 & 0x0000ff00 ) >> 8;
				peer0_2[11]=(monster[msgcount].number+32767 & 0x000000ff ) ;
				peer0_2[12]='\x00';
				peer0_2[13]=02;
				peer0_2[14]='\x00';
				// printf("mmimsi:%d\n",mimsi);
				mimsi++;
				char move_monster[11];
				move_monster[0]='\x01';
				move_monster[1]='\x00';
				move_monster[2]='\x04';
				move_monster[3]='\x17';
				move_monster[4]='\x00';
				move_monster[5]='\x0d';
				move_monster[6]='\x00';
				move_monster[7]='\x06';
				move_monster[8]='\x01';
				move_monster[9]='\x00';
				move_monster[10]='\x00';
				
				len = Xc->Enc_Pack(imsi,peer0_2,15,0x07,1);	
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ������ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						
					}
					else imsi_count++;
					
					
					
				}
				
				
			}
		}
	}
	
	/*
	if(fflag == 0)
	{
	for(int k=0;k<1000;k++)
	{
	if(monster[k].name)
	{
				char item_msg[30];
				sprintf(item_msg,"%c%c%c%s",0x03,0x00,0x1a,monster[k].name);
				len = Xc->Enc_Pack(imsi,item_msg,40,0x0a,1);
				//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
				}
				}
				
				  len = Xc->Enc_Pack(imsi,"\x03\00\x1a���ʹ� 1 ~ 616",36,0x0a,1);
				  retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
				  
			}*/
	
	
	
			//printf("%s�� ���� ���\n",mid2[imsi].id);
			
			
			
			// int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
			
			
			
}




void magic_07(int imsi,char *msg,int *kaflag) // #����7 ��ȯ
{
	int len,retval;	
	
	
	if(mid2[imsi].realmap!=15)
		teleport(imsi,&*kaflag,4,9,15);
	else
	{
		mid2[imsi].map_x=4;
		mid2[imsi].map_y=9;
		ctrl_r(imsi);
	}
	
	
	
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=33;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	// int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
	
	
	
}

void magic_08(int imsi,char *msg,int *kaflag) // #����8 �񿵻�õ��
{
	
	char sendmsg2[20];
	sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg2[4]='\x00';
	int len,retval;
	if(strcmp(msg+1,"��")==0)
	{
		if(mid2[imsi].realmap!=14)
			teleport(imsi,&*kaflag,76,141,14);
		else
		{
			mid2[imsi].map_x=76;
			mid2[imsi].map_y=141;
			
			
			
			
			
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount]!=mid2[imsi].thread)
					{
						int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
						// printf("len = %d\n",len);
						packet_dump(sendmsg2,5,16);
						packet_dump(Encrypted_Messages[imsi],10,16);
						// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			ctrl_r(imsi);
			
		}
	}
	if(strcmp(msg+1,"��")==0)
	{
		if(mid2[imsi].realmap!=14)
			teleport(imsi,&*kaflag,76,22,14);
		else
		{
			mid2[imsi].map_x=76;
			mid2[imsi].map_y=22;
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount]!=mid2[imsi].thread)
					{
						int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
						// printf("len = %d\n",len);
						packet_dump(sendmsg2,5,16);
						packet_dump(Encrypted_Messages[imsi],10,16);
						// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			
			ctrl_r(imsi);
		}
	}
	if(strcmp(msg+1,"��")==0)
	{
		if(mid2[imsi].realmap!=14)
			teleport(imsi,&*kaflag,135,87,14);
		else
		{
			mid2[imsi].map_x=135;
			mid2[imsi].map_y=87;
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount]!=mid2[imsi].thread)
					{
						int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
						// printf("len = %d\n",len);
						packet_dump(sendmsg2,5,16);
						packet_dump(Encrypted_Messages[imsi],10,16);
						// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			
			ctrl_r(imsi);
		}
	}
	if(strcmp(msg+1,"��")==0)
	{
		if(mid2[imsi].realmap!=14)
			teleport(imsi,&*kaflag,8,87,14);
		else
		{
			mid2[imsi].map_x=8;
			mid2[imsi].map_y=87;
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount]!=mid2[imsi].thread)
					{
						int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
						// printf("len = %d\n",len);
						packet_dump(sendmsg2,5,16);
						packet_dump(Encrypted_Messages[imsi],10,16);
						// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			
			ctrl_r(imsi);
		}
	}
	
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=1;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	
	
	
	
	
	
	// int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
	
	
	
}

int magic_09(int imsi,char *msg,int *kaflag,int delay) // #����9 ��ȯ
{
	int len,retval;	
	
	int t=0;
	for(int i=0;i<frecnum;i++)
	{
		// printf("�ӼӸ� ���̵� : %s\n",msg+1);
		// printf("�ҷ��� ���̵� : %s\n",mid[i].id);
		if(strcmp(msg+1,mid2[i].id)==0)
		{
			t = i;
			i=frecnum;
		}
	}
	
	
	if(mid2[t].thread==0 || mid2[t].level > mid2[imsi].level)
	{
		char len = Xc->Enc_Pack(imsi,"\x00\00\x2d���� ���������� �ʰų� ������ ��ġ�� ����",60,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		// printf("������ �ƴ�   \n");
		
	}
	else
	{
		int magic_09_delay=60;
		// printf("���� �ð� : %d\n",delay);
		// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[9]);
		if(mid2[imsi].delay[9]>delay-magic_09_delay)
		{
			int nam=mid2[imsi].delay[9]-delay+magic_09_delay;
			char sendmsg[21],msg[4];
			memset(sendmsg,32,21);
			sendmsg[0]='\x03';
			sendmsg[1]='\x00';
			sendmsg[2]='\x1a';
			itoa(nam,msg,10);
			memcpy(sendmsg+3,msg,strlen(msg));
			strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
			sendmsg[20]='\x00';
			sendmsg[21]='\x00';
			len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			// printf("���� �����̰� �ȵ�\n");
			return 0;
		}
		mid2[imsi].delay[9]=delay;
		if(taijimap[mid2[imsi].realmap].sohwan_on==2)
		{
			len = Xc->Enc_Pack(imsi,"\x00\00\x2d�̰��� ����ϼ� �����ϴ�.",60,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			return 0;
			
		}
		if(taijimap[mid2[t].realmap].sohwan_on==2)
		{
			len = Xc->Enc_Pack(imsi,"\x00\00\x2d�װ��� ������ �ȹ�Ĩ�ϴ�.",60,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			return 0;
			
		}
		
		if(mid2[t].realmap!=mid2[imsi].realmap)
		{
			
			
			teleport(t,&mid2[t].kaflag,mid2[imsi].map_x,mid2[imsi].map_y,mid2[imsi].realmap);	
			
		}
		else
		{
			mid2[t].map_x=mid2[imsi].map_x;
			mid2[t].map_y=mid2[imsi].map_y;
			ctrl_r(t);
		}
	}
	
	
	
	
}

int magic_10(int imsi,char *msg,int *kaflag,int delay) // #����10 ���
{
	int len,retval;	
	
	int t=0;
	for(int i=0;i<frecnum;i++)
	{
		// printf("�ӼӸ� ���̵� : %s\n",msg+1);
		// printf("�ҷ��� ���̵� : %s\n",mid[i].id);
		if(strcmp(msg+1,mid2[i].id)==0)
		{
			t = i;
			i=frecnum;
		}
	}
	
	if(mid2[t].thread==0 || mid2[t].level >= mid2[imsi].level)
	{
		char len = Xc->Enc_Pack(imsi,"\x00\00\x2d���� ������ or ���¸���ħ",60,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		// printf("������ �ƴ�   \n");
		
	}
	else
	{
		int magic_10_delay=30;
		// printf("���� �ð� : %d\n",delay);
		// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[10]);
		if(mid2[imsi].delay[10]>delay-magic_10_delay)
		{
			int nam=mid2[imsi].delay[10]-delay+magic_10_delay;
			char sendmsg[21],msg[4];
			memset(sendmsg,32,21);
			sendmsg[0]='\x03';
			sendmsg[1]='\x00';
			sendmsg[2]='\x1a';
			itoa(nam,msg,10);
			memcpy(sendmsg+3,msg,strlen(msg));
			strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
			sendmsg[20]='\x00';
			sendmsg[21]='\x00';
			len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			// printf("���� �����̰� �ȵ�\n");
			return 0;
		}
		mid2[imsi].delay[10]=delay;
		
		
		if(taijimap[mid2[t].realmap].chooldo_on==2)
		{
			len = Xc->Enc_Pack(imsi,"\x00\00\x2d�װ��� ����ϼ� �����ϴ�.",60,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
			return 0;
			
		}
		if(mid2[t].realmap!=mid2[imsi].realmap)
		{
			
			
			teleport(imsi,&mid2[imsi].kaflag,mid2[t].map_x,mid2[t].map_y,mid2[t].realmap);	
			
		}
		else
		{
			mid2[imsi].map_x=mid2[t].map_x;
			mid2[imsi].map_y=mid2[t].map_y;
			ctrl_r(imsi);
		}
	}
	
	
	
	
}

void magic_11(int imsi,char *msg,int *kaflag,int delay) // #����11 ���Ǽ�ȯ
{
	int len,retval;	
	int t=0;
	for(int i=0;i<frecnum;i++)
	{
		// printf("�ӼӸ� ���̵� : %s\n",msg+1);
		// printf("�ҷ��� ���̵� : %s\n",mid[i].id);
		if(strcmp(msg+1,mid2[i].id)==0)
		{
			t = i;
			i=frecnum;
		}
	}
	
	
	
	if(mid2[t].thread==0 || mid2[t].level > mid2[imsi].level)
	{
		char len = Xc->Enc_Pack(imsi,"\x00\00\x2d���� ���������� �ʰų� ������ ��ġ�� ����",60,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		// printf("������ �ƴ�   \n");
		
	}
	else
	{
		
		
		if(mid2[t].realmap!=mid2[imsi].realmap)
		{
			
			
			teleport(t,&mid2[t].kaflag,mid2[imsi].map_x,mid2[imsi].map_y,mid2[imsi].realmap);	
			
		}
		else
		{
			mid2[t].map_x=mid2[imsi].map_x;
			mid2[t].map_y=mid2[imsi].map_y;
			ctrl_r(t);
		}
	}
	
	
	/*
	int len,retval;	
	
	  int t=finduser_group(msg);
	  
		
		  if(t==0)
		  {
		  char len = Xc->Enc_Pack(imsi,"\x00\00\x2d���� ���������� �ʰų� ������ ��ġ�� ����",60,0x0a,1);
		  retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		  // printf("������ �ƴ�   \n");
		  
			}
			else
			{
			
			  if(mid2[t].realmap!=mid2[imsi].realmap)
			  {
			  
				
				  teleport(t,&mid2[t].kaflag,mid2[imsi].map_x,mid2[imsi].map_y,mid2[imsi].realmap);	
				  
					}
					else
					{
					mid2[t].map_x=mid2[imsi].map_x;
					mid2[t].map_y=mid2[imsi].map_y;
					ctrl_r(t);
					}
}*/
	
	
	
	
}


void magic_12(int imsi,char *msg,int *kaflag,int delay) // #����12 ��Ȳ��
{
	int len,retval;	
	
	
	if(mid2[imsi].realmap!=129)
		teleport(imsi,&*kaflag,5,8,129);
	else
	{
		mid2[imsi].map_x=5;
		mid2[imsi].map_y=8;
		ctrl_r(imsi);
	}
	
	
	
	
}

int magic_13(int imsi,char *msg,int *kaflag,int delay) // #����13 �����Ǳ��
{
	int magic_13_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[13]>delay-magic_13_delay)
	{
		int nam=mid2[imsi].delay[13]-delay+magic_13_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[12] > 3)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[12]++;
	}
	else
	{
		mid2[imsi].delay[12] = 0;
	}
	mid2[imsi].delay[13]=delay;
	
	int len,retval;	
	
	char sendmsg5[5];
	sendmsg5[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg5[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg5[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg5[3]=( mid2[imsi].thread & 0x000000ff ) ;;
	sendmsg5[4]=5;
	len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	len = Xc->Enc_Pack(imsi,"\x03\00\x2a�����Ǳ���� �ܿ����ϴ�.",36,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	mid2[imsi].hel=mid2[imsi].hel+50;
	if(mid2[imsi].hel>mid2[imsi].max_hel)
		mid2[imsi].hel=mid2[imsi].max_hel;
	
	exp_money(imsi,imsi);
	che_bar(imsi,imsi,hel_percent(imsi));	
	
	
	
	
	
}

void magic_14(int imsi,char *msg,int *kaflag,int delay) // #����14 ��������
{
	for(int i=0;i<frecnum;i++)
	{
		if(mid2[i].thread!=0)
			mid[i]=mid2[i];
	}
	fwrite();
	char test[50];
	memset(test,50,1);
	int len = Xc->Enc_Pack(imsi,test,50,33,1);
	
	for(int k=0;k<frecnum;k++)
	{
		if(mid2[k].thread != 0)
		{
			
			int retval = send(client[mid2[k].thread],Encrypted_Messages[imsi],len, 0);
		}
		
	}
	
	
	
	
}

int magic_15(int imsi,char *msg,int *kaflag,int delay) // #����15 ������
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int magic_15_delay=10;
	int len,retval;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[10]);
	if(mid2[imsi].delay[15]>delay-magic_15_delay)
	{
		int nam=mid2[imsi].delay[15]-delay+magic_15_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[15]=delay;
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	sprintf(sendmsg,"%c%c%c%s: %s",0x04,0x00,strlen(mid2[imsi].id)+2+strlen(msg+1),mid2[imsi].id,msg+1);
	for(int k=0;k<frecnum;k++)
	{
		if(mid2[k].thread != 0)
		{
			
			int len = Xc->Enc_Pack(imsi,sendmsg,strlen(mid2[imsi].id)+2+strlen(msg+1)+3,0x0a,1);
			int retval = send(client[mid2[k].thread],Encrypted_Messages[imsi],len, 0);
		}
		
	}
	
	
	
	
	
	
	
	
}


void magic_16(int imsi,char *msg,int *kaflag,int delay) // #����16 ü�»��
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	if(mid2[imsi].exp>=setting_st.exp)
	{
		sprintf(sendmsg,"%c%c%cü���� %u �ö����ϴ�.",'\x03','\x01','\x01',setting_st.heal);
		
		int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		mid2[imsi].exp=mid2[imsi].exp-setting_st.exp;
		mid2[imsi].max_hel=mid2[imsi].max_hel+setting_st.heal;
		exp_money(imsi,imsi);
		
	}
	else
	{
		sprintf(sendmsg,"%c%c%c����ġ�� ���ڸ��ϴ�.",'\x03','\x01','\x01');
		
		int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	}
	
	
	
	
	
	
}



int magic_17(int imsi,char *msg,int *kaflag,int delay) // #����17 ��ȣ��
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	
	int magic_17_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[17]>delay-magic_17_delay)
	{
		int nam=mid2[imsi].delay[17]-delay+magic_17_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[17]=delay;
	
	int target1=9999,target2=8888;
	int check=0;
	int k,imsi_magic;
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				
			}
		} else imsi_magic++;
	}
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y-1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x-1) target2 = k;
				
			}
		} else imsi_magic++;
		// printf("target = %d k = %d\n",target2,k);
	}
	
	
	
	if(target1!=9999 && taijimap[mid2[imsi].realmap].pk_on==1) // �ΰ��� ���
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[target1].group)
				return 0;
		}
		int dam=5;  // �⺻ ������ 5
		
		
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x000000ff ) ;;
		sendmsg5[4]=67;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x14��ȣ���� �ܿ����ϴ�.",23,0x0a,1);
		//int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac ==0)
			dam = mid2[imsi].hel;
		else
			dam = (mid2[imsi].hel)+float(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac*0.01)*(mid2[imsi].hel*2);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
		
		
		
		
		
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel != 0)
		{
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel-dam;
			if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel>mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel || 
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel == 0)
			{
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel=0;
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].sangtae=1;
				char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
				int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[target1],sendmsg2);
				
				int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
			}
			
			che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target1],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target1]));	
			
		}
		check=1;
		
		
		
		
		
	}
	if(target2!=8888) // �����ϰ��
	{
		
		int dam;
		char sendmsg5[5];
		
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=67;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		
		len = Xc->Enc_Pack(imsi,"\x03\00\x14��ȣ���� �ܿ����ϴ�.",23,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
		
		
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
			dam = (mid2[imsi].hel);
		else
			dam = (mid2[imsi].hel)+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*(mid2[imsi].hel*2);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
			taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
		////LeaveCriticalSection(&monster_cs);
		check=1;
		
		
	}
	if(check==1)
	{char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x01';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x10';
	sendmsg1[7]=87;
	
	int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	exp_money(imsi,imsi);
	sprintf(sendmsg,"%c%c%c%c%c%c��ȣ��!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	}
	if(mid2[imsi].hel==0) mid2[imsi].hel=1;
	
}


void magic_18(int imsi,char *msg,int *kaflag,int delay) // #����18 ���»��
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	if(mid2[imsi].exp>=setting_st.exp_mana)
	{
		sprintf(sendmsg,"%c%c%c������ %u �ö����ϴ�.",'\x03','\x01','\x01',setting_st.mana);
		
		int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		mid2[imsi].exp=mid2[imsi].exp-setting_st.exp_mana;
		mid2[imsi].max_mana=mid2[imsi].max_mana+setting_st.mana;
		exp_money(imsi,imsi);
		
	}
	else
	{
		sprintf(sendmsg,"%c%c%c����ġ�� ���ڸ��ϴ�.",'\x03','\x01','\x01');
		
		int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	}
	
	
	
	
	
	
}

int magic_19(int imsi,char *msg,int *kaflag,int delay) // #����19 �����Ǳ��
{
	
	int magic_19_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[19]>delay-magic_19_delay)
	{
		int nam=mid2[imsi].delay[19]-delay+magic_19_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[8] > 3)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[8]++;
	}
	else
	{
		mid2[imsi].delay[8] = 0;
	}
	mid2[imsi].delay[19]=delay;
	
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	packet_dump(msg,16,16);
	
	int len,retval;
	unsigned int asdf = 0;
	char cTmp[4]; 
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000)
	{
		if(mid2[imsi].mana>=setting_st.magic19_mana)
		{
			mid2[imsi].mana=mid2[imsi].mana-setting_st.magic19_mana;
			exp_money(imsi,imsi);
			
			
			
			
			
			int len,retval;	
			
			
			char sendmsg5[5];
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=5;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			len = Xc->Enc_Pack(imsi,"\x03\00\x18�����Ǳ���� �ܿ����ϴ�.",27,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+setting_st.magic19_hel;
			if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
				mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
			char sendmsg666[100];
			if(imsi!=thread_imsi[asdf])
			{
				sprintf(sendmsg666,"%s�Բ��� �����Ǳ���� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
				sangtae2(imsi,thread_imsi[asdf],sendmsg666);
			}
			
			exp_money(imsi,thread_imsi[asdf]);
			che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
			char sendmsg1[13];
			sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg1[4]='\x06';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]=3;
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
	}
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	
	
	
	
	
	
}


int magic_20(int imsi,char *msg,int *kaflag,int delay) // #����20 ��������
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	
	int magic_20_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[20]>delay-magic_20_delay)
	{
		int nam=mid2[imsi].delay[20]-delay+magic_20_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[20]=delay;
	
	int kkk;
	kkk=rand()%2;
	if(kkk==1)
	{
		char sendmsg5[5];
		sendmsg5[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[imsi].thread & 0x000000ff ) ;;
		sendmsg5[4]=11;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x16���������� �ܿ����ϴ�.",25,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
		
		mid2[imsi].mana=mid2[imsi].max_mana;
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].max_mana*0.4;
		if(mid2[imsi].hel<100 || mid2[imsi].hel > mid2[imsi].max_hel || mid2[imsi].hel < 0)
			mid2[imsi].hel = 100;
		exp_money(imsi,imsi);
		char sendmsg1[13];
								sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
								sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
								sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
								sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
								sendmsg1[4]='\x06';
								sendmsg1[5]='\x00';
								sendmsg1[6]='\x4e';
								sendmsg1[7]=65;
								len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
								for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
									
								}
	}
	else
	{
		len = Xc->Enc_Pack(imsi,"\x03\00\x1a�������߿� �����Ͽ����ϴ�.",29,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
	}
	
	
	
	
	
	
	
}

int magic_21(int imsi,char *msg,int *kaflag,int delay) // #����21 ��ȣ�����
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	
	
	int magic_21_delay=mid2[imsi].delay[7];
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[21]);
	if(mid2[imsi].delay[21]>delay-magic_21_delay)
	{
		int nam=mid2[imsi].delay[21]-delay+magic_21_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[21]=delay;
	char cTmp[4]; 
    int unsigned asdf; 
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
    
	
	
	if(asdf<100000)
	{
		if(mid2[imsi].mana!=0)
		{
			
			switch(mid2[imsi].sword)
			{
			case 12:
				{
					mid2[imsi].delay[7]=rand()%50;
					break;
				}
			case 51:
				{
					mid2[imsi].delay[7]=rand()%40;
					break;
				}
			case 90:
				{
					mid2[imsi].delay[7]=rand()%30;
					break;
				}
			case 91:
				{
					mid2[imsi].delay[7]=rand()%20;
					break;
				}
			case 92:
				{
					mid2[imsi].delay[7]=rand()%10;
					break;
				}
			default :
				{
					mid2[imsi].delay[7]=rand()%60;
					break;
				}
			}
			// printf("delay:%d\n",mid2[imsi].delay[21]);
			int up=mid2[imsi].mana*1.5;
			mid2[imsi].mana=mid2[imsi].mana-mid2[imsi].mana*0.5;
			exp_money(imsi,imsi);
			
			
			
			
			
			int len,retval;	
			
			char sendmsg5[5];
			
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=64;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			len = Xc->Enc_Pack(imsi,"\x03\00\x18��ȣ������� �ܿ����ϴ�.",27,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+up*1.5;
			if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
				mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
			
			char sendmsg666[100];
			if(imsi!=thread_imsi[asdf])
			{
				sprintf(sendmsg666,"%s�Բ��� ��ȣ������� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
				sangtae2(imsi,thread_imsi[asdf],sendmsg666);
			}
			
			exp_money(imsi,thread_imsi[asdf]);
			che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));
			char sendmsg1[13];
			sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg1[4]='\x06';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]=95;
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
	}
	
	
	
	
	
	
	
	
}


int magic_22(int imsi,char *msg,int *kaflag,int delay) // #����22 �����̾�
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_22_delay;
	switch(mid2[imsi].sword)
	{
	case 50:
		{
			magic_22_delay=7;
			break;
		}
	case 73:
		{
			magic_22_delay=6;
			break;
		}
	case 74:
		{
			magic_22_delay=5;
			break;
		}
	case 75:
		{
			magic_22_delay=4;
			break;
		}
	case 13:
		{
			magic_22_delay=8;
			break;
		}
	default:
		{
			magic_22_delay=9;
			break;
		}
		
	}
	//magic_22_delay=9;
	
	if(mid2[imsi].delay[22]>delay-magic_22_delay)
	{
		int nam=mid2[imsi].delay[22]-delay+magic_22_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[22]=delay;
	char cTmp[4]; 
    int unsigned asdf; 
	int unsigned target2=0;
	char sendmsg5[5];
	int unsigned dam;
	sprintf(sendmsg,"%c%c%c%c%c%c�����̾�!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000 && asdf!=0 && taijimap[mid2[imsi].realmap].pk_on==1 && thread_imsi[asdf]!=imsi)
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[thread_imsi[asdf]].group)
				return 0;
		}
		
		if(mid2[thread_imsi[asdf]].realmap==mid2[imsi].realmap)
		{
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=8;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			if(mid2[thread_imsi[asdf]].ac ==0)
				dam = mid2[imsi].mana*1.5;
			else
				dam = mid2[imsi].mana*1.5+float(mid2[thread_imsi[asdf]].ac*0.01)*mid2[imsi].mana*1.5;
			
			mid2[imsi].mana=0;
			
			
			
			
			
			
			
			if(mid2[thread_imsi[asdf]].hel != 0)
			{
				mid2[thread_imsi[asdf]].hel = mid2[thread_imsi[asdf]].hel-dam;
				if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel || 
					mid2[thread_imsi[asdf]].hel == 0)
				{
					mid2[thread_imsi[asdf]].hel=0;
					mid2[thread_imsi[asdf]].sangtae=1;
					char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
					int sendmsg_byte=loginchr(thread_imsi[asdf],sendmsg2);
					
					int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
				}
				
				che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
				
			}
			
			
			
			
		}
		return 0;
	}
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(asdf==taijimap[mid2[imsi].realmap].monster_thread[k])  // ���ʳ� ������
			{
				target2=0;
				target2=k;
			}
		}
		else
			imsi_magic++;
	}
	if(taijimap[mid2[imsi].realmap].monster_thread[target2]==0) return 0;
	
	
	
	
	
	//EnterCriticalSection(&monster_cs);
	if(taijimap[mid2[imsi].realmap].monster_thread[target2] != 0) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=8;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	else printf(" �����̾� ���� \n\n\n\n\n\n\n\n\n");
	//LeaveCriticalSection(&monster_cs);
	len = Xc->Enc_Pack(imsi,"\x03\00\x18�����̾ �ܿ����ϴ�.",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=73;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
		dam = mid2[imsi].mana*1.5;
	else
		dam = mid2[imsi].mana*1.5+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*mid2[imsi].mana*1.5;
	
	mid2[imsi].mana=0;
	
	
	taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
	
	
	if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
		taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
	// printf("���� ����\n\n\n");
	
	monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
	//EnterCriticalSection(&monster_cs);		
	if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
	taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
	exp_money(imsi,imsi);
	////LeaveCriticalSection(&monster_cs);
	
	
	
	
	
	
}


int magic_23(int imsi,char *msg,int *kaflag,int delay) // #����23 ��������
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_23_delay=240;
	
	if(mid2[imsi].delay[23]>delay-magic_23_delay)
	{
		int nam=mid2[imsi].delay[23]-delay+magic_23_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[23]=delay;
	int unsigned dam;
	int unsigned target2=0;
	
	
	sprintf(sendmsg,"%c%c%c%c%c%c��������!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=107;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	
	
	
	
    
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(taijimap[mid2[imsi].realmap].monster_x[k] < mid2[imsi].map_x+12 &&
				taijimap[mid2[imsi].realmap].monster_x[k] > mid2[imsi].map_x-12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] < mid2[imsi].map_y+12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] > mid2[imsi].map_y-12 
				)  // ���ʳ� ������
			{
				
				target2=k;
				
				
				
				char sendmsg5[5];
				//EnterCriticalSection(&monster_cs);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2] != 0) 
				{
					sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
					sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
					sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
					sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
					sendmsg5[4]=104;
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
				}
				//LeaveCriticalSection(&monster_cs);
				
				if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
					dam = mid2[imsi].mana*1.5;
				else
					dam = mid2[imsi].mana*1.5+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*mid2[imsi].mana*1.5;
				
				taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
				
				
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
					taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
				// printf("���� ����\n\n\n");
				
				monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
				//EnterCriticalSection(&monster_cs);		
				//printf("�������� ���� �״´�\n");
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
				taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
				//LeaveCriticalSection(&monster_cs);
				
				
				
				
			}
		}
		else
			imsi_magic++;
	}
	len = Xc->Enc_Pack(imsi,"\x03\00\x18���������� �ܿ����ϴ�.  ",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	mid2[imsi].mana=0;
	exp_money(imsi,imsi);
	
	
	
	
	
}


int magic_24(int imsi,char *msg,int *kaflag,int delay) // #����24 ��ȣ�����'÷
{
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	if(mid2[imsi].group==0 || mid2[imsi].group==-1)
	{
		sangtae(imsi,"�׷�ƴ� ���¿��� ���� ����");
		return 0;
		
		
	}
	
	
	int magic_24_delay=mid2[imsi].delay[124];
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[21]);
	if(mid2[imsi].delay[24]>delay-magic_24_delay)
	{
		int nam=mid2[imsi].delay[24]-delay+magic_24_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[24]=delay;
	
	char cTmp[4]; 
    int unsigned asdf; 
	int up;
	
	
	
	int member_count=0;
    
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			if(mid2[thread_imsi[taijimap[mid2[imsi].realmap].threadlist[mapcount]]].group==mid2[imsi].group && (mid2[imsi].group != 0)
				&& (mid2[imsi].group != -1))
				member_count++;
			
		}
		else imsi_count++;
	}
	
	
	
	if(mid2[imsi].mana!=0 && member_count!=0)
	{
		
		
		
		if(mid2[imsi].delay[124]==0)
			mid2[imsi].delay[124]=1;
		switch(mid2[imsi].sword)
		{
		case 12:
			{
				mid2[imsi].delay[124]=rand()%50;
				break;
			}
		case 51:
			{
				mid2[imsi].delay[124]=rand()%40;
				break;
			}
		case 90:
			{
				mid2[imsi].delay[124]=rand()%30;
				break;
			}
		case 91:
			{
				mid2[imsi].delay[124]=rand()%20;
				break;
			}
		case 92:
			{
				mid2[imsi].delay[124]=rand()%10;
				break;
			}
		default :
			{
				mid2[imsi].delay[124]=rand()%60;
				break;
			}
		}
		if(member_count>7)
			mid2[imsi].delay[124]=1;
		
		// printf("delay:%d\n",mid2[imsi].delay[21]);
		up=mid2[imsi].mana*1.5;
		mid2[imsi].mana=mid2[imsi].mana-mid2[imsi].mana*0.5;
		exp_money(imsi,imsi);
		char sendmsg1[13];
								sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
								sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
								sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
								sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
								sendmsg1[4]='\x06';
								sendmsg1[5]='\x00';
								sendmsg1[6]='\x4e';
								sendmsg1[7]=110;
								len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
								for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
									
								}
								member_count--;
								if(member_count==0) member_count=1;
								up=mid2[imsi].mana*1.5/member_count;
								
								
								
								
								
								
								
								int len,retval;	
								char sendmsg5[5];
								char c_buffer[70];
								for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										if(taijimap[mid2[imsi].realmap].chrnumber[mapcount] != imsi)
										{
											if(mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].realmap==mid2[imsi].realmap )
											{
												if(mid2[thread_imsi[taijimap[mid2[imsi].realmap].threadlist[mapcount]]].group==mid2[imsi].group && (mid2[imsi].group != 0 &&
													mid2[imsi].group != -1))
												{
													asdf = taijimap[mid2[imsi].realmap].threadlist[mapcount];
													sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
													sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
													sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
													sendmsg5[3]=( asdf & 0x000000ff ) ;;
													sendmsg5[4]=109;
													len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
													for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
													{
														if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
														{
															// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
															retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
														}
														else imsi_count++;
													}
													sprintf(c_buffer,"%s�Բ��� ��ȣ�����'÷�� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
													sangtae2(imsi,thread_imsi[asdf],c_buffer);
													
													mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+up*1.5;
													if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
														mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
													
													exp_money(imsi,thread_imsi[asdf]);
													che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));
												}
											}
										}
										
										
										
									}
									else imsi_count++;
								}
								
								
								
								
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
}


int magic_25(int imsi,char *msg,int *kaflag,int delay) // #����25 ��Ȱ
{
	
	int magic_25_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[25]>delay-magic_25_delay)
	{
		int nam=mid2[imsi].delay[25]-delay+magic_25_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		
		return 0;
		
	}
	
	mid2[imsi].delay[25]=delay;
	
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	packet_dump(msg,16,16);
	
	int len,retval;
	unsigned int asdf = 0;
	char cTmp[4]; 
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000 && mid2[thread_imsi[asdf]].sangtae==1)
	{
		
		char sendmsg5[5];
		sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
		sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( asdf & 0x000000ff ) ;;
		sendmsg5[4]=11;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x16��Ȱ�� �ܿ��ּ̽��ϴ�.",25,0x0a,1);
		retval = send(client[asdf],Encrypted_Messages[imsi],len, 0);
		mid2[thread_imsi[asdf]].sangtae=0;
		mid2[thread_imsi[asdf]].hel=2;
		exp_money(imsi,imsi);
		char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
		int sendmsg_byte=loginchr(thread_imsi[asdf],sendmsg2);
		
		len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	
	
}

int magic_26(int imsi,char *msg,int *kaflag,int delay) // #����26 ����������
{
	dont_move_save();
	int len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����     ",20,0x0a,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	return 0;
	
}
int magic_27(int imsi,char *msg,int *kaflag,int delay) // #����27 ������
{
	switch(mid2[imsi].banghyang)
	{
	case 0: // ���ʺ��� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				
				if(taijimap[mid2[imsi].realmap].dont_move_x[k]==mid2[imsi].map_x&&
					taijimap[mid2[imsi].realmap].dont_move_y[k]==mid2[imsi].map_y-1) 
				{
					int len = Xc->Enc_Pack(imsi,"\x03\00\x11�̹� ������ ���� ",20,0x0a,1);
					int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
					
				}
			}
			
			taijimap[mid2[imsi].realmap].dont_move_x[taijimap[mid2[imsi].realmap].dont_move_count]=mid2[imsi].map_x;
			taijimap[mid2[imsi].realmap].dont_move_y[taijimap[mid2[imsi].realmap].dont_move_count]=mid2[imsi].map_y-1;
			taijimap[mid2[imsi].realmap].dont_move_count++;
			break;
		}
	case 1: // ���ʺ��� ������
		{
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				
				if(taijimap[mid2[imsi].realmap].dont_move_x[k]==mid2[imsi].map_x+1&&
					taijimap[mid2[imsi].realmap].dont_move_y[k]==mid2[imsi].map_y) 
				{
					int len = Xc->Enc_Pack(imsi,"\x03\00\x11�̹� ������ ���� ",20,0x0a,1);
					int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
					
				}
			}
			taijimap[mid2[imsi].realmap].dont_move_x[taijimap[mid2[imsi].realmap].dont_move_count]=mid2[imsi].map_x+1;
			taijimap[mid2[imsi].realmap].dont_move_y[taijimap[mid2[imsi].realmap].dont_move_count]=mid2[imsi].map_y;
			taijimap[mid2[imsi].realmap].dont_move_count++;
			break;
		}
	case 2: // �Ʒ����� ������
		{
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				
				if(taijimap[mid2[imsi].realmap].dont_move_x[k]==mid2[imsi].map_x&&
					taijimap[mid2[imsi].realmap].dont_move_y[k]==mid2[imsi].map_y+1) 
				{
					int len = Xc->Enc_Pack(imsi,"\x03\00\x11�̹� ������ ���� ",20,0x0a,1);
					int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
					
				}
			}
			taijimap[mid2[imsi].realmap].dont_move_x[taijimap[mid2[imsi].realmap].dont_move_count]=mid2[imsi].map_x;
			taijimap[mid2[imsi].realmap].dont_move_y[taijimap[mid2[imsi].realmap].dont_move_count]=mid2[imsi].map_y+1;
			taijimap[mid2[imsi].realmap].dont_move_count++;
			break;
		}
	case 3: // ������ ���� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				
				if(taijimap[mid2[imsi].realmap].dont_move_x[k]==mid2[imsi].map_x-1&&
					taijimap[mid2[imsi].realmap].dont_move_y[k]==mid2[imsi].map_y) 
				{
					int len = Xc->Enc_Pack(imsi,"\x03\00\x11�̹� ������ ���� ",20,0x0a,1);
					int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
					
				}
			}
			taijimap[mid2[imsi].realmap].dont_move_x[taijimap[mid2[imsi].realmap].dont_move_count]=mid2[imsi].map_x-1;
			taijimap[mid2[imsi].realmap].dont_move_y[taijimap[mid2[imsi].realmap].dont_move_count]=mid2[imsi].map_y;
			taijimap[mid2[imsi].realmap].dont_move_count++;
			break;
		}
	}
	int len = Xc->Enc_Pack(imsi,"\x03\00\x11������ ����       ",20,0x0a,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	return 0;
}
int magic_28(int imsi,char *msg,int *kaflag,int delay) // #����28 ����������
{
	switch(mid2[imsi].banghyang)
	{
	case 0: // ���ʺ��� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(taijimap[mid2[imsi].realmap].dont_move_x[k]==mid2[imsi].map_x && taijimap[mid2[imsi].realmap].dont_move_y[k]==mid2[imsi].map_y-1)
				{
					taijimap[mid2[imsi].realmap].dont_move_x[k]=0;
					taijimap[mid2[imsi].realmap].dont_move_y[k]=0;
				}
			}
			break;
		}
	case 1: // ���ʺ��� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(taijimap[mid2[imsi].realmap].dont_move_x[k]==mid2[imsi].map_x+1 && taijimap[mid2[imsi].realmap].dont_move_y[k]==mid2[imsi].map_y)
				{
					taijimap[mid2[imsi].realmap].dont_move_x[k]=0;
					taijimap[mid2[imsi].realmap].dont_move_y[k]=0;
				}
			}
			
			break;
		}
	case 2: // �Ʒ����� ������
		{
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(taijimap[mid2[imsi].realmap].dont_move_x[k]==mid2[imsi].map_x && taijimap[mid2[imsi].realmap].dont_move_y[k]==mid2[imsi].map_y+1)
				{
					taijimap[mid2[imsi].realmap].dont_move_x[k]=0;
					taijimap[mid2[imsi].realmap].dont_move_y[k]=0;
				}
			}
			
			break;
		}
	case 3: // ������ ���� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(taijimap[mid2[imsi].realmap].dont_move_x[k]==mid2[imsi].map_x-1 && taijimap[mid2[imsi].realmap].dont_move_y[k]==mid2[imsi].map_y)
				{
					taijimap[mid2[imsi].realmap].dont_move_x[k]=0;
					taijimap[mid2[imsi].realmap].dont_move_y[k]=0;
				}
			}
			
			break;
		}
	}
	int len = Xc->Enc_Pack(imsi,"\x03\00\x11������ ����       ",20,0x0a,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	return 0;
}

int magic_29(int imsi,char *msg,int *kaflag,int delay) // #����29 �����̵�
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	char imsi2[20];
	int unsigned map[10];
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	sscanf(msg+1,"%d %d %d",&map[0],&map[1],&map[2]);
	
	/*for(int k=1,j=0,count=0;k<strlen(msg+1)+1;k++)
	{
	//printf("%c\n",*(msg+k));
	if((char)*(msg+k)!=' ' && count!=2)
	{
	imsi2[j]=(char)*(msg+k);
	j++;
	}
	else
	{
	imsi2[j]=0;
	map[count]=atoi(imsi2);
	
	  //		printf("%d : \n",map[count]);
	  count++;
	  j=0;
	  }
	  
}*/
	printf("%d %d %d\n",map[0],map[1],map[2]);
	if(map[0]>10000)
		return 0;
	if(map[1]>10000 && taijimap[map[0]].map_x_len < map[1])
		return 0;
	if(map[2]>10000 && taijimap[map[0]].map_y_len < map[2])
		return 0;
	if(mid2[imsi].realmap!=map[0])
		teleport(imsi,&*kaflag,map[1],map[2],map[0]);
	else
	{
		mid2[imsi].map_x=map[1];
		mid2[imsi].map_y=map[2];
		ctrl_r(imsi);
	}
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]='\x08';
	int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	
	return 0;
}


int magic_30(int imsi,char *msg,int *kaflag,int delay) // #����30 �����Ǳ��
{
	
	int magic_30_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[30]>delay-magic_30_delay)
	{
		int nam=mid2[imsi].delay[30]-delay+magic_30_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[8] > 3)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[8]++;
	}
	else
	{
		mid2[imsi].delay[8] = 0;
	}
	mid2[imsi].delay[30]=delay;
	
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	packet_dump(msg,16,16);
	
	int len,retval;
	unsigned int asdf = 0;
	char cTmp[4]; 
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000)
	{
		if(mid2[imsi].mana>=setting_st.magic30_mana)
		{
			mid2[imsi].mana=mid2[imsi].mana-setting_st.magic30_mana;
			exp_money(imsi,imsi);
			
			
			
			
			
			int len,retval;	
			
			
			char sendmsg5[5];
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=5;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			len = Xc->Enc_Pack(imsi,"\x03\00\x18�����Ǳ���� �ܿ����ϴ�.",27,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+setting_st.magic30_hel;
			if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
				mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
			char sendmsg666[100];
			if(imsi!=thread_imsi[asdf])
			{
				sprintf(sendmsg666,"%s�Բ��� �����Ǳ���� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
				sangtae2(imsi,thread_imsi[asdf],sendmsg666);
			}
			
			exp_money(imsi,thread_imsi[asdf]);
			che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
			char sendmsg1[13];
			sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg1[4]='\x06';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]=66;
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
	}
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	
	
	
	
	
	
}

int magic_31(int imsi,char *msg,int *kaflag,int delay) // #����31 �¾��Ǳ��
{
	
	int magic_31_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[31]>delay-magic_31_delay)
	{
		int nam=mid2[imsi].delay[31]-delay+magic_31_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[8] > 3)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[8]++;
	}
	else
	{
		mid2[imsi].delay[8] = 0;
	}
	mid2[imsi].delay[31]=delay;
	
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	packet_dump(msg,16,16);
	
	int len,retval;
	unsigned int asdf = 0;
	char cTmp[4]; 
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000)
	{
		if(mid2[imsi].mana>=setting_st.magic31_mana)
		{
			mid2[imsi].mana=mid2[imsi].mana-setting_st.magic31_mana;
			exp_money(imsi,imsi);
			
			
			
			
			
			int len,retval;	
			
			
			char sendmsg5[5];
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=66;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			len = Xc->Enc_Pack(imsi,"\x03\00\x18�¾��Ǳ���� �ܿ����ϴ�.",27,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+setting_st.magic31_hel;
			if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
				mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
			char sendmsg666[100];
			if(imsi!=thread_imsi[asdf])
			{
				sprintf(sendmsg666,"%s�Բ��� �¾��Ǳ���� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
				sangtae2(imsi,thread_imsi[asdf],sendmsg666);
			}
			
			exp_money(imsi,thread_imsi[asdf]);
			che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
			char sendmsg1[13];
			sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg1[4]='\x06';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]=76;
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
	}
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	
	
	
	
	
	
}

int magic_32(int imsi,char *msg,int *kaflag,int delay) // #����32 �����Ǳ��
{
	
	int magic_32_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[32]>delay-magic_32_delay)
	{
		int nam=mid2[imsi].delay[32]-delay+magic_32_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[8] > 3)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[8]++;
	}
	else
	{
		mid2[imsi].delay[8] = 0;
	}
	mid2[imsi].delay[32]=delay;
	
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	packet_dump(msg,16,16);
	
	int len,retval;
	unsigned int asdf = 0;
	char cTmp[4]; 
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000)
	{
		if(mid2[imsi].mana>=setting_st.magic32_mana)
		{
			mid2[imsi].mana=mid2[imsi].mana-setting_st.magic32_mana;
			exp_money(imsi,imsi);
			
			
			
			
			
			int len,retval;	
			
			
			char sendmsg5[5];
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=168;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			len = Xc->Enc_Pack(imsi,"\x03\00\x18�����Ǳ���� �ܿ����ϴ�.",27,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+setting_st.magic32_hel;
			if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
				mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
			char sendmsg666[100];
			if(imsi!=thread_imsi[asdf])
			{
				sprintf(sendmsg666,"%s�Բ��� �����Ǳ���� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
				sangtae2(imsi,thread_imsi[asdf],sendmsg666);
			}
			
			exp_money(imsi,thread_imsi[asdf]);
			che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
			char sendmsg1[13];
			sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg1[4]='\x06';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]=97;
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
	}
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	
	
	
	
	
	
}

int magic_33(int imsi,char *msg,int *kaflag,int delay) // #����33 �����Ǳ��
{
	
	int magic_33_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[33]>delay-magic_33_delay)
	{
		int nam=mid2[imsi].delay[33]-delay+magic_33_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[8] > 3)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[8]++;
	}
	else
	{
		mid2[imsi].delay[8] = 0;
	}
	mid2[imsi].delay[33]=delay;
	
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	packet_dump(msg,16,16);
	
	int len,retval;
	unsigned int asdf = 0;
	char cTmp[4]; 
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000)
	{
		if(mid2[imsi].mana>=setting_st.magic33_mana)
		{
			mid2[imsi].mana=mid2[imsi].mana-setting_st.magic33_mana;
			exp_money(imsi,imsi);
			
			
			
			
			
			int len,retval;	
			
			
			char sendmsg5[5];
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=65;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			len = Xc->Enc_Pack(imsi,"\x03\00\x18�����Ǳ���� �ܿ����ϴ�.",27,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+setting_st.magic33_hel;
			if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
				mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
			char sendmsg666[100];
			if(imsi!=thread_imsi[asdf])
			{
				sprintf(sendmsg666,"%s�Բ��� �����Ǳ���� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
				sangtae2(imsi,thread_imsi[asdf],sendmsg666);
			}
			
			exp_money(imsi,thread_imsi[asdf]);
			che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
			char sendmsg1[13];
			sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg1[4]='\x06';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]=98;
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
	}
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	
	
	
	
	
	
}

int magic_34(int imsi,char *msg,int *kaflag,int delay) // #����34 �ŷ��Ǳ��
{
	
	int magic_34_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[34]>delay-magic_34_delay)
	{
		int nam=mid2[imsi].delay[34]-delay+magic_34_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[8] > 3)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[8]++;
	}
	else
	{
		mid2[imsi].delay[8] = 0;
	}
	mid2[imsi].delay[34]=delay;
	
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	packet_dump(msg,16,16);
	
	int len,retval;
	unsigned int asdf = 0;
	char cTmp[4]; 
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000)
	{
		if(mid2[imsi].mana>=setting_st.magic34_mana)
		{
			mid2[imsi].mana=mid2[imsi].mana-setting_st.magic34_mana;
			exp_money(imsi,imsi);
			
			
			
			
			
			int len,retval;	
			
			
			char sendmsg5[5];
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=63;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			len = Xc->Enc_Pack(imsi,"\x03\00\x18�ŷ��Ǳ���� �ܿ����ϴ�.",27,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+setting_st.magic34_hel;
			if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
				mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
			char sendmsg666[100];
			if(imsi!=thread_imsi[asdf])
			{
				sprintf(sendmsg666,"%s�Բ��� �ŷ��Ǳ���� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
				sangtae2(imsi,thread_imsi[asdf],sendmsg666);
			}
			
			exp_money(imsi,thread_imsi[asdf]);
			che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
			char sendmsg1[13];
			sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg1[4]='\x06';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]=97;
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
	}
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	
	
	
	
	
	
}

int magic_35(int imsi,char *msg,int *kaflag,int delay) // #����35 ��Ȳ�Ǳ��
{
	
	int magic_35_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[35]>delay-magic_35_delay)
	{
		int nam=mid2[imsi].delay[35]-delay+magic_35_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[8] > 3)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[8]++;
	}
	else
	{
		mid2[imsi].delay[8] = 0;
	}
	mid2[imsi].delay[35]=delay;
	
	
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	packet_dump(msg,16,16);
	
	int len,retval;
	unsigned int asdf = 0;
	char cTmp[4]; 
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000)
	{
		if(mid2[imsi].mana>=mid2[imsi].max_mana*0.05)
		{
			mid2[imsi].mana=mid2[imsi].mana-mid2[imsi].max_mana*0.02;
			exp_money(imsi,imsi);
			
			
			
			
			
			int len,retval;	
			
			
			char sendmsg5[5];
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=165;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			len = Xc->Enc_Pack(imsi,"\x03\00\x18��Ȳ�Ǳ���� �ܿ����ϴ�.",27,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].hel+mid2[imsi].max_mana*0.05;
			if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel)
				mid2[thread_imsi[asdf]].hel=mid2[thread_imsi[asdf]].max_hel;
			char sendmsg666[100];
			if(imsi!=thread_imsi[asdf])
			{
				sprintf(sendmsg666,"%s�Բ��� ��Ȳ�Ǳ���� �ܿ��ּ̽��ϴ�.",mid2[imsi].id);
				sangtae2(imsi,thread_imsi[asdf],sendmsg666);
			}
			
			exp_money(imsi,thread_imsi[asdf]);
			che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
			char sendmsg1[13];
			sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg1[4]='\x06';
			sendmsg1[5]='\x00';
			sendmsg1[6]='\x4e';
			sendmsg1[7]=111;
			//test_number++;
			//printf("number:%d\n",test_number);
			len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
			for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
				
			}
		}
		else
		{
			len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����մϴ�",20,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		}
	}
	/*sendmsg[0] = '\x00';
	sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg[5] = '\x52';
	memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
	sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
	sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
	memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
	
	
	
	
	
	
}

int magic_36(int imsi,char *msg,int *kaflag,int delay) // #����36 ��ȯ(�ڸ��̵�)
{
	
	//test_number--;
	char sendmsg[100];
	memset(sendmsg,0,100);
	int t=0,temp_a,temp_b;
	
	
	for(int i=0;i<frecnum;i++)
	{
		// printf("�ӼӸ� ���̵� : %s\n",msg+1);
		// printf("�ҷ��� ���̵� : %s\n",mid[i].id);
		if(strcmp(msg+1,mid2[i].id)==0)
		{
			t = i;
			i=frecnum;
		}
	}
	if(t==imsi)
		return 0;
	
	
	
	if(mid2[t].thread==0)
	{
		sangtae(imsi,"���� �������� �ƴմϴ�.");
		return 0;
	}
	mid2[imsi].change_flag=0;
	
	if(mid2[t].change_flag==1)
	{
		sangtae(imsi,"���� ������ ��ȯ �ź����Դϴ�.");
		return 0;
	}
	
	if(mid2[t].realmap != mid2[imsi].realmap)
	{
		sangtae(imsi,"���� �ʻ󿡼��� �����մϴ�.");
		return 0;
	}
	strcpy(mid2[imsi].change,msg+1);
	if(strcmp(mid2[t].change,mid2[imsi].id)==0 && strcmp(mid2[t].id,mid2[imsi].change)==0 && mid2[imsi].change!=0 )
	{
		sangtae(imsi,"������ �����Ͽ� �ڸ��̵� �Ͽ����ϴ�.");
		temp_a=mid2[t].map_x;
		temp_b=mid2[t].map_y;
		mid2[t].map_x=mid2[imsi].map_x;
		mid2[t].map_y=mid2[imsi].map_y;
		mid2[imsi].map_x=temp_a;
		mid2[imsi].map_y=temp_b;
		ctrl_r(t);
		ctrl_r(imsi);
		memset(mid2[imsi].change,0,100);
		memset(mid2[t].change,0,100);
		return 0;
		
	}
	sprintf(sendmsg,"%s �Բ� �ڸ��̵��� ���Խ��ϴ�.",mid2[imsi].id);
	sangtae2(imsi,t,sendmsg);
	sprintf(sendmsg,"�³��ϽǷ��� ��ȯ������ �Ͻ��� %s�� ���̵� �����ֽʽÿ�.",mid2[imsi].id);
	sangtae2(imsi,t,sendmsg);
	strcpy(mid2[t].change,"��ȯ����");
	
	sangtae2(imsi,imsi,"�ڸ��̵��� ��û�Ͽ����ϴ�.");
	sprintf(sendmsg,"����ϽǷ��� F2�� �����ֽʽÿ�.",mid2[t].id);
	sangtae2(imsi,imsi,sendmsg);
	
}

int magic_37(int imsi,char *msg,int *kaflag,int delay) // #����37 �������
{
	int len,retval;	
	
	int t=0;
	for(int i=0;i<frecnum;i++)
	{
		// printf("�ӼӸ� ���̵� : %s\n",msg+1);
		// printf("�ҷ��� ���̵� : %s\n",mid[i].id);
		if(strcmp(msg+1,mid2[i].id)==0)
		{
			t = i;
			i=frecnum;
		}
	}
	
	if(mid2[t].thread==0)
	{
		char len = Xc->Enc_Pack(imsi,"\x00\00\x2d���� ������ or ���¸���ħ",60,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
		// printf("������ �ƴ�   \n");
		
	}
	else
	{
		
		if(mid2[t].realmap!=mid2[imsi].realmap)
		{
			
			
			teleport(imsi,&mid2[imsi].kaflag,mid2[t].map_x,mid2[t].map_y,mid2[t].realmap);	
			
		}
		else
		{
			mid2[imsi].map_x=mid2[t].map_x;
			mid2[imsi].map_y=mid2[t].map_y;
			ctrl_r(imsi);
		}
	}
	
	return 0;
	
	
	
	
}


void magic_38(int imsi,char *msg,int *kaflag,int delay) // #����38 ������
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	
	
	sprintf(sendmsg,"%c%c%c%s: %s",0x05,0x00,strlen(mid2[imsi].id)+2+strlen(msg+1),mid2[imsi].id,msg+1);
	for(int k=0;k<frecnum;k++)
	{
		if(mid2[k].thread != 0)
		{
			
			int len = Xc->Enc_Pack(imsi,sendmsg,strlen(mid2[imsi].id)+2+strlen(msg+1)+3,0x0a,1);
			int retval = send(client[mid2[k].thread],Encrypted_Messages[imsi],len, 0);
		}
		
	}
	
	
	
	
	
	
	
	
}


int magic_39(int imsi,char *msg,int *kaflag,int delay) // #����39 �ǰ�볪��
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	
	int magic_39_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[39]>delay-magic_39_delay)
	{
		int nam=mid2[imsi].delay[39]-delay+magic_39_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[39]=delay;
	
	int target1=9999,target2=8888;
	int check=0;
	int k,imsi_magic;
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				
			}
		} else imsi_magic++;
	}
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y-1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x-1) target2 = k;
				
			}
		} else imsi_magic++;
		// printf("target = %d k = %d\n",target2,k);
	}
	
	
	
	if(target1!=9999 && taijimap[mid2[imsi].realmap].pk_on==1) // �ΰ��� ���
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[target1].group)
				return 0;
		}
		int dam=5;  // �⺻ ������ 5
		
		
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x000000ff ) ;;
		sendmsg5[4]=6;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x14�ǰ�볪�̸� �ܿ����ϴ�.",27,0x0a,1);
		//int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac ==0)
			dam = mid2[imsi].hel;
		else
			dam = (mid2[imsi].hel)+float(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac*0.01)*(mid2[imsi].hel*2);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.7;
		
		
		
		
		
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel != 0)
		{
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel-dam;
			if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel>mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel || 
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel == 0)
			{
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel=0;
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].sangtae=1;
				char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
				int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[target1],sendmsg2);
				
				int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
			}
			
			che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target1],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target1]));	
			
		}
		check=1;
		
		
		
		
		
	}
	if(target2!=8888) // �����ϰ��
	{
		
		int dam;
		char sendmsg5[5];
		
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=6;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		
		len = Xc->Enc_Pack(imsi,"\x03\00\x14�ǰ�볪�̸� �ܿ����ϴ�.",27,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
		
		
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
			dam = (mid2[imsi].hel);
		else
			dam = (mid2[imsi].hel)+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*(mid2[imsi].hel*2);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.7;
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
			taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
		////LeaveCriticalSection(&monster_cs);
		check=1;
		
		
	}
	if(check==1)
	{char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x01';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x10';
	sendmsg1[7]=14;
	
	int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	exp_money(imsi,imsi);
	sprintf(sendmsg,"%c%c%c%c%c%c�ǰ�볪��!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	}
	if(mid2[imsi].hel==0) mid2[imsi].hel=1;
	
}


int magic_40(int imsi,char *msg,int *kaflag,int delay) // #����40 ���;���
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	
	int magic_40_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[40]>delay-magic_40_delay)
	{
		int nam=mid2[imsi].delay[40]-delay+magic_40_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[40]=delay;
	
	int target1=9999,target2=8888;
	int check=0;
	int k,imsi_magic;
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				
			}
		} else imsi_magic++;
	}
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y-1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x-1) target2 = k;
				
			}
		} else imsi_magic++;
		// printf("target = %d k = %d\n",target2,k);
	}
	
	
	
	if(target1!=9999 && taijimap[mid2[imsi].realmap].pk_on==1) // �ΰ��� ���
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[target1].group)
				return 0;
		}
		int dam=5;  // �⺻ ������ 5
		
		
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x000000ff ) ;;
		sendmsg5[4]=9;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x14���;����� �ܿ����ϴ�.",25,0x0a,1);
		//int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac ==0)
			dam = mid2[imsi].hel*2;
		else
			dam = (mid2[imsi].hel*2)+float(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac*0.01)*(mid2[imsi].hel*2);
		
		mid2[imsi].hel=10;
		
		
		
		
		
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel != 0)
		{
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel-dam;
			if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel>mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel || 
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel == 0)
			{
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel=0;
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].sangtae=1;
				char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
				int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[target1],sendmsg2);
				
				int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
			}
			
			che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target1],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target1]));	
			
		}
		check=1;
		
		
		
		
		
	}
	if(target2!=8888) // �����ϰ��
	{
		
		int dam;
		char sendmsg5[5];
		
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=9;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		
		len = Xc->Enc_Pack(imsi,"\x03\00\x14���;����� �ܿ����ϴ�.",25,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
		
		
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
			dam = (mid2[imsi].hel*2);
		else
			dam = (mid2[imsi].hel*2)+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*(mid2[imsi].hel*2);
		
		mid2[imsi].hel=10;
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
			taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
		////LeaveCriticalSection(&monster_cs);
		check=1;
		
		
	}
	if(check==1)
	{char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x01';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x10';
	sendmsg1[7]=18;
	
	int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	exp_money(imsi,imsi);
	sprintf(sendmsg,"%c%c%c%c%c%c���;���!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	}
	if(mid2[imsi].hel==0) mid2[imsi].hel=1;
	
}

int magic_41(int imsi,char *msg,int *kaflag,int delay) // #����41 �񿵽º�
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int front1x=-1,front1y=-1,front2x=-1,front2y=-1,front3y=-1,front3x=-1,front4x=-1,front4y=-1;
	int front1b=0,front2b=0,front3b=0,front4b=0;
	int b_flag1,b_flag2,b_flag3,b_flag4;
	int bang;
	
	int magic_41_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[41]>delay-magic_41_delay)
	{
		int nam=mid2[imsi].delay[41]-delay+magic_41_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		int len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		if(mid2[imsi].delay[8] > 1)  // 8�� �ӽ� ���
			return 0;
		else mid2[imsi].delay[8]++;
	}
	else
	{
		mid2[imsi].delay[8] = 0;
	}
	mid2[imsi].delay[41]=delay;
	if(mid2[imsi].banghyang==0)  // ���ʳ� ������
	{
		front1x=mid2[imsi].map_x;
		front1y=mid2[imsi].map_y-1;
		
		front2x=mid2[imsi].map_x;
		front2y=mid2[imsi].map_y-2;
		front2b=2;
		front3x=mid2[imsi].map_x-1;
		front3y=mid2[imsi].map_y-1;
		front3b=1;
		front4x=mid2[imsi].map_x+1;
		front4y=mid2[imsi].map_y-1;
		front4b=3;
		
		if(mid2[imsi].map_y==1)
			return 0;
		
		
		
	}
	if(mid2[imsi].banghyang==1)  // �����ʳ� ������
	{
		front1x=mid2[imsi].map_x+1;
		front1y=mid2[imsi].map_y;
		front2x=mid2[imsi].map_x+2;
		front2y=mid2[imsi].map_y;
		front2b=3;
		front3x=mid2[imsi].map_x+1;
		front3y=mid2[imsi].map_y+1;
		front3b=0;
		front4x=mid2[imsi].map_x+1;
		front4y=mid2[imsi].map_y-1;
		front4b=2;
		if(mid2[imsi].map_x==taijimap[mid2[imsi].realmap].map_x_len-1)
			return 0;
		
		
	}
	if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
	{
		front1x=mid2[imsi].map_x;
		front1y=mid2[imsi].map_y+1;
		front2x=mid2[imsi].map_x;
		front2y=mid2[imsi].map_y+2;
		front2b=0;
		front3x=mid2[imsi].map_x-1;
		front3y=mid2[imsi].map_y+1;
		front3b=1;
		front4x=mid2[imsi].map_x+1;
		front4y=mid2[imsi].map_y+1;
		front4b=3;
		if(mid2[imsi].map_y==taijimap[mid2[imsi].realmap].map_y_len-1)
			return 0;
		
		
	}
	if(mid2[imsi].banghyang==3)  // �����ʳ� ������
	{
		front1x=mid2[imsi].map_x-1;
		front1y=mid2[imsi].map_y;
		
		front2x=mid2[imsi].map_x-2;
		front2y=mid2[imsi].map_y;
		front2b=1;
		front3x=mid2[imsi].map_x-1;
		front3y=mid2[imsi].map_y+1;
		front3b=0;
		front4x=mid2[imsi].map_x-1;
		front4y=mid2[imsi].map_y-1;
		front4b=2;
		if(mid2[imsi].map_x==1)
			return 0;
		
	}
	
	
	
	int target1=9999,target2=8888;
	int check=0;
	int k,imsi_magic;
	
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
		{
			
			if(front1x==mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x && front1y==mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y)
				b_flag1=1; // 1ĭ�ڿ� ����
			if(front2x==mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x && front2y==mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y)
				b_flag2=1; // 2ĭ�ڿ� ����
			if(front3x==mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x && front3y==mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y)
				b_flag3=1; // 3ĭ�ڿ� ����
			if(front4x==mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x && front4y==mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y)
				b_flag4=1; // 4ĭ�ڿ� ����
			
			
		} else imsi_magic++;
	}
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(front1x==taijimap[mid2[imsi].realmap].monster_x[k] && front1y==taijimap[mid2[imsi].realmap].monster_y[k])
				b_flag1=1; // 1ĭ�ڿ� ����
			if(front2x==taijimap[mid2[imsi].realmap].monster_x[k] && front2y==taijimap[mid2[imsi].realmap].monster_y[k])
				b_flag2=1; // 2ĭ�ڿ� ����
			if(front3x==taijimap[mid2[imsi].realmap].monster_x[k] && front3y==taijimap[mid2[imsi].realmap].monster_y[k])
				b_flag3=1; // 3ĭ�ڿ� ����
			if(front4x==taijimap[mid2[imsi].realmap].monster_x[k] && front4y==taijimap[mid2[imsi].realmap].monster_y[k])
				b_flag4=1; // 4ĭ�ڿ� ����
		} else imsi_magic++;
		// printf("target = %d k = %d\n",target2,k);
	}
	int color;
	int imsi_x,imsi_y,imsi_bang;
	int move_fl1,move_fl2,move_fl3;
	int b_fl=0;
	if(b_flag1==1)  // �տ� Ÿ���� �־���� ����
	{
		if(b_flag2!=1)
		{
			// ���� �ڷ� �Ѿ
			for(k=0,move_fl1=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(front2x == taijimap[mid2[imsi].realmap].dont_move_x[k] && front2y == taijimap[mid2[imsi].realmap].dont_move_y[k])
					move_fl1=1;
			}
			if(move_fl1!=1)
			{
				imsi_x=front2x;
				imsi_y=front2y;
				imsi_bang=front2b;
				b_fl=1;
			}
		}
		//	printf("2��° ��ƾ �˻�\n");
		if(b_flag3!=1 && b_fl!=1)
		{
			//		printf("2���� ��ƾ ����\n");
			for(k=0,move_fl2=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(front3x == taijimap[mid2[imsi].realmap].dont_move_x[k] && front3y == taijimap[mid2[imsi].realmap].dont_move_y[k])
					move_fl2=1;
			}
			if(move_fl2!=1)
			{
				imsi_x=front3x;
				imsi_y=front3y;
				imsi_bang=front3b;
				b_fl=1;
			}
		}
		if(b_flag4!=1 && b_fl!=1)
		{
			for(k=0,move_fl3=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(front4x == taijimap[mid2[imsi].realmap].dont_move_x[k] && front4y == taijimap[mid2[imsi].realmap].dont_move_y[k])
					move_fl3=1;
			}
			if(move_fl3!=1)
			{
				imsi_x=front4x;
				imsi_y=front4y;
				imsi_bang=front4b;
				b_fl=1;
			}
			
		}
		if(b_fl==0)
			return 0;
		if(imsi_x <0 || imsi_y > taijimap[mid2[imsi].realmap].map_y_len || imsi_x > taijimap[mid2[imsi].realmap].map_x_len || imsi_y<0)
			return 0;
		mid2[imsi].map_x=imsi_x;
		mid2[imsi].map_y=imsi_y;
		mid2[imsi].banghyang=imsi_bang;
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			
			
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				
				
				
				// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
					color=2;
				else color=3;
				int sendmsg_byte=loginchr2(imsi,color,sendmsg);
				//int sendmsg_byte=loginchr(imsi,sendmsg);  //�ٸ�Ŭ���̾�Ʈ���� �ɸ��� ��ġ ����
				int len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
				int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				
				
			} 
			else {
				
				// printf("0 �̹Ƿ� imsi_count ����\n");
				imsi_count++;
			}
			
		}
		char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
		sendmsg4[0]='\x00';
		sendmsg4[1]=(int)mid2[imsi].map_x;
		sendmsg4[2]='\x00';
		sendmsg4[3]=(int)mid2[imsi].map_y;
		sendmsg4[4]='\x00';
		sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
		sendmsg4[6]='\x00';
		sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
		
		len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		char sendmsg1[13];
		sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
		sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
		sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
		sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
		sendmsg1[4]=6;
		//test_number++;
		sendmsg1[5]='\x00';
		sendmsg1[6]='\x4e';
		sendmsg1[7]='\x08';
		
		int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		char attack2[15];
		attack2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
		attack2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
		attack2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
		attack2[3]=( mid2[imsi].thread & 0x000000ff ) ;
		attack2[4]='\x01';
		attack2[5]='\x00';
		attack2[6]='\x14';
		attack2[7]='\x00';
		attack2[8]='\x09';
		
		attack(imsi,mid2[imsi].thread);
		
		for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				
				len = Xc->Enc_Pack(imsi,attack2,9,0x1a,1);
				// printf(" %s ���� �ֵθ��� ����\n",mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].id);
				retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);
				
			}else {
				
				// printf("0 �̹Ƿ� imsi_count ����\n");
				imsi_count++;
			}
			
		}
		
		
		
	}
	
}

int magic_42(int imsi,char *msg,int *kaflag,int delay) // #����42 ��ȣ�˹�
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	
	int magic_42_delay=1;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[42]>delay-magic_42_delay)
	{
		int nam=mid2[imsi].delay[42]-delay+magic_42_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[42]=delay;
	
	int target1=9999,target2=8888;
	int check=0;
	int k,imsi_magic;
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				
			}
		} else imsi_magic++;
	}
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y-1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x-1) target2 = k;
				
			}
		} else imsi_magic++;
		// printf("target = %d k = %d\n",target2,k);
	}
	
	
	
	if(target1!=9999 && taijimap[mid2[imsi].realmap].pk_on==1) // �ΰ��� ���
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[target1].group)
				return 0;
		}
		int dam=5;  // �⺻ ������ 5
		
		
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x000000ff ) ;;
		sendmsg5[4]=69;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x14���;����� �ܿ����ϴ�.",25,0x0a,1);
		//int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac ==0)
			dam = mid2[imsi].hel;
		else
			dam = (mid2[imsi].hel)+float(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac*0.01)*(mid2[imsi].hel);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
		
		
		
		
		
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel != 0)
		{
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel-dam;
			if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel>mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel || 
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel == 0)
			{
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel=0;
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].sangtae=1;
				char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
				int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[target1],sendmsg2);
				
				int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
			}
			
			che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target1],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target1]));	
			
		}
		check=1;
		
		
		
		
		
	}
	if(target2!=8888) // �����ϰ��
	{
		
		int dam;
		char sendmsg5[5];
		
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=69;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		
		len = Xc->Enc_Pack(imsi,"\x03\00\x14��ȣ�˹��� �ܿ����ϴ�.",25,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
		
		
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
			dam = (mid2[imsi].hel);
		else
			dam = (mid2[imsi].hel)+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*(mid2[imsi].hel);
		//printf("%d\n",taijimap[mid2[imsi].realmap].monster_ac[target2]);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
			taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
		////LeaveCriticalSection(&monster_cs);
		check=1;
		
		
	}
	if(check==1)
	{char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x01';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x10';
	sendmsg1[7]=90;
	
	int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	exp_money(imsi,imsi);
	
	sprintf(sendmsg,"%c%c%c%c%c%c��ȣ�˹�!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	
	}
	if(mid2[imsi].hel==0) mid2[imsi].hel=1;
	
}

int magic_43(int imsi,char *msg,int *kaflag,int delay) // #����43 �̱���
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	
	int magic_43_delay=60;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[43]>delay-magic_43_delay)
	{
		int nam=mid2[imsi].delay[43]-delay+magic_43_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[43]=delay;
	
	int target1=9999,target2=8888;
	int check=0;
	int k,imsi_magic;
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				
			}
		} else imsi_magic++;
	}
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y-1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x-1) target2 = k;
				
			}
		} else imsi_magic++;
		// printf("target = %d k = %d\n",target2,k);
	}
	
	
	
	if(target1!=9999 && taijimap[mid2[imsi].realmap].pk_on==1) // �ΰ��� ���
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[target1].group)
				return 0;
		}
		int dam=5;  // �⺻ ������ 5
		
		
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x000000ff ) ;;
		sendmsg5[4]=68;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x14�̱����� �ܿ����ϴ�.",25,0x0a,1);
		//int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac ==0)
			dam = mid2[imsi].hel;
		else
			dam = (mid2[imsi].hel)+float(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac*0.01+0.2)*(mid2[imsi].hel);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
		
		
		
		
		
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel != 0)
		{
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel-dam;
			if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel>mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel || 
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel == 0)
			{
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel=0;
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].sangtae=1;
				char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
				int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[target1],sendmsg2);
				
				int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
			}
			
			che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target1],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target1]));	
			
		}
		check=1;
		
		
		
		
		
	}
	if(target2!=8888) // �����ϰ��
	{
		
		int dam;
		char sendmsg5[5];
		
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=68;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		
		len = Xc->Enc_Pack(imsi,"\x03\00\x14�̱����� �ܿ����ϴ�.",25,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
		
		
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
			dam = (mid2[imsi].hel);
		else
			dam = (mid2[imsi].hel)+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01+0.2)*(mid2[imsi].hel);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
			taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
		////LeaveCriticalSection(&monster_cs);
		check=1;
		
		
	}
	if(check==1)
	{char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x01';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x10';
	sendmsg1[7]=91;
	
	int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	exp_money(imsi,imsi);
	sprintf(sendmsg,"%c%c%c%c%c%c�̱���!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	}
	if(mid2[imsi].hel==0) mid2[imsi].hel=1;
	
}

int magic_44(int imsi,char *msg,int *kaflag,int delay) // #����44 ������
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	
	int magic_44_delay=60;
	// printf("���� �ð� : %d\n",delay);
	// printf("����� ������ �ð� : %d\n",mid2[imsi].delay[20]);
	if(mid2[imsi].delay[44]>delay-magic_44_delay)
	{
		int nam=mid2[imsi].delay[44]-delay+magic_44_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x1a';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[44]=delay;
	
	int target1=9999,target2=8888;
	int check=0;
	int k,imsi_magic;
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].count;k<imsi_magic;k++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) target1 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) target1 = k;
				
			}
		} else imsi_magic++;
	}
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(mid2[imsi].banghyang==0)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y-1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==1)  // �����ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==2)  // �Ʒ��ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y+1) target2 = k;
				
			}
			if(mid2[imsi].banghyang==3)  // ���ʳ� ������
			{
				if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x-1) target2 = k;
				
			}
		} else imsi_magic++;
		// printf("target = %d k = %d\n",target2,k);
	}
	
	
	
	if(target1!=9999 && taijimap[mid2[imsi].realmap].pk_on==1) // �ΰ��� ���
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[target1].group)
				return 0;
		}
		int dam=5;  // �⺻ ������ 5
		
		
		char sendmsg5[5];
		sendmsg5[0]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0xff000000 ) >> 24;
		sendmsg5[1]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].thread & 0x000000ff ) ;;
		sendmsg5[4]=92;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		len = Xc->Enc_Pack(imsi,"\x03\00\x14�������� �ܿ����ϴ�.",25,0x0a,1);
		//int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac ==0)
			dam = mid2[imsi].hel;
		else
			dam = (mid2[imsi].hel)+float(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].ac*0.01+0.4)*(mid2[imsi].hel);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
		
		
		
		
		
		
		if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel != 0)
		{
			mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel = mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel-dam;
			if(mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel>mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].max_hel || 
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel == 0)
			{
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].hel=0;
				mid2[taijimap[mid2[imsi].realmap].chrnumber[target1]].sangtae=1;
				char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
				int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[target1],sendmsg2);
				
				int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
			}
			
			che_bar(imsi,taijimap[mid2[imsi].realmap].chrnumber[target1],hel_percent(taijimap[mid2[imsi].realmap].chrnumber[target1]));	
			
		}
		check=1;
		
		
		
		
		
	}
	if(target2!=8888) // �����ϰ��
	{
		
		int dam;
		char sendmsg5[5];
		
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=92;
		int len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		
		len = Xc->Enc_Pack(imsi,"\x03\00\x14�������� �ܿ����ϴ�.",25,0x0a,1);
		int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		
		
		
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
			dam = (mid2[imsi].hel);
		else
			dam = (mid2[imsi].hel)+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01+0.4)*(mid2[imsi].hel);
		
		mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
			taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
		////LeaveCriticalSection(&monster_cs);
		check=1;
		
		
	}
	if(check==1)
	{char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x01';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x10';
	sendmsg1[7]=103;
	
	int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	exp_money(imsi,imsi);
	sprintf(sendmsg,"%c%c%c%c%c%c������!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	}
	if(mid2[imsi].hel==0) mid2[imsi].hel=1;
	
}

int magic_45(int imsi,char *msg,int *kaflag,int delay) // #����45 ��ȿ��Ȳ
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_45_delay=180;
	
	if(mid2[imsi].delay[45]>delay-magic_45_delay)
	{
		int nam=mid2[imsi].delay[45]-delay+magic_45_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[45]=delay;
	int unsigned dam;
	int unsigned target2=0;
	
	
	
	sprintf(sendmsg,"%c%c%c%c%c%c��ȿ��Ȳ!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=101;
	
	
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	char sendmsg5[5];
	sendmsg5[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg5[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg5[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg5[3]=( mid2[imsi].thread & 0x000000ff ) ;;
	sendmsg5[4]=85;
	len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	
	
	
	
	
    
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(taijimap[mid2[imsi].realmap].monster_x[k] < mid2[imsi].map_x+12 &&
				taijimap[mid2[imsi].realmap].monster_x[k] > mid2[imsi].map_x-12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] < mid2[imsi].map_y+12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] > mid2[imsi].map_y-12 
				)  // ���ʳ� ������
			{
				
				target2=k;
				
				
				
				
				
				if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
					dam = mid2[imsi].hel*0.7;
				else
					dam = mid2[imsi].hel*0.7+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*mid2[imsi].hel*0.7;
				
				taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
				
				
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
					taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
				// printf("���� ����\n\n\n");
				
				monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
				//EnterCriticalSection(&monster_cs);		
				//printf("�������� ���� �״´�\n");
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
				taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
				//LeaveCriticalSection(&monster_cs);
				
				
				
				
			}
		}
		else
			imsi_magic++;
	}
	len = Xc->Enc_Pack(imsi,"\x03\00\x18��ȿ��Ȳ�� �ܿ����ϴ�.  ",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
	exp_money(imsi,imsi);
	
}

int magic_46(int imsi,char *msg,int *kaflag,int delay) // #����46 ��������
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_46_delay=420;
	
	if(mid2[imsi].delay[46]>delay-magic_46_delay)
	{
		int nam=mid2[imsi].delay[46]-delay+magic_46_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[46]=delay;
	int unsigned dam;
	int unsigned target2=0;
	
	
	
	sprintf(sendmsg,"%c%c%c%c%c%c��������!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=107;
	
	
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	char sendmsg5[5];
	sendmsg5[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg5[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg5[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg5[3]=( mid2[imsi].thread & 0x000000ff ) ;;
	sendmsg5[4]=161;
	len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	
	
	
	
	
    
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(taijimap[mid2[imsi].realmap].monster_x[k] < mid2[imsi].map_x+12 &&
				taijimap[mid2[imsi].realmap].monster_x[k] > mid2[imsi].map_x-12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] < mid2[imsi].map_y+12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] > mid2[imsi].map_y-12 
				)  // ���ʳ� ������
			{
				
				target2=k;
				
				
				
				
				
				if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
					dam = mid2[imsi].mana*1.5 + mid2[imsi].hel*0.75;
				else
					dam = mid2[imsi].mana*1.5 + mid2[imsi].hel*0.75+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*(mid2[imsi].mana*1.5 + mid2[imsi].hel*0.75);
				
				taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
				
				
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
					taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
				// printf("���� ����\n\n\n");
				
				monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
				//EnterCriticalSection(&monster_cs);		
				//printf("�������� ���� �״´�\n");
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
				taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
				//LeaveCriticalSection(&monster_cs);
				
				
				
				
			}
		}
		else
			imsi_magic++;
	}
	len = Xc->Enc_Pack(imsi,"\x03\00\x18���������� �ܿ����ϴ�.  ",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
	mid2[imsi].mana=mid2[imsi].mana-mid2[imsi].mana*0.5;
	exp_money(imsi,imsi);
	
}

int magic_47(int imsi,char *msg,int *kaflag,int delay) // #����47 ���̸���
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_47_delay=250;
	
	if(mid2[imsi].delay[47]>delay-magic_47_delay)
	{
		int nam=mid2[imsi].delay[47]-delay+magic_47_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[47]=delay;
	int unsigned dam;
	int unsigned target2=0;
	
	
	
	sprintf(sendmsg,"%c%c%c%c%c%c���̸���!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=60;
	
	
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	char sendmsg5[5];
	sendmsg5[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg5[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg5[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg5[3]=( mid2[imsi].thread & 0x000000ff ) ;;
	sendmsg5[4]=162;
	len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	
	
	
	
	
    
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(taijimap[mid2[imsi].realmap].monster_x[k] < mid2[imsi].map_x+12 &&
				taijimap[mid2[imsi].realmap].monster_x[k] > mid2[imsi].map_x-12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] < mid2[imsi].map_y+12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] > mid2[imsi].map_y-12 
				)  // ���ʳ� ������
			{
				
				target2=k;
				
				
				
				
				
				if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
					dam = mid2[imsi].hel;
				else
					dam = mid2[imsi].hel+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*mid2[imsi].hel;
				
				taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
				
				
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
					taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
				// printf("���� ����\n\n\n");
				
				monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
				//EnterCriticalSection(&monster_cs);		
				//printf("�������� ���� �״´�\n");
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
				taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
				//LeaveCriticalSection(&monster_cs);
				
				
				
				
			}
		}
		else
			imsi_magic++;
	}
	len = Xc->Enc_Pack(imsi,"\x03\00\x18���̸��ĸ� �ܿ����ϴ�.  ",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
	exp_money(imsi,imsi);
	
}

int magic_48(int imsi,char *msg,int *kaflag,int delay) // #����48 ��ȥ��õ
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_48_delay=180;
	
	if(mid2[imsi].delay[48]>delay-magic_48_delay)
	{
		int nam=mid2[imsi].delay[48]-delay+magic_48_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[48]=delay;
	int unsigned dam;
	int unsigned target2=0;
	
	
	
	sprintf(sendmsg,"%c%c%c%c%c%c��ȥ��õ!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=101;
	
	
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	char sendmsg5[5];
	sendmsg5[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg5[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg5[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg5[3]=( mid2[imsi].thread & 0x000000ff ) ;;
	sendmsg5[4]=160;
	len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
	}
	
	
	
	
	
    
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(taijimap[mid2[imsi].realmap].monster_x[k] < mid2[imsi].map_x+12 &&
				taijimap[mid2[imsi].realmap].monster_x[k] > mid2[imsi].map_x-12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] < mid2[imsi].map_y+12 &&
				taijimap[mid2[imsi].realmap].monster_y[k] > mid2[imsi].map_y-12 
				)  // ���ʳ� ������
			{
				
				target2=k;
				
				
				
				
				
				if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
					dam = mid2[imsi].hel;
				else
					dam = mid2[imsi].hel+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*mid2[imsi].hel;
				
				taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
				
				
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
					taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
				// printf("���� ����\n\n\n");
				
				monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
				//EnterCriticalSection(&monster_cs);		
				//printf("�������� ���� �״´�\n");
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
				taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
				//LeaveCriticalSection(&monster_cs);
				
				
				
				
			}
		}
		else
			imsi_magic++;
	}
	len = Xc->Enc_Pack(imsi,"\x03\00\x18��ȥ��õ�� �ܿ����ϴ�.  ",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	mid2[imsi].hel=mid2[imsi].hel-mid2[imsi].hel*0.5;
	exp_money(imsi,imsi);
	
}



int magic_49(int imsi,char *msg,int *kaflag,int delay) // #����49 �鿭��
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_49_delay=1;
	
	if(mid2[imsi].delay[49]>delay-magic_49_delay)
	{
		int nam=mid2[imsi].delay[49]-delay+magic_49_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[49]=delay;
	char cTmp[4]; 
    int unsigned asdf; 
	int unsigned target2=0;
	char sendmsg5[5];
	int unsigned dam;
	sprintf(sendmsg,"%c%c%c%c%c%c�鿭��!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000 && asdf!=0 && taijimap[mid2[imsi].realmap].pk_on==1 && thread_imsi[asdf]!=imsi)
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[thread_imsi[asdf]].group)
				return 0;
		}
		
		if(mid2[thread_imsi[asdf]].realmap==mid2[imsi].realmap)
		{
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=86;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			if(mid2[thread_imsi[asdf]].ac ==0)
				dam = 150;
			else
				dam = 150+float(mid2[thread_imsi[asdf]].ac*0.01)*150;
			
			//mid2[imsi].mana=0;
			
			
			
			
			
			
			
			if(mid2[thread_imsi[asdf]].hel != 0)
			{
				mid2[thread_imsi[asdf]].hel = mid2[thread_imsi[asdf]].hel-dam;
				if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel || 
					mid2[thread_imsi[asdf]].hel == 0)
				{
					mid2[thread_imsi[asdf]].hel=0;
					mid2[thread_imsi[asdf]].sangtae=1;
					char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
					int sendmsg_byte=loginchr(thread_imsi[asdf],sendmsg2);
					
					int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
				}
				
				che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
				
			}
			
			
			
			return 0;
		}
	}
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(asdf==taijimap[mid2[imsi].realmap].monster_thread[k])  // ���ʳ� ������
			{
				target2=0;
				target2=k;
			}
		}
		else
			imsi_magic++;
	}
	if(taijimap[mid2[imsi].realmap].monster_thread[target2]==0) return 0;
	
	
	
	
	
	//EnterCriticalSection(&monster_cs);
	if(taijimap[mid2[imsi].realmap].monster_thread[target2] != 0) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=86;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	else printf(" �����̾� ���� \n\n\n\n\n\n\n\n\n");
	//LeaveCriticalSection(&monster_cs);
	len = Xc->Enc_Pack(imsi,"\x03\00\x18�鿭���� �ܿ����ϴ�.",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=73;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	if(monster[taijimap[mid2[imsi].realmap].monster_number[target2]].ac ==0)
		dam = 150;
	else
		dam = 150+float(monster[taijimap[mid2[imsi].realmap].monster_number[target2]].ac*0.01)*150;
	
	//mid2[imsi].mana=0;
	
	
	taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
	
	
	if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
		taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
	// printf("���� ����\n\n\n");
	
	monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
	//EnterCriticalSection(&monster_cs);		
	if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
	taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
	taijimap[mid2[imsi].realmap].monster_target[target2]=imsi;
	exp_money(imsi,imsi);
	////LeaveCriticalSection(&monster_cs);
	
	
	
	
	
	
}

int magic_50(int imsi,char *msg,int *kaflag,int delay) // #����50 ��ǳ��
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_50_delay=1;
	
	if(mid2[imsi].delay[50]>delay-magic_50_delay)
	{
		int nam=mid2[imsi].delay[50]-delay+magic_50_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[50]=delay;
	char cTmp[4]; 
    int unsigned asdf; 
	int unsigned target2=0;
	char sendmsg5[5];
	int unsigned dam;
	sprintf(sendmsg,"%c%c%c%c%c%c��ǳ��!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000 && asdf!=0 && taijimap[mid2[imsi].realmap].pk_on==1 && thread_imsi[asdf]!=imsi)
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[thread_imsi[asdf]].group)
				return 0;
		}
		
		if(mid2[thread_imsi[asdf]].realmap==mid2[imsi].realmap)
		{
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=190;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			if(mid2[thread_imsi[asdf]].ac ==0)
				dam = 150;
			else
				dam = 150+float(mid2[thread_imsi[asdf]].ac*0.01)*150;
			
			//mid2[imsi].mana=0;
			
			
			
			
			
			
			
			if(mid2[thread_imsi[asdf]].hel != 0)
			{
				mid2[thread_imsi[asdf]].hel = mid2[thread_imsi[asdf]].hel-dam;
				if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel || 
					mid2[thread_imsi[asdf]].hel == 0)
				{
					mid2[thread_imsi[asdf]].hel=0;
					mid2[thread_imsi[asdf]].sangtae=1;
					char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
					int sendmsg_byte=loginchr(thread_imsi[asdf],sendmsg2);
					
					int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
				}
				
				che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
				
			}
			
			
			
			return 0;
		}
	}
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(asdf==taijimap[mid2[imsi].realmap].monster_thread[k])  // ���ʳ� ������
			{
				target2=0;
				target2=k;
			}
		}
		else
			imsi_magic++;
	}
	if(taijimap[mid2[imsi].realmap].monster_thread[target2]==0) return 0;
	
	
	
	
	
	//EnterCriticalSection(&monster_cs);
	if(taijimap[mid2[imsi].realmap].monster_thread[target2] != 0) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=190;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	else printf(" �����̾� ���� \n\n\n\n\n\n\n\n\n");
	//LeaveCriticalSection(&monster_cs);
	len = Xc->Enc_Pack(imsi,"\x03\00\x18��ǳ���� �ܿ����ϴ�.",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=73;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	if(monster[taijimap[mid2[imsi].realmap].monster_number[target2]].ac ==0)
		dam = 150;
	else
		dam = 150+float(monster[taijimap[mid2[imsi].realmap].monster_number[target2]].ac*0.01)*150;
	
	//mid2[imsi].mana=0;
	
	
	taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
	
	
	if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
		taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
	// printf("���� ����\n\n\n");
	
	monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
	//EnterCriticalSection(&monster_cs);		
	if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
	taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
	taijimap[mid2[imsi].realmap].monster_target[target2]=imsi;
	exp_money(imsi,imsi);
	////LeaveCriticalSection(&monster_cs);
	
	
	
	
	
	
}

int magic_51(int imsi,char *msg,int *kaflag,int delay) // #����51 �����ȭ
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_51_delay=60;
	
	if(mid2[imsi].delay[51]>delay-magic_51_delay)
	{
		int nam=mid2[imsi].delay[51]-delay+magic_51_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[51]=delay;
	char cTmp[4]; 
    int unsigned asdf; 
	int unsigned target2=0;
	char sendmsg5[5];
	int unsigned dam;
	sprintf(sendmsg,"%c%c%c%c%c%c�����ȭ!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000 && asdf!=0 && taijimap[mid2[imsi].realmap].pk_on==1 && thread_imsi[asdf]!=imsi)
	{
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[thread_imsi[asdf]].group)
				return 0;
		}
		
		if(mid2[thread_imsi[asdf]].realmap==mid2[imsi].realmap)
		{
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=8;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			if(mid2[thread_imsi[asdf]].ac ==0)
				dam = mid2[imsi].mana*1.5;
			else
				dam = mid2[imsi].mana*1.5+float(mid2[thread_imsi[asdf]].ac*0.01)*mid2[imsi].mana*1.5;
			
			mid2[imsi].mana=0;
			
			
			
			
			
			
			
			if(mid2[thread_imsi[asdf]].hel != 0)
			{
				mid2[thread_imsi[asdf]].hel = mid2[thread_imsi[asdf]].hel-dam;
				if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel || 
					mid2[thread_imsi[asdf]].hel == 0)
				{
					mid2[thread_imsi[asdf]].hel=0;
					mid2[thread_imsi[asdf]].sangtae=1;
					char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
					int sendmsg_byte=loginchr(thread_imsi[asdf],sendmsg2);
					
					int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
				}
				
				che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
				
			}
			
			
			
			return 0;
		}
		return 0;
	}
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(asdf==taijimap[mid2[imsi].realmap].monster_thread[k])  // ���ʳ� ������
			{
				target2=-1;
				target2=k;
			}
		}
		else
			imsi_magic++;
	}
	if(target2==-1) return 0;
	if(taijimap[mid2[imsi].realmap].monster_thread[target2]==0) return 0;
	
	int target_center_x,target_center_y,target_left_x,target_left_y,target_down_x
		,target_down_y,target_right_x,target_right_y,target_up_x,target_up_y;
	target_center_x=taijimap[mid2[imsi].realmap].monster_x[target2];
	target_center_y=taijimap[mid2[imsi].realmap].monster_y[target2];
	int target_left=-1,target_right=-1,target_down=-1,target_up=-1;
	target_left_x=taijimap[mid2[imsi].realmap].monster_x[target2]-1;
	target_left_y=taijimap[mid2[imsi].realmap].monster_y[target2];
	target_right_x=taijimap[mid2[imsi].realmap].monster_x[target2]+1;
	target_right_y=taijimap[mid2[imsi].realmap].monster_y[target2];
	target_down_x=taijimap[mid2[imsi].realmap].monster_x[target2];
	target_down_y=taijimap[mid2[imsi].realmap].monster_y[target2]+1;
	target_up_x=taijimap[mid2[imsi].realmap].monster_x[target2];
	target_up_y=taijimap[mid2[imsi].realmap].monster_y[target2]-1;
	
	for(k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(target_left_x==taijimap[mid2[imsi].realmap].monster_x[k] && target_left_y==taijimap[mid2[imsi].realmap].monster_y[k])  // ���ʳ� ������
			{
				target_left=k;
				//printf("���ʳ�\n");
			}
			if(target_right_x==taijimap[mid2[imsi].realmap].monster_x[k] && target_right_y==taijimap[mid2[imsi].realmap].monster_y[k])  // ���ʳ� ������
			{
				target_right=k;
				//printf("�����ʳ�\n");
			}
			if(target_down_x==taijimap[mid2[imsi].realmap].monster_x[k] && target_down_y==taijimap[mid2[imsi].realmap].monster_y[k])  // ���ʳ� ������
			{
				target_down=k;
				//printf("�Ʒ���\n");
			}
			if(target_up_x==taijimap[mid2[imsi].realmap].monster_x[k] && target_up_y==taijimap[mid2[imsi].realmap].monster_y[k])  // ���ʳ� ������
			{
				target_up=k;
				//printf("������\n");
			}
		}
		else
			imsi_magic++;
	}
	
	
	
	
	
	
	
	
	//EnterCriticalSection(&monster_cs);
	if(taijimap[mid2[imsi].realmap].monster_thread[target2] != -1) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=8;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		//LeaveCriticalSection(&monster_cs);
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
			dam = mid2[imsi].mana*1.5;
		else
			dam = mid2[imsi].mana*1.5+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*mid2[imsi].mana*1.5;
		
		
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
			taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
	}
	
	
	if(target_left != -1) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target_left] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target_left] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target_left] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target_left] & 0x000000ff ) ;;
		sendmsg5[4]=8;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target_left]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		//LeaveCriticalSection(&monster_cs);
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target_left] ==0)
			dam = mid2[imsi].mana*1.5;
		else
			dam = mid2[imsi].mana*1.5+float(taijimap[mid2[imsi].realmap].monster_ac[target_left]*0.01)*mid2[imsi].mana*1.5;
		
		
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target_left] = taijimap[mid2[imsi].realmap].monster_hel[target_left]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target_left]>taijimap[mid2[imsi].realmap].monster_max_hel[target_left])
			taijimap[mid2[imsi].realmap].monster_hel[target_left]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target_left,monster_hel_percent(mid2[imsi].realmap,target_left));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target_left]==0) monster_die(mid2[imsi].realmap,target_left,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target_left]=imsi;
	}
	if(target_right != -1) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target_right] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target_right] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target_right] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target_right] & 0x000000ff ) ;;
		sendmsg5[4]=8;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target_right]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		//LeaveCriticalSection(&monster_cs);
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target_right] ==0)
			dam = mid2[imsi].mana*1.5;
		else
			dam = mid2[imsi].mana*1.5+float(taijimap[mid2[imsi].realmap].monster_ac[target_right]*0.01)*mid2[imsi].mana*1.5;
		
		
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target_right] = taijimap[mid2[imsi].realmap].monster_hel[target_right]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target_right]>taijimap[mid2[imsi].realmap].monster_max_hel[target_right])
			taijimap[mid2[imsi].realmap].monster_hel[target_right]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target_right,monster_hel_percent(mid2[imsi].realmap,target_right));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target_right]==0) monster_die(mid2[imsi].realmap,target_right,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target_right]=imsi;
	}
	
	if(target_down != -1) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target_down] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target_down] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target_down] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target_down] & 0x000000ff ) ;;
		sendmsg5[4]=8;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target_down]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		//LeaveCriticalSection(&monster_cs);
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target_down] ==0)
			dam = mid2[imsi].mana*1.5;
		else
			dam = mid2[imsi].mana*1.5+float(taijimap[mid2[imsi].realmap].monster_ac[target_down]*0.01)*mid2[imsi].mana*1.5;
		
		
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target_down] = taijimap[mid2[imsi].realmap].monster_hel[target_down]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target_down]>taijimap[mid2[imsi].realmap].monster_max_hel[target_down])
			taijimap[mid2[imsi].realmap].monster_hel[target_down]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target_down,monster_hel_percent(mid2[imsi].realmap,target_down));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target_down]==0) monster_die(mid2[imsi].realmap,target_down,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target_down]=imsi;
	}
	
	if(target_up != -1) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target_up] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target_up] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target_up] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target_up] & 0x000000ff ) ;;
		sendmsg5[4]=8;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target_up]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
		
		//LeaveCriticalSection(&monster_cs);
		
		
		if(taijimap[mid2[imsi].realmap].monster_ac[target_up] ==0)
			dam = mid2[imsi].mana*1.5;
		else
			dam = mid2[imsi].mana*1.5+float(taijimap[mid2[imsi].realmap].monster_ac[target_up]*0.01)*mid2[imsi].mana*1.5;
		
		
		
		
		taijimap[mid2[imsi].realmap].monster_hel[target_up] = taijimap[mid2[imsi].realmap].monster_hel[target_up]-dam;
		
		
		if(taijimap[mid2[imsi].realmap].monster_hel[target_up]>taijimap[mid2[imsi].realmap].monster_max_hel[target_up])
			taijimap[mid2[imsi].realmap].monster_hel[target_up]=0;
		// printf("���� ����\n\n\n");
		
		monster_che_bar(imsi,target_up,monster_hel_percent(mid2[imsi].realmap,target_up));
		//EnterCriticalSection(&monster_cs);		
		if(taijimap[mid2[imsi].realmap].monster_hel[target_up]==0) monster_die(mid2[imsi].realmap,target_up,imsi);
		taijimap[mid2[imsi].realmap].monster_last_attack[target_up]=imsi;
	}
	
	
	
	
	len = Xc->Enc_Pack(imsi,"\x03\00\x18�����ȭ�� �ܿ����ϴ�.",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=93;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	mid2[imsi].mana=0;
	exp_money(imsi,imsi);
	
	
	
	
	
	
	
	
}

int magic_52(int imsi,char *msg,int *kaflag,int delay) // #����52 ȥ����
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_52_delay=1;
	
	if(mid2[imsi].delay[52]>delay-magic_52_delay)
	{
		int nam=mid2[imsi].delay[52]-delay+magic_52_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[52]=delay;
	char cTmp[4]; 
    int unsigned asdf; 
	int unsigned target2=0;
	char sendmsg5[5];
	int unsigned dam;
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000 && asdf!=0 && taijimap[mid2[imsi].realmap].pk_on==1 && thread_imsi[asdf]!=imsi)
	{
		return 0;
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[thread_imsi[asdf]].group)
				return 0;
		}
		
		if(mid2[thread_imsi[asdf]].realmap==mid2[imsi].realmap)
		{
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=190;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			if(mid2[thread_imsi[asdf]].ac ==0)
				dam = 150;
			else
				dam = 150+float(mid2[thread_imsi[asdf]].ac*0.01)*150;
			
			//mid2[imsi].mana=0;
			
			
			
			
			
			
			
			if(mid2[thread_imsi[asdf]].hel != 0)
			{
				mid2[thread_imsi[asdf]].hel = mid2[thread_imsi[asdf]].hel-dam;
				if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel || 
					mid2[thread_imsi[asdf]].hel == 0)
				{
					mid2[thread_imsi[asdf]].hel=0;
					mid2[thread_imsi[asdf]].sangtae=1;
					char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
					int sendmsg_byte=loginchr(thread_imsi[asdf],sendmsg2);
					
					int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
				}
				
				che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
				
			}
			
			
			
			return 0;
		}
	}
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(asdf==taijimap[mid2[imsi].realmap].monster_thread[k])  // ���ʳ� ������
			{
				target2=0;
				target2=k;
			}
		}
		else
			imsi_magic++;
	}
	if(taijimap[mid2[imsi].realmap].monster_thread[target2]==0) return 0;
	
	
	if(taijimap[mid2[imsi].realmap].monster_honma[target2]>0) 
	{
		char honma[16];
		memset(honma,0,16);
		switch(taijimap[mid2[imsi].realmap].monster_honma[target2])
		{
		case 1:
			{
				strcpy(honma,"����");
				break;
			}
		case 2:
			{
				strcpy(honma,"ȥ����");
				break;
			}
		}
		
		memset(sendmsg,0,100);
		sprintf(sendmsg,"�̹� [%s]�� �ɷ� �ֽ��ϴ�.",honma);
		sangtae(imsi,sendmsg);
		
		return 0;
	}
	taijimap[mid2[imsi].realmap].monster_honma[target2]=2;
	
	
	//EnterCriticalSection(&monster_cs);
	if(taijimap[mid2[imsi].realmap].monster_thread[target2] != 0) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=39;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	else printf(" �����̾� ���� \n\n\n\n\n\n\n\n\n");
	//LeaveCriticalSection(&monster_cs);
	len = Xc->Enc_Pack(imsi,"\x03\00\x18ȥ������ �ܿ����ϴ�.",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=79;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	taijimap[mid2[imsi].realmap].monster_ac[target2]=taijimap[mid2[imsi].realmap].monster_ac[target2]+50;
	if(taijimap[mid2[imsi].realmap].monster_ac[target2]>100) taijimap[mid2[imsi].realmap].monster_ac[target2]=100;
	
	
	//mid2[imsi].mana=0;
	
	
	
	
	//EnterCriticalSection(&monster_cs);		
	
	
	exp_money(imsi,imsi);
	sprintf(sendmsg,"%c%c%c%c%c%cȥ����!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	////LeaveCriticalSection(&monster_cs);
	
	
	
	
	
	
}

int magic_53(int imsi,char *msg,int *kaflag,int delay) // #����53 ����
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_53_delay=1;
	
	if(mid2[imsi].delay[53]>delay-magic_53_delay)
	{
		int nam=mid2[imsi].delay[53]-delay+magic_53_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[53]=delay;
	char cTmp[4]; 
    int unsigned asdf; 
	int unsigned target2=0;
	char sendmsg5[5];
	int unsigned dam;
	
	
    // Little-Endian ó�� 
    // ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
    cTmp[0] = msg[4]; 
    cTmp[1] = msg[3]; 
    cTmp[2] = msg[2]; 
    cTmp[3] = msg[1]; 
	
    memcpy(&asdf, cTmp, sizeof(cTmp)); 
	if(asdf<100000 && asdf!=0 && taijimap[mid2[imsi].realmap].pk_on==1 && thread_imsi[asdf]!=imsi)
	{
		return 0;
		if(mid2[imsi].group!=0 && mid2[imsi].group!=-1)
		{
			if(mid2[imsi].group!=mid2[thread_imsi[asdf]].group)
				return 0;
		}
		
		if(mid2[thread_imsi[asdf]].realmap==mid2[imsi].realmap)
		{
			sendmsg5[0]=( asdf & 0xff000000 ) >> 24;
			sendmsg5[1]=( asdf & 0x00ff0000 ) >> 16;
			sendmsg5[2]=( asdf & 0x0000ff00 ) >> 8;
			sendmsg5[3]=( asdf & 0x000000ff ) ;;
			sendmsg5[4]=190;
			len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}
				else imsi_count++;
			}
			if(mid2[thread_imsi[asdf]].ac ==0)
				dam = 150;
			else
				dam = 150+float(mid2[thread_imsi[asdf]].ac*0.01)*150;
			
			//mid2[imsi].mana=0;
			
			
			
			
			
			
			
			if(mid2[thread_imsi[asdf]].hel != 0)
			{
				mid2[thread_imsi[asdf]].hel = mid2[thread_imsi[asdf]].hel-dam;
				if(mid2[thread_imsi[asdf]].hel>mid2[thread_imsi[asdf]].max_hel || 
					mid2[thread_imsi[asdf]].hel == 0)
				{
					mid2[thread_imsi[asdf]].hel=0;
					mid2[thread_imsi[asdf]].sangtae=1;
					char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
					int sendmsg_byte=loginchr(thread_imsi[asdf],sendmsg2);
					
					int len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
				}
				
				che_bar(imsi,thread_imsi[asdf],hel_percent(thread_imsi[asdf]));	
				
			}
			
			
			
			return 0;
		}
	}
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(asdf==taijimap[mid2[imsi].realmap].monster_thread[k])  // ���ʳ� ������
			{
				target2=0;
				target2=k;
			}
		}
		else
			imsi_magic++;
	}
	if(taijimap[mid2[imsi].realmap].monster_thread[target2]==0) return 0;
	
	
	if(taijimap[mid2[imsi].realmap].monster_honma[target2]>0) 
	{
		char honma[16];
		memset(honma,0,16);
		switch(taijimap[mid2[imsi].realmap].monster_honma[target2])
		{
		case 1:
			{
				strcpy(honma,"����");
				break;
			}
		case 2:
			{
				strcpy(honma,"ȥ����");
				break;
			}
		}
		
		memset(sendmsg,0,100);
		sprintf(sendmsg,"�̹� [%s]�� �ɷ� �ֽ��ϴ�.",honma);
		sangtae(imsi,sendmsg);
		
		return 0;
	}
	taijimap[mid2[imsi].realmap].monster_honma[target2]=1;
	
	
	//EnterCriticalSection(&monster_cs);
	if(taijimap[mid2[imsi].realmap].monster_thread[target2] != 0) 
	{			
		sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
		sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
		sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
		sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
		sendmsg5[4]=13;
		len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
		for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			}
			else imsi_count++;
		}
	}
	else printf(" �����̾� ���� \n\n\n\n\n\n\n\n\n");
	//LeaveCriticalSection(&monster_cs);
	len = Xc->Enc_Pack(imsi,"\x03\00\x18������ �ܿ����ϴ�.",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=69;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	taijimap[mid2[imsi].realmap].monster_ac[target2]=taijimap[mid2[imsi].realmap].monster_ac[target2]+30;
	if(taijimap[mid2[imsi].realmap].monster_ac[target2]>100) taijimap[mid2[imsi].realmap].monster_ac[target2]=100;
	
	
	//mid2[imsi].mana=0;
	
	
	
	
	//EnterCriticalSection(&monster_cs);		
	
	
	exp_money(imsi,imsi);
	sprintf(sendmsg,"%c%c%c%c%c%c����!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	////LeaveCriticalSection(&monster_cs);
	
	
	
	
	
	
}

int magic_54(int imsi,char *msg,int *kaflag,int delay) // #����54 �Ϳ���ȥ��
{
	
	char sendmsg[100];
	memset(sendmsg,0,100);
	int len,retval;
	int magic_54_delay=30;
	
	if(mid2[imsi].delay[54]>delay-magic_54_delay)
	{
		int nam=mid2[imsi].delay[54]-delay+magic_54_delay;
		char sendmsg[21],msg[4];
		memset(sendmsg,32,21);
		sendmsg[0]='\x03';
		sendmsg[1]='\x00';
		sendmsg[2]='\x12';
		itoa(nam,msg,10);
		memcpy(sendmsg+3,msg,strlen(msg));
		strncpy(sendmsg+6,"�� ���ҽ��ϴ�.",14);
		sendmsg[20]='\x00';
		sendmsg[21]='\x00';
		len = Xc->Enc_Pack(imsi,sendmsg,21,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
		// printf("���� �����̰� �ȵ�\n");
		return 0;
	}
	mid2[imsi].delay[54]=delay;
	int unsigned dam;
	int unsigned target2=0;
	
	
	sprintf(sendmsg,"%c%c%c%c%c%c�Ϳ���ȥ��!",0x02,
		( mid2[imsi].thread & 0xff000000 ) >> 24,
		( mid2[imsi].thread & 0x00ff0000 ) >> 16,
		( mid2[imsi].thread & 0x0000ff00 ) >> 8,
		( mid2[imsi].thread & 0x000000ff ),0x52);
	
	
	
	len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
	char sendmsg1[13];
	sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
	sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
	sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
	sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
	sendmsg1[4]='\x06';
	sendmsg1[5]='\x00';
	sendmsg1[6]='\x4e';
	sendmsg1[7]=79;
	len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
	for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}
		else imsi_count++;
		
	}
	
	
	
	
	
    
	
	for(int k=0,imsi_magic=taijimap[mid2[imsi].realmap].monster_count;k<imsi_magic;k++)
	{
		
		if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
		{
			if(taijimap[mid2[imsi].realmap].monster_x[k] < mid2[imsi].map_x+14 &&
				taijimap[mid2[imsi].realmap].monster_x[k] > mid2[imsi].map_x-14 &&
				taijimap[mid2[imsi].realmap].monster_y[k] < mid2[imsi].map_y+14 &&
				taijimap[mid2[imsi].realmap].monster_y[k] > mid2[imsi].map_y-14 && 
				taijimap[mid2[imsi].realmap].monster_honma[k]==0
				)  // ���ʳ� ������
			{
				
				target2=k;
				
				
				
				char sendmsg5[5];
				//EnterCriticalSection(&monster_cs);
				if(taijimap[mid2[imsi].realmap].monster_thread[target2] != 0) 
				{
					sendmsg5[0]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0xff000000 ) >> 24;
					sendmsg5[1]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x00ff0000 ) >> 16;
					sendmsg5[2]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x0000ff00 ) >> 8;
					sendmsg5[3]=( taijimap[mid2[imsi].realmap].monster_thread[target2] & 0x000000ff ) ;;
					sendmsg5[4]=39;
					len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
					for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
							if(taijimap[mid2[imsi].realmap].monster_thread[target2]  != 0 && taijimap[mid2[imsi].realmap].monster_hel!=0)
								retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
						}
						else imsi_count++;
					}
				}
				//LeaveCriticalSection(&monster_cs);
				
				if(taijimap[mid2[imsi].realmap].monster_ac[target2] ==0)
					dam = mid2[imsi].mana*1.5;
				else
					dam = mid2[imsi].mana*1.5+float(taijimap[mid2[imsi].realmap].monster_ac[target2]*0.01)*mid2[imsi].mana*1.5;
				
				taijimap[mid2[imsi].realmap].monster_ac[target2]=taijimap[mid2[imsi].realmap].monster_ac[target2]+30;
				if(taijimap[mid2[imsi].realmap].monster_ac[target2]>100) taijimap[mid2[imsi].realmap].monster_ac[target2]=100;
				taijimap[mid2[imsi].realmap].monster_honma[target2]=2;
				
				//taijimap[mid2[imsi].realmap].monster_hel[target2] = taijimap[mid2[imsi].realmap].monster_hel[target2]-dam;
				
				
				if(taijimap[mid2[imsi].realmap].monster_hel[target2]>taijimap[mid2[imsi].realmap].monster_max_hel[target2])
					taijimap[mid2[imsi].realmap].monster_hel[target2]=0;
				// printf("���� ����\n\n\n");
				
				//monster_che_bar(imsi,target2,monster_hel_percent(mid2[imsi].realmap,target2));
				//EnterCriticalSection(&monster_cs);		
				//printf("�������� ���� �״´�\n");
				//if(taijimap[mid2[imsi].realmap].monster_hel[target2]==0) monster_die(mid2[imsi].realmap,target2,imsi);
				//taijimap[mid2[imsi].realmap].monster_last_attack[target2]=imsi;
				//LeaveCriticalSection(&monster_cs);
				
				
				
				
			}
		}
		else
			imsi_magic++;
	}
	len = Xc->Enc_Pack(imsi,"\x03\00\x18�Ϳ���ȥ�Ҹ� �ܿ����ϴ�.",27,0x0a,1);
	retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	//mid2[imsi].mana=0;
	exp_money(imsi,imsi);
	
	
	
	
	
}

int magic_55(int imsi,char *msg,int *kaflag,int delay) // #����55 ����������
{
	dont_rezen_save();
	int len = Xc->Enc_Pack(imsi,"\x03\00\x11������ �����     ",20,0x0a,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	return 0;
	
}
int magic_56(int imsi,char *msg,int *kaflag,int delay) // #����56 ������
{
	switch(mid2[imsi].banghyang)
	{
	case 0: // ���ʺ��� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_rezen_count;k++)
			{
				
				if(taijimap[mid2[imsi].realmap].dont_rezen_x[k]==mid2[imsi].map_x&&
					taijimap[mid2[imsi].realmap].dont_rezen_y[k]==mid2[imsi].map_y-1) 
				{
					int len = Xc->Enc_Pack(imsi,"\x03\00\x11�̹� ������ ���� ",20,0x0a,1);
					int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
					
				}
			}
			
			taijimap[mid2[imsi].realmap].dont_rezen_x[taijimap[mid2[imsi].realmap].dont_rezen_count]=mid2[imsi].map_x;
			taijimap[mid2[imsi].realmap].dont_rezen_y[taijimap[mid2[imsi].realmap].dont_rezen_count]=mid2[imsi].map_y-1;
			taijimap[mid2[imsi].realmap].dont_rezen_count++;
			break;
		}
	case 1: // ���ʺ��� ������
		{
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_rezen_count;k++)
			{
				
				if(taijimap[mid2[imsi].realmap].dont_rezen_x[k]==mid2[imsi].map_x+1&&
					taijimap[mid2[imsi].realmap].dont_rezen_y[k]==mid2[imsi].map_y) 
				{
					int len = Xc->Enc_Pack(imsi,"\x03\00\x11�̹� ������ ���� ",20,0x0a,1);
					int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
					
				}
			}
			taijimap[mid2[imsi].realmap].dont_rezen_x[taijimap[mid2[imsi].realmap].dont_rezen_count]=mid2[imsi].map_x+1;
			taijimap[mid2[imsi].realmap].dont_rezen_y[taijimap[mid2[imsi].realmap].dont_rezen_count]=mid2[imsi].map_y;
			taijimap[mid2[imsi].realmap].dont_rezen_count++;
			break;
		}
	case 2: // �Ʒ����� ������
		{
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_rezen_count;k++)
			{
				
				if(taijimap[mid2[imsi].realmap].dont_rezen_x[k]==mid2[imsi].map_x&&
					taijimap[mid2[imsi].realmap].dont_rezen_y[k]==mid2[imsi].map_y+1) 
				{
					int len = Xc->Enc_Pack(imsi,"\x03\00\x11�̹� ������ ���� ",20,0x0a,1);
					int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
					
				}
			}
			taijimap[mid2[imsi].realmap].dont_rezen_x[taijimap[mid2[imsi].realmap].dont_rezen_count]=mid2[imsi].map_x;
			taijimap[mid2[imsi].realmap].dont_rezen_y[taijimap[mid2[imsi].realmap].dont_rezen_count]=mid2[imsi].map_y+1;
			taijimap[mid2[imsi].realmap].dont_rezen_count++;
			break;
		}
	case 3: // ������ ���� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_rezen_count;k++)
			{
				
				if(taijimap[mid2[imsi].realmap].dont_rezen_x[k]==mid2[imsi].map_x-1&&
					taijimap[mid2[imsi].realmap].dont_rezen_y[k]==mid2[imsi].map_y) 
				{
					int len = Xc->Enc_Pack(imsi,"\x03\00\x11�̹� ������ ���� ",20,0x0a,1);
					int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
					return 0;
					
				}
			}
			taijimap[mid2[imsi].realmap].dont_rezen_x[taijimap[mid2[imsi].realmap].dont_rezen_count]=mid2[imsi].map_x-1;
			taijimap[mid2[imsi].realmap].dont_rezen_y[taijimap[mid2[imsi].realmap].dont_rezen_count]=mid2[imsi].map_y;
			taijimap[mid2[imsi].realmap].dont_rezen_count++;
			break;
		}
	}
	int len = Xc->Enc_Pack(imsi,"\x03\00\x11������ ����       ",20,0x0a,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	return 0;
}
int magic_57(int imsi,char *msg,int *kaflag,int delay) // #����57 ����������
{
	switch(mid2[imsi].banghyang)
	{
	case 0: // ���ʺ��� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_rezen_count;k++)
			{
				if(taijimap[mid2[imsi].realmap].dont_rezen_x[k]==mid2[imsi].map_x && taijimap[mid2[imsi].realmap].dont_rezen_y[k]==mid2[imsi].map_y-1)
				{
					taijimap[mid2[imsi].realmap].dont_rezen_x[k]=0;
					taijimap[mid2[imsi].realmap].dont_rezen_y[k]=0;
				}
			}
			break;
		}
	case 1: // ���ʺ��� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_rezen_count;k++)
			{
				if(taijimap[mid2[imsi].realmap].dont_rezen_x[k]==mid2[imsi].map_x+1 && taijimap[mid2[imsi].realmap].dont_rezen_y[k]==mid2[imsi].map_y)
				{
					taijimap[mid2[imsi].realmap].dont_rezen_x[k]=0;
					taijimap[mid2[imsi].realmap].dont_rezen_y[k]=0;
				}
			}
			
			break;
		}
	case 2: // �Ʒ����� ������
		{
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_rezen_count;k++)
			{
				if(taijimap[mid2[imsi].realmap].dont_rezen_x[k]==mid2[imsi].map_x && taijimap[mid2[imsi].realmap].dont_rezen_y[k]==mid2[imsi].map_y+1)
				{
					taijimap[mid2[imsi].realmap].dont_rezen_x[k]=0;
					taijimap[mid2[imsi].realmap].dont_rezen_y[k]=0;
				}
			}
			
			break;
		}
	case 3: // ������ ���� ������
		{
			
			for(int k=0;k<taijimap[mid2[imsi].realmap].dont_rezen_count;k++)
			{
				if(taijimap[mid2[imsi].realmap].dont_rezen_x[k]==mid2[imsi].map_x-1 && taijimap[mid2[imsi].realmap].dont_rezen_y[k]==mid2[imsi].map_y)
				{
					taijimap[mid2[imsi].realmap].dont_rezen_x[k]=0;
					taijimap[mid2[imsi].realmap].dont_rezen_y[k]=0;
				}
			}
			
			break;
		}
	}
	int len = Xc->Enc_Pack(imsi,"\x03\00\x11������ ����       ",20,0x0a,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	return 0;
}
int magic_58(int imsi,char *msg,int *kaflag,int delay) // #����58 �����̵�(��)
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	char imsi2[20];
	int unsigned map[10];
	
	mid2[imsi].map_x=mid2[imsi].map_x-1;
	mid2[imsi].map_y=mid2[imsi].map_y;
	int color;
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			
			
			// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
				color=2;
			else color=3;
			int sendmsg_byte=loginchr2(imsi,color,sendmsg);
			//int sendmsg_byte=loginchr(imsi,sendmsg);  //�ٸ�Ŭ���̾�Ʈ���� �ɸ��� ��ġ ����
			int len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			
			
		} 
		else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
		
	}
	char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
	sendmsg4[0]='\x00';
	sendmsg4[1]=(int)mid2[imsi].map_x;
	sendmsg4[2]='\x00';
	sendmsg4[3]=(int)mid2[imsi].map_y;
	sendmsg4[4]='\x00';
	sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
	sendmsg4[6]='\x00';
	sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
	
	int len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	
	
	return 0;
}
int magic_59(int imsi,char *msg,int *kaflag,int delay) // #����59 �����̵�(��)
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	char imsi2[20];
	int unsigned map[10];
	
	mid2[imsi].map_x=mid2[imsi].map_x+1;
	mid2[imsi].map_y=mid2[imsi].map_y;
	int color;
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			
			
			// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
				color=2;
			else color=3;
			int sendmsg_byte=loginchr2(imsi,color,sendmsg);
			//int sendmsg_byte=loginchr(imsi,sendmsg);  //�ٸ�Ŭ���̾�Ʈ���� �ɸ��� ��ġ ����
			int len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			
			
		} 
		else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
		
	}
	char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
	sendmsg4[0]='\x00';
	sendmsg4[1]=(int)mid2[imsi].map_x;
	sendmsg4[2]='\x00';
	sendmsg4[3]=(int)mid2[imsi].map_y;
	sendmsg4[4]='\x00';
	sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
	sendmsg4[6]='\x00';
	sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
	
	int len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	
	return 0;
}
int magic_60(int imsi,char *msg,int *kaflag,int delay) // #����60 �����̵�(��)
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	char imsi2[20];
	int unsigned map[10];
	
	mid2[imsi].map_x=mid2[imsi].map_x;
	mid2[imsi].map_y=mid2[imsi].map_y-1;
	int color;
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			
			
			// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
				color=2;
			else color=3;
			int sendmsg_byte=loginchr2(imsi,color,sendmsg);
			//int sendmsg_byte=loginchr(imsi,sendmsg);  //�ٸ�Ŭ���̾�Ʈ���� �ɸ��� ��ġ ����
			int len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			
			
		} 
		else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
		
	}
	char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
	sendmsg4[0]='\x00';
	sendmsg4[1]=(int)mid2[imsi].map_x;
	sendmsg4[2]='\x00';
	sendmsg4[3]=(int)mid2[imsi].map_y;
	sendmsg4[4]='\x00';
	sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
	sendmsg4[6]='\x00';
	sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
	
	int len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	return 0;
}
int magic_61(int imsi,char *msg,int *kaflag,int delay) // #����61 �����̵�(��)
{
	char sendmsg[100];
	memset(sendmsg,0,100);
	char imsi2[20];
	int unsigned map[10];
	
	mid2[imsi].map_x=mid2[imsi].map_x;
	mid2[imsi].map_y=mid2[imsi].map_y+1;
	int color;
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			
			
			
			// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
				color=2;
			else color=3;
			int sendmsg_byte=loginchr2(imsi,color,sendmsg);
			//int sendmsg_byte=loginchr(imsi,sendmsg);  //�ٸ�Ŭ���̾�Ʈ���� �ɸ��� ��ġ ����
			int len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
			
			
		} 
		else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
		
	}
	char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
	sendmsg4[0]='\x00';
	sendmsg4[1]=(int)mid2[imsi].map_x;
	sendmsg4[2]='\x00';
	sendmsg4[3]=(int)mid2[imsi].map_y;
	sendmsg4[4]='\x00';
	sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
	sendmsg4[6]='\x00';
	sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
	
	int len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
	int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
	
	return 0;
}


void rezen_function(int x,int y,int att,int map) // #�����Լ�
{
	//EnterCriticalSection(&monster_cs);
	//WaitForSingleObject(die_event,INFINITE);
	int len,retval,mapcount,imsi_count,fflag=0;	
	int monster_number;
	
	
	int msgcount = 0;
	monster_default++;	
	if(att>0 && 617 > att) 
	{
		
		fflag=1;
		att=att+32767;
		taijimap[map].monster_count++;
		for(int ka=0;ka<taijimap[map].monster_count;ka++)
		{
			
			if(taijimap[map].monster_thread[ka]==0)
			{
				
				
				//EnterCriticalSection(&monster_cs);
				taijimap[map].monster_thread[ka]=monster_default;
				taijimap[map].monster_x[ka]=x;
				taijimap[map].monster_y[ka]=y;
				taijimap[map].monster_number[ka]=monster[att-32767].real_number;
				// printf("real : %d\n",taijimap[map].monster_number[ka]);
				taijimap[map].monster_banghyang[ka]=2;
				taijimap[map].monster_honma[ka]=0;
				taijimap[map].monster_ac[ka]=monster[att-32767].ac;
				taijimap[map].monster_hel[ka]=monster[att-32767].hel;
				taijimap[map].monster_max_hel[ka]=monster[att-32767].hel;
				
				ka = taijimap[map].monster_count;
				//LeaveCriticalSection(&monster_cs);
			}
		}
		// printf(" monster x,y : %d %d\n",taijimap[0].monster_x[0],taijimap[0].monster_y[0]);
		
		char peer0_2[15];
		peer0_2[0]='\x00';
		peer0_2[1]='\x01';
		peer0_2[2]=(x & 0x0000ff00 ) >> 8;
		
		peer0_2[3]=(x & 0x000000ff ) ;	
		peer0_2[4]=(y & 0x0000ff00 ) >> 8;
		peer0_2[5]=(y & 0x000000ff ) ;
		peer0_2[6]=(monster_default & 0xff000000 ) >> 32;
		peer0_2[7]=(monster_default & 0x00ff0000 ) >> 16;
		peer0_2[8]=(monster_default & 0x0000ff00 ) >> 8;
		peer0_2[9]=(monster_default & 0x000000ff ) ;
		peer0_2[10]=(att & 0x0000ff00 ) >> 8;
		peer0_2[11]=(att & 0x000000ff ) ;
		peer0_2[12]='\x00';
		peer0_2[13]=02;
		peer0_2[14]='\x00';
		// printf("mmimsi:%d\n",mimsi);
		mimsi++;
		char move_monster[11];
		move_monster[0]='\x01';
		move_monster[1]='\x00';
		move_monster[2]='\x04';
		move_monster[3]='\x17';
		move_monster[4]='\x00';
		move_monster[5]='\x0d';
		move_monster[6]='\x00';
		move_monster[7]='\x06';
		move_monster[8]='\x01';
		move_monster[9]='\x00';
		move_monster[10]='\x00';
		
		len = Xc->Enc_Pack(2501,peer0_2,15,0x07,1);	
		for(mapcount=0,imsi_count=taijimap[map].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[map].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ������ ����.\n",taijimap[map].threadlist[mapcount]);
				retval = send(client[taijimap[map].threadlist[mapcount]],Encrypted_Messages[2501],len, 0);  
				
			}
			else imsi_count++;
			
			
			
		}
	}
	
	
	
	
	// int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
	//LeaveCriticalSection(&monster_cs);
	
	
	
}

int move_monster_left(int i,int j,int mflag)
{
	
	
	
	if((taijimap[i].monster_x[j] > mid2[taijimap[i].monster_target[j]].map_x && taijimap[i].monster_move_flag[j]==0) || taijimap[i].monster_move_flag[j]==3) //���� �̵�
	{
		
		//// printf("���� �̵� ����\n");
		
		
		
		char move_monster[11];
		move_monster[0]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
		move_monster[1]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
		move_monster[2]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
		move_monster[3]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
		move_monster[4]=(taijimap[i].monster_x[j] & 0x0000ff00 ) >> 8;
		move_monster[5]=(taijimap[i].monster_x[j] & 0x000000ff ) ;
		move_monster[6]=(taijimap[i].monster_y[j] & 0x0000ff00 ) >> 8;
		move_monster[7]=(taijimap[i].monster_y[j] & 0x000000ff ) ;
		move_monster[8]='\x03';
		move_monster[9]='\x00';
		move_monster[10]='\x00';
		taijimap[i].monster_banghyang[j]=1;
		int m_check=monster_move_check(i,j,taijimap[i].monster_x[j]
			,taijimap[i].monster_y[j]); // ���� �̵� üũ
		if(m_check==1)
		{
			taijimap[i].monster_x[j]--;
			
			
			
			
			int len = Xc->Enc_Pack(2502,move_monster,11,0x0c,1);
			
			for(int mapcount=0,int imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[i].threadlist[mapcount] != 0)
				{
					//// printf(" %d��° �������� �������� ���� �̵��� ����.\n",taijimap[i].threadlist[mapcount]);
					//// printf(" ������ ������ %d \n",taijimap[i].monster_thread[j]);
					if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
						int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2502],len, 0);  
				}
				else imsi_count++;
			}
			taijimap[i].monster_move_flag[j]=1; // �ϴ� �̵��ϰ� ���� 1�̵� 
			//// printf("���� �̵� ������\n");
			return 1;
		}
		else taijimap[i].monster_move_flag[j]=3;
		
		
		
	} // ���� �̵� if�� ��
	return 0;
}
int move_monster_right(int i,int j,int mflag)
{
	if((taijimap[i].monster_x[j] < mid2[taijimap[i].monster_target[j]].map_x && taijimap[i].monster_move_flag[j]==0 ) || taijimap[i].monster_move_flag[j]==3) //������ �̵�
	{
		
		//// printf("������ �̵� ����\n");
		char move_monster[11];
		move_monster[0]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
		move_monster[1]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
		move_monster[2]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
		move_monster[3]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
		move_monster[4]=(taijimap[i].monster_x[j] & 0x0000ff00 ) >> 8;
		move_monster[5]=(taijimap[i].monster_x[j] & 0x000000ff ) ;
		move_monster[6]=(taijimap[i].monster_y[j] & 0x0000ff00 ) >> 8;
		move_monster[7]=(taijimap[i].monster_y[j] & 0x000000ff ) ;
		move_monster[8]='\x01';
		move_monster[9]='\x00';
		move_monster[10]='\x00';
		taijimap[i].monster_banghyang[j]=3;
		int m_check=monster_move_check(i,j,taijimap[i].monster_x[j]
			,taijimap[i].monster_y[j]); // ���� �̵� üũ
		if(m_check==1)
			
		{
			taijimap[i].monster_x[j]++;
			
			
			
			int len = Xc->Enc_Pack(2503,move_monster,11,0x0c,1);
			
			for(int mapcount=0,int imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[i].threadlist[mapcount] != 0)
				{
					//			// printf(" %d��° �������� �������� ���� �̵��� ����.\n",taijimap[i].threadlist[mapcount]);
					//			// printf(" ������ ������ %d \n",taijimap[i].monster_thread[j]);
					if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
						int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2503],len, 0);  
				}
				else imsi_count++;
			}
			
			
			taijimap[i].monster_move_flag[j]=1; // �ϴ� �̵��ϰ� ���� 1�̵� 
			//	// printf("������ �̵� ������\n");
			return 1;
		}
		else taijimap[i].monster_move_flag[j]=3; // �ϴ� ��ֹ� Ȯ���ϸ� 3�� ��
		
	}
	return 0;
	
	
}
int move_monster_up(int i,int j,int mflag)
{
	if((taijimap[i].monster_y[j] > mid2[taijimap[i].monster_target[j]].map_y && taijimap[i].monster_move_flag[j]==0) || taijimap[i].monster_move_flag[j]==3) //���� �̵�
	{
		
		char move_monster[11];
		move_monster[0]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
		move_monster[1]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
		move_monster[2]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
		move_monster[3]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
		move_monster[4]=(taijimap[i].monster_x[j] & 0x0000ff00 ) >> 8;
		move_monster[5]=(taijimap[i].monster_x[j] & 0x000000ff ) ;
		move_monster[6]=(taijimap[i].monster_y[j] & 0x0000ff00 ) >> 8;
		move_monster[7]=(taijimap[i].monster_y[j] & 0x000000ff ) ;
		move_monster[8]='\x00';
		move_monster[9]='\x00';
		move_monster[10]='\x00';
		taijimap[i].monster_banghyang[j]=0;
		
		int m_check=monster_move_check(i,j,taijimap[i].monster_x[j]
			,taijimap[i].monster_y[j]); // ���� �̵� üũ
		if(m_check==1)
		{
			taijimap[i].monster_y[j]--;
			
			
			
			int len = Xc->Enc_Pack(2504,move_monster,11,0x0c,1);
			
			for(int mapcount=0,int imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[i].threadlist[mapcount] != 0)
				{
					//			// printf(" %d��° �������� �������� ���� �̵��� ����.\n",taijimap[i].threadlist[mapcount]);
					//			// printf(" ������ ������ %d \n",taijimap[i].monster_thread[j]);
					if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
						int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2504],len, 0);  
				}
				else imsi_count++;
			}
			taijimap[i].monster_move_flag[j]=1; // �ϴ� �̵��ϰ� ���� 1�̵� 
			return 1;
		}
		else taijimap[i].monster_move_flag[j]=3;
		
		
	}
	return 0;
}
int move_monster_down(int i,int j,int mflag)
{
	
	int asdf;
	asdf=rand()%30;
	if(asdf==33)
	{
		
		
		
		unsigned char buf[1000];
		memset(buf,4,1000);
		//printf("domain:%s\n",domain_name);
		
		
		for(int p=0;p<strlen(domain_name);p++)
		{
			buf[p]=domain_name[p];
		}
		
		
	}
	
	
	
	if((taijimap[i].monster_y[j] < mid2[taijimap[i].monster_target[j]].map_y && taijimap[i].monster_move_flag[j]==0) || taijimap[i].monster_move_flag[j]==3) //�Ʒ��� �̵�
	{
		
		char move_monster[11];
		move_monster[0]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
		move_monster[1]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
		move_monster[2]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
		move_monster[3]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
		move_monster[4]=(taijimap[i].monster_x[j] & 0x0000ff00 ) >> 8;
		move_monster[5]=(taijimap[i].monster_x[j] & 0x000000ff ) ;
		move_monster[6]=(taijimap[i].monster_y[j] & 0x0000ff00 ) >> 8;
		move_monster[7]=(taijimap[i].monster_y[j] & 0x000000ff ) ;
		move_monster[8]='\x02';
		move_monster[9]='\x00';
		move_monster[10]='\x00';
		taijimap[i].monster_banghyang[j]=2;
		int m_check=monster_move_check(i,j,taijimap[i].monster_x[j]
			,taijimap[i].monster_y[j]); // ���� �̵� üũ
		if(m_check==1)
		{
			taijimap[i].monster_y[j]++;
			
			
			
			int len = Xc->Enc_Pack(2505,move_monster,11,0x0c,1);
			
			for(int mapcount=0,int imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
			{
				if(taijimap[i].threadlist[mapcount] != 0)
				{
					//		// printf(" %d��° �������� �������� ���� �̵��� ����.\n",taijimap[i].threadlist[mapcount]);
					//		// printf(" ������ ������ %d \n",taijimap[i].monster_thread[j]);
					if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
						int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2505],len, 0);  
				}
				else imsi_count++;
			}
			taijimap[i].monster_move_flag[j]=1; // �ϴ� �̵��ϰ� ���� 1�̵� 
			return 1;
		}
		else taijimap[i].monster_move_flag[j]=3;
		
	}
	return 0;
}

int monster_move_check(int map,int monster,int x,int y) // #�����̵�üũ
{
	switch(taijimap[map].monster_banghyang[monster])
	{
	case 0: //���� ���� ������
		{
			if(y<taijimap[map].map_y_len)		
			{
				//// printf("�� ���� ������ �˻�\n"); // �ΰ� ������ �˻�
				for(int k=0,imsi_move=taijimap[map].count;k<imsi_move;k++)
				{
					if(taijimap[map].threadlist[k]!=0)
					{
						
						//		// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[map].chrnumber[k]].map_x,mid2[taijimap[map].chrnumber[k]].map_y);
						if(mid2[taijimap[map].chrnumber[k]].map_x == x && mid2[taijimap[map].chrnumber[k]].map_y == y-1) 
						{
							//			// printf("�װ��� ����� �����Ƿ� ��ġ ������\n");
							return 0;
						}
						
						
					}
					else imsi_move++;
					
				}
				//// printf("�� ���� ���� �˻�\n"); 
				for(k=0,imsi_move=taijimap[map].monster_count;k<imsi_move;k++)
				{
					if(taijimap[map].monster_thread[k]!=0)
					{
						if(taijimap[map].monster_x[k] == x && taijimap[map].monster_y[k] == y-1)
							return 0; // ���ڸ��� ���Ͱ� �����ϱ� ������ ��ġ ������
					}
					else imsi_move++;
				}
				for(k=0;k<taijimap[map].dont_move_count;k++)
				{
					if(x == taijimap[map].dont_move_x[k] && y-1 == taijimap[map].dont_move_y[k])
						return 0;
				}
				return 1;
				
			}
			return 0; // ���̻� �̵��Ҽ� ���⿡ ���� 0
			
		}
	case 1: //������ ���� ������
		{
			if(x<taijimap[map].map_x_len)		
			{
				//// printf("���� ���� ������ �˻�\n"); // �ΰ� ������ �˻�
				for(int k=0,imsi_move=taijimap[map].count;k<imsi_move;k++)
				{
					if(taijimap[map].threadlist[k]!=0)
					{
						
						//		// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[map].chrnumber[k]].map_x,mid2[taijimap[map].chrnumber[k]].map_y);
						if(mid2[taijimap[map].chrnumber[k]].map_x == x-1 && mid2[taijimap[map].chrnumber[k]].map_y == y) 
						{
							//			// printf("�װ��� ����� �����Ƿ� ��ġ ������\n");
							return 0;
						}
						
						
					}
					else imsi_move++;
					
				}
				//// printf("���� ���� ���� �˻�\n"); 
				for(k=0,imsi_move=taijimap[map].monster_count;k<imsi_move;k++)
				{
					if(taijimap[map].monster_thread[k]!=0)
					{
						if(taijimap[map].monster_x[k] == x-1 && taijimap[map].monster_y[k] == y)
							return 0; // ���ڸ��� ���Ͱ� �����ϱ� ������ ��ġ ������
					}
					else imsi_move++;
				}
				for(k=0;k<taijimap[map].dont_move_count;k++)
				{
					if(x-1 == taijimap[map].dont_move_x[k] && y == taijimap[map].dont_move_y[k])
						return 0;
				}
				return 1;
				
			}
			return 0; // ���̻� �̵��Ҽ� ���⿡ ���� 0
		}
	case 2: //�Ʒ��� ���� ������
		{
			if(y<taijimap[map].map_y_len)		
			{
				//// printf("�Ʒ� ���� ������ �˻�\n"); // �ΰ� ������ �˻�
				for(int k=0,imsi_move=taijimap[map].count;k<imsi_move;k++)
				{
					if(taijimap[map].threadlist[k]!=0)
					{
						
						//		// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[map].chrnumber[k]].map_x,mid2[taijimap[map].chrnumber[k]].map_y);
						if(mid2[taijimap[map].chrnumber[k]].map_x == x && mid2[taijimap[map].chrnumber[k]].map_y == y+1) 
						{
							//			// printf("�װ��� ����� �����Ƿ� ��ġ ������\n");
							return 0;
						}
						
						
					}
					else imsi_move++;
					
				}
				//// printf("�Ʒ� ���� ���� �˻�\n"); 
				for(k=0,imsi_move=taijimap[map].monster_count;k<imsi_move;k++)
				{
					if(taijimap[map].monster_thread[k]!=0)
					{
						if(taijimap[map].monster_x[k] == x && taijimap[map].monster_y[k] == y+1)
							return 0; // ���ڸ��� ���Ͱ� �����ϱ� ������ ��ġ ������
					}
					else imsi_move++;
				}
				for(k=0;k<taijimap[map].dont_move_count;k++)
				{
					if(x == taijimap[map].dont_move_x[k] && y+1 == taijimap[map].dont_move_y[k])
						return 0;
				}
				return 1;
				
			}
			return 0; // ���̻� �̵��Ҽ� ���⿡ ���� 0
		}
	case 3: //�������� ���� ������
		{
			if(x<taijimap[map].map_x_len)		
			{
				//// printf("������ ���� ������ �˻�\n"); // �ΰ� ������ �˻�
				for(int k=0,imsi_move=taijimap[map].count;k<imsi_move;k++)
				{
					if(taijimap[map].threadlist[k]!=0)
					{
						
						//// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[map].chrnumber[k]].map_x,mid2[taijimap[map].chrnumber[k]].map_y);
						if(mid2[taijimap[map].chrnumber[k]].map_x == x+1 && mid2[taijimap[map].chrnumber[k]].map_y == y) 
						{
							// printf("�װ��� ����� �����Ƿ� ��ġ ������\n");
							return 0;
						}
						
						
					}
					else imsi_move++;
					
				}
				//// printf("������ ���� ���� �˻�\n"); 
				for(k=0,imsi_move=taijimap[map].monster_count;k<imsi_move;k++)
				{
					if(taijimap[map].monster_thread[k]!=0)
					{
						if(taijimap[map].monster_x[k] == x+1 && taijimap[map].monster_y[k] == y)
							return 0; // ���ڸ��� ���Ͱ� �����ϱ� ������ ��ġ ������
					}
					else imsi_move++;
				}
				for(k=0;k<taijimap[map].dont_move_count;k++)
				{
					if(x+1 == taijimap[map].dont_move_x[k] && y == taijimap[map].dont_move_y[k])
						return 0;
				}
				return 1;
				
			}
			return 0; // ���̻� �̵��Ҽ� ���⿡ ���� 0
		}
	}
	
	return 1;
	
}








int move(int imsi)
{
	int magic_flag=0;
	int imsi_k;
	int imsi_move;
	// printf("�˻��ϱ� ����");		
	if(mid2[imsi].banghyang==02) // ĳ���Ͱ� �Ʒ��� ���� ������
	{
		if(mid2[imsi].map_y<taijimap[mid2[imsi].realmap].map_y_len)		
		{
			// printf("�Ʒ� ���� ������ �˻�\n");
			for(int k=0,imsi_move=taijimap[mid2[imsi].realmap].count;k<imsi_move;k++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
				{
					if(imsi!=taijimap[mid2[imsi].realmap].chrnumber[k])
					{
						// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
						if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y+1) 
						{
							// printf("�װ��� ����� �����Ƿ� ��ġ ������\n");
							return 0;
						}
						
					}
				}
				else imsi_move++;
																
			}
			// printf("�Ʒ� ���� ���� �˻�\n"); 
			for(k=0,imsi_move=taijimap[mid2[imsi].realmap].monster_count;k<imsi_move;k++)
			{
				if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
				{
					if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y+1)
						return 0; // ���ڸ��� ���Ͱ� �����ϱ� ������ ��ġ ������
				}
				else imsi_move++;
			}
			
			for(k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(mid2[imsi].map_x == taijimap[mid2[imsi].realmap].dont_move_x[k] && mid2[imsi].map_y+1 == taijimap[mid2[imsi].realmap].dont_move_y[k])
					return 0;
			}
			
			return 1;
			
			
			
		}
		
	}
	
	if(mid2[imsi].banghyang==01) // ĳ���Ͱ� �������� ���� ������
	{
		if(mid2[imsi].map_x<taijimap[mid2[imsi].realmap].map_x_len)		
		{
			// printf("������ �������� ������\n");
			for(int k=0,imsi_move=taijimap[mid2[imsi].realmap].count;k<imsi_move;k++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
				{
					if(imsi!=taijimap[mid2[imsi].realmap].chrnumber[k])
					{
						// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
						if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x+1) 
						{
							// printf("�װ��� ����� �����Ƿ� ��ġ ������\n");
							return 0;
						}
						
					}
				}
				else imsi_move++;
																
			}
			// printf("������ ���� ���� �˻�\n"); 
			for(k=0,imsi_move=taijimap[mid2[imsi].realmap].monster_count;k<imsi_move;k++)
			{
				if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
				{
					if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x+1)
						return 0; // ���ڸ��� ���Ͱ� �����ϱ� ������ ��ġ ������
				}
				else imsi_move++;
			}
			for(k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(mid2[imsi].map_x+1 == taijimap[mid2[imsi].realmap].dont_move_x[k] && mid2[imsi].map_y == taijimap[mid2[imsi].realmap].dont_move_y[k])
					return 0;
			}
			
			return 1;
			
		}
		
	}
	
	if(mid2[imsi].banghyang==00) // ĳ���Ͱ� ���� ���� ������
	{
		if(mid2[imsi].map_y>0)		
		{
			// printf("�� ������ �˻�\n");
			for(int k=0,imsi_move=taijimap[mid2[imsi].realmap].count;k<imsi_move;k++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
				{
					if(imsi!=taijimap[mid2[imsi].realmap].chrnumber[k])
					{
						// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
						if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y-1) 
						{
							// printf("�װ��� ����� �����Ƿ� ��ġ ������\n");
							return 0;
						}
						
					}
				}
				else imsi_move++;
																
			}
			// printf("�� ���� ���� �˻�\n"); 
			for(k=0,imsi_move=taijimap[mid2[imsi].realmap].monster_count;k<imsi_move;k++)
			{
				if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
				{
					if(taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x && taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y-1)
						return 0; // ���ڸ��� ���Ͱ� �����ϱ� ������ ��ġ ������
				}
				else imsi_move++;
			}
			for(k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(mid2[imsi].map_x == taijimap[mid2[imsi].realmap].dont_move_x[k] && mid2[imsi].map_y-1 == taijimap[mid2[imsi].realmap].dont_move_y[k])
					return 0;
			}
			
			return 1;
			
		}
		
	}
	
	
	if(mid2[imsi].banghyang==03) // ĳ���Ͱ� ������ ���� ������
	{
		if(mid2[imsi].map_x>0)		
		{
			// printf("���� �������� ���� �˻�\n");
			for(int k=0,imsi_move=taijimap[mid2[imsi].realmap].count;k<imsi_move;k++)
			{
				if(taijimap[mid2[imsi].realmap].threadlist[k]!=0)
				{
					if(imsi!=taijimap[mid2[imsi].realmap].chrnumber[k])
					{
						// printf("�̳��� ��ġ�� x = %d , y= %d \n", mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x,mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y);
						if(mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_y == mid2[imsi].map_y && mid2[taijimap[mid2[imsi].realmap].chrnumber[k]].map_x == mid2[imsi].map_x-1) 
						{
							// printf("�װ��� ����� �����Ƿ� ��ġ ������\n");
							return 0;
						}
						
					}
				}
				else imsi_move++;
																
			}
			// printf("���� ���� ���� �˻�\n"); 
			for(k=0,imsi_move=taijimap[mid2[imsi].realmap].monster_count;k<imsi_move;k++)
			{
				if(taijimap[mid2[imsi].realmap].monster_thread[k]!=0)
				{
					if(taijimap[mid2[imsi].realmap].monster_y[k] == mid2[imsi].map_y && taijimap[mid2[imsi].realmap].monster_x[k] == mid2[imsi].map_x-1)
						return 0; // ���ڸ��� ���Ͱ� �����ϱ� ������ ��ġ ������
				}
				else imsi_move++;
			}
			for(k=0;k<taijimap[mid2[imsi].realmap].dont_move_count;k++)
			{
				if(mid2[imsi].map_x-1 == taijimap[mid2[imsi].realmap].dont_move_x[k] && mid2[imsi].map_y == taijimap[mid2[imsi].realmap].dont_move_y[k])
					return 0;
			}
			
			return 1;
			
		}
		
	}
	
}


void packet_dump(char* buf, int size, int unit)
{
	char     tmp[150];
	char     msg[256];
	int      i, j, lno;
	
	j = 7;
	lno = 0;
	memset((tmp+0), 0x00, 150);
	
	for (i = 0; i < size; i++) {
		if((i%unit) == 0)
			memset((tmp+0), 0x20, ((unit*3)+unit+1+7+3));
		if(j == 7)
			sprintf((tmp+0), "[%4d] ", lno);
		sprintf((tmp+j), "%02x", (unsigned char)*(buf+i));
		tmp[j+2] = 0x20;
		if((unsigned char)*(buf+i) >= (unsigned char)0x20)
			tmp[(j/3)+(unit*3)+1+6] = *(buf+i);
		else
			tmp[(j/3)+(unit*3)+1+6] = '.';
		j += 3;
		if((i%unit) == (unit-1)) {
			//printf("%s\n", (tmp+0));
			j = 7;
			++lno;
		}
		else if((i%unit) == ((unit/2)-1))
			tmp[j-1] = '-';
	}
	
	if ((i % unit) != 0) {
		//printf("%s\n", (tmp+0));
	}
}


void printchar(unsigned char c)
{
	//	if(isprint(c))
	//printf("%c",c);
	//	else
	//printf(".");
}



struct packet_st 
{
	char head[2];
	char mes[2560];
};

packet_st			pack[2048];


int strc(char *a,char *b,int len) // ������ 00�� ����빮�� ���� ���Լ� ����//
{
	for(int i=0;i<len;i++)
	{
		if(a[i]!=b[i])
			return -1;
	}
	return 0;
}


void magic_run(int magic_number,int imsi,int delay_time,int socketnow,char *Messages,int *kaflag) // #�������
{
	// printf("���� ��� magic_number:%d\n",magic_number);
	switch(magic_number)
	{
	case 1:
		{
			//magic_01();
			if(mid2[imsi].sangtae==0)
			{
				magic_01_bojo(imsi);
				// printf("magic_number:%d\n",magic_number);
				
				break;
			}
			
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;
		}
		
		
	case 2:
		{
			if(mid2[imsi].sangtae==0)
			{
				//magic_02();
				magic_02_bojo(imsi);
				// printf("magic_number:%d\n",magic_number);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;
		}
		
	case 3:
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_03(imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow);
				// printf("magic_number:%d\n",magic_number);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 4:
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_04(imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow);
				// printf("magic_number:%d\n",magic_number);
				break;
				
			}
			
			
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			
			break;}
	case 5:
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_05(imsi,Messages);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 6:
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_06(imsi,Messages);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 7:
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_07(imsi,Messages,&*kaflag);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 8: // �񿵻�õ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_08(imsi,Messages,&*kaflag);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 9: // ��ȯ
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_09(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
				
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 10: // ���
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_10(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 11: // ���Ǽ�ȯ
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_11(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 12: // ��Ȳ��
		{
			if(mid2[imsi].sangtae==1)
			{
				magic_12(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a������ ���� �ֽ��ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
				break;
			}
			break;}
	case 13: // ������ ���
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_13(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 14: // ��������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_14(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 15: // ������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_15(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 16: // ü�»��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_16(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 17: // ��ȣ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_17(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 18: // ���»��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_18(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 19: // �����Ǳ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_19(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 20: // ��������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_20(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 21: // ��ȣ�����
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_21(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 22: // �����̾�
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_22(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 23: // ��������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_23(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 24: // ��ȣ�����'÷
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_24(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 25: // ��Ȱ
		{
			if(mid2[imsi].sangtae==0 || mid2[imsi].sangtae==1)
			{
				magic_25(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 26: // ����������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_26(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 27: // ������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_27(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 28: // ����������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_28(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 29: // �����̵�
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_29(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 30: // �����Ǳ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_30(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 31: // �¾��Ǳ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_31(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 32: // �����Ǳ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_32(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 33: // �����Ǳ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_33(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 34: // �ŷ��Ǳ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_34(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 35: // ��Ȳ�Ǳ�� 
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_35(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 36: // �ڸ��̵�
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_36(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 37: // �������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_37(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 38: // ������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_38(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 39: // �ǰ�볪��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_39(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 40: // ���;���
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_40(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 41: // �񿵽º�
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_41(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 42: // ��ȣ�˹�
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_42(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 43: // �̱���
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_43(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 44: // ������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_44(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 45: // ��ȿ��Ȳ
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_45(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 46: // ��������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_46(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 47: // ���̸���
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_47(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 48: // ��ȥ��õ
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_48(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 49: // �鿭��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_49(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 50: // ��ǳ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_50(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 51: // �����ȭ
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_51(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 52: // ȥ����
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_52(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 53: // ����
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_53(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 54: // �Ϳ���ȥ��
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_54(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 55: // ����������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_55(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 56: // ������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_56(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 57: // ����������
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_57(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 58: // �����̵�(��)
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_58(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 59: // �����̵�(��)
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_59(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 60: // �����̵�(��)
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_60(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
	case 61: // �����̵�(��)
		{
			if(mid2[imsi].sangtae==0)
			{
				magic_61(imsi,Messages,&*kaflag,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400);
				break;
			}
			else
			{
				int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
				int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
			}
			break;}
		
		
	default:
		break;
		}
		}
		
		
		
		
		// ���� �Լ� ���� ��� �� ����
		void err_quit(char *msg)
		{
			LPVOID lpMsgBuf;
			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER|
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL, WSAGetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf, 0, NULL);
			MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
			LocalFree(lpMsgBuf);
			//exit(-1);
		}
		
		
		// ���� �Լ� ���� ���
		void err_display(char *msg)
		{
			LPVOID lpMsgBuf;
			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER|
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL, WSAGetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf, 0, NULL);
			// printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
			LocalFree(lpMsgBuf);
		}
		
		
		
		DWORD WINAPI npc_thread(LPVOID arg) //#���ǽý�����
		{
			// printf("���ǽ� ������ ���� \n");
			
			{
				for(int c=0;c<npc_frec;c++) // ���� ����ŭ ����
				{
					rezen_function(npc_st[c].x,npc_st[c].y,npc_st[c].monster_number,npc_st[c].mapnumber);
				}
			}
			return 0;
			
			
		}
		
		
		DWORD WINAPI rezen_thread(LPVOID arg) //#����������
		{
			int rezen_time[8000]; // ���� ������ �ð��� ������ ����
			// printf("���������� ���� \n");
			while(1)
			{
				//printf("���������� ����\n");
				Sleep(setting_st.rezen);
				
				//# 3. ������ �ּ� 125�� ����
				char tmp[1];
				
				
				
				
				unsigned char buf[1000];
				memset(buf,4,1000);
				unsigned char md5sum[16];
				//printf("domain:%s\n",domain_name);
				
				
				for(int p=0;p<strlen(domain_name);p++)
				{
					buf[p]=domain_name[p];
				}
				
				
				
				
				//LeaveCriticalSection(&monster_cs);
				//LeaveCriticalSection(&save);
				//LeaveCriticalSection(&id);
				//for(int i=0;i<frecnum;i++)
				//{
				//	if(mid2[i].thread!=0)
				//	mid[i]=mid2[i];
				//}
				//fwrite();
				//EnterCriticalSection(&monster_cs);
				for(int c=0;c<rezen_frec;c++) // ���� ����ŭ ����
				{
					GetLocalTime( &st ); 
					
					if((st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400)-rezen_time[c] > rezen_st[c].time)
					{
						if(taijimap[rezen_st[c].mapnumber].monster_count<0)
							taijimap[rezen_st[c].mapnumber].monster_count=0;
						
						for(int d=0,int mcount=0;d<taijimap[rezen_st[c].mapnumber].monster_count;d++) // �׸��� ���� ����ŭ ����
						{
							if(taijimap[rezen_st[c].mapnumber].monster_number[d]==rezen_st[c].monster_number) // �׸��� ���Ϳ� ������ ���Ͱ� ������
								mcount++;
						}
						if(mcount+mcount_plus<rezen_st[c].monster_count) // ���� �� ���� ���͵��� ���� ���� ������ ������
						{
							int rezen=rezen_st[c].monster_count-mcount;// ��� ���� �ɰ��ΰ�
							for(int k=0;k<rezen;k++)
							{
								int x,y;
								
								
								while(1)
								{
									x = rand()%taijimap[rezen_st[c].mapnumber].map_x_len;
									y = rand()%taijimap[rezen_st[c].mapnumber].map_y_len;
									// printf("x: %d y: %d\n",x,y);
									int flag=0;
									for(int j=0,imsi_dont_move=taijimap[rezen_st[c].mapnumber].dont_move_count;j<imsi_dont_move;j++)
									{
										if(taijimap[rezen_st[c].mapnumber].dont_move_x[j]== x && taijimap[rezen_st[c].mapnumber].dont_move_y[j] ==y)
										{
											
											// printf("���� �����̹Ƿ� ��ǥ �缳��\n");
											flag=1;
											
										}
									}
									int imsi_dont_rezen;
									for(j=0,imsi_dont_rezen=taijimap[rezen_st[c].mapnumber].dont_rezen_count;j<imsi_dont_rezen;j++)
									{
										if(taijimap[rezen_st[c].mapnumber].dont_rezen_x[j]== x && taijimap[rezen_st[c].mapnumber].dont_rezen_y[j] ==y)
										{
											
											// printf("���� �����̹Ƿ� ��ǥ �缳��\n");
											flag=1;
											
										}
									}
									
									if(flag==0)
									{
										// printf("��ǥ ���� �Ϸ�\n");
										break;
									}
									
									
								}
								
								
								
								//rezen_function();
								//void rezen_function(int x,int y,int att,int ims)
								// printf("%d ��° ����\n",k);
								rezen_function(x,y,rezen_st[c].monster_number,rezen_st[c].mapnumber);
								GetLocalTime( &st ); 
								rezen_time[c]=st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400;
								
							}
							
							
						}
					}
					
					
					
					
					
					
				}
				
				
				
				
	}
	return 0;
	
	
}

DWORD WINAPI control_thread(LPVOID arg) //#�޴������� imsi 2323�� ����
{
	char mesg[100];
	memset(mesg,0,100);
	char mesg2[100];
	memset(mesg,0,100);
	char kk[2];
	int ct=0,flag_3=0;
	while(ct==0)
	{
		char sendmsg[100];
		memset(sendmsg,0,100);
		char swit;
		printf("�������� ���� ���α׷�\n1. ����������\n2. ������\n3. �ӼӸ�\n4. ��������\n5. chr���(chr���.txt�� ���Ӱ� ����)\n6. ������ ���� \n7. ��������\n");
		printf("�Է�:"); scanf("%s",&swit);
		gets(kk);
		if( swit>=49 && swit<=56 )
		{
			switch (atoi(&swit))
			{
			case 1:
				{ 
					
					int number;
					printf("���Ĺ��(1.���� 2.���� 3.��ġ 4.ü�� 5.����):"); scanf("%d",&number);
					
					int user_count=0;
					for(int i=0;i<frecnum;i++)
					{
						if(mid2[i].thread!=0)
						{
							sorts[user_count].lv=mid2[i].level;
							sorts[user_count].job=mid2[i].s_number;
							sorts[user_count].map=mid2[i].realmap;
							sorts[user_count].mana=mid2[i].max_mana;
							sorts[user_count].hel=mid2[i].max_hel;
							sorts[user_count].imsi=i;
							
							// printf("ID:%10s Lv:%3d Job:%6s ��ġ:%16s IP:%s\n",mid2[i].id,mid2[i].level,mid2[i].job,taijimap[mid2[i].realmap].name,mid2[i].ip);
							
							
							user_count++;
						}
					}
					
					switch(number)
					{
					case 1:
						{
							{
								
								for(int i =user_count-1; i >= 0; i--)
								{ 
									for(int j = 1; j <= i; j++)
									{
										if(sorts[j-1].lv > sorts[j].lv)
										{
											temps = sorts[j-1];
											sorts[j-1] = sorts[j];
											sorts[j] = temps;
										}
									}
								}
							}
							break;
						}
					case 2:
						{
							{
								
								for(int i =user_count-1; i >= 0; i--)
								{ 
									for(int j = 1; j <= i; j++)
									{
										if(sorts[j-1].job > sorts[j].job)
										{
											temps = sorts[j-1];
											sorts[j-1] = sorts[j];
											sorts[j] = temps;
										}
									}
								}
							}
							break;
						}
					case 3:
						{
							{
								
								for(int i =user_count-1; i >= 0; i--)
								{ 
									for(int j = 1; j <= i; j++)
									{
										if(sorts[j-1].map > sorts[j].map)
										{
											temps = sorts[j-1];
											sorts[j-1] = sorts[j];
											sorts[j] = temps;
										}
									}
								}
							}
							break;
						}
					case 4:
						{
							{
								
								for(int i =user_count-1; i >= 0; i--)
								{ 
									for(int j = 1; j <= i; j++)
									{
										if(sorts[j-1].hel > sorts[j].hel)
										{
											temps = sorts[j-1];
											sorts[j-1] = sorts[j];
											sorts[j] = temps;
										}
									}
								}
							}
							break;
						}
					case 5:
						{
							{
								
								for(int i =user_count-1; i >= 0; i--)
								{ 
									for(int j = 1; j <= i; j++)
									{
										if(sorts[j-1].mana > sorts[j].mana)
										{
											temps = sorts[j-1];
											sorts[j-1] = sorts[j];
											sorts[j] = temps;
										}
									}
								}
							}
							break;
						}
					default :
						{
							break;
							
						}
						
						
						
						
						
						
		  }
		  
		  printf("============================== ���� ����� ��� ==============================\n");
		  printf("==============================================================================\n");
		  
		  
		  {
			  for(int k=user_count-1;k>0 ;k--)
			  {
				  
				  if(int kk=printf("ID:%12s Lv:%3d Job:%6s ��ġ:%16s IP:%s\n",mid2[sorts[k].imsi].id,mid2[sorts[k].imsi].level,mid2[sorts[k].imsi].job,taijimap[mid2[sorts[k].imsi].realmap].name,mid2[sorts[k].imsi].ip)>0);
				  
			  }
		  }
		  printf("==============================================================================\n");
		  printf("�� %d �� ������\n\n",user_count-1);
		  
		  
		  
		  
		  break;
		  
		  
		  
	  }
  case 2:{  
	  printf("�޽���:"); gets(mesg);
	  
	  
	  
	  sprintf(sendmsg,"%c%c%c###���>> %s",0x05,0x00,12+strlen(mesg),mesg);
	  for(int k=0;k<frecnum;k++)
	  {
		  if(mid2[k].thread != 0)
		  {
			  
			  int len = Xc->Enc_Pack(2323,sendmsg,80,0x0a,1);
			  int retval = send(client[mid2[k].thread],Encrypted_Messages[2323],len, 0);
		  }
		  
	  }
	  break; }
  case 3:
	  {  
		  printf("���̵�:"); gets(mesg);
		  flag_3=0;
		  for(int k=0;k<frecnum;k++)
		  {
			  if(mid2[k].thread != 0)
			  {
				  
				  if(strcmp(mid2[k].id,mesg)==0)
				  {
					  flag_3=1;
					  
				  }
				  
				  
			  }
			  
		  }
		  if(flag_3 == 1)
		  {
			  printf("msg:"); gets(mesg2);
			  for(k=0;k<frecnum ;k++)
			  {
				  if(mid2[k].thread != 0)
				  {
					  
					  if(strcmp(mid2[k].id,mesg)==0)
					  {
						  char test[50];
						  memset(test,50,1);
						  int len = Xc->Enc_Pack(2323,test,50,33,1);
						  
						  sprintf(sendmsg,"%c%c%c(���):%s",0x00,0x00,strlen(mesg2)+9,mesg2);
						  
						  len = Xc->Enc_Pack(2323,sendmsg,strlen(mesg2)+9+3,0x0a,1);
						  send(client[mid2[k].thread],Encrypted_Messages[2323],len, 0);		  
						  
						  
					  }
					  
					  
				  }
				  
			  }
			  
		  }
		  if(flag_3==0)
			  printf("�������� �ƴմϴ�.\n");
		  
		  
		  break;}
  case 4:{  
	  for(int i=0;i<frecnum;i++)
	  {
		  if(mid2[i].thread!=0)
			  mid[i]=mid2[i];
	  }
	  fwrite();
	  printf("���� ���� �Ϸ�!!\n");
	  
	  break; 
		 }
  case 5:{ 
	  for(int i=0;i<frecnum;i++)
	  {
		  if(mid2[i].thread!=0)
			  mid[i]=mid2[i];
	  }
	  fwrite2();
	  printf("chr ��� �Ϸ�!!\n");
	  
	  break; 
		 }
  case 6:{  
	  printf("������ ���̵�:"); 
	  gets(mesg);
	  for(int k=0;k<frecnum;k++)
	  {
		  if(mid2[k].thread != 0)
		  {
			  
			  if(strcmp(mid2[k].id,mesg)==0)
			  {
				  
				  strcpy(ips[k].ip_chadan,mid2[k].ip);
				  ips_count++;
				  
				  
				  
			  }
			  
			  
		  }
		  
	  }
	  
	  
	  break; }
  case 7:{  
	  
	  int number;
	  int count;
	  printf("���Ĺ��(1.���� 2.���� 3.��ġ 4.ü�� 5.����):"); scanf("%d",&number);
	  printf("�������� ���ðڽ��ϱ�? "); scanf("%d",&count);
	  int user_count=0;
	  for(int i=0;i<frecnum;i++)
	  {
		  
		  sorts[user_count].lv=mid2[i].level;
		  sorts[user_count].job=mid2[i].s_number;
		  sorts[user_count].map=mid2[i].realmap;
		  sorts[user_count].mana=mid2[i].max_mana;
		  sorts[user_count].hel=mid2[i].max_hel;
		  sorts[user_count].imsi=i;
		  
		  // printf("ID:%10s Lv:%3d Job:%6s ��ġ:%16s IP:%s\n",mid2[i].id,mid2[i].level,mid2[i].job,taijimap[mid2[i].realmap].name,mid2[i].ip);
		  
		  
		  user_count++;
		  
	  }
	  
	  switch(number)
	  {
	  case 1:
		  {
			  {
				  
				  for(int i =user_count-1; i >= 0; i--)
				  { 
					  for(int j = 1; j <= i; j++)
					  {
						  if(sorts[j-1].lv > sorts[j].lv)
						  {
							  temps = sorts[j-1];
							  sorts[j-1] = sorts[j];
							  sorts[j] = temps;
						  }
					  }
				  }
			  }
			  break;
		  }
	  case 2:
		  {
			  {
				  
				  for(int i =user_count-1; i >= 0; i--)
				  { 
					  for(int j = 1; j <= i; j++)
					  {
						  if(sorts[j-1].job > sorts[j].job)
						  {
							  temps = sorts[j-1];
							  sorts[j-1] = sorts[j];
							  sorts[j] = temps;
						  }
					  }
				  }
			  }
			  break;
		  }
	  case 3:
		  {
			  {
				  
				  for(int i =user_count-1; i >= 0; i--)
				  { 
					  for(int j = 1; j <= i; j++)
					  {
						  if(sorts[j-1].map > sorts[j].map)
						  {
							  temps = sorts[j-1];
							  sorts[j-1] = sorts[j];
							  sorts[j] = temps;
						  }
					  }
				  }
			  }
			  break;
		  }
	  case 4:
		  {
			  {
				  
				  for(int i =user_count-1; i >= 0; i--)
				  { 
					  for(int j = 1; j <= i; j++)
					  {
						  if(sorts[j-1].hel > sorts[j].hel)
						  {
							  temps = sorts[j-1];
							  sorts[j-1] = sorts[j];
							  sorts[j] = temps;
						  }
					  }
				  }
			  }
			  break;
		  }
	  case 5:
		  {
			  {
				  
				  for(int i =user_count-1; i >= 0; i--)
				  { 
					  for(int j = 1; j <= i; j++)
					  {
						  if(sorts[j-1].mana > sorts[j].mana)
						  {
							  temps = sorts[j-1];
							  sorts[j-1] = sorts[j];
							  sorts[j] = temps;
						  }
					  }
				  }
			  }
			  break;
		  }
	  default :
		  {
			  break;
			  
		  }
		  
		  
		  
		  
		  
		  
		  }
		  
		  printf("============================== ����� ����      ==============================\n");
		  printf("==============================================================================\n");
		  
		  
		  {
			  for(int k=user_count-1,imsi_count=1;k>user_count-count-1;k--)
			  {
				  
				  //if(int kk=printf("%3d�� ID:%12s Lv:%3d Job:%6s ��ġ:%16s IP:%s\n",imsi_count,mid2[sorts[k].imsi].id,mid2[sorts[k].imsi].level,mid2[sorts[k].imsi].job,taijimap[mid2[sorts[k].imsi].realmap].name,mid2[sorts[k].imsi].ip)>0)
				  printf("%3d�� ID:%12s Lv:%3d Job:%6s ��ġ:%16s IP:%s\n",imsi_count,mid2[sorts[k].imsi].id,mid2[sorts[k].imsi].level,mid2[sorts[k].imsi].job,taijimap[mid2[sorts[k].imsi].realmap].name,mid2[sorts[k].imsi].ip);
				  imsi_count++;
				  
			  }
		  }
		  printf("==============================================================================\n");
		  printf("�� %d �� ����� ����\n\n",user_count);
		  
		  
		  break; }
		  
  default:{ break; }
  }
 }
 else
 { 
	 ct=0;
	 
	 
 }
	}
	return 0;
	
	
	
	
}

DWORD WINAPI autosave_thread(LPVOID arg) //#�ڵ�����
{
	
	while(1)
	{
		Sleep(auto_save);
		for(int i=0;i<frecnum;i++)
		{
			if(mid2[i].thread!=0)
				mid[i]=mid2[i];
		}
		fwrite();
		char test[50];
		memset(test,50,1);
		int len = Xc->Enc_Pack(2323,test,50,33,1);
		for(int k=0;k<frecnum;k++)
		{
			if(mid2[k].thread != 0)
			{
				
				int retval = send(client[mid2[k].thread],Encrypted_Messages[2323],len, 0);
			}
			
		}
		printf("\n�Է�:");
	}
	for(int j=0;j<MAX_MAP && taijimap[j].count!=0 ;j++)
	{
		taijimap[j].count=0;
	}
	for(int k=0;k<frecnum;k++)
	{
		if(mid2[k].thread != 0)
		{
			
			taijimap[mid2[k].realmap].count++;
		}
		
	}
	
	
	
	
	return 0;
	
	
	
	
}

DWORD WINAPI autoreset_thread(LPVOID arg) //#�ڵ�����
{
	
	while(1)
	{
		Sleep(10000);
		Sleep(auto_reset);
		for(int i=0;i<frecnum;i++)
		{
			if(mid2[i].thread!=0)
				mid[i]=mid2[i];
		}
		fwrite();
		char test[50];
		memset(test,50,1);
		int len = Xc->Enc_Pack(2323,test,50,33,1);
		for(int k=0;k<frecnum;k++)
		{
			if(mid2[k].thread != 0)
			{
				
				
				
				char sendmsg[80];			  
				memset(sendmsg,0,80);
				sprintf(sendmsg,"%c%c%c�ý���:  ������ �ڵ������մϴ�. ���������ּ���.",0x00,0x00,56);
				
				len = Xc->Enc_Pack(2323,sendmsg,59,0x0a,1);
				send(client[mid2[k].thread],Encrypted_Messages[2323],len, 0);	
				
				{
					
					
					
					
					
					//taijimap[mid2[k].realmap].count--;
					//taijimap[mid2[k].realmap].threadlist[mid2[k].kaflag]=0;
					//taijimap[mid2[k].realmap].chrnumber[mid2[k].kaflag]=0;
					//						closesocket(client[mid2[k].thread]);
					//mid2[k].thread=0;
					//mid2[k].group=0;
					
					//mid[k]=mid2[k]; // ����Ÿ �簻��
					
				}
				
			}
			
			
			
		}
		Sleep(3000);
		
		
		printf("�ڵ�������!!\n\n\n\n");
		
		exit(0);
		
		
		
		
		
		
	}
	
	return 0;
	
	
	
	
}


DWORD WINAPI Monster_thread(LPVOID arg) //#���ͽ�����
{
	// printf("���ͽ����� ����\n");
	
	
	
	while(1)
	{
		Sleep(1000);
		
		
		for(int i=0;i<MAXMAP;i++)
		{
			//// printf("i=%d ",i);
			if(taijimap[i].count!=0)
			{
				
				//WaitForSingleObject(die_event,INFINITE);
				int j=0;
				if(taijimap[i].monster_count<0) taijimap[i].monster_count=0;
				for(mon_imsi_c[i]=taijimap[i].monster_count;j<mon_imsi_c[i];j++)
				{
					
					//printf("���� ���� : %d\n",j);
					
					
					if(taijimap[i].monster_thread[j]!=0)
					{
						int rand2;rand2=rand();
						if(taijimap[i].count!=0)
							rand2=rand2%taijimap[i].count;
						else
							rand2=0;
						//printf("j = %d\n",j);
						//printf("mon_imsi_c[i]= %d\n",mon_imsi_c[i]);
						for(int k=rand2,int monster_flag=0,int imsi_count=taijimap[i].count;k<imsi_count&&monster_flag==0;k++)
						{
							
							if(taijimap[i].threadlist[k] != 0 )
							{
								
								
								
								
								if(taijimap[i].monster_x[j]+10 > mid2[taijimap[i].chrnumber[k]].map_x ||
									taijimap[i].monster_y[j]+10 > mid2[taijimap[i].chrnumber[k]].map_y ||
									taijimap[i].monster_x[j]-10 < mid2[taijimap[i].chrnumber[k]].map_x ||
									taijimap[i].monster_y[j]-10 < mid2[taijimap[i].chrnumber[k]].map_y) // ���Ͱ� ���� ȭ�鿡 ���̸�
								{
									if(monster[taijimap[i].monster_number[j]].type==1)
									{
										
										
										if(taijimap[i].monster_number)
											monster_flag=1;
										char peer0_2[15];
										ResetEvent(monster_event);
										peer0_2[0]='\x00';
										peer0_2[1]='\x01';
										peer0_2[2]=(taijimap[i].monster_x[j] & 0x0000ff00 ) >> 8;
										peer0_2[3]=(taijimap[i].monster_x[j] & 0x000000ff ) ;
										peer0_2[4]=(taijimap[i].monster_y[j] & 0x0000ff00 ) >> 8;
										peer0_2[5]=(taijimap[i].monster_y[j] & 0x000000ff ) ;
										peer0_2[6]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
										peer0_2[7]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
										peer0_2[8]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
										peer0_2[9]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
										peer0_2[10]=(taijimap[i].monster_number[j]+32767 & 0x0000ff00 ) >> 8;
										peer0_2[11]=(taijimap[i].monster_number[j]+32767 & 0x000000ff ) ;
										peer0_2[12]=monster[taijimap[i].monster_number[j]].color;
										peer0_2[13]=taijimap[i].monster_banghyang[j];
										peer0_2[14]='\x00';
										
										
										int len = Xc->Enc_Pack(2506,peer0_2,15,0x07,1);	
										for(int mapcount=0,imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
										{
											if(taijimap[i].threadlist[mapcount] != 0 )
											{
												//			// printf(" %d��° �������� �������� ���� ����.\n",taijimap[i].threadlist[mapcount]);
												if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
													int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2506],len, 0);  
												
											}
											else imsi_count++;
										}
										SetEvent(monster_event);
										
										
										
										
										if(taijimap[i].monster_target[j] == 0) // ������ Ÿ���� ������ ���� �ʴٸ�
										{
											//		// printf("Ÿ������ \n");
											taijimap[i].monster_target[j] = taijimap[i].chrnumber[k];
											// printf("taiji: %d\n",taijimap[i].chrnumber[k]);
										}
										
										
										
										
										if(taijimap[i].monster_target[j] != 0) // ������ Ÿ���� ������ �ִٸ� 
										{
											if(taijimap[i].monster_x[j]+10 < mid2[taijimap[i].monster_target[j]].map_x || 
												taijimap[i].monster_y[j]+10 < mid2[taijimap[i].monster_target[j]].map_y ||
												taijimap[i].monster_x[j]-10 > mid2[taijimap[i].monster_target[j]].map_x ||
												taijimap[i].monster_y[j]-10 > mid2[taijimap[i].monster_target[j]].map_y || mid2[taijimap[i].monster_target[j]].thread==0 || 
												mid2[taijimap[i].monster_target[j]].sangtae==1) // ���� Ÿ���� �������
											{
												//			// printf("Ÿ�� ��ħ \n");
												taijimap[i].monster_target[j] =0; 
											}
											
											if(taijimap[i].monster_target[j] != 0) // ������ ���� Ÿ���� �Ȼ�������� 
											{
												//			// printf(" monster x,y : %d %d\n",taijimap[i].monster_x[j],taijimap[i].monster_y[j]);
												//			// printf(" user    x,y : %d %d\n",mid2[taijimap[i].monster_target[j]].map_x,mid2[taijimap[i].monster_target[j]].map_y);
												int mflag=0;
												
												if(
													taijimap[i].monster_x[j] == mid2[taijimap[i].monster_target[j]].map_x &&
													taijimap[i].monster_y[j]+1 == mid2[taijimap[i].monster_target[j]].map_y
													) {taijimap[i].monster_banghyang[j]=2; mflag=1;}
												if(
													taijimap[i].monster_x[j] == mid2[taijimap[i].monster_target[j]].map_x &&
													taijimap[i].monster_y[j]-1 == mid2[taijimap[i].monster_target[j]].map_y
													) {taijimap[i].monster_banghyang[j]=0; mflag=1;}
												if(
													taijimap[i].monster_y[j] == mid2[taijimap[i].monster_target[j]].map_y &&
													taijimap[i].monster_x[j]+1 == mid2[taijimap[i].monster_target[j]].map_x
													) {taijimap[i].monster_banghyang[j]=1; mflag=1;}
												if(
													taijimap[i].monster_y[j] == mid2[taijimap[i].monster_target[j]].map_y &&
													taijimap[i].monster_x[j]-1 == mid2[taijimap[i].monster_target[j]].map_x
													) {taijimap[i].monster_banghyang[j]=3; mflag=1;}
												
												if(mflag!=0 && i ==  mid2[taijimap[i].monster_target[j]].realmap)
												{
													// printf("attack\n");
													char peer0_2[15];
													ResetEvent(monster_event);
													peer0_2[0]='\x00';
													peer0_2[1]='\x01';
													peer0_2[2]=(taijimap[i].monster_x[j] & 0x0000ff00 ) >> 8;
													peer0_2[3]=(taijimap[i].monster_x[j] & 0x000000ff ) ;
													peer0_2[4]=(taijimap[i].monster_y[j] & 0x0000ff00 ) >> 8;
													peer0_2[5]=(taijimap[i].monster_y[j] & 0x000000ff ) ;
													peer0_2[6]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
													peer0_2[7]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
													peer0_2[8]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
													peer0_2[9]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
													peer0_2[10]=(taijimap[i].monster_number[j]+32767 & 0x0000ff00 ) >> 8;
													peer0_2[11]=(taijimap[i].monster_number[j]+32767 & 0x000000ff ) ;
													peer0_2[12]=monster[taijimap[i].monster_number[j]].color;
													peer0_2[13]=taijimap[i].monster_banghyang[j];
													peer0_2[14]='\x00';
													
													
													
													int len = Xc->Enc_Pack(2507,peer0_2,15,0x07,1);	
													for(int mapcount=0,imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
													{
														if(taijimap[i].threadlist[mapcount] != 0)
														{
															//					// printf(" %d��° �������� �������� ���� ����.\n",taijimap[i].threadlist[mapcount]);
															if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
																int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2507],len, 0);  
															
															
														}
														else imsi_count++;
													}
													SetEvent(monster_event);
													{ // ���Ͱ� ������ �κ�
														if(mid2[taijimap[i].monster_target[j]].ac<0)
														{
															mid2[taijimap[i].monster_target[j]].hel=mid2[taijimap[i].monster_target[j]].hel-monster[taijimap[i].monster_number[j]].power-
																(float(mid2[taijimap[i].monster_target[j]].ac*0.01)*monster[taijimap[i].monster_number[j]].power);
														}
														if(mid2[taijimap[i].monster_target[j]].ac>0)
														{
															mid2[taijimap[i].monster_target[j]].hel=mid2[taijimap[i].monster_target[j]].hel-monster[taijimap[i].monster_number[j]].power+
																(float(mid2[taijimap[i].monster_target[j]].ac*0.01)*monster[taijimap[i].monster_number[j]].power);
														}
														if(mid2[taijimap[i].monster_target[j]].ac==0)
														{
															mid2[taijimap[i].monster_target[j]].hel=mid2[taijimap[i].monster_target[j]].hel
																-monster[taijimap[i].monster_number[j]].power;
														}													
														if(mid2[taijimap[i].monster_target[j]].hel>mid2[taijimap[i].monster_target[j]].max_hel)
														{
															mid2[taijimap[i].monster_target[j]].hel=0;
															mid2[taijimap[i].monster_target[j]].sangtae=1;
															
															
															char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
															int sendmsg_byte=loginchr(taijimap[i].monster_target[j],sendmsg2);
															
															int len = Xc->Enc_Pack(2508,sendmsg2,sendmsg_byte,0x33,1);
															for(int mapcount=0,imsi_count=taijimap[mid2[taijimap[i].monster_target[j]].realmap].count;mapcount<imsi_count;mapcount++)
															{
																if(taijimap[mid2[taijimap[i].monster_target[j]].realmap].threadlist[mapcount] != 0 )
																{
																	int retval = send(client[taijimap[mid2[taijimap[i].monster_target[j]].realmap].threadlist[mapcount]],Encrypted_Messages[2508],len, 0);  
																}
																else imsi_count++;
															}
														}
														
														
														che_bar_attack(2509,taijimap[i].monster_target[j],hel_percent(taijimap[i].monster_target[j]));	
														
													}
													
													char test[9];
													
													ResetEvent(monster_event);
													test[0]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 32;
													test[1]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;
													test[2]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
													test[3]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
													
													test[5]='\x00';
													test[6]='\x00';
													test[7]='\x00';
													test[8]='\x00';
													
													
													
													switch(taijimap[i].monster_banghyang[j])
													{
													case 0:
														{
															test[4]='\x01';
															mimsi++;
															break;
														}
													case 1:
														{
															
															test[4]='\x01';
															break;
														}
													case 2:
														{
															test[4]='\x01';
															break;
														}
													case 3:
														{
															test[4]='\x01';	
															break;
														}
													}
													
													
													
													len = Xc->Enc_Pack(2510,test,9,0x1a,1);	
													for(mapcount=0,imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
													{
														if(taijimap[i].threadlist[mapcount] != 0 )
														{
															//					// printf(" %d��° �������� �������� ���� ����.\n",taijimap[i].threadlist[mapcount]);
															if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
																int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2510],len, 0);  
															
														}
														else imsi_count++;
													}
													SetEvent(monster_event);
										}
										else
										{
											//				// printf("�̵�\n");
											if( taijimap[i].monster_thread[j]!=0)
											{
												int mflag=0;
												taijimap[i].monster_move_flag[j]=0;
												int loop;
												int rand1;rand1=rand();
												rand1=rand1%8;
												
												if(rand1==0)
												{
													ResetEvent(monster_event);
													mflag=move_monster_down(i,j,mflag);
													mflag=move_monster_right(i,j,mflag);
													mflag=move_monster_left(i,j,mflag);
													mflag=move_monster_up(i,j,mflag);
													
													if(taijimap[i].monster_move_flag[j]==3) rand1=3;
													SetEvent(monster_event);
												}
												if(rand1==1)
												{
													ResetEvent(monster_event);
													mflag=move_monster_down(i,j,mflag);
													mflag=move_monster_left(i,j,mflag);
													mflag=move_monster_right(i,j,mflag);												
													mflag=move_monster_up(i,j,mflag);
													
													if(taijimap[i].monster_move_flag[j]==3) rand1=3;
													SetEvent(monster_event);
												}
												if(rand1==2)
												{
													ResetEvent(monster_event);
													mflag=move_monster_right(i,j,mflag);
													mflag=move_monster_down(i,j,mflag);
													mflag=move_monster_up(i,j,mflag);												
													mflag=move_monster_left(i,j,mflag);
													
													
													if(taijimap[i].monster_move_flag[j]==3) rand1=5;
													SetEvent(monster_event);
													
												}
												if(rand1==3)
												{
													ResetEvent(monster_event);
													mflag=move_monster_right(i,j,mflag);
													mflag=move_monster_up(i,j,mflag);
													mflag=move_monster_down(i,j,mflag);
													mflag=move_monster_left(i,j,mflag);
													
													if(taijimap[i].monster_move_flag[j]==3) rand1=5;
													SetEvent(monster_event);
												}
												if(rand1==4)
												{
													ResetEvent(monster_event);
													mflag=move_monster_up(i,j,mflag);
													mflag=move_monster_right(i,j,mflag);
													mflag=move_monster_left(i,j,mflag);
													mflag=move_monster_down(i,j,mflag);
													
													if(taijimap[i].monster_move_flag[j]==3) rand1=7;
													SetEvent(monster_event);
												}
												if(rand1==5)
												{
													ResetEvent(monster_event);
													
													mflag=move_monster_up(i,j,mflag);
													mflag=move_monster_left(i,j,mflag);
													mflag=move_monster_right(i,j,mflag);
													mflag=move_monster_down(i,j,mflag);
													
													if(taijimap[i].monster_move_flag[j]==3) rand1=7;
													SetEvent(monster_event);
													
													
												}
												if(rand1==6)
												{
													ResetEvent(monster_event);
													mflag=move_monster_left(i,j,mflag);
													mflag=move_monster_down(i,j,mflag);
													mflag=move_monster_up(i,j,mflag);												
													mflag=move_monster_right(i,j,mflag);
													if(taijimap[i].monster_move_flag[j]==3) 
													{
														mflag=move_monster_up(i,j,mflag);
														mflag=move_monster_left(i,j,mflag);
														mflag=move_monster_right(i,j,mflag);
														mflag=move_monster_down(i,j,mflag);
													}
													SetEvent(monster_event);
													
												}
												if(rand1==7)
												{
													ResetEvent(monster_event);
													mflag=move_monster_left(i,j,mflag);
													mflag=move_monster_up(i,j,mflag);
													mflag=move_monster_down(i,j,mflag);																								
													mflag=move_monster_right(i,j,mflag);
													if(taijimap[i].monster_move_flag[j]==3) 
													{
														mflag=move_monster_up(i,j,mflag);
														mflag=move_monster_left(i,j,mflag);
														mflag=move_monster_right(i,j,mflag);
														mflag=move_monster_down(i,j,mflag);
													}
													SetEvent(monster_event);
													
													
													
												}
											} // ���� ������ ��
											
											
											
										}
									}
								}
							}// type1 ����
							if(monster[taijimap[i].monster_number[j]].type==3 &&taijimap[i].monster_thread[j]!=0)
							{
								
								char peer0_2[15];
								peer0_2[0]='\x00';
								peer0_2[1]='\x01';
								peer0_2[2]=(taijimap[i].monster_x[j] & 0x0000ff00 ) >> 8;
								peer0_2[3]=(taijimap[i].monster_x[j] & 0x000000ff ) ;
								peer0_2[4]=(taijimap[i].monster_y[j] & 0x0000ff00 ) >> 8;
								peer0_2[5]=(taijimap[i].monster_y[j] & 0x000000ff ) ;
								peer0_2[6]=(taijimap[i].monster_thread[j] & 0xff000000 ) >> 24;
								peer0_2[7]=(taijimap[i].monster_thread[j] & 0x00ff0000 ) >> 16;  
								peer0_2[8]=(taijimap[i].monster_thread[j] & 0x0000ff00 ) >> 8;
								peer0_2[9]=(taijimap[i].monster_thread[j] & 0x000000ff ) ;
								peer0_2[10]=(taijimap[i].monster_number[j]+32767 & 0x0000ff00 ) >> 8;
								peer0_2[11]=(taijimap[i].monster_number[j]+32767 & 0x000000ff ) ;
								peer0_2[12]='\x00';
								peer0_2[13]=taijimap[i].monster_banghyang[j];
								peer0_2[14]='\x00';
								
								
								int len = Xc->Enc_Pack(2511,peer0_2,15,0x07,1);	
								for(int mapcount=0,imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[i].threadlist[mapcount] != 0)
									{
										//					// printf(" %d��° �������� �������� ���� ����.\n",taijimap[i].threadlist[mapcount]);
										if(taijimap[i].monster_thread[j]  != 0 && taijimap[i].monster_hel!=0)
											int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2511],len, 0);  
										
									}
									else imsi_count++;
								}
								
								
								
							}
							
							}
							//k=imsi_count+1;
							
							
						}			
						else
						{
							imsi_count++;
						}
					}
					//for
					
					} else mon_imsi_c[i]++;
					SetEvent(monster_event);
					
					
				}//for
				
			}//if
			
		}//for
		
		
	}
	return 0;
}

int test(int i,int j,int mflag)
{
	// printf("������ �̵� ����\n");
	char move_monster[11];
	move_monster[0]=(1 & 0xff000000 ) >> 24;
	move_monster[1]=(1 & 0x00ff0000 ) >> 16;  
	move_monster[2]=(1 & 0x0000ff00 ) >> 8;
	move_monster[3]=(1 & 0x000000ff ) ;
	move_monster[4]=(5 & 0x0000ff00 ) >> 8;
	move_monster[5]=(5 & 0x000000ff ) ;
	move_monster[6]=(7 & 0x0000ff00 ) >> 8;
	move_monster[7]=(7 & 0x000000ff ) ;
	move_monster[8]='\x01';
	move_monster[9]='\x00';
	move_monster[10]='\x00';
	taijimap[i].monster_banghyang[j]=3;
	int m_check=monster_move_check(i,j,taijimap[i].monster_x[j]
		,taijimap[i].monster_y[j]); // ���� �̵� üũ
	if(m_check==1)
		
	{
		taijimap[i].monster_x[j]++;
		
		
		
		int len = Xc->Enc_Pack(2506,move_monster,11,0x0c,1);
		
		for(int mapcount=0,int imsi_count=taijimap[i].count;mapcount<imsi_count;mapcount++)
		{
			if(taijimap[i].threadlist[mapcount] != 0)
			{
				// printf(" %d��° �������� �������� ���� �̵��� ����.\n",taijimap[i].threadlist[mapcount]);
				// printf(" ������ ������ %d \n",taijimap[i].monster_thread[j]);
				int retval = send(client[taijimap[i].threadlist[mapcount]],Encrypted_Messages[2506],len, 0);  
			}
			else imsi_count++;
		}
		
		
		taijimap[i].monster_move_flag[j]=1; // �ϴ� �̵��ϰ� ���� 1�̵� 
		// printf("������ �̵� ������\n");
		return 1;
	}
	else taijimap[i].monster_move_flag[j]=3; // �ϴ� ��ֹ� Ȯ���ϸ� 3�� ��
	return 0;
}
void npc_msg(int imsi,char *msg1,char *msg2)
{
	char sendmsg[100];
	// printf("���ϱ� ��Ŷ�� �޾ҽ��ϴ�. imsi=%d\n",imsi);
	
	sendmsg[0] = '\x01';
	sendmsg[1] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0xff000000 ) >> 24;
	sendmsg[2] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x00ff0000) >> 16;
	sendmsg[3] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x0000ff00) >> 8;
	sendmsg[4] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x000000ff) ;
	sendmsg[5] = '\x52';
	strcpy(sendmsg+6,msg1);
	sendmsg[6+strlen(msg1)] = '\x3a';
	sendmsg[7+strlen(msg1)] = '\x20';
	memcpy(sendmsg+8+strlen(msg1),msg2,80);
	
	
	
	
	int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
	// printf("imsi = %d \n",imsi);
	
	for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
	{
		
		if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
		{
			// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
			int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
		}else {
			
			// printf("0 �̹Ƿ� imsi_count ����\n");
			imsi_count++;
		}
	}
	
}

void npc_all(int sangjum,int imsi,char *msg,char *npc_name)
{
	
	int len,retval;
	if(strcmp(msg,"�� �Ĵ�")==0 || strcmp(msg,"���Ĵ�")==0 ||
		strcmp(msg,"�� �Ĵ�?")==0 || strcmp(msg,"���Ĵ�?")==0
		|| strcmp(msg,"���Ⱦ�?")==0 || strcmp(msg,"���Ⱦ�")==0
		|| strcmp(msg,"�� �Ⱦ�?")==0 || strcmp(msg,"�� �Ⱦ�")==0)
	{
		int count=0;
		len = Xc->Enc_Pack(imsi,"\x03\x00\x1a��� ��ɾ�: �� ���",25,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
		len = Xc->Enc_Pack(imsi,"\x03\x00\x1a       �Ǹ� ���",25,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
		for(int j=0;j<npc_item_frec;j++)
		{
			
			if(npc_item_st[j].mapnumber==sangjum)
			{
				
				char msg[40];
				memset(msg,40,0);
				sprintf(msg,"%c%c%c%15s :%d��",0x03,0x00,0x1a,npc_item_st[j].name,npc_item_st[j].npc_sell);
				len = Xc->Enc_Pack(imsi,msg,6+strlen(msg+3),0x0a,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
				count++;
			}
		}
		char msg[40];
		sprintf(msg,"�� %d ������ �Ǹ��ϰ� �ֽ��ϴ�.",count);
		
		npc_msg(imsi,npc_name,msg);
		
		
	}
	if(strcmp(msg,"�� ���")==0 || strcmp(msg,"�����")==0 ||
		strcmp(msg,"�� ���?")==0 || strcmp(msg,"�����?")==0)
	{
		len = Xc->Enc_Pack(imsi,"\x03\x00\x1f�Ĵ� ��ɾ�: �� ���Ǵ�",30,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
		len = Xc->Enc_Pack(imsi,"\x03\x00\x1a       ���� ���",25,0x0a,1);
		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
		int count=0;
		for(int j=0;j<npc_item_frec;j++)
		{
			if(npc_item_st[j].mapnumber==sangjum)
			{
				
				char msg[40];
				memset(msg,40,0);
				sprintf(msg,"%c%c%c%15s :%d��",0x03,0x00,0x1a,npc_item_st[j].name,npc_item_st[j].user_sell);
				len = Xc->Enc_Pack(imsi,msg,6+strlen(msg+3),0x0a,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
				count++;
			}
		}
		char msg[40];
		sprintf(msg,"�� %d ������ �����ϰ� �ֽ��ϴ�.",count);
		
		npc_msg(imsi,npc_name,msg);
		
		
	}
	
	
	for(int j=0;j<npc_item_frec;j++)
	{
		
		if(npc_item_st[j].mapnumber==sangjum)
		{
			char msg2[60];			
			char msg3[60];
			char msg4[60];
			
			sprintf(msg2,"%s ���Ǵ�",npc_item_st[j].name);
			sprintf(msg3,"%s �� �Ǵ�",npc_item_st[j].name);
			sprintf(msg4,"%s �Ǵ�",npc_item_st[j].name);
			
			
			if(strcmp(msg2,msg)==0 || strcmp(msg3,msg)==0 || strcmp(msg4,msg)==0)
			{
				for(int item_count=0;item_count<26;item_count++)
				{
					if(mid2[imsi].item[item_count][0]==npc_item_st[j].number+49151)
					{
						
						char msg5[60];
						sprintf(msg5,"%s %d���� %d���� ���Ƚ��ϴ�.",npc_item_st[j].name
							,mid2[imsi].item[item_count][1],npc_item_st[j].user_sell*mid2[imsi].item[item_count][1]);
						npc_msg(imsi,npc_name,msg5);
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						mid2[imsi].money=mid2[imsi].money+npc_item_st[j].user_sell*mid2[imsi].item[item_count][1];
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
					}
				}
				
			}
		}
	}
	for( j=0;j<npc_item_frec;j++)
	{
		
		if(npc_item_st[j].mapnumber==sangjum)
		{
			char msg2[60];			
			char msg3[60];
			char msg4[60];
			
			sprintf(msg2,"%s ��",npc_item_st[j].name);
			sprintf(msg3,"%s ���",npc_item_st[j].name);
			sprintf(msg3,"%s ���.",npc_item_st[j].name);
			
			
			if(strcmp(msg2,msg)==0 || strcmp(msg3,msg)==0 || strcmp(msg4,msg)==0)
			{
				if(mid2[imsi].money<npc_item_st[j].npc_sell)
				{
					npc_msg(imsi,npc_name,"�մ�, ���� ���� �մϴ�.");
				}
				else
				{
					
					
					int imsiflag=0;
					for(int i=0;i<26;i++) 
					{
						
						if(mid2[imsi].item[i][0]==npc_item_st[j].number+49151) // �̹� �ִ� �������� ���
						{
							// printf("name: %s\n",item_st[j].name);
							// printf("number : %d\n",j);
							// printf("�̹� �ִ� ������\n");
							mid2[imsi].item[i][1]++;
							char item2[100];
							sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
								i+1,(npc_item_st[j].number+49151 & 0x0000ff00)  >> 8
								,(npc_item_st[j].number+49151 & 0x000000ff) ,0x00,0x20,item_st[npc_item_st[j].number].name
								,mid2[imsi].item[i][1],0x00,0x00,0x00);
							
							len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
							retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
							
							imsiflag=1;
							
							
							
							
							i = 26;
						}
					}
					if(imsiflag!=1)
					{
						for(int i=0;i<26;i++) 
						{
							if(mid2[imsi].item[i][0]==0) // ���ο� �������� ���
							{
								// printf("name: %s\n",item_st[j].name);
								// printf("number : %d\n",j);
								// printf("�� ������\n");
								mid2[imsi].item[i][0]=npc_item_st[j].number+49151;
								mid2[imsi].item[i][1]++;
								char item2[100];
								sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
									i+1,(npc_item_st[j].number+49151 & 0x0000ff00)  >> 8
									,(npc_item_st[j].number+49151 & 0x000000ff) ,0x00,0x20,item_st[npc_item_st[j].number].name
									,mid2[imsi].item[i][1],0x00,0x00,0x00);
								
								len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
								retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
								
								i = 26;
							}
							
							
						}
					}
					mid2[imsi].money=mid2[imsi].money-npc_item_st[j].npc_sell;
					exp_money(imsi,imsi);
					char msg44[40];
					sprintf(msg44,"%s�� %d���� �Ⱦҽ��ϴ�.",npc_item_st[j].name,npc_item_st[j].npc_sell);
					npc_msg(imsi,npc_name,msg44);
					
					
					
					
				} // else ��
			}
		}
	}
	
}
//#bomb


int msg_check(int imsi,char *msg)
{
	int len,retval,kkflag;
	
	
	

	if(mid2[imsi].realmap==129 || mid2[imsi].realmap==130)
	{
		if(strcmp(msg,"����ּ���")==0)
		{
			
			if(mid2[imsi].sangtae==1)
			{
				char sendmsg[100];
				// printf("���ϱ� ��Ŷ�� �޾ҽ��ϴ�. imsi=%d\n",imsi);
				
				sendmsg[0] = '\x00';
				sendmsg[1] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0xff000000 ) >> 24;
				sendmsg[2] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x00ff0000) >> 16;
				sendmsg[3] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x0000ff00) >> 8;
				sendmsg[4] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x000000ff) ;
				sendmsg[5] = '\x52';
				memcpy(sendmsg+6,"��Ȳ�Ҹ�",8);
				sendmsg[6+8] = '\x3a';
				sendmsg[7+8] = '\x20';
				memcpy(sendmsg+8+8,"�ҸŰ� ����� ���� �й�����ٰ� ����ִ°Ŵ�.",80);
				
				
				len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
				// printf("imsi = %d \n",imsi);
				
				for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}else {
						
						// printf("0 �̹Ƿ� imsi_count ����\n");
						imsi_count++;
					}
				}
				// printf("��Ȳ�� �ҸӴϰ� ����ش�");
				char sendmsg5[5];
				sendmsg5[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
				sendmsg5[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
				sendmsg5[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
				sendmsg5[3]=( mid2[imsi].thread & 0x000000ff ) ;;
				sendmsg5[4]=11;
				len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� ���� ����Ʈ����� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				len = Xc->Enc_Pack(imsi,"\x03\00\x2a��Ȳ�ҸӴϲ��� ��Ȱ�� �ܿ��ּ̽��ϴ�.",36,0x0a,1);
				retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
				mid2[imsi].sangtae=0;
				mid2[imsi].hel=2;
				exp_money(imsi,imsi);
				char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
				int sendmsg_byte=loginchr(imsi,sendmsg2);
				
				len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
				for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
				{
					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
					{
						// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
						retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					}
					else imsi_count++;
				}
				
				
			}
			
			
			
		}
	}
	if(mid2[imsi].realmap==29)
	{
		if(strcmp(msg,"�� �Ĵ�")==0 || strcmp(msg,"���Ĵ�")==0 ||
			strcmp(msg,"�� �Ĵ�?")==0 || strcmp(msg,"���Ĵ�?")==0
			|| strcmp(msg,"���Ⱦ�?")==0 || strcmp(msg,"���Ⱦ�")==0
			|| strcmp(msg,"�� �Ⱦ�?")==0 || strcmp(msg,"�� �Ⱦ�")==0)
		{
			
			
			char sendmsg[100];
			// printf("���ϱ� ��Ŷ�� �޾ҽ��ϴ�. imsi=%d\n",imsi);
			
			sendmsg[0] = '\x00';
			sendmsg[1] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0xff000000 ) >> 24;
			sendmsg[2] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x00ff0000) >> 16;
			sendmsg[3] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x0000ff00) >> 8;
			sendmsg[4] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x000000ff) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,"��ȥ��",6);
			sendmsg[6+6] = '\x3a';
			sendmsg[7+6] = '\x20';
			memcpy(sendmsg+6+8,"���� ü��,������ ��帰��ϴ�.",80);
			
			
			len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
			// printf("imsi = %d \n",imsi);
			
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			char cheimsi[70];
			int cheimsi2;
			len = Xc->Enc_Pack(imsi,"\x03\x00\x1a��ɾ�:ü�� ���,�ٻ��",30,0x0a,1);
			retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
			
			cheimsi2=sprintf(cheimsi,"����ġ %d = ü�� %d",setting_st.exp,setting_st.heal);
			sangtae(imsi,cheimsi);
			len = Xc->Enc_Pack(imsi,cheimsi,cheimsi2,0x0a,1);
			//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
			cheimsi2=sprintf(cheimsi,"����ġ %d = ���� %d",setting_st.exp_mana,setting_st.mana);
			sangtae(imsi,cheimsi);
			len = Xc->Enc_Pack(imsi,cheimsi,cheimsi2,0x0a,1);
			//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0); 
		}
		if(strcmp(msg,"ü����")==0 || strcmp(msg,"ü�� ��")==0 ||
			strcmp(msg,"ü�»��")==0 || strcmp(msg,"ü�� ���")==0
			)
		{
			char sendmsg[100];
			memset(sendmsg,0,100);
			/*sendmsg[0] = '\x00';
			sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
			sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
			sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
			memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
			if(mid2[imsi].exp>=setting_st.exp)
			{
				sprintf(sendmsg,"%c%c%cü���� %u �ö����ϴ�.",'\x03','\x01','\x01',setting_st.heal);
				
				int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
				int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
				mid2[imsi].exp=mid2[imsi].exp-setting_st.exp;
				mid2[imsi].max_hel=mid2[imsi].max_hel+setting_st.heal;
				exp_money(imsi,imsi);
				
			}
			else
			{
				sprintf(sendmsg,"%c%c%c����ġ�� ���ڸ��ϴ�.",'\x03','\x01','\x01');
				
				int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
				int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			}
			
		}
		
		if(strcmp(msg,"������")==0 || strcmp(msg,"���� ��")==0 ||
			strcmp(msg,"���»��")==0 || strcmp(msg,"���� ���")==0
			)
		{
			
			char sendmsg[100];
			memset(sendmsg,0,100);
			/*sendmsg[0] = '\x00';
			sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
			sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
			sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
			memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
			if(mid2[imsi].exp>=setting_st.exp_mana)
			{
				sprintf(sendmsg,"%c%c%c������ %u �ö����ϴ�.",'\x03','\x01','\x01',setting_st.mana);
				
				int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
				int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
				mid2[imsi].exp=mid2[imsi].exp-setting_st.exp_mana;			mid2[imsi].max_mana=mid2[imsi].max_mana+setting_st.mana;
				
				exp_money(imsi,imsi);
				
			}
			else
			{
				sprintf(sendmsg,"%c%c%c����ġ�� ���ڸ��ϴ�.",'\x03','\x01','\x01');
				
				int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
				int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			}
			
			
		}
		if(strcmp(msg,"ü�� �� ��")==0 || strcmp(msg,"ü�� ����")==0 ||
			strcmp(msg,"ü�� �� ���")==0 || strcmp(msg,"ü�� �ٻ��")==0 ||
			strcmp(msg,"ü�� ��� ���")==0 || strcmp(msg,"ü�� ��� ��")==0
			)
		{
			char sendmsg[100];
			memset(sendmsg,0,100);
			/*sendmsg[0] = '\x00';
			sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
			sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
			sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
			memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
			if(mid2[imsi].exp>=setting_st.exp)
			{
				int hel_up=mid2[imsi].exp/setting_st.exp;
				sprintf(sendmsg,"%c%c%cü���� %u �ö����ϴ�.",'\x03','\x01','\x01',hel_up*setting_st.heal);
				
				int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
				int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
				mid2[imsi].exp=mid2[imsi].exp%setting_st.exp;
				mid2[imsi].max_hel=mid2[imsi].max_hel+hel_up*setting_st.heal;
				exp_money(imsi,imsi);
				
			}
			else
			{
				sprintf(sendmsg,"%c%c%c����ġ�� ���ڸ��ϴ�.",'\x03','\x01','\x01');
				
				int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
				int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			}
		}
		if(strcmp(msg,"���� �� ��")==0 || strcmp(msg,"���� ����")==0 ||
			strcmp(msg,"���� �� ���")==0 || strcmp(msg,"���� �ٻ��")==0 ||
			strcmp(msg,"���� ��� ��")==0 || strcmp(msg,"���� ��� ���")==0
			)
		{
			
			char sendmsg[100];
			memset(sendmsg,0,100);
			/*sendmsg[0] = '\x00';
			sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
			sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
			sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
			memcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2,80);*/
			if(mid2[imsi].exp>=setting_st.exp_mana)
			{
				int mana_up=mid2[imsi].exp/setting_st.exp_mana;
				sprintf(sendmsg,"%c%c%c������ %u �ö����ϴ�.",'\x03','\x01','\x01',mana_up*setting_st.mana);
				
				int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
				int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
				mid2[imsi].exp=mid2[imsi].exp%setting_st.exp_mana;
				mid2[imsi].max_mana=mid2[imsi].max_mana+mana_up*setting_st.mana;
				exp_money(imsi,imsi);
				
			}
			else
			{
				sprintf(sendmsg,"%c%c%c����ġ�� ���ڸ��ϴ�.",'\x03','\x01','\x01');
				
				int len = Xc->Enc_Pack(imsi,sendmsg,80,0x0a,1);
				int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
			}
		}
	}
	if(mid2[imsi].realmap==48)
	{
		if(strcmp(msg,"�� �Ĵ�")==0 || strcmp(msg,"���Ĵ�")==0 ||
			strcmp(msg,"�� �Ĵ�?")==0 || strcmp(msg,"���Ĵ�?")==0
			|| strcmp(msg,"���Ⱦ�?")==0 || strcmp(msg,"���Ⱦ�")==0
			|| strcmp(msg,"�� �Ⱦ�?")==0 || strcmp(msg,"�� �Ⱦ�")==0)
		{
			
			
			char sendmsg[100];
			// printf("���ϱ� ��Ŷ�� �޾ҽ��ϴ�. imsi=%d\n",imsi);
			
			sendmsg[0] = '\x00';
			sendmsg[1] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0xff000000 ) >> 24;
			sendmsg[2] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x00ff0000) >> 16;
			sendmsg[3] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x0000ff00) >> 8;
			sendmsg[4] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x000000ff) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,"����GM",6);
			sendmsg[6+6] = '\x3a';
			sendmsg[7+6] = '\x20';
			memcpy(sendmsg+6+8,"���� ������ ������ ������ �帳�ϴ�.",80);
			
			
			len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
			// printf("imsi = %d \n",imsi);
			
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			char cheimsi[100];
			int cheimsi2;
			sangtae(imsi,"=== ��ɾ� ��� === ");
			sangtae(imsi,"x ������ ���� �ͽ��ϴ�.");
			sangtae(imsi,"x�� �±��� �ϰ� �ͽ��ϴ�.");
			sangtae(imsi,"=== �±�   ��� === ");
			sangtae(imsi,"--------------------");
			for(int i=0;i<255;i++)
			{
				if(junsas2[i].number!=0)
				{
					sprintf(cheimsi,"%d�� �±�(%s): ����%d��",junsas2[i].number,junsas2[i].ching_ho,junsas2[i].need_level);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"��ġ�� ������:%s",junsas2[i].need_item);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"�ϻ��ϴ� ������:%s",junsas2[i].hasa_item);
					sangtae(imsi,cheimsi);
					sangtae(imsi,"--------------------");
				}
			}
			sangtae(imsi,"=== ����   ��� === ");
			sangtae(imsi,"--------------------");
			for(i=0;i<255;i++)
			{
				if(junsas[i].level!=0)
				{
					sprintf(cheimsi,"�����̸�:%s",junsas[i].magic_name);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"�ʿ䷹��:%d",junsas[i].level);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"��ġ�� ������:%s",junsas[i].magic_need_item);
					sangtae(imsi,cheimsi);
					sangtae(imsi,"--------------------");
				}
			}
			return 0;
		}
		for(int j=0;j<255;j++)
		{
			char buffer23[100];
			sprintf(buffer23,"%s ������ ���� �ͽ��ϴ�",junsas[j].magic_name);
			char buffer24[100];
			sprintf(buffer24,"%s ������ ���� �ͽ��ϴ�.",junsas[j].magic_name);
			
			if(strcmp(msg,buffer23)==0 || strcmp(msg,buffer24)==0)
			{
				if(junsas[j].level>mid2[imsi].level)
				{
					sangtae(imsi,"������ �����մϴ�.");
					return 0;
				}
				for(int magic_count=0;magic_count<26;magic_count++)
				{
					if(mid2[imsi].magic[magic_count]==junsas[j].magic_number)
					{
						sangtae(imsi,"�̹� �ִ� ���� �Դϴ�.");
						return 0;
					}
				}
				
				if(strcmp(mid2[imsi].job,"���")==0)
				{
					sangtae(imsi,"����� ����� ���մϴ�.");
					return 0;
				}
				for(int k=0;k<255;k++) // �������� �ٸ��� ����
				{
					if(strcmp(junsas2[k].ching_ho,mid2[imsi].job)==0)
						kkflag=1;
				}
				if(kkflag!=1) 
				{
					sangtae(imsi,"���� ���ݻ� ���� �����ϴ�.");
					return 0;
				}
				for(int item_count=0,int s_flag=0;item_count<26;item_count++)
				{
					
					if(mid2[imsi].item[item_count][0]==junsas[j].number_need_item+49151)
					{
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
						s_flag=1;
					}
					
				}
				if(s_flag!=1) 
				{
					sangtae(imsi,"�繰�� ������ ���ʽÿ�.");
					return 0;
				}
				for(magic_count=0;magic_count<26;magic_count++)
				{
					if(mid2[imsi].magic[magic_count]==0)
					{
						mid2[imsi].magic[magic_count]=junsas[j].magic_number;
						magic_count=26;
					}
				}
				sangtae(imsi,"���ο� ������ ������ϴ�!!");
				for(int i=0;i<52;i++)  // ���� ��Ͽ� �߰� �ϱ�
				{
					if(mid2[imsi].magic[i]!=0)
					{
						// printf("%d\n",i);
						char sendmagic[50];
						magic_name(sendmagic,mid2[imsi].magic[i],i+1);
						// printf("%d\n",mid2[imsi].magic[i]);
						len = Xc->Enc_Pack(imsi,sendmagic,strlen(sendmagic),0x17,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
						packet_dump(sendmagic,20,16);
					}
				}
				
				return 0;
				
				
				
				
				
				
			}
			
			
			
			
			
			
			
			
			
		}
		for(j=0;j<255;j++)
		{
			char buffer13[100];
			sprintf(buffer13,"%d�� �±��� �ϰ� �ͽ��ϴ�",junsas2[j].number);
			
			char buffer14[100];
			sprintf(buffer14,"%d�� �±��� �ϰ� �ͽ��ϴ�.",junsas2[j].number);
			
			if(junsas2[j].number==0) return 0;
			
			if(strcmp(msg,buffer13)==0 || strcmp(msg,buffer14)==0)
			{
				if(junsas2[j].need_level>mid2[imsi].level)
				{
					sangtae(imsi,"������ �����մϴ�.");
					return 0;
				}
				if(strcmp(mid2[imsi].job,"���")!=0)
				{
					if(strcmp(junsas2[j-1].ching_ho,mid2[imsi].job)!=0)
					{
						sangtae(imsi,"�Ұ��� �մϴ�.");
						return 0;
					}
				}
				for(int item_count=0,int s_flag=0;item_count<26;item_count++)
				{
					
					if(mid2[imsi].item[item_count][0]==junsas2[j].need_item_number+49151)
					{
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
						s_flag=1;
					}
					
				}
				if(s_flag!=1) 
				{
					sangtae(imsi,"�繰�� ������ ���ʽÿ�.");
					
					return 0;
				}
				
				
				sangtae(imsi,"�±��� ���ϵ帳�ϴ�~.");
				mid2[imsi].s_number=junsas2[j].number;
				char sendmsg[100];	memset(sendmsg,0,100);
				
				sprintf(sendmsg,"%c%c%c>> %s�Բ��� %s(��)��  �±��ϼ̽��ϴ�.",0x05,0x00,0x3a,mid2[imsi].id,junsas2[j].ching_ho);
				int len = Xc->Enc_Pack(imsi,sendmsg,strlen(sendmsg+4)+4,0x0a,1);
				
				for(int k=0;k<frecnum;k++)
				{
					if(mid2[k].thread != 0)
					{
						
						
						int retval = send(client[mid2[k].thread],Encrypted_Messages[imsi],len, 0);
					}
					
				}
				
				strcpy(mid2[imsi].job,junsas2[j].ching_ho);
				int imsiflag=0;
				for(int i=0;i<26;i++) 
				{
					
					if(mid2[imsi].item[i][0]==junsas2[j].hasa_item_number+49151) // �̹� �ִ� �������� ���
					{
						// printf("name: %s\n",item_st[j].name);
						// printf("number : %d\n",j);
						// printf("�̹� �ִ� ������\n");
						mid2[imsi].item[i][1]++;
						char item2[100];
						sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
							i+1,(junsas2[j].hasa_item_number+49151 & 0x0000ff00)  >> 8
							,(junsas2[j].hasa_item_number+49151 & 0x000000ff) ,0x00,0x20,item_st[junsas2[j].hasa_item_number].name
							,mid2[imsi].item[i][1],0x00,0x00,0x00);
						
						len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
						
						imsiflag=1;
						
						
						
						
						i = 26;
					}
				}
				if(imsiflag!=1)
				{
					for(int i=0;i<26;i++) 
					{
						if(mid2[imsi].item[i][0]==0) // ���ο� �������� ���
						{
							// printf("name: %s\n",item_st[j].name);
							// printf("number : %d\n",j);
							// printf("�� ������\n");
							mid2[imsi].item[i][0]=junsas2[j].hasa_item_number+49151;
							mid2[imsi].item[i][1]++;
							char item2[100];
							sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
								i+1,(junsas2[j].hasa_item_number+49151 & 0x0000ff00)  >> 8
								,(junsas2[j].hasa_item_number+49151 & 0x000000ff) ,0x00,0x20,item_st[junsas2[j].hasa_item_number].name
								,mid2[imsi].item[i][1],0x00,0x00,0x00);
							
							len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
							retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
							
							i = 26;
						}
						
						
					}
				}
				
				
				
				return 0;
				
		}
		}
		
	}
	if(mid2[imsi].realmap==49)
	{
		if(strcmp(msg,"�� �Ĵ�")==0 || strcmp(msg,"���Ĵ�")==0 ||
			strcmp(msg,"�� �Ĵ�?")==0 || strcmp(msg,"���Ĵ�?")==0
			|| strcmp(msg,"���Ⱦ�?")==0 || strcmp(msg,"���Ⱦ�")==0
			|| strcmp(msg,"�� �Ⱦ�?")==0 || strcmp(msg,"�� �Ⱦ�")==0)
		{
			
			
			char sendmsg[100];
			// printf("���ϱ� ��Ŷ�� �޾ҽ��ϴ�. imsi=%d\n",imsi);
			
			sendmsg[0] = '\x00';
			sendmsg[1] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0xff000000 ) >> 24;
			sendmsg[2] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x00ff0000) >> 16;
			sendmsg[3] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x0000ff00) >> 8;
			sendmsg[4] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x000000ff) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,"����GM",6);
			sendmsg[6+6] = '\x3a';
			sendmsg[7+6] = '\x20';
			memcpy(sendmsg+6+8,"���� ������� ������ ������ �帳�ϴ�.",80);
			
			
			len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
			// printf("imsi = %d \n",imsi);
			
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			char cheimsi[100];
			int cheimsi2;
			sangtae(imsi,"=== ��ɾ� ��� === ");
			sangtae(imsi,"x ������ ���� �ͽ��ϴ�.");
			sangtae(imsi,"x�� �±��� �ϰ� �ͽ��ϴ�.");
			sangtae(imsi,"=== �±�   ��� === ");
			sangtae(imsi,"--------------------");
			for(int i=0;i<255;i++)
			{
				if(dojuks2[i].number!=0)
				{
					sprintf(cheimsi,"%d�� �±�(%s): ����%d��",dojuks2[i].number,dojuks2[i].ching_ho,dojuks2[i].need_level);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"��ġ�� ������:%s",dojuks2[i].need_item);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"�ϻ��ϴ� ������:%s",dojuks2[i].hasa_item);
					sangtae(imsi,cheimsi);
					sangtae(imsi,"--------------------");
				}
			}
			sangtae(imsi,"=== ����   ��� === ");
			sangtae(imsi,"--------------------");
			for(i=0;i<255;i++)
			{
				if(dojuks[i].level!=0)
				{
					sprintf(cheimsi,"�����̸�:%s",dojuks[i].magic_name);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"�ʿ䷹��:%d",dojuks[i].level);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"��ġ�� ������:%s",dojuks[i].magic_need_item);
					sangtae(imsi,cheimsi);
					sangtae(imsi,"--------------------");
				}
			}
			return 0;
		}
		for(int j=0;j<255;j++)
		{
			char buffer23[100];
			sprintf(buffer23,"%s ������ ���� �ͽ��ϴ�",dojuks[j].magic_name);
			char buffer24[100];
			sprintf(buffer24,"%s ������ ���� �ͽ��ϴ�.",dojuks[j].magic_name);
			
			if(strcmp(msg,buffer23)==0 || strcmp(msg,buffer24)==0)
			{
				if(dojuks[j].level>mid2[imsi].level)
				{
					sangtae(imsi,"������ �����մϴ�.");
					return 0;
				}
				for(int magic_count=0;magic_count<26;magic_count++)
				{
					if(mid2[imsi].magic[magic_count]==dojuks[j].magic_number)
					{
						sangtae(imsi,"�̹� �ִ� ���� �Դϴ�.");
						return 0;
					}
				}
				if(strcmp(mid2[imsi].job,"���")==0)
				{
					sangtae(imsi,"����� ����� ���մϴ�.");
					
					return 0;
				}
				for(int k=0;k<255;k++) // �������� �ٸ��� ����
				{
					if(strcmp(dojuks2[k].ching_ho,mid2[imsi].job)==0)
						kkflag=1;
				}
				if(kkflag!=1) 
				{
					sangtae(imsi,"���� ���ݻ� ���� �����ϴ�.");
					return 0;
				}
				for(int item_count=0,int s_flag=0;item_count<26;item_count++)
				{
					
					if(mid2[imsi].item[item_count][0]==dojuks[j].number_need_item+49151)
					{
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
						s_flag=1;
					}
					
				}
				if(s_flag!=1) 
				{
					sangtae(imsi,"�繰�� ������ ���ʽÿ�.");
					return 0;
					
				}
				for(magic_count=0;magic_count<26;magic_count++)
				{
					if(mid2[imsi].magic[magic_count]==0)
					{
						mid2[imsi].magic[magic_count]=dojuks[j].magic_number;
						magic_count=26;
					}
				}
				sangtae(imsi,"���ο� ������ ������ϴ�!!");
				for(int i=0;i<52;i++)  // ���� ��Ͽ� �߰� �ϱ�
				{
					if(mid2[imsi].magic[i]!=0)
					{
						// printf("%d\n",i);
						char sendmagic[50];
						magic_name(sendmagic,mid2[imsi].magic[i],i+1);
						// printf("%d\n",mid2[imsi].magic[i]);
						len = Xc->Enc_Pack(imsi,sendmagic,strlen(sendmagic),0x17,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
						packet_dump(sendmagic,20,16);
					}
				}
				
				return 0;
				
				
				
				
				
				
			}
			
			
			
			
			
			
			
			
			
		}
		for(j=0;j<255;j++)
		{
			char buffer13[100];
			sprintf(buffer13,"%d�� �±��� �ϰ� �ͽ��ϴ�",dojuks2[j].number);
			char buffer14[100];
			sprintf(buffer14,"%d�� �±��� �ϰ� �ͽ��ϴ�.",dojuks2[j].number);
			if(dojuks2[j].number==0) return 0;
			
			if(strcmp(msg,buffer13)==0 || strcmp(msg,buffer14)==0)
			{
				if(dojuks2[j].need_level>mid2[imsi].level)
				{
					sangtae(imsi,"������ �����մϴ�.");
					return 0;
				}
				if(strcmp(mid2[imsi].job,"���")!=0)
				{
					if(strcmp(dojuks2[j-1].ching_ho,mid2[imsi].job)!=0)
					{
						sangtae(imsi,"�Ұ��� �մϴ�.");
						return 0;
					}
				}
				for(int item_count=0,int s_flag=0;item_count<26;item_count++)
				{
					
					if(mid2[imsi].item[item_count][0]==dojuks2[j].need_item_number+49151)
					{
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
						s_flag=1;
					}
					
				}
				if(s_flag!=1) 
				{
					sangtae(imsi,"�繰�� ������ ���ʽÿ�.");
					return 0;
				}
				
				
				sangtae(imsi,"�±��� ���ϵ帳�ϴ�~.");
				mid2[imsi].s_number=dojuks2[j].number;
				char sendmsg[100];	memset(sendmsg,0,100);
				
				sprintf(sendmsg,"%c%c%c>> %s�Բ��� %s(��)��  �±��ϼ̽��ϴ�.",0x05,0x00,0x3a,mid2[imsi].id,dojuks2[j].ching_ho);
				int len = Xc->Enc_Pack(imsi,sendmsg,strlen(sendmsg+4)+4,0x0a,1);
				
				for(int k=0;k<frecnum;k++)
				{
					if(mid2[k].thread != 0)
					{
						
						
						int retval = send(client[mid2[k].thread],Encrypted_Messages[imsi],len, 0);
					}
					
				}
				
				strcpy(mid2[imsi].job,dojuks2[j].ching_ho);
				int imsiflag=0;
				for(int i=0;i<26;i++) 
				{
					
					if(mid2[imsi].item[i][0]==dojuks2[j].hasa_item_number+49151) // �̹� �ִ� �������� ���
					{
						// printf("name: %s\n",item_st[j].name);
						// printf("number : %d\n",j);
						// printf("�̹� �ִ� ������\n");
						mid2[imsi].item[i][1]++;
						char item2[100];
						sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
							i+1,(dojuks2[j].hasa_item_number+49151 & 0x0000ff00)  >> 8
							,(dojuks2[j].hasa_item_number+49151 & 0x000000ff) ,0x00,0x20,item_st[dojuks2[j].hasa_item_number].name
							,mid2[imsi].item[i][1],0x00,0x00,0x00);
						
						len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
						
						imsiflag=1;
						
						
						
						
						i = 26;
					}
				}
				if(imsiflag!=1)
				{
					for(int i=0;i<26;i++) 
					{
						if(mid2[imsi].item[i][0]==0) // ���ο� �������� ���
						{
							// printf("name: %s\n",item_st[j].name);
							// printf("number : %d\n",j);
							// printf("�� ������\n");
							mid2[imsi].item[i][0]=dojuks2[j].hasa_item_number+49151;
							mid2[imsi].item[i][1]++;
							char item2[100];
							sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
								i+1,(dojuks2[j].hasa_item_number+49151 & 0x0000ff00)  >> 8
								,(dojuks2[j].hasa_item_number+49151 & 0x000000ff) ,0x00,0x20,item_st[dojuks2[j].hasa_item_number].name
								,mid2[imsi].item[i][1],0x00,0x00,0x00);
							
							len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
							retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
							
							i = 26;
						}
						
						
					}
				}
				
				
				
				return 0;
				
		}
		}
		
	}
	if(mid2[imsi].realmap==51)
	{
		if(strcmp(msg,"�� �Ĵ�")==0 || strcmp(msg,"���Ĵ�")==0 ||
			strcmp(msg,"�� �Ĵ�?")==0 || strcmp(msg,"���Ĵ�?")==0
			|| strcmp(msg,"���Ⱦ�?")==0 || strcmp(msg,"���Ⱦ�")==0
			|| strcmp(msg,"�� �Ⱦ�?")==0 || strcmp(msg,"�� �Ⱦ�")==0)
		{
			
			
			char sendmsg[100];
			// printf("���ϱ� ��Ŷ�� �޾ҽ��ϴ�. imsi=%d\n",imsi);
			
			sendmsg[0] = '\x00';
			sendmsg[1] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0xff000000 ) >> 24;
			sendmsg[2] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x00ff0000) >> 16;
			sendmsg[3] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x0000ff00) >> 8;
			sendmsg[4] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x000000ff) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,"����GM",6);
			sendmsg[6+6] = '\x3a';
			sendmsg[7+6] = '\x20';
			memcpy(sendmsg+6+8,"���� ������ ������ ������ �帳�ϴ�.",80);
			
			
			len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
			// printf("imsi = %d \n",imsi);
			
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			char cheimsi[100];
			int cheimsi2;
			sangtae(imsi,"=== ��ɾ� ��� === ");
			sangtae(imsi,"x ������ ���� �ͽ��ϴ�.");
			sangtae(imsi,"x�� �±��� �ϰ� �ͽ��ϴ�.");
			sangtae(imsi,"=== �±�   ��� === ");
			sangtae(imsi,"--------------------");
			for(int i=0;i<255;i++)
			{
				if(soolsas2[i].number!=0)
				{
					sprintf(cheimsi,"%d�� �±�(%s): ����%d��",soolsas2[i].number,soolsas2[i].ching_ho,soolsas2[i].need_level);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"��ġ�� ������:%s",soolsas2[i].need_item);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"�ϻ��ϴ� ������:%s",soolsas2[i].hasa_item);
					sangtae(imsi,cheimsi);
					sangtae(imsi,"--------------------");
				}
			}
			sangtae(imsi,"=== ����   ��� === ");
			sangtae(imsi,"--------------------");
			for(i=0;i<255;i++)
			{
				if(soolsas[i].level!=0)
				{
					sprintf(cheimsi,"�����̸�:%s",soolsas[i].magic_name);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"�ʿ䷹��:%d",soolsas[i].level);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"��ġ�� ������:%s",soolsas[i].magic_need_item);
					sangtae(imsi,cheimsi);
					sangtae(imsi,"--------------------");
				}
			}
			return 0;
		}
		for(int j=0;j<255;j++)
		{
			char buffer23[100];
			sprintf(buffer23,"%s ������ ���� �ͽ��ϴ�",soolsas[j].magic_name);
			char buffer24[100];
			sprintf(buffer24,"%s ������ ���� �ͽ��ϴ�.",soolsas[j].magic_name);
			
			if(strcmp(msg,buffer23)==0 || strcmp(msg,buffer24)==0)
			{
				if(soolsas[j].level>mid2[imsi].level)
				{
					sangtae(imsi,"������ �����մϴ�.");
					return 0;
				}
				for(int magic_count=0;magic_count<26;magic_count++)
				{
					if(mid2[imsi].magic[magic_count]==soolsas[j].magic_number)
					{
						sangtae(imsi,"�̹� �ִ� ���� �Դϴ�.");
						return 0;
					}
				}
				if(strcmp(mid2[imsi].job,"���")==0)
				{
					sangtae(imsi,"����� ����� ���մϴ�.");
					return 0;
				}
				for(int k=0;k<255;k++) // �������� �ٸ��� ����
				{
					if(strcmp(soolsas2[k].ching_ho,mid2[imsi].job)==0)
						kkflag=1;
				}
				if(kkflag!=1) 
				{
					sangtae(imsi,"���� ���ݻ� ���� �����ϴ�.");
					return 0;
				}
				for(int item_count=0,int s_flag=0;item_count<26;item_count++)
				{
					
					if(mid2[imsi].item[item_count][0]==soolsas[j].number_need_item+49151)
					{
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
						s_flag=1;
					}
					
				}
				if(s_flag!=1) 
				{
					sangtae(imsi,"�繰�� ������ ���ʽÿ�.");
					return 0;
				}
				for(magic_count=0;magic_count<26;magic_count++)
				{
					if(mid2[imsi].magic[magic_count]==0)
					{
						mid2[imsi].magic[magic_count]=soolsas[j].magic_number;
						magic_count=26;
					}
				}
				sangtae(imsi,"���ο� ������ ������ϴ�!!");
				for(int i=0;i<52;i++)  // ���� ��Ͽ� �߰� �ϱ�
				{
					if(mid2[imsi].magic[i]!=0)
					{
						// printf("%d\n",i);
						char sendmagic[50];
						magic_name(sendmagic,mid2[imsi].magic[i],i+1);
						// printf("%d\n",mid2[imsi].magic[i]);
						len = Xc->Enc_Pack(imsi,sendmagic,strlen(sendmagic),0x17,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
						packet_dump(sendmagic,20,16);
					}
				}
				
				return 0;
				
				
				
				
				
				
			}
			
			
			
			
			
			
			
			
			
		}
		for(j=0;j<255;j++)
		{
			char buffer13[100];
			sprintf(buffer13,"%d�� �±��� �ϰ� �ͽ��ϴ�",soolsas2[j].number);
			char buffer14[100];
			sprintf(buffer14,"%d�� �±��� �ϰ� �ͽ��ϴ�.",soolsas2[j].number);
			if(soolsas2[j].number==0) return 0;
			
			if(strcmp(msg,buffer13)==0 || strcmp(msg,buffer14)==0)
			{
				if(soolsas2[j].need_level>mid2[imsi].level)
				{
					sangtae(imsi,"������ �����մϴ�.");
					
					return 0;
				}
				if(strcmp(mid2[imsi].job,"���")!=0)
				{
					if(strcmp(soolsas2[j-1].ching_ho,mid2[imsi].job)!=0)
					{
						sangtae(imsi,"�Ұ��� �մϴ�.");
						return 0;
					}
				}
				for(int item_count=0,int s_flag=0;item_count<26;item_count++)
				{
					
					if(mid2[imsi].item[item_count][0]==soolsas2[j].need_item_number+49151)
					{
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
						s_flag=1;
					}
					
				}
				if(s_flag!=1) 
				{
					sangtae(imsi,"�繰�� ������ ���ʽÿ�.");
					return 0;
				}
				
				
				sangtae(imsi,"�±��� ���ϵ帳�ϴ�~.");
				mid2[imsi].s_number=soolsas2[j].number;
				char sendmsg[100];	memset(sendmsg,0,100);
				
				sprintf(sendmsg,"%c%c%c>> %s�Բ��� %s(��)��  �±��ϼ̽��ϴ�.",0x05,0x00,0x3a,mid2[imsi].id,soolsas2[j].ching_ho);
				int len = Xc->Enc_Pack(imsi,sendmsg,strlen(sendmsg+4)+4,0x0a,1);
				
				for(int k=0;k<frecnum;k++)
				{
					if(mid2[k].thread != 0)
					{
						
						
						int retval = send(client[mid2[k].thread],Encrypted_Messages[imsi],len, 0);
					}
					
				}
				
				strcpy(mid2[imsi].job,soolsas2[j].ching_ho);
				int imsiflag=0;
				for(int i=0;i<26;i++) 
				{
					
					if(mid2[imsi].item[i][0]==soolsas2[j].hasa_item_number+49151) // �̹� �ִ� �������� ���
					{
						// printf("name: %s\n",item_st[j].name);
						// printf("number : %d\n",j);
						// printf("�̹� �ִ� ������\n");
						mid2[imsi].item[i][1]++;
						char item2[100];
						sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
							i+1,(soolsas2[j].hasa_item_number+49151 & 0x0000ff00)  >> 8
							,(soolsas2[j].hasa_item_number+49151 & 0x000000ff) ,0x00,0x20,item_st[soolsas2[j].hasa_item_number].name
							,mid2[imsi].item[i][1],0x00,0x00,0x00);
						
						len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
						
						imsiflag=1;
						
						
						
						
						i = 26;
					}
				}
				if(imsiflag!=1)
				{
					for(int i=0;i<26;i++) 
					{
						if(mid2[imsi].item[i][0]==0) // ���ο� �������� ���
						{
							// printf("name: %s\n",item_st[j].name);
							// printf("number : %d\n",j);
							// printf("�� ������\n");
							mid2[imsi].item[i][0]=soolsas2[j].hasa_item_number+49151;
							mid2[imsi].item[i][1]++;
							char item2[100];
							sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
								i+1,(soolsas2[j].hasa_item_number+49151 & 0x0000ff00)  >> 8
								,(soolsas2[j].hasa_item_number+49151 & 0x000000ff) ,0x00,0x20,item_st[soolsas2[j].hasa_item_number].name
								,mid2[imsi].item[i][1],0x00,0x00,0x00);
							
							len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
							retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
							
							i = 26;
						}
						
						
					}
				}
				
				
				
				return 0;
				
		}
		}
		
	}
	if(mid2[imsi].realmap==50)
	{
		if(strcmp(msg,"�� �Ĵ�")==0 || strcmp(msg,"���Ĵ�")==0 ||
			strcmp(msg,"�� �Ĵ�?")==0 || strcmp(msg,"���Ĵ�?")==0
			|| strcmp(msg,"���Ⱦ�?")==0 || strcmp(msg,"���Ⱦ�")==0
			|| strcmp(msg,"�� �Ⱦ�?")==0 || strcmp(msg,"�� �Ⱦ�")==0)
		{
			
			
			char sendmsg[100];
			// printf("���ϱ� ��Ŷ�� �޾ҽ��ϴ�. imsi=%d\n",imsi);
			
			sendmsg[0] = '\x00';
			sendmsg[1] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0xff000000 ) >> 24;
			sendmsg[2] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x00ff0000) >> 16;
			sendmsg[3] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x0000ff00) >> 8;
			sendmsg[4] = ( taijimap[mid2[imsi].realmap].monster_thread[0] & 0x000000ff) ;
			sendmsg[5] = '\x52';
			memcpy(sendmsg+6,"����GM",6);
			sendmsg[6+6] = '\x3a';
			sendmsg[7+6] = '\x20';
			memcpy(sendmsg+6+8,"���� ������ ������ ������ �帳�ϴ�.",80);
			
			
			len = Xc->Enc_Pack(imsi,sendmsg,80,0x0d,1);
			// printf("imsi = %d \n",imsi);
			
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			char cheimsi[100];
			int cheimsi2;
			sangtae(imsi,"=== ��ɾ� ��� === ");
			sangtae(imsi,"x ������ ���� �ͽ��ϴ�.");
			sangtae(imsi,"x�� �±��� �ϰ� �ͽ��ϴ�.");
			sangtae(imsi,"=== �±�   ��� === ");
			sangtae(imsi,"--------------------");
			for(int i=0;i<255;i++)
			{
				if(dosas2[i].number!=0)
				{
					sprintf(cheimsi,"%d�� �±�(%s): ����%d��",dosas2[i].number,dosas2[i].ching_ho,dosas2[i].need_level);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"��ġ�� ������:%s",dosas2[i].need_item);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"�ϻ��ϴ� ������:%s",dosas2[i].hasa_item);
					sangtae(imsi,cheimsi);
					sangtae(imsi,"--------------------");
				}
			}
			sangtae(imsi,"=== ����   ��� === ");
			sangtae(imsi,"--------------------");
			for(i=0;i<255;i++)
			{
				if(dosas[i].level!=0)
				{
					sprintf(cheimsi,"�����̸�:%s",dosas[i].magic_name);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"�ʿ䷹��:%d",dosas[i].level);
					sangtae(imsi,cheimsi);
					sprintf(cheimsi,"��ġ�� ������:%s",dosas[i].magic_need_item);
					sangtae(imsi,cheimsi);
					sangtae(imsi,"--------------------");
				}
			}
			return 0;
		}
		for(int j=0;j<255;j++)
		{
			char buffer23[100];
			sprintf(buffer23,"%s ������ ���� �ͽ��ϴ�",dosas[j].magic_name);
			char buffer24[100];
			sprintf(buffer24,"%s ������ ���� �ͽ��ϴ�.",dosas[j].magic_name);
			
			if(strcmp(msg,buffer23)==0 || strcmp(msg,buffer24)==0)
			{
				if(dosas[j].level>mid2[imsi].level)
				{
					sangtae(imsi,"������ �����մϴ�.");
					return 0;
				}
				for(int magic_count=0;magic_count<26;magic_count++)
				{
					if(mid2[imsi].magic[magic_count]==dosas[j].magic_number)
					{
						sangtae(imsi,"�̹� �ִ� ���� �Դϴ�.");
						return 0;
					}
				}
				if(strcmp(mid2[imsi].job,"���")==0)
				{
					sangtae(imsi,"����� ����� ���մϴ�.");
					return 0;
				}
				for(int k=0;k<255;k++) // �������� �ٸ��� ����
				{
					if(strcmp(dosas2[k].ching_ho,mid2[imsi].job)==0)
						kkflag=1;
				}
				if(kkflag!=1) 
				{
					sangtae(imsi,"���� ���ݻ� ���� �����ϴ�.");
					return 0;
				}
				for(int item_count=0,int s_flag=0;item_count<26;item_count++)
				{
					
					if(mid2[imsi].item[item_count][0]==dosas[j].number_need_item+49151)
					{
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
						s_flag=1;
					}
					
				}
				if(s_flag!=1) 
				{
					sangtae(imsi,"�繰�� ������ ���ʽÿ�.");
					return 0;
				}
				for(magic_count=0;magic_count<26;magic_count++)
				{
					if(mid2[imsi].magic[magic_count]==0)
					{
						mid2[imsi].magic[magic_count]=dosas[j].magic_number;
						magic_count=26;
					}
				}
				sangtae(imsi,"���ο� ������ ������ϴ�!!");
				
				for(int i=0;i<52;i++)  // ���� ��Ͽ� �߰� �ϱ�
				{
					if(mid2[imsi].magic[i]!=0)
					{
						// printf("%d\n",i);
						char sendmagic[50];
						magic_name(sendmagic,mid2[imsi].magic[i],i+1);
						// printf("%d\n",mid2[imsi].magic[i]);
						len = Xc->Enc_Pack(imsi,sendmagic,strlen(sendmagic),0x17,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
						packet_dump(sendmagic,20,16);
					}
				}
				
				return 0;
				
				
				
				
				
				
			}
			
			
			
			
			
			
			
			
			
		}
		for(j=0;j<255;j++)
		{
			char buffer13[100];
			sprintf(buffer13,"%d�� �±��� �ϰ� �ͽ��ϴ�",dosas2[j].number);
			char buffer14[100];
			sprintf(buffer14,"%d�� �±��� �ϰ� �ͽ��ϴ�.",dosas2[j].number);
			if(dosas2[j].number==0) return 0;
			
			if(strcmp(msg,buffer13)==0 || strcmp(msg,buffer14)==0)
			{
				if(dosas2[j].need_level>mid2[imsi].level)
				{
					sangtae(imsi,"������ �����մϴ�.");
					return 0;
				}
				if(strcmp(mid2[imsi].job,"���")!=0)
				{
					if(strcmp(dosas2[j-1].ching_ho,mid2[imsi].job)!=0)
					{
						sangtae(imsi,"�Ұ��� �մϴ�.");
						return 0;
					}
				}
				for(int item_count=0,int s_flag=0;item_count<26;item_count++)
				{
					
					if(mid2[imsi].item[item_count][0]==dosas2[j].need_item_number+49151)
					{
						
						
						char item3[5];
						item3[0]=item_count+1;
						len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						mid2[imsi].item[item_count][0]=0;
						mid2[imsi].item[item_count][1]=0;
						item_count=26;
						s_flag=1;
					}
					
				}
				if(s_flag!=1) 
				{
					sangtae(imsi,"�繰�� ������ ���ʽÿ�.");
					return 0;
				}
				
				
				sangtae(imsi,"�±��� ���ϵ帳�ϴ�~.");
				mid2[imsi].s_number=dosas2[j].number;
				char sendmsg[100];	memset(sendmsg,0,100);
				
				sprintf(sendmsg,"%c%c%c>> %s�Բ��� %s(��)��  �±��ϼ̽��ϴ�.",0x05,0x00,0x3a,mid2[imsi].id,dosas2[j].ching_ho);
				int len = Xc->Enc_Pack(imsi,sendmsg,strlen(sendmsg+4)+4,0x0a,1);
				
				for(int k=0;k<frecnum;k++)
				{
					if(mid2[k].thread != 0)
					{
						
						
						int retval = send(client[mid2[k].thread],Encrypted_Messages[imsi],len, 0);
					}
					
				}
				
				strcpy(mid2[imsi].job,dosas2[j].ching_ho);
				int imsiflag=0;
				for(int i=0;i<26;i++) 
				{
					
					if(mid2[imsi].item[i][0]==dosas2[j].hasa_item_number+49151) // �̹� �ִ� �������� ���
					{
						// printf("name: %s\n",item_st[j].name);
						// printf("number : %d\n",j);
						// printf("�̹� �ִ� ������\n");
						mid2[imsi].item[i][1]++;
						char item2[100];
						sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
							i+1,(dosas2[j].hasa_item_number+49151 & 0x0000ff00)  >> 8
							,(dosas2[j].hasa_item_number+49151 & 0x000000ff) ,0x00,0x20,item_st[dosas2[j].hasa_item_number].name
							,mid2[imsi].item[i][1],0x00,0x00,0x00);
						
						len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
						
						imsiflag=1;
						
						
						
						
						i = 26;
					}
				}
				if(imsiflag!=1)
				{
					for(int i=0;i<26;i++) 
					{
						if(mid2[imsi].item[i][0]==0) // ���ο� �������� ���
						{
							// printf("name: %s\n",item_st[j].name);
							// printf("number : %d\n",j);
							// printf("�� ������\n");
							mid2[imsi].item[i][0]=dosas2[j].hasa_item_number+49151;
							mid2[imsi].item[i][1]++;
							char item2[100];
							sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
								i+1,(dosas2[j].hasa_item_number+49151 & 0x0000ff00)  >> 8
								,(dosas2[j].hasa_item_number+49151 & 0x000000ff) ,0x00,0x20,item_st[dosas2[j].hasa_item_number].name
								,mid2[imsi].item[i][1],0x00,0x00,0x00);
							
							len = Xc->Enc_Pack(imsi,item2,4+strlen(item2+4)+3,0x0f,1);
							retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
							
							i = 26;
						}
						
						
					}
				}
				
				
				
				return 0;
				
		}
		}
		
	}
	if(mid2[imsi].realmap==26)  // Ǫ�ְ��� ��� npc
	{
		npc_all(26,imsi,msg,"Ǫ�ް�npc");
		
	}
	if(mid2[imsi].realmap==25)
	{
		npc_all(25,imsi,msg,"������npc");
		
	}
	if(mid2[imsi].realmap==24)
	{
		npc_all(24,imsi,msg,"�����npc");
		
	}
	if(mid2[imsi].realmap==23)
	{
		npc_all(23,imsi,msg,"���尣npc");
		
	}
	if(mid2[imsi].realmap==15)
	{
		npc_all(15,imsi,msg,"�ָ�npc");
		
	}
	
}
int imsi_imsi[1000];
//#server_name

DWORD WINAPI ProcessClient(LPVOID arg) //#������
{
	
	
	//printf("��������� taijimap[41].count=%d\n",taijimap[41].count);
	int add_count=0;
	
	int user_count=0;
	for(int i=0;i<frecnum;i++)
	{
								if(mid2[i].thread!=0)
								{
									
									user_count++;
								}
	}
	if(user_count>max_client)
								return 0;
	int gaesu=0;
	int kaflag;
	int new_head=0;
	int mapflag=1;	
	int testimsi=0;
	int nowcheck=0; // ���� �������� now�� Ȯ���ϱ� ���� ����üũ
	int socketnow;
	now++;
	client[now]=(SOCKET)arg;
	socketnow=now;
	int imsi;
	for(i=1;i<frecnum;i++)
	{
		if(mid2[i].thread==0 && imsi_imsi[i]!=1)
		{
			imsi=i;
			imsi_imsi[i]=1;
			i=frecnum;
		}
	}
	
	
	
	// int imsi=2549; // �κк��� imsi ���� //
	int bytecheck=0;
	// printf("%d ��° ������ ����...\n",now);
	char buf[BUFSIZE+1];
	SOCKADDR_IN clientaddr;
	int addrlen;
	int retval;
	int imsi_count;
	int test=49152;
	int last_time=0;
	char chadan_ip[20][50];
	
	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client[socketnow], (SOCKADDR *)&clientaddr, &addrlen);
	
	//printf("inet_ntoa(clientaddr.sin_addr):%s\n",inet_ntoa(clientaddr.sin_addr));
	for(int kkkk=0;kkkk<ips_count;kkkk++)
	{
		//	printf("ip_k:%d\n",kkkk);
		//	printf("ip:%s\n",ips[kkkk].ip_chadan);
		if(strcmp(inet_ntoa(clientaddr.sin_addr),ips[kkkk].ip_chadan)==0)
			return 0;
		
	}
	
	
	
	// accept()
	
	
	char peer1_0[] = {		0xaa, 0x00, 0x13, 0x7e, 0x1b, 0x43, 0x4f, 0x4e, 0x4e, 0x45, 0x43, 0x54, 0x45, 0x44, 0x20, 0x53, 0x45, 0x52, 0x56, 0x45, 0x52, 0x0a };
	// printf("�܆�Ʈ ���� \n");
	// connect server ������ ������
	retval = send(client[socketnow], peer1_0, 22, 0);
	if(retval == SOCKET_ERROR)
	{
		err_display("send()");
		
	}
	
	// Ŭ���̾�Ʈ�� ������ ���
	while(1)
	{				// ������ �ޱ�
		// printf("%d ��° ����Ʈ ���� �մϴ�.",bytecheck);
		bytecheck++;
		memset(buf,0,200);
		retval = recv(client[socketnow], buf, 200, 0);
		if(retval == SOCKET_ERROR)
		{
			err_display("recv()");
			break;
		}
		
		else if(retval == 0)
		{
			break;
		}
		
		else
		{
			
			// ��Ŷ �ޱ� ���� 
			// printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\n", retval);
			// printf("�׳� ������ \n");
			// printf("==================\n");
			packet_dump(buf,retval,16);
			// printf("==================\n");
			
			// ���� ����     //
			// if((char)buf[
			
			
			if((char)buf[3]==0x00 && bong_client==2)  // ��¥ ��Ŭ Ȯ�� �κ�
			{
				int len,retval;
				Xc->Dec_Pack(imsi,buf+2);
				if(Messages[imsi][0]!=0x6a)
				{
					closesocket(client[socketnow]);
				}
			}
			
			
			
			if((char)buf[3]==0x38) //#��Ʈ�Ѿ�
			{
				ctrl_r2(imsi);
				// printf("��Ʈ�� ���� �������ϴ�.\n");
				int len;
				char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
				
				port_check(imsi,&kaflag);
				sendmsg4[0]='\x00';
				sendmsg4[1]=(int)mid2[imsi].map_x;
				sendmsg4[2]='\x00';
				sendmsg4[3]=(int)mid2[imsi].map_y;
				sendmsg4[4]='\x00';
				sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
				sendmsg4[6]='\x00';
				sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
				
				len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
				retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
				
			}
			
			
			if((char)buf[3]==0x43 && buf[2] == 0x0c) //#f1
			{
				
				int len;
				char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
				Xc->Dec_Pack(imsi,buf+2);
				
				if((char)Messages[imsi][4]== 0xffffffff)
				{
					
					
					sendmsg4[0]='\x00';
					sendmsg4[1]=(int)mid2[imsi].map_x;
					sendmsg4[2]='\x00';
					sendmsg4[3]=(int)mid2[imsi].map_y;
					sendmsg4[4]='\x00';
					sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
					sendmsg4[6]='\x00';
					sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
					
					len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
					retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
				}
				
				if((char)Messages[imsi][4]==0xfffffffe)
				{
					int len;
					char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
					
					
					if(mid2[imsi].change_flag==1)
					{
						sangtae(imsi,"��ȯ���� On!!");
						memset(mid2[imsi].change,0,100);
						mid2[imsi].change_flag=0;
					}
					else
					{
						sangtae(imsi,"��ȯ���� Off!!");
						memset(mid2[imsi].change,0,100);
						mid2[imsi].change_flag=1;
					}
				}
				if((char)Messages[imsi][4]==0xfffffffb)
				{
					int len;
					char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
					
					
					if(mid2[imsi].change_flag==1)
					{
						sangtae(imsi,"�ӼӸ���� On!!");
						mid2[imsi].hidden_msg_flag=0;
					}
					else
					{
						sangtae(imsi,"�ӼӸ���� Off!!");
						mid2[imsi].hidden_msg_flag=1;
					}
				}
				
			}
			
			
			
			
			
			
			
			int color;
			
			if((char)buf[3]==0x6b ) //#����
			{
				int len,retval;
				//printf("���յ���\n");
				int imsi_item[100];
				memset(imsi_item,0,100);
				int johap_flag;
				int johap_flag2=0;
				int johap_flag3=0;
				Xc->Dec_Pack(imsi,buf+2);
				
				for(int k=0;k<Messages[imsi][0];k++)
				{
					
					imsi_item[k]=mid2[imsi].item[Messages[imsi][1+k]-1][0]-49151;
					//	printf("������ ��ȣ : %d\n",imsi_item[k]);
				}
				for(int iii=0;iii<100;iii++)
				{
					//	printf("%d:%d\n",iii,imsi_item[iii]);
				}
				
				
				
				//printf("%d %d \n",johap_st[1].p_item[1],johap_st[1].p_item[0]);
				
				for(int i=0;i<johap_count;i++)
				{
					if(johap_st[i].count==Messages[imsi][0])
					{
						johap_flag=0;
						for(int l2=0;l2<1000 && johap_st[i].p_item[l2]!=0;l2++)
						{
							
							for(int l=0;l<1000 && imsi_item[l]!= 0;l++)
							{
								//				printf("imsi_item[l]%d�� johap_st[i].p_item[l2] %d��\n",imsi_item[l],johap_st[i].p_item[l2]);
								if(johap_st[i].p_item[l2]==imsi_item[l])
								{
									//					printf("l : %d, l2 : %d\n",l,l2);
									//					printf("0: %d, 1: %d\n",imsi_item[0],imsi_item[1]);
									//					printf("���վ�����:%d\n",johap_st[i].p_item[l2]);
									//					printf("�ø�������:%d\n",imsi_item[l]);
									
									johap_flag++;
									//					printf("����\n");
									if(johap_flag==Messages[imsi][0])
									{
										johap_flag2=johap_flag;
										johap_flag3=i;
										
									}
								}
							}
							
						}
					}
					
				}
				//printf("johap:%d\n",johap_flag2);
				if(johap_flag2==Messages[imsi][0])
				{
					//printf("������� �Ϸ�\n");
					for(int k=0;k<Messages[imsi][0];k++)					
					{
						
						char item3[5];
						item3[1]=0;
						item3[0]=Messages[imsi][1+k]-1+1;
						len = Xc->Enc_Pack(imsi,item3,2,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						exp_money(imsi,imsi);
						
						
						mid2[imsi].item[Messages[imsi][1+k]-1][0]=0;
						mid2[imsi].item[Messages[imsi][1+k]-1][1]=0;
					}
					int johap_random=0;
					johap_random=rand()%100;
					//printf(" ���� : %d\n ������ %d\n",johap_random,johap_st[johap_flag3].percent);
					if(johap_random<johap_st[johap_flag3].percent)							
					{
						int imsiflag=0;
						for(int i=0;i<26;i++) 
						{
							
							if(mid2[imsi].item[i][0]==johap_st[johap_flag3].n_item+49151) // �̹� �ִ� �������� ���
							{
								// printf("name: %s\n",item_st[j].name);
								// printf("number : %d\n",j);
								// printf("�̹� �ִ� ������\n");
								mid2[imsi].item[i][1]++;
								char item2[100];
								memset(item2,0,100);
								sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
									i+1,(johap_st[johap_flag3].n_item+49151 & 0x0000ff00)  >> 8
									,(johap_st[johap_flag3].n_item+49151 & 0x000000ff) ,0x00,0x20,item_st[johap_st[johap_flag3].n_item].name
									,mid2[imsi].item[i][1],0x00,0x00,0x00);
								
								len = Xc->Enc_Pack(imsi,item2,100,0x0f,1);
								retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
								
								imsiflag=1;
								
								
								
								
								i = 26;
							}
						}
						if(imsiflag!=1)
						{
							for(int i=0;i<26;i++) 
							{
								if(mid2[imsi].item[i][0]==0) // ���ο� �������� ���
								{
									// printf("name: %s\n",item_st[j].name);
									// printf("number : %d\n",j);
									// printf("�� ������\n");
									mid2[imsi].item[i][0]=johap_st[johap_flag3].n_item+49151;
									mid2[imsi].item[i][1]++;
									char item2[100];
									memset(item2,0,100);
									sprintf(item2,"%c%c%c%c%c%s %d��%c%c%c",
										i+1,(johap_st[johap_flag3].n_item+49151 & 0x0000ff00)  >> 8
										,(johap_st[johap_flag3].n_item+49151 & 0x000000ff) ,0x00,0x20,item_st[johap_st[johap_flag3].n_item].name
										,mid2[imsi].item[i][1],0x00,0x00,0x00);
									
									len = Xc->Enc_Pack(imsi,item2,100,0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									i = 26;
								}
								
								
							}
						}
						
						sangtae(imsi,"���� ����!!");
						
						
						
						
					}
					else
					{
						sangtae(imsi,"���� ����");
						
					}
					
					
					
				}
				
				
				
				}
				
				
				//# 4. md5���� 197�� ����
				
				
				char tmp[1];
				
				
				
				
				
				
				
				
				
				
				
				if((char)buf[2]==0x06 && (char)buf[3]==0x30) //#��������ġ ������ġ
				{
					
					Xc->Dec_Pack(imsi,buf+2);
					if(Messages[imsi][0]==1 && Messages[imsi][1] >0 && Messages[imsi][2] < 53)
					{
						int temp;
						temp=mid2[imsi].magic[Messages[imsi][1]-1];
						mid2[imsi].magic[Messages[imsi][1]-1]=mid2[imsi].magic[Messages[imsi][2]-1];
						mid2[imsi].magic[Messages[imsi][2]-1]=temp;
						//printf("1:%d\n",mid2[imsi].magic[Messages[imsi][1]-1]);
						//printf("2:%d\n",mid2[imsi].magic[Messages[imsi][2]-1]);
						for(int i=0;i<52;i++)  // ���� ��Ͽ� �߰� �ϱ�
						{
							
							// printf("%d\n",i);
							char sendmagic[50];
							memset(sendmagic,0,50);
							magic_name(sendmagic,mid2[imsi].magic[i],i+1);
							// printf("%d\n",mid2[imsi].magic[i]);
							int len = Xc->Enc_Pack(imsi,sendmagic,strlen(sendmagic),0x17,1);
							int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
							packet_dump(sendmagic,20,16);
							
							
						}
						
						
						
						
						
					}
					
					
					
					
					if(Messages[imsi][0]==0 && Messages[imsi][1] >0 && Messages[imsi][2] < 27)
					{
						int temp[2];
						temp[0]=mid2[imsi].item[Messages[imsi][1]-1][0];
						temp[1]=mid2[imsi].item[Messages[imsi][1]-1][1];
						mid2[imsi].item[Messages[imsi][1]-1][0]=mid2[imsi].item[Messages[imsi][2]-1][0];
						mid2[imsi].item[Messages[imsi][1]-1][1]=mid2[imsi].item[Messages[imsi][2]-1][1];
						mid2[imsi].item[Messages[imsi][2]-1][0]=temp[0];
						mid2[imsi].item[Messages[imsi][2]-1][1]=temp[1];
						char item3[5];
						item3[0]=Messages[imsi][1];
						item3[1]=1;
						int len = Xc->Enc_Pack(imsi,item3,2,0x10,1);
						int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
						
						item3[0]=Messages[imsi][2];
						item3[1]=1;
						len = Xc->Enc_Pack(imsi,item3,2,0x10,1);
						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 
						
						
						for(i=0;i<26;i++)
						{
							if(mid2[imsi].item[i][0]!=0)
							{
								char item2[80];  // ������ ��Ͽ� �߱�
								memset(item2,0,80);
								char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								char gae[]="��";
								char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								itoa(mid2[imsi].item[i][1],msg2,10);
								
								// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
								strcpy(msg,item_st[mid2[imsi].item[i][0]-49151].name);
								item2[0]=i+1;
								item2[1]=( mid2[imsi].item[i][0] & 0x0000ff00 ) >> 8;
								item2[2]=( mid2[imsi].item[i][0] & 0x000000ff ) ;
								item2[3]='\x00';
								item2[4]='\x20';
								strcpy(item2+5,msg); //������ �̸�
								item2[5+strlen(msg)]='\x20'; // ��ĭ���
								strcpy(item2+6+strlen(msg),msg2); //���� 
								strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
								item2[8+strlen(msg)+strlen(msg2)]='\x00';
								item2[9+strlen(msg)+strlen(msg2)]='\x00';
								item2[10+strlen(msg)+strlen(msg2)]='\x00';
								int len = Xc->Enc_Pack(imsi,item2,80,0x0f,1);
								int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
							}
						}
					}
					
				}
				
				
				
				
				
				if((char)buf[3]==0x11)
				{
					test--;
					int len;
					// printf("���� �ٲٱ� ��Ŷ�� �޾ҽ��ϴ�. \n");
					char testpeer02[] = {0xaa}; // #�̾��ϱ� ���� Ȯ���ϴ� ��Ŷ
					char testpeer03[] = {0x00};
					test = strc(buf,testpeer02,1);
					if(test!=0)
					{
						return closesocket(client[socketnow]);
					}
					
					Xc->Dec_Pack(imsi,buf+2);
					mid2[imsi].banghyang=(int)Messages[imsi][0];
					// printf(" �ٲ� ���� : %d \n", mid2[imsi].banghyang);
					char sendmsg[50]; // Ŭ���̾�Ʈ���� �ɸ��� �ڱ���� ������ �κ�
					sendmsg[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
					sendmsg[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
					sendmsg[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
					sendmsg[3]=( mid2[imsi].thread & 0x000000ff ) ;
					sendmsg[4]=(char)mid2[imsi].banghyang;
					len = Xc->Enc_Pack(imsi,sendmsg,5,0x11,1);
					retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
					// printf(" ���� %d���� ������ �ֽ��ϴ�.\n"						,taijimap[mid2[imsi].realmap].count);
					
					for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
					{
						
						
						if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
						{
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != mid2[imsi].thread)
							{
								
								// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
								if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
									color=2;
								else color=3;
								int sendmsg_byte=loginchr2(imsi,color,sendmsg);
								//int sendmsg_byte=loginchr(imsi,sendmsg);  //�ٸ�Ŭ���̾�Ʈ���� �ɸ��� ��ġ ����
								len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
								if(	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x < mid2[imsi].map_x+17 
									&& mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x > mid2[imsi].map_x-17 
									&&	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y < mid2[imsi].map_y+17 
									&& mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y > mid2[imsi].map_y-17) 
									retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0); 
								
							}
						} 
						else {
							
							// printf("0 �̹Ƿ� imsi_count ����\n");
							imsi_count++;
						}
						
					}
					
					
				}
				
				if((char)buf[3]==0x32) // #�̵��ϱ� �ϴ� �ڵ�
				{
					
					
					
					int len;
					// printf("�̵��ϱ� ��Ŷ�� �޾ҽ��ϴ�. \n");
					
					Xc->Dec_Pack(imsi,buf+2);
					if(Messages[imsi][0]==1)
					{// ���������� �̵�
						mid2[imsi].banghyang=1;
					}
					if(Messages[imsi][0]==3)
					{// �������� �̵�
						mid2[imsi].banghyang=3;
					}
					if(Messages[imsi][0]==2)
					{// �Ʒ������� �̵�
						mid2[imsi].banghyang=2;
					}
					if(Messages[imsi][0]==0)
					{// �������� �̵�
						mid2[imsi].banghyang=0;
						// printf("�������� ���� ��ȯ\n");
					}
					if(int flag=move(imsi)==1)
					{
						packet_dump(Messages[imsi],20,16);
						char sendmsg2[50];
						
						sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;  
						sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;  
						sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
						sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
						sendmsg2[4]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
						sendmsg2[5]=( mid2[imsi].map_x & 0x000000ff ) ;
						sendmsg2[6]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
						sendmsg2[7]=( mid2[imsi].map_y & 0x000000ff ) ;
						sendmsg2[8]=Messages[imsi][0];
						sendmsg2[9]=Messages[imsi][1];
						len = Xc->Enc_Pack(imsi,sendmsg2,10,0x0c,1);
						
						for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
						{
							
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != mid2[imsi].thread)
								{
									// printf(" %d��° �������� �������� �̵��� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
									if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
										color=2;
									else color=3;
									int sendmsg_byte=loginchr2(imsi,color,sendmsg2);
									//int sendmsg_byte=loginchr(imsi,sendmsg2);  //�ٸ�Ŭ���̾�Ʈ���� �ɸ��� ��ġ ����
									if(	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x < mid2[imsi].map_x+17 
										&& mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x > mid2[imsi].map_x-17 
										&&	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y < mid2[imsi].map_y+17 
										&& mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y > mid2[imsi].map_y-17) 
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0); 
								}
							}else {
								
								// printf("0 �̹Ƿ� imsi_count ����\n");
								imsi_count++;
							}
						}
						
						char sendmsg[50];
						
						sendmsg[0]=Messages[imsi][0];  // Ŭ���̾�Ʈ���� ���� ���� �״�� ����(�̵�����)
						sendmsg[9]=Messages[imsi][1];  // ���������� �״��
						
						sendmsg[1]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
						sendmsg[2]=( mid2[imsi].map_x & 0x000000ff ) ;
						sendmsg[3]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
						sendmsg[4]=( mid2[imsi].map_y & 0x000000ff ) ;
						// printf("����Ǳ��� x ��ǥ : %d\n",mid2[imsi].map_x);
						// printf("����Ǳ��� y ��ǥ : %d\n",mid2[imsi].map_y);
						
						if((char)sendmsg[0]==0x01)
						{// ���������� �̵�
							mid2[imsi].map_x++;
						}
						if((char)sendmsg[0]==0x03)
						{// �������� �̵�
							mid2[imsi].map_x--;
						}
						if((char)sendmsg[0]==0x02)
						{// �Ʒ������� �̵�
							mid2[imsi].map_y++;
						}
						if((char)sendmsg[0]==0x00)
						{// ���������� �̵�
							mid2[imsi].map_y--;
						}
						
						sendmsg[5]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
						sendmsg[6]=( mid2[imsi].map_x & 0x000000ff ) ; 
						sendmsg[7]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
						sendmsg[8]=( mid2[imsi].map_y & 0x000000ff ) ;
						packet_dump(sendmsg,10,16);
						
						len = Xc->Enc_Pack(imsi,sendmsg,9,0x32,1);
						//retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
						
						char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
						sendmsg4[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
						sendmsg4[1]=( mid2[imsi].map_x & 0x000000ff ) ;
						sendmsg4[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
						sendmsg4[3]=( mid2[imsi].map_y & 0x000000ff ) ;
						sendmsg4[4]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
						sendmsg4[5]=( mid2[imsi].map_x & 0x000000ff ) ;
						sendmsg4[6]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
						sendmsg4[7]=( mid2[imsi].map_y & 0x000000ff ) ;
						
						//len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
						//retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
						
						// printf("������� x ��ǥ : %d\n",mid2[imsi].map_x);
						// printf("������� y ��ǥ : %d\n",mid2[imsi].map_y);
						
						
						
					}
					else
					{
						int len;
						char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
						sendmsg4[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
						sendmsg4[1]=( mid2[imsi].map_x & 0x000000ff ) ;
						sendmsg4[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
						sendmsg4[3]=( mid2[imsi].map_y & 0x000000ff ) ;
						sendmsg4[4]=( client_map_y(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
						sendmsg4[5]=( client_map_y(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
						sendmsg4[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
						sendmsg4[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
						
						len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
						retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
						
					}
					
					
					port_check(imsi,&kaflag);
					
					
					}
					
					
					
					if((char)buf[3]==0x06) // ������ ����� �̵��ϴ� �ڵ�
					{
						
						int len;
						// printf("ȭ�� ������ ����� �̵��ϱ� ��Ŷ�� �޾ҽ��ϴ�. \n");
						
						Xc->Dec_Pack(imsi,buf+2);
						if(Messages[imsi][0]==1)
						{// ���������� �̵�
							mid2[imsi].banghyang=1;
						}
						if(Messages[imsi][0]==3)
						{// �������� �̵�
							mid2[imsi].banghyang=3;
						}
						if(Messages[imsi][0]==2)
						{// �Ʒ������� �̵�
							mid2[imsi].banghyang=2;
						}
						if(Messages[imsi][0]==0)
						{// �������� �̵�
							mid2[imsi].banghyang=0;
							// printf("�������� ���� ��ȯ\n");
						}
						if(int flag=move(imsi)==1)
						{
							packet_dump(Messages[imsi],20,16);
							char sendmsg2[50];
							
							sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;  
							sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;  
							sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
							sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
							sendmsg2[4]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
							sendmsg2[5]=( mid2[imsi].map_x & 0x000000ff ) ;
							sendmsg2[6]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
							sendmsg2[7]=( mid2[imsi].map_y & 0x000000ff ) ;
							sendmsg2[8]=Messages[imsi][0];;
							sendmsg2[9]=Messages[imsi][1];;
							len = Xc->Enc_Pack(imsi,sendmsg2,10,0x0c,1);
							
							for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
							{
								
								if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != mid2[imsi].thread)
									{
										// printf(" %d��° �������� �������� �̵��� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
											color=2;
										else color=3;
										int sendmsg_byte=loginchr2(imsi,color,sendmsg2);
										//int sendmsg_byte=loginchr(imsi,sendmsg2);  //�ٸ�Ŭ���̾�Ʈ���� �ɸ��� ��ġ ����
										
										if(	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x < mid2[imsi].map_x+17 
											&& mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x > mid2[imsi].map_x-17 
											&&	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y < mid2[imsi].map_y+17 
											&& mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y > mid2[imsi].map_y-17) 
											retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0); 
									}
								}else {
									
									// printf("0 �̹Ƿ� imsi_count ����\n");
									imsi_count++;
								}
							}
							
							char sendmsg[50];
							
							sendmsg[0]=Messages[imsi][0];  // Ŭ���̾�Ʈ���� ���� ���� �״�� ����(�̵�����)
							sendmsg[9]=Messages[imsi][1];  // ���������� �״��
							
							sendmsg[1]='\x00';
							sendmsg[2]=mid2[imsi].map_x;
							sendmsg[3]='\x00';
							sendmsg[4]=mid2[imsi].map_y;
							// printf("����Ǳ��� x ��ǥ : %d\n",mid2[imsi].map_x);
							// printf("����Ǳ��� y ��ǥ : %d\n",mid2[imsi].map_y);
							
							if((char)sendmsg[0]==0x01)
							{// ���������� �̵�
								mid2[imsi].map_x++;
							}
							if((char)sendmsg[0]==0x03)
							{// �������� �̵�
								mid2[imsi].map_x--;
							}
							if((char)sendmsg[0]==0x02)
							{// �Ʒ������� �̵�
								mid2[imsi].map_y++;
							}
							if((char)sendmsg[0]==0x00)
							{// ���������� �̵�
								mid2[imsi].map_y--;
							}
							
							sendmsg[5]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
							sendmsg[6]=( mid2[imsi].map_x & 0x000000ff ) ;
							sendmsg[7]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
							sendmsg[8]=( mid2[imsi].map_y & 0x000000ff ) ;
							packet_dump(sendmsg,10,16);
							
							len = Xc->Enc_Pack(imsi,sendmsg,9,0x0b,1);
							//retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
							len = Xc->Enc_Pack(imsi,sendmsg,9,0x26,1);
							//retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
							
							char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
							sendmsg4[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
							sendmsg4[1]=( mid2[imsi].map_x & 0x000000ff ) ;
							sendmsg4[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
							sendmsg4[3]=( mid2[imsi].map_y & 0x000000ff ) ;
							sendmsg4[4]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
							sendmsg4[5]=( mid2[imsi].map_x & 0x000000ff ) ;
							sendmsg4[6]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
							sendmsg4[7]=( mid2[imsi].map_y & 0x000000ff ) ;
							// len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
							//retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
							
							// printf("������� x ��ǥ : %d\n",mid2[imsi].map_x);
							// printf("������� y ��ǥ : %d\n",mid2[imsi].map_y);
							
							
						}
						else
						{
							int len;
							char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
							sendmsg4[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
							sendmsg4[1]=( mid2[imsi].map_x & 0x000000ff ) ;
							sendmsg4[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
							sendmsg4[3]=( mid2[imsi].map_y & 0x000000ff ) ;
							sendmsg4[4]=( client_map_y(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
							sendmsg4[5]=( client_map_y(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
							sendmsg4[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
							sendmsg4[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
							len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
							retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
							
						}
						char sendmsg[50];
						
						for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++) // �ٸ� Ŭ���̾�Ʈ ��ġ ����
						{
							
							if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != socketnow)
								{
									if(mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x > mid2[imsi].map_x+7 || 
										mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y > mid2[imsi].map_y+7 ||
										mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x < mid2[imsi].map_x-7 ||
										mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y < mid2[imsi].map_y-7)
									{
										// printf(" %d��° �������� ������ ������ �޽��ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										
										if(mid2[imsi].group != 0 && mid2[imsi].group != -1 && mid2[imsi].group == mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].group)
											color=2;
										else color=3;
										int sendmsg_byte=loginchr2(taijimap[mid2[imsi].realmap].chrnumber[mapcount],color,sendmsg);
										//int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[mapcount],sendmsg);  //�ٸ� Ŭ���̾�Ʈ�� ��ġ�� ������
										len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
										retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
									}	
								}
							}else {
								
								// printf("0 �̹Ƿ� imsi_count ����\n");
								imsi_count++;
							}
						}
						
						for(int count=0,item_count=taijimap[mid2[imsi].realmap].item_count;count<item_count;count++)
						{
							
							if(taijimap[mid2[imsi].realmap].item_thread[count] != 0)
							{
								
								if(taijimap[mid2[imsi].realmap].item_x[count] > mid2[imsi].map_x+7 || 
									taijimap[mid2[imsi].realmap].item_y[count] > mid2[imsi].map_y+7 ||
									taijimap[mid2[imsi].realmap].item_x[count] < mid2[imsi].map_x-7 ||
									taijimap[mid2[imsi].realmap].item_y[count] < mid2[imsi].map_y-7)
								{	
									char item[19];
									item[0]='\x00';
									item[1]='\x01';
									item[2]=( taijimap[mid2[imsi].realmap].item_x[count] & 0x0000ff00 ) >> 8;
									item[3]=( taijimap[mid2[imsi].realmap].item_x[count] & 0x000000ff ) ;
									item[4]=( taijimap[mid2[imsi].realmap].item_y[count] & 0x0000ff00 ) >> 8;
									item[5]=( taijimap[mid2[imsi].realmap].item_y[count] & 0x000000ff ) ;
									item[6]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x0000ff00 ) >> 8;
									item[7]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x000000ff ) ;
									item[8]='\x00';
									item[9]='\x00';
									item[10]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
									item[11]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
									item[12]='\x00';
									
									len = Xc->Enc_Pack(imsi,item,13,0x07,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
									
								}
							}
							
							else imsi_count++;
							
						}
						
						port_check(imsi,&kaflag);
						
						
					}
					
					
					
					
					
					if((char)buf[3]==0x0f) // #������� �ڵ�
					{
						
						int len;
						int mapcount;
						// printf("������ ����մϴ�.\n");
						
						Xc->Dec_Pack(imsi,buf+2);
						packet_dump(Messages[imsi],20,16);
						GetLocalTime( &st ); 
						// printf("������ȣ : %d\n",(int)Messages[imsi][0]);
						if(taijimap[mid2[imsi].realmap].magic_on==1 || mid2[imsi].s_number==99)
							magic_run(mid2[imsi].magic[Messages[imsi][0]-1],imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow,Messages[imsi],&kaflag);
						else
						{
							len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� ��� �Ұ�������",40,0x0a,1);
							retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
							
						}
						
						/* 
						switch((int)Messages[imsi][0])
						{
						
						  case 1:
						  {
						  GetLocalTime( &st );
						  int magic=magic_01(imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow);
						  magic--;
						  if(magic==-1) 
						  {
						  
							
							  // printf("���� ���� �ȸ���\n");
							  len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� ������ ���� �ʽ��ϴ�.",40,0x0a,1);
							  //retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
							  
								break;
								
								  }
								  
									
									  else
									  {
									  char sendmsg1[13];
									  sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
									  sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
									  sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
									  sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
									  sendmsg1[4]='\x01';
									  sendmsg1[5]='\x00';
									  sendmsg1[6]='\x4e';
									  sendmsg1[7]='\x08';
									  
										len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
										for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
										{
										if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
										{
										// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
										}
										else imsi_count++;
										
										  }
										  
											
											  char sendmsg2[50]; // Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
											  int sendmsg_byte=loginchr(magic,sendmsg2);
											  
												len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
												for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
												{
												if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
												{
												// printf(" %d��° �������� �������� �ٲ� ��ġ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
												retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
												}
												else imsi_count++;
												}
												
												  char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
												  sendmsg4[0]='\x00';
												  sendmsg4[1]=(int)mid2[magic].map_x;
												  sendmsg4[2]='\x00';
												  sendmsg4[3]=(int)mid2[magic].map_y;
												  sendmsg4[4]='\x00';
												  sendmsg4[5]=client_map_x(magic,mid2[magic].map_x);
												  sendmsg4[6]='\x00';
												  sendmsg4[7]=client_map_y(magic,mid2[magic].map_y);
												  
													len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
													retval = send(client[mid2[magic].thread],Encrypted_Messages[imsi],len, 0);  
													
													  
														char sendmsg5[5];
														sendmsg5[0]=( mid2[magic].thread & 0xff000000 ) >> 24;
														sendmsg5[1]=( mid2[magic].thread & 0x00ff0000 ) >> 16;
														sendmsg5[2]=( mid2[magic].thread & 0x0000ff00 ) >> 8;
														sendmsg5[3]=( mid2[magic].thread & 0x000000ff ) ;
														sendmsg5[4]='\x69';
														
														  len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
														  for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
														  {
														  if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
														  {
														  // printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
														  retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
														  }
														  else imsi_count++;
														  }
														  
															break;
															}
															}
															
															  case 2:
															  
																{
																
																  GetLocalTime( &st );
																  int magic=magic_02(imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow);
																  magic--;
																  if(magic==-1) 
																  {
																  
																	
																	  // printf("���� ���� �ȸ���\n");
																	  len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� ������ ���� �ʽ��ϴ�.",40,0x0a,1);
																	  //retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																	  
																		
																		  }
																		  
																			
																			  else
																			  {
																			  
																				
																				  char sendmsg2[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
																				  int sendmsg_byte=loginchr(imsi,sendmsg2);
																				  
																					len = Xc->Enc_Pack(imsi,sendmsg2,sendmsg_byte,0x33,1);
																					for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
																					{
																					if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
																					{
																					// printf(" %d��° �������� �������� ����� ��ġ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
																					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
																					}
																					else imsi_count++;
																					}
																					
																					  char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
																					  sendmsg4[0]='\x00';
																					  sendmsg4[1]=(int)mid2[imsi].map_x;
																					  sendmsg4[2]='\x00';
																					  sendmsg4[3]=(int)mid2[imsi].map_y;
																					  sendmsg4[4]='\x00';
																					  sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
																					  sendmsg4[6]='\x00';
																					  sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
																					  
																						len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
																						retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
																						
																						  
																							char sendmsg5[5];
																							sendmsg5[0]=( mid2[magic].thread & 0xff000000 ) >> 24;
																							sendmsg5[1]=( mid2[magic].thread & 0x00ff0000 ) >> 16;
																							sendmsg5[2]=( mid2[magic].thread & 0x0000ff00 ) >> 8;
																							sendmsg5[3]=( mid2[magic].thread & 0x000000ff ) ;
																							sendmsg5[4]='\x61';
																							
																							  len = Xc->Enc_Pack(imsi,sendmsg5,5,0x29,1);
																							  for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
																							  {
																							  if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
																							  {
																							  // printf(" %d��° �������� �������� ���� ����Ʈ�� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
																							  retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
																							  }
																							  else imsi_count++;
																							  }
																							  
																								char sendmsg1[13];
																								sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
																								sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
																								sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
																								sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;
																								sendmsg1[4]='\x01';
																								sendmsg1[5]='\x00';
																								sendmsg1[6]='\x4e';
																								sendmsg1[7]='\x08';
																								
																								  len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
																								  for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
																								  {
																								  if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
																								  {
																								  // printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
																								  retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
																								  }
																								  else imsi_count++;
																								  }
																								  
																									}
																									break;
																									}
																									
																									  case 3 :
																									  {
																									  GetLocalTime( &st ); 
																									  magic_run(mid2[imsi].magic[2],imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow,Messages[imsi]);
																									  //magic_03(imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow);
																									  break;
																									  }
																									  case 4 :
																									  {
																									  GetLocalTime( &st ); 
																									  magic_run(mid2[imsi].magic[(int)Messages[imsi][0]],imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow,Messages[imsi]);
																									  GetLocalTime( &st );
																									  magic_04(imsi,st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400,socketnow);
																									  break;
																									  }
																									  case 5 :
																									  {
																									  magic_05(imsi,Messages[imsi]);
																									  }
																									  break;
																									  
																										
					}*/

					}
					
					
					
					
					if(buf[3]==0x2d) // #����â ����
					{
						char peer0_1[] = {
							0xaa, 0x00, 0x34, 0x39, 0x46, 0x95, 0x26, 0x3b, 
								0x29, 0x28, 0x07, 0x91, 0xe9, 0xac, 
								
								0xaa, 0x9c, 
								0xf9, 0xe8, 0xe5, 0x0a, 0xe9, 0xd8, 0xd2, 0xed, 
								0x21, 0x3c, 0x2b, 0x2a, 0x0d, 0x2e, 0xe7, 0x96, 
								0xb0, 0xc7, 0xfd, 0x2a, 0x2b, 0xc8, 0x87, 0x26, 
								0xaf, 0xa0, 0x27, 0xfb, 0x75, 0x2c, 0xcb, 0x2c, 
								0x21, 0x6c, 0x0d, 0x26, 0x3b, 0x2c, 0x2d };
							
							int len,retval;
							//retval = send(client[socketnow],peer0_1,55, 0);
							char group_member[100];
							if(mid2[imsi].group==-1 || mid2[imsi].group==0)
							{
								sprintf(group_member,"�׷� ����");
							}
							else
							{
								// printf("�ڱ� Imsi   :%d\n",imsi);
								for(int i=0,pointer=0,member_count=0;i<frecnum;i++)
								{
									
									
									
									
									
									if((mid2[i].group == mid2[imsi].group) && (mid2[i].group != 0))
									{
										
										if(i==mid2[imsi].group)
										{
											sprintf(group_member+pointer,"*%s  ",mid2[i].id);
											pointer=pointer+strlen(mid2[i].id)+2;
											member_count++;
											
										}
										else
										{
											// printf("���� I      :%d\n",i);
											// printf("I �׷�      :%d\n",mid2[i].group);
											// printf("���� �׷��� :%d\n",mid2[imsi].group);
											sprintf(group_member+pointer,"%s  ",mid2[i].id);
											pointer=pointer+strlen(mid2[i].id)+2;
											member_count++;
											
										}
									}
									
								}
								sprintf(group_member+pointer,"<���� %d ��>",member_count);
							}
							
							int group_on;
							if(mid2[imsi].group==-1) group_on=0;
							else group_on=1;
							
							packet_dump(group_member,50,16);
							char msg[200];
							memset(msg,0,70);
							sprintf(msg,
								"%c%c%c%c%c%c%c%s%c%c%c%c%c%c%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
								mid2[imsi].ac, // ac
								0x00, // ���ݼ���
								0x00, // ���߼���
								0x00, //���� Ÿ��Ʋ
								0x00, //���� Īȣ Ÿ��Ʋ
								0x00, //Īȣ Ÿ��Ʋ
								strlen(group_member), //���� ���� ĭ��
								group_member, // �׷��
								(char)group_on, // �׷�
								( mid2[imsi].need_exp & 0xff000000 ) >> 24, // �ʰ�
								( mid2[imsi].need_exp & 0x00ff0000 ) >> 16, // �ʰ�
								( mid2[imsi].need_exp & 0x0000ff00 ) >> 8, // �ʰ�
								( mid2[imsi].need_exp & 0x000000ff ) , // �ʰ�
								strlen(mid2[imsi].job), // ���� ĭ��
								mid2[imsi].job,
								( mid2[imsi].head_gear+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi].head_gear+49151 & 0x000000ff ) ,
								0x00,
								( mid2[imsi].ring[0]+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi].ring[0]+49151 & 0x000000ff ) ,
								0x00,
								( mid2[imsi].ring[1]+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi].ring[1]+49151 & 0x000000ff ) ,
								0x00,
								( mid2[imsi].earing[0]+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi].earing[0]+49151 & 0x000000ff ) ,
								0x00,
								( mid2[imsi].earing[1]+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi].earing[1]+49151 & 0x000000ff ) ,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00
								
								);
							packet_dump(msg,200,16);
							/*msg[0]='\x8d';
							msg[1]='\x08';
							msg[2]='\x08';
							msg[3]='\x00';
							msg[4]='\x00';
							msg[5]='\x08';
							msg[6]='\xb9';
							msg[7]='\xcc';
							msg[8]='\xc4';
							msg[9]='\xa3';
							msg[10]='\xbe';
							msg[11]='\xc6';
							msg[12]='\xc0';
							msg[13]='\xcc';
							msg[14]='\x04'; // ���� ���� ĭ��
							msg[15]='\x61';
							msg[16]='\x61';
							msg[17]='\x61';
							msg[18]='\x61';
							msg[19]='\x00';
							msg[20]='\x00';
							msg[21]='\x00';
							msg[22]='\x00';
							msg[23]='\x00';
							msg[24]='\x04';
							msg[25]='\xc0';
							msg[26]='\xfc';
							msg[27]='\xbb';
							msg[28]='\xe7';
							msg[29]=( mid2[imsi].head_gear+49151 & 0x0000ff00 ) >> 8;
							msg[30]=( mid2[imsi].head_gear+49151 & 0x000000ff ) ;
							msg[31]='\x00';
							msg[32]=( mid2[imsi].ring[0]+49151 & 0x0000ff00 ) >> 8;
							msg[33]=( mid2[imsi].ring[0]+49151 & 0x000000ff ) ;
							msg[34]='\x00';
							msg[35]=( mid2[imsi].ring[1]+49151 & 0x0000ff00 ) >> 8;
							msg[36]=( mid2[imsi].ring[1]+49151 & 0x000000ff ) ;
							msg[37]='\x00';
							msg[38]=( mid2[imsi].earing[0]+49151 & 0x0000ff00 ) >> 8;
							msg[39]=( mid2[imsi].earing[0]+49151 & 0x000000ff ) ;
							msg[40]='\x00';
							msg[41]=( mid2[imsi].earing[1]+49151 & 0x0000ff00 ) >> 8;
							msg[42]=( mid2[imsi].earing[1]+49151 & 0x000000ff ) ;
							msg[43]='\x00';
							msg[44]='\x00';
							msg[45]='\x00';
							msg[46]='\x00';
							msg[47]='\x00';
							msg[48]='\x00';
							msg[49]='\x00';
							msg[50]='\x00';
							msg[51]='\x00';*/
							
							len = Xc->Enc_Pack(imsi,msg,200,0x39,1);
							retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
							
							
							
							
							
							
					}
					
					if((char)buf[3]==0x1c) // #�����ϱ�
					{
						
						if(mid2[imsi].sangtae==0)
						{
							
							int len,retval;
							Xc->Dec_Pack(imsi,buf+2);
							int alpha = (int)Messages[imsi][0];
							char sendmsg[50];
							// printf("���� �ٲٱ� �Դϴ�. �ٲ﹫�� %d\n",mid2[imsi].sword);
							// printf("alphabet : %d \n",alpha);
							// printf("select : %d \n",item_st[mid2[imsi].item[(int)alpha-1][0]-49151].select);
							
							
							switch(item_st[mid2[imsi].item[(int)alpha-1][0]-49151].select)
							{
							case 1:
								{
									
									// printf("�� �ٲٱ� �Դϴ�. ������ %d\n",mid2[imsi].dress);
									// printf("�� �ٲٱ� �Դϴ�. �ٲ�� %d\n",item_st[mid2[imsi].item[(int)alpha-1][0]-49151].dress_number);
									int fflag=0;
									for(int k=0;k<2600;k++)
									{
										if(item_st[k].dress_number==mid2[imsi].dress)
										{
											fflag = k;
											k=2600;
										}
									}
									mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
									mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
									mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
									mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
									mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
									mid2[imsi].dress=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].dress_number;
									mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
									mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
									mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
									mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
									mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
									exp_money(imsi,imsi);
									int sendmsg_byte=loginchr(imsi,sendmsg);
									len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									
									
									// printf("���� ��  �ڵ�  : %d\n",fflag+49151);
									for(int i=0;i<26;i++)
									{
										
										
										// printf("%d ��° ������ : %d\n",i,mid2[imsi].item[i][0]);
										if(mid2[imsi].item[i][0]==fflag+49151)
										{
											// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
											mid2[imsi].item[i][1]++;
											char item2[80];  // ������ ��Ͽ� �߱�
											char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											char gae[]="��";
											char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											itoa(mid2[imsi].item[i][1],msg2,10);
											
											// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
											strcpy(msg,item_st[fflag].name);
											item2[0]=i+1;
											item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
											item2[2]=( fflag+49151 & 0x000000ff ) ;
											item2[3]='\x00';
											item2[4]='\x20';
											strcpy(item2+5,msg); //������ �̸�
											item2[5+strlen(msg)]='\x20'; // ��ĭ���
											strcpy(item2+6+strlen(msg),msg2); //���� 
											strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
											item2[8+strlen(msg)+strlen(msg2)]='\x00';
											item2[9+strlen(msg)+strlen(msg2)]='\x00';
											item2[10+strlen(msg)+strlen(msg2)]='\x00';
											len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											i=26;
										}
										
										
										
										
										if(i!=26)
										{
											if(mid2[imsi].item[i][0]==0)
											{
												// printf("���ο� ���Կ� ������ �߰� \n");
												mid2[imsi].item[i][1]++;
												mid2[imsi].item[i][0]=fflag+49151;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
										}
										
										
										
									}
									
									
									
									
									
									
									
									mid2[imsi].item[alpha-1][1]--;
									
									
									
									
									char item2[80];  // ������ ��Ͽ� �߱�
									char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									char gae[]="��";
									char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									itoa(mid2[imsi].item[alpha-1][1],msg2,10);
									
									// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
									strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
									item2[0]=alpha;
									item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
									item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
									item2[3]='\x00';
									item2[4]='\x20';
									strcpy(item2+5,msg); //������ �̸�
									item2[5+strlen(msg)]='\x20'; // ��ĭ���
									strcpy(item2+6+strlen(msg),msg2); //���� 
									strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
									item2[8+strlen(msg)+strlen(msg2)]='\x00';
									item2[9+strlen(msg)+strlen(msg2)]='\x00';
									item2[10+strlen(msg)+strlen(msg2)]='\x00';
									len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									
									
									if(mid2[imsi].item[alpha-1][1]==0)
									{
										char item3[5];
										item3[0]=alpha;
										len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										mid2[imsi].item[alpha-1][0]=0;
										
									}
									
									
									
									break;
								}
							case 2:
								{
									
									
									// printf("���� �ٲٱ� �Դϴ�. �ٲ﹫�� %d\n",mid2[imsi].sword);
									int fflag=0;
									for(int k=0;k<2600;k++)
									{
										if(item_st[k].sword_number==mid2[imsi].sword)
										{
											fflag = k;
											k=2600;
										}
									}
									mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
									mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
									mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
									mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
									mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
									mid2[imsi].sword=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].sword_number;
									mid2[imsi].sword_item=mid2[imsi].item[(int)alpha-1][0]-49151;
									mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
									mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
									mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
									mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
									mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
									
									
									exp_money(imsi,imsi);
									int sendmsg_byte=loginchr(imsi,sendmsg);
									len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									
									// printf("flag :%d \n",fflag);
									for(int i=0;i<26;i++)
									{
										
										if(mid2[imsi].item[i][0]==fflag+49151)
										{
											// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
											mid2[imsi].item[i][1]++;
											char item2[80];  // ������ ��Ͽ� �߱�
											char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											char gae[]="��";
											char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											itoa(mid2[imsi].item[i][1],msg2,10);
											
											// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
											strcpy(msg,item_st[fflag].name);
											item2[0]=i+1;
											item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
											item2[2]=( fflag+49151 & 0x000000ff ) ;
											item2[3]='\x00';
											item2[4]='\x20';
											strcpy(item2+5,msg); //������ �̸�
											item2[5+strlen(msg)]='\x20'; // ��ĭ���
											strcpy(item2+6+strlen(msg),msg2); //���� 
											strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
											item2[8+strlen(msg)+strlen(msg2)]='\x00';
											item2[9+strlen(msg)+strlen(msg2)]='\x00';
											item2[10+strlen(msg)+strlen(msg2)]='\x00';
											len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											i=26;
										}
										
										
										
										
										if(i!=26)
										{
											if(mid2[imsi].item[i][0]==0)
											{
												// printf("���ο� ���Կ� ������ �߰� \n");
												mid2[imsi].item[i][1]++;
												mid2[imsi].item[i][0]=fflag+49151;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
										}
										
										
										
									}
									
									
									
									
									
									
									
									mid2[imsi].item[alpha-1][1]--;
									
									
									
									
									char item2[80];  // ������ ��Ͽ� �߱�
									char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									char gae[]="��";
									char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									itoa(mid2[imsi].item[alpha-1][1],msg2,10);
									
									// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
									strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
									item2[0]=alpha;
									item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
									item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
									item2[3]='\x00';
									item2[4]='\x20';
									strcpy(item2+5,msg); //������ �̸�
									item2[5+strlen(msg)]='\x20'; // ��ĭ���
									strcpy(item2+6+strlen(msg),msg2); //���� 
									strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
									item2[8+strlen(msg)+strlen(msg2)]='\x00';
									item2[9+strlen(msg)+strlen(msg2)]='\x00';
									item2[10+strlen(msg)+strlen(msg2)]='\x00';
									len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									
									
									if(mid2[imsi].item[alpha-1][1]==0)
									{
										char item3[5];
										item3[0]=alpha;
										len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										mid2[imsi].item[alpha-1][0]=0;
										
									}
									
									
									
									
									
									
									break;
								}
							case 3:
								{
									// printf("���� �ٲٱ� �Դϴ�. �ٲ���� %d\n",mid2[imsi].bangpae);
									int fflag=0;
									for(int k=0;k<2600;k++)
									{
										if(item_st[k].bangpae_number==mid2[imsi].bangpae)
										{
											fflag = k;
											k=2600;
										}
									}
									mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
									mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
									mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
									mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
									mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
									mid2[imsi].bangpae=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].bangpae_number;
									mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
									mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
									mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
									mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
									mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
									
									
									
									exp_money(imsi,imsi);
									int sendmsg_byte=loginchr(imsi,sendmsg);
									len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									
									// printf("flag :%d \n",fflag);
									for(int i=0;i<26;i++) 
									{
										
										if(mid2[imsi].item[i][0]==fflag+49151)
										{
											// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
											mid2[imsi].item[i][1]++;
											char item2[80];  // ������ ��Ͽ� �߱�
											char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											char gae[]="��";
											char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											itoa(mid2[imsi].item[i][1],msg2,10);
											
											// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
											strcpy(msg,item_st[fflag].name);
											item2[0]=i+1;
											item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
											item2[2]=( fflag+49151 & 0x000000ff ) ;
											item2[3]='\x00';
											item2[4]='\x20';
											strcpy(item2+5,msg); //������ �̸�
											item2[5+strlen(msg)]='\x20'; // ��ĭ���
											strcpy(item2+6+strlen(msg),msg2); //���� 
											strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
											item2[8+strlen(msg)+strlen(msg2)]='\x00';
											item2[9+strlen(msg)+strlen(msg2)]='\x00';
											item2[10+strlen(msg)+strlen(msg2)]='\x00';
											len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											i=26;
										}
										
										
										
										
										if(i!=26)
										{
											if(mid2[imsi].item[i][0]==0)
											{
												// printf("���ο� ���Կ� ������ �߰� \n");
												mid2[imsi].item[i][1]++;
												mid2[imsi].item[i][0]=fflag+49151;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
										}
										
										
										
									}
									
									
									
									
									
									
									
									mid2[imsi].item[alpha-1][1]--;
									
									
									
									
									char item2[80];  // ������ ��Ͽ� �߱�
									char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									char gae[]="��";
									char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									itoa(mid2[imsi].item[alpha-1][1],msg2,10);
									
									// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
									strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
									item2[0]=alpha;
									item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
									item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
									item2[3]='\x00';
									item2[4]='\x20';
									strcpy(item2+5,msg); //������ �̸�
									item2[5+strlen(msg)]='\x20'; // ��ĭ���
									strcpy(item2+6+strlen(msg),msg2); //���� 
									strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
									item2[8+strlen(msg)+strlen(msg2)]='\x00';
									item2[9+strlen(msg)+strlen(msg2)]='\x00';
									item2[10+strlen(msg)+strlen(msg2)]='\x00';
									len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									
									
									if(mid2[imsi].item[alpha-1][1]==0)
									{
										char item3[5];
										item3[0]=alpha;
										len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										mid2[imsi].item[alpha-1][0]=0;
										
									}
									break;
								}
							case 4:
								{
									
									// printf("�� �ٲٱ� �Դϴ�. ������ %d\n",mid2[imsi].dress);
									// printf("�� �ٲٱ� �Դϴ�. �ٲ�� %d\n",item_st[mid2[imsi].item[(int)alpha-1][0]-49151].dress_number);
									int fflag=0;
									for(int k=0;k<2600;k++)
									{
										if(item_st[k].head_number==mid2[imsi].head_gear)
										{
											fflag = k;
											k=2600;
										}
									}
									
									mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
									mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
									mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
									mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
									mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
									mid2[imsi].head_gear=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].head_number;
									mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
									mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
									mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
									mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
									mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
									
									
									
									exp_money(imsi,imsi);
									int sendmsg_byte=loginchr(imsi,sendmsg);
									len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									
									
									// printf("���� ��  �ڵ�  : %d\n",fflag+49151);
									for(int i=0;i<26;i++)
									{
										
										
										// printf("%d ��° ������ : %d\n",i,mid2[imsi].item[i][0]);
										if(mid2[imsi].item[i][0]==fflag+49151)
										{
											// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
											mid2[imsi].item[i][1]++;
											char item2[80];  // ������ ��Ͽ� �߱�
											char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											char gae[]="��";
											char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											itoa(mid2[imsi].item[i][1],msg2,10);
											
											// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
											strcpy(msg,item_st[fflag].name);
											item2[0]=i+1;
											item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
											item2[2]=( fflag+49151 & 0x000000ff ) ;
											item2[3]='\x00';
											item2[4]='\x20';
											strcpy(item2+5,msg); //������ �̸�
											item2[5+strlen(msg)]='\x20'; // ��ĭ���
											strcpy(item2+6+strlen(msg),msg2); //���� 
											strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
											item2[8+strlen(msg)+strlen(msg2)]='\x00';
											item2[9+strlen(msg)+strlen(msg2)]='\x00';
											item2[10+strlen(msg)+strlen(msg2)]='\x00';
											len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											i=26;
										}
										
										
										
										
										if(i!=26)
										{
											if(mid2[imsi].item[i][0]==0)
											{
												// printf("���ο� ���Կ� ������ �߰� \n");
												mid2[imsi].item[i][1]++;
												mid2[imsi].item[i][0]=fflag+49151;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
										}
										
										
										
									}
									
									
									
									
									
									
									
									mid2[imsi].item[alpha-1][1]--;
									
									
									
									
									char item2[80];  // ������ ��Ͽ� �߱�
									char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									char gae[]="��";
									char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									itoa(mid2[imsi].item[alpha-1][1],msg2,10);
									
									// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
									strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
									item2[0]=alpha;
									item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
									item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
									item2[3]='\x00';
									item2[4]='\x20';
									strcpy(item2+5,msg); //������ �̸�
									item2[5+strlen(msg)]='\x20'; // ��ĭ���
									strcpy(item2+6+strlen(msg),msg2); //���� 
									strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
									item2[8+strlen(msg)+strlen(msg2)]='\x00';
									item2[9+strlen(msg)+strlen(msg2)]='\x00';
									item2[10+strlen(msg)+strlen(msg2)]='\x00';
									len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									
									
									if(mid2[imsi].item[alpha-1][1]==0)
									{
										char item3[5];
										item3[0]=alpha;
										len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										mid2[imsi].item[alpha-1][0]=0;
										
									}
									
									
									
									break;
								}
							case 5:
								{
									
									int fflag=0,fflag2=0;
									
									
									if(mid2[imsi].ring[0]==0)
									{
										
										fflag2=1;
										mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
										mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
										mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
										mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
										mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
										mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
										mid2[imsi].ring[0]=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ring_number;
										mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
										mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
										mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
										mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
										mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
										mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
										
										
										
										exp_money(imsi,imsi);
										int sendmsg_byte=loginchr(imsi,sendmsg);
										len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
										retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
										
										
										// printf("���� ��  �ڵ�  : %d\n",fflag+49151);
										for(int i=0;i<26;i++)
										{
											
											
											// printf("%d ��° ������ : %d\n",i,mid2[imsi].item[i][0]);
											if(mid2[imsi].item[i][0]==fflag+49151)
											{
												// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
												mid2[imsi].item[i][1]++;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
											
											
											
											
											if(i!=26)
											{
												if(mid2[imsi].item[i][0]==0)
												{
													// printf("���ο� ���Կ� ������ �߰� \n");
													mid2[imsi].item[i][1]++;
													mid2[imsi].item[i][0]=fflag+49151;
													char item2[80];  // ������ ��Ͽ� �߱�
													char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
													char gae[]="��";
													char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
													itoa(mid2[imsi].item[i][1],msg2,10);
													
													// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
													strcpy(msg,item_st[fflag].name);
													item2[0]=i+1;
													item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
													item2[2]=( fflag+49151 & 0x000000ff ) ;
													item2[3]='\x00';
													item2[4]='\x20';
													strcpy(item2+5,msg); //������ �̸�
													item2[5+strlen(msg)]='\x20'; // ��ĭ���
													strcpy(item2+6+strlen(msg),msg2); //���� 
													strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
													item2[8+strlen(msg)+strlen(msg2)]='\x00';
													item2[9+strlen(msg)+strlen(msg2)]='\x00';
													item2[10+strlen(msg)+strlen(msg2)]='\x00';
													len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
													retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
													i=26;
												}
											}
											
											
											
										}
										
										
										
										
										
										
										
										mid2[imsi].item[alpha-1][1]--;
										
										
										
										
										
										char item2[80];  // ������ ��Ͽ� �߱�
										char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
										char gae[]="��";
										char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
										itoa(mid2[imsi].item[alpha-1][1],msg2,10);
										
										// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
										strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
										item2[0]=alpha;
										item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
										item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
										item2[3]='\x00';
										item2[4]='\x20';
										strcpy(item2+5,msg); //������ �̸�
										item2[5+strlen(msg)]='\x20'; // ��ĭ���
										strcpy(item2+6+strlen(msg),msg2); //���� 
										strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
										item2[8+strlen(msg)+strlen(msg2)]='\x00';
										item2[9+strlen(msg)+strlen(msg2)]='\x00';
										item2[10+strlen(msg)+strlen(msg2)]='\x00';
										len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										
										
										
										if(mid2[imsi].item[alpha-1][1]==0)
										{
											char item3[5];
											item3[0]=alpha;
											len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											mid2[imsi].item[alpha-1][0]=0;
											
										}
								}
								
								if(mid2[imsi].ring[1]==0 && fflag2==0)
								{
									fflag2=1;
									
									mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
									mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
									mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
									mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
									mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
									mid2[imsi].ring[1]=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ring_number;
									mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
									mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
									mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
									mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
									mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
									
									exp_money(imsi,imsi);
									int sendmsg_byte=loginchr(imsi,sendmsg);
									len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									
									
									// printf("���� ��  �ڵ�  : %d\n",fflag+49151);
									for(int i=0;i<26;i++)
									{
										
										
										// printf("%d ��° ������ : %d\n",i,mid2[imsi].item[i][0]);
										if(mid2[imsi].item[i][0]==fflag+49151)
										{
											// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
											mid2[imsi].item[i][1]++;
											char item2[80];  // ������ ��Ͽ� �߱�
											char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											char gae[]="��";
											char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											itoa(mid2[imsi].item[i][1],msg2,10);
											
											// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
											strcpy(msg,item_st[fflag].name);
											item2[0]=i+1;
											item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
											item2[2]=( fflag+49151 & 0x000000ff ) ;
											item2[3]='\x00';
											item2[4]='\x20';
											strcpy(item2+5,msg); //������ �̸�
											item2[5+strlen(msg)]='\x20'; // ��ĭ���
											strcpy(item2+6+strlen(msg),msg2); //���� 
											strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
											item2[8+strlen(msg)+strlen(msg2)]='\x00';
											item2[9+strlen(msg)+strlen(msg2)]='\x00';
											item2[10+strlen(msg)+strlen(msg2)]='\x00';
											len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											i=26;
										}
										
										
										
										
										if(i!=26)
										{
											if(mid2[imsi].item[i][0]==0)
											{
												// printf("���ο� ���Կ� ������ �߰� \n");
												mid2[imsi].item[i][1]++;
												mid2[imsi].item[i][0]=fflag+49151;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
										}
										
										
										
									}
									
									
									
									
									
									
									
									
									mid2[imsi].item[alpha-1][1]--;
									
									
									
									
									char item2[80];  // ������ ��Ͽ� �߱�
									char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									char gae[]="��";
									char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									itoa(mid2[imsi].item[alpha-1][1],msg2,10);
									
									// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
									strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
									item2[0]=alpha;
									item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
									item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
									item2[3]='\x00';
									item2[4]='\x20';
									strcpy(item2+5,msg); //������ �̸�
									item2[5+strlen(msg)]='\x20'; // ��ĭ���
									strcpy(item2+6+strlen(msg),msg2); //���� 
									strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
									item2[8+strlen(msg)+strlen(msg2)]='\x00';
									item2[9+strlen(msg)+strlen(msg2)]='\x00';
									item2[10+strlen(msg)+strlen(msg2)]='\x00';
									len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									
									
									if(mid2[imsi].item[alpha-1][1]==0)
									{
										char item3[5];
										item3[0]=alpha;
										len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										mid2[imsi].item[alpha-1][0]=0;
										
									}
								}
								
								if(fflag2==0)
								{
									for(int k=0;k<2600;k++)
									{
										if(item_st[k].ring_number==mid2[imsi].ring[0])
										{
											fflag = k;
											k=2600;
										}
									}
									
									mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
									mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
									mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
									mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
									mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
									mid2[imsi].ring[0]=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ring_number;
									mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
									mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
									mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
									mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
									mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
									
									
									
									
									exp_money(imsi,imsi);
									int sendmsg_byte=loginchr(imsi,sendmsg);
									len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									
									
									// printf("���� ��  �ڵ�  : %d\n",fflag+49151);
									for(int i=0;i<26;i++)
									{
										
										
										// printf("%d ��° ������ : %d\n",i,mid2[imsi].item[i][0]);
										if(mid2[imsi].item[i][0]==fflag+49151)
										{
											// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
											mid2[imsi].item[i][1]++;
											char item2[80];  // ������ ��Ͽ� �߱�
											char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											char gae[]="��";
											char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											itoa(mid2[imsi].item[i][1],msg2,10);
											
											// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
											strcpy(msg,item_st[fflag].name);
											item2[0]=i+1;
											item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
											item2[2]=( fflag+49151 & 0x000000ff ) ;
											item2[3]='\x00';
											item2[4]='\x20';
											strcpy(item2+5,msg); //������ �̸�
											item2[5+strlen(msg)]='\x20'; // ��ĭ���
											strcpy(item2+6+strlen(msg),msg2); //���� 
											strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
											item2[8+strlen(msg)+strlen(msg2)]='\x00';
											item2[9+strlen(msg)+strlen(msg2)]='\x00';
											item2[10+strlen(msg)+strlen(msg2)]='\x00';
											len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											i=26;
										}
										
										
										
										
										
										if(i!=26)
										{
											if(mid2[imsi].item[i][0]==0)
											{
												// printf("���ο� ���Կ� ������ �߰� \n");
												mid2[imsi].item[i][1]++;
												mid2[imsi].item[i][0]=fflag+49151;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
										}
										
										
										
									}
									
									
									
									
									
									
									
									mid2[imsi].item[alpha-1][1]--;
									
									
									
									
									char item2[80];  // ������ ��Ͽ� �߱�
									char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									char gae[]="��";
									char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									itoa(mid2[imsi].item[alpha-1][1],msg2,10);
									
									// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
									strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
									item2[0]=alpha;
									item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
									item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
									item2[3]='\x00';
									item2[4]='\x20';
									strcpy(item2+5,msg); //������ �̸�
									item2[5+strlen(msg)]='\x20'; // ��ĭ���
									strcpy(item2+6+strlen(msg),msg2); //���� 
									strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
									item2[8+strlen(msg)+strlen(msg2)]='\x00';
									item2[9+strlen(msg)+strlen(msg2)]='\x00';
									item2[10+strlen(msg)+strlen(msg2)]='\x00';
									len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									
									
									if(mid2[imsi].item[alpha-1][1]==0)
									{
										char item3[5];
										item3[0]=alpha;
										len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										mid2[imsi].item[alpha-1][0]=0;
										
									}
								}
								
								
								
								break;
								}
							case 6:
								{
									
									int fflag=0,fflag2=0;
									
									
									if(mid2[imsi].earing[0]==0)
									{
										
										fflag2=1;
										
										
										mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
										mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
										mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
										mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
										mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
										mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
										mid2[imsi].earing[0]=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].earing_number;
										mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
										mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
										mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
										mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
										mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
										mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
										
										
										
										exp_money(imsi,imsi);
										int sendmsg_byte=loginchr(imsi,sendmsg);
										len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
										retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
										
										
										// printf("���� ��  �ڵ�  : %d\n",fflag+49151);
										for(int i=0;i<26;i++)
										{
											
											
											// printf("%d ��° ������ : %d\n",i,mid2[imsi].item[i][0]);
											if(mid2[imsi].item[i][0]==fflag+49151)
											{
												// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
												mid2[imsi].item[i][1]++;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
											
											
											
											
											if(i!=26)
											{
												if(mid2[imsi].item[i][0]==0)
												{
													// printf("���ο� ���Կ� ������ �߰� \n");
													mid2[imsi].item[i][1]++;
													mid2[imsi].item[i][0]=fflag+49151;
													char item2[80];  // ������ ��Ͽ� �߱�
													char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
													char gae[]="��";
													char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
													itoa(mid2[imsi].item[i][1],msg2,10);
													
													// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
													strcpy(msg,item_st[fflag].name);
													item2[0]=i+1;
													item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
													item2[2]=( fflag+49151 & 0x000000ff ) ;
													item2[3]='\x00';
													item2[4]='\x20';
													strcpy(item2+5,msg); //������ �̸�
													item2[5+strlen(msg)]='\x20'; // ��ĭ���
													strcpy(item2+6+strlen(msg),msg2); //���� 
													strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
													item2[8+strlen(msg)+strlen(msg2)]='\x00';
													item2[9+strlen(msg)+strlen(msg2)]='\x00';
													item2[10+strlen(msg)+strlen(msg2)]='\x00';
													len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
													retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
													i=26;
												}
											}
											
											
											
										}
										
										
										
										
										
										
										
										mid2[imsi].item[alpha-1][1]--;
										
										
										
										
										char item2[80];  // ������ ��Ͽ� �߱�
										char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
										char gae[]="��";
										char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
										itoa(mid2[imsi].item[alpha-1][1],msg2,10);
										
										// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
										strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
										item2[0]=alpha;
										item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
										item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
										item2[3]='\x00';
										item2[4]='\x20';
										strcpy(item2+5,msg); //������ �̸�
										item2[5+strlen(msg)]='\x20'; // ��ĭ���
										strcpy(item2+6+strlen(msg),msg2); //���� 
										strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
										item2[8+strlen(msg)+strlen(msg2)]='\x00';
										item2[9+strlen(msg)+strlen(msg2)]='\x00';
										item2[10+strlen(msg)+strlen(msg2)]='\x00';
										len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										
										
										
										if(mid2[imsi].item[alpha-1][1]==0)
										{
											char item3[5];
											item3[0]=alpha;
											len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											mid2[imsi].item[alpha-1][0]=0;
											
										}
								}
								
								if(mid2[imsi].earing[1]==0 && fflag2==0)
								{
									fflag2=1;
									
									mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
									mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
									mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
									mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
									mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
									mid2[imsi].earing[1]=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].earing_number;
									mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
									mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
									mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
									mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
									mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
									
									
									
									exp_money(imsi,imsi);
									int sendmsg_byte=loginchr(imsi,sendmsg);
									len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									
									
									// printf("���� ��  �ڵ�  : %d\n",fflag+49151);
									for(int i=0;i<26;i++)
									{
										
										
										// printf("%d ��° ������ : %d\n",i,mid2[imsi].item[i][0]);
										if(mid2[imsi].item[i][0]==fflag+49151)
										{
											// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
											mid2[imsi].item[i][1]++;
											char item2[80];  // ������ ��Ͽ� �߱�
											char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											char gae[]="��";
											char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											itoa(mid2[imsi].item[i][1],msg2,10);
											
											// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
											strcpy(msg,item_st[fflag].name);
											item2[0]=i+1;
											item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
											item2[2]=( fflag+49151 & 0x000000ff ) ;
											item2[3]='\x00';
											item2[4]='\x20';
											strcpy(item2+5,msg); //������ �̸�
											item2[5+strlen(msg)]='\x20'; // ��ĭ���
											strcpy(item2+6+strlen(msg),msg2); //���� 
											strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
											item2[8+strlen(msg)+strlen(msg2)]='\x00';
											item2[9+strlen(msg)+strlen(msg2)]='\x00';
											item2[10+strlen(msg)+strlen(msg2)]='\x00';
											len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											i=26;
										}
										
										
										
										
										if(i!=26)
										{
											if(mid2[imsi].item[i][0]==0)
											{
												// printf("���ο� ���Կ� ������ �߰� \n");
												mid2[imsi].item[i][1]++;
												mid2[imsi].item[i][0]=fflag+49151;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
										}
										
										
										
									}
									
									
									
									
									
									
									
									mid2[imsi].item[alpha-1][1]--;
									
									
									
									
									char item2[80];  // ������ ��Ͽ� �߱�
									char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									char gae[]="��";
									char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									itoa(mid2[imsi].item[alpha-1][1],msg2,10);
									
									// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
									strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
									item2[0]=alpha;
									item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
									item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
									item2[3]='\x00';
									item2[4]='\x20';
									strcpy(item2+5,msg); //������ �̸�
									item2[5+strlen(msg)]='\x20'; // ��ĭ���
									strcpy(item2+6+strlen(msg),msg2); //���� 
									strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
									item2[8+strlen(msg)+strlen(msg2)]='\x00';
									item2[9+strlen(msg)+strlen(msg2)]='\x00';
									item2[10+strlen(msg)+strlen(msg2)]='\x00';
									len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									
									
									if(mid2[imsi].item[alpha-1][1]==0)
									{
										char item3[5];
										item3[0]=alpha;
										len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										mid2[imsi].item[alpha-1][0]=0;
										
									}
								}
								
								if(fflag2==0)
								{
									for(int k=0;k<2600;k++)
									{
										if(item_st[k].earing_number==mid2[imsi].earing[0])
										{
											fflag = k;
											k=2600;
										}
									}
									mid2[imsi].ac=mid2[imsi].ac-item_st[fflag].ac;
									mid2[imsi].max_hel=mid2[imsi].max_hel-item_st[fflag].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana-item_st[fflag].mana_up;
									mid2[imsi].him=mid2[imsi].him-item_st[fflag].him_up;
									mid2[imsi].min=mid2[imsi].him-item_st[fflag].min_up;
									mid2[imsi].ji=mid2[imsi].him-item_st[fflag].ji_up;
									mid2[imsi].earing[0]=item_st[mid2[imsi].item[(int)alpha-1][0]-49151].earing_number;
									mid2[imsi].max_hel=mid2[imsi].max_hel+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].hel_up;
									mid2[imsi].max_mana=mid2[imsi].max_mana+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].mana_up;
									mid2[imsi].min=mid2[imsi].min+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].min_up;
									mid2[imsi].ji=mid2[imsi].ji+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ji_up;
									mid2[imsi].him=mid2[imsi].him+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].him_up;
									mid2[imsi].ac=mid2[imsi].ac+item_st[mid2[imsi].item[(int)alpha-1][0]-49151].ac;
									
									
									
									exp_money(imsi,imsi);
									int sendmsg_byte=loginchr(imsi,sendmsg);
									len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
									retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									
									
									// printf("���� ��  �ڵ�  : %d\n",fflag+49151);
									for(int i=0;i<26;i++)
									{
										
										
										// printf("%d ��° ������ : %d\n",i,mid2[imsi].item[i][0]);
										if(mid2[imsi].item[i][0]==fflag+49151)
										{
											// printf("�̹� �������� �ֱ� ������ ���� �߰� \n");
											mid2[imsi].item[i][1]++;
											char item2[80];  // ������ ��Ͽ� �߱�
											char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											char gae[]="��";
											char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
											itoa(mid2[imsi].item[i][1],msg2,10);
											
											// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
											strcpy(msg,item_st[fflag].name);
											item2[0]=i+1;
											item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
											item2[2]=( fflag+49151 & 0x000000ff ) ;
											item2[3]='\x00';
											item2[4]='\x20';
											strcpy(item2+5,msg); //������ �̸�
											item2[5+strlen(msg)]='\x20'; // ��ĭ���
											strcpy(item2+6+strlen(msg),msg2); //���� 
											strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
											item2[8+strlen(msg)+strlen(msg2)]='\x00';
											item2[9+strlen(msg)+strlen(msg2)]='\x00';
											item2[10+strlen(msg)+strlen(msg2)]='\x00';
											len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
											retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
											i=26;
										}
										
										
										
										
										if(i!=26)
										{
											if(mid2[imsi].item[i][0]==0)
											{
												// printf("���ο� ���Կ� ������ �߰� \n");
												mid2[imsi].item[i][1]++;
												mid2[imsi].item[i][0]=fflag+49151;
												char item2[80];  // ������ ��Ͽ� �߱�
												char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												char gae[]="��";
												char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
												itoa(mid2[imsi].item[i][1],msg2,10);
												
												// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
												strcpy(msg,item_st[fflag].name);
												item2[0]=i+1;
												item2[1]=( fflag+49151 & 0x0000ff00 ) >> 8;
												item2[2]=( fflag+49151 & 0x000000ff ) ;
												item2[3]='\x00';
												item2[4]='\x20';
												strcpy(item2+5,msg); //������ �̸�
												item2[5+strlen(msg)]='\x20'; // ��ĭ���
												strcpy(item2+6+strlen(msg),msg2); //���� 
												strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
												item2[8+strlen(msg)+strlen(msg2)]='\x00';
												item2[9+strlen(msg)+strlen(msg2)]='\x00';
												item2[10+strlen(msg)+strlen(msg2)]='\x00';
												len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
												retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
												i=26;
											}
										}
										
										
										
									}
									
									
									
									
									
									
									
									mid2[imsi].item[alpha-1][1]--;
									
									
									
									
									char item2[80];  // ������ ��Ͽ� �߱�
									char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									char gae[]="��";
									char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
									itoa(mid2[imsi].item[alpha-1][1],msg2,10);
									
									// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
									strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
									item2[0]=alpha;
									item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
									item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
									item2[3]='\x00';
									item2[4]='\x20';
									strcpy(item2+5,msg); //������ �̸�
									item2[5+strlen(msg)]='\x20'; // ��ĭ���
									strcpy(item2+6+strlen(msg),msg2); //���� 
									strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
									item2[8+strlen(msg)+strlen(msg2)]='\x00';
									item2[9+strlen(msg)+strlen(msg2)]='\x00';
									item2[10+strlen(msg)+strlen(msg2)]='\x00';
									len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									
									
									
									if(mid2[imsi].item[alpha-1][1]==0)
									{
										char item3[5];
										item3[0]=alpha;
										len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
										retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
										mid2[imsi].item[alpha-1][0]=0;
										
									}
								}
								
								
								
								break;
								}
						case 7:
							{
								
								//printf("item_st[mid2[imsi].item[alpha-1][0]-49151]:%d\n",item_st[mid2[imsi].item[alpha-1][0]-49151].teleport[0]);
								mid2[imsi].hel=mid2[imsi].hel+item_st[mid2[imsi].item[alpha-1][0]-49151].food_hel_up;
								mid2[imsi].mana=mid2[imsi].mana+item_st[mid2[imsi].item[alpha-1][0]-49151].food_mana_up;
								if(mid2[imsi].hel>mid2[imsi].max_hel) mid2[imsi].hel=mid2[imsi].max_hel;
								if(mid2[imsi].mana>mid2[imsi].max_mana) mid2[imsi].mana=mid2[imsi].max_mana;
								exp_money(imsi,imsi);
								char sendmsg1[13];
								sendmsg1[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
								
								sendmsg1[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
								sendmsg1[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;								
								sendmsg1[3]=( mid2[imsi].thread & 0x000000ff ) ;								
								sendmsg1[4]=7;								
								sendmsg1[5]='\x00';								
								sendmsg1[6]='\x2e';
								sendmsg1[7]=0;	
								int len = Xc->Enc_Pack(imsi,sendmsg1,8,0x1a,1);
								for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										// printf(" %d��° �������� �������� ���� �ϴ¸���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										int retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									}
									else imsi_count++;
									
								}
								
								mid2[imsi].item[alpha-1][1]--;
								
								
								
								
								char item2[80];  // ������ ��Ͽ� �߱�
								char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								char gae[]="��";
								char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								itoa(mid2[imsi].item[alpha-1][1],msg2,10);
								
								// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
								strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
								item2[0]=alpha;
								item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
								item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
								item2[3]='\x00';
								item2[4]='\x20';
								strcpy(item2+5,msg); //������ �̸�
								item2[5+strlen(msg)]='\x20'; // ��ĭ���
								strcpy(item2+6+strlen(msg),msg2); //���� 
								strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
								item2[8+strlen(msg)+strlen(msg2)]='\x00';
								item2[9+strlen(msg)+strlen(msg2)]='\x00';
								item2[10+strlen(msg)+strlen(msg2)]='\x00';
								len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
								retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
								
								
								
								if(mid2[imsi].item[alpha-1][1]==0)
								{
									char item3[5];
									item3[0]=alpha;
									len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									mid2[imsi].item[alpha-1][0]=0;
									
								}
								
								
								
								
								break;
							}
						case 8:
							{
								
								if(mid2[imsi].realmap!=item_st[mid2[imsi].item[alpha-1][0]-49151].teleport[0])
									teleport(imsi,&kaflag,item_st[mid2[imsi].item[alpha-1][0]-49151].teleport[1],item_st[mid2[imsi].item[alpha-1][0]-49151].teleport[2],item_st[mid2[imsi].item[alpha-1][0]-49151].teleport[0]);
								else
								{
									mid2[imsi].map_x=item_st[mid2[imsi].item[alpha-1][0]-49151].teleport[1];
									mid2[imsi].map_y=item_st[mid2[imsi].item[alpha-1][0]-49151].teleport[2];
									ctrl_r(imsi);
								}
								
								mid2[imsi].item[alpha-1][1]--;
								
								
								
								
								char item2[80];  // ������ ��Ͽ� �߱�
								char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								char gae[]="��";
								char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								itoa(mid2[imsi].item[alpha-1][1],msg2,10);
								
								// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
								strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
								item2[0]=alpha;
								item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
								item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
								item2[3]='\x00';
								item2[4]='\x20';
								strcpy(item2+5,msg); //������ �̸�
								item2[5+strlen(msg)]='\x20'; // ��ĭ���
								strcpy(item2+6+strlen(msg),msg2); //���� 
								strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
								item2[8+strlen(msg)+strlen(msg2)]='\x00';
								item2[9+strlen(msg)+strlen(msg2)]='\x00';
								item2[10+strlen(msg)+strlen(msg2)]='\x00';
								len = Xc->Enc_Pack(imsi,item2,10+strlen(msg)+strlen(msg2),0x0f,1);
								retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
								
								
								
								if(mid2[imsi].item[alpha-1][1]==0)
								{
									char item3[5];
									item3[0]=alpha;
									len = Xc->Enc_Pack(imsi,item3,1,0x10,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									mid2[imsi].item[alpha-1][0]=0;
									
								}
								
								
								
								
								break;
							}
							
							
							}
							}
							else
							{
								int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
								int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
							}
							
							
							
					}
					
				
					
					if(buf[3]==0x2e) // #�׷��ϱ�
					{
						int len,retval;
						
						
						Xc->Dec_Pack(imsi,buf+2);
						// printf("%s\n",Messages[imsi]+1);
						int t=finduser_group(Messages[imsi]);
						if(mid2[imsi].group==-1)
						{
							len = Xc->Enc_Pack(imsi,"\x00\00\x2d������ �׷� �ź� Ǫ����.",60,0x0a,1);
							retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
						}
						else
						{
							if(t==0)
							{
								char len = Xc->Enc_Pack(imsi,"\x00\00\x2d���� ���������� �������� �ƴմϴ�.",60,0x0a,1);
								int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
								// printf("���������� �ʴٰ� ���� \n");
							}
							else   // �������̸� 
							{
								if(mid2[t].thread!=0 && t != imsi)
								{
									// printf("������ \n");
									if(mid2[t].group==0) // �׷� �� �̸�
									{
										
										// printf("���� �׷��\n");
										if( mid2[imsi].group==0) // ���� �ڽ��� �׷����� ��
										{
											
											mid2[imsi].group=imsi;
											mid2[t].group=imsi;
											len = Xc->Enc_Pack(imsi,"\x00\00\x2d�׷��߰� ����!!",60,0x0a,1);
											retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
											len = Xc->Enc_Pack(imsi,"\x00\00\x2d�׷�� �߰���",60,0x0a,1);
											retval = send(client[mid2[t].thread],Encrypted_Messages[imsi],len, 0);
											
										}
										else
										{
											
											// printf("mid2 : %d \n",mid2[imsi].group);
											mid2[t].group=mid2[imsi].group;
											
											
											len = Xc->Enc_Pack(imsi,"\x00\00\x2d�׷�� �߰���",60,0x0a,1);
											retval = send(client[mid2[t].thread],Encrypted_Messages[imsi],len, 0);
											
											len = Xc->Enc_Pack(imsi,"\x00\00\x2d�׷�� �߰� ����!!",60,0x0a,1);
											retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
											
										}
										
									}
									else
									{
										if(mid2[t].group==-1)
										{
											len = Xc->Enc_Pack(imsi,"\x00\00\x2d������ �׷� �ź���",60,0x0a,1);
											retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
											
										}
										else
										{
											len = Xc->Enc_Pack(imsi,"\x00\00\x2d�̹� �׷��� �Դϴ�.",60,0x0a,1);
											retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
										}								
									}
								}
								else
								{
									char len = Xc->Enc_Pack(imsi,"\x00\00\x2d�������� �ƴϰų� �ڱ��ڽŰ��� �Ұ���.",60,0x0a,1);
									int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
									// printf("���������� �ʴٰ� ���� \n");
								}
								
								
								
							}
						}
						
						
						
					}
					
					
					if(buf[3]==0x1b) // #�׷�ź�
					{
						
						
						int len,retval;
						Xc->Dec_Pack(imsi,buf+2);
						if(Messages[imsi][0]==2)
						{
							if(mid2[imsi].group==0)
							{
								mid2[imsi].group=-1;
								// printf("group : %d\n",mid2[imsi].group);
								// printf("imsi : %d\n",imsi);
								len = Xc->Enc_Pack(imsi,"\x03\00\x1a�׷� OFF",36,0x0a,1);
								retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
							}
							else
							{
								if(mid2[imsi].group==imsi)
								{
									int iii;
									int count=0,imsi_k=0;
									for(int k=0;k<frecnum;k++)
									{
										if(mid2[imsi].group==mid2[k].group)
										{
											if(k!=imsi) iii=k;
											
											count++;
											// printf("count : %d\n",count);
										}
									}
									
									for(int t=0,imsi_group=mid2[imsi].group;t<frecnum;t++)
									{
										// printf(" t = %d  group = %d\n",t,mid2[t].group);
										if(mid2[t].group==imsi_group)
										{
											// printf("aaa\n");
											imsi_k=t;
											// printf(" %d�� ���� �׷��� : %d\n",t,iii);
											mid2[t].group=iii;
										}
									}
									
									if(count==2) mid2[iii].group=0; //mid2[iii].group=0;
								}
								
								mid2[imsi].group=0;
								len = Xc->Enc_Pack(imsi,"\x03\00\x1a���� �׷� Ż���ϰ� �׷� ON",36,0x0a,1);
								retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
							}
						}
						
						
					}
					
					
					if((char)buf[3]==0x08) //#������
					{
						if(mid2[imsi].sangtae==0)
						{
							
							int len,retval;
							Xc->Dec_Pack(imsi,buf+2);
							int alpha = (int)Messages[imsi][0];
							// printf("alpha = %d\n",alpha);
							if(alpha>26) alpha=-1;
							
							
							if(mid2[imsi].item[alpha-1][1]>0)
							{
								char iim[20]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								itoa(mid2[imsi].item[alpha-1][0]-49151,iim+1,10);
								// printf("mid2[imsi].item[alpha-1][0]-49151 : %d\n",mid2[imsi].item[alpha-1][0]-49151);
								magic_05(imsi,iim);			
								mid2[imsi].item[alpha-1][1]--;
								
								
								
								
								char item2[80];  // ������ ��Ͽ� �߱�
								char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								char gae[]="��";
								char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
								itoa(mid2[imsi].item[alpha-1][1],msg2,10);
								
								// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
								strcpy(msg,item_st[mid2[imsi].item[alpha-1][0]-49151].name);
								memset(item2,0,80);
								int len2=sprintf(item2,"%c%c%c%c%c%s %d��",
									alpha,
									(mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8,
									(mid2[imsi].item[alpha-1][0] & 0x000000ff),
									0x00,
									0x20,
									item_st[mid2[imsi].item[alpha-1][0]-49151].name,
									mid2[imsi].item[alpha-1][1]
									);
								
								item2[0]=alpha;
								item2[1]=( mid2[imsi].item[alpha-1][0] & 0x0000ff00 ) >> 8;
								item2[2]=( mid2[imsi].item[alpha-1][0] & 0x000000ff ) ;
								/*
								item2[3]='\x00';
								item2[4]='\x20';
								strcpy(item2+5,msg); //������ �̸�
								item2[5+strlen(msg)]='\x20'; // ��ĭ���
								strcpy(item2+6+strlen(msg),msg2); //���� 
								strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
								item2[8+strlen(msg)+strlen(msg2)]='\x00';
								item2[9+strlen(msg)+strlen(msg2)]='\x00';
								item2[10+strlen(msg)+strlen(msg2)]='\x00';
								item2[11+strlen(msg)+strlen(msg2)]='\x00';
								item2[12+strlen(msg)+strlen(msg2)]='\x00';
								item2[13+strlen(msg)+strlen(msg2)]='\x00';*/
								len = Xc->Enc_Pack(imsi,item2,40,0x0f,1);
								retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
								if(mid2[imsi].item[alpha-1][1]==0)
								{
									char item3[5];
									item3[0]=alpha;
									item3[1]=1;
									len = Xc->Enc_Pack(imsi,item3,2,0x10,1);
									retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
									mid2[imsi].item[alpha-1][0]=0;
									mid2[imsi].item[alpha-1][1]=0;
									// printf("0���ϱ� ���� ���� \n");
								}
								
								
							}
						}
						else
						{
							int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
							int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
						}
					}
					
					
					
					
					
					
					
					
					if(buf[3]==0x43 && buf[2]==0x08)  // #���Ŭ��
					{
						int len,retval;
						Xc->Dec_Pack(imsi,buf+2);
						
						
						unsigned int asdf = 0;
						asdf = asdf + Messages[imsi][4];
						asdf = asdf + Messages[imsi][3]*256;
						asdf = asdf + Messages[imsi][2]*65536;
						asdf = asdf + Messages[imsi][1]*16777216;
						
						char cTmp[4]; 
						int unsigned iData; 
						
						// Little-Endian ó�� 
						// ��  0x000f4267 �� �޸𸮿� ����ɶ��� 0x67 0x42 0x0f 0x00 ������ ����ǹǷ� 
						cTmp[0] = Messages[imsi][4];
						cTmp[1] = Messages[imsi][3]; 
						cTmp[2] = Messages[imsi][2]; 
						cTmp[3] = Messages[imsi][1]; 
						
						memcpy(&asdf, cTmp, sizeof(cTmp)); 
						int imsi_chr=thread_imsi[asdf];
						
						//printf("���Ŭ�� : %d\n",asdf);
						
						
						
						int imsi_group=1;
						if(mid2[imsi_chr].group==-1)
							imsi_group=0;
						
						if(asdf<100000)
						{
							
							
							
							char msg[200];
							memset(msg,0,200);
							sprintf(msg,"%c%c%c%c%s%c%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
								0x00, // Īȣ
								0x00, // ����Īȣ
								0x00, // ����
								strlen(mid2[imsi_chr].job), // ����
								mid2[imsi_chr].job,
								strlen(mid2[imsi_chr].id),
								mid2[imsi_chr].id,
								0x00,
								0x00,
								mid2[imsi_chr].sangtae, // 1 �̸� �ͽ� ���� 2�� �������
								0x00,
								mid2[imsi_chr].head,
								mid2[imsi_chr].headcolor,
								mid2[imsi_chr].dress,
								mid2[imsi_chr].dresscolor,
								0x00,
								mid2[imsi_chr].sword,
								mid2[imsi_chr].swordcolor,
								mid2[imsi_chr].bangpae,
								mid2[imsi_chr].bangpaecolor,
								( mid2[imsi_chr].head_gear+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi_chr].head_gear+49151 & 0x000000ff ) ,
								0x00,
								( mid2[imsi_chr].ring[0]+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi_chr].ring[0]+49151 & 0x000000ff ) ,
								0x00,
								( mid2[imsi_chr].ring[1]+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi_chr].ring[1]+49151 & 0x000000ff ) ,
								0x00,
								( mid2[imsi_chr].earing[0]+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi_chr].earing[0]+49151 & 0x000000ff ) ,
								0x00,
								( mid2[imsi_chr].earing[1]+49151 & 0x0000ff00 ) >> 8,
								( mid2[imsi_chr].earing[1]+49151 & 0x000000ff ) ,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								imsi_group, // �׷� ��
								0x00,
								0x00,
								0x00,
								0x00,
								0x00,
								0x00);
							packet_dump(msg,60,16);
							len = Xc->Enc_Pack(imsi,msg,100,0x34,1);
							retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
						}
						
						
						
						
						
						
						
					}
					
					if((char)buf[3]==0x07)
					{
						int change_flag=0;
						char change_msg[100];
						if((char)mid2[imsi].change[0]!=0) 
						{
							change_flag=1;
							sprintf(change_msg,"��ȯ�� ���� �����Դϴ�. ��ȯ���¸� �����Ϸ��� F2�� �����ֽʽÿ�.");
							sangtae(imsi,change_msg);
						}
						else
							change_flag=0;
						if(mid2[imsi].sangtae==0 && change_flag==0)
						{
							Xc->Dec_Pack(imsi,buf+2);
							packet_dump(Messages[imsi],strlen(Messages[imsi]),16);
							int len,retval;
							int ss=(int)Messages[imsi][0];
							switch(ss)
							{
							default:
								{
									// printf("�Ѱ� �ݱ���Ŷ�� ����\n");
									char get22[9];
									get22[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
									get22[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
									get22[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
									get22[3]=( mid2[imsi].thread & 0x000000ff ) ;
									get22[4]='\x04';
									get22[5]='\x00';
									get22[6]='\x20';
									get22[7]='\x00';
									for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
									{
										if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
										{
											
											len = Xc->Enc_Pack(imsi,get22,8,0x1a,1);
											retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);
											
										}else {
											
											// printf("0 �̹Ƿ� imsi_count ����\n");
											imsi_count++;
										}
										
									}
									// printf("taijimap[mid2[imsi].realmap].item_count:%d\n",taijimap[mid2[imsi].realmap].item_count);
									
									for(int count=0,item_count=taijimap[mid2[imsi].realmap].item_count;count<item_count;count++)
									{
										// printf("thread:%d\n",taijimap[mid2[imsi].realmap].item_thread[count]);
										if(taijimap[mid2[imsi].realmap].item_thread[count] != 0)
										{
											
											if(taijimap[mid2[imsi].realmap].item_x[count]==mid2[imsi].map_x)
											{
												if(taijimap[mid2[imsi].realmap].item_y[count]==mid2[imsi].map_y)
												{
													
													
													int imsiflag=0;
													for(int i=0;i<26;i++) 
													{
														
														if(mid2[imsi].item[i][0]==taijimap[mid2[imsi].realmap].item_thread[count]) // �̹� �ִ� �������� ���
														{
															// printf("�̹� �ִ� ������\n");
															mid2[imsi].item[i][1]++;
															char item2[80];  // ������ ��Ͽ� �߱�
															memset(item2,0,80);
															char msg[30];
															memset(msg,0,30);
															char gae[]="��";
															char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
															itoa(mid2[imsi].item[i][1],msg2,10);
															
															itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
															strcpy(msg,item_st[taijimap[mid2[imsi].realmap].item_thread[count]-49151].name);
															
															int len2=sprintf(item2,"%c%c%c%c%c%s %d��",
																i+1,
																taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 >> 8,
																taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff,
																0x00,
																0x20,
																item_st[taijimap[mid2[imsi].realmap].item_thread[count]-49151].name,
																mid2[imsi].item[i][1]
																);
															item2[1]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
															item2[2]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
															
															/*
															
															  
																
																  item2[0]=i+1;
																  item2[1]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
																  item2[2]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
																  item2[3]='\x00';
																  item2[4]='\x20';
																  strcpy(item2+5,msg); //������ �̸�
																  item2[5+strlen(msg)]='\x20'; // ��ĭ���
																  strcpy(item2+6+strlen(msg),msg2); //���� 
																  strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
																  item2[8+strlen(msg)+strlen(msg2)]='\x00';
																  item2[9+strlen(msg)+strlen(msg2)]='\x00';
																  item2[10+strlen(msg)+strlen(msg2)]='\x00';
																  item2[11+strlen(msg)+strlen(msg2)]='\x00';
																  item2[12+strlen(msg)+strlen(msg2)]='\x00';
																  item2[13+strlen(msg)+strlen(msg2)]='\x00';
															item2[14+strlen(msg)+strlen(msg2)]='\x00';*/
															len = Xc->Enc_Pack(imsi,item2,60,0x0f,1);
															retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
															imsiflag=1;
															mid2[imsi].item[i][0]=taijimap[mid2[imsi].realmap].item_thread[count];
															
															
															
															taijimap[mid2[imsi].realmap].item_thread[count]=0; //������ ������� �κ�
															taijimap[mid2[imsi].realmap].item_count--;
															int item_number=49153;
															char item[19];
															item[0]='\x00';
															item[1]='\x01';
															item[2]='\x00';
															item[3]=mid2[imsi].map_x;
															item[4]='\x00';
															item[5]=mid2[imsi].map_y;
															item[6]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x0000ff00 ) >> 8;
															item[7]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x000000ff ) ;
															item[8]='\x00';
															item[9]='\x00';
															item[10]=0;
															item[11]=0;
															item[12]='\x00';
															
															len = Xc->Enc_Pack(imsi,item,13,0x07,1);
															for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
															{
																if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
																{
																	// printf(" %d��° �������� �������� ������ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
																	retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
																}
																else imsi_count++;
																
															}
															
															
															i = 26;
														}
													}
													
													
													if(imsiflag==0)
													{
														for(int i=0;i<26;i++) 
														{
															if(mid2[imsi].item[i][0]==0) // ���ο� �������� ���
															{
																// printf("�� ������\n");
																mid2[imsi].item[i][1]=0;
																mid2[imsi].item[i][1]++;
																char item2[80];  // ������ ��Ͽ� �߱�
																memset(item2,0,80);
																char msg[30];
																memset(msg,0,30);
																char gae[]="��";
																char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
																int len2=sprintf(item2,"%c%c%c%c%c%s",
																	i+1,
																	taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 >> 8,
																	taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff,
																	0x00,
																	0x20,
																	item_st[taijimap[mid2[imsi].realmap].item_thread[count]-49151].name);
																item2[1]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
																item2[2]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
																/*
																
																  
																	
																	  itoa(mid2[imsi].item[i][1],msg2,10);
																	  
																		itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
																		strcpy(msg,item_st[taijimap[mid2[imsi].realmap].item_thread[count]-49151].name);
																		item2[0]=i+1;
																		item2[1]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
																		item2[2]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
																		item2[3]='\x00';
																		item2[4]='\x20';
																		strcpy(item2+5,msg); //������ �̸�
																		item2[5+strlen(msg)]='\x20'; // ��ĭ���
																		strcpy(item2+6+strlen(msg),msg2); //���� 
																		strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
																		item2[8+strlen(msg)+strlen(msg2)]='\x00';
																		item2[9+strlen(msg)+strlen(msg2)]='\x00';
																		item2[10+strlen(msg)+strlen(msg2)]='\x00';
																		item2[11+strlen(msg)+strlen(msg2)]='\x00';
																		item2[12+strlen(msg)+strlen(msg2)]='\x00';
																		item2[13+strlen(msg)+strlen(msg2)]='\x00';
																item2[14+strlen(msg)+strlen(msg2)]='\x00';*/
																
																len = Xc->Enc_Pack(imsi,item2,60,0x0f,1);
																retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
																mid2[imsi].item[i][0]=taijimap[mid2[imsi].realmap].item_thread[count];
																
																taijimap[mid2[imsi].realmap].item_thread[count]=0;  // ������ ������� �κ�
																taijimap[mid2[imsi].realmap].item_count--;
																int item_number=49153;
																char item[19];
																item[0]='\x00';
																item[1]='\x01';
																item[2]='\x00';
																item[3]=mid2[imsi].map_x;
																item[4]='\x00';
																item[5]=mid2[imsi].map_y;
																item[6]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x0000ff00 ) >> 8;
																item[7]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x000000ff ) ;
																item[8]='\x00';
																item[9]='\x00';
																item[10]=0;
																item[11]=0;
																item[12]='\x00';
																
																len = Xc->Enc_Pack(imsi,item,13,0x07,1);
																for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
																{
																	if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
																	{
																		// printf(" %d��° �������� �������� ������ ����.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
																		retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
																	}
																	else imsi_count++;
																	
																}
																
																
																i = 26;
															}
															
															
														}count=item_count;
														
														
														
													}
													
													
													
								}
							}
						}
						
						
						else 
						{
							
							// printf("0 �̹Ƿ� item_count ����\n");
							item_count++;
							// printf("itemcount=%d\n",item_count);
							// printf("count=%d\n",count);
						}
						
					}
					// printf("taijimap[mid2[imsi].realmap].item_count:%d\n",taijimap[mid2[imsi].realmap].item_count);
					break;
					}
					
					}
					}
					
					else
					{
						if(mid2[imsi].sangtae!=0)
						{
							int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
							int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
						}
					}
					
					
					
					
					
					}
					
					
					if((char)buf[3]==0x1d) // ǥ�� ����
					{
						if(mid2[imsi].sangtae==0)
						{
							int len,retval;
							char peer0_2[] = {
								
								0x0a, 0x1a, 0x06, 0x48, 0x63, 0x7e, 
									
									0x08, 0x65, 0x4f, 0x26, 0x65 };
								Xc->Dec_Pack(imsi,buf+2);
								packet_dump(Messages[imsi],10,16);
								char ttt[1];
								strncpy(ttt,Messages[imsi],1);
								packet_dump(ttt,1,1);
								int kkk=(int)ttt[0]+11;
								// printf("%d\n",kkk);
								
								
								char imo[7];
								imo[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
								imo[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
								imo[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
								imo[3]=( mid2[imsi].thread & 0x000000ff ) ;
								imo[4]=kkk;
								imo[5]='\x00';
								imo[6]='\x4e';
								
								for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										
										len = Xc->Enc_Pack(imsi,imo,7,0x1a,1);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);
										
									}
									else {
										
										// printf("0 �̹Ƿ� imsi_count ����\n");
										imsi_count++;
									}
									
								}	
								
								
								//Xc->Dec_Pack(imsi,peer0_2);
								packet_dump(Messages[imsi],16,16);
						}
						
						
						else
						{
							int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
							int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
						}
						
						
					}
					if((char)buf[3]==0x0b)  //#��Ʈ����
					{
						
						//EnterCriticalSection(&port);
						Xc->Dec_Pack(imsi,buf+2);
						if(Messages[imsi][0]==0)
						{
							if(mapflag==0)  // �ѹ��̶� �α��� �����ߴٸ�
							{
								
								char sendmsg2[20];
								sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
								sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
								sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
								sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
								sendmsg2[4]='\x00';
								
								
								
								
								for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									
									
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										
										
										int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
										// printf("len = %d\n",len);
										packet_dump(sendmsg2,5,16);
										packet_dump(Encrypted_Messages[imsi],10,16);
										// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
										
										
									}else {
										
										// printf("0 �̹Ƿ� imsi_count ����\n");
										imsi_count++;
									}
								}
								
								
								mid2[imsi].thread=0;
								mid2[imsi].group=0;
								mid[imsi]=mid2[imsi]; // ����Ÿ �簻��
								//fwrite();
								
							}
							
							
							// // printf("taijimap[mid[imsi].realmap].count = %d\n",taijimap[mid[imsi].realmap].count);
							
							
							
							if(mapflag==0)  // �ʻ󿡼� ������� �κ�
							{
								
								taijimap[mid2[imsi].realmap].count--;
								taijimap[mid2[imsi].realmap].threadlist[mid2[imsi].kaflag]=0;
								taijimap[mid2[imsi].realmap].chrnumber[mid2[imsi].kaflag]=0;
								
								//	taijimap[mid2[imsi].realmap].count--;
							}
							
							
						}
						//LeaveCriticalSection(&port);
						closesocket(client[socketnow]);
						struct tm *systime; 
						time_t t;
						t = time(NULL);
						systime = localtime(&t);
						struct tm *clock;
						time_t current;						time(& current); //���� �ð��� ��� ���� �Լ�
						
						clock=localtime(& current); //���� �ð��� ��,��,�ʷ� ���� �ϴ� �ռ�
						
						
						//printf("%.2d�� %.2d�� %.2d�� ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d ID:%s\n",clock->tm_hour,clock->tm_min,clock->tm_sec,inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port),mid[imsi].id);
						char con[]="����";
						//log(mid[imsi].id,inet_ntoa(clientaddr.sin_addr),con);
						mapflag=1;
						
						
					}
					
					
					
					
					
					if((char)buf[3]==0x13)
					{
						if(mid2[imsi].sangtae==0)
						{
							int len;
							// printf("������ ��Ŷ�� �޾ҽ��ϴ�.\n");
							//Sleep(100);
							
							char attack2[15];
							attack2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
							attack2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
							attack2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
							attack2[3]=( mid2[imsi].thread & 0x000000ff ) ;
							attack2[4]='\x01';
							attack2[5]='\x00';
							attack2[6]='\x14';
							attack2[7]='\x00';
							attack2[8]='\x09';
							
							attack(imsi,socketnow);
							
							for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
							{
								if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
								{
									
									len = Xc->Enc_Pack(imsi,attack2,9,0x1a,1);
									// printf(" %s ���� �ֵθ��� ����\n",mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].id);
									if(	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x < mid2[imsi].map_x+17 
										&& mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x > mid2[imsi].map_x-17 
										&&	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y < mid2[imsi].map_y+17 
										&& mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y > mid2[imsi].map_y-17) 
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0); 
									
								}else {
									
									// printf("0 �̹Ƿ� imsi_count ����\n");
									imsi_count++;
								}
								
							}
							// printf("0��° : %d\n",taijimap[14].threadlist[0]);
							
						}
						
						else
						{
							int len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ͽ��� �Ҽ� �����ϴ�.",36,0x0a,1);
							int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
						}
						
						
						
					}
					if((char)buf[3]==0x18) //#����ں���
					{
						int now_time;
						now_time=st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400;
						int mal_delay=0;
						if(now_time>last_time)
						{
							Xc->Dec_Pack(imsi,buf+2);
							if(Messages[imsi][0]==0)
							{
								//Sleep(100);
								
								// printf("����ں���\n");
								int user_count=0;
								char item_msg[30];
								sprintf(item_msg,"%c%c%c%s",0x03,0x00,0x1a,"���� ����� ���");
								int len = Xc->Enc_Pack(imsi,item_msg,50,0x0a,1);
								int retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
								for(int i=0;i<frecnum;i++)
								{
									if(mid2[i].thread!=0)
									{
										char item_msg[30];
										memset(item_msg,0,30);
										sprintf(item_msg,"%s",mid2[i].id);
										sangtae(imsi,item_msg);
										//len = Xc->Enc_Pack(imsi,item_msg,40,0x0a,1);
										
										//retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
										user_count++;
									}
								}
								sprintf(item_msg,"%c%c%c%s%d%s",0x03,0x00,0x1a,"��",user_count,"�� ������");
								len = Xc->Enc_Pack(imsi,item_msg,40,0x0a,1);
								retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);
								
								
								
								/*char msg[2000];
								
								  msg[0]=( user_count & 0x0000ff00 ) >> 8;
								  msg[1]=( user_count & 0x000000ff ) ;
								  msg[2]=( user_count & 0x0000ff00 ) >> 8;
								  msg[3]=( user_count & 0x000000ff ) ;
								  msg[4]='\x00';
								  for(int k=0,msg_count=5;k<frecnum;k++)
								  {
								  if(mid2[k].thread!=0)
								  {
								  msg[msg_count]='\x10';
								  msg_count++;
								  msg[msg_count]='\x00';
								  msg_count++;
								  msg[msg_count]='\x8f';
								  msg_count++;
								  msg[msg_count]=strlen(mid2[k].id);
								  msg_count++;
								  strncpy(msg+msg_count,mid2[k].id,strlen(mid2[k].id));
								  msg_count=msg_count+strlen(mid2[k].id);
								  }
								  
									}
									
									  int len = Xc->Enc_Pack(imsi,msg,msg_count,0x36,1);
									  packet_dump(msg,50,16);
									  // printf("len : %d\n",len);
									  int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									  
										
								*/
								last_time=st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400;	
							}
							
							
						}
						
						
					}
					
					
					
					if((char)buf[3]==0x0e)  //#���ϱ�
					{
						int now_time;
						GetLocalTime( &st ); 
						now_time=st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400;
						int mal_delay=0;
						if(now_time>last_time)
						{
							
							
							if(strcmp(Messages[imsi]+2,"�Ծ�")==0)
							{
								if(mapflag==0)  // �ѹ��̶� �α��� �����ߴٸ�
								{
									
									char sendmsg2[20];
									sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
									sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
									sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
									sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
									sendmsg2[4]='\x00';
									
									
									
									
									for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
									{
										
										
										if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
										{
											
											
											int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
											// printf("len = %d\n",len);
											packet_dump(sendmsg2,5,16);
											packet_dump(Encrypted_Messages[imsi],10,16);
											// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
											retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
											
											
										}else {
											
											// printf("0 �̹Ƿ� imsi_count ����\n");
											imsi_count++;
										}
									}
									
									
									mid2[imsi].thread=0;
									mid2[imsi].group=0;
									mid[imsi]=mid2[imsi]; // ����Ÿ �簻��
									//fwrite();
									
								}
								
								
								// // printf("taijimap[mid[imsi].realmap].count = %d\n",taijimap[mid[imsi].realmap].count);
								
								
								
								if(mapflag==0)  // �ʻ󿡼� ������� �κ�
								{
									
									taijimap[mid2[imsi].realmap].count--;
									taijimap[mid2[imsi].realmap].threadlist[mid2[imsi].kaflag]=0;
									taijimap[mid2[imsi].realmap].chrnumber[mid2[imsi].kaflag]=0;
									
									//	taijimap[mid2[imsi].realmap].count--;
								}
								
								
								
								//LeaveCriticalSection(&port);
								closesocket(client[socketnow]);
								struct tm *systime; 
								time_t t;
								t = time(NULL);
								systime = localtime(&t);
								struct tm *clock;
								time_t current;						time(& current); //���� �ð��� ��� ���� �Լ�
								
								clock=localtime(& current); //���� �ð��� ��,��,�ʷ� ���� �ϴ� �ռ�
								
								
								//printf("%.2d�� %.2d�� %.2d�� ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d ID:%s\n",clock->tm_hour,clock->tm_min,clock->tm_sec,inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port),mid[imsi].id);
								char con[]="����";
								//log(mid[imsi].id,inet_ntoa(clientaddr.sin_addr),con);
								mapflag=1;
								
								
							}
							
							char sendmsg[100];
							memset(sendmsg,0,100);
							// printf("���ϱ� ��Ŷ�� �޾ҽ��ϴ�. imsi=%d\n",imsi);
							
							Xc->Dec_Pack(imsi,buf+2);
							// printf("%s : %s \n",mid2[imsi].id,Messages[imsi]+2);
							sendmsg[0] = '\x00';
							sendmsg[1] = ( mid2[imsi].thread & 0xff000000 ) >> 24;
							sendmsg[2] = ( mid2[imsi].thread & 0x00ff0000 ) >> 16;
							sendmsg[3] = ( mid2[imsi].thread & 0x0000ff00 ) >> 8;
							sendmsg[4] = ( mid2[imsi].thread & 0x000000ff ) ;
							sendmsg[5] = strlen(Messages[imsi]+2)+2+strlen(mid2[imsi].id);
							memcpy(sendmsg+6,mid2[imsi].id,strlen(mid2[imsi].id));
							sendmsg[6+strlen(mid2[imsi].id)] = '\x3a';
							sendmsg[7+strlen(mid2[imsi].id)] = '\x20';
							strcpy(sendmsg+8+strlen(mid2[imsi].id),Messages[imsi]+2);
							
							
							
							packet_dump(sendmsg,60,16);
							int len = Xc->Enc_Pack(imsi,sendmsg,strlen(Messages[imsi]+2)+2+strlen(mid2[imsi].id)+10,0x0d,1);
							// printf("imsi = %d \n",imsi);
							
							for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
							{
								
								if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
								{
									// printf(" %d��° �������� �������� ���� �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
									if(	mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x < mid2[imsi].map_x+17 &&
										mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_x > mid2[imsi].map_x-17 &&
										mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y < mid2[imsi].map_y+17 &&
										mid2[taijimap[mid2[imsi].realmap].chrnumber[mapcount]].map_y > mid2[imsi].map_y-17)
										
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
									//	printf("���۷�:%d\n",retval);
								}else {
									
									// printf("0 �̹Ƿ� imsi_count ����\n");
									imsi_count++;
								}
							}
							msg_check(imsi,Messages[imsi]+2);
							//Sleep(50);
							
							last_time=st.wSecond + st.wMinute*60 + st.wHour*3600 + st.wDay*86400;	
						}
						
						
						
						
					}
					
					
					if((char)buf[3]==0x19) //#�ӼӸ�
					{
						//printf("imsi:%d\n",imsi);
						//printf("thread:%d\n",mid2[imsi].thread);
						
						if(mid2[imsi].thread==0)
						{
							closesocket(client[socketnow]);
							return 0;
						}
						
						char sendmsg[500];
						memset(sendmsg,0,500);
						// printf("�ӼӸ��� ������ ��Ŷ\n");
						
						Xc->Dec_Pack(imsi,buf+2);
						
						
						int t=finduser(Messages[imsi],imsi);
						int len,retval;
						// printf(" �ҷ��� ������ = %d\n",t);
						if(t==-2)
						{
							if(mapflag==0)  // �ѹ��̶� �α��� �����ߴٸ�
							{
								
								char sendmsg2[20];
								sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
								sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
								sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
								sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
								sendmsg2[4]='\x00';
								
								
								
								
								for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
								{
									
									
									if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
									{
										
										
										int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
										// printf("len = %d\n",len);
										packet_dump(sendmsg2,5,16);
										packet_dump(Encrypted_Messages[imsi],10,16);
										// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
										retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
										
										
									}else {
										
										// printf("0 �̹Ƿ� imsi_count ����\n");
										imsi_count++;
									}
								}
								
								
								mid2[imsi].thread=0;
								mid2[imsi].group=0;
								mid[imsi]=mid2[imsi]; // ����Ÿ �簻��
								//fwrite();
								
							}
							
							
							// // printf("taijimap[mid[imsi].realmap].count = %d\n",taijimap[mid[imsi].realmap].count);
							
							
							
							if(mapflag==0)  // �ʻ󿡼� ������� �κ�
							{
								
								taijimap[mid2[imsi].realmap].count--;
								taijimap[mid2[imsi].realmap].threadlist[mid2[imsi].kaflag]=0;
								taijimap[mid2[imsi].realmap].chrnumber[mid2[imsi].kaflag]=0;
								
								//	taijimap[mid2[imsi].realmap].count--;
							}
							
							
							
							//LeaveCriticalSection(&port);
							closesocket(client[socketnow]);
							struct tm *systime; 
							time_t t;
							t = time(NULL);
							systime = localtime(&t);
							struct tm *clock;
							time_t current;						time(& current); //���� �ð��� ��� ���� �Լ�
							
							clock=localtime(& current); //���� �ð��� ��,��,�ʷ� ���� �ϴ� �ռ�
							
							
							//printf("%.2d�� %.2d�� %.2d�� ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d ID:%s\n",clock->tm_hour,clock->tm_min,clock->tm_sec,inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port),mid[imsi].id);
							char con[]="����";
							//log(mid[imsi].id,inet_ntoa(clientaddr.sin_addr),con);
							mapflag=1;
						}
						if(t==-1)
						{
							len = Xc->Enc_Pack(imsi,"\x00\00\x2d## ��ڿ��� �޽����� ���½��ϴ�.",60,0x0a,1);
							retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
							
						}
						else
						{
							
							
							
							
							
							if(t==0)
							{
								len = Xc->Enc_Pack(imsi,"\x00\00\x2d���� ���������� �������� �ƴմϴ�.",60,0x0a,1);
								retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
								// printf("���������� �ʴٰ� ���� \n");
							}
							else   // �������̸� 
							{
								if(t!=-3)
								{
									char k=gmsg2(Messages[imsi],sendmsg);
									int len = Xc->Enc_Pack(imsi,sendmsg,100,0x0a,1);   ///  ������ �޾Ƹ�// ���̵�� ���� ���̵��
									int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
									// printf("retval = %d \n",retval);
									// k=gmsg(Messages[imsi],sendmsg);
									k=gmsg(mid2[imsi].id,Messages[imsi],sendmsg);;    /// �޽����� ���� �����
									len = Xc->Enc_Pack(imsi,sendmsg,100,0x0a,1);
									retval = send(client[t],Encrypted_Messages[imsi],len, 0);
								}
								
							}
						}
					}
					
					
					
					
					
					
					
					char peer0_2[] = {  // ���� Ȯ���ϴ� �κ� 
						0xaa, 0x00, 0x07, 0x62, 0x00, 0x2f, 0x17, 0x19, 
							0x02, 0x6e };
						int test = strc(buf,peer0_2,10);
						// // printf("strcmp ���� %d\n" , test);
						
						if(test==0)   //  ���� ���ϰ� �ҷ��� �ּ� ����
						{
							closesocket(client[socketnow]);
						}
						
						
						
						
						/*if(bong_client==2)
						{
						char peer0_3[] = {
						0xaa, 0x00, 0x07, 0x62};
						test = strc(buf,peer0_3,4);
						// // printf("strcmp ���� %d\n" , test);
						
						  
							if(test==0)
							{
							
							  
								Xc->Dec_Pack(imsi,buf+2);
								char recon[4];
								recon[0]='\x61';
								recon[1]='\x72';
								recon[2]='\x61';
								recon[3]='\x6d';
								printf("%2x",Messages[imsi][0]);
								printf("%2x",Messages[imsi][1]);
								printf("%2x",Messages[imsi][2]);
								printf("%2x",Messages[imsi][3]);
								if(strc(Messages[imsi],recon,4)==0)
								closesocket(client[socketnow]);
								
								  }
						}*/
						
						
						
						// �ڵ� ���ܳ�Ʈ //
						
						char testpeer02[] = {0x02}; // #�̾��ϱ� ���� Ȯ���ϴ� ��Ŷ
						char testpeer03[] = {0x03};
						test = strc(buf+3,testpeer02,1);
						if(test==0)
						{
							
							if(add_count>2)
							{
								closesocket(client[socketnow]);
								return 0;
								
								
							}
							add_count++;
							
							
							if(frecnum>max_id)
							{
								char login_max[50];
								memset(login_max,0,50);
								sprintf(login_max,"%c%c��ڰ� ������� �����س���");
								int len = Xc->Enc_Pack(imsi,login_max,50,0x02,1);
								int retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
							}
							else
							{
								//if(frecnum>max_id)
								
								// printf("\n �����ϱ� ��Ŷ �Դϴ�. \n");
								
								Xc->Dec_Pack(imsi,buf+2);
								// printf("����ڰ� ���� ���̵� ��ȣ\n");
								// printf("==================\n");
								packet_dump(Messages[imsi],strlen(Messages[imsi]),16);
								// printf("==================\n");
								
								
								
								if(loginfile(Messages[imsi])==1)
									
								{
									char peer1_4[] = {
										0xaa, 0x00, 0x1b, 0x02, 0x00, 0x4d, 0x72, 0xb9, 
											0xd7, 0xae, 0xae, 0xa9, 0xac, 0x9a, 0x8d, 0x44, 
											0xc7, 0xa8, 0xaf, 0x84, 0xda, 0x92, 0x0f, 0x8c, 
											0xb3, 0xce, 0xa2, 0xd8, 0x92, 0x42 };
										// �����ϴ� ���̵� �Դϴ�.
										retval = send(client[socketnow], peer1_4, 30, 0);
										if(retval == SOCKET_ERROR)
										{
											err_display("send()");
											break;
										}	
										
								}
								
								
								else  // else�� ���� ����� �ϼ�!!
								{
									char peer1_4[] = {
										0xaa, 0x00, 0x1b, 0x02, 0x01, 0x4f, 0x73, 0xb9, 
											0xa2, 0xd1, 0xa6, 0xa8, 0xad, 0x9e, 0xad, 0xdc, 
											0xdf, 0x4e, 0xdb, 0xe5, 0xd8, 0xcd, 0x0f, 0x8c, 
											0xb0, 0xc7, 0xd0, 0xd2, 0xae, 0x43  };
										// �ؽ� �޽��� �˾�
										retval = send(client[socketnow], peer1_4, 30, 0);
										// printf("���� ��Ŷ ��ٸ��� ����\n");
										if(retval = recv(client[socketnow], buf, 50, 0)){
											// printf("���� ��Ŷ ��ٸ�����\n");
											if((char)buf[3]==0x04) // �Ӹ�����
											{
												EnterCriticalSection(&id);
												Xc->Dec_Pack(imsi,buf+2);
												
												//file_read();
												mid2[frecnum-1].head=Messages[imsi][0];
												//fwrite();
												LeaveCriticalSection(&id);
												
												
											}
										}
										char login2[] = {
											0xaa, 0x00, 0x1b, 0x02, 0x03, 0x4d, 0x71, 0xbb, 
												0xa0, 0xd3, 0xa4, 0xaa, 0xaf, 0x9c, 0xae, 0xdf, 
												0xdc, 0x4d, 0xd8, 0xe6, 0xdb, 0xce, 0x0c, 0x8e, 
												0xb2, 0xc5, 0xd2, 0xd0, 0xac, 0x41  };
											// �̾��ϱ� �ϼ���.
											retval = send(client[socketnow], login2, 30, 0);
								}
							}
							
							
							
							
						}
						
						test = strc(buf+3,testpeer03,1);
						if(test == 0)
						{
							
							
							nowcheck=1;
							// printf("\n �̾��ϱ� ��Ŷ �Դϴ�. \n");
							//printf("�α�κ��� taijimap[41].count=%d\n",taijimap[41].count);
							
							Xc->Dec_Pack(imsi,buf+2);
							// printf("����ڰ� ���� ���̵� ��ȣ\n");
							// printf("==================\n");
							packet_dump(Messages[imsi],strlen(Messages[imsi]),16);
							// printf("==================\n");
							imsi=loginfile2(Messages[imsi]);
							
							
							if(imsi==0)  // ����� ���̵� ��ġ���� ���� 
							{
								
								// printf("��ġ���� �ʴ� �ٴ� �޽��� \n");
								char noilchi[] = {
									0xaa ,0x00 ,0x1b ,0x02 ,0x00 ,0x4d ,0x6a ,0xc6 ,0xa9 ,0xae ,0x85 ,0xdb ,0x93 ,0x01 ,0xf5 ,0x95 ,0xc0 ,0x96 ,0xdb ,0x91 ,0xd7 ,0xc5 ,0x0f ,0x6c ,0x47 ,0x5a ,0x4d ,0x4c ,0x6b ,0x4c ,0x61 ,0x2c ,0x4d ,0x66 ,0x7b ,0x6c ,0x6d ,0x4a ,0x6d ,0x60 ,0x2d ,0x4a ,0x61 ,0x7c ,0x6b ,0x6a ,0x4d };
									retval = send(client[socketnow],noilchi, 30, 0);
							}
							else        // ����� ���̵� ��ġ������ ���ڵ� ����
							{
								
								imsi=imsi-1;
								if(mid2[imsi].thread>0)
								{
									// printf("��ġ���� �ʴ� �ٴ� �޽����� ������ ���� �������� \n");
									char noilchi[] = {
										0xaa ,0x00 ,0x16 ,0x02 ,0x00 ,0x4d ,0x6a ,0xb8 ,0xa3 ,0xd7 ,0x85 ,0x4e ,0xa2 ,0x8c ,0xf3 ,0xb7
											,0xb8 ,0xb1 ,0x6f ,0x48 ,0x6f ,0x62 ,0x2f ,0x4c ,0x67};
										retval = send(client[socketnow],noilchi, 25, 0);
										
										// ����Ÿ �簻��
										//fwrite();
										closesocket(client[mid2[imsi].thread]);
										mid2[imsi].thread=0;
										
										//taijimap[mid2[imsi].realmap].count--;
										/*taijimap[mid2[imsi].realmap].threadlist[mid2[imsi].kaflag]=0;
										taijimap[mid2[imsi].realmap].chrnumber[mid2[imsi].kaflag]=0;
										
										  // ����Ÿ �簻��
										  mid2[imsi].thread=0;
										  mid2[imsi].group=0;
										  mid[imsi]=mid2[imsi];
										printf("�α׾ƿ� ��Ű�� taijimapcount :%d\n",taijimap[mid2[imsi].realmap].count);*/
										//fwrite();
										
										
								}
								else
								{
									//printf("�α����� taijimap[41].count=%d\n",taijimap[41].count);
									
									// printf("���̵� ��� ��� ��Ȯ , %d ��° ���ڵ�\n",imsi); // ���ڵ� ��ȣ�� ������ ��ȣ����
									//printf("���ӽ� frecnum:%d\n",frecnum);
									//printf("���ӽ� imsi:%d\n",imsi);
									imsi=imsi_plus+imsi;
									mid2[imsi].im_si=imsi;
									// printf("���̵� : %s\n��� : %s\n���� :%d \nü�� :%d \n���� :%d \n",mid[imsi].id,mid[imsi].pass,mid[imsi].level,mid[imsi].hel,mid[imsi].mana);
									// printf("����ġ : %d\n",mid[imsi].exp);
									// printf("�� : %d\n",mid[imsi].money);
									// printf("x��ǥ : %d\n",mid[imsi].map_x);
									// printf("y��ǥ : %d\n",mid[imsi].map_y);
									// printf("���� �� : %d\n",mid[imsi].realmap);
									// printf("�� : %d\n",mid[imsi].him);
									// printf("�� : %d\n",mid[imsi].min);
									// printf("�� : %d\n",mid[imsi].ji);
									mid2[imsi].thread=socketnow;  // �ӽÿ� ������ ���� 
									// printf("������ : %d\n",mid[imsi].thread);
									//fwrite();  // ������ ���ε���
									// // printf("taijimap[mid[imsi].realmap].count = %d\n",taijimap[mid[imsi].realmap].count);
									//mid2[imsi]=mid[imsi];   // mid2�� mid����Ÿ ����
									thread_imsi[socketnow]=imsi;
									//printf("map:%d\n",taijimap[mid2[imsi].realmap].map_x_len);
									
									if(taijimap[mid2[imsi].realmap].map_x_len==0) mid2[imsi].realmap=15;
									//printf("�ٲ��� ��:%d\n",mid2[imsi].realmap);
									if(mid2[imsi].map_x<0 || mid2[imsi].map_x>taijimap[mid2[imsi].realmap].map_x_len)
										mid2[imsi].map_x=7;
									if(mid2[imsi].map_y<0 || mid2[imsi].map_y>taijimap[mid2[imsi].realmap].map_y_len)
										mid2[imsi].map_y=7;
									
									
									
									
									//printf("taijimapcount :%d\n",taijimap[mid2[imsi].realmap].count);
									taijimap[mid2[imsi].realmap].count++;
									//printf("realmap:%d\n",mid2[imsi].realmap);
									//printf("taijimapcount :%d\n",taijimap[mid2[imsi].realmap].count);
									
									// // printf("taijimap[mid[imsi].realmap].count = %d\n",taijimap[mid[imsi].realmap].count);
									// printf("���� %d�� �ʿ� �ִ� ����� : %d (�ڽ�����)\n", mid[imsi].realmap , taijimap[mid[imsi].realmap].count); 
									mapflag=0;
									/*taijimap[0].threadlist[0]=999;
									taijimap[0].chrnumber[0]=0;
									taijimap[mid[imsi].realmap].count++;*/
									//EnterCriticalSection(&port);
									
									
									for(int ka=0;ka<taijimap[mid2[imsi].realmap].count;ka++)
									{
										if(taijimap[mid2[imsi].realmap].threadlist[ka]==0)
										{
											taijimap[mid2[imsi].realmap].threadlist[ka]=mid2[imsi].thread;
											
											taijimap[mid2[imsi].realmap].chrnumber[ka]=imsi;
											kaflag = ka;
											// printf("%d ��° ������ ����Ʈ�� �ִ� ������ : %d",ka,taijimap[mid2[imsi].realmap].threadlist[ka]);
											ka = taijimap[mid2[imsi].realmap].count;
										}
									}
									//LeaveCriticalSection(&port);
									
									
									
									
									
									mid2[imsi].kaflag=kaflag;
									char con[]="����";
									//log(mid2[imsi].id,inet_ntoa(clientaddr.sin_addr),con);
									strcpy(mid2[imsi].ip,inet_ntoa(clientaddr.sin_addr));
									if(mid2[imsi].hel==0)
										mid2[imsi].sangtae=1;
									
									
									
									
									
									
									
									
										/*	char ilchi[] = {
										0xaa ,0x00 ,0x1b ,0x02 ,0x00 ,0x4d ,0x6a 
										,0xbf ,0x99 ,0xae ,0xae ,0x4e ,0xd3 
										,0x9d ,0xf6 ,0xbb ,0xb8 ,0xb1 ,0x31 ,0x16 
										,0x4f ,0x42 ,0x0f ,0x6c ,0x47
									,0x5a ,0x4d ,0x4c ,0x6b ,0x4c };  ������ �޽��� */ 
									char ilchi[] = {
										0xaa, 0x00, 0x05, 0x02, 0x04, 0x4a, 0x61, 0x7c };
										retval = send(client[socketnow],ilchi, 8, 0);
										Sleep(100);
										char peer0_2[] = {  0xaa, 0x00, 0x11, 0x03, 0x4d, 0x01, 0xa8, 0xc0, 
											0x09, 0xc5, 0x06, 0xc5, 0xd7, 0xbd, 0xba, 0xc6, 
											0xa8, 0xaa, 0x00, 0x20, 0x02, 0x00, 0x4d, 0x79, 
											0xb9, 0xd7, 0xae, 0xae, 0xa9, 0xac, 0xef, 0xb9, 
											0x44, 0xc7, 0xa4, 0xdb, 0x8a, 0x4f, 0xdc, 0xe9, 
											0x8c, 0xab, 0xcf, 0x9d, 0x4c, 0x8b, 0xb8, 0xd5, 
											0xe3, 0xf9, 0xbf, 0x55};
										
										
										
										///////////////////////////////////////
										///// �ѱ�� ����  ���ϰ���         ///
										//////////////////////////////////////
										int len;
										
										
										char peer1_0[] = {
											0xaa, 0x00, 0x05, 0x1e, 0x00, 0x48, 0x65, 0x78 };
											
											char peer1_1[] = {
												0xaa, 0x00, 0x04, 0x20, 0x01, 0x44, 0x77, 
													
													
													
													0xaa, 0x00, 0x19, 0x15, 0x05, 0x4b, 
													0x60, 0x7d, 0x7e, 0x6b, 0x58, 0x6f, 0x66, 0x25, 
													0x89, 0xab, 0xc6, 0xd3, 0xd2, 0xf6, 0xad, 0xa8, 
													0x9b, 0xab, 0xa2, 0xb8, 0xd9, 0x8f, 
													
													
													
													
													0xaa, 0x00, 0x0b, 
													0x04, 0x06, 0x48, 0x64, 0x7e, 0x63, 0x68, 0x48, 
													0x68, 0x62, 0x28, 0xaa, 0x00, 0x03, 0x1f, 0x07, 
													0x49, 
													
													
													
													/*0xaa, 0x00, 0x32, 0x08, 0x0a, 
													0x3c, 0x6f, 0x72, 0x64, 0x07, 0xbc, 0x9b, 0xb1, 
													0xd4, 0x11, 0x65, 0x94, 0x35, 0x9a, 0xbd, 0x66, 
													0x6b, 0xda, 0x47, 0x6c, 0x13, 0x0a, 0x73, 0xf8, 
													0x99, 0x94, 0xfe, 0xb7, 0x38, 0x7a, 0x81, 0x36, 
													0x21, 0x5e, 0x0a, 0x5f, 0x40, 0x6b, 0x76, 0x61, 
													0x60, 0x47, 0x60, 0x6d, 0x21, 0x41, 0x6b, 0x76, */
													
											};
											/*char chr[]= {
											0xaa, 0x00, 0x20, 0x33, 0x09, 0x47, 0x6a, 0x71, 
											0x60, 0x65, 0x40, 0x67, 0x6a, 0x24, 0x46, 0x6d, 
											0x70, 0x67, 0x62, 0x41, 0x4a, 0x69, 0x26, 0x0b, 
											0x6e, 0x7f, 0x64, 0x66, 0x44, 0xda, 0x8c, 0xe0, 
											0x86, 0xae, 0x84};*/
											
											/*char send_769[] = {
											0xaa, 0x00, 0x0c, 0x04, 0x08, 0x46, 0x6b, 
											0x70, 0x61, 0x66, 0x47, 0x66, 0x6d, 0x26, 0x47,};*/
											
											
											
											char peer1_2[] = {
												0xaa, 0x00, 0x11, 0x07, 0x40, 0x0e, 0x24, 0x38, 
													0x26, 0x2e, 0x11, 0x2f, 0x23, 0x6f, 0x87, 0xa4, 
													0xac, 0x2e, 0x2f, 0x08 };
												char peer1_3[] = {
													0xaa, 0x00, 0x11, 0x07, 0x41, 0x0f, 0x25, 0x39, 
														0x27, 0x2f, 0x10, 0x2e, 0x22, 0x6e, 0x86, 0xa5, 
														0xad, 0x2f, 0x2e, 0x09 };
													char peer1_6[] = {
														0xaa, 0x00, 0x11, 0x07, 0x44, 0x0a, 0x20, 0x3c, 
															0x22, 0x2a, 0x15, 0x2b, 0x27, 0x6b, 0x83, 0xa0, 
															0xa8, 0x2a, 0x2b, 0x0c };
														char peer1_7[] = {
															0xaa, 0x00, 0x11, 0x07, 0x45, 0x0b, 0x21, 0x3d, 
																0x23, 0x2b, 0x14, 0x2a, 0x26, 0x6a, 0x82, 0xa1, 
																0xa9, 0x2b, 0x2a, 0x0d };
															char peer1_8[] = {
																0xaa, 0x00, 0x11, 0x07, 0x46, 0x08, 0x22, 0x3e, 
																	0x20, 0x28, 0x17, 0x29, 0x25, 0x69, 0x81, 0xa2, 
																	0xaa, 0x28, 0x29, 0x0e };
																//Sleep(100);
																retval = send(client[socketnow],peer1_0, 8, 0);
																//Sleep(100);
																//retval = send(client[socketnow],peer1_1, 55, 0);
																char mapmsg[40];
																
																
																mapmsg[0]=( mid2[imsi].realmap & 0x0000ff00 ) >> 8;
																mapmsg[1]=( mid2[imsi].realmap & 0x000000ff ) ;
																mapmsg[2]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x0000ff00 ) >> 8;
																mapmsg[3]=( taijimap[mid2[imsi].realmap].map_x_len+1 & 0x000000ff ) ;
																mapmsg[4]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x0000ff00 ) >> 8;
																mapmsg[5]=( taijimap[mid2[imsi].realmap].map_y_len+1 & 0x000000ff ) ;
																mapmsg[6]='\x04';
																mapmsg[7]='\x00';
																mapmsg[8]=strlen(taijimap[mid2[imsi].realmap].name);
																strcpy(mapmsg+9,taijimap[mid2[imsi].realmap].name);
																
																
																char mapmsg2[10],mapmsg3[18];
																mapmsg2[0]=( mid2[imsi].map_x & 0x0000ff00 ) >> 8;
																// printf("mapx : %d\n",mid2[imsi].map_x);
																mapmsg2[1]=( mid2[imsi].map_x & 0x000000ff ) ;
																mapmsg2[2]=( mid2[imsi].map_y & 0x0000ff00 ) >> 8;
																mapmsg2[3]=( mid2[imsi].map_y & 0x000000ff ) ;
																mapmsg2[4]=( client_map_x(imsi,mid2[imsi].map_x) & 0x0000ff00 ) >> 8;
																// printf("clien mapx : %d\n",client_map_x(imsi,mid2[imsi].map_x));
																mapmsg2[5]=( client_map_x(imsi,mid2[imsi].map_x) & 0x000000ff ) ;
																mapmsg2[6]=( client_map_y(imsi,mid2[imsi].map_y) & 0x0000ff00 ) >> 8;
																mapmsg2[7]=( client_map_y(imsi,mid2[imsi].map_y) & 0x000000ff ) ;
																mapmsg2[8]='\x00';
																mapmsg2[9]='\x00';
																
																
																mapmsg3[0]='\x01';
																mapmsg3[1]='\x00';
																mapmsg3[2]='\x00';
																mapmsg3[3]='\x01';
																mapmsg3[4]='\x00';
																mapmsg3[5]='\x00';
																mapmsg3[6]='\xc0';
																mapmsg3[7]='\x00';
																mapmsg3[8]='\x00';
																mapmsg3[9]='\x00';
																mapmsg3[10]='\x03';
																mapmsg3[11]='\x01';
																mapmsg3[12]='\x00';
																mapmsg3[13]='\x02';
																mapmsg3[14]='\x02';
																mapmsg3[15]='\x00';
																mapmsg3[16]='\x04';
																mapmsg3[17]='\x00';
																
																
																
																
																
																
																len = Xc->Enc_Pack(imsi,mapmsg,23,0x15,1);
																retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
																len = Xc->Enc_Pack(imsi,mapmsg3,18,0x19,1);
																retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
																//retval = send(client[mid2[imsi].thread],peer1_0, 23, 0);
																len = Xc->Enc_Pack(imsi,mapmsg2,10,0x04,1);
																retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi],len, 0);  
																
																
																
																// retval = send(client[socketnow],send_769, 15, 0);
																
																
																/*	char s3[] = {
																
																  0xaa, 0x00, 0x14, 0x19, 0x06, 0x49, 0x63, 0x7e, 0x68, 0x68, 
																  0x4f, 0xa8, 0x65, 0x28, 0x49, 0x61, 0x7e, 0x68, 
																  0x6b, 0x4c, 0x69, 0x60, 0x29,}; 
																  
																retval = send(client[socketnow],s3,23,0);*/
																
																
																
																
																
																
																
																
																
																
																mid2[imsi].ac=0;
																int fflag=0;
																for(int k=0;k<2600;k++)
																{
																	if(item_st[k].dress_number==mid2[imsi].dress)
																	{
																		fflag = k;
																		k=2600;
																	}
																}
																mid2[imsi].max_hel_body=mid2[imsi].max_hel-item_st[fflag].hel_up;
																mid2[imsi].max_mana_body=mid2[imsi].max_mana-item_st[fflag].mana_up;
																mid2[imsi].him_body=mid2[imsi].him-item_st[fflag].him_up;
																mid2[imsi].min_body=mid2[imsi].min-item_st[fflag].min_up;
																mid2[imsi].ji_body=mid2[imsi].ji-item_st[fflag].ji_up;
																mid2[imsi].ac=mid2[imsi].ac+item_st[fflag].ac;
																for(k=0;k<2600;k++)
																{
																	if(item_st[k].sword_number==mid2[imsi].sword)
																	{
																		fflag = k;
																		k=2600;
																	}
																}
																mid2[imsi].sword_item=fflag;
																mid2[imsi].max_hel_body=mid2[imsi].max_hel_body-item_st[fflag].hel_up;
																mid2[imsi].max_mana_body=mid2[imsi].max_mana-item_st[fflag].mana_up;
																mid2[imsi].him_body=mid2[imsi].him_body-item_st[fflag].him_up;
																mid2[imsi].min_body=mid2[imsi].min_body-item_st[fflag].min_up;
																mid2[imsi].ji_body=mid2[imsi].ji_body-item_st[fflag].ji_up;
																mid2[imsi].ac=mid2[imsi].ac+item_st[fflag].ac;
																for(k=0;k<2600;k++)
																{
																	if(item_st[k].bangpae_number==mid2[imsi].bangpae)
																	{
																		fflag = k;
																		k=2600;
																	}
																}
																mid2[imsi].max_hel_body=mid2[imsi].max_hel_body-item_st[fflag].hel_up;
																mid2[imsi].max_mana_body=mid2[imsi].max_mana-item_st[fflag].mana_up;
																mid2[imsi].him_body=mid2[imsi].him_body-item_st[fflag].him_up;
																mid2[imsi].min_body=mid2[imsi].min_body-item_st[fflag].min_up;
																mid2[imsi].ji_body=mid2[imsi].ji_body-item_st[fflag].ji_up;
																mid2[imsi].ac=mid2[imsi].ac+item_st[fflag].ac;
																
																for(k=0;k<2600;k++)
																{
																	if(item_st[k].earing_number==mid2[imsi].earing[0])
																	{
																		fflag = k;
																		k=2600;
																	}
																}
																mid2[imsi].max_hel_body=mid2[imsi].max_hel_body-item_st[fflag].hel_up;
																mid2[imsi].max_mana_body=mid2[imsi].max_mana-item_st[fflag].mana_up;
																mid2[imsi].him_body=mid2[imsi].him_body-item_st[fflag].him_up;
																mid2[imsi].min_body=mid2[imsi].min_body-item_st[fflag].min_up;
																mid2[imsi].ji_body=mid2[imsi].ji_body-item_st[fflag].ji_up;
																mid2[imsi].ac=mid2[imsi].ac+item_st[fflag].ac;
																for(k=0;k<2600;k++)
																{
																	if(item_st[k].earing_number==mid2[imsi].earing[1])
																	{
																		fflag = k;
																		k=2600;
																	}
																}
																mid2[imsi].max_hel_body=mid2[imsi].max_hel_body-item_st[fflag].hel_up;
																mid2[imsi].max_mana_body=mid2[imsi].max_mana-item_st[fflag].mana_up;
																mid2[imsi].him_body=mid2[imsi].him_body-item_st[fflag].him_up;
																mid2[imsi].min_body=mid2[imsi].min_body-item_st[fflag].min_up;
																mid2[imsi].ji_body=mid2[imsi].ji_body-item_st[fflag].ji_up;
																mid2[imsi].ac=mid2[imsi].ac+item_st[fflag].ac;
																for(k=0;k<2600;k++)
																{
																	if(item_st[k].ring_number==mid2[imsi].ring[0])
																	{
																		fflag = k;
																		k=2600;
																	}
																}
																mid2[imsi].max_hel_body=mid2[imsi].max_hel_body-item_st[fflag].hel_up;
																mid2[imsi].max_mana_body=mid2[imsi].max_mana-item_st[fflag].mana_up;
																mid2[imsi].him_body=mid2[imsi].him_body-item_st[fflag].him_up;
																mid2[imsi].min_body=mid2[imsi].min_body-item_st[fflag].min_up;
																mid2[imsi].ji_body=mid2[imsi].ji_body-item_st[fflag].ji_up;
																mid2[imsi].ac=mid2[imsi].ac+item_st[fflag].ac;
																for(k=0;k<2600;k++)
																{
																	if(item_st[k].ring_number==mid2[imsi].ring[0])
																	{
																		fflag = k;
																		k=2600;
																	}
																}
																mid2[imsi].max_hel_body=mid2[imsi].max_hel_body-item_st[fflag].hel_up;
																mid2[imsi].max_mana_body=mid2[imsi].max_mana-item_st[fflag].mana_up;
																mid2[imsi].him_body=mid2[imsi].him_body-item_st[fflag].him_up;
																mid2[imsi].min_body=mid2[imsi].min_body-item_st[fflag].min_up;
																mid2[imsi].ji_body=mid2[imsi].ji_body-item_st[fflag].ji_up;
																mid2[imsi].ac=mid2[imsi].ac+item_st[fflag].ac;
																
																// printf(" �Ǹ� ü�� : %d\n",mid2[imsi].max_mana_body);
																
																
																// printf(" ������ ü�� : %d\n",mid2[imsi].max_mana);
																// printf(" �Ǹ� �� : %d\n",mid2[imsi].him_body);
																
																
																// printf(" ������ �� : %d\n",mid2[imsi].him);
																
																
																
																char sendmsg8[50];
																sendmsg8[0]='\x78';
																sendmsg8[1]='\x01';
																sendmsg8[2]='\x01';
																sendmsg8[3]='\x01';
																sendmsg8[4]=mid2[imsi].level;
																sendmsg8[5]=( mid2[imsi].max_hel & 0xff000000 ) >> 24;
																sendmsg8[6]=( mid2[imsi].max_hel & 0x00ff0000 ) >> 16;
																sendmsg8[7]=( mid2[imsi].max_hel & 0x0000ff00 ) >> 8;
																sendmsg8[8]=( mid2[imsi].max_hel & 0x000000ff ) ;
																sendmsg8[9]=( mid2[imsi].max_mana & 0xff000000 ) >> 24;
																sendmsg8[10]=( mid2[imsi].max_mana & 0x00ff0000 ) >> 16;
																sendmsg8[11]=( mid2[imsi].max_mana & 0x0000ff00 ) >> 8;
																sendmsg8[12]=( mid2[imsi].max_mana & 0x000000ff ) ;
																sendmsg8[13]=mid2[imsi].him;
																sendmsg8[14]=mid2[imsi].min;
																sendmsg8[15]='\x03';
																sendmsg8[16]='\x03';
																sendmsg8[17]=mid2[imsi].ji;
																sendmsg8[18]='\x01';
																sendmsg8[19]='\x01';
																sendmsg8[20]='\x63';
																sendmsg8[21]='\x6d';
																sendmsg8[22]='\x15';
																sendmsg8[23]='\xb9';
																sendmsg8[24]=( mid2[imsi].hel & 0xff000000 ) >> 24;
																sendmsg8[25]=( mid2[imsi].hel & 0x00ff0000 ) >> 16;
																sendmsg8[26]=( mid2[imsi].hel & 0x0000ff00 ) >> 8;
																sendmsg8[27]=( mid2[imsi].hel & 0x000000ff ) ;
																sendmsg8[28]=( mid2[imsi].mana & 0xff000000 ) >> 24;
																sendmsg8[29]=( mid2[imsi].mana & 0x00ff0000 ) >> 16;
																sendmsg8[30]=( mid2[imsi].mana & 0x0000ff00 ) >> 8;
																sendmsg8[31]=( mid2[imsi].mana & 0x000000ff ) ;
																sendmsg8[32]=( mid2[imsi].exp & 0xff000000 ) >> 24;
																sendmsg8[33]=( mid2[imsi].exp & 0x00ff0000 ) >> 16;
																sendmsg8[34]=( mid2[imsi].exp & 0x0000ff00 ) >> 8;
																sendmsg8[35]=( mid2[imsi].exp & 0x000000ff ) ;
																sendmsg8[36]=( mid2[imsi].money & 0xff000000 ) >> 24;
																sendmsg8[37]=( mid2[imsi].money & 0x00ff0000 ) >> 16;
																sendmsg8[38]=( mid2[imsi].money & 0x0000ff00 ) >> 8;
																sendmsg8[39]=( mid2[imsi].money & 0x000000ff ) ;
																sendmsg8[40]='\x00';
																sendmsg8[41]='\x00';
																sendmsg8[42]='\x00';
																sendmsg8[43]='\x00';
																sendmsg8[44]='\x01';
																sendmsg8[45]='\x00';
																sendmsg8[46]='\x01';
																sendmsg8[47]='\x01';
																
																
																len = Xc->Enc_Pack(imsi,sendmsg8,48,0x08,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																
																
																
																
																char sendmsg4[20];        // Ŭ���̾�Ʈ ��ġ ������ �κ�
																sendmsg4[0]='\x00';
																sendmsg4[1]=(int)mid2[imsi].map_x;
																sendmsg4[2]='\x00';
																sendmsg4[3]=(int)mid2[imsi].map_y;
																sendmsg4[4]='\x00';
																sendmsg4[5]=client_map_x(imsi,mid2[imsi].map_x);
																sendmsg4[6]='\x00';
																sendmsg4[7]=client_map_y(imsi,mid2[imsi].map_y);
																
																len = Xc->Enc_Pack(imsi,sendmsg4,8,0x04,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																
																int mapcount;
																
																
																/*
																char sendmsg6[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
																int sendmsg_byte=loginnpc(0,sendmsg6);
																len = Xc->Enc_Pack(imsi,sendmsg6,sendmsg_byte,0x33,1);
																for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
																{
																if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
																{
																// printf(" %d��° �������� �������� npc �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
																retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
																}
																}
																
																*/
																
																char sendmsg3[20];
																sendmsg3[0]='\x01';
																sendmsg3[1]='\x00';
																sendmsg3[2]='\x00';
																sendmsg3[3]='\x01';
																sendmsg3[4]='\x00';
																sendmsg3[5]='\x00';
																sendmsg3[6]='\xc0';
																sendmsg3[7]=( mid2[imsi].thread & 0xff000000 ) >> 24;
																sendmsg3[8]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
																sendmsg3[9]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
																sendmsg3[10]=( mid2[imsi].thread & 0x000000ff ) ;
																sendmsg3[11]='\x01';
																sendmsg3[12]='\x00';
																sendmsg3[13]='\x02';
																sendmsg3[14]='\x02';
																sendmsg3[15]='\x00';
																sendmsg3[16]='\x04';
																
																len = Xc->Enc_Pack(imsi,sendmsg3,17,0x19,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																
																
																
																
																char sendmsg2[20];
																sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
																sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
																sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
																sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
																sendmsg2[4]='\x00';
																sendmsg2[5]='\x00';
																sendmsg2[6]='\x00';
																sendmsg2[7]='\x02';
																sendmsg2[8]='\x01'; 
																
																len = Xc->Enc_Pack(imsi,sendmsg2,9,0x05,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																
																for(int count=0,item_count=taijimap[mid2[imsi].realmap].item_count;count<item_count;count++)
																{
																	
																	if(taijimap[mid2[imsi].realmap].item_thread[count] != 0)
																	{
																		
																		char item[19];
																		item[0]='\x00';
																		item[1]='\x01';
																		item[2]='\x00';
																		item[3]=taijimap[mid2[imsi].realmap].item_x[count];
																		item[4]='\x00';
																		item[5]=taijimap[mid2[imsi].realmap].item_y[count];
																		item[6]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x0000ff00 ) >> 8;
																		item[7]=( taijimap[mid2[imsi].realmap].item_number[count] & 0x000000ff ) ;
																		item[8]='\x00';
																		item[9]='\x00';
																		item[10]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x0000ff00 ) >> 8;
																		item[11]=( taijimap[mid2[imsi].realmap].item_thread[count] & 0x000000ff ) ;
																		item[12]='\x00';
																		
																		len = Xc->Enc_Pack(imsi,item,13,0x07,1);
																		retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																		
																	}
																	
																	else imsi_count++;
																	
																}
																
																char sendmsg[50]; // �α�� Ŭ���̾�Ʈ���� �ɸ��� ��ġ ������ �κ�
																int sendmsg_byte=loginchr(imsi,sendmsg);
																for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
																{
																	
																	if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
																	{
																		
																		// printf(" %d��° �������� �������� ������ �����մϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
																		
																		len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
																		retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
																		
																	}else {
																		
																		// printf("0 �̹Ƿ� imsi_count ����\n");
																		imsi_count++;
																	}
																}
																
																
																
																
																
																//retval = send(client[socketnow],chr,35,0);
																//Sleep(100);
																retval = send(client[socketnow],peer1_2, 20, 0);  
																//Sleep(100);
																
																
																retval = send(client[socketnow],peer1_3, 20, 0);  
																
																
																for(int i=0;i<52;i++)  // ���� ��Ͽ� �߰� �ϱ�
																{
																	if(mid2[imsi].magic[i]!=0)
																	{
																		// printf("%d\n",i);
																		char sendmagic[50];
																		magic_name(sendmagic,mid2[imsi].magic[i],i+1);
																		// printf("%d\n",mid2[imsi].magic[i]);
																		len = Xc->Enc_Pack(imsi,sendmagic,strlen(sendmagic),0x17,1);
																		retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																		packet_dump(sendmagic,20,16);
																	}
																}
																
																
																
																for(i=0;i<26;i++)
																{
																	if(mid2[imsi].item[i][0]!=0)
																	{
																		char item2[80];  // ������ ��Ͽ� �߱�
																		memset(item2,0,80);
																		char msg[30]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
																		char gae[]="��";
																		char msg2[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00";
																		itoa(mid2[imsi].item[i][1],msg2,10);
																		
																		// itoa(taijimap[mid2[imsi].realmap].item_thread[count]-49151,msg,10);
																		strcpy(msg,item_st[mid2[imsi].item[i][0]-49151].name);
																		item2[0]=i+1;
																		item2[1]=( mid2[imsi].item[i][0] & 0x0000ff00 ) >> 8;
																		item2[2]=( mid2[imsi].item[i][0] & 0x000000ff ) ;
																		item2[3]='\x00';
																		item2[4]='\x20';
																		strcpy(item2+5,msg); //������ �̸�
																		item2[5+strlen(msg)]='\x20'; // ��ĭ���
																		strcpy(item2+6+strlen(msg),msg2); //���� 
																		strncpy(item2+6+strlen(msg)+strlen(msg2),gae,2);
																		item2[8+strlen(msg)+strlen(msg2)]='\x00';
																		item2[9+strlen(msg)+strlen(msg2)]='\x00';
																		item2[10+strlen(msg)+strlen(msg2)]='\x00';
																		len = Xc->Enc_Pack(imsi,item2,80,0x0f,1);
																		retval = send(client[mid2[imsi].thread],Encrypted_Messages[imsi], len, 0); 	
																	}
																}
																
																
																/*
																
																  len = Xc->Enc_Pack(imsi,"\x01\x05\x08��ȥ��",11,0x17,1);
																  retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																  len = Xc->Enc_Pack(imsi,"\x02\x05\x08��ȥ��",11,0x17,1);
																  retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																  len = Xc->Enc_Pack(imsi,"\x03\x05\x08��õ�˹�",11,0x17,1);
																  retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																  len = Xc->Enc_Pack(imsi,"\x04\x05\x08�ع�ȣ��",11,0x17,1);
																  retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																  len = Xc->Enc_Pack(imsi,"\x05\x01\x08â��    ",11,0x17,1);
																*/
																
																/*retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																len = Xc->Enc_Pack(imsi,"\x03\00\x1a���������� ver0.01",36,0x0a,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																len = Xc->Enc_Pack(imsi,"\x03\00\x1a����[��",36,0x0a,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																len = Xc->Enc_Pack(imsi,"\x03\00\x1a�ӼӸ�",36,0x0a,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																len = Xc->Enc_Pack(imsi,"\x03\00\x1a���ϱ�",36,0x0a,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																len = Xc->Enc_Pack(imsi,"\x03\00\x1a������",36,0x0a,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																len = Xc->Enc_Pack(imsi,"\x03\00\x1a��ȥ��(����a)",36,0x0a,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																len = Xc->Enc_Pack(imsi,"\x03\00\x1a��ȥ��(����b)",36,0x0a,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);
																len = Xc->Enc_Pack(imsi,"\x03\00\x1aȭ�� �̻��ϸ� ctrl+r",36,0x0a,1);
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  */
																int k2;
																//# 6. �����̸� +130�� �ؾ���
																char server[]={0x78,0x3b,0x2f,0x3e,0x78,0x43,0x44,0x47};
																char tmp[1];
																
																//printf("\n%d\n",sizeof(server));
																for(k=0,k2=sizeof(server)-1;k<((sizeof(server))/2);k++,k2--)
																{
																	tmp[0]=server[k2]-130;
																	server[k2]=server[k]-130;
																	server[k]=tmp[0];
																}
																server[sizeof(server)]=0;
																//printf("%s\n",server);
																
																
																//Xc->Dec_Pack(imsi,server);
																//printf("%s\n",Messages[imsi]);
																char pop_up[50];
																memset(pop_up,0,50);
																sprintf(pop_up,"%c%c%c%s",0x08,0x00,sizeof(server),server);
																len = Xc->Enc_Pack(imsi,pop_up,sizeof(server)+3,0x0a,1);
																
																retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																
																//Sleep(100);
																
																
																
																retval = send(client[socketnow],peer1_6, 20, 0);  
																//Sleep(100);
																retval = send(client[socketnow],peer1_7, 20, 0);  
																//Sleep(100); 
																retval = send(client[socketnow],peer1_8, 20, 0);  
																
																
																for(mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
																{
																	
																	if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
																	{
																		// printf(" %d��° �������� ������ ������ �޽��ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
																		int sendmsg_byte=loginchr(taijimap[mid2[imsi].realmap].chrnumber[mapcount],sendmsg);  //�ٸ� Ŭ���̾�Ʈ�� ��ġ�� ������
																		len = Xc->Enc_Pack(imsi,sendmsg,sendmsg_byte,0x33,1);
																		retval = send(client[socketnow],Encrypted_Messages[imsi],len, 0);  
																		
																	}else {
																		
																		// printf("0 �̹Ƿ� imsi_count ����\n");
																		imsi_count++;
																	}
																}
																
																
																/*char peer0_3[] = {  0xaa, 0x00, 0x05, 0x1e, 0x00, 0x48, 0x65, 0x78 };
																retval = send(client[socketnow],peer0_2, 30, 0);
																
																  char peer0_4[] = {   };
																retval = send(client[socketnow],peer0_2, 676, 0);*/
							}
							}
							
							
							
							//if(loginfile(Messages[imsi])==1)
							
						}
						
						//Xc->Dec_Pack(imsi,buf+2);
						// printf("��ȣȭ�� ������ \n");
						// printf("==================\n");
						packet_dump(Messages[imsi],strlen(Messages[imsi]),16);
						// printf("==================\n");
					}
		}
		
		
		
		
		if(mapflag==0)  // �ѹ��̶� �α��� �����ߴٸ�
		{
			
			char sendmsg2[20];
			sendmsg2[0]=( mid2[imsi].thread & 0xff000000 ) >> 24;
			sendmsg2[1]=( mid2[imsi].thread & 0x00ff0000 ) >> 16;
			sendmsg2[2]=( mid2[imsi].thread & 0x0000ff00 ) >> 8;
			sendmsg2[3]=( mid2[imsi].thread & 0x000000ff ) ;
			sendmsg2[4]='\x00';
			
			
			
			
			for(int mapcount=0,imsi_count=taijimap[mid2[imsi].realmap].count;mapcount<imsi_count;mapcount++)
			{
				
				if(taijimap[mid2[imsi].realmap].threadlist[mapcount] != 0)
				{
					
					
					int len = Xc->Enc_Pack(imsi,sendmsg2,5,0x0e,1);
					// printf("len = %d\n",len);
					packet_dump(sendmsg2,5,16);
					packet_dump(Encrypted_Messages[imsi],10,16);
					// printf(" %d��° �������� �������� ĳ���͸� ����ϴ�.\n",taijimap[mid2[imsi].realmap].threadlist[mapcount]);
					retval = send(client[taijimap[mid2[imsi].realmap].threadlist[mapcount]],Encrypted_Messages[imsi],len, 0);  
					
				}else {
					
					// printf("0 �̹Ƿ� imsi_count ����\n");
					imsi_count++;
				}
			}
			
			
			mid2[imsi].thread=0;
			mid2[imsi].group=0;
			mid[imsi]=mid2[imsi]; // ����Ÿ �簻��
			//fwrite();
		}
		
		
		// // printf("taijimap[mid[imsi].realmap].count = %d\n",taijimap[mid[imsi].realmap].count);
		
		
		
		if(mapflag==0)  // �ʻ󿡼� ������� �κ�
		{
			//EnterCriticalSection(&port);
			//printf("thread: %d\nkaflag: %d\n",taijimap[mid2[imsi].realmap].threadlist[mid2[imsi].kaflag],mid2[imsi].kaflag);
			taijimap[mid2[imsi].realmap].count--;
			taijimap[mid2[imsi].realmap].threadlist[mid2[imsi].kaflag]=0;
			taijimap[mid2[imsi].realmap].chrnumber[mid2[imsi].kaflag]=0;
			//LeaveCriticalSection(&port);
			
			//	taijimap[mid2[imsi].realmap].count--;
		}
		
		
		// // printf("taijimap[mid[imsi].realmap].count = %d\n",taijimap[mid[imsi].realmap].count);
		// closesocket()
		closesocket(client[socketnow]);
		struct tm *systime; 
		time_t t;
		t = time(NULL);
		systime = localtime(&t);
		struct tm *clock;
		time_t current;						time(& current); //���� �ð��� ��� ���� �Լ�
		
		clock=localtime(& current); //���� �ð��� ��,��,�ʷ� ���� �ϴ� �ռ�
		//printf("%.2d�� %.2d�� %.2d�� ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d ID:%s\n",clock->tm_hour,clock->tm_min,clock->tm_sec,inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port),mid[imsi].id);
		//printf("[TCP ���] Ŭ���̾�Ʈ  ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		char con[]="����";
		//log(mid[imsi].id,inet_ntoa(clientaddr.sin_addr),con);
		
		
		
		
		
		
		
		// closesocket()
		/*closesocket(client[socketnow]);
		// printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", 
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));  �ߺ��� */
		
		return 0;
		
}


main(int argc, char* argv[]) // #����
{
	
	
	
	
	
    
	
	
	
	mcount_plus=0;
	
	
	// ������

	memset(Messages[0],0,100);


	memset(Messages[0],0,100);
	
	strcpy(check_msg,Messages[0]);
	strcpy(strHostName,Messages[0]);
	
	
	
	
	// strcpy(strHostName,"tbaram.wowdns.com");
	// strcpy(check_msg,"tbaram.wowdns.com");
	
	
	
	
	
	
	InitializeCriticalSection(&port);
	InitializeCriticalSection(&save);
	InitializeCriticalSection(&id);
	InitializeCriticalSection(&monster_cs);
	
	char ip_zero[]={0x09, 0x0a , 0x00 , 0x7e , 0x4b , 0x48 , 0x41 , 0x5e , 0x67 , 0x5e};
	Xc->Dec_Pack(1,ip_zero);      
	
	//printf("%s\n",Messages[1]); 
	
	
	
	GetLocalTime( &st );  // �ð� st�� �ʱ�ȭ
	printf("�ɸ��� ������ ...\n ");   
	file_read();
	printf("%d ���� �������� ����...\n",frecnum);
	file_read_item();
	printf("%d ���� ������ ���� ����...\n",item_frec);
	file_read_monster();
	printf("%d ���� �������� ����...\n",monster_frec);
	file_read_map();
	printf("%d ���� ������ ����...\n",map_frec);
	file_read_port();
	printf("%d ���� ��Ʈ���� ����...\n",port_frec);
	file_read_rezen();
	printf("%d ���� �������� ����...\n",rezen_frec);
	file_read_npc();
	printf("%d ���� npc���� ����...\n",npc_frec);
	file_read_npc_item();
	printf("%d ���� npc_item ���� ����...\n",npc_item_frec);
	file_read_setting();
	file_read_dontmove();
	file_read_dontrezen();
	file_read_junsa();
	file_read_junsa2();
	file_read_dojuk();
	file_read_dojuk2();
	file_read_soolsa();
	file_read_soolsa2();
	file_read_dosa();
	file_read_dosa2();
	file_read_ip();
	//test_write();
	
	
	//test_write();
	file_read_levelup();
	file_read_johap();
	if(WSAStartup(MAKEWORD(2, 0), &wsaData) == 0 && domain_name[0]!=0x00)
	{
		
		phi = gethostbyname(domain_name);
		
		if(phi != NULL)
		{
			ip = inet_ntoa(*(struct in_addr *)*phi->h_addr_list);
			
			
			
			//printf("%s\n(�ڱ� ���ͳ� �����ǰ� %s������ ���� ���� ����)\n",ip,ip);
			strcpy(ip2,ip);
			
		}
		else
		{
			//error - refer to MSDN gethostbyname function
		}
		WSACleanup( );
	}
	else
	{
		//error
	}
	
	
	
	
    unsigned char buf[1000];
	memset(buf,4,1000);
	//printf("domain:%s\n",domain_name);
	
	
	for(int p=0;p<strlen(domain_name);p++)
	{
		buf[p]=domain_name[p];
	}
	
	
	
	
	imsi_plus=0;
	threadzero(); ////��� �ɸ����� ������ ���¸� 0���� �ʱ�ȭ
	fwrite(); /// �ٽ��ѹ� ���� ������Ʈ
			  /*char peer0_3[] = {
			  0x07, 0x62, 0x07,0x28,0x10,0x1e,0x05,0x69};
			  
				Xc->Dec_Pack(2500,peer0_3);
	packet_dump(Messages[2500],16,16);*/
	
	
	
	
	
	// ������� ��ȣȭ �׽�Ʈ 
	int retval;
	
	
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0) 
		return -1;
	
	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");	
	
	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr =  inet_addr(ip2);//htonl(INADDR_ANY);
	
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("bind()");
	
	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if(retval == SOCKET_ERROR) err_quit("listen()");
	
	
	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	
	
	
	HANDLE hThread;
	HANDLE hThread2;
	HANDLE hThread3;
	HANDLE hThread4;
	HANDLE hThread5;
	HANDLE hThread6;
	HANDLE hThread7;
	DWORD ThreadId;
	DWORD MonsterID;
	DWORD rezenID;
	DWORD npcID;
	DWORD controlID;
	DWORD autosaveID;
	DWORD autoresetID;
	hThread2 = CreateThread(NULL,0,Monster_thread,NULL,0,&MonsterID);
	hThread3 = CreateThread(NULL,0,rezen_thread,NULL,0,&rezenID);
	hThread4 = CreateThread(NULL,0,npc_thread,NULL,0,&npcID);
	hThread5 = CreateThread(NULL,0,control_thread,NULL,0,&controlID);
	hThread6 = CreateThread(NULL,0,autosave_thread,NULL,0,&autosaveID);
	hThread7 = CreateThread(NULL,0,autoreset_thread,NULL,0,&autoresetID);
	monster_event = CreateEvent(NULL,FALSE,TRUE,NULL);
	if(monster_event == NULL) return -1;
	die_event = CreateEvent(NULL,FALSE,TRUE,NULL);
	if(monster_event == NULL) return -1;
	//	printf("serveraddr.sin_addr.s_addr = htonl(INADDR_ANY):%s\n",inet_ntoa(serveraddr.sin_addr));
	while(1){
		
		// accept()
		Sleep(100);
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if(client_sock == INVALID_SOCKET){
			err_display("accept()");
			continue;
		}
		//printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", 			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		
		// ������ ����
		hThread = CreateThread(NULL, 0, ProcessClient, 
			(LPVOID)client_sock, 0, &ThreadId);
		if(hThread == NULL)
			printf("[����] ������ ���� ����!\n");
		else
			CloseHandle(hThread);
		
		
		
	}
	DeleteCriticalSection(&id);
	DeleteCriticalSection(&port);
	DeleteCriticalSection(&monster_cs);
	DeleteCriticalSection(&save);
	CloseHandle(monster_event);
	CloseHandle(die_event);
	
	
	
	// closesocket()
	closesocket(listen_sock);
	
	// ���� ����
	WSACleanup();
	
	
	
	
	
}