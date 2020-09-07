#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"Winmm.lib")
#include<conio.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<tchar.h>
#include<windows.h>

/*״̬*/
#define STATENUMBER 12 //״̬����
#define REST 0 //��Ϣ
#define EXPERIMENT 1  //ʵ������������
#define BORROWING 2 //������
#define STUDYING 3 //��ϰ��
#define SAVING 4 //������
#define LOAN 5 //����
#define EASIER 6 //����ѧϰ
#define RECOVERING 7 //�����ָ�
#define FRESH 8 //��������
#define SKILLFUL 9 //�Ƿ��켫
#define UNFAMILIAR 10 //����
#define FAILURE 11 //ʧ��
/*����*/
#define ITEMNUMBER 7 //��������
#define MAGIC_DICE 0 //�ٱ�����
#define TRADING_LICENSE 1 //�������֤
#define LEARNING_MATERIALS 2 //ѧϰ����
#define STAYING_UP_DOOR 3 //ˢҹ������
#define SWAP 4 //���λ�λ
#define ENERGY_DRINK 5 //��������
#define ADVANCED_READINGS 6 //���׶���
/*�¼�*/
#define EVENTNUMBER 12 //�¼�����
#define LATE 0 //�Ͽγٵ�
#define OVERPLAY 1 //��������������
#define STAY_UP 2 //��ҹ����Ϸ
#define RECHARGE 3 //봽�
#define ILL 4 //��һ��
#define BIRTHDAY 5 //������
#define PART_TIME_JOB 6 //��ĩ׬���
#define LIVING_EXEPENSES 7 //����Ѳ���
#define DDL_END 8 //ddl�ս�
#define SCHOLARSHIP 9 //��ѧ��
#define SAVE 10 //����
#define CAMPUS_LOAN 11 //У԰��
/*����*/
#define START 0 //��ʼ
#define CAL 1 //΢����
#define L_A 2 //���Դ���
#define ENTRANCE 3 //ˢҹ�����
#define P_A_S 4 //������������ͳ��
#define EVENT_CARD 5 //�¼���
#define LABORATORY 6 //ʵ����
#define P_O_C 7 //��ѧԭ��
#define I_E_C 8 //�޻�Ԫ�ػ�ѧ
#define O_C 9 //�л���ѧ
#define P_C 10 //����ѧ
#define S_C 11 //�ṹ��ѧ
#define LIBRARY 12 //ͼ���
#define A_C 13 //������ѧ
#define I_A 14 //��������
#define EXIT 15 //ˢҹ������
#define B_O_C_E 16 //��ѧ���������
#define C_P 17 //C���Գ�����ƻ���
#define STUDY_ROOM 18 //��ϰ��
#define ENG 19 //��ѧӢ��
#define ITEM_CARD 20 //���߿�
#define P_A_I 21 //����������˼�����ר��
#define PE 22 //����
#define G_P 23 //��ͨ����
#define B_M -5 //��ɽ
#define C_M -4 //���Ȼ�
#define M_S_B -3 //ҹ��̯
#define E_S -2 //�⺣
#define B_D -1 //�����
/*�γ�����*/
#define MAJOR 1
#define M_A_P 2
#define CS 3
#define OTHER 4

/*��ҽṹ��*/
struct player
{
	char name;
	int gold = 500; //��ʼ��Ǯ500
	int energy = 10; //��ʼ����10
	bool state[STATENUMBER] = { false }; //״̬��
	int item[ITEMNUMBER] = { 0 }; //������
	int position = START; //λ��
	int* level; //�γ̵ȼ�ָ��
	int rank = 1; //����
};
/*�γ̽ṹ��*/
struct course
{
	int max_level; //�γ���ߵȼ�
	int category; //����
	bool forget; //�����ƶ�
	int energy_cost[7]; //��������
	int gold_gain[7]; //����
	int playerA_level = 0, playerB_level = 0, playerC_level = 0, playerD_level = 0; //��ҿγ̵ȼ�
};

/*��ʼ��*/
TCHAR position_text[100];
TCHAR guide_text[200];
RECT position_r = { 725,170,975,320 }; //λ����ʾ����
RECT guide_r = { 725,400,975,650 }; //����ָ������
int playernumber = 4; //�������
int Round = 1; //�غ���
bool load_continous_state = false; //�������������״̬�غ����浵
struct player playerA = { 'A' }, playerB = { 'B' }, playerC = { 'C' }, playerD = { 'D' };
struct course cal = { 5,M_A_P,true };
struct course l_a = { 3,M_A_P,true };
struct course p_a_s = { 3,M_A_P,true };
struct course g_p = { 5,M_A_P,true };
struct course p_o_c = { 3,MAJOR,true };
struct course i_e_c = { 3, MAJOR, true };
struct course o_c = { 5,MAJOR,true };
struct course p_c = { 4,MAJOR,true };
struct course s_c = { 3,MAJOR,true };
struct course a_c = { 3,MAJOR,true };
struct course i_a = { 3,MAJOR,true };
struct course b_o_c_e = { 3,CS,true };
struct course c_p = { 3,CS,true };
struct course eng = { 7,OTHER,false };
struct course p_a_i = { 7,OTHER,false };
struct course pe = { 7,OTHER,false };
void course_start_up(void)
{
	int i;
	for (i = 0; i < cal.max_level; i++) //΢����
	{
		cal.energy_cost[i] = i + 1; //��������1/2/3/4/5
		cal.gold_gain[i] = 40 * (i + 1); //����40/80/120/160/200
	}
	for (i = 0; i < l_a.max_level; i++) //���Դ���
	{
		l_a.energy_cost[i] = 2 * i + 1; //��������1/3/5
		l_a.gold_gain[i] = 60 * (i + 1); //����60/120/180
	}
	for (i = 0; i < p_a_s.max_level; i++) //������������ͳ��
	{
		p_a_s.energy_cost[i] = 2 * i + 1; //��������1/3/5
		p_a_s.gold_gain[i] = 70 * (i + 1); //����70/140/210
	}
	for (i = 0; i < g_p.max_level; i++) //��ͨ����
	{
		g_p.energy_cost[i] = i + 1; //��������1/2/3/4/5
		g_p.gold_gain[i] = 40 * (i + 1); //����40/80/120/160/200
	}
	for (i = 0; i < p_o_c.max_level; i++) //��ѧԭ��
	{
		p_o_c.energy_cost[i] = 2 * i + 1; //��������1/3/5
		p_o_c.gold_gain[i] = 60 * (i + 1); //����60/120/180
	}
	for (i = 0; i < i_e_c.max_level; i++) //�޻�Ԫ�ػ�ѧ
	{
		i_e_c.energy_cost[i] = 2 * i + 1; //��������1/3/5
		i_e_c.gold_gain[i] = 60 * (i + 1); //����60/120/180
	}
	for (i = 0; i < o_c.max_level; i++) //�л���ѧ
	{
		o_c.energy_cost[i] = i + 1; //��������1/2/3/4/5
		o_c.gold_gain[i] = 20 * (int)(pow(2, i)); //����20/40/80/160/320
	}
	for (i = 0; i < p_c.max_level; i++) //����ѧ
	{
		p_c.energy_cost[i] = 2 * (i + 1); //��������2/4/6/8
		if (i != p_c.max_level - 1) //����80/160/240/360
			p_c.gold_gain[i] = 80 * (i + 1);
		else
			p_c.gold_gain[i] = 360;
	}
	for (i = 0; i < s_c.max_level; i++) //�ṹ��ѧ
	{
		s_c.energy_cost[i] = 2 * (i + 1); //��������2/4/6
		s_c.gold_gain[i] = 80 * (i + 1); //����80/160/240
	}
	for (i = 0; i < a_c.max_level; i++) //������ѧ
	{
		a_c.energy_cost[i] = (int)(pow(2, i)); //��������1/2/4
		a_c.gold_gain[i] = 60 + 40 * i; //����60/100/140
	}
	for (i = 0; i < i_a.max_level; i++) //��������
	{
		i_a.energy_cost[i] = 2 * i + 1; //��������1/3/5
		i_a.gold_gain[i] = 80 + 40 * i; //����80/120/160
	}
	for (i = 0; i < b_o_c_e.max_level; i++) //��ѧ���������
	{
		b_o_c_e.energy_cost[i] = 2 * i + 1; //��������1/3/5
		b_o_c_e.gold_gain[i] = 20 + 40 * i; //����20/60/100
	}
	for (i = 0; i < c_p.max_level; i++) //C���Գ�����ƻ���
	{
		c_p.energy_cost[i] = 2 * (i + 1); //��������2/4/6
		c_p.gold_gain[i] = 60 * (int)(pow(2, i)); //����60/120/240
	}
	for (i = 0; i < eng.max_level; i++) //��ѧӢ��
	{
		eng.energy_cost[i] = i + 1; //��������1/2/3/4/5/6/7
		if (i >= eng.max_level - 2) //����40/60/80/100/120/160/200
			eng.gold_gain[i] = 40 * i - 40;
		else
			eng.gold_gain[i] = 40 + 20 * i;
	}
	for (i = 0; i < p_a_i.max_level; i++) //����������˼�����ר��
	{
		p_a_i.energy_cost[i] = i + 1; //��������1/2/3/4/5/6/7
		if (i >= p_a_i.max_level - 2) //����20/40/60/80/100/130/170
			p_a_i.gold_gain[i] = 40 * i - 70;
		else
			p_a_i.gold_gain[i] = 20 * (i + 1);
	}
	for (i = 0; i < pe.max_level; i++) //����
	{
		pe.energy_cost[i] = i + 1; //��������1/2/3/4/5/6/7
		if (i >= pe.max_level - 2) //����20/40/60/80/100/130/170
			pe.gold_gain[i] = 40 * i - 70;
		else
			pe.gold_gain[i] = 20 * (i + 1);
	}
}

/*�浵����*/
void save_game(void)
{
	FILE* documents;
	documents = fopen("D:\\C_Project_Resource\\documents.txt", "w");
	fwrite(&playerA, sizeof(struct player), 1, documents);
	fwrite(&playerB, sizeof(struct player), 1, documents);
	fwrite(&playerC, sizeof(struct player), 1, documents);
	fwrite(&playerD, sizeof(struct player), 1, documents);
	fwrite(&cal, sizeof(struct course), 1, documents);
	fwrite(&l_a, sizeof(struct course), 1, documents);
	fwrite(&p_a_s, sizeof(struct course), 1, documents);
	fwrite(&g_p, sizeof(struct course), 1, documents);
	fwrite(&p_o_c, sizeof(struct course), 1, documents);
	fwrite(&i_e_c, sizeof(struct course), 1, documents);
	fwrite(&o_c, sizeof(struct course), 1, documents);
	fwrite(&p_c, sizeof(struct course), 1, documents);
	fwrite(&s_c, sizeof(struct course), 1, documents);
	fwrite(&a_c, sizeof(struct course), 1, documents);
	fwrite(&i_a, sizeof(struct course), 1, documents);
	fwrite(&b_o_c_e, sizeof(struct course), 1, documents);
	fwrite(&c_p, sizeof(struct course), 1, documents);
	fwrite(&eng, sizeof(struct course), 1, documents);
	fwrite(&p_a_i, sizeof(struct course), 1, documents);
	fwrite(&pe, sizeof(struct course), 1, documents);
	fwrite(&Round, sizeof(int), 1, documents);
	fclose(documents);
}
/*��������*/
void load_game(void)
{
	FILE* documents;
	documents = fopen("D:\\C_Project_Resource\\documents.txt", "r");
	fread(&playerA, sizeof(struct player), 1, documents);
	fread(&playerB, sizeof(struct player), 1, documents);
	fread(&playerC, sizeof(struct player), 1, documents);
	fread(&playerD, sizeof(struct player), 1, documents);
	fread(&cal, sizeof(struct course), 1, documents);
	fread(&l_a, sizeof(struct course), 1, documents);
	fread(&p_a_s, sizeof(struct course), 1, documents);
	fread(&g_p, sizeof(struct course), 1, documents);
	fread(&p_o_c, sizeof(struct course), 1, documents);
	fread(&i_e_c, sizeof(struct course), 1, documents);
	fread(&o_c, sizeof(struct course), 1, documents);
	fread(&p_c, sizeof(struct course), 1, documents);
	fread(&s_c, sizeof(struct course), 1, documents);
	fread(&a_c, sizeof(struct course), 1, documents);
	fread(&i_a, sizeof(struct course), 1, documents);
	fread(&b_o_c_e, sizeof(struct course), 1, documents);
	fread(&c_p, sizeof(struct course), 1, documents);
	fread(&eng, sizeof(struct course), 1, documents);
	fread(&p_a_i, sizeof(struct course), 1, documents);
	fread(&pe, sizeof(struct course), 1, documents);
	fread(&Round, sizeof(int), 1, documents);
	fclose(documents);
}

/*�����Ϣ��ʾ����*/
void show_player(struct player* playerX, bool end)
{
	settextstyle(18, 0, _T("����"));
	TCHAR s[50];
	RECT r;
	if (!end) //�ǻغϽ���ͨ����ɫ���������Ϣ
	{
		switch (playerX->name)
		{
		case 'A':
			settextcolor(LIGHTRED);
			_stprintf_s(s, _T("���A\n������%d\n��Ǯ��%d"), playerX->energy, playerX->gold);
			r = { 120,123,280,343 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'B':
			settextcolor(BLUE);
			_stprintf_s(s, _T("���B\n������%d\n��Ǯ��%d"), playerX->energy, playerX->gold);
			r = { 420,123,580,343 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'C':
			settextcolor(MAGENTA);
			_stprintf_s(s, _T("���C\n������%d\n��Ǯ��%d"), playerX->energy, playerX->gold);
			r = { 120,363,280,583 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'D':
			settextcolor(GREEN);
			_stprintf_s(s, _T("���D\n������%d\n��Ǯ��%d"), playerX->energy, playerX->gold);
			r = { 420,363,580,583 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		}
	}
	else //�غϽ���ͨ����ɫ������Ϣ
	{
		settextcolor(WHITE);
		switch (playerX->name)
		{
		case 'A':
			_stprintf_s(s, _T("���A\n������%d\n��Ǯ��%d"), playerX->energy, playerX->gold);
			r = { 120,123,280,343 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'B':
			_stprintf_s(s, _T("���B\n������%d\n��Ǯ��%d"), playerX->energy, playerX->gold);
			r = { 420,123,580,343 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'C':
			_stprintf_s(s, _T("���C\n������%d\n��Ǯ��%d"), playerX->energy, playerX->gold);
			r = { 120,363,280,583 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'D':
			_stprintf_s(s, _T("���D\n������%d\n��Ǯ��%d"), playerX->energy, playerX->gold);
			r = { 420,363,580,583 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		}
	}
}
/*״̬����ʾ����*/
void show_state(struct player* playerX)
{
	IMAGE state;
	switch (playerX->name)
	{
	case 'A':
		if (playerX->state[REST])
			loadimage(&state, _T("D:\\C_Project_Resource\\0.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(120, 180, &state);
		if (playerX->state[EXPERIMENT])
			loadimage(&state, _T("D:\\C_Project_Resource\\1.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(147, 180, &state);
		if (playerX->state[BORROWING])
			loadimage(&state, _T("D:\\C_Project_Resource\\2.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(174, 180, &state);
		if (playerX->state[STUDYING])
			loadimage(&state, _T("D:\\C_Project_Resource\\3.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(200, 180, &state);
		if (playerX->state[SAVING])
			loadimage(&state, _T("D:\\C_Project_Resource\\4.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(227, 180, &state);
		if (playerX->state[LOAN])
			loadimage(&state, _T("D:\\C_Project_Resource\\5.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(254, 180, &state);
		if (playerX->state[EASIER])
			loadimage(&state, _T("D:\\C_Project_Resource\\6.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(120, 210, &state);
		if (playerX->state[RECOVERING])
			loadimage(&state, _T("D:\\C_Project_Resource\\7.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(147, 210, &state);
		if (playerX->state[FRESH])
			loadimage(&state, _T("D:\\C_Project_Resource\\8.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(174, 210, &state);
		if (playerX->state[SKILLFUL])
			loadimage(&state, _T("D:\\C_Project_Resource\\9.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(200, 210, &state);
		if (playerX->state[UNFAMILIAR])
			loadimage(&state, _T("D:\\C_Project_Resource\\10.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(227, 210, &state);
		if (playerX->state[FAILURE])
			loadimage(&state, _T("D:\\C_Project_Resource\\11.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(254, 210, &state);
		break;
	case 'B':
		if (playerX->state[REST])
			loadimage(&state, _T("D:\\C_Project_Resource\\0.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(420, 180, &state);
		if (playerX->state[EXPERIMENT])
			loadimage(&state, _T("D:\\C_Project_Resource\\1.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(447, 180, &state);
		if (playerX->state[BORROWING])
			loadimage(&state, _T("D:\\C_Project_Resource\\2.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(474, 180, &state);
		if (playerX->state[STUDYING])
			loadimage(&state, _T("D:\\C_Project_Resource\\3.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(500, 180, &state);
		if (playerX->state[SAVING])
			loadimage(&state, _T("D:\\C_Project_Resource\\4.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(527, 180, &state);
		if (playerX->state[LOAN])
			loadimage(&state, _T("D:\\C_Project_Resource\\5.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(554, 180, &state);
		if (playerX->state[EASIER])
			loadimage(&state, _T("D:\\C_Project_Resource\\6.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(420, 210, &state);
		if (playerX->state[RECOVERING])
			loadimage(&state, _T("D:\\C_Project_Resource\\7.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(447, 210, &state);
		if (playerX->state[FRESH])
			loadimage(&state, _T("D:\\C_Project_Resource\\8.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(474, 210, &state);
		if (playerX->state[SKILLFUL])
			loadimage(&state, _T("D:\\C_Project_Resource\\9.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(500, 210, &state);
		if (playerX->state[UNFAMILIAR])
			loadimage(&state, _T("D:\\C_Project_Resource\\10.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(527, 210, &state);
		if (playerX->state[FAILURE])
			loadimage(&state, _T("D:\\C_Project_Resource\\11.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(554, 210, &state);
		break;
	case 'C':
		if (playerX->state[REST])
			loadimage(&state, _T("D:\\C_Project_Resource\\0.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(120, 420, &state);
		if (playerX->state[EXPERIMENT])
			loadimage(&state, _T("D:\\C_Project_Resource\\1.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(147, 420, &state);
		if (playerX->state[BORROWING])
			loadimage(&state, _T("D:\\C_Project_Resource\\2.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(174, 420, &state);
		if (playerX->state[STUDYING])
			loadimage(&state, _T("D:\\C_Project_Resource\\3.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(200, 420, &state);
		if (playerX->state[SAVING])
			loadimage(&state, _T("D:\\C_Project_Resource\\4.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(227, 420, &state);
		if (playerX->state[LOAN])
			loadimage(&state, _T("D:\\C_Project_Resource\\5.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(254, 420, &state);
		if (playerX->state[EASIER])
			loadimage(&state, _T("D:\\C_Project_Resource\\6.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(120, 450, &state);
		if (playerX->state[RECOVERING])
			loadimage(&state, _T("D:\\C_Project_Resource\\7.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(147, 450, &state);
		if (playerX->state[FRESH])
			loadimage(&state, _T("D:\\C_Project_Resource\\8.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(174, 450, &state);
		if (playerX->state[SKILLFUL])
			loadimage(&state, _T("D:\\C_Project_Resource\\9.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(200, 450, &state);
		if (playerX->state[UNFAMILIAR])
			loadimage(&state, _T("D:\\C_Project_Resource\\10.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(227, 450, &state);
		if (playerX->state[FAILURE])
			loadimage(&state, _T("D:\\C_Project_Resource\\11.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(254, 450, &state);
		break;
	case 'D':
		if (playerX->state[REST])
			loadimage(&state, _T("D:\\C_Project_Resource\\0.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(420, 420, &state);
		if (playerX->state[EXPERIMENT])
			loadimage(&state, _T("D:\\C_Project_Resource\\1.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(447, 420, &state);
		if (playerX->state[BORROWING])
			loadimage(&state, _T("D:\\C_Project_Resource\\2.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(473, 420, &state);
		if (playerX->state[STUDYING])
			loadimage(&state, _T("D:\\C_Project_Resource\\3.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(500, 420, &state);
		if (playerX->state[SAVING])
			loadimage(&state, _T("D:\\C_Project_Resource\\4.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(527, 420, &state);
		if (playerX->state[LOAN])
			loadimage(&state, _T("D:\\C_Project_Resource\\5.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(554, 420, &state);
		if (playerX->state[EASIER])
			loadimage(&state, _T("D:\\C_Project_Resource\\6.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(420, 450, &state);
		if (playerX->state[RECOVERING])
			loadimage(&state, _T("D:\\C_Project_Resource\\7.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(447, 450, &state);
		if (playerX->state[FRESH])
			loadimage(&state, _T("D:\\C_Project_Resource\\8.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(474, 450, &state);
		if (playerX->state[SKILLFUL])
			loadimage(&state, _T("D:\\C_Project_Resource\\9.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(500, 450, &state);
		if (playerX->state[UNFAMILIAR])
			loadimage(&state, _T("D:\\C_Project_Resource\\10.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(527, 450, &state);
		if (playerX->state[FAILURE])
			loadimage(&state, _T("D:\\C_Project_Resource\\11.jpg"));
		else
			loadimage(&state, _T("D:\\C_Project_Resource\\bk.jpg"));
		putimage(554, 450, &state);
		break;
	}
}
/*��������ʾ����*/
void show_item(void)
{
	IMAGE item;
	BeginBatchDraw();
	loadimage(&item, _T("D:\\C_Project_Resource\\�ٱ�����.jpg"));
	putimage(120, 260, &item);
	putimage(420, 260, &item);
	putimage(120, 500, &item);
	putimage(420, 500, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\ˢҹ������.jpg"));
	putimage(160, 260, &item);
	putimage(460, 260, &item);
	putimage(160, 500, &item);
	putimage(460, 500, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\���λ�λ.jpg"));
	putimage(200, 260, &item);
	putimage(500, 260, &item);
	putimage(200, 500, &item);
	putimage(500, 500, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\��������.jpg"));
	putimage(240, 260, &item);
	putimage(540, 260, &item);
	putimage(240, 500, &item);
	putimage(540, 500, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\ѧϰ����.jpg"));
	putimage(120, 300, &item);
	putimage(420, 300, &item);
	putimage(120, 540, &item);
	putimage(420, 540, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\�������֤.jpg"));
	putimage(160, 300, &item);
	putimage(460, 300, &item);
	putimage(160, 540, &item);
	putimage(460, 540, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\���׶���.jpg"));
	putimage(200, 300, &item);
	putimage(500, 300, &item);
	putimage(200, 540, &item);
	putimage(500, 540, &item);
	EndBatchDraw();
}
/*��������������*/
void item_number(struct player* playerX)
{
	TCHAR number[5];
	settextcolor(BLACK);
	settextstyle(15, 0, _T("����"));
	switch (playerX->name)
	{
	case 'A':
		_stprintf_s(number, _T("%d"), playerA.item[MAGIC_DICE]);
		outtextxy(120, 260, number);
		_stprintf_s(number, _T("%d"), playerA.item[STAYING_UP_DOOR]);
		outtextxy(160, 260, number);
		_stprintf_s(number, _T("%d"), playerA.item[SWAP]);
		outtextxy(200, 260, number);
		_stprintf_s(number, _T("%d"), playerA.item[ENERGY_DRINK]);
		outtextxy(240, 260, number);
		_stprintf_s(number, _T("%d"), playerA.item[LEARNING_MATERIALS]);
		outtextxy(120, 300, number);
		_stprintf_s(number, _T("%d"), playerA.item[TRADING_LICENSE]);
		outtextxy(160, 300, number);
		_stprintf_s(number, _T("%d"), playerA.item[ADVANCED_READINGS]);
		outtextxy(200, 300, number);
		break;
	case 'B':
		_stprintf_s(number, _T("%d"), playerB.item[MAGIC_DICE]);
		outtextxy(420, 260, number);
		_stprintf_s(number, _T("%d"), playerB.item[STAYING_UP_DOOR]);
		outtextxy(460, 260, number);
		_stprintf_s(number, _T("%d"), playerB.item[SWAP]);
		outtextxy(500, 260, number);
		_stprintf_s(number, _T("%d"), playerB.item[ENERGY_DRINK]);
		outtextxy(540, 260, number);
		_stprintf_s(number, _T("%d"), playerB.item[LEARNING_MATERIALS]);
		outtextxy(420, 300, number);
		_stprintf_s(number, _T("%d"), playerB.item[TRADING_LICENSE]);
		outtextxy(460, 300, number);
		_stprintf_s(number, _T("%d"), playerB.item[ADVANCED_READINGS]);
		outtextxy(500, 300, number);
		break;
	case 'C':
		_stprintf_s(number, _T("%d"), playerC.item[MAGIC_DICE]);
		outtextxy(120, 500, number);
		_stprintf_s(number, _T("%d"), playerC.item[STAYING_UP_DOOR]);
		outtextxy(160, 500, number);
		_stprintf_s(number, _T("%d"), playerC.item[SWAP]);
		outtextxy(200, 500, number);
		_stprintf_s(number, _T("%d"), playerC.item[ENERGY_DRINK]);
		outtextxy(240, 500, number);
		_stprintf_s(number, _T("%d"), playerC.item[LEARNING_MATERIALS]);
		outtextxy(120, 540, number);
		_stprintf_s(number, _T("%d"), playerC.item[TRADING_LICENSE]);
		outtextxy(160, 540, number);
		_stprintf_s(number, _T("%d"), playerC.item[ADVANCED_READINGS]);
		outtextxy(200, 540, number);
		break;
	case 'D':
		_stprintf_s(number, _T("%d"), playerD.item[MAGIC_DICE]);
		outtextxy(420, 500, number);
		_stprintf_s(number, _T("%d"), playerD.item[STAYING_UP_DOOR]);
		outtextxy(460, 500, number);
		_stprintf_s(number, _T("%d"), playerD.item[SWAP]);
		outtextxy(500, 500, number);
		_stprintf_s(number, _T("%d"), playerD.item[ENERGY_DRINK]);
		outtextxy(540, 500, number);
		_stprintf_s(number, _T("%d"), playerD.item[LEARNING_MATERIALS]);
		outtextxy(420, 540, number);
		_stprintf_s(number, _T("%d"), playerD.item[TRADING_LICENSE]);
		outtextxy(460, 540, number);
		_stprintf_s(number, _T("%d"), playerD.item[ADVANCED_READINGS]);
		outtextxy(500, 540, number);
	}
}

/*�γ���Ϣ��ʾ����*/
void show_course_information(void)
{
	TCHAR s[80];
	RECT r;
	int i = 0;
	TCHAR sn[8];
	settextstyle(12, 0, _T("����"));
	BeginBatchDraw();
	/*΢����*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), cal.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < cal.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), cal.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < cal.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), cal.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 500,625,600,695 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*���Դ���*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), l_a.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < l_a.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), l_a.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < l_a.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), l_a.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 400,625,500,695 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*������������ͳ��*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), p_a_s.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < p_a_s.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_a_s.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < p_a_s.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_a_s.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 200,625,300,695 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��ѧԭ��*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), p_o_c.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < p_o_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_o_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < p_o_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_o_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,525,100,595 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*�޻�Ԫ�ػ�ѧ*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), i_e_c.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < i_e_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), i_e_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < i_e_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), i_e_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,425,100,495 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*�л���ѧ*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), o_c.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < o_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), o_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < o_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), o_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,325,100,395 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*����ѧ*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), p_c.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < p_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < p_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,225,100,295 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*�ṹ��ѧ*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), s_c.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < s_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), s_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < s_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), s_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,125,100,195 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*������ѧ*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), a_c.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < a_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), a_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < a_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), a_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 100,25,200,95 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��������*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), i_a.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < i_a.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), i_a.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < i_a.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), i_a.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 200,25,300,95 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��ѧ���������*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), b_o_c_e.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < b_o_c_e.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), b_o_c_e.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < b_o_c_e.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), b_o_c_e.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 400,25,500,95 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*C���Գ�����ƻ���*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), c_p.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < c_p.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), c_p.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < c_p.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), c_p.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 500,25,600,95 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��ѧӢ��*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), eng.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < eng.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), eng.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < eng.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), eng.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 600,125,700,195 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*����������˼�����ר��*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), p_a_i.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < p_a_i.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_a_i.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < p_a_i.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_a_i.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 600,325,700,395 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*����*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), pe.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < pe.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), pe.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < pe.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), pe.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 600,425,700,495 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��ͨ����*/
	_stprintf_s(s, _T("�γ���ߵȼ���%d"), g_p.max_level);
	_tcscat_s(s, _T("\n�������ģ�\n"));
	for (i = 0; i < g_p.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), g_p.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n���棺\n"));
	for (i = 0; i < g_p.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), g_p.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 600,525,700,595 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	EndBatchDraw();
}
/*�γ̵ȼ���ʾ����*/
void show_course_level(void)
{
	TCHAR s[80];
	RECT r;
	settextstyle(16, 0, _T("Ink Free"));
	/*΢����*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), cal.playerA_level, cal.max_level, cal.playerB_level, cal.max_level, cal.playerC_level, cal.max_level, cal.playerD_level, cal.max_level);
	r = { 500,630,600,700 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*���Դ���*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), l_a.playerA_level, l_a.max_level, l_a.playerB_level, l_a.max_level, l_a.playerC_level, l_a.max_level, l_a.playerD_level, l_a.max_level);
	r = { 400,630,500,700 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*������������ͳ��*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), p_a_s.playerA_level, p_a_s.max_level, p_a_s.playerB_level, p_a_s.max_level, p_a_s.playerC_level, p_a_s.max_level, p_a_s.playerD_level, p_a_s.max_level);
	r = { 200,630,300,700 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��ѧԭ��*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), p_o_c.playerA_level, p_o_c.max_level, p_o_c.playerB_level, p_o_c.max_level, p_o_c.playerC_level, p_o_c.max_level, p_o_c.playerD_level, p_o_c.max_level);
	r = { 0,530,100,600 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*�޻�Ԫ�ػ�ѧ*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), i_e_c.playerA_level, i_e_c.max_level, i_e_c.playerB_level, i_e_c.max_level, i_e_c.playerC_level, i_e_c.max_level, i_e_c.playerD_level, i_e_c.max_level);
	r = { 0,430,100,500 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*�л���ѧ*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), o_c.playerA_level, o_c.max_level, o_c.playerB_level, o_c.max_level, o_c.playerC_level, o_c.max_level, o_c.playerD_level, o_c.max_level);
	r = { 0,330,100,400 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*����ѧ*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), p_c.playerA_level, p_c.max_level, p_c.playerB_level, p_c.max_level, p_c.playerC_level, p_c.max_level, p_c.playerD_level, p_c.max_level);
	r = { 0,230,100,300 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*�ṹ��ѧ*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), s_c.playerA_level, s_c.max_level, s_c.playerB_level, s_c.max_level, s_c.playerC_level, s_c.max_level, s_c.playerD_level, s_c.max_level);
	r = { 0,130,100,200 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*������ѧ*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), a_c.playerA_level, a_c.max_level, a_c.playerB_level, a_c.max_level, a_c.playerC_level, a_c.max_level, a_c.playerD_level, a_c.max_level);
	r = { 100,30,200,100 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��������*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), i_a.playerA_level, i_a.max_level, i_a.playerB_level, i_a.max_level, i_a.playerC_level, i_a.max_level, i_a.playerD_level, i_a.max_level);
	r = { 200,30,300,100 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��ѧ���������*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), b_o_c_e.playerA_level, b_o_c_e.max_level, b_o_c_e.playerB_level, b_o_c_e.max_level, b_o_c_e.playerC_level, b_o_c_e.max_level, b_o_c_e.playerD_level, b_o_c_e.max_level);
	r = { 400,30,500,100 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*C���Գ�����ƻ���*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), c_p.playerA_level, c_p.max_level, c_p.playerB_level, c_p.max_level, c_p.playerC_level, c_p.max_level, c_p.playerD_level, c_p.max_level);
	r = { 500,30,600,100 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��ѧӢ��*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), eng.playerA_level, eng.max_level, eng.playerB_level, eng.max_level, eng.playerC_level, eng.max_level, eng.playerD_level, eng.max_level);
	r = { 600,130,700,200 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*����������˼�����ר��*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), p_a_i.playerA_level, p_a_i.max_level, p_a_i.playerB_level, p_a_i.max_level, p_a_i.playerC_level, p_a_i.max_level, p_a_i.playerD_level, p_a_i.max_level);
	r = { 600,330,700,400 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*����*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), pe.playerA_level, pe.max_level, pe.playerB_level, pe.max_level, pe.playerC_level, pe.max_level, pe.playerD_level, pe.max_level);
	r = { 600,430,700,500 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*��ͨ����*/
	_stprintf_s(s, _T("level A��%d/%d\nlevel B��%d/%d\nlevel C��%d/%d\nlevel D��%d/%d"), g_p.playerA_level, g_p.max_level, g_p.playerB_level, g_p.max_level, g_p.playerC_level, g_p.max_level, g_p.playerD_level, g_p.max_level);
	r = { 600,530,700,600 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
}

/*λ�û��ƺ���*/
void draw_position(struct player* playerX, int x, int y)
{
	switch (playerX->position)
	{
	case START:
		solidcircle(650 + x, 650 + y, 4);
		break;
	case CAL:
		solidcircle(550 + x, 650 + y, 4);
		break;
	case L_A:
		solidcircle(450 + x, 650 + y, 4);
		break;
	case ENTRANCE:
		solidcircle(350 + x, 650 + y, 4);
		break;
	case P_A_S:
		solidcircle(250 + x, 650 + y, 4);
		break;
	case EVENT_CARD:
		solidcircle(150 + x, 650 + y, 4);
		break;
	case LABORATORY:
		solidcircle(50 + x, 650 + y, 4);
		break;
	case P_O_C:
		solidcircle(50 + x, 550 + y, 4);
		break;
	case I_E_C:
		solidcircle(50 + x, 450 + y, 4);
		break;
	case O_C:
		solidcircle(50 + x, 350 + y, 4);
		break;
	case P_C:
		solidcircle(50 + x, 250 + y, 4);
		break;
	case S_C:
		solidcircle(50 + x, 150 + y, 4);
		break;
	case LIBRARY:
		solidcircle(50 + x, 50 + y, 4);
		break;
	case A_C:
		solidcircle(150 + x, 50 + y, 4);
		break;
	case I_A:
		solidcircle(250 + x, 50 + y, 4);
		break;
	case EXIT:
		solidcircle(350 + x, 50 + y, 4);
		break;
	case B_O_C_E:
		solidcircle(450 + x, 50 + y, 4);
		break;
	case C_P:
		solidcircle(550 + x, 50 + y, 4);
		break;
	case STUDY_ROOM:
		solidcircle(650 + x, 50 + y, 4);
		break;
	case ENG:
		solidcircle(650 + x, 150 + y, 4);
		break;
	case ITEM_CARD:
		solidcircle(650 + x, 250 + y, 4);
		break;
	case P_A_I:
		solidcircle(650 + x, 350 + y, 4);
		break;
	case PE:
		solidcircle(650 + x, 450 + y, 4);
		break;
	case G_P:
		solidcircle(650 + x, 550 + y, 4);
		break;
	case B_M:
		solidcircle(350 + x, 550 + y, 4);
		break;
	case C_M:
		solidcircle(350 + x, 450 + y, 4);
		break;
	case M_S_B:
		solidcircle(350 + x, 350 + y, 4);
		break;
	case E_S:
		solidcircle(350 + x, 250 + y, 4);
		break;
	case B_D:
		solidcircle(350 + x, 150 + y, 4);
		break;
	}
}
/*λ��ѡ����*/
void select_position(struct player* playerX, bool leave)
{
	if (!leave) //����λ��ͨ����ɫԲ��������λ��
	{
		switch (playerX->name)
		{
		case 'A':
			setfillcolor(LIGHTRED);
			draw_position(playerX, -43, 20);
			break;
		case 'B':
			setfillcolor(BLUE);
			draw_position(playerX, 43, 20);
			break;
		case 'C':
			setfillcolor(MAGENTA);
			draw_position(playerX, -43, 40);
			break;
		case 'D':
			setfillcolor(GREEN);
			draw_position(playerX, 43, 40);
			break;
		}
	}
	else //�뿪λ��ͨ����ɫԲ��������λ��
	{
		setfillcolor(WHITE);
		switch (playerX->name)
		{
		case 'A':
			draw_position(playerX, -43, 20);
			break;
		case 'B':
			draw_position(playerX, 43, 20);
			break;
		case 'C':
			draw_position(playerX, -43, 40);
			break;
		case 'D':
			draw_position(playerX, 43, 40);
			break;
		}
	}
}

/*ʧ����ҿγ̵ȼ���������*/
void delete_course_level(struct player* playerX)
{
	int height = 16;
	int k;
	switch (playerX->name)
	{
	case 'A':
		k = 0;
		break;
	case 'B':
		k = 1;
		break;
	case 'C':
		k = 2;
		break;
	case 'D':
		k = 3;
		break;
	}
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 3);
	line(515, 638 + k * height, 585, 638 + k * height);
	line(415, 638 + k * height, 485, 638 + k * height);
	line(215, 638 + k * height, 285, 638 + k * height);
	line(15, 538 + k * height, 85, 538 + k * height);
	line(15, 438 + k * height, 85, 438 + k * height);
	line(15, 338 + k * height, 85, 338 + k * height);
	line(15, 238 + k * height, 85, 238 + k * height);
	line(15, 138 + k * height, 85, 138 + k * height);
	line(115, 38 + k * height, 185, 38 + k * height);
	line(215, 38 + k * height, 285, 38 + k * height);
	line(415, 38 + k * height, 485, 38 + k * height);
	line(515, 38 + k * height, 585, 38 + k * height);
	line(615, 138 + k * height, 685, 138 + k * height);
	line(615, 338 + k * height, 685, 338 + k * height);
	line(615, 438 + k * height, 685, 438 + k * height);
	line(615, 538 + k * height, 685, 538 + k * height);
}
/*�γ̲鿴����*/
void view_course(void)
{
	BeginBatchDraw();
	setlinecolor(RED);
	if (!playerA.state[FAILURE])
		select_position(&playerA, false);
	if (!playerB.state[FAILURE])
		select_position(&playerB, false);
	if (!playerC.state[FAILURE])
		select_position(&playerC, false);
	if (!playerD.state[FAILURE])
		select_position(&playerD, false);
	EndBatchDraw();
	_stprintf_s(guide_text, _T("����Ҽ��鿴�γ���Ϣ\n�����������鿴"));
	settextcolor(BLACK);
	settextstyle(15, 0, _T("����"));
	drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_RBUTTONDOWN) //��������Ҽ��鿴�γ���Ϣ
			{
				BeginBatchDraw();
				settextcolor(WHITE);
				show_course_level();
				setlinecolor(WHITE);
				if (playerA.state[FAILURE])
					delete_course_level(&playerA);
				if (playerB.state[FAILURE])
					delete_course_level(&playerB);
				if (playerC.state[FAILURE])
					delete_course_level(&playerC);
				if (playerD.state[FAILURE])
					delete_course_level(&playerD);
				settextcolor(BLACK);
				show_course_information();
				EndBatchDraw();
			}
			else if (m.uMsg == WM_RBUTTONUP) //�ɿ�����Ҽ���ʾ�γ̵ȼ�
			{
				BeginBatchDraw();
				settextcolor(WHITE);
				show_course_information();
				settextcolor(BLACK);
				show_course_level();
				setlinecolor(RED);
				if (playerA.state[FAILURE])
					delete_course_level(&playerA);
				if (playerB.state[FAILURE])
					delete_course_level(&playerB);
				if (playerC.state[FAILURE])
					delete_course_level(&playerC);
				if (playerD.state[FAILURE])
					delete_course_level(&playerD);
				EndBatchDraw();
			}
			else if (m.uMsg == WM_LBUTTONUP) //�����������鿴
			{
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK); //��ղ���ָ������
				break;
			}
			else
				FlushMouseMsgBuffer();
		}
		if (_kbhit())
			_getch();
	}
}

/*�ж�ʧ�ܺ���*/
void failure(struct player* playerX)
{
	if (playerX->energy <= 0 || playerX->gold < 0) //�����ľ����Ǯ�ľ���ʧ��
	{
		_stprintf_s(guide_text, _T("���%c�����������Ǯ���㡪��ʧ��"), playerX->name);
		settextcolor(BROWN);
		settextstyle(15, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		Sleep(1000);
		settextcolor(WHITE);
		settextstyle(15, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		select_position(playerX, true);
		for (int i = 0; i < (STATENUMBER - 1); i++)
			playerX->state[i] = false;
		for (int i = 0; i < ITEMNUMBER; i++)
			playerX->item[i] = 0;
		playerX->state[FAILURE] = true;
		playerX->rank = playernumber; //��������
		playernumber -= 1;
	}
}

/*�¼�������*/
void position(struct player*); //λ����Ӧ����ԭ��
void event_card(struct player* playerX)
{
	int i, j;
	i = rand() % EVENTNUMBER;
	j = rand() % 100;
	if (j >= 0 && j <= 2)
	{
		_tcscat_s(position_text, _T("һҹ������С�����¼���\n��ǰ��Ǯ����"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold *= 2;
		return;
	}
	if (j >= 10 && j <= 12)
	{
		_tcscat_s(position_text, _T("ʱ����϶��С�����¼���\n��������ˢҹ�������λ��"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		select_position(playerX, true);
		playerX->position = rand() % 24;
		select_position(playerX, false);
		return;
	}
	if (j >= 20 && j <= 22)
	{
		_tcscat_s(position_text, _T("ϴ��һ�գ�С�����¼���\nʧȥ��ǰ���еĵ���"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		for (int k = 0; k < ITEMNUMBER; k++)
			playerX->item[k] = 0;
		return;
	}
	if (j >= 30 && j <= 32)
	{
		_tcscat_s(position_text, _T("ج�Σ�С�����¼���\n�������루����ʣ��1�㾫��������Ϣһ�غ�"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (playerX->energy > 1)
			playerX->energy /= 2;
		playerX->state[REST] = true;
		return;
	}
	if (j >= 40 && j < 42)
	{
		_tcscat_s(position_text, _T("��ʦ��ָ�㣨С�����¼���\nͬʱ����״̬��������ѧϰ���Ƿ��켫��ʵ������������"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[EASIER] = true;
		playerX->state[SKILLFUL] = true;
		playerX->state[EXPERIMENT] = true;
		return;
	}
	switch (i)
	{
	case LATE:
		_tcscat_s(position_text, _T("�ٵ�\n����״̬������Ϣ������һ�غ�"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[REST] = true;
		break;
	case OVERPLAY:
		_tcscat_s(position_text, _T("��������������\n����״̬�������裺�´ογ�ѧϰ��������+3"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[UNFAMILIAR] = true;
		break;
	case STAY_UP:
		_tcscat_s(position_text, _T("��ҹ����Ϸ\n����-2"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy -= 2;
		break;
	case RECHARGE:
		_tcscat_s(position_text, _T("봽�\n��Ǯ-100"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold -= 100;
		break;
	case ILL:
		_tcscat_s(position_text, _T("��һ��\n����-5"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy -= 5;
		break;
	case BIRTHDAY:
		_tcscat_s(position_text, _T("��ף����\n����+7����Ǯ-300"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 7;
		playerX->gold -= 300;
		break;
	case PART_TIME_JOB:
		_tcscat_s(position_text, _T("��ĩ��ְ\n����-3����Ǯ+200"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy -= 3;
		playerX->gold += 200;
		break;
	case LIVING_EXEPENSES:
		_tcscat_s(position_text, _T("�µ������\n��Ǯ+150"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold += 150;
		break;
	case DDL_END:
		_tcscat_s(position_text, _T("ddl�ս�\n����+6"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 6;
		break;
	case SCHOLARSHIP:
		_tcscat_s(position_text, _T("��ѧ��\n��Ǯ+300"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold += 300;
		break;
	case SAVE:
		_tcscat_s(position_text, _T("����\n��Ǯ-200��������������غ�ÿ�غϽ�����Ǯ+60������״̬�������У�"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold -= 200;
		playerX->state[SAVING] = true;
		break;
	case CAMPUS_LOAN:
		_tcscat_s(position_text, _T("У԰��\n��Ǯ+400��������������غ�ÿ�غϽ�����Ǯ-100������״̬�����"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold += 400;
		playerX->state[LOAN] = true;
		break;
	}
	failure(playerX);
}
/*���߿�����*/
void item_card(struct player* playerX)
{
	int i;
	for (int j = 0; j < 2; j++)
	{
		i = rand() % (ITEMNUMBER - 1); //���׶��ﲻ��ͨ�����߿�������
		playerX->item[i] += 1;
		switch (i)
		{
		case MAGIC_DICE:
			_tcscat_s(position_text, _T("��ðٱ�����\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case TRADING_LICENSE:
			_tcscat_s(position_text, _T("��ý������֤\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case LEARNING_MATERIALS:
			_tcscat_s(position_text, _T("���ѧϰ����\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case STAYING_UP_DOOR:
			_tcscat_s(position_text, _T("���ˢҹ������\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case SWAP:
			_tcscat_s(position_text, _T("������λ�λ\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case ENERGY_DRINK:
			_tcscat_s(position_text, _T("�����������\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		}
	}
}

/*����ӳɺ���*/
int extra(struct player* playerX, struct course* courseX)
{
	int extra_gold = 0;
	if (courseX->category == MAJOR) //רҵ������ӳɣ�����γ�+60��������γ�+40��ÿ�����׶���+20
	{
		switch (playerX->name)
		{
		case 'A':
			if (cal.playerA_level > 0 && l_a.playerA_level > 0 && p_a_s.playerA_level > 0 && g_p.playerA_level > 0)
			{
				_stprintf_s(guide_text, _T("���A��ѧϰ��������ͨʶ�γ̣�רҵ�γ�����+60"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 60;
			}
			if (b_o_c_e.playerA_level > 0 && c_p.playerA_level > 0)
			{
				_stprintf_s(guide_text, _T("���A��ѧϰ���м����ͨʶ�γ̣�רҵ�γ�����+40"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 40;
			}
			extra_gold += playerA.item[ADVANCED_READINGS] * 30;
			break;
		case 'B':
			if (cal.playerB_level > 0 && l_a.playerB_level > 0 && p_a_s.playerB_level > 0 && g_p.playerB_level > 0)
			{
				_stprintf_s(guide_text, _T("���B��ѧϰ��������ͨʶ�γ̣�רҵ�γ�����+60"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 60;
			}
			if (b_o_c_e.playerB_level > 0 && c_p.playerB_level > 0)
			{
				_stprintf_s(guide_text, _T("���B��ѧϰ���м����ͨʶ�γ̣�רҵ�γ�����+40"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 40;
			}
			extra_gold += playerB.item[ADVANCED_READINGS] * 30;
			break;
		case 'C':
			if (cal.playerC_level > 0 && l_a.playerC_level > 0 && p_a_s.playerC_level > 0 && g_p.playerC_level > 0)
			{
				_stprintf_s(guide_text, _T("���C��ѧϰ��������ͨʶ�γ̣�רҵ�γ�����+60"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 60;
			}
			if (b_o_c_e.playerC_level > 0 && c_p.playerC_level > 0)
			{
				_stprintf_s(guide_text, _T("���C��ѧϰ���м����ͨʶ�γ̣�רҵ�γ�����+40"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 40;
			}
			extra_gold += playerC.item[ADVANCED_READINGS] * 30;
			break;
		case 'D':
			if (cal.playerD_level > 0 && l_a.playerD_level > 0 && p_a_s.playerD_level > 0 && g_p.playerD_level > 0)
			{
				_stprintf_s(guide_text, _T("���D��ѧϰ��������ͨʶ�γ̣�רҵ�γ�����+60"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 60;
			}
			if (b_o_c_e.playerD_level > 0 && c_p.playerD_level > 0)
			{
				_stprintf_s(guide_text, _T("���D��ѧϰ���м����ͨʶ�γ̣�רҵ�γ�����+40"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 40;
			}
			extra_gold += playerD.item[ADVANCED_READINGS] * 30;
			break;
		}
	}
	return extra_gold;
}
/*��Ǯ���ɺ���*/
void pay(struct player* playerX, struct player* playerY, struct course* courseX)
{
	if (*playerY->level > * playerX->level && !playerY->state[FAILURE])
	{
		if (playerY->state[STUDYING])
		{
			_stprintf_s(guide_text, _T("���%c��ϰ�У�����������"), playerX->name);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(2000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			return;
		}
		else
		{
			int gold_gain;
			if (playerX->state[BORROWING])
				gold_gain = (courseX->gold_gain[*playerY->level - 1] + extra(playerY, courseX)) / 2;
			else
				gold_gain = courseX->gold_gain[*playerY->level - 1] + extra(playerY, courseX);
			_stprintf_s(guide_text, _T("���%c���ɸ����%c %d��Ǯ"), playerX->name, playerY->name, gold_gain);
			switch (playerY->name)
			{
			case 'A':
				settextcolor(LIGHTRED);
				break;
			case 'B':
				settextcolor(BLUE);
				break;
			case 'C':
				settextcolor(MAGENTA);
				break;
			case 'D':
				settextcolor(GREEN);
				break;
			}
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1500);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			playerX->gold -= gold_gain;
			playerY->gold += gold_gain;
		}
	}
}
/*��Ǯ�뾫�����Ľ��㺯��*/
bool cost(struct player* playerX, struct course* courseX)
{
	bool learned = false;
	char input;
	if (*playerX->level < courseX->max_level)
	{
		if ((*playerA.level <= *playerX->level || playerA.state[FAILURE]) && (*playerB.level <= *playerX->level || playerB.state[FAILURE]) && (*playerC.level <= *playerX->level || playerC.state[FAILURE]) && (*playerD.level <= *playerX->level || playerD.state[FAILURE])) //����ѧϰ��������ɽ�Ǯ
		{
			if (playerX->state[SKILLFUL])
			{
				_stprintf_s(guide_text, _T("״̬���Ƿ��켫\nL��ѧϰ�γ̣�����������ѧϰ��"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				input = _getch();
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				if (input == 'l' || input == 'L') //���¡�L��������ѧϰ������������ѧϰ
				{
					_stprintf_s(guide_text, _T("ѧϰ�ɹ�"));
					settextcolor(RED);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					BeginBatchDraw();
					settextcolor(WHITE);
					show_course_level();
					setlinecolor(WHITE);
					if (playerA.state[FAILURE])
						delete_course_level(&playerA);
					if (playerB.state[FAILURE])
						delete_course_level(&playerB);
					if (playerC.state[FAILURE])
						delete_course_level(&playerC);
					if (playerD.state[FAILURE])
						delete_course_level(&playerD);
					*playerX->level += 1;
					settextcolor(BLACK);
					show_course_level();
					setlinecolor(RED);
					if (playerA.state[FAILURE])
						delete_course_level(&playerA);
					if (playerB.state[FAILURE])
						delete_course_level(&playerB);
					if (playerC.state[FAILURE])
						delete_course_level(&playerC);
					if (playerD.state[FAILURE])
						delete_course_level(&playerD);
					EndBatchDraw();
					learned = true;
					playerX->state[SKILLFUL] = false;
				}
			}
			else
			{
				_stprintf_s(guide_text, _T("L��ѧϰ�γ̣�����������ѧϰ��"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				input = _getch();
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				if (input == 'l' || input == 'L') //���¡�L��������ѧϰ������������ѧϰ
				{
					int energy_cost = courseX->energy_cost[*playerX->level];
					if (playerX->state[EASIER])
					{
						_stprintf_s(guide_text, _T("״̬������ѧϰ"));
						settextcolor(BLACK);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						Sleep(1000);
						settextcolor(WHITE);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						if (energy_cost > 1)
							energy_cost /= 2;
					}
					if (playerX->state[UNFAMILIAR])
					{
						_stprintf_s(guide_text, _T("״̬������"));
						settextcolor(BLACK);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						Sleep(1000);
						settextcolor(WHITE);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						energy_cost += 3;
					}
					if (playerX->energy <= energy_cost)
					{
						_stprintf_s(guide_text, _T("�������㣬ѧϰʧ��"));
						settextcolor(RED);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						Sleep(1000);
						settextcolor(WHITE);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						return false;
					}
					else
					{
						_stprintf_s(guide_text, _T("ѧϰ�ɹ�"));
						settextcolor(RED);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						Sleep(1000);
						settextcolor(WHITE);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						playerX->energy -= energy_cost;
						BeginBatchDraw();
						settextcolor(WHITE);
						show_course_level();
						setlinecolor(WHITE);
						if (playerA.state[FAILURE])
							delete_course_level(&playerA);
						if (playerB.state[FAILURE])
							delete_course_level(&playerB);
						if (playerC.state[FAILURE])
							delete_course_level(&playerC);
						if (playerD.state[FAILURE])
							delete_course_level(&playerD);
						*playerX->level += 1;
						settextcolor(BLACK);
						show_course_level();
						setlinecolor(RED);
						if (playerA.state[FAILURE])
							delete_course_level(&playerA);
						if (playerB.state[FAILURE])
							delete_course_level(&playerB);
						if (playerC.state[FAILURE])
							delete_course_level(&playerC);
						if (playerD.state[FAILURE])
							delete_course_level(&playerD);
						EndBatchDraw();
						learned = true;
						playerX->state[UNFAMILIAR] = false;
					}
				}
			}
		}
		else
		{
			if (playerX->state[SKILLFUL])
			{
				_stprintf_s(guide_text, _T("״̬���Ƿ��켫\nѧϰ�ɹ�"));
				settextcolor(RED);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				BeginBatchDraw();
				settextcolor(WHITE);
				show_course_level();
				setlinecolor(WHITE);
				if (playerA.state[FAILURE])
					delete_course_level(&playerA);
				if (playerB.state[FAILURE])
					delete_course_level(&playerB);
				if (playerC.state[FAILURE])
					delete_course_level(&playerC);
				if (playerD.state[FAILURE])
					delete_course_level(&playerD);
				*playerX->level += 1;
				settextcolor(BLACK);
				show_course_level();
				setlinecolor(RED);
				if (playerA.state[FAILURE])
					delete_course_level(&playerA);
				if (playerB.state[FAILURE])
					delete_course_level(&playerB);
				if (playerC.state[FAILURE])
					delete_course_level(&playerC);
				if (playerD.state[FAILURE])
					delete_course_level(&playerD);
				EndBatchDraw();
				learned = true;
				playerX->state[SKILLFUL] = false;
			}
			else
			{
				int energy_cost = courseX->energy_cost[*playerX->level];
				if (playerX->state[EASIER])
				{
					_stprintf_s(guide_text, _T("״̬������ѧϰ"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					if (energy_cost > 1)
						energy_cost /= 2;
				}
				if (playerX->state[UNFAMILIAR])
				{
					_stprintf_s(guide_text, _T("״̬������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					energy_cost += 3;
				}
				playerX->energy -= energy_cost;
				pay(playerX, &playerA, courseX);
				pay(playerX, &playerB, courseX);
				pay(playerX, &playerC, courseX);
				pay(playerX, &playerD, courseX);
				failure(playerX);
				if (playerX->state[FAILURE])
					return false;
				_stprintf_s(guide_text, _T("ѧϰ�ɹ�"));
				settextcolor(RED);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				BeginBatchDraw();
				settextcolor(WHITE);
				show_course_level();
				setlinecolor(WHITE);
				if (playerA.state[FAILURE])
					delete_course_level(&playerA);
				if (playerB.state[FAILURE])
					delete_course_level(&playerB);
				if (playerC.state[FAILURE])
					delete_course_level(&playerC);
				if (playerD.state[FAILURE])
					delete_course_level(&playerD);
				*playerX->level += 1;
				settextcolor(BLACK);
				show_course_level();
				setlinecolor(RED);
				if (playerA.state[FAILURE])
					delete_course_level(&playerA);
				if (playerB.state[FAILURE])
					delete_course_level(&playerB);
				if (playerC.state[FAILURE])
					delete_course_level(&playerC);
				if (playerD.state[FAILURE])
					delete_course_level(&playerD);
				EndBatchDraw();
				learned = true;
				playerX->state[UNFAMILIAR] = false;
			}
		}
	}
	else
	{
		if (courseX->forget)
		{
			_stprintf_s(guide_text, _T("�ÿγ��Ѵﵽ��ߵȼ���������������\nL����ϰ������3�㾫����������������ϰ���γ̵ȼ�-1��"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			input = _getch();
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if ((input == 'l' || input == 'L') && playerX->energy > 3) //���¡�L�������и�ϰ��������������ϰ
			{
				_stprintf_s(guide_text, _T("��ϰ�ɹ�"));
				settextcolor(RED);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				playerX->energy -= 3;
			}
			else
			{
				_stprintf_s(guide_text, _T("δ��ϰ"));
				settextcolor(RED);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				BeginBatchDraw();
				settextcolor(WHITE);
				show_course_level();
				setlinecolor(WHITE);
				if (playerA.state[FAILURE])
					delete_course_level(&playerA);
				if (playerB.state[FAILURE])
					delete_course_level(&playerB);
				if (playerC.state[FAILURE])
					delete_course_level(&playerC);
				if (playerD.state[FAILURE])
					delete_course_level(&playerD);
				*playerX->level -= 1;
				settextcolor(BLACK);
				show_course_level();
				setlinecolor(RED);
				if (playerA.state[FAILURE])
					delete_course_level(&playerA);
				if (playerB.state[FAILURE])
					delete_course_level(&playerB);
				if (playerC.state[FAILURE])
					delete_course_level(&playerC);
				if (playerD.state[FAILURE])
					delete_course_level(&playerD);
				EndBatchDraw();
			}
		}
	}
	return learned;
}
/*�γ�ѧϰ����*/
bool learn(struct player* playerX, struct course* courseX)
{
	playerA.level = &courseX->playerA_level;
	playerB.level = &courseX->playerB_level;
	playerC.level = &courseX->playerC_level;
	playerD.level = &courseX->playerD_level;
	switch (playerX->name)
	{
	case 'A':
		return cost(&playerA, courseX);
		break;
	case 'B':
		return cost(&playerB, courseX);
		break;
	case 'C':
		return cost(&playerC, courseX);
		break;
	case 'D':
		return cost(&playerD, courseX);
		break;
	}
}
/*ʵ�����������Ϻ���*/
void experience(struct player* playerX, struct course* courseX)
{
	if (playerX->state[EXPERIMENT] && *playerX->level < courseX->max_level)
	{

		char input;
		_stprintf_s(guide_text, _T("״̬��ʵ������������\nK���ٴ�ѧϰ�γ̣�����������ѧϰ��"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		input = _getch();
		settextcolor(WHITE);
		settextstyle(15, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		if (input == 'k' || input == 'K')
		{
			if (learn(playerX, courseX))
				playerX->state[EXPERIMENT] = false;
		}
	}
}

/*λ����Ӧ����*/
void position(struct player* playerX)
{
	select_position(playerX, false);
	_stprintf_s(position_text, _T("���%c��λ��\n"), playerX->name);
	switch (playerX->position)
	{
	case START:
		_tcscat_s(position_text, _T("***��ʼλ��***\n��Ǯ+400"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold += 400;
		break;
	case CAL:
		_tcscat_s(position_text, _T("***΢����***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &cal);
		break;
	case L_A:
		_tcscat_s(position_text, _T("***���Դ���***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &l_a);
		break;
	case ENTRANCE:
		_tcscat_s(position_text, _T("***ˢҹ�����***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		break;
	case P_A_S:
		_tcscat_s(position_text, _T("***������������ͳ��***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &p_a_s);
		break;
	case EVENT_CARD:
		_tcscat_s(position_text, _T("***�¼���***\n"));
		event_card(playerX);
		break;
	case LABORATORY:
		_tcscat_s(position_text, _T("***ʵ����***\n����״̬����ʵ�����������ϣ��ɶ���ѧϰרҵ�γ�һ��"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[EXPERIMENT] = true;
		break;
	case P_O_C:
		_tcscat_s(position_text, _T("***��ѧԭ��***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &p_o_c))
			experience(playerX, &p_o_c);
		break;
	case I_E_C:
		_tcscat_s(position_text, _T("***�޻�Ԫ�ػ�ѧ***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &i_e_c))
			experience(playerX, &i_e_c);
		break;
	case O_C:
		_tcscat_s(position_text, _T("***�л���ѧ***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &o_c))
			experience(playerX, &o_c);
		break;
	case P_C:
		_tcscat_s(position_text, _T("***����ѧ***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &p_c))
			experience(playerX, &p_c);
		break;
	case S_C:
		_tcscat_s(position_text, _T("***�ṹ��ѧ***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &s_c))
			experience(playerX, &s_c);
		break;
	case LIBRARY:
		_tcscat_s(position_text, _T("***ͼ���***\n����״̬�������ģ�ѧϰ�γ̽��ɽ�Ǯ���룬ֱ���ٴε���ͼ��ݣ�����ʮ�غ�δ�ٴε���ͼ��ݣ�״̬����ҽ�Ǯ-250"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[BORROWING] = true;
		break;
	case A_C:
		_tcscat_s(position_text, _T("***������ѧ***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &a_c))
			experience(playerX, &a_c);
		break;
	case I_A:
		_tcscat_s(position_text, _T("***��������***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &i_a))
			experience(playerX, &i_a);
		break;
	case EXIT:
		_tcscat_s(position_text, _T("***ˢҹ������***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		break;
	case B_O_C_E:
		_tcscat_s(position_text, _T("***��ѧ���������***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &b_o_c_e);
		break;
	case C_P:
		_tcscat_s(position_text, _T("***C���Գ�����ƻ���***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &c_p);
		break;
	case STUDY_ROOM:
		_tcscat_s(position_text, _T("***��ϰ��***\n����״̬������ϰ�У�����һ�غϣ�����������Ҳ�����ܵ�����Ӱ��"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[STUDYING] = true;
		break;
	case ENG:
		_tcscat_s(position_text, _T("***��ѧӢ��***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &eng);
		break;
	case ITEM_CARD:
		_tcscat_s(position_text, _T("***���߿�***\n"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		item_card(playerX);
		break;
	case P_A_I:
		_tcscat_s(position_text, _T("***����������˼�����ר��***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &p_a_i);
		break;
	case PE:
		_tcscat_s(position_text, _T("***����***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &pe);
		break;
	case G_P:
		_tcscat_s(position_text, _T("***��ͨ����***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &g_p);
		break;
	case B_M:
		_tcscat_s(position_text, _T("***��ɽ***\n��ý��׶���"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->item[ADVANCED_READINGS] += 1;
		break;
	case C_M:
		_tcscat_s(position_text, _T("***���Ȼ�***\n���� + 15����������ʮ���غ�ÿ�غϽ������� - 1������״̬���������ԣ�"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 15;
		playerX->state[FRESH] = true;
		break;
	case M_S_B:
		_tcscat_s(position_text, _T("***ҹ��̯***\n����+7����Ǯ-200"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 7;
		playerX->gold -= 200;
		failure(playerX);
		break;
	case E_S:
		_tcscat_s(position_text, _T("***�⺣***\n����״̬�����Ƿ��켫���´ογ�ѧϰ����Ҫ���ľ����ͽ��ɽ�Ǯ"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[SKILLFUL] = true;
		break;
	case B_D:
		_tcscat_s(position_text, _T("***�����***\n����+5"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 5;
		break;
	}
	Sleep(4000);
	settextcolor(WHITE);
	settextstyle(15, 0, _T("����"));
	drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
}

enum round_continue { borrowing_round = 10, saving_round = 5, loan_round = 5, recovering_round = 5, easier_round = 5, fresh_round = 10 };
/*���ĺ���*/
void borrowing(struct player* playerX)
{
	static int a = borrowing_round;
	static int b = borrowing_round;
	static int c = borrowing_round;
	static int d = borrowing_round;
	if (load_continous_state)
	{
		FILE* Borrowing = fopen("D:\\C_Project_Resource\\continous_state\\Borrowing.txt", "r");
		fread(&a, sizeof(int), 1, Borrowing);
		fread(&b, sizeof(int), 1, Borrowing);
		fread(&c, sizeof(int), 1, Borrowing);
		fread(&d, sizeof(int), 1, Borrowing);
		fclose(Borrowing);
	}
	if (playerX->state[BORROWING])
	{
		switch (playerX->name)
		{
		case 'A':
			_stprintf_s(guide_text, _T("״̬�������У���ʣ%d���غϣ�"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			a -= 1;
			if (a == -1 || playerX->position == LIBRARY && a != borrowing_round - 1)
			{
				a = borrowing_round;
				playerX->state[BORROWING] = false;
				if (playerX->position != LIBRARY)
					playerX->gold -= 250;
				failure(playerX);
			}
			break;
		case 'B':
			_stprintf_s(guide_text,_T( "״̬�������У���ʣ%d���غϣ�"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			b -= 1;
			if (b == -1 || playerX->position == LIBRARY && b != borrowing_round - 1)
			{
				b = borrowing_round;
				playerX->state[BORROWING] = false;
				if (playerX->position != LIBRARY)
					playerX->gold -= 250;
				failure(playerX);
			}
			break;
		case 'C':
			_stprintf_s(guide_text, _T("״̬�������У���ʣ%d���غϣ�"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			c -= 1;
			if (c == -1 || playerX->position == LIBRARY && c != borrowing_round - 1)
			{
				c = borrowing_round;
				playerX->state[BORROWING] = false;
				if (playerX->position != LIBRARY)
					playerX->gold -= 250;
				failure(playerX);
			}
			break;
		case 'D':
			_stprintf_s(guide_text, _T("״̬�������У���ʣ%d���غϣ�"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			d -= 1;
			if (d == -1 || playerX->position == LIBRARY && d != borrowing_round - 1)
			{
				d = borrowing_round;
				playerX->state[BORROWING] = false;
				if (playerX->position != LIBRARY)
					playerX->gold -= 250;
				failure(playerX);
			}
			break;
		}
	}
	if (playerX->name == 'D')
	{
		FILE* Borrowing = fopen("D:\\C_Project_Resource\\continous_state\\Borrowing.txt", "w");
		fwrite(&a, sizeof(int), 1, Borrowing);
		fwrite(&b, sizeof(int), 1, Borrowing);
		fwrite(&c, sizeof(int), 1, Borrowing);
		fwrite(&d, sizeof(int), 1, Borrowing);
		fclose(Borrowing);
	}
}
/*�����*/
void saving(struct player* playerX)
{
	static int a = saving_round;
	static int b = saving_round;
	static int c = saving_round;
	static int d = saving_round;
	if (load_continous_state)
	{
		FILE* Saving = fopen("D:\\C_Project_Resource\\continous_state\\Saving.txt", "r");
		fread(&a, sizeof(int), 1, Saving);
		fread(&b, sizeof(int), 1, Saving);
		fread(&c, sizeof(int), 1, Saving);
		fread(&d, sizeof(int), 1, Saving);
		fclose(Saving);
	}
	if (playerX->state[SAVING])
	{
		switch (playerX->name)
		{
		case 'A':
			_stprintf_s(guide_text, _T("״̬�������У���ʣ%d���غϣ�"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (a < saving_round)
				playerX->gold += 60;
			a -= 1;
			if (a == -1)
			{
				a = saving_round;
				playerX->state[SAVING] = false;
			}
			break;
		case 'B':
			_stprintf_s(guide_text, _T("״̬�������У���ʣ%d���غϣ�"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (b < saving_round)
				playerX->gold += 60;
			b -= 1;
			if (b == -1)
			{
				b = saving_round;
				playerX->state[SAVING] = false;
			}
			break;
		case 'C':
			_stprintf_s(guide_text, _T("״̬�������У���ʣ%d���غϣ�"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (c < saving_round)
				playerX->gold += 60;
			c -= 1;
			if (c == -1)
			{
				c = saving_round;
				playerX->state[SAVING] = false;
			}
			break;
		case 'D':
			_stprintf_s(guide_text, _T("״̬�������У���ʣ%d���غϣ�"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (d < saving_round)
				playerX->gold += 60;
			d -= 1;
			if (d == -1)
			{
				d = saving_round;
				playerX->state[SAVING] = false;
			}
			break;
		}
	}
	if (playerX->name == 'D')
	{
		FILE* Saving = fopen("D:\\C_Project_Resource\\continous_state\\Saving.txt", "w");
		fwrite(&a, sizeof(int), 1, Saving);
		fwrite(&b, sizeof(int), 1, Saving);
		fwrite(&c, sizeof(int), 1, Saving);
		fwrite(&d, sizeof(int), 1, Saving);
		fclose(Saving);
	}
}
/*У԰������*/
void loan(struct player* playerX)
{
	static int a = loan_round;
	static int b = loan_round;
	static int c = loan_round;
	static int d = loan_round;
	if (load_continous_state)
	{
		FILE* Loan = fopen("D:\\C_Project_Resource\\continous_state\\Loan.txt", "r");
		fread(&a, sizeof(int), 1, Loan);
		fread(&b, sizeof(int), 1, Loan);
		fread(&c, sizeof(int), 1, Loan);
		fread(&d, sizeof(int), 1, Loan);
		fclose(Loan);
	}
	if (playerX->state[LOAN])
	{
		switch (playerX->name)
		{
		case 'A':
			_stprintf_s(guide_text, _T("״̬�������ʣ%d���غϣ�"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (a < loan_round)
				playerX->gold -= 100;
			a -= 1;
			if (a == -1)
			{
				a = loan_round;
				playerX->state[LOAN] = false;
			}
			break;
		case 'B':
			_stprintf_s(guide_text, _T("״̬�������ʣ%d���غϣ�"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (b < loan_round)
				playerX->gold -= 100;
			b -= 1;
			if (b == -1)
			{
				b = loan_round;
				playerX->state[LOAN] = false;
			}
			break;
		case 'C':
			_stprintf_s(guide_text, _T("״̬�������ʣ%d���غϣ�"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (c < loan_round)
				playerX->gold -= 100;
			c -= 1;
			if (c == -1)
			{
				c = loan_round;
				playerX->state[LOAN] = false;
			}
			break;
		case 'D':
			_stprintf_s(guide_text, _T("״̬�������ʣ%d���غϣ�"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (d < loan_round)
				playerX->gold -= 100;
			d -= 1;
			if (d == -1)
			{
				d = loan_round;
				playerX->state[LOAN] = false;
			}
			break;
		}
		failure(playerX);
	}
	if (playerX->name == 'D')
	{
		FILE* Loan = fopen("D:\\C_Project_Resource\\continous_state\\Loan.txt", "w");
		fwrite(&a, sizeof(int), 1, Loan);
		fwrite(&b, sizeof(int), 1, Loan);
		fwrite(&c, sizeof(int), 1, Loan);
		fwrite(&d, sizeof(int), 1, Loan);
		fclose(Loan);
	}
}
/*�����ָ�����*/
void recovering(struct player* playerX)
{
	static int a = recovering_round;
	static int b = recovering_round;
	static int c = recovering_round;
	static int d = recovering_round;
	if (load_continous_state)
	{
		FILE* Recovering = fopen("D:\\C_Project_Resource\\continous_state\\Recovering.txt", "r");
		fread(&a, sizeof(int), 1, Recovering);
		fread(&b, sizeof(int), 1, Recovering);
		fread(&c, sizeof(int), 1, Recovering);
		fread(&d, sizeof(int), 1, Recovering);
		fclose(Recovering);
	}
	if (playerX->state[RECOVERING])
	{
		switch (playerX->name)
		{
		case 'A':
			_stprintf_s(guide_text, _T("״̬�������ָ�����ʣ%d���غϣ�"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (a < recovering_round)
			{
				if (playerX->energy < 10)
					playerX->energy += 3;
				else
					playerX->energy += 1;
			}
			a -= 1;
			if (a == -1)
			{
				a = recovering_round;
				playerX->state[RECOVERING] = false;
			}
			break;
		case 'B':
			_stprintf_s(guide_text, _T("״̬�������ָ�����ʣ%d���غϣ�"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (b < recovering_round)
			{
				if (playerX->energy < 10)
					playerX->energy += 3;
				else
					playerX->energy += 1;
			}
			b -= 1;
			if (b == -1)
			{
				b = recovering_round;
				playerX->state[RECOVERING] = false;
			}
			break;
		case 'C':
			_stprintf_s(guide_text, _T("״̬�������ָ�����ʣ%d���غϣ�"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (c < recovering_round)
			{
				if (playerX->energy < 10)
					playerX->energy += 3;
				else
					playerX->energy += 1;
			}
			c -= 1;
			if (c == -1)
			{
				c = recovering_round;
				playerX->state[RECOVERING] = false;
			}
			break;
		case 'D':
			_stprintf_s(guide_text, _T("״̬�������ָ�����ʣ%d���غϣ�"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (d < recovering_round)
			{
				if (playerX->energy < 10)
					playerX->energy += 3;
				else
					playerX->energy += 1;
			}
			d -= 1;
			if (d == -1)
			{
				d = recovering_round + 1;
				playerX->state[RECOVERING] = false;
			}
			break;
		}
	}
	if (playerX->name == 'D')
	{
		FILE* Recovering = fopen("D:\\C_Project_Resource\\continous_state\\Recovering.txt", "w");
		fwrite(&a, sizeof(int), 1, Recovering);
		fwrite(&b, sizeof(int), 1, Recovering);
		fwrite(&c, sizeof(int), 1, Recovering);
		fwrite(&d, sizeof(int), 1, Recovering);
		fclose(Recovering);
	}
}
/*����ѧϰ����*/
void easier(struct player* playerX)
{
	static int a = easier_round;
	static int b = easier_round;
	static int c = easier_round;
	static int d = easier_round;
	if (load_continous_state)
	{
		FILE* Easier = fopen("D:\\C_Project_Resource\\continous_state\\Easier.txt", "r");
		fread(&a, sizeof(int), 1, Easier);
		fread(&b, sizeof(int), 1, Easier);
		fread(&c, sizeof(int), 1, Easier);
		fread(&d, sizeof(int), 1, Easier);
		fclose(Easier);
	}
	if (playerX->state[EASIER])
	{
		switch (playerX->name)
		{
		case 'A':
			_stprintf_s(guide_text, _T("״̬������ѧϰ����ʣ%d���غϣ�"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			a -= 1;
			if (a == -1)
			{
				a = easier_round;
				playerX->state[EASIER] = false;
			}
			break;
		case 'B':
			_stprintf_s(guide_text, _T("״̬������ѧϰ����ʣ%d���غϣ�"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			b -= 1;
			if (b == -1)
			{
				b = easier_round;
				playerX->state[EASIER] = false;
			}
			break;
			_stprintf_s(guide_text, _T("״̬������ѧϰ����ʣ%d���غϣ�"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			c -= 1;
			if (c == -1)
			{
				c = easier_round;
				playerX->state[EASIER] = false;
			}
			break;
		case 'D':
			_stprintf_s(guide_text, _T("״̬������ѧϰ����ʣ%d���غϣ�"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			d -= 1;
			if (d == -1)
			{
				d = easier_round;
				playerX->state[EASIER] = false;
			}
			break;
		}
	}
	if (playerX->name == 'D')
	{
		FILE* Easier = fopen("D:\\C_Project_Resource\\continous_state\\Easier.txt", "w");
		fwrite(&a, sizeof(int), 1, Easier);
		fwrite(&b, sizeof(int), 1, Easier);
		fwrite(&c, sizeof(int), 1, Easier);
		fwrite(&d, sizeof(int), 1, Easier);
		fclose(Easier);
	}
}
/*�������Ժ���*/
void fresh(struct player* playerX)
{
	static int a = fresh_round;
	static int b = fresh_round;
	static int c = fresh_round;
	static int d = fresh_round;
	if (load_continous_state)
	{
		FILE* Fresh = fopen("D:\\C_Project_Resource\\continous_state\\Fresh.txt", "r");
		fread(&a, sizeof(int), 1, Fresh);
		fread(&b, sizeof(int), 1, Fresh);
		fread(&c, sizeof(int), 1, Fresh);
		fread(&d, sizeof(int), 1, Fresh);
		fclose(Fresh);
	}
	if (playerX->state[FRESH])
	{
		switch (playerX->name)
		{
		case 'A':
			_stprintf_s(guide_text, _T("״̬���������ԣ���ʣ%d���غϣ�"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (a < fresh_round)
				playerX->energy -= 1;
			a -= 1;
			if (a == -1)
			{
				a = fresh_round;
				playerX->state[FRESH] = false;
			}
			break;
		case 'B':
			_stprintf_s(guide_text, _T("״̬���������ԣ���ʣ%d���غϣ�"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (b < fresh_round)
				playerX->energy -= 1;
			b -= 1;
			if (b == -1)
			{
				b = fresh_round;
				playerX->state[FRESH] = false;
			}
			break;
		case 'C':
			_stprintf_s(guide_text, _T("״̬���������ԣ���ʣ%d���غϣ�"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (c < fresh_round)
				playerX->energy -= 1;
			c -= 1;
			if (c == -1)
			{
				c = fresh_round;
				playerX->state[FRESH] = false;
			}
			break;
		case 'D':
			_stprintf_s(guide_text, _T("״̬���������ԣ���ʣ%d���غϣ�"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (d < fresh_round)
				playerX->energy -= 1;
			d -= 1;
			if (d == -1)
			{
				d = fresh_round;
				playerX->state[FRESH] = false;
			}
			break;
		}
		failure(playerX);
	}
	if (playerX->name == 'D')
	{
		FILE* Fresh = fopen("D:\\C_Project_Resource\\continous_state\\Fresh.txt", "w");
		fwrite(&a, sizeof(int), 1, Fresh);
		fwrite(&b, sizeof(int), 1, Fresh);
		fwrite(&c, sizeof(int), 1, Fresh);
		fwrite(&d, sizeof(int), 1, Fresh);
		fclose(Fresh);
	}
}

/*�����Ӻ���*/
int roll(void)
{
	return 1 + rand() % 6;
}
/*�ٱ����Ӻ���*/
int magic_dice(void)
{
	char input;
	int result;
	_stprintf_s(guide_text, _T("�ٱ����ӡ���������Ӧ��ѡ�����ӵķ�Χ\nW��1-3 E��4-6\nR��7-9 T��10-12"));
	settextcolor(BLACK);
	settextstyle(15, 0, _T("����"));
	drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
	while (true)
	{
		input = _getch();
		if (input == 'w' || input == 'W')
		{
			result = 1 + rand() % 3;
			break;
		}
		if (input == 'e' || input == 'E')
		{
			result = 4 + rand() % 3;
			break;
		}
		if (input == 'r' || input =='R')
		{
			result = 7 + rand() % 3;
			break;
		}
		if (input == 't' || input == 'T')
		{
			result = 10 + rand() % 3;
			break;
		}
	}
	settextcolor(WHITE);
	settextstyle(15, 0, _T("����"));
	drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
	return result;
}

/*���λ�λ����*/
bool swap(struct player* playerX)
{
	int temp;
	char input;
	int invalid_player = 0; //���ɽ��������
	if (playerA.state[FAILURE] || playerA.state[STUDYING])
		invalid_player += 1;
	if (playerB.state[FAILURE] || playerB.state[STUDYING])
		invalid_player += 1;
	if (playerC.state[FAILURE] || playerC.state[STUDYING])
		invalid_player += 1;
	if (playerD.state[FAILURE] || playerD.state[STUDYING])
		invalid_player += 1;
	if (invalid_player == 3)
	{
		_stprintf_s(guide_text, _T("���λ�λ�޿����õ����"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		Sleep(1000);
		settextcolor(WHITE);
		settextstyle(15, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		return false;
	}
	else
	{
		while (true)
		{
			_stprintf_s(guide_text, _T("������Ӧ��ѡ����Ҫ���������\nZ�����A X�����B\nC�����C V�����D"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			input = _getch();
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if ((input == 'z' || input == 'Z') && playerX->name != 'A')
			{
				if (playerA.state[FAILURE])
				{
					_stprintf_s(guide_text, _T("���A���и����޷�����������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else if (playerA.state[STUDYING])
				{
					_stprintf_s(guide_text, _T("���A��ϰ�У��޷�����������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else
				{
					select_position(playerX, true);
					select_position(&playerA, true);
					temp = playerA.position;
					playerA.position = playerX->position;
					playerX->position = temp;
					select_position(playerX, false);
					select_position(&playerA, false);
					break;
				}
			}
			if ((input == 'x' || input == 'X') && playerX->name != 'B')
			{
				if (playerB.state[FAILURE])
				{
					_stprintf_s(guide_text, _T("���B���и����޷�����������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else if (playerB.state[STUDYING])
				{
					_stprintf_s(guide_text, _T("���B��ϰ�У��޷�����������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else
				{
					select_position(playerX, true);
					select_position(&playerB, true);
					temp = playerB.position;
					playerB.position = playerX->position;
					playerX->position = temp;
					select_position(playerX, false);
					select_position(&playerB, false);
					break;
				}
			}
			if ((input == 'c' || input == 'C') && playerX->name != 'C')
			{
				if (playerC.state[FAILURE])
				{
					_stprintf_s(guide_text, _T("���C���и����޷�����������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else if (playerC.state[STUDYING])
				{
					_stprintf_s(guide_text, _T("���C��ϰ�У��޷�����������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else
				{
					select_position(playerX, true);
					select_position(&playerC, true);
					temp = playerC.position;
					playerC.position = playerX->position;
					playerX->position = temp;
					select_position(playerX, false);
					select_position(&playerC, false);
					break;
				}
			}
			if ((input == 'v' || input == 'V') && playerX->name != 'D')
			{
				if (playerD.state[FAILURE])
				{
					_stprintf_s(guide_text, _T("���D���и����޷�����������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else if (playerD.state[STUDYING])
				{
					_stprintf_s(guide_text, _T("���D��ϰ�У��޷�����������"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else
				{
					select_position(playerX, true);
					select_position(&playerD, true);
					temp = playerD.position;
					playerD.position = playerX->position;
					playerX->position = temp;
					select_position(playerX, false);
					select_position(&playerD, false);
					break;
				}
			}
		}
		return true;
	}
}

enum value { magic_dice_value = 200, learning_materials_value = 400, energy_drink_value = 300, swap_value = 300, staying_up_door_value = 400 };
/*������ߺ���*/
bool buy(struct player* playerX, struct player* playerY)
{
	char input;
	while (true)
	{
		_stprintf_s(guide_text, _T("������Ӧ�������%c�������\n1���ٱ�����(%d) 2��ѧϰ����(%d\n3����������(%d) 4�����λ�λ(%d)\n5��ˢҹ������(%d)"), playerY->name, magic_dice_value / 2, learning_materials_value / 2, energy_drink_value / 2, swap_value / 2, staying_up_door_value / 2);
		settextcolor(BLACK);
		settextstyle(14, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		input = _getch();
		settextcolor(WHITE);
		settextstyle(14, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		switch (input)
		{
		case '1':
			if (playerY->item[MAGIC_DICE] > 0 && playerX->gold >= magic_dice_value / 2)
			{
				playerY->item[MAGIC_DICE] -= 1;
				playerX->item[MAGIC_DICE] += 1;
				playerY->gold += magic_dice_value / 2;
				playerX->gold -= magic_dice_value / 2;
				return true;
			}
			else
				return false;
			break;
		case '2':
			if (playerY->item[LEARNING_MATERIALS] > 0 && playerX->gold >= learning_materials_value / 2)
			{
				playerY->item[LEARNING_MATERIALS] -= 1;
				playerX->item[LEARNING_MATERIALS] += 1;
				playerY->gold += learning_materials_value / 2;
				playerX->gold -= learning_materials_value / 2;
				return true;
			}
			else
				return false;
			break;
		case '3':
			if (playerY->item[ENERGY_DRINK] > 0 && playerX->gold >= energy_drink_value / 2)
			{
				playerY->item[ENERGY_DRINK] -= 1;
				playerX->item[ENERGY_DRINK] += 1;
				playerY->gold += energy_drink_value / 2;
				playerX->gold -= energy_drink_value / 2;
				return true;
			}
			else
				return false;
			break;
		case '4':
			if (playerY->item[SWAP] > 0 && playerX->gold >= swap_value / 2)
			{
				playerY->item[SWAP] -= 1;
				playerX->item[SWAP] += 1;
				playerY->gold += swap_value / 2;
				playerX->gold -= swap_value / 2;
				return true;
			}
			else
				return false;
			break;
		case '5':
			if (playerY->item[STAYING_UP_DOOR] > 0 && playerX->gold >= staying_up_door_value / 2)
			{
				playerY->item[STAYING_UP_DOOR] -= 1;
				playerX->item[STAYING_UP_DOOR] += 1;
				playerY->gold += staying_up_door_value / 2;
				playerX->gold -= staying_up_door_value / 2;
				return true;
			}
			else
				return false;
			break;
		}
	}
}
/*�������֤����*/
bool trading_license(struct player* playerX)
{
	char input;
	while (true)
	{
		_stprintf_s(guide_text, _T("������Ӧ��ѡ����Ҫ���׵����\nZ�����A X�����B C�����C V�����D\n���������̵꽻��"));
		settextcolor(BLACK);
		settextstyle(14, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		input = _getch();
		settextcolor(WHITE);
		settextstyle(14, 0, _T("����"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		if ((input == 'z' || input == 'Z') && playerX->name != 'A')
		{
			if (playerA.state[FAILURE])
			{
				_stprintf_s(guide_text, _T("���A���и����޷�����������"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else if (playerA.state[STUDYING])
			{
				_stprintf_s(guide_text, _T("���A��ϰ�У��޷�����������"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else
				return buy(playerX, &playerA);
		}
		if ((input == 'x' || input == 'X') && playerX->name != 'B')
		{
			if (playerB.state[FAILURE])
			{
				_stprintf_s(guide_text, _T("���B���и����޷�����������"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else if (playerB.state[STUDYING])
			{
				_stprintf_s(guide_text, _T("���B��ϰ�У��޷�����������"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else
				return buy(playerX, &playerB);
		}
		if ((input == 'c' || input == 'C') && playerX->name != 'C')
		{
			if (playerC.state[FAILURE])
			{
				_stprintf_s(guide_text, _T("���C���и����޷�����������"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else if (playerC.state[STUDYING])
			{
				_stprintf_s(guide_text, _T("���C��ϰ�У��޷�����������"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else
				return buy(playerX, &playerC);
		}
		if ((input == 'v' || input == 'V') && playerX->name != 'D')
		{
			if (playerD.state[FAILURE])
			{
				_stprintf_s(guide_text, _T("���D���и����޷�����������"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else if (playerD.state[STUDYING])
			{
				_stprintf_s(guide_text, _T("���D��ϰ�У��޷�����������"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else
				return buy(playerX, &playerD);
		}
		if (input != 'z' && input != 'x' && input != 'c' && input != 'v' && input != 'Z' && input != 'X' && input != 'C' && input != 'V')
		{
			while (true)
			{
				_stprintf_s(guide_text, _T("������Ӧ�����̵깺�����\n1���ٱ�����(%d) 2��ѧϰ����(%d)\n3����������(%d) 4�����λ�λ(%d)\n5��ˢҹ������(%d)"), magic_dice_value, learning_materials_value, energy_drink_value, swap_value, staying_up_door_value);
				settextcolor(BLACK);
				settextstyle(14, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				input = _getch();
				settextcolor(WHITE);
				settextstyle(14, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				switch (input)
				{
				case '1':
					if (playerX->gold >= magic_dice_value)
					{
						playerX->item[MAGIC_DICE] += 1;
						playerX->gold -= magic_dice_value;
						return true;
					}
					else
						return false;
					break;
				case '2':
					if (playerX->gold >= learning_materials_value)
					{
						playerX->item[LEARNING_MATERIALS] += 1;
						playerX->gold -= learning_materials_value;
						return true;
					}
					else
						return false;
					break;
				case '3':
					if (playerX->gold >= energy_drink_value)
					{
						playerX->item[ENERGY_DRINK] += 1;
						playerX->gold -= energy_drink_value;
						return true;
					}
					else
						return false;
					break;
				case '4':
					if (playerX->gold >= swap_value)
					{
						playerX->item[SWAP] += 1;
						playerX->gold -= swap_value;
						return true;
					}
					else
						return false;
					break;
				case '5':
					if (playerX->gold >= staying_up_door_value)
					{
						playerX->item[STAYING_UP_DOOR] += 1;
						playerX->gold -= staying_up_door_value;
						return true;
					}
					else
						return false;
					break;
				}
			}
		}
	}
}

/*�غϱ�Ǻ���*/
void signal(struct player* playerX, bool end)
{
	if (!end)
		setfillcolor(YELLOW);
	else
		setfillcolor(WHITE);
	switch (playerX->name)
	{
	case 'A':
		solidcircle(260, 320, 15);
		break;
	case 'B':
		solidcircle(560, 320, 15);
		break;
	case 'C':
		solidcircle(260, 560, 15);
		break;
	case 'D':
		solidcircle(560, 560, 15);
		break;
	}
}
/*��һغϺ���*/
void turn(struct player* playerX)
{
	char input;
	int step;
	/*���������Ʒ*/
	BeginBatchDraw();
	show_item();
	item_number(&playerA);
	item_number(&playerB);
	item_number(&playerC);
	item_number(&playerD);
	signal(playerX, false);
	EndBatchDraw();
	struct player copyA = playerA;
	struct player copyB = playerB;
	struct player copyC = playerC;
	struct player copyD = playerD;
	/*�غϿ�ʼǰ�鿴�γ���Ϣ*/
	view_course();
	if (playerX->state[REST] || playerX->state[STUDYING] || playerX->state[FAILURE]) //�ж��Ƿ������غ�
	{
		playerX->state[REST] = false;
		playerX->state[STUDYING] = false;
		if (playerX->state[FAILURE])
		{
			_stprintf_s(guide_text, _T("���%c���и�"), playerX->name);
			settextcolor(RED);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		}
		else
		{
			_stprintf_s(guide_text, _T("���%c�����غ�"), playerX->name);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		}
	}
	else
	{
		while (true)
		{
			_stprintf_s(guide_text, _T("�ո�:�����ӣ�A:ʹ��ˢҹ������\nS:ʹ�����λ�λ��D:ʹ����������\nF:ʹ��ѧϰ���ϣ�G:ʹ�ý������֤"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			input = _getch();
			settextcolor(WHITE);
			settextstyle(15, 0, _T("����"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (input == ' ') //���¿ո��������
			{
				if (playerX->item[MAGIC_DICE] > 0)
				{
					_stprintf_s(guide_text, _T("Q��ʹ�ðٱ����ӣ�����������ʹ�ã�"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					input = _getch();
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					if (input == 'q' || input == 'Q') //���¡�Q����ʹ�ðٱ�����
					{
						playerX->item[MAGIC_DICE] -= 1;
						step = magic_dice();
					}
					else
						step = roll();
				}
				else
					step = roll();
				mciSendString(_T("close rollmusic"), NULL, 0, NULL);
				mciSendString(_T("open D:\\C_Project_Resource\\dice_music.mp3 alias rollmusic"), NULL, 0, NULL);
				mciSendString(_T("play rollmusic"), NULL, 0, NULL);
				if (playerX->position == ENTRANCE) //ˢҹ����ڴ����¿ո��������ˢҹ��������������ˢҹ��������4�㾫������Խˢҹ�������ľ���
				{
					_stprintf_s(guide_text, _T("���ӵ�����%d\n�ո񣺲�����ˢҹ��������������ˢҹ��������4�㾫������Խˢҹ�������ľ���)\n"), step);
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					input = _getch();
					if (input == ' ')
					{
						select_position(playerX, true);
						playerX->position = (playerX->position + step) % 24;
						settextcolor(WHITE);
						settextstyle(15, 0, _T("����"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						position(playerX);
						break;
					}
					else
					{
						select_position(playerX, true);
						playerX->position = -6;
						if (step < 6)
							playerX->energy -= 4;
					}
				}
				else
				{
					_stprintf_s(guide_text, _T("���ӵ�����%d"), step);
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(2000);
				}
				if (playerX->position >= 0 && playerX->position != ENTRANCE) //��ˢҹ������
				{
					select_position(playerX, true);
					playerX->position = (playerX->position + step) % 24;
				}
				if (playerX->position < 0) //ˢҹ������
				{
					select_position(playerX, true);
					if (playerX->position + step < 0)
						playerX->position += step;
					else
						playerX->position = (EXIT + step + playerX->position) % 24;
				}
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				position(playerX);
				break;
			}
			else if ((input == 'a' || input == 'A') && playerX->item[STAYING_UP_DOOR] > 0)
			{
				_stprintf_s(guide_text, _T("������ˢҹ���ڵ����λ��"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(2000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				select_position(playerX, true);
				playerX->position = -rand() % 5 - 1;
				playerX->item[STAYING_UP_DOOR] -= 1;
				position(playerX);
				break;
			}
			if ((input == 's' || input == 'S') && playerX->item[SWAP] > 0)
			{
				if (swap(playerX))
				{
					playerX->item[SWAP] -= 1;
					break;
				}
			}
			if ((input == 'd' || input == 'D') && playerX->item[ENERGY_DRINK] > 0)
			{
				_stprintf_s(guide_text, _T("����״̬���������ָ���������������غ�ÿ�غϽ�������+1������<10ʱÿ�غϽ�������+3��"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(2000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				playerX->state[RECOVERING] = true;
				playerX->item[ENERGY_DRINK] -= 1;
				break;
			}
			if ((input == 'f' || input == 'F') && playerX->item[LEARNING_MATERIALS] > 0)
			{
				_stprintf_s(guide_text, _T("����״̬��������ѧϰ��������������غ�ѧϰ�γ̾������ļ���(��������1�㾫��)"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(2000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("����"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				playerX->state[EASIER] = true;
				playerX->item[LEARNING_MATERIALS] -= 1;
				break;
			}
			if ((input == 'g' || input == 'G') && playerX->item[TRADING_LICENSE] > 0)
			{
				if (trading_license(playerX))
				{
					_stprintf_s(guide_text, _T("���׳ɹ�"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					playerX->item[TRADING_LICENSE] -= 1;
					break;
				}
				else
				{
					_stprintf_s(guide_text, _T("������Ч"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("����"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
			}
		}
	}
	/*�ж�������״̬*/
	easier(playerX);
	recovering(playerX);
	borrowing(playerX);
	saving(playerX);
	loan(playerX);
	fresh(playerX);
	load_continous_state = false;
	/*���������Ϣ*/
	BeginBatchDraw();
	signal(playerX, true);
	show_player(&copyA, true);
	show_player(&copyB, true);
	show_player(&copyC, true);
	show_player(&copyD, true);
	show_player(&playerA, false);
	show_state(&playerA);
	show_player(&playerB, false);
	show_state(&playerB);
	show_player(&playerC, false);
	show_state(&playerC);
	show_player(&playerD, false);
	show_state(&playerD);
	EndBatchDraw();
}

/*������*/
int main(void)
{
	/*���ű�������*/
	mciSendString(_T("open D:\\C_Project_Resource\\BGM.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	/*ѡ������Ϸ���ȡ�浵*/
	initgraph(1000, 700);
	IMAGE cover;
	loadimage(&cover, _T("D:\\C_Project_Resource\\cover.jpg"));
	putimage(0, 0, &cover);
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG m = GetMouseMsg();
			if (m.x > 340 && m.x < 660 && m.y > 400 && m.y < 500)
			{
				setlinecolor(RED);
				setlinestyle(PS_SOLID, 4);
				rectangle(335, 395, 665, 505);
			}
			else if (m.x > 340 && m.x < 660 && m.y > 520 && m.y < 620)
			{
				setlinecolor(RED);
				setlinestyle(PS_SOLID, 4);
				rectangle(335, 515, 665, 625);
			}
			else
			{
				setlinecolor(WHITE);
				setlinestyle(PS_SOLID, 4);
				rectangle(335, 395, 665, 505);
				rectangle(335, 515, 665, 625);
			}
			if (m.uMsg == WM_LBUTTONUP && m.x > 340 && m.x < 660 && m.y > 400 && m.y < 500)
			{
				/*����浵*/
				FILE* clear; 
				clear = fopen("D:\\C_Project_Resource\\documents.txt", "w");
				fclose(clear);
				clear = fopen("D:\\C_Project_Resource\\continous_state\\Borrowing.txt", "w");
				fclose(clear);
				clear = fopen("D:\\C_Project_Resource\\continous_state\\Saving.txt", "w");
				fclose(clear);
				clear = fopen("D:\\C_Project_Resource\\continous_state\\Loan.txt", "w");
				fclose(clear);
				clear = fopen("D:\\C_Project_Resource\\continous_state\\Recovering.txt", "w");
				fclose(clear);
				clear = fopen("D:\\C_Project_Resource\\continous_state\\Easier.txt", "w");
				fclose(clear);
				clear = fopen("D:\\C_Project_Resource\\continous_state\\Fresh.txt", "w");
				fclose(clear);
				break;
			}
			if (m.uMsg == WM_LBUTTONUP && m.x > 340 && m.x < 660 && m.y > 520 && m.y < 620)
			{
				load_game();
				load_continous_state = true;
				break;
			}
		}
		if (_kbhit())
			_getch();
	}
	/*��Ϸ��ʼ��*/
	IMAGE map;
	loadimage(&map, _T("D:\\C_Project_Resource\\map.jpg"));
	putimage(0, 0, &map);
	setbkmode(TRANSPARENT);
	srand(time(NULL));
	course_start_up();
	TCHAR s[50];
	RECT r;
	BeginBatchDraw();
	settextcolor(BLACK);
	show_course_level();
	setlinecolor(RED);
	if (playerA.state[FAILURE])
		delete_course_level(&playerA);
	if (playerB.state[FAILURE])
		delete_course_level(&playerB);
	if (playerC.state[FAILURE])
		delete_course_level(&playerC);
	if (playerD.state[FAILURE])
		delete_course_level(&playerD);
	show_item();
	show_player(&playerA, false);
	show_state(&playerA);
	item_number(&playerA);
	show_player(&playerB, false);
	show_state(&playerB);
	item_number(&playerB);
	show_player(&playerC, false);
	show_state(&playerC);
	item_number(&playerC);
	show_player(&playerD, false);
	show_state(&playerD);
	item_number(&playerD);
	EndBatchDraw();
	/*��ʼ��Ϸ*/
	while (true)
	{
		_stprintf_s(s, _T("��%d�غ�"), Round);
		r = { 700,25,1000,75 };
		settextcolor(BLACK);
		settextstyle(25, 0, _T("����"));
		drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
		turn(&playerA);
		turn(&playerB);
		turn(&playerC);
		turn(&playerD);
		settextcolor(WHITE);
		settextstyle(25, 0, _T("����"));
		drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
		Round += 1;
		int energy_plus;
		if (Round % 4 == 0) //ÿ�ĸ��غ�������һָ�2-6�㾫������غ�����أ�
		{
			struct player copyA = playerA;
			struct player copyB = playerB;
			struct player copyC = playerC;
			struct player copyD = playerD;
			energy_plus = 2 + Round / 8;
			if (energy_plus > 6)
				energy_plus = 6;
			_stprintf_s(s, _T("�µ�һ�쿪ʼ��\n������Ҿ���+%d"), energy_plus);
			settextcolor(BLACK);
			settextstyle(25, 0, _T("����"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			Sleep(2500);
			settextcolor(WHITE);
			settextstyle(25, 0, _T("����"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			if (!playerA.state[FAILURE])
				playerA.energy += energy_plus;
			if (!playerB.state[FAILURE])
				playerB.energy += energy_plus;
			if (!playerC.state[FAILURE])
				playerC.energy += energy_plus;
			if (!playerD.state[FAILURE])
				playerD.energy += energy_plus;
			BeginBatchDraw();
			show_player(&copyA, true);
			show_player(&copyB, true);
			show_player(&copyC, true);
			show_player(&copyD, true);
			show_player(&playerA, false);
			show_player(&playerB, false);
			show_player(&playerC, false);
			show_player(&playerD, false);
			EndBatchDraw();
		}
		if (playernumber <= 1)
		{
			_stprintf_s(s, _T("��Ϸ����\n������\n���A����%d�� ���B����%d��\n���C����%d�� ���D����%d��\n��������˳���Ϸ"), playerA.rank, playerB.rank, playerC.rank, playerD.rank);
			r = { 700,0,1000,100 };
			settextcolor(BLACK);
			settextstyle(15, 0, _T("����"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			/*����浵*/
			FILE* clear;
			clear = fopen("D:\\C_Project_Resource\\documents.txt", "w");
			fclose(clear);
			clear = fopen("D:\\C_Project_Resource\\continous_state\\Borrowing.txt", "w");
			fclose(clear);
			clear = fopen("D:\\C_Project_Resource\\continous_state\\Saving.txt", "w");
			fclose(clear);
			clear = fopen("D:\\C_Project_Resource\\continous_state\\Loan.txt", "w");
			fclose(clear);
			clear = fopen("D:\\C_Project_Resource\\continous_state\\Recovering.txt", "w");
			fclose(clear);
			clear = fopen("D:\\C_Project_Resource\\continous_state\\Easier.txt", "w");
			fclose(clear);
			clear = fopen("D:\\C_Project_Resource\\continous_state\\Fresh.txt", "w");
			fclose(clear);
			break;
			_getch();
			closegraph();
			break;
		}
		else
		{
			_stprintf_s(s, _T("��Ϸ���Զ�����"));
			settextcolor(BLACK);
			settextstyle(25, 0, _T("����"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			Sleep(1500);
			settextcolor(WHITE);
			settextstyle(25, 0, _T("����"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			save_game(); //�غϽ�������Ϸ�Զ�����
		}
	}
}