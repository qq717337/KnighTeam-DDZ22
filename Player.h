#pragma once
#include<vector>
#include "define.h"

using namespace std;

class Player
{
	

public:
	Player(void);
	virtual ~Player(void);

	/*******************���p1 ********************/
	static vector<CARDSMOVE> p1_yiChu;  //	  �ѳ�����
	static vector<CARDSMOVE> p1_general;//	  �ѳ����ƻ�Ϊ��������ֵ���洢����
	static int p1_front;									//    �ϼ�
	static int p1_next;										//    �¼�
	static vector<unsigned> p1_cardsList;		//    �����Ƶ���Ϣ
	static int p1_bid;										//    �з�
	static int p1_pos;										//	  ���λ��	
	static int p1_cardsNum;							//	  ��������Ƶ�����
	static bool p1_IsLandlord;						//	  ����Ƿ�Ϊ����
	static unsigned p1_EachCardNum[15];     //    �������3~K��A��2��С��������15����������
	static double p1_Membership[54];			//    �����ȱ�
	static int p1_manyCards[14];					//    �϶����
	static int p1_fewCards[14];						//	  ���ٵ���
	/***********************************************/


	/********************���p2 ********************/
	static vector<CARDSMOVE> p2_yiChu;   //	    �ѳ�����
	static vector<CARDSMOVE> p2_general;//	    �ѳ����ƻ�Ϊ��������ֵ���洢����
	static int p2_front;									 //    �ϼ�
	static int p2_next;										 //    �¼�
	static vector<unsigned> p2_cardsList;	     //    �����Ƶ���Ϣ
	static int p2_bid;										 //    �з�
	static int p2_pos;									     //	   ���λ��	
	static int p2_cardsNum;							 //	   ��������Ƶ�����
	static bool p2_IsLandlord;						 //	   ����Ƿ�Ϊ����
	static unsigned p2_EachCardNum[15];      //    �������3~K��A��2��С��������15����������
	static double p2_Membership[54];			 //    �����ȱ�
	static int p2_manyCards[14];					//     �϶����
	static int p2_fewCards[14];						//	   ���ٵ���
	/************************************************/


	/*****************���p3,���ҷ� **************/
	static vector<CARDSMOVE> p3_yiChu;   //	    �ѳ�����
	static vector<CARDSMOVE> p3_general; //	    �ѳ����ƻ�Ϊ��������ֵ���洢����
	static int p3_front;							  //    �ϼ�
	static int p3_next;								  //    �¼�
	static vector<unsigned> p3_cardsList;			  //    �����Ƶ���Ϣ
	static int p3_bid;								  //    �з�
	static int p3_pos;								  //	���λ��	
	static int p3_cardsNum;						      //	��������Ƶ�����
	static bool p3_IsLandlord;						  //	����Ƿ�Ϊ����
	static unsigned p3_EachCardNum[15];               //    �ҷ�����3~K��A��2��С��������15����������
	static int p3_manyCards[14];					  //     �϶����
	static int p3_fewCards[14];						  //	 ���ٵ���
	static bool p3_canPlayOver;						  //	 �Ƿ�ﵽ��Ӯ״̬
	static vector<CARDSMOVE> p3_comb;					  //	 ��Ӯ����߲�
	
	static unsigned remaining[15];							   //     ʣ�����ͱ�
	static vector<CARDSMOVE> p3_allMoves;//     �������ƴ��ڵ��߲��洢����
	static int p3_IsExistCardsType[14];				//    �����Ƿ����14������
	static CombsLib p3_combs;							//    ��Ͽ�
	static CARDSMOVE firstMove;					//    ����������
	static int firstPlayer;									   //     ÿһ�����ķ��������ƣ�1->���p1;2->���p2; 3->�ҷ�
	static CARDSMOVE lastMove;					   //     ��¼��һ�ηǿճ���
	static int lastPlayer;									   //     ��¼��һ�ηǿճ������
	/**************************************************/

};

