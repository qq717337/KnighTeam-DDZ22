#pragma once
#include "stdafx.h"
#include "stdafx.h"
#include "define.h"
#include "DDZPlayer.h"
#include "vector"
#include "Player.h"

class CThinkTable
{

public:
	CThinkTable();
	~CThinkTable();
	int getBid(Player p);
	
	void initEachCardNum(Player p);
	void updateEachCardNum(Player p, vector<unsigned> list, int flag);

private:
	void increaseEachCardNum(Player p, vector<unsigned> list);
	void decreaseEachCardNum(Player p, vector<unsigned> list);

	int getBidByComb(int combsNum);
	int getBidByTopCards(unsigned *cards);
	int getBidByCardsPoints(unsigned *cards);
	void updateBidByTheirBid(Player p, int *bid);
	void updateBidByCombsWithTopCards(int *bid, const int *level);
	int getCurrentMaxBid(Player p);
};

