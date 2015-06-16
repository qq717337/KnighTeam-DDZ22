#include "DDZPlayer.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "PublicVar.h"
#include "string"
#include "iostream"
#include "vector"
#include "ThinkTable.h"
#include "MoveGenerator.h"
#include "time.h"
#include "fstream"
#include "MCSearch.h"
#include "AlphaBeta.h"


using namespace std;

typedef vector<unsigned> VECTORINT;
typedef vector<vector<unsigned>> MOVES;


DDZPlayer::DDZPlayer(void)
{
}


DDZPlayer::~DDZPlayer(void)
{
}



/**     �յ�ƽ̨���DOUDIZHUVER 1.0					*/
/**	    �ظ���Name cqut									*/
void DDZPlayer::CalName(char *cInMessage, char *cOutMessage)
{
	strcpy_s(cOutMessage,80,"Name cqut");
}


/**		�յ�ƽ̨���INFO 1,4,1,6,9,2100,15				*/
/**	    �ظ���OK INFO									*/
void DDZPlayer::CalInfo(char *cInMessage,char *cOutMessage)
{
	strcpy_s(cOutMessage,80,"OK INFO");
}


/**		�յ�ƽ̨���ERROR A(B/C)						*/
/**	    �ظ���OK ERROR									*/
void DDZPlayer::CalErr(char *cInMessage,char *cOutMessage)
{
	strcpy_s(cOutMessage,80,"OK ERROR");
}


/**		�յ�ƽ̨���DEAL B0,4,5,7,9,10,17,21,25,		*/
/**     33,34,39,41,43,44,45,46							*/
/**	    �ظ���OK DEAL									*/
void DDZPlayer::CalDeal(char *cInMessage,char *cOutMessage,Player p)
{
	CEveluation *eveluate;
	eveluate =(CEveluation*)malloc(sizeof(CEveluation));
	CThinkTable think = CThinkTable();
	// ����Ĭ�����p3Ϊ�ҷ������p2Ϊ�ҷ��ϼң����p1Ϊ�ҷ��¼�
	p.p3_pos=cInMessage[5]-'A';			// �����ҷ�λ��  ��/��/��
	
	/** ��ʼ�����λ����Ϣ */
	int pos3 = p.p3_pos;
	switch(pos3)
	{
	case 0:
		p.p1_pos=1;
		p.p2_pos=2;

		p.p1_front =0;
		p.p1_next = 2;

		p.p2_front=1;
		p.p2_next =0;

		p.p3_front=2;
		p.p3_next=1;
		break;
	case 1:
		p.p1_pos=2;
		p.p2_pos=0;

		p.p1_front =1;
		p.p1_next = 0;

		p.p2_front=2;
		p.p2_next =1;

		p.p3_front=0;
		p.p3_next=2;
		break;
	case 2:
		p.p1_pos=0;
		p.p2_pos=1;

		p.p1_front =2;
		p.p1_next = 1;

		p.p2_front=0;
		p.p2_next =2;

		p.p3_front=1;
		p.p3_next=0;
		break;
	}

	string deal = string(cInMessage);

	string subDeal(deal.begin()+6,deal.end()); // ��ȡ����������17����

	p.p3_cardsList=stringUtil->stringSplit(subDeal,',');
	
	think.initEachCardNum(p);	// ��ʼ��p3_EachCardNum
	think.updateEachCardNum(p, p.p3_cardsList, 1);//�����ҷ���������������

	eveluate->initMembership(p);    // ��ʼ����������ȱ�
	eveluate->ClearedByDealCards(p);// ��������ҳ����� Ϊ �ҷ�����������������
	eveluate->RefreshRemaining(p, p.p3_cardsList);//����ʣ�����ͱ�

	delete(eveluate);//�ͷ�ָ���ڴ�
	strcpy_s(cOutMessage,80,"OK DEAL");
}


/**		�յ�ƽ̨���BID A3	/ BID WHAT					*/
/**	    �ظ���OK BID	   /  BID B3[(A/C)(1/2)]			*/
void DDZPlayer::CalBid(char *cInMessage,char *cOutMessage,Player p)
{
	CThinkTable think;
	char callBid[80];
	strcpy_s(callBid,80,"BID A0");
	callBid[4]+=p.p3_pos;// ���λ��
	int bid = think.getBid(p);
	callBid[5]+=bid;// �з�
	

	switch(cInMessage[4])
	{
	case 'A':
		if(p.p1_pos==0)
		{
			p.p1_bid=cInMessage[5]-'0';
		}
		else
		{
			p.p2_bid=cInMessage[5]-'0';
		}
		strcpy_s(cOutMessage,80,"OK BID");
		break;
	case 'B':
		if(p.p1_pos==1)
		{
			p.p1_bid=cInMessage[5]-'0';
		}
		else
		{
			p.p2_bid=cInMessage[5]-'0';
		}

		strcpy_s(cOutMessage,80,"OK BID");
		break;
	case 'C':
		if(p.p1_pos==2)
		{
			p.p1_bid=cInMessage[5]-'0';
		}
		else
		{
			p.p2_bid=cInMessage[5]-'0';
		}
		strcpy_s(cOutMessage,80,"OK BID");
		break;
	case 'W':
		strcpy_s(cOutMessage,80,callBid);
		break;
	}
	
}


/**		�յ�ƽ̨���LEFTOVER B27,48,53					*/
/**	    �ظ���OK LEFTOVER								*/
void DDZPlayer::CalLeft(char *cInMessage,char *cOutMessage,Player p)
{
	CEveluation *eveluate;
	eveluate =(CEveluation*)malloc(sizeof(CEveluation));
	CMoveGenerator *m_pMG;
	m_pMG=(CMoveGenerator*)malloc(sizeof(m_pMG));

	CThinkTable *think;
	think=(CThinkTable*)malloc(sizeof(CThinkTable));
	string tmp_str(cInMessage);
	string str2(tmp_str.begin()+10,tmp_str.end());
	vector<unsigned> list =stringUtil->stringSplit(str2,',');// ���3�ŵ���

	switch(cInMessage[9])
	{
	case 'A':
		if(p.p1_pos==0)
		{
			p.p1_IsLandlord=true;
			p.p1_cardsNum+=3;
			p.firstPlayer=1;
		}
		else if(p.p2_pos==0)
		{
			p.p2_IsLandlord=true;
			p.p2_cardsNum+=3;
			p.firstPlayer=2;
		}
		else
		{
			p.p3_IsLandlord=true;
			p.p3_cardsNum+=3;
			p.firstPlayer=3;

			for(size_t i=0;i<list.size();i++)
			{
				p.p3_cardsList.push_back(list.at(i));
			}
			think->updateEachCardNum(p, list, 1);
			eveluate->RefreshRemaining(p, list);//����ʣ�����ͱ�
		}
		break;
	case 'B':
		if(p.p1_pos==1)
		{
			p.p1_IsLandlord=true;
			p.p1_cardsNum+=3;
			p.firstPlayer=1;
		}
		else if(p.p2_pos==1)
		{
			p.p2_IsLandlord=true;
			p.p2_cardsNum+=3;
			p.firstPlayer=2;
		}
		else
		{
			p.p3_IsLandlord=true;
			p.p3_cardsNum+=3;
			p.firstPlayer=3;

			for(size_t i=0;i<list.size();i++)
			{
				p.p3_cardsList.push_back(list.at(i));
			}
			think->updateEachCardNum(p, list, 1);
			eveluate->RefreshRemaining(p, list);//����ʣ�����ͱ�
		}
		break;
	case 'C':
		if(p.p1_pos==2)
		{
			p.p1_IsLandlord=true;
			p.p1_cardsNum+=3;
			p.firstPlayer=1;

			
		}
		else if(p.p2_pos==2)
		{
			p.p2_IsLandlord=true;
			p.p2_cardsNum+=3;
			p.firstPlayer=2;
		}
		else
		{
			p.p3_IsLandlord=true;
			p.p3_cardsNum+=3;
			p.firstPlayer=3;

			for(size_t i=0;i<list.size();i++)
			{
				p.p3_cardsList.push_back(list.at(i));
			}
			think->updateEachCardNum(p, list, 1);
			eveluate->RefreshRemaining(p, list);//����ʣ�����ͱ�
		}
		break;
		
	}

	p.p3_allMoves=m_pMG->getMovesByMyself(p.p3_cardsList.size(),p.p3_EachCardNum);
	//m_pMG->PriorityCombinatoriaLibrary(p);
	eveluate->ClearedByLeftCards(p,list); // ���ݵ��Ƹ��������ȱ�
	
	strcpy_s(cOutMessage,80,"OK LEFTOVER");
	delete(think);
	delete(eveluate);//�ͷ�ָ���ڴ�
}


/**		�յ�ƽ̨���PLAY A12��13��14��21 /  PLAY WHAT	*/
/**	    �ظ���OK PLAY		/    PLAY B31��32��33��0		*/
void DDZPlayer:: CalPla(char *cInMessage,char *cOutMessage,Player p)
{
	CEveluation *eveluate; 
	eveluate =(CEveluation*)malloc(sizeof(CEveluation));
	char callPass[20];
	char callPla[200];
	CMoveGenerator *move;
	move = (CMoveGenerator*)malloc(sizeof(CMoveGenerator));

	strcpy_s(callPass,20,"PLAY A-1");
	strcpy_s(callPla,200,"PLAY A");

	callPass[5]+=p.p3_pos;
	callPla[5]+=p.p3_pos;

	string tmp_str(cInMessage);
	
	switch(cInMessage[5])
	{
	case 'A':
		if(cInMessage[6]=='-')
		{
			CARDSMOVE null_move;
			NULL_MOVE(null_move);
			if(p.p1_pos==0)
			{
				eveluate->UpdateFewCards(1,p);
				p.p1_yiChu.push_back(null_move);
				p.p1_general.push_back(null_move);
				p.p3_allMoves=move->getMovesByMyself(p.p3_cardsList.size(),p.p3_EachCardNum);
				//move->PriorityCombinatoriaLibrary(p);
			}
			else
			{
				eveluate->UpdateFewCards(2,p);
				p.p2_yiChu.push_back(null_move);
				p.p2_general.push_back(null_move);
			}
		}
		else
		{
			string subPla(tmp_str.begin()+6,tmp_str.end());
			vector<unsigned> list = stringUtil->stringSplit(subPla,',');

			vector<unsigned> generalCards =getCardsValue(sortCardsVector(list));// �ź��򣬻�Ϊһ������ֵ
			int cardType = getCardsType(generalCards);// ��ó�������

			CARDSMOVE g_move,y_move;
			g_move.cards=generalCards;
			g_move.cardsType=cardType;

			y_move.cards=list;
			y_move.cardsType=cardType;


			eveluate->ClearedByPlayCards(p,list);//���ݳ��Ƹ�����������ȱ�
			eveluate->RefreshRemaining(p,list);// ����ʣ�����ͱ�

			if(p.p1_pos==0)
			{
				if(p.firstPlayer==1)
				{
					p.p1_manyCards[cardType]=1;
				}
				p.p1_cardsNum-=list.size();// ��ҳ�һ���ƣ�������=ԭ������-��������
				p.p1_yiChu.push_back(y_move);
				p.p1_general.push_back(g_move);
				p.p3_allMoves=move->getMovesByMyself(p.p3_cardsList.size(),p.p3_EachCardNum);
				//move->PriorityCombinatoriaLibrary(p);
				eveluate->UpdateByPlayCards(p, 1, cardType, generalCards);
			}
			else
			{
				if(p.firstPlayer==2)
				{
					p.p2_manyCards[cardType]=1;
				}
				p.p2_cardsNum-=list.size();// ��ҳ�һ���ƣ�������=ԭ������-��������
				p.p2_yiChu.push_back(y_move);
				p.p2_general.push_back(g_move);
				eveluate->UpdateByPlayCards(p, 2, cardType, generalCards);
			}
		}
		delete(eveluate);//�ͷ�eveluateָ���ڴ�
		delete(move);	 //�ͷ�moveָ���ڴ�
		strcpy_s(cOutMessage,80,"OK PLAY");
		break;
	case 'B':
		if(cInMessage[6]=='-')
		{
			CARDSMOVE null_move;
			NULL_MOVE(null_move);
			if(p.p1_pos==1)
			{
				eveluate->UpdateFewCards(1,p);
				p.p1_yiChu.push_back(null_move);
				p.p1_general.push_back(null_move);
				p.p3_allMoves=move->getMovesByMyself(p.p3_cardsList.size(),p.p3_EachCardNum);
				//move->PriorityCombinatoriaLibrary(p);
			}
			else
			{
				eveluate->UpdateFewCards(2,p);
				p.p2_yiChu.push_back(null_move);
				p.p2_general.push_back(null_move);
			}
		}
		else
		{
			string subPla(tmp_str.begin()+6,tmp_str.end());
			vector<unsigned> list = stringUtil->stringSplit(subPla,',');

			vector<unsigned> generalCards =getCardsValue(sortCardsVector(list));// �ź��򣬻�Ϊһ������ֵ
			int cardType = getCardsType(generalCards);// ��ó�������
			

			CARDSMOVE g_move,y_move;
			g_move.cards=generalCards;
			g_move.cardsType=cardType;

			y_move.cards=list;
			y_move.cardsType=cardType;

			eveluate->ClearedByPlayCards(p,list);//���ݳ��Ƹ�����������ȱ�
			eveluate->RefreshRemaining(p,list);// ����ʣ�����ͱ�

			if(p.p1_pos==1)
			{
				if(p.firstPlayer==1)
				{
					p.p1_manyCards[cardType]=1;
				}
				p.p1_cardsNum-=list.size();// ��ҳ�һ���ƣ�������=ԭ������-��������
				p.p1_yiChu.push_back(y_move);
				p.p1_general.push_back(g_move);
				p.p3_allMoves=move->getMovesByMyself(p.p3_cardsList.size(),p.p3_EachCardNum);
				//move->PriorityCombinatoriaLibrary(p);
				eveluate->UpdateByPlayCards(p, 1, cardType, generalCards);
			}
			else
			{
				if(p.firstPlayer==2)
				{
					p.p2_manyCards[cardType]=1;
				}
				p.p2_cardsNum-=list.size();// ��ҳ�һ���ƣ�������=ԭ������-��������
				p.p2_yiChu.push_back(y_move);
				p.p2_general.push_back(g_move);
				eveluate->UpdateByPlayCards(p, 2, cardType, generalCards);
			}
		}
		delete(eveluate);//�ͷ�ָ���ڴ�

		delete(move);	 //�ͷ�moveָ���ڴ�
		strcpy_s(cOutMessage,80,"OK PLAY");
		break;
	case 'C':
		if(cInMessage[6]=='-')
		{
			CARDSMOVE null_move;
			NULL_MOVE(null_move);
			if(p.p1_pos==2)
			{
				eveluate->UpdateFewCards(1,p);
				p.p1_yiChu.push_back(null_move);
				p.p1_general.push_back(null_move);

				p.p3_allMoves=move->getMovesByMyself(p.p3_cardsList.size(),p.p3_EachCardNum);
				//move->PriorityCombinatoriaLibrary(p);
			}
			else
			{
				eveluate->UpdateFewCards(2,p);
				p.p2_yiChu.push_back(null_move);
				p.p2_general.push_back(null_move);
			}
		}
		else
		{
			string subPla(tmp_str.begin()+6,tmp_str.end());
			vector<unsigned> list = stringUtil->stringSplit(subPla,',');

			vector<unsigned> generalCards =getCardsValue(sortCardsVector(list));// �ź��򣬻�Ϊһ������ֵ
			int cardType = getCardsType(generalCards);// ��ó�������

			CARDSMOVE g_move,y_move;
			g_move.cards=generalCards;
			g_move.cardsType=cardType;

			y_move.cards=list;
			y_move.cardsType=cardType;

			eveluate->ClearedByPlayCards(p,list);//���ݳ��Ƹ�����������ȱ�
			eveluate->RefreshRemaining(p,list);// ����ʣ�����ͱ�

			if(p.p1_pos==2)
			{
				if(p.firstPlayer==1)
				{
					p.p1_manyCards[cardType]=1;
				}
				p.p1_cardsNum-=list.size();// ��ҳ�һ���ƣ�������=ԭ������-��������
				p.p1_yiChu.push_back(y_move);
				p.p1_general.push_back(g_move);
				p.p3_allMoves=move->getMovesByMyself(p.p3_cardsList.size(),p.p3_EachCardNum);
				//move->PriorityCombinatoriaLibrary(p);
				eveluate->UpdateByPlayCards(p, 1, cardType, generalCards);
			}
			else
			{
				if(p.firstPlayer==2)
				{
					p.p2_manyCards[cardType]=1;
				}
				p.p2_cardsNum-=list.size();// ��ҳ�һ���ƣ�������=ԭ������-��������
				p.p2_yiChu.push_back(y_move);
				p.p2_general.push_back(g_move);
				eveluate->UpdateByPlayCards(p, 2, cardType, generalCards);
			}
		}
		delete(eveluate);//�ͷ�ָ���ڴ�
		delete(move);	 //�ͷ�moveָ���ڴ�
		strcpy_s(cOutMessage,80,"OK PLAY");
		break;
	case 'W':
		{
			setFirstPlayer(p);
			CThinkTable *think;
			think=(CThinkTable*)malloc(sizeof(CThinkTable));
			
			VECTORINT tmp_vector1;
			CARDSMOVE bestMove;
			AlphaBeta m_cSE =  AlphaBeta();
			
			m_cSE.SearchAGoodMove(p,AlphaBeta_Depth);//�������߲�
			bestMove=m_cSE.bestMove;
			/*MCSearch *m_cSE;
			m_cSE=(MCSearch*)malloc(sizeof(MCSearch));
			bestMove=m_cSE->SearchAGoodMove(p);*/

			
			p.p3_general.push_back(bestMove);

			if(bestMove.cardsType!=-1)
			{		
				tmp_vector1=CardsToIndex(bestMove.cards,p);


				p.p3_cardsNum-=tmp_vector1.size();		// ��ҳ�һ���ƣ�������=ԭ������-��������
				p.p3_yiChu.push_back(bestMove);				// ���ѳ����ƴ���p3_yiChu��
				string str2=string(callPla);
				for(size_t i=0;i<tmp_vector1.size();i++)
				{
					if(i==0)
					{
						str2+=stringUtil->getString(tmp_vector1.at(i));
					}
					else
					{
					str2+=(","+stringUtil->getString(tmp_vector1.at(i)));
					}
				}

				strncpy(cOutMessage,str2.c_str(),str2.length());
				cOutMessage[str2.length()]='\0';
			}
			else 
			{
				p.p3_yiChu.push_back(bestMove);
				strcpy_s(cOutMessage,200,callPass);
			}
		//delete(m_cSE);
		
		delete(think);
		delete(eveluate);//�ͷ�ָ���ڴ�
		delete(move);	 //�ͷ�moveָ���ڴ�
		break;
		}
	}
}




/**		�յ�ƽ̨���GAMEOVER C							*/
/**	    �ظ���OK GAMEOVER								    */
void DDZPlayer::CalGam(char *cInMessage,char *cOutMessage)
{
	strcpy_s(cOutMessage,80,"OK GAMEOVER");
}



/**
*   һ���������³�ʼ�������Ϣ��������һ��
*/
void DDZPlayer::initPlayer(Player p)
{
	p.p1_pos=-1;

	p.p1_IsLandlord=false;

	p.p1_cardsNum=17;

	p.p1_bid=0;

	p.p1_front=-1;

	p.p1_next=-1;

	p.p1_cardsList.clear();

	p.p1_yiChu.clear();

	p.p1_general.clear();



	p.p2_pos=-1;

	p.p2_IsLandlord=false;

	p.p2_cardsNum=17;

	p.p2_bid=0;

	p.p2_front=-1;

	p.p2_next=-1;

	p.p2_cardsList.clear();

	p.p2_yiChu.clear();

	p.p2_general.clear();



	p.p3_pos=-1;

	p.p3_IsLandlord=false;

	p.p3_cardsNum=17;

	p.p3_bid=0;

	p.p3_front=-1;

	p.p3_next=-1;

	p.p3_cardsList.clear();

	p.p3_yiChu.clear();



	p.firstPlayer=-1;

	p.p3_general.clear();
	
	p.p3_canPlayOver = false;

	p.p3_comb.clear();

	for(size_t i=0;i<15;i++)//��ʼ������ʣ���
	{
		if(i>=13)
		{
			p.remaining[i]=1;
		}
		else
		{
			p.remaining[i]=4;
		}
	}

}

/**
*  ���ݸ�����ѳ���,���������������
*/
void DDZPlayer::setFirstPlayer(Player p)
{
	if(p.p1_yiChu.empty()||p.p2_yiChu.empty()||p.p3_yiChu.empty())
	{
		return ;
	}
	else 
	{
		CARDSMOVE p1_lastMove = p.p1_yiChu.at(p.p1_yiChu.size()-1);
		CARDSMOVE p2_lastMove = p.p2_yiChu.at(p.p2_yiChu.size()-1);
		CARDSMOVE p3_lastMove = p.p3_yiChu.at(p.p3_yiChu.size()-1);


		if(p1_lastMove.cardsType==-1&&p2_lastMove.cardsType==-1)
		{
			p.firstPlayer=3;
			return;
		}

		if(p1_lastMove.cardsType==-1&&p3_lastMove.cardsType==-1)
		{
			p.firstPlayer=2;
			return;
		}

		if(p2_lastMove.cardsType==-1&&p3_lastMove.cardsType==-1)
		{
			p.firstPlayer=1;
			return;
		}
	}
}

/**     0	 ��Ȩ             1	  ���		  */
/** 	 2	 ը��             3	  ����		   */
/** 	 4	 ����             5	  ����		   */
/**		 6	 ������          7   ����˫      */
/**      8	 ��˳		      9   ˫˳         */
/** 	10 ��˳		     11  ��˳����   */
/** 	12 ��˳��˫	                            */
/**     13	�Ĵ�����   14  �Ĵ���˫	 */
/** 	-1	  �Ƿ�����                */
int DDZPlayer::getCardsType(VECTORINT vector)// vectorΪ��ת�������Ͳ�������1��2��3��4ת��Ϊ3����3������4
{
	int cardsNum = vector.size();
	switch(cardsNum)
	{
	case 1:
		if(vector.at(0)==-1)
		{
			return PASS;// ���pass
		}
		else if(ISingleCard(vector))
		{
			return SINGLE;
		}
		else
		{
			return INVALID;
		}
		break;

	case 2:
		if(IsRocket(vector))
		{
			return ROCKET;
				
		}
		else if(IsCoupleCards(vector))
		{
			return COUPLE; 
		}
		else
		{
			return INVALID;  // �Ƿ�����
		}
		break;

	case 3:
		if(IsThreeCards(vector))
			return SANTIAO;
		else
			return INVALID;
		break;

	case 4:
		if(IsZhaDan(vector))
		{
			return ZHADAN;
		}
		else if(IsThree_One(vector))
		{
			return THREE_ONE; 
		}
		else 
			return INVALID;
		break;
	case 5:
		if(IsSingleJunko(vector))
		{
			return SINGLEJUNKO; 
		}
		else if(IsThree_Two(vector))
		{
			return THREE_TWO; 
		}
		else
			return INVALID;
		break;

	case 6:
		if(IsSingleJunko(vector))
		{
			return SINGLEJUNKO; 
		}
		else if(IsDualJunko(vector))
		{
			return DUALJUNKO;
		}
		else if(IsThree_Shun(vector))
		{
			return THREEJUNKO; 
		}
		else if(IsFour_Two(vector))
		{
			return FOUR_TWO; 
		}
		else
			return INVALID;
		break;

	case 7:
		if(IsSingleJunko(vector))
		{
			return SINGLEJUNKO;
		}
		else
			return INVALID;
		break;

	case 8:
		if(IsSingleJunko(vector))
		{
			return SINGLEJUNKO; 
		}
		else if(IsDualJunko(vector))
		{
			return DUALJUNKO; 
		}
		else if(IsThree_One(vector))
		{
			return THREEJUNKO_ONE; 
		}
		else if(IsFour_Two(vector))
		{
			return FOUR_TWO_COUPLE; 
		}
		else
			return INVALID;
		break;

	case 9:
		if(IsSingleJunko(vector))
		{
			return SINGLEJUNKO; 
		}
		else if(IsThree_Shun(vector))
		{
			return THREEJUNKO;
		}
		break;

	case 10:
		if(IsSingleJunko(vector))
		{
			return SINGLEJUNKO;
		}
		else if(IsDualJunko(vector))
		{
			return DUALJUNKO; 
		}
		else if(IsThree_Two(vector))
		{
			return THREEJUNKO_TWO; 
		}
		else
			return INVALID;
		break;

	case 11:
		if(IsSingleJunko(vector))
		{
			return SINGLEJUNKO; 
		}
		else 
			return INVALID;
		break;

	case 12:
		if(IsSingleJunko(vector))
		{
			return SINGLEJUNKO;
		}
		else if(IsDualJunko(vector))
		{
			return DUALJUNKO; 
		}
		else if(IsThree_Shun(vector))
		{
			return THREEJUNKO; 
		}
		else if(IsThree_One(vector))
		{
			return THREEJUNKO_ONE;
		}
		else
			return INVALID;
		break;

	case 13:

		return INVALID;
		break;

	case 14:
		if(IsDualJunko(vector))
		{
			return DUALJUNKO; 
		}
		else
			return INVALID;
		break;

	case 15:
		if(IsThree_Shun(vector))
		{
			return THREEJUNKO;
		}
		else if(IsThree_Two(vector))
		{
			return THREEJUNKO_TWO; 
		}
		else
			return INVALID;
		break;

	case 16:
		if(IsDualJunko(vector))
		{
			return DUALJUNKO;
		}
		else if(IsThree_One(vector))
		{
			return THREEJUNKO_ONE; 
		}
		break;

	case 17:
		return INVALID;// û��һ�γ�17�ŵ�����
		break;

	case 18:
		if(IsDualJunko(vector))
		{
			return DUALJUNKO; 
		}
		else if(IsThree_Shun(vector))
		{
			return THREEJUNKO;
		}
		else
		{
			return INVALID;
		}
		break;

	case 19:
		return INVALID;// û��һ�γ�19�ŵ�����
		break;

	case 20:
		return INVALID;// һ�γ�20��Ҫô�Ƿ���Ҫô����Ѿ�����������
		break;
	}	

	return INVALID;
}

/**  ���ݲ��е��±귵������ֵ���� 0 -> ÷��3���򷵻�����ֵΪ0 */
int DDZPlayer::getValue(int value)
{
	if(value<=52)
	{
		return value/4;
	}
	else
	{
		return 14;// ����
	}
}

/**���±�ת��Ϊ����ֵ����4,7ת��Ϊһ��4/4=1,7/4=1,��1��1, */
vector<unsigned> DDZPlayer::getCardsValue(vector<unsigned> vector)
{
	VECTORINT cardsList;
	for(size_t i=0;i<vector.size();i++)
	{
		int tmp_card=vector.at(i);

		cardsList.push_back(getValue(tmp_card));
	}

	return cardsList;
}

///** �������� p.p3_cardsList ���� */
//void DDZPlayer::sortVectorLowToHigh(Player p,int low,int high)
//{
//	if(low>=high)
//	{
//		return;
//	}
//
//	int first=low;
//	int last =high;
//
//	int key=p.p3_cardsList.at(first);
//	while(first<last)
//	{
//		while(first<last&&p.p3_cardsList.at(last)>=key)
//			--last;
//		p.p3_cardsList.at(first)=p.p3_cardsList.at(last);
//		while(first<last&&p.p3_cardsList.at(first)<=key)
//			++first;
//		p.p3_cardsList.at(last)=p.p3_cardsList.at(first);
//	}
//	p.p3_cardsList.at(first)=key;
//	sortVectorLowToHigh(p,low,first-1);
//	sortVectorLowToHigh(p,last+1,high);
//}

bool DDZPlayer::IsRocket(VECTORINT vector)
{
	bool flag = false;
	if(vector.size()==2&&vector[0]==13&&vector[1]==14)
	{
		flag = true;
	}

	return flag;
}

/** �ж�vector�Ƿ�Ϊը���������������ֵ���д洢  */
bool DDZPlayer::IsZhaDan(VECTORINT vector)
{
	bool flag=true;
	int tmp=vector.at(0);

	for(size_t i=1;i<vector.size();i++)
	{
		if(tmp!=vector[i])
		{
			flag=false;
		}
	}

	return flag;
}


unsigned DDZPlayer::getZhaDanValue(VECTORINT vector)
{
	if(vector.size()==4)
	{
		return vector[0];
	}
	else
	{
		return 60;
	}
}
/**�ж�vector�Ƿ�Ϊ���ƣ������������ֵ���д洢  */
bool DDZPlayer::ISingleCard(VECTORINT vector)
{
	bool flag = false;
	if(vector.size()==1&&vector[0]>=0&&vector[0]<=14)
	{
		flag = true;
	}

	return flag;
}

unsigned DDZPlayer::getSingleValue(vector<unsigned> vector)
{
	if(vector.size()>0)
	{
		return vector[0];
	}
	else
	{
		return 60;
	}
}

/**�ж�vector�Ƿ�Ϊ���ƣ������������ֵ���д洢  */
bool DDZPlayer::IsCoupleCards(VECTORINT vector)
{
	bool flag=true;
	unsigned tmp=vector[0];
	if(tmp!=vector[1])
	{
		flag = false;
	}

	return flag;
}

unsigned DDZPlayer::getCoupleValue(vector<unsigned> vector)
{
	if(vector.size()==2)
	{
		return vector[0];
	}
	else
	{
		return 60;
	}
}

/**�ж�vector�Ƿ�Ϊ�����������������ֵ���д洢 */
bool DDZPlayer::IsThreeCards(VECTORINT vector)
{
	bool flag=false;
	if(vector.size()==3&&vector[0]==vector[1]&&vector[1]==vector[2])
	{
		flag = true;
	}

	return flag;
}

unsigned DDZPlayer::getSanTiaoValue(vector<unsigned> vector)
{
	if(vector.size()>0)
	{
		return vector[0];
	}
	else
	{
		return 60;
	}
}

/** �����ź������򣩵�vector �ж��Ƿ�Ϊ��˳�ӣ������������ֵ���д洢  */
bool DDZPlayer::IsSingleJunko(VECTORINT vector)
{
	bool flag=true;
	for(size_t i=0;i<vector.size()-1;i++)
	{
		if(vector[i+1]-vector[i]!=1)
		{
			flag=false;
		}
	}

	return flag;
}

vector<unsigned> DDZPlayer::getSingleJunkoValue(VECTORINT vector)
{
	VECTORINT singleJunkoValue;

	singleJunkoValue.push_back(vector[0]);
	singleJunkoValue.push_back(vector[vector.size()-1]);

	return singleJunkoValue;
}

/** �����ź������򣩵�vector �ж��Ƿ�Ϊ˫˳�������������ֵ���д洢  */
bool DDZPlayer::IsDualJunko(VECTORINT vector)
{
	bool flag=true;

	for(size_t i=0;i<vector.size()-1;i++)
	{
		if(i%2==0)
		{
			if(vector.at(i)!=vector.at(i+1))
			{
				flag=false;
			}
		}

		if(i<vector.size()-2)
		{
			if(vector.at(i+2)-vector.at(i)!=1)
			{
				flag=false;
			}
		}
	}

	return flag;
}

VECTORINT DDZPlayer::getDualJunkoValue(VECTORINT vector)
{
	VECTORINT dualJunkoValue;

	dualJunkoValue.push_back(vector[0]);
	dualJunkoValue.push_back(vector[vector.size()-1]);

	return dualJunkoValue;
}

/** �ж�vector�Ƿ�Ϊ��˳�������������ֵ���д洢  */
bool DDZPlayer::IsThree_Shun(VECTORINT vector)
{
	VECTORINT tmp_vector;
	VECTORINT santiaos;
	bool flag = false;
	int tmp_three[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_three[vector.at(i)]++;//��¼��������
	}

	for(size_t j=0;j<13;j++)
	{
		if(tmp_three[j]==3)
		{
			santiaos.push_back(j);
		}
	}

	if(vector.size()/3==santiaos.size()&&IsSingleJunko(santiaos))
	{
		flag = true;
	}

	return flag;
	/*if(flag)
	{
		tmp_vector.push_back(1);	
		tmp_vector.push_back(tmp_vector1.at(0));
		tmp_vector.push_back(tmp_vector1.at(tmp_vector1.size()-1));
	}
	else
	{
		tmp_vector.push_back(0);
	}


	return tmp_vector;*/
}


VECTORINT DDZPlayer::getThree_ShunValue(VECTORINT vector)
{
	VECTORINT three_shunValue;

	three_shunValue.push_back(vector[0]);
	three_shunValue.push_back(vector[vector.size()-1]);

	return three_shunValue;
}

//void (^fackd)(int i);
/** �ж�vector�Ƿ�Ϊ����һ����˳������ �������������ֵ���д洢 */
bool DDZPlayer::IsThree_One(VECTORINT vector)
{
	VECTORINT tmp_vector;
	VECTORINT threeTiaos;//����������ֵ���д洢
	VECTORINT carryCards;//��������������ֵ���д洢
	bool flag = false;
	unsigned tmp_three[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_three[vector.at(i)]++;
	}

	for(size_t j=0;j<15;j++)
	{
		if(tmp_three[j]==3)
		{
			threeTiaos.push_back(j);
		}
		if(tmp_three[j]!=3&&tmp_three!=0)
		{
			for(size_t k=0;k<tmp_three[j];k++)
			{
				carryCards.push_back(j);
			}
		}
	}

	if(vector.size()/4==threeTiaos.size()&&IsSingleJunko(threeTiaos))
	{
		flag = true;
	}

	return flag;
}

VECTORINT DDZPlayer::getThree_OneValue(VECTORINT vector)
{
	VECTORINT three_OneValue;
	VECTORINT threeTiaos;//����������ֵ���д洢
	VECTORINT carryCards;//��������������ֵ���д洢
	bool flag = false;
	unsigned tmp_three[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_three[vector[i]]++;
	}

	for(size_t j=0;j<15;j++)
	{
		if(tmp_three[j]==3)
		{
			threeTiaos.push_back(j);
		}
		if(tmp_three[j]!=3&&tmp_three!=0)
		{
			for(size_t k=0;k<tmp_three[j];k++)
			{
				carryCards.push_back(j);
			}
		}
	}

	three_OneValue.push_back(threeTiaos[0]);
	three_OneValue.push_back(threeTiaos[threeTiaos.size()-1]);
	for(size_t i=0;i<carryCards.size();i++)
	{
		three_OneValue.push_back(carryCards[i]);
	}

	return three_OneValue;
}

/** �ж�vector�Ƿ�Ϊ����һ��(��˳��˫���������������ֵ���д洢  */
bool DDZPlayer::IsThree_Two(VECTORINT vector)
{
	VECTORINT tmp_vector;
	VECTORINT threeTiaos;
	VECTORINT carryCards;
	bool flag = false;
	int tmp_three[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_three[vector[i]]++;
	}

	for(size_t j=0;j<15;j++)
	{
		if(tmp_three[j]==3)
		{
			threeTiaos.push_back(j);//����������ֵ���д洢
		}
		if(tmp_three[j]==2)
		{
			carryCards.push_back(j);//��������������ֵ���д洢
		}
	}

	if(vector.size()/5==threeTiaos.size()&&threeTiaos.size()==carryCards.size()&&IsSingleJunko(threeTiaos))
	{
		flag = true;
	}

	return flag;
}

VECTORINT DDZPlayer::getThree_TwoValue(VECTORINT vector)
{
	VECTORINT three_TwoValue;
	VECTORINT threeTiaos;
	VECTORINT carryCards;
	bool flag = false;
	int tmp_three[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_three[vector[i]]++;
	}

	for(size_t j=0;j<15;j++)
	{
		if(tmp_three[j]==3)
		{
			threeTiaos.push_back(j);//����������ֵ���д洢
		}
		if(tmp_three[j]==2)
		{
			carryCards.push_back(j);//��������������ֵ���д洢
		}
	}

	three_TwoValue.push_back(threeTiaos[0]);
	three_TwoValue.push_back(threeTiaos[threeTiaos.size()-1]);
	
	for(size_t i=0;i<carryCards.size();i++)
	{
		three_TwoValue.push_back(carryCards[i]);
		three_TwoValue.push_back(carryCards[i]);
	}


	return three_TwoValue;
}
/** �ж�vector�Ƿ�Ϊ�Ĵ����������������ֵ���д洢  */
bool DDZPlayer::IsFour_Two(VECTORINT vector)
{
	VECTORINT tmp_vector;
	VECTORINT tmp_vector1;
	VECTORINT tmp_vector2;
	bool flag = false;
	unsigned tmp_four[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_four[vector.at(i)]++;
	}

	for(size_t j=0;j<15;j++)
	{
		if(tmp_four[j]==4)
		{
			tmp_vector1.push_back(j);
		}
		if(tmp_four[j]!=4&&tmp_four!=0)
		{
			for(size_t t=0;t<tmp_four[j];t++)
				tmp_vector2.push_back(j);
		}
	}

	if(vector.size()/6==tmp_vector1.size()&&(tmp_vector1.size()*2)==tmp_vector2.size()&&IsSingleJunko(tmp_vector1))
	{
		flag = true;
	}


	return flag;
}

VECTORINT DDZPlayer::getFour_TwoValue(VECTORINT vector)
{
	VECTORINT four_TwoValue;
	VECTORINT four_num;
	VECTORINT carryCards;
	unsigned tmp_four[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_four[vector.at(i)]++;
	}

	for(size_t j=0;j<15;j++)
	{
		if(tmp_four[j]==4)
		{
			four_num.push_back(j);
		}
		if(tmp_four[j]!=4&&tmp_four!=0)
		{
			for(size_t t=0;t<tmp_four[j];t++)
				carryCards.push_back(j);
		}
	}


	four_TwoValue.push_back(four_num[0]);
	for(size_t i=0;i<carryCards.size();i++)
	{
		four_TwoValue.push_back(carryCards[i]);
	}

	return four_TwoValue;
}

/** �ж�vector�Ƿ�Ϊ�Ĵ����ԣ������������ֵ���д洢  */
bool DDZPlayer::IsFour_TwoCouple(VECTORINT vector)
{
	VECTORINT tmp_vector;
	VECTORINT four_num;
	VECTORINT carryCards;
	bool flag = false;
	int tmp_three[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_three[vector.at(i)]++;
	}

	for(size_t j=0;j<15;j++)
	{
		if(tmp_three[j]==4)
		{
			four_num.push_back(j);
		}
		if(tmp_three[j]==2)
		{
			carryCards.push_back(j);
		}
	}

	if(vector.size()/8==four_num.size()&&(four_num.size()*2)==carryCards.size())
	{
		flag = true;
	}

	if(vector.size()==2)//�ĸ����ĸ�����2222��JJ��JJ���������Ͱ��������
	{
		flag=true;
	}


	return flag;
}


VECTORINT DDZPlayer::getFour_TwoCoupleValue(VECTORINT vector)
{
	VECTORINT four_TwoCoupleValue;
	VECTORINT four_num;
	VECTORINT carryCards;
	int tmp_three[15]={0};
	for(size_t i=0;i<vector.size();i++)
	{
		tmp_three[vector.at(i)]++;
	}

	for(size_t j=0;j<15;j++)
	{
		if(tmp_three[j]==4)
		{
			four_num.push_back(j);
		}
		if(tmp_three[j]==2)
		{
			carryCards.push_back(j);
		}
	}

	if(four_num.size()==1)
	{
		four_TwoCoupleValue.push_back(four_num[four_num.size()-1]);
		for(size_t i=0;i<carryCards.size();i++)
		{
			four_TwoCoupleValue.push_back(carryCards[i]);
			four_TwoCoupleValue.push_back(carryCards[i]);
		}
	}
	else if(four_num.size()==2)
	{
		four_TwoCoupleValue.push_back(four_num[four_num.size()-1]);

		for(size_t tmp=0;tmp<4;tmp++)
		{
			four_TwoCoupleValue.push_back(four_num[four_num.size()-2]);
		}
		
		for(size_t i=0;i<carryCards.size();i++)
		{
			four_TwoCoupleValue.push_back(carryCards[i]);
			four_TwoCoupleValue.push_back(carryCards[i]);
		}
	}

	return four_TwoCoupleValue;
}




/** ѡ������ */
VECTORINT DDZPlayer::sortCardsVector(VECTORINT vector)
{	
	for(size_t i=0;i<vector.size();i++)
		{
			int min=60;
			int index;
			for(size_t j=i;j<vector.size();j++)
			{
				if(min>vector.at(j))
				{
					min=vector.at(j);
					index=j;
				}
			}
			vector.at(index)=vector.at(i);
			vector.at(i)=min;
		}

	return vector;
}

VECTORINT DDZPlayer::CardsToIndex(VECTORINT v,Player p)
{
	VECTORINT tmp_vector1;
	for(size_t i=0;i<v.size();i++)
	{
		p.p3_EachCardNum[v.at(i)]--;
		for(size_t j=0;j<p.p3_cardsList.size();j++)
		{
			if(p.p3_cardsList.at(j)==53)
			{
				if(v.at(i)==14)// ����Ϊ����ʱ���⴦��
				{
					VECTORINT::iterator it = p.p3_cardsList.begin()+j;
					tmp_vector1.push_back(p.p3_cardsList.at(j));
					p.p3_cardsList.erase(it);
					break;
				}
			}		
			else if(p.p3_cardsList.at(j)/4==v.at(i))
			{
				VECTORINT::iterator it = p.p3_cardsList.begin()+j;
				tmp_vector1.push_back(p.p3_cardsList.at(j));
				p.p3_cardsList.erase(it);
				break;
			}
		}
	}	

	return tmp_vector1;
}