#include "ThinkTable.h"
#include "define.h"
#include "vector"
#include "MoveGenerator.h"
#include "DDZMoveManager.h"



CThinkTable::CThinkTable()
{
}


CThinkTable::~CThinkTable()
{
}

///**���ƣ����ط��� */
//int CThinkTable::getBid(Player p)
//{
//	int bid=0;
//	int cardsPoints=0;// �Ƶ�
//	getMyCardsInfo(p);
//	if(p.p3_cardsInfo.n.big==1)
//	{
//		cardsPoints+=6;  // �����Ƶ�+6
//	}
//	if(p.p3_cardsInfo.n.small==1)
//	{
//		cardsPoints+=4;  // С���Ƶ�+4
//	}
//	if(p.p3_cardsInfo.m.num!=0)
//	{
//		cardsPoints+=(2*p.p3_cardsInfo.m.num); // �� 2 �Ƶ�+2*����
//	}
//
//	if(p.p3_cardsInfo.a.num!=0) // ��3
//	{
//		if(p.p3_cardsInfo.a.num==1)
//			cardsPoints-=2;
//		if(p.p3_cardsInfo.a.num==2)
//			cardsPoints-=1;
//		if(p.p3_cardsInfo.a.num==4)
//			cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.b.num!=0)  // ��4
//	{
//		if(p.p3_cardsInfo.b.num==1)
//			cardsPoints-=2;
//		if(p.p3_cardsInfo.b.num==2)
//			cardsPoints-=1;
//		if(p.p3_cardsInfo.b.num==4)
//			cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.c.num!=0)  // ��5
//	{
//		if(p.p3_cardsInfo.c.num==1)
//			cardsPoints-=2;
//		if(p.p3_cardsInfo.c.num==2)
//			cardsPoints-=1;
//		if(p.p3_cardsInfo.c.num==4)
//			cardsPoints+=6;
//	}
//
//	if(p.p3_cardsInfo.d.num!=0)  // ��6
//	{
//		if(p.p3_cardsInfo.d.num==1)
//			cardsPoints-=1;
//		if(p.p3_cardsInfo.d.num==4)
//			cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.e.num!=0)  // ��7
//	{
//		if(p.p3_cardsInfo.e.num==1)
//			cardsPoints-=1;
//		if(p.p3_cardsInfo.e.num==4)
//			cardsPoints+=8;// ������7��ը�������������С˳���ƣ����ҷ��Ʋ�㶼���Խ���
//	}
//	if(p.p3_cardsInfo.f.num!=0)  // ��8
//	{
//		if(p.p3_cardsInfo.f.num==1)
//			cardsPoints-=1;
//		if(p.p3_cardsInfo.f.num==4)
//			cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.g.num!=0)  // ��9
//	{
//		if(p.p3_cardsInfo.g.num==1)
//			cardsPoints-=1;
//		if(p.p3_cardsInfo.g.num==4)
//			cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.h.num!=0)  // ��10
//	{
//		if(p.p3_cardsInfo.h.num==4)
//			cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.i.num!=0)
//	{
//		if(p.p3_cardsInfo.i.num==3)
//			cardsPoints+=1;
//		if(p.p3_cardsInfo.i.num==4)  // ��J
//			cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.j.num!=0)
//	{
//		if(p.p3_cardsInfo.j.num==3)
//				cardsPoints+=1;
//		if(p.p3_cardsInfo.j.num==4)  // ��Q
//				cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.k.num!=0)
//	{
//		if(p.p3_cardsInfo.k.num==3)
//				cardsPoints+=1;
//		if(p.p3_cardsInfo.k.num==4)  // ��K
//				cardsPoints+=6;
//	}
//	if(p.p3_cardsInfo.l.num!=0)
//	{
//		if(p.p3_cardsInfo.l.num==3)
//			cardsPoints+=1;
//		if(p.p3_cardsInfo.l.num==4)  // ��A
//			cardsPoints+=6;
//	}
//		
//
//	if(cardsPoints>=8)
//		bid+=3;                  // ��3��
//	else if(cardsPoints>=4)
//		bid+=2;                  // ��2��
//	else if(cardsPoints>=2)
//		bid+=1;                  // ��1��
//	return bid;
//}


int CThinkTable::getBid(Player p)
{
	int bid = 0;
	unsigned cards[15];
	int cardsNum = 0;
	memcpy(cards, p.p3_EachCardNum, sizeof(cards));
	cardsNum = p.p3_cardsNum;
	CMoveGenerator ddz_MG = CMoveGenerator();
	DDZMoveManager ddz_MM = DDZMoveManager();
	vector<CARDSMOVE> moves = ddz_MG.getMovesByMyself(cardsNum, cards);
	vector<CARDSMOVE> combs =ddz_MM.getCombBySocre(p);
	

	bid =getBidByComb(combs.size());//������ϲ����з�

	int level = getBidByTopCards(cards);

	updateBidByCombsWithTopCards(&bid, &level);

	updateBidByTheirBid(p, &bid);

	int currentBid = getCurrentMaxBid(p);

	if (currentBid < bid) 
	{
		return bid;
	}
	else
	{
		return 0;	//��û��ǰ������߽еķָߣ�������0��
	}
	
}


/**
*  ������ϲ����ʹ��������ı�з�
* @bid       ԭ���з�
* @level    ���Ƽ���
*/
void CThinkTable::updateBidByCombsWithTopCards(int *bid, const int *level)
{
	switch(*bid)
	{
	case 0:
		{
			if( *level ==1)
			{
				*bid=1;
			}

			break;
		}
	case 1:
		{
			if( *level ==1)
			{
				*bid = 2;
			}
			break;
		}
	case 2:
		{
			if( *level == 1)
			{
				*bid = 3;
			}
			break;
		}
	case 3:
		{
			if( *level ==3)
			{
				*bid = 2;
			}
			break;
		}
	}
}

/**
*    ������ϲ����з�
*/
int CThinkTable::getBidByComb(int combsNum)
{
	if(combsNum < 6)
	{
		return 3;
	}
	else if(combsNum < 8)
	{
		return 2;
	}
	else if(combsNum < 10)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
*	ͳ�����д��Ƹ������������ˮƽ
*	�á�һ�㡢��
*/
int CThinkTable::getBidByTopCards(unsigned *cards)
{
	if(cards[14] == 1) // һ������
	{
		if(cards[13] == 1) // һ��С��
		{
			if(cards[12] >0)
			{
				return 1;//��
			}
			else
			{
				return 2;//һ��
			}
		}
		else						// û��С��
		{
			if(cards[12] > 1)
			{
				return 1;
			}
			else if(cards[12] == 1)
			{
				return 2;
			}
			else
			{
				return 3;//��
			}
		}
	}
	else						// û�д���
	{
		if(cards[13] == 1)// һ��С��
		{
			if(cards[12] > 2)
			{
				return 1;
			}
			else if(cards[12] >1)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
		else					// û��С��
		{
			if(cards[12] > 3)
			{
				return 1;
			}
			else if(cards[12] >2)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
}

/**
*	ͳ���ҷ��Ƶ���
*/
int CThinkTable::getBidByCardsPoints(unsigned *cards)
{
	int cardsPoints = 0;// ��¼�Ƶ���
	for (size_t i = 0; i < 13; i++)
	{
		if (cards[i] == 1)
		{
			if (i < 4)
			{
				cardsPoints -= 2;
			}
			else if (i < 8)
			{
				cardsPoints -= 1;
			}
		}
		else if (cards[i] == 2)
		{
			if (i < 3)
			{
				cardsPoints -= 1;
			}
			else if (i > 8 && i < 12)
			{
				cardsPoints += 1;
			}
		}
		else if (cards[i] == 3)
		{
			if (i >= 8)
			{
				cardsPoints += 2;
			}
		}
		else
		{
			cardsPoints += 6;
		}
	}


	return cardsPoints;
}

/*
*	������������ѽ��ƽз�
*/
void CThinkTable::updateBidByTheirBid(Player p, int *bid)
{
	if (p.p1_bid != -1 && p.p2_bid != -1)
	{
		if (p.p1_bid < 2 && p.p2_bid < 2)
		{
			if (*bid != 3)
			{
				*bid += 1;
			}	
		}
	}
}

/** ͳ���ҷ�����3~K��A��2��С��������15����������*/
void CThinkTable::initEachCardNum(Player p)
{
	for(size_t i=0;i<15;i++)
	{
		p.p3_EachCardNum[i]=0;// ��ʼ������������
	}
}

/**  �����ҷ�������p3_EachCardNum
*     @list  ������Ƶ��±�
*     @flag ��ʶ---> 1���� ��0����
*/
void CThinkTable::updateEachCardNum(Player p,vector<unsigned> list, int flag)
{
	if(flag)
	{
		increaseEachCardNum(p, list);
	}
	else
	{
		decreaseEachCardNum(p, list);
	}
}


void CThinkTable::increaseEachCardNum(Player p, vector<unsigned> list)
{
	for(int i=list.size()-1;i>=0;i--)
	{
		if(list[i] == 53)
		{
			p.p3_EachCardNum[14]++;
		}
		else
		{
			int k = list[ i ] / 4;

			p.p3_EachCardNum[ k ]++;
		}
	}
}

void CThinkTable::decreaseEachCardNum(Player p, vector<unsigned> list)
{
	for(int i=list.size()-1;i>=0;i--)
	{
		if(list[i] == 53)
		{
			if(p.p3_EachCardNum[i] != 0)
			{
				p.p3_EachCardNum[14]--;
			}
		}
		else
		{
			int k = list[ i ] / 4;
			if(p.p3_EachCardNum[ k ] !=0)
			{
				p.p3_EachCardNum[ k ]--;
			}
		}
	}
}

/**
*	��õ�ǰ������з�
*/
int CThinkTable::getCurrentMaxBid(Player p)
{
	int maxBid = -1;

	max(maxBid, p.p1_bid);
	max(maxBid, p.p2_bid);
	
	return maxBid;
}



