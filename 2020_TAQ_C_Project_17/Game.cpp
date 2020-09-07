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

/*状态*/
#define STATENUMBER 12 //状态总数
#define REST 0 //休息
#define EXPERIMENT 1  //实践与理论相结合
#define BORROWING 2 //借阅中
#define STUDYING 3 //自习中
#define SAVING 4 //储蓄中
#define LOAN 5 //贷款
#define EASIER 6 //轻松学习
#define RECOVERING 7 //精力恢复
#define FRESH 8 //提神醒脑
#define SKILLFUL 9 //登峰造极
#define UNFAMILIAR 10 //生疏
#define FAILURE 11 //失败
/*道具*/
#define ITEMNUMBER 7 //道具总数
#define MAGIC_DICE 0 //百变骰子
#define TRADING_LICENSE 1 //交易许可证
#define LEARNING_MATERIALS 2 //学习资料
#define STAYING_UP_DOOR 3 //刷夜传送门
#define SWAP 4 //移形换位
#define ENERGY_DRINK 5 //能量饮料
#define ADVANCED_READINGS 6 //进阶读物
/*事件*/
#define EVENTNUMBER 12 //事件总数
#define LATE 0 //上课迟到
#define OVERPLAY 1 //浪脱了整个假期
#define STAY_UP 2 //熬夜打游戏
#define RECHARGE 3 //氪金
#define ILL 4 //大病一场
#define BIRTHDAY 5 //过生日
#define PART_TIME_JOB 6 //周末赚外快
#define LIVING_EXEPENSES 7 //生活费补贴
#define DDL_END 8 //ddl终结
#define SCHOLARSHIP 9 //奖学金
#define SAVE 10 //储蓄
#define CAMPUS_LOAN 11 //校园贷
/*棋盘*/
#define START 0 //开始
#define CAL 1 //微积分
#define L_A 2 //线性代数
#define ENTRANCE 3 //刷夜区入口
#define P_A_S 4 //概率论与数理统计
#define EVENT_CARD 5 //事件卡
#define LABORATORY 6 //实验室
#define P_O_C 7 //化学原理
#define I_E_C 8 //无机元素化学
#define O_C 9 //有机化学
#define P_C 10 //物理化学
#define S_C 11 //结构化学
#define LIBRARY 12 //图书馆
#define A_C 13 //分析化学
#define I_A 14 //仪器分析
#define EXIT 15 //刷夜区出口
#define B_O_C_E 16 //大学计算机基础
#define C_P 17 //C语言程序设计基础
#define STUDY_ROOM 18 //自习室
#define ENG 19 //大学英语
#define ITEM_CARD 20 //道具卡
#define P_A_I 21 //政治理论与思想教育专题
#define PE 22 //体育
#define G_P 23 //普通物理
#define B_M -5 //书山
#define C_M -4 //咖啡机
#define M_S_B -3 //夜宵摊
#define E_S -2 //题海
#define B_D -1 //早餐厅
/*课程类型*/
#define MAJOR 1
#define M_A_P 2
#define CS 3
#define OTHER 4

/*玩家结构体*/
struct player
{
	char name;
	int gold = 500; //初始金钱500
	int energy = 10; //初始精力10
	bool state[STATENUMBER] = { false }; //状态栏
	int item[ITEMNUMBER] = { 0 }; //道具栏
	int position = START; //位置
	int* level; //课程等级指针
	int rank = 1; //排名
};
/*课程结构体*/
struct course
{
	int max_level; //课程最高等级
	int category; //类型
	bool forget; //遗忘制度
	int energy_cost[7]; //精力消耗
	int gold_gain[7]; //收益
	int playerA_level = 0, playerB_level = 0, playerC_level = 0, playerD_level = 0; //玩家课程等级
};

/*初始化*/
TCHAR position_text[100];
TCHAR guide_text[200];
RECT position_r = { 725,170,975,320 }; //位置显示区域
RECT guide_r = { 725,400,975,650 }; //操作指导区域
int playernumber = 4; //玩家人数
int Round = 1; //回合数
bool load_continous_state = false; //控制载入持续性状态回合数存档
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
	for (i = 0; i < cal.max_level; i++) //微积分
	{
		cal.energy_cost[i] = i + 1; //精力消耗1/2/3/4/5
		cal.gold_gain[i] = 40 * (i + 1); //收益40/80/120/160/200
	}
	for (i = 0; i < l_a.max_level; i++) //线性代数
	{
		l_a.energy_cost[i] = 2 * i + 1; //精力消耗1/3/5
		l_a.gold_gain[i] = 60 * (i + 1); //收益60/120/180
	}
	for (i = 0; i < p_a_s.max_level; i++) //概率论与数理统计
	{
		p_a_s.energy_cost[i] = 2 * i + 1; //精力消耗1/3/5
		p_a_s.gold_gain[i] = 70 * (i + 1); //收益70/140/210
	}
	for (i = 0; i < g_p.max_level; i++) //普通物理
	{
		g_p.energy_cost[i] = i + 1; //精力消耗1/2/3/4/5
		g_p.gold_gain[i] = 40 * (i + 1); //收益40/80/120/160/200
	}
	for (i = 0; i < p_o_c.max_level; i++) //化学原理
	{
		p_o_c.energy_cost[i] = 2 * i + 1; //精力消耗1/3/5
		p_o_c.gold_gain[i] = 60 * (i + 1); //收益60/120/180
	}
	for (i = 0; i < i_e_c.max_level; i++) //无机元素化学
	{
		i_e_c.energy_cost[i] = 2 * i + 1; //精力消耗1/3/5
		i_e_c.gold_gain[i] = 60 * (i + 1); //收益60/120/180
	}
	for (i = 0; i < o_c.max_level; i++) //有机化学
	{
		o_c.energy_cost[i] = i + 1; //精力消耗1/2/3/4/5
		o_c.gold_gain[i] = 20 * (int)(pow(2, i)); //收益20/40/80/160/320
	}
	for (i = 0; i < p_c.max_level; i++) //物理化学
	{
		p_c.energy_cost[i] = 2 * (i + 1); //精力消耗2/4/6/8
		if (i != p_c.max_level - 1) //收益80/160/240/360
			p_c.gold_gain[i] = 80 * (i + 1);
		else
			p_c.gold_gain[i] = 360;
	}
	for (i = 0; i < s_c.max_level; i++) //结构化学
	{
		s_c.energy_cost[i] = 2 * (i + 1); //精力消耗2/4/6
		s_c.gold_gain[i] = 80 * (i + 1); //收益80/160/240
	}
	for (i = 0; i < a_c.max_level; i++) //分析化学
	{
		a_c.energy_cost[i] = (int)(pow(2, i)); //精力消耗1/2/4
		a_c.gold_gain[i] = 60 + 40 * i; //收益60/100/140
	}
	for (i = 0; i < i_a.max_level; i++) //仪器分析
	{
		i_a.energy_cost[i] = 2 * i + 1; //精力消耗1/3/5
		i_a.gold_gain[i] = 80 + 40 * i; //收益80/120/160
	}
	for (i = 0; i < b_o_c_e.max_level; i++) //大学计算机基础
	{
		b_o_c_e.energy_cost[i] = 2 * i + 1; //精力消耗1/3/5
		b_o_c_e.gold_gain[i] = 20 + 40 * i; //收益20/60/100
	}
	for (i = 0; i < c_p.max_level; i++) //C语言程序设计基础
	{
		c_p.energy_cost[i] = 2 * (i + 1); //精力消耗2/4/6
		c_p.gold_gain[i] = 60 * (int)(pow(2, i)); //收益60/120/240
	}
	for (i = 0; i < eng.max_level; i++) //大学英语
	{
		eng.energy_cost[i] = i + 1; //精力消耗1/2/3/4/5/6/7
		if (i >= eng.max_level - 2) //收益40/60/80/100/120/160/200
			eng.gold_gain[i] = 40 * i - 40;
		else
			eng.gold_gain[i] = 40 + 20 * i;
	}
	for (i = 0; i < p_a_i.max_level; i++) //政治理论与思想教育专题
	{
		p_a_i.energy_cost[i] = i + 1; //精力消耗1/2/3/4/5/6/7
		if (i >= p_a_i.max_level - 2) //收益20/40/60/80/100/130/170
			p_a_i.gold_gain[i] = 40 * i - 70;
		else
			p_a_i.gold_gain[i] = 20 * (i + 1);
	}
	for (i = 0; i < pe.max_level; i++) //体育
	{
		pe.energy_cost[i] = i + 1; //精力消耗1/2/3/4/5/6/7
		if (i >= pe.max_level - 2) //收益20/40/60/80/100/130/170
			pe.gold_gain[i] = 40 * i - 70;
		else
			pe.gold_gain[i] = 20 * (i + 1);
	}
}

/*存档函数*/
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
/*读档函数*/
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

/*玩家信息显示函数*/
void show_player(struct player* playerX, bool end)
{
	settextstyle(18, 0, _T("黑体"));
	TCHAR s[50];
	RECT r;
	if (!end) //非回合结束通过彩色绘制玩家信息
	{
		switch (playerX->name)
		{
		case 'A':
			settextcolor(LIGHTRED);
			_stprintf_s(s, _T("玩家A\n精力：%d\n金钱：%d"), playerX->energy, playerX->gold);
			r = { 120,123,280,343 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'B':
			settextcolor(BLUE);
			_stprintf_s(s, _T("玩家B\n精力：%d\n金钱：%d"), playerX->energy, playerX->gold);
			r = { 420,123,580,343 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'C':
			settextcolor(MAGENTA);
			_stprintf_s(s, _T("玩家C\n精力：%d\n金钱：%d"), playerX->energy, playerX->gold);
			r = { 120,363,280,583 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'D':
			settextcolor(GREEN);
			_stprintf_s(s, _T("玩家D\n精力：%d\n金钱：%d"), playerX->energy, playerX->gold);
			r = { 420,363,580,583 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		}
	}
	else //回合结束通过白色擦除信息
	{
		settextcolor(WHITE);
		switch (playerX->name)
		{
		case 'A':
			_stprintf_s(s, _T("玩家A\n精力：%d\n金钱：%d"), playerX->energy, playerX->gold);
			r = { 120,123,280,343 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'B':
			_stprintf_s(s, _T("玩家B\n精力：%d\n金钱：%d"), playerX->energy, playerX->gold);
			r = { 420,123,580,343 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'C':
			_stprintf_s(s, _T("玩家C\n精力：%d\n金钱：%d"), playerX->energy, playerX->gold);
			r = { 120,363,280,583 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		case 'D':
			_stprintf_s(s, _T("玩家D\n精力：%d\n金钱：%d"), playerX->energy, playerX->gold);
			r = { 420,363,580,583 };
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			break;
		}
	}
}
/*状态栏显示函数*/
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
/*道具栏显示函数*/
void show_item(void)
{
	IMAGE item;
	BeginBatchDraw();
	loadimage(&item, _T("D:\\C_Project_Resource\\百变骰子.jpg"));
	putimage(120, 260, &item);
	putimage(420, 260, &item);
	putimage(120, 500, &item);
	putimage(420, 500, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\刷夜传送门.jpg"));
	putimage(160, 260, &item);
	putimage(460, 260, &item);
	putimage(160, 500, &item);
	putimage(460, 500, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\移形换位.jpg"));
	putimage(200, 260, &item);
	putimage(500, 260, &item);
	putimage(200, 500, &item);
	putimage(500, 500, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\能量饮料.jpg"));
	putimage(240, 260, &item);
	putimage(540, 260, &item);
	putimage(240, 500, &item);
	putimage(540, 500, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\学习资料.jpg"));
	putimage(120, 300, &item);
	putimage(420, 300, &item);
	putimage(120, 540, &item);
	putimage(420, 540, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\交易许可证.jpg"));
	putimage(160, 300, &item);
	putimage(460, 300, &item);
	putimage(160, 540, &item);
	putimage(460, 540, &item);
	loadimage(&item, _T("D:\\C_Project_Resource\\进阶读物.jpg"));
	putimage(200, 300, &item);
	putimage(500, 300, &item);
	putimage(200, 540, &item);
	putimage(500, 540, &item);
	EndBatchDraw();
}
/*道具栏数量函数*/
void item_number(struct player* playerX)
{
	TCHAR number[5];
	settextcolor(BLACK);
	settextstyle(15, 0, _T("宋体"));
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

/*课程信息显示函数*/
void show_course_information(void)
{
	TCHAR s[80];
	RECT r;
	int i = 0;
	TCHAR sn[8];
	settextstyle(12, 0, _T("宋体"));
	BeginBatchDraw();
	/*微积分*/
	_stprintf_s(s, _T("课程最高等级：%d"), cal.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < cal.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), cal.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < cal.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), cal.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 500,625,600,695 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*线性代数*/
	_stprintf_s(s, _T("课程最高等级：%d"), l_a.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < l_a.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), l_a.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < l_a.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), l_a.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 400,625,500,695 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*概率论与数理统计*/
	_stprintf_s(s, _T("课程最高等级：%d"), p_a_s.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < p_a_s.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_a_s.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < p_a_s.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_a_s.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 200,625,300,695 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*化学原理*/
	_stprintf_s(s, _T("课程最高等级：%d"), p_o_c.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < p_o_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_o_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < p_o_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_o_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,525,100,595 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*无机元素化学*/
	_stprintf_s(s, _T("课程最高等级：%d"), i_e_c.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < i_e_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), i_e_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < i_e_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), i_e_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,425,100,495 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*有机化学*/
	_stprintf_s(s, _T("课程最高等级：%d"), o_c.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < o_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), o_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < o_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), o_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,325,100,395 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*物理化学*/
	_stprintf_s(s, _T("课程最高等级：%d"), p_c.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < p_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < p_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,225,100,295 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*结构化学*/
	_stprintf_s(s, _T("课程最高等级：%d"), s_c.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < s_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), s_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < s_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), s_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 0,125,100,195 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*分析化学*/
	_stprintf_s(s, _T("课程最高等级：%d"), a_c.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < a_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), a_c.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < a_c.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), a_c.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 100,25,200,95 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*仪器分析*/
	_stprintf_s(s, _T("课程最高等级：%d"), i_a.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < i_a.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), i_a.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < i_a.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), i_a.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 200,25,300,95 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*大学计算机基础*/
	_stprintf_s(s, _T("课程最高等级：%d"), b_o_c_e.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < b_o_c_e.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), b_o_c_e.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < b_o_c_e.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), b_o_c_e.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 400,25,500,95 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*C语言程序设计基础*/
	_stprintf_s(s, _T("课程最高等级：%d"), c_p.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < c_p.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), c_p.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < c_p.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), c_p.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 500,25,600,95 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*大学英语*/
	_stprintf_s(s, _T("课程最高等级：%d"), eng.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < eng.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), eng.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < eng.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), eng.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 600,125,700,195 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*政治理论与思想教育专题*/
	_stprintf_s(s, _T("课程最高等级：%d"), p_a_i.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < p_a_i.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_a_i.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < p_a_i.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), p_a_i.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 600,325,700,395 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*体育*/
	_stprintf_s(s, _T("课程最高等级：%d"), pe.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < pe.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), pe.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < pe.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), pe.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 600,425,700,495 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*普通物理*/
	_stprintf_s(s, _T("课程最高等级：%d"), g_p.max_level);
	_tcscat_s(s, _T("\n精力消耗：\n"));
	for (i = 0; i < g_p.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), g_p.energy_cost[i]);
		_tcscat_s(s, sn);
	}
	_tcscat_s(s, _T("\n收益：\n"));
	for (i = 0; i < g_p.max_level; i++)
	{
		_stprintf_s(sn, _T("%d "), g_p.gold_gain[i]);
		_tcscat_s(s, sn);
	}
	r = { 600,525,700,595 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	EndBatchDraw();
}
/*课程等级显示函数*/
void show_course_level(void)
{
	TCHAR s[80];
	RECT r;
	settextstyle(16, 0, _T("Ink Free"));
	/*微积分*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), cal.playerA_level, cal.max_level, cal.playerB_level, cal.max_level, cal.playerC_level, cal.max_level, cal.playerD_level, cal.max_level);
	r = { 500,630,600,700 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*线性代数*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), l_a.playerA_level, l_a.max_level, l_a.playerB_level, l_a.max_level, l_a.playerC_level, l_a.max_level, l_a.playerD_level, l_a.max_level);
	r = { 400,630,500,700 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*概率论与数理统计*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), p_a_s.playerA_level, p_a_s.max_level, p_a_s.playerB_level, p_a_s.max_level, p_a_s.playerC_level, p_a_s.max_level, p_a_s.playerD_level, p_a_s.max_level);
	r = { 200,630,300,700 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*化学原理*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), p_o_c.playerA_level, p_o_c.max_level, p_o_c.playerB_level, p_o_c.max_level, p_o_c.playerC_level, p_o_c.max_level, p_o_c.playerD_level, p_o_c.max_level);
	r = { 0,530,100,600 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*无机元素化学*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), i_e_c.playerA_level, i_e_c.max_level, i_e_c.playerB_level, i_e_c.max_level, i_e_c.playerC_level, i_e_c.max_level, i_e_c.playerD_level, i_e_c.max_level);
	r = { 0,430,100,500 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*有机化学*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), o_c.playerA_level, o_c.max_level, o_c.playerB_level, o_c.max_level, o_c.playerC_level, o_c.max_level, o_c.playerD_level, o_c.max_level);
	r = { 0,330,100,400 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*物理化学*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), p_c.playerA_level, p_c.max_level, p_c.playerB_level, p_c.max_level, p_c.playerC_level, p_c.max_level, p_c.playerD_level, p_c.max_level);
	r = { 0,230,100,300 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*结构化学*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), s_c.playerA_level, s_c.max_level, s_c.playerB_level, s_c.max_level, s_c.playerC_level, s_c.max_level, s_c.playerD_level, s_c.max_level);
	r = { 0,130,100,200 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*分析化学*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), a_c.playerA_level, a_c.max_level, a_c.playerB_level, a_c.max_level, a_c.playerC_level, a_c.max_level, a_c.playerD_level, a_c.max_level);
	r = { 100,30,200,100 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*仪器分析*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), i_a.playerA_level, i_a.max_level, i_a.playerB_level, i_a.max_level, i_a.playerC_level, i_a.max_level, i_a.playerD_level, i_a.max_level);
	r = { 200,30,300,100 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*大学计算机基础*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), b_o_c_e.playerA_level, b_o_c_e.max_level, b_o_c_e.playerB_level, b_o_c_e.max_level, b_o_c_e.playerC_level, b_o_c_e.max_level, b_o_c_e.playerD_level, b_o_c_e.max_level);
	r = { 400,30,500,100 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*C语言程序设计基础*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), c_p.playerA_level, c_p.max_level, c_p.playerB_level, c_p.max_level, c_p.playerC_level, c_p.max_level, c_p.playerD_level, c_p.max_level);
	r = { 500,30,600,100 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*大学英语*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), eng.playerA_level, eng.max_level, eng.playerB_level, eng.max_level, eng.playerC_level, eng.max_level, eng.playerD_level, eng.max_level);
	r = { 600,130,700,200 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*政治理论与思想教育专题*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), p_a_i.playerA_level, p_a_i.max_level, p_a_i.playerB_level, p_a_i.max_level, p_a_i.playerC_level, p_a_i.max_level, p_a_i.playerD_level, p_a_i.max_level);
	r = { 600,330,700,400 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*体育*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), pe.playerA_level, pe.max_level, pe.playerB_level, pe.max_level, pe.playerC_level, pe.max_level, pe.playerD_level, pe.max_level);
	r = { 600,430,700,500 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
	/*普通物理*/
	_stprintf_s(s, _T("level A：%d/%d\nlevel B：%d/%d\nlevel C：%d/%d\nlevel D：%d/%d"), g_p.playerA_level, g_p.max_level, g_p.playerB_level, g_p.max_level, g_p.playerC_level, g_p.max_level, g_p.playerD_level, g_p.max_level);
	r = { 600,530,700,600 };
	drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
}

/*位置绘制函数*/
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
/*位置选择函数*/
void select_position(struct player* playerX, bool leave)
{
	if (!leave) //到达位置通过彩色圆绘制棋子位置
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
	else //离开位置通过白色圆擦除棋子位置
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

/*失败玩家课程等级划除函数*/
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
/*课程查看函数*/
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
	_stprintf_s(guide_text, _T("鼠标右键查看课程信息\n鼠标左键跳过查看"));
	settextcolor(BLACK);
	settextstyle(15, 0, _T("宋体"));
	drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_RBUTTONDOWN) //按下鼠标右键查看课程信息
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
			else if (m.uMsg == WM_RBUTTONUP) //松开鼠标右键显示课程等级
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
			else if (m.uMsg == WM_LBUTTONUP) //鼠标左键跳过查看
			{
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK); //清空操作指导区域
				break;
			}
			else
				FlushMouseMsgBuffer();
		}
		if (_kbhit())
			_getch();
	}
}

/*判定失败函数*/
void failure(struct player* playerX)
{
	if (playerX->energy <= 0 || playerX->gold < 0) //精力耗尽或金钱耗尽则失败
	{
		_stprintf_s(guide_text, _T("玩家%c精力殆尽或金钱不足——失败"), playerX->name);
		settextcolor(BROWN);
		settextstyle(15, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		Sleep(1000);
		settextcolor(WHITE);
		settextstyle(15, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		select_position(playerX, true);
		for (int i = 0; i < (STATENUMBER - 1); i++)
			playerX->state[i] = false;
		for (int i = 0; i < ITEMNUMBER; i++)
			playerX->item[i] = 0;
		playerX->state[FAILURE] = true;
		playerX->rank = playernumber; //结算排名
		playernumber -= 1;
	}
}

/*事件卡函数*/
void position(struct player*); //位置响应函数原型
void event_card(struct player* playerX)
{
	int i, j;
	i = rand() % EVENTNUMBER;
	j = rand() % 100;
	if (j >= 0 && j <= 2)
	{
		_tcscat_s(position_text, _T("一夜暴富（小概率事件）\n当前金钱翻倍"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold *= 2;
		return;
	}
	if (j >= 10 && j <= 12)
	{
		_tcscat_s(position_text, _T("时空裂隙（小概率事件）\n传送至非刷夜区的随机位置"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		select_position(playerX, true);
		playerX->position = rand() % 24;
		select_position(playerX, false);
		return;
	}
	if (j >= 20 && j <= 22)
	{
		_tcscat_s(position_text, _T("洗劫一空（小概率事件）\n失去当前所有的道具"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		for (int k = 0; k < ITEMNUMBER; k++)
			playerX->item[k] = 0;
		return;
	}
	if (j >= 30 && j <= 32)
	{
		_tcscat_s(position_text, _T("噩梦（小概率事件）\n精力减半（至少剩余1点精力）并休息一回合"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (playerX->energy > 1)
			playerX->energy /= 2;
		playerX->state[REST] = true;
		return;
	}
	if (j >= 40 && j < 42)
	{
		_tcscat_s(position_text, _T("名师的指点（小概率事件）\n同时点亮状态——轻松学习、登峰造极、实践与理论相结合"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[EASIER] = true;
		playerX->state[SKILLFUL] = true;
		playerX->state[EXPERIMENT] = true;
		return;
	}
	switch (i)
	{
	case LATE:
		_tcscat_s(position_text, _T("迟到\n点亮状态——休息：跳过一回合"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[REST] = true;
		break;
	case OVERPLAY:
		_tcscat_s(position_text, _T("浪脱了整个假期\n点亮状态——生疏：下次课程学习精力消耗+3"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[UNFAMILIAR] = true;
		break;
	case STAY_UP:
		_tcscat_s(position_text, _T("熬夜打游戏\n精力-2"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy -= 2;
		break;
	case RECHARGE:
		_tcscat_s(position_text, _T("氪金\n金钱-100"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold -= 100;
		break;
	case ILL:
		_tcscat_s(position_text, _T("大病一场\n精力-5"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy -= 5;
		break;
	case BIRTHDAY:
		_tcscat_s(position_text, _T("庆祝生日\n精力+7，金钱-300"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 7;
		playerX->gold -= 300;
		break;
	case PART_TIME_JOB:
		_tcscat_s(position_text, _T("周末兼职\n精力-3，金钱+200"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy -= 3;
		playerX->gold += 200;
		break;
	case LIVING_EXEPENSES:
		_tcscat_s(position_text, _T("月底生活费\n金钱+150"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold += 150;
		break;
	case DDL_END:
		_tcscat_s(position_text, _T("ddl终结\n精力+6"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 6;
		break;
	case SCHOLARSHIP:
		_tcscat_s(position_text, _T("奖学金\n金钱+300"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold += 300;
		break;
	case SAVE:
		_tcscat_s(position_text, _T("储蓄\n金钱-200，接下来的五个回合每回合结束金钱+60（点亮状态：储蓄中）"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold -= 200;
		playerX->state[SAVING] = true;
		break;
	case CAMPUS_LOAN:
		_tcscat_s(position_text, _T("校园贷\n金钱+400，接下来的五个回合每回合结束金钱-100（点亮状态：贷款）"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold += 400;
		playerX->state[LOAN] = true;
		break;
	}
	failure(playerX);
}
/*道具卡函数*/
void item_card(struct player* playerX)
{
	int i;
	for (int j = 0; j < 2; j++)
	{
		i = rand() % (ITEMNUMBER - 1); //进阶读物不能通过道具卡随机获得
		playerX->item[i] += 1;
		switch (i)
		{
		case MAGIC_DICE:
			_tcscat_s(position_text, _T("获得百变骰子\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case TRADING_LICENSE:
			_tcscat_s(position_text, _T("获得交易许可证\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case LEARNING_MATERIALS:
			_tcscat_s(position_text, _T("获得学习资料\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case STAYING_UP_DOOR:
			_tcscat_s(position_text, _T("获得刷夜传送门\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case SWAP:
			_tcscat_s(position_text, _T("获得移形换位\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		case ENERGY_DRINK:
			_tcscat_s(position_text, _T("获得能量饮料\n"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
			break;
		}
	}
}

/*收益加成函数*/
int extra(struct player* playerX, struct course* courseX)
{
	int extra_gold = 0;
	if (courseX->category == MAJOR) //专业课收益加成：数理课程+60，计算机课程+40，每本进阶读物+20
	{
		switch (playerX->name)
		{
		case 'A':
			if (cal.playerA_level > 0 && l_a.playerA_level > 0 && p_a_s.playerA_level > 0 && g_p.playerA_level > 0)
			{
				_stprintf_s(guide_text, _T("玩家A已学习所有数理通识课程，专业课程收益+60"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 60;
			}
			if (b_o_c_e.playerA_level > 0 && c_p.playerA_level > 0)
			{
				_stprintf_s(guide_text, _T("玩家A已学习所有计算机通识课程，专业课程收益+40"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 40;
			}
			extra_gold += playerA.item[ADVANCED_READINGS] * 30;
			break;
		case 'B':
			if (cal.playerB_level > 0 && l_a.playerB_level > 0 && p_a_s.playerB_level > 0 && g_p.playerB_level > 0)
			{
				_stprintf_s(guide_text, _T("玩家B已学习所有数理通识课程，专业课程收益+60"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 60;
			}
			if (b_o_c_e.playerB_level > 0 && c_p.playerB_level > 0)
			{
				_stprintf_s(guide_text, _T("玩家B已学习所有计算机通识课程，专业课程收益+40"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 40;
			}
			extra_gold += playerB.item[ADVANCED_READINGS] * 30;
			break;
		case 'C':
			if (cal.playerC_level > 0 && l_a.playerC_level > 0 && p_a_s.playerC_level > 0 && g_p.playerC_level > 0)
			{
				_stprintf_s(guide_text, _T("玩家C已学习所有数理通识课程，专业课程收益+60"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 60;
			}
			if (b_o_c_e.playerC_level > 0 && c_p.playerC_level > 0)
			{
				_stprintf_s(guide_text, _T("玩家C已学习所有计算机通识课程，专业课程收益+40"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 40;
			}
			extra_gold += playerC.item[ADVANCED_READINGS] * 30;
			break;
		case 'D':
			if (cal.playerD_level > 0 && l_a.playerD_level > 0 && p_a_s.playerD_level > 0 && g_p.playerD_level > 0)
			{
				_stprintf_s(guide_text, _T("玩家D已学习所有数理通识课程，专业课程收益+60"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 60;
			}
			if (b_o_c_e.playerD_level > 0 && c_p.playerD_level > 0)
			{
				_stprintf_s(guide_text, _T("玩家D已学习所有计算机通识课程，专业课程收益+40"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				extra_gold += 40;
			}
			extra_gold += playerD.item[ADVANCED_READINGS] * 30;
			break;
		}
	}
	return extra_gold;
}
/*金钱缴纳函数*/
void pay(struct player* playerX, struct player* playerY, struct course* courseX)
{
	if (*playerY->level > * playerX->level && !playerY->state[FAILURE])
	{
		if (playerY->state[STUDYING])
		{
			_stprintf_s(guide_text, _T("玩家%c自习中，不会获得收益"), playerX->name);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(2000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("玩家%c缴纳给玩家%c %d金钱"), playerX->name, playerY->name, gold_gain);
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
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1500);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			playerX->gold -= gold_gain;
			playerY->gold += gold_gain;
		}
	}
}
/*金钱与精力消耗结算函数*/
bool cost(struct player* playerX, struct course* courseX)
{
	bool learned = false;
	char input;
	if (*playerX->level < courseX->max_level)
	{
		if ((*playerA.level <= *playerX->level || playerA.state[FAILURE]) && (*playerB.level <= *playerX->level || playerB.state[FAILURE]) && (*playerC.level <= *playerX->level || playerC.state[FAILURE]) && (*playerD.level <= *playerX->level || playerD.state[FAILURE])) //优先学习者无需缴纳金钱
		{
			if (playerX->state[SKILLFUL])
			{
				_stprintf_s(guide_text, _T("状态：登峰造极\nL：学习课程（其他键放弃学习）"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				input = _getch();
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				if (input == 'l' || input == 'L') //按下“L”键进行学习，其他键放弃学习
				{
					_stprintf_s(guide_text, _T("学习成功"));
					settextcolor(RED);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
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
				_stprintf_s(guide_text, _T("L：学习课程（其他键放弃学习）"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				input = _getch();
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				if (input == 'l' || input == 'L') //按下“L”键进行学习，其他键放弃学习
				{
					int energy_cost = courseX->energy_cost[*playerX->level];
					if (playerX->state[EASIER])
					{
						_stprintf_s(guide_text, _T("状态：轻松学习"));
						settextcolor(BLACK);
						settextstyle(15, 0, _T("宋体"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						Sleep(1000);
						settextcolor(WHITE);
						settextstyle(15, 0, _T("宋体"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						if (energy_cost > 1)
							energy_cost /= 2;
					}
					if (playerX->state[UNFAMILIAR])
					{
						_stprintf_s(guide_text, _T("状态：生疏"));
						settextcolor(BLACK);
						settextstyle(15, 0, _T("宋体"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						Sleep(1000);
						settextcolor(WHITE);
						settextstyle(15, 0, _T("宋体"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						energy_cost += 3;
					}
					if (playerX->energy <= energy_cost)
					{
						_stprintf_s(guide_text, _T("精力不足，学习失败"));
						settextcolor(RED);
						settextstyle(15, 0, _T("宋体"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						Sleep(1000);
						settextcolor(WHITE);
						settextstyle(15, 0, _T("宋体"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						return false;
					}
					else
					{
						_stprintf_s(guide_text, _T("学习成功"));
						settextcolor(RED);
						settextstyle(15, 0, _T("宋体"));
						drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
						Sleep(1000);
						settextcolor(WHITE);
						settextstyle(15, 0, _T("宋体"));
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
				_stprintf_s(guide_text, _T("状态：登峰造极\n学习成功"));
				settextcolor(RED);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
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
					_stprintf_s(guide_text, _T("状态：轻松学习"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					if (energy_cost > 1)
						energy_cost /= 2;
				}
				if (playerX->state[UNFAMILIAR])
				{
					_stprintf_s(guide_text, _T("状态：生疏"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
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
				_stprintf_s(guide_text, _T("学习成功"));
				settextcolor(RED);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("该课程已达到最高等级，具有遗忘机制\nL：复习（消耗3点精力，其他键放弃复习，课程等级-1）"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			input = _getch();
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if ((input == 'l' || input == 'L') && playerX->energy > 3) //按下“L”键进行复习，其他键放弃复习
			{
				_stprintf_s(guide_text, _T("复习成功"));
				settextcolor(RED);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				playerX->energy -= 3;
			}
			else
			{
				_stprintf_s(guide_text, _T("未复习"));
				settextcolor(RED);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
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
/*课程学习函数*/
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
/*实践与理论相结合函数*/
void experience(struct player* playerX, struct course* courseX)
{
	if (playerX->state[EXPERIMENT] && *playerX->level < courseX->max_level)
	{

		char input;
		_stprintf_s(guide_text, _T("状态：实践与理论相结合\nK：再次学习课程（其他键放弃学习）"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		input = _getch();
		settextcolor(WHITE);
		settextstyle(15, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		if (input == 'k' || input == 'K')
		{
			if (learn(playerX, courseX))
				playerX->state[EXPERIMENT] = false;
		}
	}
}

/*位置响应函数*/
void position(struct player* playerX)
{
	select_position(playerX, false);
	_stprintf_s(position_text, _T("玩家%c的位置\n"), playerX->name);
	switch (playerX->position)
	{
	case START:
		_tcscat_s(position_text, _T("***起始位置***\n金钱+400"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->gold += 400;
		break;
	case CAL:
		_tcscat_s(position_text, _T("***微积分***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &cal);
		break;
	case L_A:
		_tcscat_s(position_text, _T("***线性代数***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &l_a);
		break;
	case ENTRANCE:
		_tcscat_s(position_text, _T("***刷夜区入口***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		break;
	case P_A_S:
		_tcscat_s(position_text, _T("***概率论与数理统计***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &p_a_s);
		break;
	case EVENT_CARD:
		_tcscat_s(position_text, _T("***事件卡***\n"));
		event_card(playerX);
		break;
	case LABORATORY:
		_tcscat_s(position_text, _T("***实验室***\n点亮状态——实践与理论相结合：可额外学习专业课程一次"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[EXPERIMENT] = true;
		break;
	case P_O_C:
		_tcscat_s(position_text, _T("***化学原理***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &p_o_c))
			experience(playerX, &p_o_c);
		break;
	case I_E_C:
		_tcscat_s(position_text, _T("***无机元素化学***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &i_e_c))
			experience(playerX, &i_e_c);
		break;
	case O_C:
		_tcscat_s(position_text, _T("***有机化学***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &o_c))
			experience(playerX, &o_c);
		break;
	case P_C:
		_tcscat_s(position_text, _T("***物理化学***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &p_c))
			experience(playerX, &p_c);
		break;
	case S_C:
		_tcscat_s(position_text, _T("***结构化学***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &s_c))
			experience(playerX, &s_c);
		break;
	case LIBRARY:
		_tcscat_s(position_text, _T("***图书馆***\n点亮状态——借阅：学习课程缴纳金钱减半，直至再次到达图书馆，若经十回合未再次到达图书馆，状态解除且金钱-250"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[BORROWING] = true;
		break;
	case A_C:
		_tcscat_s(position_text, _T("***分析化学***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &a_c))
			experience(playerX, &a_c);
		break;
	case I_A:
		_tcscat_s(position_text, _T("***仪器分析***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		if (learn(playerX, &i_a))
			experience(playerX, &i_a);
		break;
	case EXIT:
		_tcscat_s(position_text, _T("***刷夜区出口***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		break;
	case B_O_C_E:
		_tcscat_s(position_text, _T("***大学计算机基础***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &b_o_c_e);
		break;
	case C_P:
		_tcscat_s(position_text, _T("***C语言程序设计基础***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &c_p);
		break;
	case STUDY_ROOM:
		_tcscat_s(position_text, _T("***自习室***\n点亮状态——自习中：跳过一回合，不会获得收益也不会受到道具影响"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[STUDYING] = true;
		break;
	case ENG:
		_tcscat_s(position_text, _T("***大学英语***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &eng);
		break;
	case ITEM_CARD:
		_tcscat_s(position_text, _T("***道具卡***\n"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		item_card(playerX);
		break;
	case P_A_I:
		_tcscat_s(position_text, _T("***政治理论与思想教育专题***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &p_a_i);
		break;
	case PE:
		_tcscat_s(position_text, _T("***体育***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &pe);
		break;
	case G_P:
		_tcscat_s(position_text, _T("***普通物理***"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		learn(playerX, &g_p);
		break;
	case B_M:
		_tcscat_s(position_text, _T("***书山***\n获得进阶读物"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->item[ADVANCED_READINGS] += 1;
		break;
	case C_M:
		_tcscat_s(position_text, _T("***咖啡机***\n精力 + 15，接下来的十个回合每回合结束精力 - 1（点亮状态：提神醒脑）"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 15;
		playerX->state[FRESH] = true;
		break;
	case M_S_B:
		_tcscat_s(position_text, _T("***夜宵摊***\n精力+7，金钱-200"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 7;
		playerX->gold -= 200;
		failure(playerX);
		break;
	case E_S:
		_tcscat_s(position_text, _T("***题海***\n点亮状态——登峰造极：下次课程学习不需要消耗精力和缴纳金钱"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->state[SKILLFUL] = true;
		break;
	case B_D:
		_tcscat_s(position_text, _T("***早餐厅***\n精力+5"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
		playerX->energy += 5;
		break;
	}
	Sleep(4000);
	settextcolor(WHITE);
	settextstyle(15, 0, _T("宋体"));
	drawtext(position_text, &position_r, DT_CENTER | DT_WORDBREAK);
}

enum round_continue { borrowing_round = 10, saving_round = 5, loan_round = 5, recovering_round = 5, easier_round = 5, fresh_round = 10 };
/*借阅函数*/
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
			_stprintf_s(guide_text, _T("状态：借阅中（还剩%d个回合）"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text,_T( "状态：借阅中（还剩%d个回合）"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：借阅中（还剩%d个回合）"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：借阅中（还剩%d个回合）"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
/*储蓄函数*/
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
			_stprintf_s(guide_text, _T("状态：储蓄中（还剩%d个回合）"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：储蓄中（还剩%d个回合）"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：储蓄中（还剩%d个回合）"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：储蓄中（还剩%d个回合）"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
/*校园贷函数*/
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
			_stprintf_s(guide_text, _T("状态：贷款（还剩%d个回合）"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：贷款（还剩%d个回合）"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：贷款（还剩%d个回合）"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：贷款（还剩%d个回合）"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
/*精力恢复函数*/
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
			_stprintf_s(guide_text, _T("状态：精力恢复（还剩%d个回合）"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：精力恢复（还剩%d个回合）"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：精力恢复（还剩%d个回合）"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：精力恢复（还剩%d个回合）"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
/*轻松学习函数*/
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
			_stprintf_s(guide_text, _T("状态：轻松学习（还剩%d个回合）"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			a -= 1;
			if (a == -1)
			{
				a = easier_round;
				playerX->state[EASIER] = false;
			}
			break;
		case 'B':
			_stprintf_s(guide_text, _T("状态：轻松学习（还剩%d个回合）"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			b -= 1;
			if (b == -1)
			{
				b = easier_round;
				playerX->state[EASIER] = false;
			}
			break;
			_stprintf_s(guide_text, _T("状态：轻松学习（还剩%d个回合）"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			c -= 1;
			if (c == -1)
			{
				c = easier_round;
				playerX->state[EASIER] = false;
			}
			break;
		case 'D':
			_stprintf_s(guide_text, _T("状态：轻松学习（还剩%d个回合）"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
/*提神醒脑函数*/
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
			_stprintf_s(guide_text, _T("状态：提神醒脑（还剩%d个回合）"), a);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：提神醒脑（还剩%d个回合）"), b);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：提神醒脑（还剩%d个回合）"), c);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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
			_stprintf_s(guide_text, _T("状态：提神醒脑（还剩%d个回合）"), d);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
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

/*掷骰子函数*/
int roll(void)
{
	return 1 + rand() % 6;
}
/*百变骰子函数*/
int magic_dice(void)
{
	char input;
	int result;
	_stprintf_s(guide_text, _T("百变骰子——按下相应键选择骰子的范围\nW：1-3 E：4-6\nR：7-9 T：10-12"));
	settextcolor(BLACK);
	settextstyle(15, 0, _T("宋体"));
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
	settextstyle(15, 0, _T("宋体"));
	drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
	return result;
}

/*移形换位函数*/
bool swap(struct player* playerX)
{
	int temp;
	char input;
	int invalid_player = 0; //不可交换的玩家
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
		_stprintf_s(guide_text, _T("移形换位无可作用的玩家"));
		settextcolor(BLACK);
		settextstyle(15, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		Sleep(1000);
		settextcolor(WHITE);
		settextstyle(15, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		return false;
	}
	else
	{
		while (true)
		{
			_stprintf_s(guide_text, _T("按下相应键选择你要交换的玩家\nZ：玩家A X：玩家B\nC：玩家C V：玩家D"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			input = _getch();
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if ((input == 'z' || input == 'Z') && playerX->name != 'A')
			{
				if (playerA.state[FAILURE])
				{
					_stprintf_s(guide_text, _T("玩家A已判负，无法被道具作用"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else if (playerA.state[STUDYING])
				{
					_stprintf_s(guide_text, _T("玩家A自习中，无法被道具作用"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
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
					_stprintf_s(guide_text, _T("玩家B已判负，无法被道具作用"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else if (playerB.state[STUDYING])
				{
					_stprintf_s(guide_text, _T("玩家B自习中，无法被道具作用"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
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
					_stprintf_s(guide_text, _T("玩家C已判负，无法被道具作用"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else if (playerC.state[STUDYING])
				{
					_stprintf_s(guide_text, _T("玩家C自习中，无法被道具作用"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
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
					_stprintf_s(guide_text, _T("玩家D已判负，无法被道具作用"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
				else if (playerD.state[STUDYING])
				{
					_stprintf_s(guide_text, _T("玩家D自习中，无法被道具作用"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
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
/*购买道具函数*/
bool buy(struct player* playerX, struct player* playerY)
{
	char input;
	while (true)
	{
		_stprintf_s(guide_text, _T("按下相应键向玩家%c购买道具\n1：百变骰子(%d) 2：学习资料(%d\n3：能量饮料(%d) 4：移形换位(%d)\n5：刷夜传送门(%d)"), playerY->name, magic_dice_value / 2, learning_materials_value / 2, energy_drink_value / 2, swap_value / 2, staying_up_door_value / 2);
		settextcolor(BLACK);
		settextstyle(14, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		input = _getch();
		settextcolor(WHITE);
		settextstyle(14, 0, _T("宋体"));
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
/*交易许可证函数*/
bool trading_license(struct player* playerX)
{
	char input;
	while (true)
	{
		_stprintf_s(guide_text, _T("按下相应键选择你要交易的玩家\nZ：玩家A X：玩家B C：玩家C V：玩家D\n其他键与商店交易"));
		settextcolor(BLACK);
		settextstyle(14, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		input = _getch();
		settextcolor(WHITE);
		settextstyle(14, 0, _T("宋体"));
		drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		if ((input == 'z' || input == 'Z') && playerX->name != 'A')
		{
			if (playerA.state[FAILURE])
			{
				_stprintf_s(guide_text, _T("玩家A已判负，无法被道具作用"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else if (playerA.state[STUDYING])
			{
				_stprintf_s(guide_text, _T("玩家A自习中，无法被道具作用"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else
				return buy(playerX, &playerA);
		}
		if ((input == 'x' || input == 'X') && playerX->name != 'B')
		{
			if (playerB.state[FAILURE])
			{
				_stprintf_s(guide_text, _T("玩家B已判负，无法被道具作用"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else if (playerB.state[STUDYING])
			{
				_stprintf_s(guide_text, _T("玩家B自习中，无法被道具作用"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else
				return buy(playerX, &playerB);
		}
		if ((input == 'c' || input == 'C') && playerX->name != 'C')
		{
			if (playerC.state[FAILURE])
			{
				_stprintf_s(guide_text, _T("玩家C已判负，无法被道具作用"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else if (playerC.state[STUDYING])
			{
				_stprintf_s(guide_text, _T("玩家C自习中，无法被道具作用"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else
				return buy(playerX, &playerC);
		}
		if ((input == 'v' || input == 'V') && playerX->name != 'D')
		{
			if (playerD.state[FAILURE])
			{
				_stprintf_s(guide_text, _T("玩家D已判负，无法被道具作用"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else if (playerD.state[STUDYING])
			{
				_stprintf_s(guide_text, _T("玩家D自习中，无法被道具作用"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(1000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			}
			else
				return buy(playerX, &playerD);
		}
		if (input != 'z' && input != 'x' && input != 'c' && input != 'v' && input != 'Z' && input != 'X' && input != 'C' && input != 'V')
		{
			while (true)
			{
				_stprintf_s(guide_text, _T("按下相应键向商店购买道具\n1：百变骰子(%d) 2：学习资料(%d)\n3：能量饮料(%d) 4：移形换位(%d)\n5：刷夜传送门(%d)"), magic_dice_value, learning_materials_value, energy_drink_value, swap_value, staying_up_door_value);
				settextcolor(BLACK);
				settextstyle(14, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				input = _getch();
				settextcolor(WHITE);
				settextstyle(14, 0, _T("宋体"));
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

/*回合标记函数*/
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
/*玩家回合函数*/
void turn(struct player* playerX)
{
	char input;
	int step;
	/*更新玩家物品*/
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
	/*回合开始前查看课程信息*/
	view_course();
	if (playerX->state[REST] || playerX->state[STUDYING] || playerX->state[FAILURE]) //判断是否跳过回合
	{
		playerX->state[REST] = false;
		playerX->state[STUDYING] = false;
		if (playerX->state[FAILURE])
		{
			_stprintf_s(guide_text, _T("玩家%c已判负"), playerX->name);
			settextcolor(RED);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		}
		else
		{
			_stprintf_s(guide_text, _T("玩家%c跳过回合"), playerX->name);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			Sleep(1000);
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
		}
	}
	else
	{
		while (true)
		{
			_stprintf_s(guide_text, _T("空格:掷骰子，A:使用刷夜传送门\nS:使用移形换位，D:使用能量饮料\nF:使用学习资料，G:使用交易许可证"));
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			input = _getch();
			settextcolor(WHITE);
			settextstyle(15, 0, _T("宋体"));
			drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
			if (input == ' ') //按下空格键掷骰子
			{
				if (playerX->item[MAGIC_DICE] > 0)
				{
					_stprintf_s(guide_text, _T("Q：使用百变骰子（其他键跳过使用）"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					input = _getch();
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					if (input == 'q' || input == 'Q') //按下“Q”键使用百变骰子
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
				if (playerX->position == ENTRANCE) //刷夜区入口处按下空格键不进入刷夜区，其他键进入刷夜区并消耗4点精力，穿越刷夜区不消耗精力
				{
					_stprintf_s(guide_text, _T("骰子点数：%d\n空格：不进入刷夜区（其他键进入刷夜区并消耗4点精力，穿越刷夜区不消耗精力)\n"), step);
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					input = _getch();
					if (input == ' ')
					{
						select_position(playerX, true);
						playerX->position = (playerX->position + step) % 24;
						settextcolor(WHITE);
						settextstyle(15, 0, _T("宋体"));
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
					_stprintf_s(guide_text, _T("骰子点数：%d"), step);
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(2000);
				}
				if (playerX->position >= 0 && playerX->position != ENTRANCE) //非刷夜区行走
				{
					select_position(playerX, true);
					playerX->position = (playerX->position + step) % 24;
				}
				if (playerX->position < 0) //刷夜区行走
				{
					select_position(playerX, true);
					if (playerX->position + step < 0)
						playerX->position += step;
					else
						playerX->position = (EXIT + step + playerX->position) % 24;
				}
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				position(playerX);
				break;
			}
			else if ((input == 'a' || input == 'A') && playerX->item[STAYING_UP_DOOR] > 0)
			{
				_stprintf_s(guide_text, _T("传送至刷夜区内的随机位置"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(2000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
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
				_stprintf_s(guide_text, _T("点亮状态——精力恢复：接下来的五个回合每回合结束精力+1（精力<10时每回合结束精力+3）"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(2000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				playerX->state[RECOVERING] = true;
				playerX->item[ENERGY_DRINK] -= 1;
				break;
			}
			if ((input == 'f' || input == 'F') && playerX->item[LEARNING_MATERIALS] > 0)
			{
				_stprintf_s(guide_text, _T("点亮状态——轻松学习：接下来的五个回合学习课程精力消耗减半(至少消耗1点精力)"));
				settextcolor(BLACK);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				Sleep(2000);
				settextcolor(WHITE);
				settextstyle(15, 0, _T("宋体"));
				drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				playerX->state[EASIER] = true;
				playerX->item[LEARNING_MATERIALS] -= 1;
				break;
			}
			if ((input == 'g' || input == 'G') && playerX->item[TRADING_LICENSE] > 0)
			{
				if (trading_license(playerX))
				{
					_stprintf_s(guide_text, _T("交易成功"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					playerX->item[TRADING_LICENSE] -= 1;
					break;
				}
				else
				{
					_stprintf_s(guide_text, _T("交易无效"));
					settextcolor(BLACK);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
					Sleep(1000);
					settextcolor(WHITE);
					settextstyle(15, 0, _T("宋体"));
					drawtext(guide_text, &guide_r, DT_CENTER | DT_WORDBREAK);
				}
			}
		}
	}
	/*判定持续性状态*/
	easier(playerX);
	recovering(playerX);
	borrowing(playerX);
	saving(playerX);
	loan(playerX);
	fresh(playerX);
	load_continous_state = false;
	/*更新玩家信息*/
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

/*主函数*/
int main(void)
{
	/*播放背景音乐*/
	mciSendString(_T("open D:\\C_Project_Resource\\BGM.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	/*选择新游戏或读取存档*/
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
				/*清除存档*/
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
	/*游戏初始化*/
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
	/*开始游戏*/
	while (true)
	{
		_stprintf_s(s, _T("第%d回合"), Round);
		r = { 700,25,1000,75 };
		settextcolor(BLACK);
		settextstyle(25, 0, _T("宋体"));
		drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
		turn(&playerA);
		turn(&playerB);
		turn(&playerC);
		turn(&playerD);
		settextcolor(WHITE);
		settextstyle(25, 0, _T("宋体"));
		drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
		Round += 1;
		int energy_plus;
		if (Round % 4 == 0) //每四个回合所有玩家恢复2-6点精力（与回合数相关）
		{
			struct player copyA = playerA;
			struct player copyB = playerB;
			struct player copyC = playerC;
			struct player copyD = playerD;
			energy_plus = 2 + Round / 8;
			if (energy_plus > 6)
				energy_plus = 6;
			_stprintf_s(s, _T("新的一天开始了\n所有玩家精力+%d"), energy_plus);
			settextcolor(BLACK);
			settextstyle(25, 0, _T("宋体"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			Sleep(2500);
			settextcolor(WHITE);
			settextstyle(25, 0, _T("宋体"));
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
			_stprintf_s(s, _T("游戏结束\n排名：\n玩家A：第%d名 玩家B：第%d名\n玩家C：第%d名 玩家D：第%d名\n按任意键退出游戏"), playerA.rank, playerB.rank, playerC.rank, playerD.rank);
			r = { 700,0,1000,100 };
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			/*清除存档*/
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
			_stprintf_s(s, _T("游戏已自动保存"));
			settextcolor(BLACK);
			settextstyle(25, 0, _T("宋体"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			Sleep(1500);
			settextcolor(WHITE);
			settextstyle(25, 0, _T("宋体"));
			drawtext(s, &r, DT_CENTER | DT_WORDBREAK);
			save_game(); //回合结束，游戏自动保存
		}
	}
}