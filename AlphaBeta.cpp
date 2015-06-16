#include "AlphaBeta.h"
#include "FileWriter.h"
#include "sstream"
#include "DDZMoveManager.h"

AlphaBeta::AlphaBeta(void):score(-99999),currentScore(0)
{
	junkoNum=0;
};

AlphaBeta::~AlphaBeta(void)
{
}

CARDSMOVE AlphaBeta::bestMove;

int AlphaBeta::SearchAGoodMove(Player p,int nDepth)
{
	DDZMoveManager ddz_MM = DDZMoveManager();

	int canPlayOver = 0;
	int current=-99999;
	CMoveGenerator *ddz_MG;
	CEveluation *ddz_Eve;
	ddz_MG = (CMoveGenerator*)malloc(sizeof(CMoveGenerator));
	ddz_Eve = (CEveluation*)malloc(sizeof(CEveluation));

	
	
	vector<CARDSMOVE> moves = ddz_MG->getMoves(p, nDepth);
	//FileWriter fw = FileWriter("m.txt");
	//m_pEve->FilterForMoves(&moves,p.p3_EachCardNum);

	if(moves.size()>0&&moves[0].outWay==1)
	{
		p.p3_allMoves=moves;
	}

	ddz_Eve->RandMenu(p);

	ddz_Eve->EveluateMoves(p, &moves, nDepth);

	ddz_Eve->EveluateMoves(p, &p.p3_allMoves, nDepth);
	
	

	ddz_Eve->cutCarryCardsMoves(p, &moves);
	ddz_Eve->cutCarryCardsMoves(p, &p.p3_allMoves);


	if(moves.size()==0)
	{
		NULL_MOVE(bestMove);	
		return 0;
	}
	

	vector<CARDSMOVE> comb = ddz_MM.getCombBySocre(p);
	ddz_MM.setMovesStatus(p,&comb);

	// 判断是否达到必胜状态
	p.p3_canPlayOver = ddz_MM.canPlayOver(comb);
	if (p.p3_canPlayOver)
	{
		p.p3_comb = comb;
	}

	for (size_t i = 0; i<moves.size(); i++)
	{
		if (i >= 0 && i<moves.size())
		{
			if (nDepth == AlphaBeta_Depth)
			{
				if (current<moves[i].score)
				{
					bestMove = moves[i];
					current = moves[i].score;
				}
			}
		}
	}


	int way = moves[0].outWay;
	if(way)//主动出牌
	{
		// 当到终局时，需特殊处理
		if ((p.p1_IsLandlord && p.p1_cardsNum == 1) || (p.p2_IsLandlord && p.p2_cardsNum == 1)
			|| p.p3_IsLandlord && (p.p1_cardsNum == 1 || p.p2_cardsNum == 1))
		{
			if (moves.size()>0)
			{
				bestMove = moves[moves.size() - 1];
				return 0;
			}
		}
		if (p.p3_canPlayOver)//到达必胜状态
		{
			if (p.p3_comb.size() == 1)
			{
				bestMove = p.p3_comb[0];
				return 0;
			}

			for (size_t i = 0; i < p.p3_comb.size(); i++)
			{
				if (p.p3_comb[i].status == STATUS_MAX)
				{
					bestMove = p.p3_comb[i];
					vector<CARDSMOVE>::iterator it = p.p3_comb.begin() + i;
					p.p3_comb.erase(it);
					return 0;
				}
			}
		}

		int k =ddz_MM.getMaxScoreMove(p.p3_allMoves);
		if (ddz_Eve->IsPlay3Single(moves, p, p.p3_EachCardNum))
		{
				vector<CARDSMOVE> tmp_single;
				vector<CARDSMOVE> single = ddz_MM.getGoodMove3Single(moves,tmp_single,p.p3_EachCardNum,1);
				bestMove=single[0];
				return 0;
		}
		else if (ddz_Eve->IsPlay4Couple(moves, p, p.p3_EachCardNum))
		{
			vector<CARDSMOVE> tmp_couple;
			vector<CARDSMOVE> couple = ddz_MM.getGoodMove4Couple(moves,tmp_couple,p.p3_EachCardNum,1);
			bestMove=couple[0];
			return 0;
		}
		else if (ddz_Eve->IsPlay5Santiao(moves, p, p.p3_EachCardNum))
		{
			vector<CARDSMOVE> tmp;
			vector<CARDSMOVE> single = ddz_MM.getGoodMove3Single(moves, tmp, p.p3_EachCardNum, 1);
			vector<CARDSMOVE> couple = ddz_MM.getGoodMove4Couple(moves, tmp, p.p3_EachCardNum, 1);
			vector<CARDSMOVE> threeJunko = ddz_MM.getGoodMove5Santiao(moves,tmp,p.p3_EachCardNum,1);
			
			bestMove=threeJunko[0];
			if (single.size() > 0)
			{
				bestMove.cards.push_back(single[0].cards[0]);
			}
			else if (couple.size() > 0)
			{
				bestMove.cards.push_back(couple[0].cards[0]);
				bestMove.cards.push_back(couple[0].cards[0]);
			}
			return 0;
		}
		if(k>=0)
			bestMove=p.p3_allMoves[k];
		else
			bestMove=p.p3_allMoves[0];
		return 0;
	}
	else        //被动出牌
	{
		if (p.p3_canPlayOver)
		{
			for (size_t i = 0; i < p.p3_comb.size(); i++)
			{
				for (size_t j = 0; j < moves.size(); j++)
				{
					if (ddz_MM.IsEqualsMove(p.p3_comb[i],moves[j]) 
						&& p.p3_comb[i].status == STATUS_MAX)
					{
						bestMove = p.p3_comb[i];
						vector<CARDSMOVE>::iterator it = p.p3_comb.begin() + i;
						p.p3_comb.erase(it);
						return 0;
					}
					else if (p.p3_comb.size() == 1 
						&& ddz_MM.IsEqualsMove(p.p3_comb[0], moves[j]))
					{
						bestMove = p.p3_comb[0];
						vector<CARDSMOVE>::iterator it = p.p3_comb.begin();
						p.p3_comb.erase(it);
						return 0;
	 				}
				}
				
			}
		}
		if (ddz_Eve->IsAiPass(p))	//让同伴权
		{
			NULL_MOVE(bestMove);
			return 0;
		}

		PassivePlay(moves, p);

		if (!p.p3_canPlayOver &&(bestMove.cardsType == ZHADAN || bestMove.cardsType == ROCKET))
		{
			NULL_MOVE(bestMove);
		}

		return 0;
	}


	//fw.WriteToFile(moves,bestMove);写入文件
	//if(moves.size()==1)
	//{
	//	bestMove.cards.clear();
	//	bestMove.cardsType=-1;
	//}
	delete(ddz_Eve);
	delete(ddz_MG);
	ddz_Eve = NULL;
	ddz_MG = NULL;
	return 0;
}

/** 被动出牌查找走步 */
int AlphaBeta::PassivePlay(vector<CARDSMOVE> moves,Player p)
{
	DDZMoveManager ddz_MM = DDZMoveManager();
	//被动出牌
	int cardsType = moves[0].cardsType;
	switch(cardsType)
	{
	case SINGLE:
		{
			// 当到终局时，需特殊处理
			if((p.p1_IsLandlord && p.p1_cardsNum ==1) || (p.p2_IsLandlord && p.p2_cardsNum==1)
				|| p.p3_IsLandlord  && (p.p1_cardsNum ==1 || p.p2_cardsNum==1))
			{
				if(moves.size()>0)
				{
					bestMove=moves[moves.size()-1];
					return 0;
				}
			}
			vector<CARDSMOVE> single= ddz_MM.getGoodMove3Single(p.p3_allMoves,moves,p.p3_EachCardNum,0);
			if(single.size()==0)
			{
				NULL_MOVE(bestMove);
				return 0;
			}
			if(p.p1_IsLandlord)
			{
				bestMove=single[single.size()-1];
			}
			else
			{
				bestMove=single[0];
			}
			
			break;
		}
	case COUPLE:
		{
			vector<CARDSMOVE> couple= ddz_MM.getGoodMove4Couple(p.p3_allMoves,
					moves,p.p3_EachCardNum,0);
			if(couple.size()==0)
			{
				NULL_MOVE(bestMove);
				return 0;
			}
			if((p.p1_IsLandlord && p.firstPlayer ==1) || p.p1_cardsNum == 2)
			{
				bestMove=couple[couple.size()-1];
			}
			else
			{
				bestMove=couple[0];
			}
			
			break;
		}
	case THREE_ONE:	
		{
			vector<CARDSMOVE> tmp_single;
			vector<CARDSMOVE> single = ddz_MM.getGoodMove3Single(p.p3_allMoves, tmp_single, p.p3_EachCardNum, 1);
			//vector<CARDSMOVE> santiaos = ddz_MM.getGoodMove5Santiao(p.p3_allMoves, tmp_single, p.p3_EachCardNum, 1);
			if(single.size()>0)
			{
				int index = 0;
				while (index < moves.size())
				{
					if (moves[index].cardsType != ZHADAN
						&& p.p3_EachCardNum[moves[index].cards[0]] != 4
						&& moves[index].score>0)
					{
						
						for (int i = moves[index].cards.size() - 1; i > 2; i--)
						{
							vector<unsigned>::iterator it = moves[index].cards.begin();
							moves[index].cards.erase(it + i);
						}
						if (moves[index].cards[0] != single[0].cards[0])
						{
							moves[index].cards.push_back(single[0].cards[0]);
							bestMove = moves[index];
							break;
						}
						else
						{
							index++;
						}
					}
					else
					{
						// 若为炸弹，则不拆
						index++;
					}
				}
			}
			else
				NULL_MOVE(bestMove);
			
			break;
		}
	case THREE_TWO:
		{
			vector<CARDSMOVE> tmp_couple;
			vector<CARDSMOVE> couple= ddz_MM.getGoodMove4Couple(p.p3_allMoves,
				tmp_couple,p.p3_EachCardNum,1);
			if(couple.size()>0)
			{
				int index = 0;
				while (index < moves.size())
				{
					if (moves[index].cardsType != ZHADAN 
						&& p.p3_EachCardNum[moves[index].cards[0]]!= 4)
					{
						for (int i = moves[index].cards.size() - 1; i > 2; i--)
						{
							vector<unsigned>::iterator it = moves[index].cards.begin();
							moves[index].cards.erase(it + i);
						}
						if (moves[index].cards[0] != couple[0].cards[0])
						{
							moves[index].cards.push_back(couple[0].cards[0]);
							moves[index].cards.push_back(couple[0].cards[0]);
							bestMove = moves[index];
							break;
						}
						else
						{
							index++;
						}
							
						
						
					}
					else
					{
						// 若为炸弹，则不拆
						index++;
					}
				}
			}
			else
				NULL_MOVE(bestMove);
			
			break;
		}
	default:
		{
			if (currentScore < 0)
				NULL_MOVE(bestMove);

			break;
		}

	}	

	return 0;
}

int AlphaBeta::someoneLastOne(Player p, vector<CARDSMOVE> moves)
{
	// 当到终局时，需特殊处理
	if ((p.p1_IsLandlord && p.p1_cardsNum == 1) || (p.p2_IsLandlord && p.p2_cardsNum == 1)
		|| p.p3_IsLandlord && (p.p1_cardsNum == 1 || p.p2_cardsNum == 1))
	{
		if (moves.size()>0)
		{
			bestMove = moves[moves.size() - 1];
			return 0;
		}
	}
}

int AlphaBeta::IsFinal(Player p)
{
	if (IsFinal1LastOne(p))
	{
		return 1;
	}
	else if (IsFinal2LastTwo(p))
	{
		return 2;
	}
		
	else if (IsFinal3LastThree(p))
	{
		return 3;
	}
	else
	{
		return 4;
	}
		
}

/*
*   终局其他玩家只剩下一张牌
*/
bool AlphaBeta::IsFinal1LastOne(Player p)
{
	return IsFinalByLastCardsNum(p, 1);
}

/*
*   终局其他玩家只剩下两张牌
*/
bool AlphaBeta::IsFinal2LastTwo(Player p)
{
	return IsFinalByLastCardsNum(p, 2);
}

/*
*   终局其他玩家只剩下三张牌
*/
bool AlphaBeta::IsFinal3LastThree(Player p)
{
	return IsFinalByLastCardsNum(p, 3);
}


bool AlphaBeta::IsFinalByLastCardsNum(Player p, int lastCardsNum)
{
	if ((p.p1_IsLandlord && p.p1_cardsNum == lastCardsNum) || (p.p2_IsLandlord && p.p2_cardsNum == lastCardsNum)
		|| p.p3_IsLandlord && (p.p1_cardsNum == lastCardsNum || p.p2_cardsNum == lastCardsNum))
	{
		return true;
	}

	return false;
}