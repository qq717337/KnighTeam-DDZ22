#include "VectorUtil.h"
#include<vector>

VectorUtil::VectorUtil(void)
{
}


VectorUtil::~VectorUtil(void)
{
}

/** ȡvector����Ԫ��,��index������
*	@index   ��ʼ����
*	@vi	     Ŀ��vector
*/
vector<unsigned> VectorUtil::subVector(unsigned index,vector<unsigned> vi)
{
	vector<unsigned> back_vi;
	try {
		for(unsigned i=index;i<vi.size();i++)
		{
			back_vi.push_back(vi.at(i));
		}
	}
	catch(exception e)
	{
		cout<<"subvector1����Խ���쳣"<<endl;
	}

	return back_vi;
}

/** ȡvector����Ԫ��
*	@start_i ��ʼ����
*	@end_i   ��������
*	@vi	     Ŀ��vector
*/
vector<unsigned> VectorUtil::subVector(unsigned start_i,unsigned end_i,vector<unsigned> vi)
{
	vector<unsigned> back_vi;
	try {
		for(unsigned i=start_i;i<=end_i;i++)
		{
			back_vi.push_back(vi.at(i));
		}
	}catch(exception e)
	{
		cout<<"subvector2����Խ���쳣"<<endl;
	}

	return back_vi;
}

bool VectorUtil::isContains(vector<unsigned> vi,unsigned n)
{
	for(size_t i=0;i<vi.size();i++)
	{
		if(vi[i]==n)
		{
			return true;
		}
	}

	return false;
}

bool VectorUtil::IsEqualVector(vector<unsigned> v1, vector<unsigned> v2)
{
	unsigned len1 = v1.size();
	unsigned len2 = v2.size();

	if (len1 != len2)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < len1; i++)
		{
			if (v1[i] != v2[i])
			{
				return false;
			}
		}
	}

	return true;
}