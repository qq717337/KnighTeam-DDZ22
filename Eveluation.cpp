#include "Eveluation.h"
#include "time.h"
#include "DDZMoveManager.h"

CEveluation::CEveluation() 
{

}

CEveluation::~CEveluation() 
{

}

/**
*   ��ʼ����������ȱ�
*/
void CEveluation::initMembership(Player p)
{
	for(size_t i=0;i<54;i++)  //��ʼ�����p1�����ȱ�
	{
		p.p1_Membership[i]=0.5;
	}

	for(size_t i=0;i<54;i++)  //��ʼ�����p2�����ȱ�
	{
		p.p2_Membership[i]=0.5;
	}
}


/**
* �����ҷ������ƽ����p1��p2�����ȱ����
*/
void CEveluation::ClearedByDealCards(Player p)
{
	for(size_t i=0;i<p.p3_cardsList.size();i++)
	{
		int value = p.p3_cardsList[i];
		p.p1_Membership[value]=0;
		p.p2_Membership[value]=0;
	}
}
/**
* ����3�ŵ��ƽ����p1��p2�����ȱ����
* @leftCards 3�ŵ���
*/
void CEveluation::ClearedByLeftCards(Player p,vector<unsigned> leftCards)
{
	if(p.p3_IsLandlord)    // �ҷ�ץ��
	{
		for(size_t i=0;i<leftCards.size();i++)
		{
			p.p1_Membership[leftCards.at(i)]=0;//ץ������������
			p.p2_Membership[leftCards.at(i)]=0;//ץ������������
		}
	}
	else if(p.p2_IsLandlord)// ���p2ץ��
	{
		for(size_t i=0;i<leftCards.size();i++)
		{
			p.p1_Membership[leftCards.at(i)]=0;//ץ������������
			p.p2_Membership[leftCards.at(i)]=1;//ץ��������Ϊ1.0
		}
	}
	else					// ���p1ץ��
	{
		for(size_t i=0;i<leftCards.size();i++)
		{
			p.p1_Membership[leftCards.at(i)]=1;//ץ��������Ϊ1.0
			p.p2_Membership[leftCards.at(i)]=0;//ץ������������
		}
	}
}

/**
*  ��ҳ��ƣ��������ȱ����
* @playerCards ����
*/
void CEveluation::ClearedByPlayCards(Player p,vector<unsigned> playCards)
{

	for(size_t i=0;i<playCards.size();i++)
	{
		p.p1_Membership[playCards.at(i)]=0;
		p.p2_Membership[playCards.at(i)]=0;
	}
}

/**
*  ����ʣ�����ͱ�
*  @list �ѳ�����
*/
void CEveluation::RefreshRemaining(Player p,vector<unsigned> list)
{
	for(size_t i=0;i<list.size();i++)
	{
		if(list[i]==53)
		{
			if(p.remaining[14]!=0)
			{
				p.remaining[14]--;// �������⴦��
			}
		}
		else
		{
			if(p.remaining[list.at(i)/4]!=0)
			{
				p.remaining[list.at(i)/4]--;
			}
		}
	}
}
/**
*  �����߲��²������������ȣ��������
*  @whoseGo �ֵ�˭�߲�  @cardsType ��������  @playCards ����
*/
void CEveluation::UpdateByPlayCards(Player p,int whoseGo,int cardsType,vector<unsigned> playCards)
{
	DDZPlayer *play = new DDZPlayer();
	
	switch(cardsType)
	{
	case ROCKET:
		break;
	case ZHADAN:
		break;
	case SINGLE:
		{
			unsigned singleValue = playCards.at(0);
			for (size_t i = 4 * singleValue; i<4 * singleValue + 4; i++)
			{
				if(whoseGo==1)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i] -= 0.25;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i] += 0.25;
					}

				}
				else if(whoseGo==2)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i] += 0.25;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i] -= 0.25;
					}
				}
			}
			break;
		}
	case COUPLE:
		{
			unsigned coupleValue = playCards.at(0);
			for (size_t i = 4 * coupleValue; i<4 * coupleValue + 4; i++)
			{
				if(whoseGo==1)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i] -= 0.25;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i] += 0.25;
					}

				}
				else if(whoseGo==2)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i] += 0.25;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i] -= 0.25;
					}
				}
			}
			break;
		}
	case SANTIAO:
		{	
			unsigned SanTiaoValue = playCards.at(0);
			for (size_t i = 4 * SanTiaoValue; i<4 * SanTiaoValue + 4; i++)
			{
				if(whoseGo==1)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]=0;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]=1;
					}

				}
				else if(whoseGo==2)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]=1;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]=0;
					}
				}
			}
		break;
		}
	case THREE_ONE:
		{

			vector<unsigned> Three_OneInfo = play->getThree_OneValue(playCards);

			unsigned SanTiaoValue = Three_OneInfo.at(0);//����һ ��������ֵ
			unsigned SanTiao_One = Three_OneInfo.at(2);//����һ ��������ֵ

			for (size_t i = 4 * SanTiaoValue; i<4 * SanTiaoValue + 4; i++)
			{
				if(whoseGo==1)// ���һ���������һ�����ҷ�����������ʣ���һ�ţ�����һ�ż�������һ�������
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]=0;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]=1;
					}

				}
				else if(whoseGo==2)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]=1;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]=0;
					}
				}
			}

			for (size_t i = 4 * SanTiao_One; i<4 * SanTiao_One + 4; i++)
			{
				if(whoseGo==1)// ���Ĵ���������
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i] -= 0.25;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i] += 0.25;
					}

				}
				else if(whoseGo==2)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]+=0.25;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]-=0.25;
					}
				}
			}
		break;
		}
	case THREE_TWO:
		{
			vector<unsigned> Three_TwoInfo = play->getThree_TwoValue(playCards);

			unsigned SanTiaoValue = Three_TwoInfo.at(0);//����һ ��������ֵ
			unsigned SanTiao_Two = Three_TwoInfo.at(2);//����һ ��������ֵ

			for (size_t i = 4 * SanTiaoValue; i<4 * SanTiaoValue + 4; i++)
			{
				if(whoseGo==1)// ���һ���������һ�����ҷ�����������ʣ���һ�ţ�����һ�ż�������һ�������
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]=0;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]=1;
					}

				}
				else if(whoseGo==2)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]=1;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]=0;
					}
				}
			}

			for (size_t i = 4 * SanTiao_Two; i<4 * SanTiao_Two + 4; i++)
			{
				if(whoseGo==1)// ���Ĵ���������
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]-=0.25;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]+=0.25;
					}

				}
				else if(whoseGo==2)
				{
					if(p.p1_Membership[i]!=0)
					{
						p.p1_Membership[i]+=0.25;
					}

					if(p.p2_Membership[i]!=0)
					{
						p.p2_Membership[i]-=0.25;
					}
				}
			}
		break;
		}
	case SINGLEJUNKO:
		{
			vector<unsigned> singleJunkoInfo = play->getSingleJunkoValue(playCards);

			unsigned startJunkoValue = singleJunkoInfo.at(0);
			unsigned endJunkoValue = singleJunkoInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]-=0.2;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]+=0.2;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]+=0.2;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]-=0.2;
						}
					}
				}
			}
		
		break;
		}
	case DUALJUNKO:
		{
			vector<unsigned> DualJunkoInfo = play->getDualJunkoValue(playCards);

			unsigned startJunkoValue = DualJunkoInfo.at(0);
			unsigned endJunkoValue = DualJunkoInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]-=0.3;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]+=0.3;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]+=0.3;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]-=0.3;
						}
					}
				}
			}
		
		break;
		}
	case THREEJUNKO:
		{
			vector<unsigned> ThreeJunkoInfo = play->getThree_ShunValue(playCards);

			unsigned startJunkoValue = ThreeJunkoInfo.at(0);
			unsigned endJunkoValue = ThreeJunkoInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]=0;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]=1;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]=1;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]=0;
						}
					}
				}
			}
		
		break;
		}
	case THREEJUNKO_ONE:
		{
			vector<unsigned> ThreeJunko_OneInfo = play->getThree_OneValue(playCards);

			unsigned startJunkoValue = ThreeJunko_OneInfo.at(0);
			unsigned endJunkoValue = ThreeJunko_OneInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]=0;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]=1;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]=1;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]=0;
						}
					}
				}
			}

			for(size_t k=2;k<ThreeJunko_OneInfo.size();k++)
			{
				for (size_t i = 4 * (ThreeJunko_OneInfo.at(k)); 
					i<4 * (ThreeJunko_OneInfo.at(k)) + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]-=0.25;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i] += 0.25;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i] += 0.25;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i] -= 0.25;
						}
					}
				}
			}
		
		break;
		}
	case THREEJUNKO_TWO:
		{
			vector<unsigned> ThreeJunko_TwoInfo = play->getThree_TwoValue(playCards);

			unsigned startJunkoValue = ThreeJunko_TwoInfo.at(0);
			unsigned endJunkoValue = ThreeJunko_TwoInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]=0;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]=1;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]=1;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]=0;
						}
					}
				}
			}

			for(size_t k=2;k<ThreeJunko_TwoInfo.size();k++)// ������Ϣ����
			{
				for (size_t i = 4 * (ThreeJunko_TwoInfo.at(k)); 
					i<4 * (ThreeJunko_TwoInfo.at(k)) + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]=0;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]=1;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]=1;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i]=0;
						}
					}
				}
			}
		
		break;
		}
	case FOUR_TWO:
		{
			vector<unsigned> four_TwoInfo = play->getFour_TwoValue(playCards);

			for(size_t k=1;k<four_TwoInfo.size();k++)// ������Ϣ����
			{
				for (size_t i = 4 * (four_TwoInfo.at(k)); i<4 * (four_TwoInfo.at(k)) + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i]-=0.25;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i] += 0.25;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i] += 0.25;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i] -= 0.25;
						}
					}
				}
			}


			break;
		}
	case FOUR_TWO_COUPLE:
		{
		vector<unsigned> four_TwoCoupleInfo = play->getFour_TwoCoupleValue(playCards);

			for(size_t k=1;k<four_TwoCoupleInfo.size();k++)// ������Ϣ����
			{
				for (size_t i = 4 * (four_TwoCoupleInfo.at(k)); 
					i<4 * (four_TwoCoupleInfo.at(k)) + 4; i++)
				{
					if(whoseGo==1)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i] -= 0.25;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i] += 0.25;
						}

					}
					else if(whoseGo==2)
					{
						if(p.p1_Membership[i]!=0)
						{
							p.p1_Membership[i] += 0.25;
						}

						if(p.p2_Membership[i]!=0)
						{
							p.p2_Membership[i] -= 0.25;
						}
					}
				}
			}
		break;
		}
	}


	delete(play);
	play = NULL;
}

void CEveluation::UpdateFewCards(int whoseGo,Player p)
{
	int cardsType=p.lastMove.cardsType;
	if(whoseGo!=1||whoseGo!=2||whoseGo!=3)
	{
		return ;
	}
	else if(whoseGo==1)
	{
		p.p1_fewCards[cardsType]=1;
	}
	else if(whoseGo==2)
	{
		p.p2_fewCards[cardsType]=1;
	}
}

void CEveluation::UpdateManyCards(int whoseGo,Player p)
{
	int cardsType=p.firstMove.cardsType;
	if(whoseGo!=1||whoseGo!=2||whoseGo!=3)
	{
		return ;
	}
	else if(whoseGo==1&&p.firstPlayer==1)
	{
		p.p1_manyCards[cardsType]=1;
	}
	else if(whoseGo==2&&p.firstPlayer==2)
	{
		p.p2_manyCards[cardsType]=1;
	}
}

/**
*   ���ؿ������
*   ����������˵�
*   ����ʣ�����ӱ�Ͷ����������ȱ����һ����ҵ�ģ������ƣ���ʣ�����Ӽ�Ϊ��һ���
*   ��ע���������ģ�ⷽѡ��Ҳ���������
*/
void CEveluation::RandMenu(Player p)
{
	srand(time(NULL));

	//��ʼ�����1��2����
	for(size_t i=0;i<15;i++)
	{
		p.p1_EachCardNum[i]=0;
		p.p2_EachCardNum[i]=0;
	}


	int whoseRand=rand()%10;

	double tmp_Membership[54];
	int cardsNum=0;   // ����˵���Ҫ���������������???

	if(whoseRand<5) // �����Ϊ0-4������������1ģ������
	{
		memcpy(tmp_Membership,p.p1_Membership,sizeof(tmp_Membership));
		cardsNum=p.p1_cardsNum;

		while(cardsNum)// ֱ���������������ƣ�ѭ������
		{
			for(size_t i=0;i<54;i++) // �������ģ����ʽ��ʼ
			{
				double randNum = (double)(rand()%100)/100.00;// ����һ��0.00->1.00�������
		
				if (i == 53)
				{
					if (randNum < tmp_Membership[i] && cardsNum != 0 
						&& p.p1_EachCardNum[14] < p.remaining[14])
					{
						p.p1_EachCardNum[14]++;
						cardsNum--;
					}
				}
				else
				{
					if (randNum < tmp_Membership[i] && cardsNum != 0
						&& p.p1_EachCardNum[i / 4] < p.remaining[i / 4])
					{
						p.p1_EachCardNum[i / 4]++;
						cardsNum--;
					}
				}
			}
		}

		for(size_t i=0;i<15;i++)
		{
			p.p2_EachCardNum[i]=p.remaining[i]-p.p1_EachCardNum[i];//�������1������Ƽ�����ʣ���õ����2����
		}
	}
	else			// �����Ϊ5-9������������2ģ������
	{
		memcpy(tmp_Membership,p.p2_Membership,sizeof(tmp_Membership));
		cardsNum=p.p2_cardsNum;

		while(cardsNum)
		{
			for(size_t i=0;i<54;i++) // �������ģ����ʽ��ʼ
			{
				double randNum = (double)(rand()%100)/100.00;// ����һ��0.00->1.00�������
		
				if (i == 53)
				{
					if (randNum < tmp_Membership[i] && cardsNum != 0
						&& p.p2_EachCardNum[14] < p.remaining[14])
					{
						p.p2_EachCardNum[14]++;
						cardsNum--;
					}
				}
				else
				{
					if (randNum < tmp_Membership[i] && cardsNum != 0
						&& p.p2_EachCardNum[i / 4] < p.remaining[i / 4])
					{
						p.p2_EachCardNum[i / 4]++;
						cardsNum--;
					}
				}
			}
		}

		for(size_t i=0;i<15;i++)
		{
			p.p1_EachCardNum[i]=p.remaining[i]-p.p2_EachCardNum[i];//�������2������Ƽ�����ʣ���õ����1����
		}
	}	
}

vector<int> CEveluation::ComputeNumOfBasic(int *cards)
{
	vector<int> tmp_vector;

	int single=0;
	int couple=0;
	int threeTiao=0;

	int tmp_cards[15];
	memcpy(tmp_cards,cards,sizeof(tmp_cards));

	for(size_t i=0;i<13;i++)//3->A��2
	{
		if(tmp_cards[i]==1)
		{
			single++;
		}
		else if(tmp_cards[i]==2)
		{
			couple++;
		}
		else if(tmp_cards[i]==3)
		{
			threeTiao++;
		}
	}

	if(tmp_cards[13]==1&&tmp_cards[14]==0)
	{
		single++;
	}
	if(tmp_cards[13]==0&&tmp_cards[14]==1)
	{
		single++;
	}

	tmp_vector.push_back(single);
	tmp_vector.push_back(couple);
	tmp_vector.push_back(threeTiao);

	return tmp_vector;
}
//
//int getMaxIndexOfBasic(vector<int> vector)
//{
//	int maxIndex=0;
//
//	for(size_t i=1;i<vector.size();i++)
//	{
//		if(vector.at(i)>vector.at(i-1))
//		{
//			maxIndex=i;
//		}
//	}
//
//	return maxIndex+1;
//}

/*    AI Pass����   */
int CEveluation::IsAiPass(Player p)
{
	if(p.p2_IsLandlord)		 //  �ϼ�Ϊ����
	{
		if(p.lastPlayer==1)	 //  ������Ϊ�¼�
		{
			return 1;
		}
	}

	if(p.p1_IsLandlord)
	{
		if(p.p1_general.size()>0 && p.p1_general[p.p1_general.size()-1].cardsType==-1 
			&& p.lastPlayer == 2 && p.firstPlayer ==3)
		{
			return 1;
		}
	}

	return 0;
}

int CEveluation::EveluateMove(Player p, CARDSMOVE* move, int whoseGo)
{
	int score=0;//��ֵ
	
	int MoveType = move->cardsType;
	vector<unsigned> tmp_vi = move->cards;
	
	unsigned tmp_cards[15];
	unsigned next_cards[15];

	bool current_IsLandlord; // ��ǰ�Ƿ�Ϊ����
	bool next_IsLandlord;     // �¼��Ƿ�Ϊ����
	bool front_IsLandLord;
	

	if(whoseGo%3==0)
	{
		memcpy(tmp_cards,p.p3_EachCardNum,sizeof(tmp_cards));
		memcpy(next_cards,p.p1_EachCardNum,sizeof(next_cards));

		current_IsLandlord=p.p3_IsLandlord;
		next_IsLandlord=p.p1_IsLandlord;
		front_IsLandLord=p.p2_IsLandlord;
	}
	else if(whoseGo%3==2)
	{
		memcpy(tmp_cards,p.p1_EachCardNum,sizeof(tmp_cards));
		memcpy(next_cards,p.p2_EachCardNum,sizeof(next_cards));

		current_IsLandlord=p.p1_IsLandlord;
		next_IsLandlord=p.p2_IsLandlord;
		front_IsLandLord=p.p3_IsLandlord;
	}
	else
	{
		memcpy(tmp_cards,p.p2_EachCardNum,sizeof(tmp_cards));
		memcpy(next_cards,p.p3_EachCardNum,sizeof(next_cards));

		current_IsLandlord=p.p2_IsLandlord;
		next_IsLandlord=p.p3_IsLandlord;
		front_IsLandLord=p.p1_IsLandlord;
	}

	DDZPlayer *play=new DDZPlayer();
	

	switch(MoveType)
	{
	case ROCKET:
		{
			break;
		}
		

	case ZHADAN:
		{
			int hisZhaDanValue = play->getZhaDanValue(tmp_vi);// ��ȡը��������ֵ
			int myZhaDanValue = play->getZhaDanValue(tmp_vi);// ��ȡը��������ֵ
			if (move->status == STATUS_MAX && p.p3_canPlayOver)
			{
				score += 9999;
			}
			break;
		}

	case SINGLE:
		{
			int SingleValue = play->getSingleValue(tmp_vi);

			if(tmp_cards[SingleValue]==1 )//����ʵ������������ȡ��ֵ
			{
				score+=10;
			}
			else if(tmp_cards[SingleValue]==2)
			{
				score-=20;
			}
			else if(tmp_cards[SingleValue]==3)
			{
				score-=30;
			}
			else if(tmp_cards[SingleValue]==4)
			{
				score-=60;
			}

			if ((SingleValue == 13 || SingleValue == 14) &&
				(tmp_cards[13] == 1 && tmp_cards[14] == 1))// �ж����������۷�
			{
				score -= 100;
			}

			break;
		}

	case COUPLE:
		{
			int coupleValue =play->getCoupleValue(tmp_vi);

			if(tmp_cards[coupleValue]==2)
			{
				score+=20;
			}
			else if(tmp_cards[coupleValue]==3)
			{
				score-=30;
			}
			else if(tmp_cards[coupleValue]==4)
			{
				score-=60;
			}
			break;
		}

	case SANTIAO:
		{
			int threeTiaoValue=play->getSanTiaoValue(tmp_vi);

			if(tmp_cards[threeTiaoValue]==3)
			{
				score+=30;
			}
			else if(tmp_cards[threeTiaoValue]==4)
			{
				score-=60;
			} 

			score-=20;// ���������Ƽ���

			break;
		}

	case THREE_ONE:
		{
			vector<unsigned> cardsInfo = play->getThree_OneValue(tmp_vi);
			int threeTiaoValue=cardsInfo.at(0);

			if(tmp_cards[threeTiaoValue]==3)
			{
				score+=30;
			}
			else if(tmp_cards[threeTiaoValue]==4)
			{
				score-=60;
			}
		}
		break;

	case THREE_TWO:
		{
			vector<unsigned> cardsInfo = play->getThree_TwoValue(tmp_vi);
		
			int threeTiaoValue=cardsInfo.at(0);

			if(tmp_cards[threeTiaoValue]==3)
			{
				score+=30;
			}
			else if(tmp_cards[threeTiaoValue]==4)
			{
				score-=60;
			}
		}
		break;

	case SINGLEJUNKO:
		{
			vector<unsigned> cardsInfo = play->getSingleJunkoValue(tmp_vi);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);

			for(unsigned i =startValue;i<=endValue;i++)
			{
				if(tmp_cards[i]==1)
				{
					score+=20;
				}
				else if(tmp_cards[i]==2)
				{
					score-=10;
				}
				else if(tmp_cards[i]==3)
				{
					score-=20;
				}
				else if(tmp_cards[i]==4)
				{
					score-=60;
				}
			}
		}
		break;

	case DUALJUNKO:
		{
			vector<unsigned> cardsInfo = play->getDualJunkoValue(tmp_vi);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);
			//int junkoNum = endValue-startValue;

			for(unsigned i =startValue;i<=endValue;i++)
			{
				if(tmp_cards[i]==2)
				{
					score+=15;
				}
				else if(tmp_cards[i]==3)
				{
					score-=20;
				}
				else if(tmp_cards[i]==4)
				{
					score-=60;
				}
			}
		}
		break;

	case THREEJUNKO:
		{
			vector<unsigned> cardsInfo = play->getThree_ShunValue(tmp_vi);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);
			//int junkoNum = endValue-startValue;

			for(unsigned i =startValue;i<=endValue;i++)
			{
				if(tmp_cards[i]==3)
				{
					score+=30;
				}
				else if(tmp_cards[i]==4)
				{
					score-=60;
				}
			}
		}
		break;

	case THREEJUNKO_ONE:
		{
			vector<unsigned> cardsInfo = play->getThree_OneValue(tmp_vi);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);
			int junkoNum = endValue-startValue+1;
			
			for(unsigned i =startValue;i<=endValue;i++)
			{
				if(tmp_cards[i]==3)
				{
					score+=40;
				}
				else if(tmp_cards[i]==4)
				{
					score-=200;
				}
			}
		}
		break;

	case THREEJUNKO_TWO:
		{
			vector<unsigned> cardsInfo = play->getThree_TwoValue(tmp_vi);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);
			int junkoNum = endValue-startValue+1;
			 
			for(unsigned i =startValue;i<=endValue;i++)
			{
				if(tmp_cards[i]==3)
				{
					score+=40;
				}
				else if(tmp_cards[i]==4)
				{
					score-=200;
				}
			}
		}
		break;

	case FOUR_TWO:
		{
			vector<unsigned> cardsInfo = play->getFour_TwoValue(tmp_vi);
			int FourValue = cardsInfo.at(0);

			score-=100;
		}
		break;

	case FOUR_TWO_COUPLE:
		{
			vector<unsigned> cardsInfo = play->getFour_TwoCoupleValue(tmp_vi);
			int FourValue = cardsInfo.at(0);
			
			score-=100;
		}
		break;
	}

	move->score=score;
	return score;
}

void CEveluation::EveluateMoves(Player p, vector<CARDSMOVE> *moves, int whoseGo)
{
	for (int i = moves->size() - 1; i >= 0; i--)
	{
		EveluateMove(p, &moves->at(i), whoseGo);
	}
}

void CEveluation::cutCarryCards(Player p,CARDSMOVE *move)
{
	int cardsType = move->cardsType;
	DDZPlayer play = DDZPlayer();
	vector<unsigned> cardsInfo;
	vector<unsigned> canCarryCards;
	if(cardsType==THREE_ONE || cardsType == THREEJUNKO_ONE)
	{
		cardsInfo = play.getThree_OneValue(move->cards);
		canCarryCards = VectorUtil::subVector(2,cardsInfo);
		if(cardsType == THREE_ONE)
		{	
			cutCarryCards1(p, move, canCarryCards, 1, 3, 1);
		}
		else
		{
 			int start = cardsInfo.at(0);
			int end = cardsInfo.at(1);
			int junkoNum = end-start+1;
			canCarryCards = VectorUtil::subVector(2,cardsInfo);

			cutCarryCards1(p, move, canCarryCards, junkoNum , 3 * junkoNum,1);
		}
		
	}
	else if(cardsType == THREE_TWO || cardsType == THREEJUNKO_TWO)
	{
		cardsInfo = play.getThree_TwoValue(move->cards);
		canCarryCards = VectorUtil::subVector(2,cardsInfo);

		if(cardsType == THREE_TWO)
		{	
			cutCarryCards1(p, move, canCarryCards, 2, 3, 0);
		}
		else
		{
 			int start = cardsInfo.at(0);
			int end = cardsInfo.at(1);
			int junkoNum = end-start+1;
			canCarryCards = VectorUtil::subVector(2,cardsInfo);

			cutCarryCards1(p, move, canCarryCards, 2 * junkoNum, 3 * junkoNum, 0);
		}
	}
	else if(cardsType==FOUR_TWO)
	{
		cardsInfo = play.getFour_TwoValue(move->cards);
		canCarryCards = VectorUtil::subVector(1,cardsInfo);

		cutCarryCards1(p, move, canCarryCards, 2, 4, 1);
	}
	else if(cardsType == FOUR_TWO_COUPLE)
	{
		cardsInfo = play.getFour_TwoCoupleValue(move->cards);
		canCarryCards = VectorUtil::subVector(1,cardsInfo);

		cutCarryCards1(p, move, canCarryCards, 4, 4, 0);
	}
	else
	{
		return ;
	}
}

void CEveluation::cutCarryCardsMoves(Player p, vector<CARDSMOVE> *moves)
{
	for (int i = moves->size() - 1; i >= 0;i--)
	{
		cutCarryCards(p, &moves->at(i));// ��ֵ��������
	}
}

void CEveluation::FilterForMoves(vector<CARDSMOVE> *moves,unsigned *cards)
{
	DDZMoveManager ddz_MM = DDZMoveManager();
	vector<CARDSMOVE> singleJunko = ddz_MM.getType8SingleJunko(*moves);


	for(size_t i=0;i < singleJunko.size();i++)
	{
		vector<CARDSMOVE>::iterator it ;
		int len =  singleJunko[i].cards.size();
		int single = 0, couple = 0, santiao = 0, bomb = 0;
		for(size_t j=0;j<len;j++)
		{
			int value = singleJunko[i].cards[j];
			
			if(cards[value]==1)
			{
				single++;
			}
			else if(cards[value]==2)
			{
				couple++;
			}
			else if(cards[value]==3)
			{
				santiao++;
			}
			else 
			{
				bomb++;
			}
		}
		
		if(single < (couple + santiao + 2 * bomb))
		{
			it = singleJunko.begin()+i;
			moves->erase(it);
		}
		
	}
}


/** 
*		��������/˫����˳����/˫���м����Ʋ���
*
*		@*move �������Ƶ��߲�
*		@canCarryCards ����
*		@shouldCarryCards_num Ӧ�ô�������
*		@startIndex ����֮ǰ�����꣨�����м��Ʋ�����
*		@flag �����ǵ��ƻ��Ƕ��ƣ�
*/
void CEveluation::cutCarryCards1(Player p,CARDSMOVE *move,
								 vector<unsigned> canCarryCards,int shouldCarryCards_num,
								 int startIndex, int  flag)
{
	int carryCards_Score[17]={0};
	int carryNum=canCarryCards.size();
	DDZMoveManager ddz_MM= DDZMoveManager();
	vector<CARDSMOVE> tmp_moves;
	vector<CARDSMOVE> single= ddz_MM.getGoodMove3Single(p.p3_allMoves,tmp_moves,p.p3_EachCardNum,1);
	vector<CARDSMOVE> couple= ddz_MM.getGoodMove4Couple(p.p3_allMoves,tmp_moves,p.p3_EachCardNum,1);

	if(flag)
	{
		if(single.size() > 0 && couple.size() > 0)
		{
			if(single[0].cards[0] > couple[0].cards[0])
			{
				move->score-=20;
			}
		}
	}
	else
	{
		if(single.size() > 0 && couple.size() > 0)
		{
			if(single[0].cards[0] < couple[0].cards[0])
			{
				move->score-=20;
			}
		}
	}

	for(size_t i=0;i<canCarryCards.size();i++)
	{
		if(flag)
		{
			if(ddz_MM.IsRelateMoves(single,canCarryCards[i]))
			{
				carryCards_Score[i]+=60;
			}
			else
			{
				carryCards_Score[i]-=30;
			}
		}
		else
		{
			if(ddz_MM.IsRelateMoves(couple,canCarryCards[i]))
			{
				carryCards_Score[i]+=60;
			}
			else
			{
				carryCards_Score[i]-=30;
			}
		}
	}
	vector<unsigned> carryCardsIndex=getMaxElementIndex(carryCards_Score,canCarryCards.size(),shouldCarryCards_num);
	
	for(size_t i=move->cards.size()-1;i>=startIndex;i--)
	{
		bool IsDelete = true;
		for(size_t j=0;j<carryCardsIndex.size();j++)
		{
			if(canCarryCards[carryCardsIndex[j]]==move->cards[i])
			{
				IsDelete = false;
				if (carryCards_Score[carryCardsIndex[j]] < 0)
				{
					move->score -=30;
				}
			}
		}

		if (IsDelete)
		{
			vector<unsigned>::iterator it = move->cards.begin();
			move->cards.erase(it+i);
		}
	}
}

//// ����˫����˳��˫��������
//void CEveluation::cutCarryCards2(Player p,CARDSMOVE *move,vector<unsigned> canCarryCards,int shouldCarryCards_num)
//{
//	int carryCards_Score[17]={0};
//	int carryNum=canCarryCards.size();
//	DDZMoveManager ddz_MM= DDZMoveManager();
//	vector<CARDSMOVE> tmp_moves;
//	vector<CARDSMOVE> couple= ddz_MM.getGoodMove4Couple(p.p3_allMoves,tmp_moves,p.p3_EachCardNum,1);
//	
//	for(size_t i=0;i<canCarryCards.size();i++)
//	{
//		if(ddz_MM.IsRelateMoves(couple,canCarryCards[i]))
//		{
//			carryCards_Score[i]+=60;
//		}
//		else
//		{
//			carryCards_Score[i]-=30;
//		}
//	}
//
//	vector<unsigned> carryCardsIndex=getMaxElementIndex(carryCards_Score,canCarryCards.size(),shouldCarryCards_num);
//	
//	for(size_t i=move->cards.size()-1;i>=3*shouldCarryCards_num/2;i--)
//	{
//		bool flag = true;
//		for(size_t j=0;j<carryCardsIndex.size();j++)
//		{
//			if(canCarryCards[carryCardsIndex[j]]==move->cards[i])
//			{
//				flag=false;	
//			}
//		}
//
//		if(flag)
//		{
//			vector<unsigned>::iterator it = move->cards.begin();
//			move->cards.erase(it+i);
//		}
//	}
//}
//
//// �Ĵ�������������
//void CEveluation::cutCarryCards3(Player p,CARDSMOVE *move,vector<unsigned> canCarryCards,int shouldCarryCards_num)
//{
//	int carryCards_Score[17]={0};
//	int carryNum=canCarryCards.size();
//	DDZMoveManager ddz_MM= DDZMoveManager();
//	vector<CARDSMOVE> tmp_moves;
//	vector<CARDSMOVE> couple= ddz_MM.getGoodMove4Couple(p.p3_allMoves,tmp_moves,p.p3_EachCardNum,1);
//	
//	for(size_t i=0;i<canCarryCards.size();i++)
//	{
//		if(ddz_MM.IsRelateMoves(couple,canCarryCards[i]))
//		{
//			carryCards_Score[i]+=60;
//		}
//		else
//		{
//			carryCards_Score[i]-=30;
//		}
//	}
//	vector<unsigned> carryCardsIndex=getMaxElementIndex(carryCards_Score,canCarryCards.size(),2);
//	
//	for(size_t i=move->cards.size()-1;i>=4;i--)
//	{
//		bool flag = true;
//		for(size_t j=0;j<carryCardsIndex.size();j++)
//		{
//			if(canCarryCards[carryCardsIndex[j]]==move->cards[i])
//			{
//				flag=false;	
//			}
//		}
//
//		if(flag)
//		{
//			vector<unsigned>::iterator it = move->cards.begin();
//			move->cards.erase(it+i);
//		}
//	}
//}
//
//// �Ĵ����Լ�������
//void CEveluation::cutCarryCards4(Player p,CARDSMOVE *move,vector<unsigned> canCarryCards,int shouldCarryCards_num)
//{
//	int carryCards_Score[17]={0};
//	int carryNum=canCarryCards.size();
//	for(size_t i=0;i<canCarryCards.size();i++)
//	{
//		
//	}
//	vector<unsigned> carryCardsIndex=getMaxElementIndex(carryCards_Score,canCarryCards.size(),4);
//	
//	for(size_t i=move->cards.size()-1;i>=4;i--)
//	{
//		bool flag = true;
//		for(size_t j=0;j<carryCardsIndex.size();j++)
//		{
//			if(canCarryCards[carryCardsIndex[j]]==move->cards[i])
//			{
//				flag=false;	
//			}
//		}
//
//		if(flag)
//		{
//			vector<unsigned>::iterator it = move->cards.begin();
//			move->cards.erase(it+i);
//		}
//	}
//}
//

/** �������Ԫ�������ļ���Ԫ�� 
*  @arr					����
*  @len					���鳤��
*  @top_num		���ٸ�Ԫ��
*
*/
vector<unsigned> CEveluation::getMaxElementIndex(int arr[15],unsigned len,int top_num)
{
	vector<unsigned> top_vec;
	int tmp_arr[15];
	memcpy(tmp_arr, arr, sizeof(tmp_arr));

	int maxIndex=0;

	while(top_num--)
	{
		for(size_t i=1;i<len;i++)
		{
			if (tmp_arr[i]>tmp_arr[maxIndex] && !VectorUtil::isContains(top_vec, i))
			{
				maxIndex=i;
			}
		}

		top_vec.push_back(maxIndex);
		tmp_arr[maxIndex] = -999;
		maxIndex=0;

	}

	return top_vec;
}


/**
*  �˺���ֻ����ҷ������ж�
*  
*/
//bool IsPassMove(Player p)
//{
//	if(p.p2_IsLandlord)
//	{
//		if(p.lastPlayer==1)
//		{
//			return true;
//		}
//
//		if(p.firstPlayer==2&&IsBadMove(p)&&IsNotSickMove(p))
//		{
//			return true;
//		}
//
//		if(p.firstPlayer==1&&IsBadMove(p))
//		{
//			return true;
//		}
//	}
//	else if(p.p1_IsLandlord)
//	{
//		if(p.lastPlayer==2&&IsTopMove(p))
//		{
//			return true;
//		}
//
//		if(p.lastPlayer==2&&IsBadMove(p))
//		{
//			return true;
//		}
//	}
//	else 
//	{
//		if(IsBadMove(p))
//		{
//			return true;
//		}
//	}
//}
//
//bool IsBadMove(Player p)
//{
//	return false;
//}
//
//bool IsNotSickMove(Player p)
//{
//	return false;
//}
//
//bool IsTopMove(Player p)
//{
//	return false;
//}

/**
*  ��ָ���ķ�Χ�У��Ƶ�����Ϊ���ƣ����ƻ��������ĸ����ĸ���
*  @array �Ƶ�������ʽ
*  @num   ָ��������
*  @start ��ʼ��Χ
*  @end   ������Χ
*/
unsigned ComputeTotalOfNum(int *array,int num,unsigned start,unsigned end)
{
	unsigned count=0;
	unsigned len;

	GET_ARRAY_LEN(array,len);

	for(unsigned i=start;i<len&&i<=end;i++)
	{
		if(array[i]>=num)
		{
			count++;
		}
	}

	return count;
}

void CEveluation::EveluateCombs(Player p)
{
	CombsLib combs = p.p3_combs;
	if(p.p3_IsLandlord)//�ҷ�Ϊ�����������������ֻʣ��һ���ƣ���ѡ���ƽ��ٵ����
	{
		if(p.p1_cardsNum==1||p.p2_cardsNum==1)
		{
			combs[6].score+=100;
		}
	}
	else						 //�ҷ�Ϊũ��
	{
		if(p.p1_IsLandlord&&p.p1_cardsNum==1)
		{
			combs[6].score+=100;
		}

		if(p.p2_IsLandlord&&p.p2_cardsNum==1)
		{
			combs[6].score+=100;
		}
	}

	int min=getMinIndexOfCombs(combs);
	
	if(combs[min].moves.size()==1)
	{
		combs[min].score+=200;
	}
	else
	{
		combs[min].score+=50;		//�߲����ٵ����
	}

	for(size_t i=0;i<combs.size();i++)
	{
		for(size_t j=0;j<combs[i].moves.size();j++)
		{

		}
	}
}

int CEveluation::getMinIndexOfCombs(CombsLib combs)
{
	int min=0;
	for(size_t i=1;i<combs.size();i++)
	{
		if(combs[i].moves.size()<combs[min].moves.size())
		{
			min=i;
		}
	}

	return min;
}

vector<unsigned> CEveluation::haveZhaDanOutside(Player p)
{
	vector<unsigned> zhaDans;
	for(size_t i=0;i<13;i++)
	{
		if(p.remaining[i]==4)
		{
			zhaDans.push_back(i); 
		}
	}

	return zhaDans;
}

vector<unsigned> CEveluation::haveZhaDanP2(Player p)
{
	vector<unsigned> zhaDans;

	for(size_t i=0;i<13;i++)
	{
		if(p.p2_EachCardNum[i]==4)
		{
			zhaDans.push_back(i);
		}
	}

	return zhaDans;
}

vector<unsigned> CEveluation::haveZhaDanP1(Player p)
{
	vector<unsigned> zhaDans;

	for(size_t i=0;i<13;i++)
	{
		if(p.p1_EachCardNum[i]==4)
		{
			zhaDans.push_back(i);
		}
	}


	return zhaDans;
}


int CEveluation::IsPlay3Single(vector<CARDSMOVE> moves,Player p,unsigned *cards)
{
	DDZMoveManager ddz_MM = DDZMoveManager();
	vector<CARDSMOVE> tmp_single;
	vector<CARDSMOVE> single = ddz_MM.getGoodMove3Single(moves,tmp_single,cards,1);
	unsigned santiao_Num = ddz_MM.getGoodMove5Santiao(moves,tmp_single,cards,1).size();
	int k = single.size() - santiao_Num;
	if(single.size()>0 && k >= 4 && single[0].cards[0]<7)
	{
		return 1;
	}

	return 0;
}

int CEveluation::IsPlay4Couple(vector<CARDSMOVE> moves,Player p,unsigned *cards)
{
	DDZMoveManager ddz_MM = DDZMoveManager();
	vector<CARDSMOVE> tmp_couple;
	vector<CARDSMOVE> couple = ddz_MM.getGoodMove4Couple(moves,tmp_couple,cards,1);
	
	if(couple.size() >=4)
	{
		return 1;
	}

	return 0;
}

int CEveluation::IsPlay5Santiao(vector<CARDSMOVE> moves,Player p,unsigned *cards)
{
	DDZMoveManager ddz_MM = DDZMoveManager();
	vector<CARDSMOVE> tmp_couple;
	vector<CARDSMOVE> santiao = ddz_MM.getGoodMove5Santiao(moves,tmp_couple,cards,1);
	
	if(santiao.size() >=3)
	{
		return 1;
	}

	if(santiao.size() >=2 && santiao[santiao.size()-1].cards[0]>7)
	{ 
		return 1;
	}

	return 0;

}