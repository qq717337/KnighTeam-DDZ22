#include "MoveGenerator.h"
#include "FileWriter.h"
#include "string.h"
#include "stdlib.h"
#include "vector"

using namespace std;
CMoveGenerator::CMoveGenerator(void)
{
	lastWhoseGo=0;
}

CMoveGenerator::~CMoveGenerator(void)
{
}

/**
*   �߷���������ڣ���Ϊ�����ͱ�������
*  (1)�ҷ�Ϊ��������������Ҷ���δ����; (2)�������Ҿ�pass;->�������ƣ�����1
*  (1)�ϼ�δpass,���ϼҳ���; (2)�ϼ�pass,�¼�δpass,���¼ҳ���;->�������ƣ�����2
*/
vector<CARDSMOVE> CMoveGenerator::getMoves(Player p,int whoseGo)
{
	vector<CARDSMOVE> p1 =p.p1_general;
	vector<CARDSMOVE> p2 =p.p2_general;
	vector<CARDSMOVE> p3 =p.p3_general;

	vector<CARDSMOVE> moves;
	bool IsCanGo = false;
	int turn =whoseGo%3;														 // �ֵ��ķ����ƣ�����и÷����������������ж�
	unsigned tmp_EachCardNum[15];										 // �����ķ�����������߲�
	int cardsNum;																	 //  �������������
	CARDSMOVE p1_lastMove,p2_lastMove,p3_lastMove;	 //  ����������Ʋ�Ϊ�գ���ȡ�������һ������
	CARDSMOVE lastMove;													 //	 ��ǰ��ҵ��ϼ��ϴγ�������ֵ

	if(turn==0)  // ����ҷ��߲�
	{
		if(p.p3_IsLandlord==true)// �ҷ�Ϊ��������һ�ֳ���
		{
			if(p1.empty()&&p2.empty()&&p3.empty())
			{
				IsCanGo =true;
			}
		}

		if(!p2.empty()&&!p1.empty()) // �ϼ��¼Ҿ�pass,����Ϊ�ҷ���������
		{
			if((p2.at(p2.size()-1)).cardsType==-1 && (p1.at(p1.size()-1)).cardsType==-1)
			{
				IsCanGo = true;
			}
		}
		memcpy(tmp_EachCardNum,p.p3_EachCardNum,sizeof(tmp_EachCardNum));

		if(IsCanGo)
		{
			cardsNum =p.p3_cardsNum;

			NULL_MOVE(p.lastMove);
			p.lastPlayer=-1;
		}
		else 
		{
			if(!p2.empty())
			{
				p2_lastMove = p2.at(p2.size()-1);

				if(p2_lastMove.cardsType!=-1)
				{
					lastMove=p2_lastMove;

					p.lastMove=p2_lastMove;
					p.lastPlayer=2;
				}
				else
				{
					if(!p1.empty())
					{
						p1_lastMove=p1.at(p1.size()-1);

						if(p1_lastMove.cardsType!=-1)
						{
							lastMove=p1_lastMove;

							p.lastMove=p1_lastMove;
							p.lastPlayer=1;
						}
					}
				}
			}
		}
	}
	else if(turn ==2)  //������1�߲�
	{
		if(!p2.empty()&&!p3.empty())// ���1�ж��Ƿ�Ϊ�Լ��������ƣ��������ж����1��2��ʼΪ������������
		{
			if((p2.at(p2.size()-1)).cardsType==-1 && (p3.at(p3.size()-1)).cardsType==-1)
			{
				IsCanGo = true;
			}
		}
		memcpy(tmp_EachCardNum,p.p1_EachCardNum,sizeof(tmp_EachCardNum));

		if(IsCanGo)
		{
			cardsNum =p.p1_cardsNum;

			NULL_MOVE(p.lastMove);
			p.lastPlayer=-1;
		}
		else
		{
			if(!p3.empty())
			{
				p3_lastMove = p3.at(p3.size()-1);

				if(p3_lastMove.cardsType!=-1)
				{
					lastMove=p3_lastMove;

					
					p.lastMove=p3_lastMove;
					p.lastPlayer=3;
				}
				else
				{
					if(!p2.empty())
					{
						p2_lastMove=p2.at(p2.size()-1);

						if(p2_lastMove.cardsType!=-1)
						{
							lastMove=p2_lastMove;
							
							p.lastMove=p2_lastMove;
							p.lastPlayer=2;
						}
					}
				}
			}
		}
	}
	else				//������2�߲�
	{
		if(!p1.empty()&&!p3.empty())// ���2�ж��Ƿ�Ϊ�Լ��������ƣ��������ж����1��2��ʼΪ������������
		{
			if((p1.at(p1.size()-1)).cardsType==-1 && (p3.at(p3.size()-1)).cardsType==-1)
			{
				IsCanGo = true;
			}
		}
		memcpy(tmp_EachCardNum,p.p2_EachCardNum,sizeof(tmp_EachCardNum));

		if(IsCanGo)
		{
			cardsNum =p.p2_cardsNum;

			NULL_MOVE(p.lastMove);
			p.lastPlayer=-1;
		}
		else
		{
			if(!p1.empty())
			{
				p1_lastMove = p1.at(p1.size()-1);

				if(p1_lastMove.cardsType!=-1)
				{
					lastMove=p1_lastMove;

					
					p.lastMove=p1_lastMove;
					p.lastPlayer=1;
				}
				else
				{
					if(!p3.empty())
					{
						p3_lastMove=p3.at(p3.size()-1);

						if(p3_lastMove.cardsType!=-1)
						{
							lastMove=p3_lastMove;

							
							p.lastMove=p1_lastMove;
							p.lastPlayer=1;
						}
					}
				}
			}
		}
	}


	if(IsCanGo)	// ��������
	{		
		vector<CARDSMOVE> tmp_moves =(vector<CARDSMOVE>)getMovesByMyself(cardsNum,tmp_EachCardNum);// ��ȡ�����ƿ��ܵ������߲�
		for(size_t j=0;j<tmp_moves.size();j++)
		{
			moves.push_back(tmp_moves.at(j));
		}

		//VECTORINT method;// ��Ԫ��Ϊ1��2��vector�����߷������ж�Ϊ�������Ǳ����߲�
		//method.push_back(1);// method=>Ϊ1:��������
		//moves.push_back(method);
	}
	else	   // ��������(�����������һ�ֳ����߲�)
	{
		vector<CARDSMOVE> tmp_moves = (vector<CARDSMOVE>) getMovesByOthers(lastMove,tmp_EachCardNum);// ������������ƻ���ҷ����������߲�
		for(size_t j=0;j<tmp_moves.size();j++)
		{
			tmp_moves.at(j).outWay=0;
			moves.push_back(tmp_moves.at(j));
		}

		//VECTORINT method;// ��Ԫ��Ϊ1��2��vector�����߷������ж�Ϊ�������Ǳ����߲�
		//method.push_back(2);// method=>Ϊ2:��������
		//moves.push_back(method);
	}
	
	return moves;
}

/**
*   ����������ҳ��ƻ�ȡ�ҷ������߲�
*  @CardsType ��������  @v ������ϸ���磺3��4��5->4445
*/
vector<CARDSMOVE> CMoveGenerator::getMovesByOthers(CARDSMOVE lastMove,unsigned *cards)
{
	vector<CARDSMOVE> moves;
	vector<CARDSMOVE> tmp_moves;
	DDZPlayer *play;
	play = (DDZPlayer*)malloc(sizeof(DDZPlayer));
	int CardsType = lastMove.cardsType;
	vector<unsigned> v = lastMove.cards;
	switch(CardsType)
	{
		case 1:// ���������ͣ����߲���
			break;

		case 2:// ը��
			{
				unsigned ZhaDanValue = play->getZhaDanValue(v);// ��ȡը��������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByZhaDan(ZhaDanValue,cards);
				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}				
			break;
			}
				
		case 3:// ����
			{
				int SingleCardValue = play->getSingleValue(v);// ��ȡ���Ƶ�����ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesBySingleCard(SingleCardValue,cards);
				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}			
			break;
			}

		case 4:// ����
			{
				int CoupleCardsValue = play->getCoupleValue(v);// ��ȡ���Ƶ�����ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByCoupleCards(CoupleCardsValue,cards);
				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}				
			break;
			}

		case 5:// ����
			{
				int ThreeCardsValue = play->getSanTiaoValue(v);// ��ȡ����������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByThreeTiaoCards(ThreeCardsValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}

		case 6:// ������
			{
				int Three_OneCardsValue = play->getThree_OneValue(v).at(0);// ��ȡ������������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByThree_One(Three_OneCardsValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}

		case 7:// ����˫
			{
				int Three_TwoCardsValue = play->getThree_TwoValue(v).at(0);// ��ȡ����˫������ֵ
				tmp_moves =(vector<CARDSMOVE>)getMovesByThree_Two(Three_TwoCardsValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}

		case 8:// ��˳
			{
				int cardBeginValue = play->getSingleJunkoValue(v).at(0);// ��ȡ��˳��ʼ����ֵ
				int cardEndValue = play->getSingleJunkoValue(v).at(1);	// ��ȡ��˳��������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesBySingleJunko(cardBeginValue,cardEndValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}

		case 9: // ˫˳
			{
				int cardBeginValue = play->getDualJunkoValue(v).at(0);// ��ȡ˫˳��ʼ����ֵ
				int cardEndValue = play->getDualJunkoValue(v).at(1);  // ��ȡ˫˳��������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByDualJunko(cardBeginValue,cardEndValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}

		case 10:// ��˳
			{
				int cardBeginValue = play->getThree_ShunValue(v).at(0);// ��ȡ��˳��ʼ����ֵ
				int cardEndValue = play->getThree_ShunValue(v).at(1);  // ��ȡ��˳��������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByThree_Shun(cardBeginValue,cardEndValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}

		case 11:// ��˳
			{
				int cardBeginValue = play->getThree_OneValue(v).at(0);// ��ȡ��˳������ʼ����ֵ
				int cardEndValue = play->getThree_OneValue(v).at(1);  // ��ȡ��˳������������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByThree_Shun_One(cardBeginValue,cardEndValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}

		case 12: // ��˳��˫
			{
				int cardBeginValue = play->getThree_TwoValue(v).at(0); // ��ȡ��˳��˫��ʼ����ֵ
				int cardEndValue = play->getThree_TwoValue(v).at(1);   // ��ȡ��˳��˫��������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByThree_Shun_Couple(cardBeginValue,cardEndValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}

		case 13:// �Ĵ���
			{
				int Four_TwoCardsValue = play->getFour_TwoValue(v).at(0);	    // ��ȡ�Ĵ�����������ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByFour_Two(Four_TwoCardsValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}
		case 14:// �Ĵ�����
			{
				int Four_TwoCoupleCardsValue = play->getFour_TwoCoupleValue(v).at(0);  // ��ȡ�Ĵ����Ե�����ֵ
				tmp_moves = (vector<CARDSMOVE>)getMovesByFour_TwoCouple(Four_TwoCoupleCardsValue,cards);

				for(size_t i=0;i<tmp_moves.size();i++)
				{
					moves.push_back(tmp_moves.at(i));
				}
				break;
			}
		case -1:
			break;
		}

		if(CardsType!=ZHADAN && CardsType!=ROCKET)// ը���ͻ����һ������
		{
			for(size_t i=0;i<13;i++)
			{
				if(cards[i]==4)
				{
					CARDSMOVE bomb;
					for(size_t k=0;k<4;k++)
					{
						bomb.cards.push_back(i);
					}
					bomb.cardsType=ZHADAN;
					bomb.outWay=0;
					moves.push_back(bomb);
				}
			}

			if(cards[13]==1 && cards[14]==1)
			{
				CARDSMOVE rocket;
				rocket.cards.push_back(13);
				rocket.cards.push_back(14);
				rocket.cardsType=ROCKET;
				rocket.outWay=0;
				moves.push_back(rocket);
			}
		}		
		return moves;
}

/**
*   ��ȡ�������Ƶ������߲�
*/
vector<CARDSMOVE> CMoveGenerator::getMovesByMyself(unsigned cardsNum,unsigned *EachCardNum)
{
	vector<CARDSMOVE> moves;
	for(size_t i=1;i<=cardsNum;i++)// �����ҷ��Ƶ�������1�š���>���������ȡ�����߲�
	{
			vector<CARDSMOVE>  tmp_moves = (vector<CARDSMOVE>) getMovesByCardsNum(i,EachCardNum);
			for(size_t j=0;j<tmp_moves.size();j++)
			{
				tmp_moves.at(j).outWay=1;
				moves.push_back(tmp_moves.at(j));
				
			}
	}

	return moves;
}
/** ��ȡָ�����������߲�*/
/** ��@ n=3 ,���ȡ������Ϊ3�ŵ������߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByCardsNum(unsigned n,unsigned *cards)
{
	vector<CARDSMOVE> tmp_moves;
	switch(n)
	{
	case 1:// ��ȡ������Ϊ1�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByOneCard(cards);
		break;

	case 2:// ��ȡ������Ϊ2�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByTwoCards(cards);
		break;

	case 3:// ��ȡ������Ϊ3�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByThreeCards(cards);
		break;

	case 4:// ��ȡ������Ϊ4�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByFourCards(cards);
		break;

	case 5:// ��ȡ������Ϊ5�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByFiveCards(cards);
		break;

	case 6:// ��ȡ������Ϊ6�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesBySixCards(cards);
		break;

	case 7:// ��ȡ������Ϊ7�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesBySevenCards(cards);
		break;

	case 8:// ��ȡ������Ϊ8�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByEightCards(cards);
		break;

	case 9:// ��ȡ������Ϊ9�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByNineCards(cards);
		break;

	case 10:// ��ȡ������Ϊ10�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByTenCards(cards);
		break;

	case 11:// ��ȡ������Ϊ11�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByElevenCards(cards);
		break;

	case 12:// ��ȡ������Ϊ12�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByTwelveCards(cards);
		break;

	case 13:// ������13�ŵ�����
		
	case 14:// ��ȡ������Ϊ14�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByForteenCards(cards);
		break;
	case 15:// ��ȡ������Ϊ15�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByFifteenCards(cards);
		break;

	case 16:// ��ȡ������Ϊ16�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesBySixteenCards(cards);
		break;

	case 17:// ������17�ŵ�����
	
	case 18:// ��ȡ������Ϊ18�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByEighteenCards(cards);
		break;

	case 19:// ������19�ŵ�����
		break;
	case 20:// ��ȡ������Ϊ20�������߲�
		tmp_moves=(vector<CARDSMOVE>)getMovesByTwentyCards(cards);
		break;
	}

	return tmp_moves;
}


/**��ȡ�ҷ�����Ϊһ�ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByOneCard(unsigned *cards)
{
	vector<CARDSMOVE> OneCard_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<15;i++)
	{
		if(tmp_cards[i]>=1)
		{
			CARDSMOVE tmp_vector;
			tmp_vector.cards.push_back(i);
			tmp_vector.cardsType=3;// ���߲�����׷�����ͣ���������Ϊ3
			OneCard_moves.push_back(tmp_vector);
		}
	}

	return OneCard_moves;
}

/**��ȡ�ҷ�����Ϊ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByTwoCards(unsigned *cards)
{
	vector<CARDSMOVE> TwoCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(tmp_cards[i]>=2)
		{
			CARDSMOVE tmp_vector;
			tmp_vector.cards.push_back(i);
			tmp_vector.cards.push_back(i);
			tmp_vector.cardsType=4;// ���߲�����׷�����ͣ���������Ϊ4
			TwoCards_moves.push_back(tmp_vector);
		}
	}

	if(tmp_cards[13]==1&&tmp_cards[14]==1)
	{
		CARDSMOVE tmp_vector;
		tmp_vector.cards.push_back(13);
		tmp_vector.cards.push_back(14);
		tmp_vector.cardsType=1;// ���߲�����׷�����ͣ��������Ϊ1
		TwoCards_moves.push_back(tmp_vector);
	}

	return TwoCards_moves;
}

/**��ȡ�ҷ�����Ϊ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByThreeCards(unsigned *cards)
{
	vector<CARDSMOVE> ThreeCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(tmp_cards[i]>=3)
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=0;tmp<3;tmp++)
			{
				tmp_vector.cards.push_back(i);
			}
			tmp_vector.cardsType=5;// ���߲�����׷�����ͣ���������Ϊ5
			ThreeCards_moves.push_back(tmp_vector);
		}
	}

	return ThreeCards_moves;
}

/**��ȡ�ҷ�����Ϊ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByFourCards(unsigned *cards)
{
	vector<CARDSMOVE> FourCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(tmp_cards[i]==4)// ը��
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=0;tmp<4;tmp++)
			{
				tmp_vector.cards.push_back(i);
			}
			tmp_vector.cardsType=2;// ���߲�����׷�����ͣ�ը������Ϊ2
			FourCards_moves.push_back(tmp_vector);
		}

		if(tmp_cards[i]>=3)// ����һ
		{
			CARDSMOVE tmp_vector;
			for(size_t k=0;k<3;k++)
			{
				tmp_vector.cards.push_back(i);
			}
			for(size_t j=0;j<15;j++)
			{
				if(tmp_cards[j]>=1&&j!=i) // ���������������ڵ���1�����ͣ���Ϊ����
				{
					tmp_vector.cards.push_back(j);			
				}			
			}
			if(tmp_vector.cards.size()<4)
			{
				continue;
			}
			else
			{
				tmp_vector.cardsType=6;// ���߲�����׷�����ͣ�����������Ϊ6
				FourCards_moves.push_back(tmp_vector);
			}
		}
	}

	return FourCards_moves;
}

/**��ȡ�ҷ�����Ϊ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByFiveCards(unsigned *cards)
{
	vector<CARDSMOVE> FiveCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveSingleJunko(i,5,tmp_cards))// ��i->i+5�ĵ�˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+5;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
			}
			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			FiveCards_moves.push_back(tmp_vector);
		}

		if(tmp_cards[i]>=3)// ����һ��
		{
			CARDSMOVE tmp_vector;
			for(size_t k=0;k<3;k++)
			{
				tmp_vector.cards.push_back(i);
			}
			for(size_t j=0;j<15;j++)
			{
				if(tmp_cards[j]>=2&&j!=i) // ���������������ڵ���1�����ͣ���Ϊ����
				{
					
					tmp_vector.cards.push_back(j);
					tmp_vector.cards.push_back(j);			
				}
			}
			if(tmp_vector.cards.size()<5)
			{
				continue;
			}
			else
			{
				tmp_vector.cardsType=7;// ���߲�����׷�����ͣ�����˫����Ϊ7
				FiveCards_moves.push_back(tmp_vector);
			}
		}
	}

	return FiveCards_moves;
}

/**��ȡ�ҷ�����Ϊ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesBySixCards(unsigned *cards)
{
	vector<CARDSMOVE> SixCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveSingleJunko(i,6,tmp_cards))// ��i->i+6�ĵ�˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+6;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
			}
			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			SixCards_moves.push_back(tmp_vector);
		}

		if(HaveDualJunko(i,3,tmp_cards))// ��i->i+3��˫˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+3;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
				tmp_vector.cards.push_back(tmp);
			}
			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			SixCards_moves.push_back(tmp_vector);
		}

		if (HaveThreeJunko(i, 2, tmp_cards))// ��i->i+2����˳
		{
			CARDSMOVE tmp_vector;
			for (size_t tmp = i; tmp<i + 2; tmp++)
			{
				for (size_t k = 0; k<3; k++)
				{
					tmp_vector.cards.push_back(tmp);
				}
			}

			tmp_vector.cardsType = 10;// ���߲�����׷�����ͣ���˳����Ϊ10
			SixCards_moves.push_back(tmp_vector);
		}
		if(tmp_cards[i]==4)// �Ĵ�����
		{
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if(i1!=i&&tmp_cards[i1]>0)// ��������
				{
					carryCards.push_back(i1);
				}
			}
			if(carryCards.size()<2)
			{
				continue;// ���Ʋ���
			}

			CARDSMOVE tmp_vector;
			for(size_t tmp=0;tmp<4;tmp++)
			{
				tmp_vector.cards.push_back(i);
			}
				
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
			}

			tmp_vector.cardsType=FOUR_TWO;// ���߲�����׷�����ͣ��Ĵ���������Ϊ14
			SixCards_moves.push_back(tmp_vector);
		}
	}

	return SixCards_moves;
}


/**��ȡ�ҷ�����Ϊ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesBySevenCards(unsigned *cards)
{
	vector<CARDSMOVE> SevenCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveSingleJunko(i,7,tmp_cards))// ��i->i+7�ĵ�˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+7;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
			}
			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			SevenCards_moves.push_back(tmp_vector);
		}
	}

	return SevenCards_moves;
}


/**��ȡ�ҷ�����Ϊ���ŵ��߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByEightCards(unsigned *cards)
{
	vector<CARDSMOVE> EightCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveSingleJunko(i,8,tmp_cards))// ��i->i+8�ĵ�˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+8;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
			}
			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			EightCards_moves.push_back(tmp_vector);
		}

		if(HaveDualJunko(i,4,tmp_cards))// ��i->i+4��˫˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+4;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
				tmp_vector.cards.push_back(tmp);
			}
			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			EightCards_moves.push_back(tmp_vector);
		}
		if(HaveThreeJunko(i,2,tmp_cards))// ��i->i+2����˳����
		{
			
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+1)&&tmp_cards[i1]>0)
				{	
					carryCards.push_back(i1);		
				}
			}
			if(carryCards.size()<2)
			{
				continue;// ���Ʋ���
			}
			
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+2;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
			}

			tmp_vector.cardsType=11;// ���߲�����׷�����ͣ���˳��������Ϊ11
			EightCards_moves.push_back(tmp_vector);
			
		}

		if(tmp_cards[i]==4)// �Ĵ�����
		{
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if(i1!=i&&tmp_cards[i1]>1)// ��������
				{
					carryCards.push_back(i1);
				}
			}
			if(carryCards.size()<2)
			{
				continue;// ���Ʋ���
			}

			CARDSMOVE tmp_vector;
			for(size_t tmp=0;tmp<4;tmp++)
			{
				tmp_vector.cards.push_back(i);
			}
				
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
				tmp_vector.cards.push_back(carryCards[m]);
			}

			tmp_vector.cardsType=14;// ���߲�����׷�����ͣ��Ĵ���������Ϊ14
			EightCards_moves.push_back(tmp_vector);
		}
	}
	return EightCards_moves;
}


/**��ȡ�ҷ�����Ϊ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByNineCards(unsigned *cards)
{
	vector<CARDSMOVE> NineCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveSingleJunko(i,9,tmp_cards))// ��i->i+9�ĵ�˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+9;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
			}

			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			NineCards_moves.push_back(tmp_vector);
		}

		if(HaveThreeJunko(i,3,tmp_cards))// ��i->i+3����˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+3;tmp++)
			{
				for(size_t k=0;k<3;k++)
				{
					tmp_vector.cards.push_back(tmp);
				}
			}

			tmp_vector.cardsType=10;// ���߲�����׷�����ͣ���˳����Ϊ10
			NineCards_moves.push_back(tmp_vector);
		}
	}

	return NineCards_moves;
}


/**��ȡ�ҷ�����Ϊʮ�ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByTenCards(unsigned *cards)
{
	vector<CARDSMOVE> TenCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveSingleJunko(i,10,tmp_cards))// ��i->i+10�ĵ�˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+10;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
			}

			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			TenCards_moves.push_back(tmp_vector);
		}

		if(HaveDualJunko(i,5,tmp_cards))// ��i->i+5��˫˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+5;tmp++)
			{
				for(size_t k=0;k<2;k++)
				{
					tmp_vector.cards.push_back(i);
				}
			}

			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			TenCards_moves.push_back(tmp_vector);
		}

		if(HaveThreeJunko(i,2,tmp_cards))// ��i->i+2����˳��˫
		{
			
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+1)&&tmp_cards[i1]>1)// ��������
				{
					carryCards.push_back(i1);
				}
			}

			if(carryCards.size()<2)
			{
				continue;// ���Ʋ���
			}
			
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+2;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
				tmp_vector.cards.push_back(carryCards[m]);
			}
			tmp_vector.cardsType=12;// ���߲�����׷�����ͣ���˳��˫����Ϊ12
			TenCards_moves.push_back(tmp_vector);			
		}
	}

	return TenCards_moves;
}


/**��ȡ�ҷ�����Ϊʮһ�ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByElevenCards(unsigned *cards)
{
	vector<CARDSMOVE> ElevenCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveSingleJunko(i,11,tmp_cards))// ��i->i+11�ĵ�˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+5;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
			}

			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			ElevenCards_moves.push_back(tmp_vector);
		}
	}

	return ElevenCards_moves;
}

/**��ȡ�ҷ�����Ϊʮ���ŵ��߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByTwelveCards(unsigned *cards)
{
	vector<CARDSMOVE> TwelveCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveSingleJunko(i,12,tmp_cards))// ��i->i+12�ĵ�˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+12;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
			}

			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			TwelveCards_moves.push_back(tmp_vector);
		}

		if(HaveDualJunko(i,6,tmp_cards))// ��i->i+6��˫˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+4;tmp++)
			{
				for(size_t k=0;k<2;k++)
				{
				tmp_vector.cards.push_back(tmp);
				}
			}

			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			TwelveCards_moves.push_back(tmp_vector);
		}

		if(HaveThreeJunko(i,4,tmp_cards))// ��i->i+4����˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+4;tmp++)
			{
				for(size_t k=0;k<3;k++)
				{
					tmp_vector.cards.push_back(tmp);
				}
			}

			tmp_vector.cardsType=10;// ���߲�����׷�����ͣ���˳����Ϊ10
			TwelveCards_moves.push_back(tmp_vector);
		}


		if(HaveThreeJunko(i,3,tmp_cards))// ��i->i+3����˳����
		{
			
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+2)&&tmp_cards[i1]>0)
				{	
					carryCards.push_back(i1);		
				}
			}
			if(carryCards.size()<3)
			{
				continue;// ���Ʋ���
			}
			
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+3;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
			}

			tmp_vector.cardsType=11;// ���߲�����׷�����ͣ���˳��������Ϊ11
			TwelveCards_moves.push_back(tmp_vector);
			
		}
	}

	return TwelveCards_moves;
}

/**��ȡ�ҷ�����Ϊʮ���ŵ��߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByForteenCards(unsigned *cards)
{
	vector<CARDSMOVE> ForteenCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveDualJunko(i,7,tmp_cards))// ��i->i+7��˫˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+7;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
				tmp_vector.cards.push_back(tmp);
			}

			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			ForteenCards_moves.push_back(tmp_vector);
		}	

		
	}

	return ForteenCards_moves;
}

/**��ȡ�ҷ�����Ϊʮ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByFifteenCards(unsigned *cards)
{
	vector<CARDSMOVE> FifteenCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveThreeJunko(i,5,tmp_cards))// ��i->i+5����˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+7;tmp++)
			{
				for(size_t k=0;k<3;k++)
				{
				tmp_vector.cards.push_back(tmp);
				}
			}

			tmp_vector.cardsType=10;// ���߲�����׷�����ͣ���˳����Ϊ10
			FifteenCards_moves.push_back(tmp_vector);
		}	

		if(HaveThreeJunko(i,3,tmp_cards))// ��i->i+3����˳��˫
		{
			
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+2)&&tmp_cards[i1]>1)// ��������
				{
					carryCards.push_back(i1);
				}
			}

			if(carryCards.size()<3)
			{
				continue;// ���Ʋ���
			}
			
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+3;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
				tmp_vector.cards.push_back(carryCards[m]);
			}
			tmp_vector.cardsType=12;// ���߲�����׷�����ͣ���˳��˫����Ϊ12
			FifteenCards_moves.push_back(tmp_vector);			
		}
	}

	return FifteenCards_moves;
}

/**��ȡ�ҷ�����Ϊʮ���ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesBySixteenCards(unsigned *cards)
{
	vector<CARDSMOVE> SixteenCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveDualJunko(i,8,tmp_cards))// ��i->i+8��˫˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+8;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
				tmp_vector.cards.push_back(tmp);
			}

			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			SixteenCards_moves.push_back(tmp_vector);
		}	

		if(HaveThreeJunko(i,4,tmp_cards))// ��i->i+4����˳����
		{
			
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+3)&&tmp_cards[i1]>0)
				{	
					carryCards.push_back(i1);		
				}
			}
			if(carryCards.size()<4)
			{
				continue;// ���Ʋ���
			}
			
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+4;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
			}

			tmp_vector.cardsType=11;// ���߲�����׷�����ͣ���˳��������Ϊ11
			SixteenCards_moves.push_back(tmp_vector);
			
		}
	}

	return SixteenCards_moves;
}


/**��ȡ�ҷ�����Ϊʮ���ŵ��߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByEighteenCards(unsigned *cards)
{
	vector<CARDSMOVE> EighteenCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveThreeJunko(i,9,tmp_cards))// ��i->i+9��˫˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+9;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
				tmp_vector.cards.push_back(tmp);
			}

			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			EighteenCards_moves.push_back(tmp_vector);
		}

		if(HaveThreeJunko(i,6,tmp_cards))// ��i->i+6����˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+6;tmp++)
			{
				for(size_t k=0;k<3;k++)
				{
					tmp_vector.cards.push_back(tmp);
				}
			}

			tmp_vector.cardsType=10;// ���߲�����׷�����ͣ���˳����Ϊ10
			EighteenCards_moves.push_back(tmp_vector);
		}	
	}

	return EighteenCards_moves;
}

/**��ȡ�ҷ�����Ϊ��ʮ�ŵ��߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByTwentyCards(unsigned *cards)
{
	vector<CARDSMOVE> TwentyCards_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)// 3-A��2
	{
		if(HaveThreeJunko(i,10,tmp_cards))// ��i->i+10��˫˳
		{
			CARDSMOVE tmp_vector;
			for(size_t tmp=i;tmp<i+9;tmp++)
			{
				tmp_vector.cards.push_back(tmp);
				tmp_vector.cards.push_back(tmp);
			}

			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			TwentyCards_moves.push_back(tmp_vector);
		}

		if(HaveThreeJunko(i,5,tmp_cards))// ��i->i+5����˳����
		{
			
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+4)&&tmp_cards[i1]>0)
				{	
					carryCards.push_back(i1);		
				}
			}
			if(carryCards.size()<5)
			{
				continue;// ���Ʋ���
			}
			
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+5;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
			}

			tmp_vector.cardsType=11;// ���߲�����׷�����ͣ���˳��������Ϊ11
			TwentyCards_moves.push_back(tmp_vector);
			
		}

		if(HaveThreeJunko(i,4,tmp_cards))// ��i->i+4����˳��˫
		{
			
			VECTORINT carryCards;

			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+3)&&tmp_cards[i1]>1)// ��������
				{
					carryCards.push_back(i1);
				}
			}

			if(carryCards.size()<4)
			{
				continue;// ���Ʋ���
			}
			
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+4;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}
			for(size_t m=0;m<carryCards.size();m++)
			{
				tmp_vector.cards.push_back(carryCards[m]);
				tmp_vector.cards.push_back(carryCards[m]);
			}
			tmp_vector.cardsType=12;// ���߲�����׷�����ͣ���˳��˫����Ϊ12
			TwentyCards_moves.push_back(tmp_vector);			
		}
	}

	return TwentyCards_moves;
}

/**		�ж��Ƿ�һ�����д�ָ��λ�õ�ָ�������ĵ�˳			*/
/**   @start ��ʼλ��,��СΪ0 @ JunkoNum ��˳����  @ cards[] ��	*/
bool CMoveGenerator::HaveSingleJunko(unsigned start,unsigned JunkoNum,unsigned *cards)
{
	bool flag = true;

	while(JunkoNum--)
	{
		if(cards[start]<1||start>=12)// ���ܳ�����A
		{
			flag = false;
			break;
		}
		
		start++;
	}

	return flag;
}


/**		�ж��Ƿ�һ�����д�ָ��λ�õ�ָ��������˫˳			*/
/**   @start ��ʼλ��,��СΪ0 @ JunkoNum ˫˳����  @ cards[] ��	*/
bool CMoveGenerator::HaveDualJunko(unsigned start,unsigned JunkoNum,unsigned *cards)
{
	bool flag = true;

	while(JunkoNum--)
	{
		if(cards[start]<2||start>=12)// ���ܳ�����A
		{
			flag = false;
			break;
		}
		
		start++;
	}

	return flag;
}

/**		�ж��Ƿ�һ�����д�ָ��λ�õ�ָ����������˳			*/
/**   @start ��ʼλ��,��СΪ0 @ JunkoNum ��˳����  @ cards[] ��	*/
bool CMoveGenerator::HaveThreeJunko(unsigned start,unsigned JunkoNum,unsigned *cards)
{
	bool flag = true;

	while(JunkoNum--)
	{
		if(cards[start]<3||start>=12)// ���ܳ�����A
		{
			flag = false;
			break;
		}
		
		start++;
	}

	return flag;
}

/**���ݶԷ�ը���������ը���߲� */
vector<CARDSMOVE> CMoveGenerator::getMovesByZhaDan(unsigned ZhaDanValue,unsigned *cards)
{
	vector<CARDSMOVE> ZhaDan_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t j=ZhaDanValue+1;j<13;j++)
	{
		if(tmp_cards[j]==4)
		{
			CARDSMOVE tmp_vector;
			for(size_t i=0;i<4;i++)
			{
				tmp_vector.cards.push_back(j);
			}
			tmp_vector.cardsType=2;// ���߲�����׷�����ͣ�ը������Ϊ2
			ZhaDan_moves.push_back(tmp_vector);
		}	
	}

	if(tmp_cards[13]==1&&tmp_cards[14]==1)
	{
		CARDSMOVE tmp_vector;
		tmp_vector.cards.push_back(13);// С��
		tmp_vector.cards.push_back(14);// ����

		tmp_vector.cardsType=1;// ���߲�����׷�����ͣ��������Ϊ1
		ZhaDan_moves.push_back(tmp_vector);
	}

	return ZhaDan_moves;
}

/** ���ݶԷ����ƻ���ҷ����е����߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesBySingleCard(unsigned SingleCard,unsigned *cards)
{
	vector<CARDSMOVE> SingleCard_moves;
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=SingleCard+1;i<15;i++)
	{
		if(tmp_cards[i]>=1)
		{
			CARDSMOVE tmp_vector;
			tmp_vector.cards.push_back(i);

			tmp_vector.cardsType=3;// ���߲�����׷�����ͣ���������Ϊ3
			SingleCard_moves.push_back(tmp_vector);			
		}
	}
	return SingleCard_moves;
}

/** ���ݶԷ����ƻ���ҷ����ж����߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByCoupleCards(unsigned CoupleCards,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> CoupleCards_moves;
	for(size_t i=CoupleCards+1;i<15;i++)
	{
		if(tmp_cards[i]>=2)
		{
			CARDSMOVE tmp_vector;
			tmp_vector.cards.push_back(i);
			tmp_vector.cards.push_back(i);

			tmp_vector.cardsType=4;// ���߲�����׷�����ͣ���������Ϊ4
			CoupleCards_moves.push_back(tmp_vector);
		}
	}

	return CoupleCards_moves;
}

/** ���ݶԷ���������ҷ����������߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByThreeTiaoCards(unsigned ThreeCards,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> ThreeCards_moves;
	for(size_t i=ThreeCards+1;i<15;i++)
	{
		if(tmp_cards[i]>=3)
		{
			CARDSMOVE tmp_vector;
			for(size_t j=0;j<3;j++)
			{
				tmp_vector.cards.push_back(i);
			}

			tmp_vector.cardsType=5;// ���߲�����׷�����ͣ���������Ϊ5
			ThreeCards_moves.push_back(tmp_vector);
		}
	}

	return ThreeCards_moves;
}

/** ���ݶԷ�����һ����ҷ���������һ�߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByThree_One(unsigned Three_OneCards,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> Three_OneCards_moves;
	for(size_t i=Three_OneCards+1;i<15;i++)
	{
		if(tmp_cards[i]>=3)
		{
			CARDSMOVE tmp_vector;
			for(size_t k=0;k<3;k++)
			{
				tmp_vector.cards.push_back(i);
			}
			for(size_t j=0;j<15;j++)
			{
				if(tmp_cards[j]>=1&&j!=i) // ���������������ڵ���1�����ͣ���Ϊ����
				{
					tmp_vector.cards.push_back(j);	
				}
			}
			tmp_vector.cardsType=6;// ���߲�����׷�����ͣ�����������Ϊ6
			Three_OneCards_moves.push_back(tmp_vector);
		}
	}

	return Three_OneCards_moves;
}

/** ���ݶԷ�����������ҷ������������߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByThree_Two(unsigned Three_TwoCards,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> Three_TwoCards_moves;
	for(size_t i=Three_TwoCards+1;i<15;i++)
	{
		if(tmp_cards[i]>=3)
		{
			CARDSMOVE tmp_vector;
			for(size_t k=0;k<3;k++)
			{
				tmp_vector.cards.push_back(i);
			}
			for(size_t j=0;j<15;j++)
			{
				if(tmp_cards[j]>=2&&j!=i) // ����������������2�����ͣ���Ϊ����
				{
					tmp_vector.cards.push_back(j);	
					tmp_vector.cards.push_back(j);
				}
			}

			tmp_vector.cardsType=7;// ���߲�����׷�����ͣ�����˫����Ϊ7
			Three_TwoCards_moves.push_back(tmp_vector);
		}
	}

	return Three_TwoCards_moves;
}

/** ���ݶԷ���˳����ҷ����е�˳�߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesBySingleJunko(unsigned cardBeginValue,unsigned cardEndValue,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> SingleJunko_moves;
	unsigned JunkoNum = cardEndValue-cardBeginValue+1;// ��˳������

	for(size_t i=cardBeginValue+1;i+JunkoNum<=11;i++) // ��˳ֻ�ܿ�ʼ�����Ϊ10,�Ҵӵ�˳��ʼ���ϵ�˳�������ô�����A(11)
	{
		bool flag = true;
		for(size_t j=i;j<i+JunkoNum;j++)
		{
			if(tmp_cards[j]==0)
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+JunkoNum;k++)
			{
				tmp_vector.cards.push_back(k);
			}

			tmp_vector.cardsType=8;// ���߲�����׷�����ͣ���˳����Ϊ8
			SingleJunko_moves.push_back(tmp_vector);
		}
	}


	return SingleJunko_moves;
}

/** ���ݶԷ�˫˳����ҷ�����˫˳�߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByDualJunko(unsigned cardBeginValue,unsigned cardEndValue,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> DualJunko_moves;
	unsigned JunkoNum = cardEndValue-cardBeginValue+1;// ˫˳�ƶ���
	//vector<bool> tmp_vector3;

	for(int i=cardBeginValue+1;i+JunkoNum<=11;i++)// ˫˳���Ϊ12( Q )���Ҵ�˫˳��ʼ����˫˳�������ô�����A(11)
	{
		bool flag = true;
		for(size_t j=i;j<i+JunkoNum;j++)
		{
			if(tmp_cards[j]<2)
			{
				flag = false;
				break;
			}
		}
		//tmp_vector3.push_back(flag);

		if(flag)
		{
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+JunkoNum;k++)
			{
				for(size_t tmp=0;tmp<2;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}

			tmp_vector.cardsType=9;// ���߲�����׷�����ͣ�˫˳����Ϊ9
			DualJunko_moves.push_back(tmp_vector);
		}
	}


	return DualJunko_moves;
}

/** ���ݶԷ���˳����ҷ�������˳�߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByThree_Shun(unsigned cardBeginValue,unsigned cardEndValue,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> Three_Shun_moves;
	int JunkoNum = cardEndValue-cardBeginValue+1;// ��˳�Ƹ���

	for(int i=cardBeginValue+1;i+JunkoNum<=11;i++)// ��˳��ʼ���Ϊ13��K���磺KKKAAA
	{
		bool flag = true;
		for(size_t j=i;j<i+JunkoNum;j++)
		{
			if(tmp_cards[j]<3)
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{
			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+JunkoNum;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}

			tmp_vector.cardsType=10;// ���߲�����׷�����ͣ���˳����Ϊ10
			Three_Shun_moves.push_back(tmp_vector);
		}
	}


	return Three_Shun_moves;
}

/** ���ݶԷ���˳��������ҷ�������˳�����߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByThree_Shun_One(unsigned cardBeginValue,unsigned cardEndValue,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> Three_Shun_One_moves;
	unsigned JunkoNum = cardEndValue-cardBeginValue+1;// ��˳�����Ƹ���

	for(size_t i=cardBeginValue+1;i+JunkoNum<=11;i++)// ��˳������ʼ���Ϊ13��K���磺KKKAAA34
	{
		bool flag = true;
		for(size_t j=i;j<i+JunkoNum;j++)
		{
			if(tmp_cards[j]<3)
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{ 
			
			VECTORINT carryCards;// �ɴ��ƴ洢

			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+JunkoNum-1)&&tmp_cards[i1]>0)
				{
					carryCards.push_back(i1);		
				}
			}

			if(carryCards.size()<JunkoNum)
			{
				continue;// ���Ʋ���
			}

			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+JunkoNum;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}

			for(size_t k=0;k<carryCards.size();k++)
			{
				tmp_vector.cards.push_back(carryCards[k]);
			}
			

			tmp_vector.cardsType=11;// ���߲�����׷�����ͣ���˳��������Ϊ11
			Three_Shun_One_moves.push_back(tmp_vector);
		}
	}

	return Three_Shun_One_moves;
}


/**����㷨����ָ���ƽ���������� */
vector<unsigned> CMoveGenerator::combinateCards(vector<unsigned> tmp)
{
	for(size_t i=0;i<tmp.size();i++)
	{
		if(tmp.at(i)==0)
		{
			if(i>0)
			{
				if(tmp.at(i-1)==1)
				{
					tmp.at(i)=1;
					tmp.at(i-1)=0;
					int b=0;
					for(size_t j=0;j<i-1;j++)
					{	
						if(tmp.at(j)==1)
						{
							if(tmp.at(b)==0)
							{
								tmp.at(b)=1;
								b++;
								tmp.at(j)=0;
							}
							else
							{
								b++;
							}
						}
					}
					break;
				}
			}
		}
	}

	return tmp;
}

/** ���ݶԷ���˳��˫����ҷ�������˳��˫�߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByThree_Shun_Couple(unsigned cardBeginValue,unsigned cardEndValue,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> Three_Shun_Couple_moves;
	unsigned JunkoNum = cardEndValue-cardBeginValue+1;// ��˳�Ƹ���

	for(int i=cardBeginValue+1;i<=10&&i+JunkoNum<=12;i++)// ��˳��ʼ���Ϊ13��K���磺KKKAAA3344
	{
		bool flag = true;
		for(size_t j=i;j<i+JunkoNum;j++)
		{
			if(tmp_cards[j]<3)
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{	
			VECTORINT carryCards;// �ɴ��ƴ洢
			
			for(size_t i1=0;i1<15;i1++)
			{
				if((i1<i||i1>i+JunkoNum-1)&&tmp_cards[i1]>1)
				{
					carryCards.push_back(i1);
				}
			}

			if(carryCards.size()<JunkoNum)
			{
				continue;// ���Ʋ���
			}

			CARDSMOVE tmp_vector;
			for(size_t k=i;k<i+JunkoNum;k++)
			{
				for(size_t tmp=0;tmp<3;tmp++)
				{
					tmp_vector.cards.push_back(k);
				}
			}
			for(size_t k=0;k<carryCards.size();k++)
			{
				tmp_vector.cards.push_back(carryCards[k]);
				tmp_vector.cards.push_back(carryCards[k]);
			}

			tmp_vector.cardsType=12;// ���߲�����׷�����ͣ���˳��˫����Ϊ12
			Three_Shun_Couple_moves.push_back(tmp_vector);
			}
	}


	return Three_Shun_Couple_moves;
}

/** ���ݶԷ��Ĵ���������ҷ������Ĵ������߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByFour_Two(unsigned Four_TwoCards,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> Four_Two_moves;
	for(size_t i=Four_TwoCards+1;i<13;i++)
	{
		if(tmp_cards[i]==4)
		{
			VECTORINT carryCards;// �ɴ��ƴ洢


			for(size_t i1=0;i1<15;i1++)
			{
				if(i1!=i&&tmp_cards[i1]>0)// ���Ƽ�����
				{
					for(size_t tmp=0;tmp<tmp_cards[i1];tmp++)
					{
						carryCards.push_back(i1);
					}
				}
			}

			if(carryCards.size()<2)
			{
				continue;// ���Ʋ���
			}

			CARDSMOVE tmp_vector;
			for(size_t tmp=0;tmp<4;tmp++)
			{
				tmp_vector.cards.push_back(i);
			}

			for(size_t k=0;k<carryCards.size();k++)
			{
				tmp_vector.cards.push_back(carryCards[k]);
			}

			tmp_vector.cardsType=13;// ���߲�����׷�����ͣ��Ĵ���������Ϊ13
			Four_Two_moves.push_back(tmp_vector);		
		}
	}

	return Four_Two_moves;
}

/** ���ݶԷ��Ĵ���˫����ҷ������Ĵ���˫�߲�*/
vector<CARDSMOVE> CMoveGenerator::getMovesByFour_TwoCouple(unsigned Four_TwoCoupleCards,unsigned *cards)
{
	unsigned tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));
	vector<CARDSMOVE> Four_TwoCouple_moves;
	for(size_t i=Four_TwoCoupleCards+1;i<15;i++)
	{
		if(tmp_cards[i]==4)
		{
			VECTORINT carryCards;// �ɴ��ƴ洢

			for(size_t i1=0;i1<15;i1++)
			{
				if(i1!=i&&tmp_cards[i1]>1)
				{
					carryCards.push_back(i1);
				}
			}

			if(carryCards.size()<2)
			{
				continue;// ���Ʋ���
			}
		
			CARDSMOVE tmp_vector;
			for(size_t tmp=0;tmp<4;tmp++)
			{
				tmp_vector.cards.push_back(i);
			}
						
			for(size_t k=0;k<carryCards.size();k++)
			{
				tmp_vector.cards.push_back(carryCards[k]);
				tmp_vector.cards.push_back(carryCards[k]);
			}

			tmp_vector.cardsType=14;// ���߲�����׷�����ͣ��Ĵ���˫����Ϊ14
			Four_TwoCouple_moves.push_back(tmp_vector);
		}
	}
	return Four_TwoCouple_moves;
}


//MOVES CMoveGenerator::getBasicMovesByMyself(Player p,int basicIndex)
//{
//	MOVES moves =getMovesByMyself(p.p3_cardsList.size(),p.p3_EachCardNum);
//	MOVES singleOrSingleJunko;
//	MOVES coupleOrDualJunko;
//	MOVES threeOrThreeJunko;
//
//	for(size_t i=0;i<moves.size();i++)
//	{
//		vector<int> tmp_move=moves.at(i);
//
//		if(tmp_move.at(tmp_move.size()-1)==3||tmp_move.at(tmp_move.size()-1)==8)
//		{
//			singleOrSingleJunko.push_back(tmp_move);
//		}
//		else if(tmp_move.at(tmp_move.size()-1)==4||tmp_move.at(tmp_move.size()-1)==9)
//		{
//			coupleOrDualJunko.push_back(tmp_move);
//		}
//		else if(tmp_move.at(tmp_move.size()-1)==5||tmp_move.at(tmp_move.size()-1)==6||tmp_move.at(tmp_move.size()-1)==7||tmp_move.at(tmp_move.size()-1)==11||tmp_move.at(tmp_move.size()-1)==12)
//		{
//			threeOrThreeJunko.push_back(tmp_move);
//		}
//	}
//
//	if(basicIndex ==1)
//	{
//		return singleOrSingleJunko;
//	}
//	else if(basicIndex ==2)
//	{
//		return coupleOrDualJunko;
//	}
//	else
//	{
//		return threeOrThreeJunko;
//	}
//}

/**
*	�����߲��ܷ���ϣ���һ���߲��ܷ�����һ���߲���
*	@m1 һ���߲�
*  @m2 �ܷ����m1���߲�
*
*/
bool CMoveGenerator::IsValidMove(CARDSMOVE m1,CARDSMOVE m2)
{
	DDZPlayer* play;
	play=(DDZPlayer*)malloc(sizeof(DDZPlayer));

	int cardsType1 = m1.cardsType;
	int cardsType2 = m2.cardsType;

	vector<unsigned> cards1 = m1.cards;
	vector<unsigned> cards2 = m2.cards;

	if(cardsType1==cardsType2)
	{
		switch(cardsType1)
		{
		case INVALID:
			{
				return false;
				break;
			}
		case ROCKET:
			{
				return false;
			break;
			}
		case ZHADAN:
			{
				unsigned zhaDanValue1 =play->getZhaDanValue(cards1);
				unsigned zhaDanValue2 =play->getZhaDanValue(cards2);

				if(zhaDanValue1<zhaDanValue2)
				{
					return true;
				}
				else
				{
					return false;
				}
			break;
			}
		case SINGLE:
			{
				unsigned singleValue1 =play->getSingleValue(cards1);
				unsigned singleValue2 =play->getSingleValue(cards2);

				if(singleValue1<singleValue2)
				{
					return true;
				}
				else
				{
					return false;
				}
			break;
			}
		
		case COUPLE:
			{
				unsigned coupleValue1 =play->getCoupleValue(cards1);
				unsigned coupleValue2 =play->getCoupleValue(cards2);

				if(coupleValue1<coupleValue2)
				{
					return true;
				}
				else
				{
					return false;
				}
			break;
			} 
	
		case SANTIAO:
			{
				unsigned threeValue1 =play->getSanTiaoValue(cards1);
				unsigned threeValue2 =play->getSanTiaoValue(cards2);

				if(threeValue1<threeValue2)
				{
					return true;
				}
				else
				{
					return false;
				}
			break;
			}
	
		case SINGLEJUNKO:
			{
					vector<unsigned> cardsInfo1=play->getSingleJunkoValue(cards1);
					vector<unsigned> cardsInfo2=play->getSingleJunkoValue(cards2);
					
					return IsValidJunkoMove(cardsInfo1,cardsInfo2);
				break;
				}
		
		case DUALJUNKO:
			{
					vector<unsigned> cardsInfo1=play->getDualJunkoValue(cards1);
					vector<unsigned> cardsInfo2=play->getDualJunkoValue(cards2);
					
					return IsValidJunkoMove(cardsInfo1,cardsInfo2);
				break;
				}
		
		case THREEJUNKO:
			{
					vector<unsigned> cardsInfo1=play->getThree_ShunValue(cards1);
					vector<unsigned> cardsInfo2=play->getThree_ShunValue(cards2);

					return IsValidJunkoMove(cardsInfo1,cardsInfo2);
				break;
				}

		case THREEJUNKO_ONE:
			{
					vector<unsigned> cardsInfo1=play->getThree_OneValue(cards1);
					vector<unsigned> cardsInfo2=play->getThree_OneValue(cards2);
					
					return IsValidJunkoMove(cardsInfo1,cardsInfo2);
					break;
					}
		case THREEJUNKO_TWO:
			{
				vector<unsigned> cardsInfo1=play->getThree_TwoValue(cards1);
				vector<unsigned> cardsInfo2=play->getThree_TwoValue(cards2);

				return IsValidJunkoMove(cardsInfo1,cardsInfo2);
				break;
			}
		case FOUR_TWO:
			{
				vector<unsigned> cardsInfo1 = play->getFour_TwoValue(cards1);
				vector<unsigned> cardsInfo2= play->getFour_TwoValue(cards2);

				unsigned fourValue1=cardsInfo1.at(0);
				unsigned fourValue2=cardsInfo2.at(0);

				if(fourValue1<fourValue2)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			}

		case FOUR_TWO_COUPLE:
			{
				vector<unsigned> cardsInfo1 = play->getFour_TwoCoupleValue(cards1);
				vector<unsigned> cardsInfo2= play->getFour_TwoCoupleValue(cards2);

				unsigned fourValue1=cardsInfo1.at(0);
				unsigned fourValue2=cardsInfo2.at(0);

				if(fourValue1<fourValue2)
				{
					return true;
				}
				else
				{
					return false;
				}

				break;
			}

		default:
			return false;

		}
	}

	if(cardsType1!=2&&cardsType1!=1&&(cardsType2==2||cardsType2==1))
	{
		return true;
	}

	return false;
}

bool CMoveGenerator::IsValidJunkoMove(vector<unsigned> cardsInfo1,vector<unsigned> cardsInfo2)
{
	unsigned startValue1 = cardsInfo1[0];
	unsigned endValue1 = cardsInfo1[1];

	unsigned startValue2 = cardsInfo2[0];
	unsigned endValue2 = cardsInfo2[1];

	unsigned junkoNum1 = endValue1-startValue1+1;
	unsigned junkoNum2 = endValue2-startValue2+1;

	if(junkoNum1!=junkoNum2)
	{
			return false;
	}
	else if(startValue1>startValue2)
	{
			return false;
	}
	else
	{
		return true;
	}
}


/**
*	��Ͽ����
*   ���������ȼ��������
*	Ŀǰ���� 8 �����
*/
void CMoveGenerator::PriorityCombinatoriaLibrary(Player p)
{

	CombsLib combs;
	int len;
	initP3_IsExistCardsType(p);
	vector<CARDSMOVE> p3_moves = p.p3_allMoves;
	int cardsNum=p.p3_cardsNum;
	unsigned tmp_EachCardsNum[15];
	memcpy(tmp_EachCardsNum,p.p3_EachCardNum,sizeof(tmp_EachCardsNum));

	vector<unsigned> v_cardsTypes;
		#pragma region  ���1
	v_cardsTypes.push_back(ROCKET); 
	v_cardsTypes.push_back(ZHADAN); 
	v_cardsTypes.push_back(THREEJUNKO_ONE); 
	v_cardsTypes.push_back(THREEJUNKO_TWO); 
	v_cardsTypes.push_back(DUALJUNKO); 
	v_cardsTypes.push_back(SINGLEJUNKO); 
	v_cardsTypes.push_back(THREE_ONE); 
	v_cardsTypes.push_back(THREE_TWO); 
	v_cardsTypes.push_back(THREEJUNKO); 
	v_cardsTypes.push_back(SANTIAO); 
	v_cardsTypes.push_back(COUPLE); 
	v_cardsTypes.push_back(SINGLE); 
	v_cardsTypes.push_back(FOUR_TWO); 
	v_cardsTypes.push_back(FOUR_TWO_COUPLE); 
	combs.push_back(comb(p,v_cardsTypes));
	v_cardsTypes.clear();
	p.p3_cardsNum=cardsNum;
	p.p3_allMoves=p3_moves;
	memcpy(p.p3_EachCardNum,tmp_EachCardsNum,sizeof(p.p3_EachCardNum));
	#pragma endregion

		#pragma region  ���2
	v_cardsTypes.push_back(ROCKET); 
	v_cardsTypes.push_back(ZHADAN); 
	v_cardsTypes.push_back(THREEJUNKO_TWO); 
	v_cardsTypes.push_back(THREEJUNKO_ONE); 
	v_cardsTypes.push_back(DUALJUNKO); 
	v_cardsTypes.push_back(SINGLEJUNKO); 
	v_cardsTypes.push_back(THREE_ONE); 
	v_cardsTypes.push_back(THREE_TWO); 
	v_cardsTypes.push_back(THREEJUNKO); 
	v_cardsTypes.push_back(SANTIAO); 
	v_cardsTypes.push_back(COUPLE); 
	v_cardsTypes.push_back(SINGLE); 
	v_cardsTypes.push_back(FOUR_TWO); 
	v_cardsTypes.push_back(FOUR_TWO_COUPLE); 
	combs.push_back(comb(p,v_cardsTypes));
	v_cardsTypes.clear();
	p.p3_cardsNum=cardsNum;
	p.p3_allMoves=p3_moves;
	memcpy(p.p3_EachCardNum,tmp_EachCardsNum,sizeof(p.p3_EachCardNum));
	#pragma endregion

		#pragma region ���3
	v_cardsTypes.push_back(ROCKET); 
	v_cardsTypes.push_back(ZHADAN); 
	v_cardsTypes.push_back(SINGLEJUNKO); 
	v_cardsTypes.push_back(THREEJUNKO_ONE); 
	v_cardsTypes.push_back(THREEJUNKO_TWO); 
	v_cardsTypes.push_back(DUALJUNKO); 
	v_cardsTypes.push_back(THREE_ONE); 
	v_cardsTypes.push_back(THREE_TWO); 
	v_cardsTypes.push_back(THREEJUNKO); 
	v_cardsTypes.push_back(SANTIAO); 
	v_cardsTypes.push_back(COUPLE); 
	v_cardsTypes.push_back(SINGLE); 
	v_cardsTypes.push_back(FOUR_TWO); 
	v_cardsTypes.push_back(FOUR_TWO_COUPLE); 
	combs.push_back(comb(p,v_cardsTypes));
	v_cardsTypes.clear();
	p.p3_cardsNum=cardsNum;
	p.p3_allMoves=p3_moves;
	memcpy(p.p3_EachCardNum,tmp_EachCardsNum,sizeof(p.p3_EachCardNum));
	#pragma endregion

		#pragma region ���4
	v_cardsTypes.push_back(ROCKET); 
	v_cardsTypes.push_back(ZHADAN); 
	v_cardsTypes.push_back(DUALJUNKO); 
	v_cardsTypes.push_back(SINGLEJUNKO); 
	v_cardsTypes.push_back(THREEJUNKO_TWO); 
	v_cardsTypes.push_back(THREEJUNKO_ONE); 
	v_cardsTypes.push_back(THREE_ONE); 
	v_cardsTypes.push_back(THREE_TWO); 
	v_cardsTypes.push_back(THREEJUNKO); 
	v_cardsTypes.push_back(SANTIAO); 
	v_cardsTypes.push_back(COUPLE); 
	v_cardsTypes.push_back(SINGLE); 
	v_cardsTypes.push_back(FOUR_TWO); 
	v_cardsTypes.push_back(FOUR_TWO_COUPLE); 
	combs.push_back(comb(p,v_cardsTypes));
	v_cardsTypes.clear();
	p.p3_cardsNum=cardsNum;
	p.p3_allMoves=p3_moves;
	memcpy(p.p3_EachCardNum,tmp_EachCardsNum,sizeof(p.p3_EachCardNum));
	#pragma endregion

		#pragma region ���5
	v_cardsTypes.push_back(ROCKET); 
	v_cardsTypes.push_back(ZHADAN); 
	v_cardsTypes.push_back(THREEJUNKO_ONE); 
	v_cardsTypes.push_back(THREEJUNKO_TWO); 
	v_cardsTypes.push_back(THREE_ONE); 
	v_cardsTypes.push_back(THREE_TWO); 
	v_cardsTypes.push_back(DUALJUNKO); 
	v_cardsTypes.push_back(SINGLEJUNKO);
	v_cardsTypes.push_back(THREEJUNKO); 
	v_cardsTypes.push_back(SANTIAO); 
	v_cardsTypes.push_back(FOUR_TWO); 
	v_cardsTypes.push_back(FOUR_TWO_COUPLE); 
	v_cardsTypes.push_back(COUPLE); 
	v_cardsTypes.push_back(SINGLE); 
	
	combs.push_back(comb(p,v_cardsTypes));
	v_cardsTypes.clear();
	p.p3_cardsNum=cardsNum;
	p.p3_allMoves=p3_moves;
	memcpy(p.p3_EachCardNum,tmp_EachCardsNum,sizeof(p.p3_EachCardNum));
	#pragma endregion

		#pragma region ���6
	v_cardsTypes.push_back(ROCKET); 
	v_cardsTypes.push_back(ZHADAN); 
	v_cardsTypes.push_back(THREEJUNKO_TWO); 
	v_cardsTypes.push_back(THREEJUNKO_ONE); 
	v_cardsTypes.push_back(DUALJUNKO); 
	v_cardsTypes.push_back(SINGLEJUNKO); 
	v_cardsTypes.push_back(THREE_ONE); 
	v_cardsTypes.push_back(THREE_TWO); 
	v_cardsTypes.push_back(THREEJUNKO); 
	v_cardsTypes.push_back(SANTIAO); 
	v_cardsTypes.push_back(COUPLE); 
	v_cardsTypes.push_back(SINGLE); 
	v_cardsTypes.push_back(FOUR_TWO); 
	v_cardsTypes.push_back(FOUR_TWO_COUPLE); 
	combs.push_back(comb(p,v_cardsTypes));
	v_cardsTypes.clear();
	p.p3_cardsNum=cardsNum;
	p.p3_allMoves=p3_moves;
	memcpy(p.p3_EachCardNum,tmp_EachCardsNum,sizeof(p.p3_EachCardNum));
	#pragma endregion

		#pragma region ���7
	v_cardsTypes.push_back(ROCKET); 
	v_cardsTypes.push_back(FOUR_TWO); 
	v_cardsTypes.push_back(ZHADAN); 
	v_cardsTypes.push_back(THREEJUNKO_ONE);
	v_cardsTypes.push_back(THREE_ONE);
	v_cardsTypes.push_back(SINGLEJUNKO);
	v_cardsTypes.push_back(THREEJUNKO_TWO); 
	v_cardsTypes.push_back(THREEJUNKO); 
	 v_cardsTypes.push_back(THREE_TWO); 
	v_cardsTypes.push_back(DUALJUNKO); 
	v_cardsTypes.push_back(SANTIAO); 
	v_cardsTypes.push_back(COUPLE); 
	v_cardsTypes.push_back(SINGLE); 
	v_cardsTypes.push_back(FOUR_TWO_COUPLE); 
	combs.push_back(comb(p,v_cardsTypes));
	v_cardsTypes.clear();
	p.p3_cardsNum=cardsNum;
	p.p3_allMoves=p3_moves;
	memcpy(p.p3_EachCardNum,tmp_EachCardsNum,sizeof(p.p3_EachCardNum));
	#pragma endregion

		#pragma region ���8
	v_cardsTypes.push_back(ROCKET); 
	v_cardsTypes.push_back(ZHADAN); 
	v_cardsTypes.push_back(THREEJUNKO_ONE); 
	v_cardsTypes.push_back(THREEJUNKO_TWO); 
	v_cardsTypes.push_back(THREE_TWO); 
	v_cardsTypes.push_back(THREE_ONE); 
	v_cardsTypes.push_back(DUALJUNKO); 
	v_cardsTypes.push_back(SINGLEJUNKO);
	v_cardsTypes.push_back(THREEJUNKO); 
	v_cardsTypes.push_back(SANTIAO); 
	v_cardsTypes.push_back(FOUR_TWO); 
	v_cardsTypes.push_back(FOUR_TWO_COUPLE); 
	v_cardsTypes.push_back(COUPLE); 
	v_cardsTypes.push_back(SINGLE); 
	
	combs.push_back(comb(p,v_cardsTypes));
	v_cardsTypes.clear();
	p.p3_cardsNum=cardsNum;
	p.p3_allMoves=p3_moves;
	memcpy(p.p3_EachCardNum,tmp_EachCardsNum,sizeof(p.p3_EachCardNum));
	#pragma endregion
	


	FileWriter fw = FileWriter("comb.txt");
	fw.CombsToFile(combs);

	p.p3_combs.clear();
	p.p3_combs=combs;
}

/**
*	����һ���������ȼ����л��һ�����
*   @v_cardsTypes  �������ȼ�����
*/
Comb CMoveGenerator::comb(Player p,vector<unsigned> v_cardsTypes)
{
	Comb comb;
	
	for(int i=0;i<v_cardsTypes.size();i++)
	{
		if(p.p3_IsExistCardsType[v_cardsTypes.at(i)-1])
		{
			combByCardsType(p,&comb,v_cardsTypes.at(i));
		}
	}
	
	return comb;
}

/**
*	��ָ�����ͻ�ȡ�߲���ָ�����������߲�
*   @cardsType ָ������
*/
void CMoveGenerator::combByCardsType(Player p,Comb *comb,int cardsType)
{
	for(int i=p.p3_allMoves.size()-1;i>=0;i--)
	{
		if(i>=0&&i<p.p3_allMoves.size()&&p.p3_allMoves.at(i).cardsType==cardsType)
		{
			comb->moves.push_back(p.p3_allMoves[i]);
			for(size_t j=0;j<p.p3_allMoves[i].cards.size();j++)
			{
				p.p3_EachCardNum[p.p3_allMoves[i].cards[j]]--;
			}
			p.p3_cardsNum-=p.p3_allMoves[i].cards.size();
			p.p3_allMoves=getMovesByMyself(p.p3_cardsNum,p.p3_EachCardNum);
			if(p.p3_allMoves.size()>0&&cardsType!=ROCKET)
			{
				i=p.p3_allMoves.size();
				continue;
			}
		}
	}
}

void CMoveGenerator::initP3_IsExistCardsType(Player p)
{
	vector<CARDSMOVE> moves = p.p3_allMoves;

	for(size_t i=0;i<moves.size();i++)
	{
		if(moves.at(i).cardsType==ROCKET)
		{
			p.p3_IsExistCardsType[ROCKET-1]=1;
		}
		else if(moves.at(i).cardsType==ZHADAN)
		{
			p.p3_IsExistCardsType[ZHADAN-1]=1;
		}
		else if(moves.at(i).cardsType==SINGLE)
		{
			p.p3_IsExistCardsType[SINGLE-1]=1;
		}
		else if(moves.at(i).cardsType==COUPLE)
		{
			p.p3_IsExistCardsType[COUPLE-1]=1;
		}
		else if(moves.at(i).cardsType==SANTIAO)
		{
			p.p3_IsExistCardsType[SANTIAO-1]=1;
		}
		else if(moves.at(i).cardsType==THREE_ONE)
		{
			p.p3_IsExistCardsType[THREE_ONE-1]=1;
		}
		else if(moves.at(i).cardsType==THREE_TWO)
		{
			p.p3_IsExistCardsType[THREE_TWO-1]=1;
		}
		else if(moves.at(i).cardsType==SINGLEJUNKO)
		{
			p.p3_IsExistCardsType[SINGLEJUNKO-1]=1;
		}
		else if(moves.at(i).cardsType==DUALJUNKO)
		{
			p.p3_IsExistCardsType[DUALJUNKO-1]=1;
		}
		else if(moves.at(i).cardsType==THREEJUNKO)
		{
			p.p3_IsExistCardsType[THREEJUNKO-1]=1;
		}
		else if(moves.at(i).cardsType==THREEJUNKO_ONE)
		{
			p.p3_IsExistCardsType[THREEJUNKO_ONE-1]=1;
		}
		else if(moves.at(i).cardsType==THREEJUNKO_TWO)
		{
			p.p3_IsExistCardsType[THREEJUNKO_TWO-1]=1;
		}
		else if(moves.at(i).cardsType==FOUR_TWO)
		{
			p.p3_IsExistCardsType[FOUR_TWO-1]=1;
		}
		else
		{
			p.p3_IsExistCardsType[FOUR_TWO_COUPLE-1]=1;
		}
	}
}