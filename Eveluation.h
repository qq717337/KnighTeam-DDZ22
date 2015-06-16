#pragma once
#include "define.h"
#include "Player.h"
#include "DDZPlayer.h"
#include "MoveGenerator.h"
#include "VectorUtil.h"

using namespace std;

class CEveluation
{
public:
	CEveluation();
	~CEveluation();
	void initMembership(Player p);
	void ClearedByDealCards(Player p);
	void ClearedByLeftCards(Player p,vector<unsigned> leftCards);
	void ClearedByPlayCards(Player p,vector<unsigned> playCards);
	void UpdateByPlayCards(Player p,int whoseGo,int cardsType,vector<unsigned> playCards);

	void UpdateFewCards(int whoseGo,Player p);
	void UpdateManyCards(int whoseGo,Player p);
	void RefreshRemaining(Player p,vector<unsigned> list);


	void RandMenu(Player p);// Ëæ»ú²Ëµ¥

	vector<int> ComputeNumOfBasic(int *cards);
	int EveluateMove(Player p,CARDSMOVE* move,int whoseGo);
	void EveluateMoves(Player p, vector<CARDSMOVE> *moves, int whoseGo);

	void EveluateCombs(Player p);
	int getMinIndexOfCombs(CombsLib combs);
	void cutCarryCards(Player p,CARDSMOVE *move);
	void cutCarryCardsMoves(Player p, vector<CARDSMOVE> *moves);

	void cutCarryCards1(Player p,CARDSMOVE *move,
		vector<unsigned> carryCards,int shouldCarryCards_num,int startIndex,int flag);

	vector<unsigned> getMaxElementIndex(int *arr,unsigned len,int top_num);

	void FilterForMoves(vector<CARDSMOVE> *moves,unsigned *cards);

	int IsPlay3Single(vector<CARDSMOVE> moves,Player p,unsigned *cards);
	int IsPlay4Couple(vector<CARDSMOVE> moves,Player p,unsigned *cards);
	int IsPlay5Santiao(vector<CARDSMOVE> moves,Player p,unsigned *cards);

	int IsAiPass(Player p);

	vector<unsigned> haveZhaDanOutside(Player p);
	vector<unsigned> haveZhaDanP2(Player p);
	vector<unsigned> haveZhaDanP1(Player p);


};