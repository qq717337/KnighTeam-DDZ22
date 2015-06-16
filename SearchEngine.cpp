#include "SearchEngine.h"
#include<vector>
#include"define.h"
#include "time.h"

using namespace std;

CSearchEngine::CSearchEngine(void)
{
	
}


CSearchEngine::~CSearchEngine(void)
{
	
}


/** �ж��ƾ��Ƿ����
**  @ nDepthΪ�������
**  ��Ϊ�ҷ�ʤ�����ؼ���ֵ����֮�򷵻ؼ�Сֵ���ƾ�δ�������� 0
**  (�ر�ע�ͣ��˳���Ĭ�������ҷ�Ϊ���p3)
*/
int CSearchEngine::IsGameOver(Player p,int nDepth)
{
	int p1_cardsNum = p.p1_cardsNum;
	int p2_cardsNum = p.p2_cardsNum;
	int p3_cardsNum = p.p3_cardsNum;

	if(p3_cardsNum==0)// �ҷ������ƣ�ֱ�ӷ��ؼ���ֵ
	{
		return 19990+nDepth;// ���ؼ���ֵ
	}

	if(p.p3_IsLandlord==true)// �ҷ�Ϊ����
	{
		if(p1_cardsNum==0||p2_cardsNum==0)// ���p1,p2����������
		{
			return -19990-nDepth;// ���ؼ�Сֵ
		}
	}
	else                     // �ҷ���Ϊ����
	{
		if(p1_cardsNum==0)// ���p1����������
		{
			if(p.p1_IsLandlord)// ���p1Ϊ����
			{
				return -19990-nDepth;// ���ؼ�Сֵ
			}
			else
			{
				return 19990+nDepth;// ���ؼ���ֵ
			}
		}

		if(p2_cardsNum==0)// ���p2����������
		{
			if(p.p2_IsLandlord)// ���p2Ϊ����
			{
				return -19990-nDepth;// ���ؼ�Сֵ
			}
			else
			{
				return 19990+nDepth;// ���ؼ���ֵ
			}
		}
	}


	return 0;
}



/** ���ݳ����Ƴ����е���
*   @ move ���� @ whoseGo �ֵ�˭����
*   whoseGo��ֵ���� ������4��3��2��1. �ҷ�ֵ%3==0
*/
void CSearchEngine::MakeMove(CARDSMOVE move,Player p,int whoseGo)
{
	 if(whoseGo%3==0)   // �ҷ�
	 {
		 if(move.cardsType!=-1)
		 {
			 for(size_t i=0;i<move.cards.size();i++)
			 {
					p.p3_EachCardNum[move.cards.at(i)]--;
			 }
		 p.p3_cardsNum-=(move.cards.size());		// ��ȥ��������
		 }
		 p.p3_general.push_back(move);
	 }
	 else if(whoseGo%3==2)  // ���p1�����ҷ��¼�
	 {
		 if(move.cardsType!=-1)
		 {
			 for(size_t i=0;i<move.cards.size();i++)
			 {
				 p.p1_EachCardNum[move.cards.at(i)]--;
			 }

			 p.p1_cardsNum-=(move.cards.size());		// ��ȥ��������
		 }
		 p.p1_general.push_back(move);
	 }
	 else					// ���p2�����ҷ��ϼ�
	 {
		  if(move.cardsType!=-1)
		  {
				 for(size_t i=0;i<move.cards.size();i++)
				 {
					 p.p2_EachCardNum[move.cards.at(i)]--;
				 }

				 p.p2_cardsNum-=(move.cards.size());		// ��ȥ��������
		  }
		 p.p2_general.push_back(move);
	 }

	 
}

void CSearchEngine::UnMakeMove(CARDSMOVE move,Player p,int whoseGo)
{
	vector<CARDSMOVE>::iterator it;
	if(whoseGo%3==0)  // �ҷ�
	 {
		 if(move.cardsType!=-1)
		 {
			 for(size_t i=0;i<move.cards.size();i++)
			 {
				 p.p3_EachCardNum[move.cards.at(i)]++;
			 }
	 
			 p.p3_cardsNum+=(move.cards.size());		// �ָ���������
		 }
		 p.p3_general.erase(p.p3_general.end()-1);
	 }
	 else if(whoseGo%3==2)  // ���p1�����ҷ��¼�
	 {
		 if(move.cardsType!=-1)
		 {
			 for(size_t i=0;i<move.cards.size();i++)
			 {
				 p.p1_EachCardNum[move.cards.at(i)]++;
			 }

			 p.p1_cardsNum+=(move.cards.size());		// �ָ���������
		 }
		 p.p1_general.erase(p.p1_general.end()-1);
	 }
	 else					// ���p2�����ҷ��ϼ�
	 {
		 if(move.cardsType!=-1)
		 {
			 for(size_t i=0;i<move.cards.size();i++)
			 {
				 p.p2_EachCardNum[move.cards.at(i)]++;
			 }

			 p.p2_cardsNum+=(move.cards.size());		    // �ָ���������
		 }
		 p.p2_general.erase(p.p2_general.end()-1);//�ָ��߲�
	 }
}
