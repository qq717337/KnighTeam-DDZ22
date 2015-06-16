#ifndef define_h_
#define define_h_
#include<vector>
#include<set>

using namespace std;

#define MAX_Depth 120     //蒙特卡罗深度
#define AlphaBeta_Depth 3 // α-β模拟深度
#define RANDTIME 100		   // 随机模拟次数


#define PASS -1				// pass
#define INVALID 0 			//无效牌型
#define ROCKET 1			// 火箭
#define ZHADAN 2			// 炸弹
#define SINGLE 3			// 单牌
#define COUPLE 4			// 对牌
#define SANTIAO 5			// 三条
#define THREE_ONE 6			// 三带单
#define THREE_TWO 7			// 三带双
#define SINGLEJUNKO 8		// 单顺
#define DUALJUNKO 9			// 双顺
#define THREEJUNKO 10		// 三顺
#define THREEJUNKO_ONE 11   // 三顺带单
#define THREEJUNKO_TWO 12   // 三顺带双
#define FOUR_TWO 13         // 四带二
#define FOUR_TWO_COUPLE 14  // 四带两对

#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}//获得数组长度

#define STATUS_MAX 1		//  必胜牌
#define STATUS_LARGE 2		//  大牌
#define STATUS_MID 3		//  中等牌
#define STATUS_SMALL 4		//  小牌

// 设置空走步
#define NULL_MOVE(move) \
{ \
	vector<unsigned> list;\
	list.push_back(60);\
	move.cards=list;\
	move.cardsType=-1;\
	move.score=0;\
}

#define max(x, y) {x = x > y ? x : y;}





typedef vector<unsigned> VECTORINT;

typedef struct _cardsmoves
{
	vector<unsigned> cards;
	int cardsType;
	int status;	  // 状态
	int outWay;// 出牌方式
	int score;
}CARDSMOVE;//走步

typedef struct _comb
{
	vector<CARDSMOVE> moves;//一组走步
	int score;
}Comb;

typedef vector<Comb> CombsLib;


#endif //define_h_