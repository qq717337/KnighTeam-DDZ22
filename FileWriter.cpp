#include "FileWriter.h"
#include "string.h"


FileWriter::FileWriter(void)
{
}

FileWriter::~FileWriter(void)
{
}

FileWriter::FileWriter(string filePath)
{
	this->filePath=filePath;
}


void FileWriter::WriteToFile(vector<CARDSMOVE> moves,CARDSMOVE bestMove)
{
	fstream fout=fstream(filePath,ios::app);

	for(unsigned i=0;i<moves.size();i++)
	{
		fout<<"\t\t";
		for(unsigned j=0;j<moves.at(i).cards.size();j++)
		{
			fout<<moves.at(i).cards.at(j)<<" ";
		}		
		fout<<moves.at(i).cardsType<<"\t\t";
		fout<<"��ֵ�� "<<moves.at(i).score;
		fout<<endl;		
	}
	fout<<"\t\t�����߲���";
	for(unsigned j=0;j<bestMove.cards.size();j++)
		{
			fout<<bestMove.cards.at(j)<<" ";
		}
	fout<<bestMove.score<<endl;
	fout<<"\t\t================================="<<endl;
	fout.flush();
	fout.close();
}


void FileWriter::CombsToFile(CombsLib combs)
{
	fstream fout=fstream(filePath,ios::app);

	for(size_t i=0;i<combs.size();i++)
	{
		fout<<"\t\t��� "<<i<<endl;
		for(size_t j=0;j<combs[i].moves.size();j++)
		{
			fout<<"\t\t";
			for(size_t k=0;k<combs[i].moves[j].cards.size();k++)
			{
				fout<<combs[i].moves[j].cards.at(k)<<" ";
			}
			fout<<endl;
		}

		fout<<endl<<endl;
	}

	fout.flush();
	fout.close();
}

void FileWriter::writeOrderFromFatherExe(char *cInMessage)
{
	fstream fout = fstream(filePath, ios::app);
	string a = string(cInMessage);
	fout << a << endl;
	fout.flush();
	fout.close();
}

/**
*	��������Ϣд��error.txt��
*
*/
void FileWriter::writeErrorInfo(string errorInfo)
{
	fstream fout = fstream("error.txt", ios::app);
	
	fout << errorInfo << endl;
	fout.flush();
	fout.close();
}