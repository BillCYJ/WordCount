#include <iostream>
#include <fstream>
using namespace std;

int charsCount = 0;//�ַ�����
int wordsCount = 0;//���ʸ���
int linesCount = 0;//����
FILE *file;

int countFunc(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	countFunc(argc, argv);
	getchar();
	return 0;
}

//�Ƿ��ǿո�
bool isSpace(char c)
{
	if (c == ' ')
		return true;
	return false;
}

//�Ƿ���ˮƽ�Ʊ��
bool isTab(char c)
{
	if (c == '\t')
		return true;
	return false;
}

//�Ƿ��ǻ��з�
bool isEndline(char c)
{
	if (c == '\n')
		return true;
	return false;
}

//�Ƿ���Ӣ�Ķ���
bool isComma(char c)
{
	if (c == ',')
		return true;
	return false;
}

//�ǲ��Ƿָ���
bool isSep(char c)
{
	if ( c == ' ' || c == ',' || c == '\t' || c == '\n')
		return true;
	return false;
}

//ͳ�Ƶ��������ַ���������
void CountWord()
{
	charsCount = 0,wordsCount = 0,linesCount = 0;
	char c;
	//fgetc�����������ļ�ĩβ���߶�ȡ����ʱ����EOF
	while ((c = fgetc(file)) != -1) //ѭ����ȡ�����ı�����ַ�
	{
		charsCount++;//�ַ���+1
		if (!isSep(c)) //���Ƿָ����Ļ����Ǿ��ǵ��ʵ�һ���ַ�
		{
			wordsCount++;//������+1
			while ((c = fgetc(file)) != -1) //ѭ����ȡĳ����������ַ�
			{
				charsCount++;//�ַ���+1
				if (isEndline(c))//����
				{
					linesCount++;//����+1
					break;
				}
				else if (isSpace(c) || isComma(c) || isTab(c))
				{
					break;//�õ��ʽ�����
				}
			}
		}
		else if (isEndline(c))//�Ƿָ�������Ϊ���з�
			linesCount++;//����+1
	}

	if (charsCount != 0)
		linesCount++;//���һ��û�л��з���ҲҪ���ϸ���
}

//�ļ����������
int countFunc(int argc, char *argv[])
{
	int _cIndex = 0, _wIndex = 0, _lIndex = 0, _oIndex = 0;
	char* outputFile;//������ļ���
	char temp[11]= "result.txt";//Ĭ�ϵ�������ļ���
	outputFile = temp;
	char* inputFile = nullptr;
	for (int i = 0; i < argc; i++)//����ÿ������
	{
		//strcmp�������ַ���1���ַ���2������ֵ��0
		if (strcmp(argv[i], "-o") == 0)//�������Ϊ"-o"
		{
			if (i == 0)
			{
				cout << "No exe" << endl;
				return 0;
			}
			else if (_oIndex == 0)
				_oIndex = i;
			else
			{
				cout << "Repeated parameters" << endl;
				return 0;
			}

			if (i <= argc - 2)//����Ϊ���һ������
				outputFile = argv[i + 1];//-o�����Ǹ�����������ļ���
			else//��������һ���������ͱ���
			{
				cout << "No output file" << endl;
				return 0;
			}
		}
		else if (strcmp(argv[i], "-c") == 0)//�������Ϊ"-c"
		{
			if (i == 0)
			{
				cout << "No exe" << endl;
				return 0;
			}
			else if (_cIndex == 0)
				_cIndex = i;
			else
			{
				cout << "Repeated parameters" << endl;
				return 0;
			}
		}
		else if (strcmp(argv[i], "-w") == 0)//�������Ϊ"-w"
		{
			if (i == 0)
			{
				cout << "No exe" << endl;
				return 0;
			}
			else if (_wIndex == 0)
				_wIndex = i;
			else
			{
				cout << "Repeated parameters" << endl;
				return 0;
			}

		}
		else if (strcmp(argv[i], "-l") == 0)//�������Ϊ"-l"
		{
			if (i == 0)
			{
				cout << "No exe" << endl;
				return 0;
			}
			else if (_lIndex == 0)
				_lIndex = i;
			else
			{
				cout << "Repeated parameters" << endl;
				return 0;
			}

		}
		else if (i != 0 && i <= 4 && argv[i][0] != '-'&& inputFile == nullptr)//�������Ϊ����ļ���
		{
			inputFile = argv[i];
		}
	}

	//-o��Ϊ��һ�����������ǳ�������ļ���������һ������
	if (_oIndex != 0 && (_oIndex < _cIndex || _oIndex < _wIndex || _oIndex < _lIndex))
	{
		cout << "-o should be the last parameter" << endl;
		return 0;
	}

	if (inputFile == nullptr)
	{
		cout << "No input file" << endl;
		return 0;
	}

	file = fopen(inputFile, "r");//��ȡinput file
	if (file == nullptr)
	{
		cout << "Can not open input file." << endl;
		return 0;
	}
	CountWord();
	fclose(file);//�ر�input file
	
	//�����ָ�����ļ�outputFile
	fstream resFile;
	resFile.open(outputFile, ios_base::out);//�򿪸��ļ�
	for (int i = 0; i <= argc-1; i++)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			cout << "charsCount:" << charsCount << endl;
			if (resFile.is_open())
			{
				resFile << inputFile << ", �ַ�����" << charsCount << "\n" << endl;
			}
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			cout << "wordsCount:" << wordsCount << endl;
			if (resFile.is_open())
			{
				resFile << inputFile << ", ��������" << wordsCount << "\n" << endl;
			}
		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			cout << "linesCount:" << linesCount << endl;
			if (resFile.is_open())
			{
				resFile << inputFile << ", ������" << linesCount << "\n" << endl;
			}
		}
		else if (argv[i][0] == '-' && strcmp(argv[i], "-o") != 0)
		{
			cout << "Error parameter" << endl;
			return 0;
		}
	}
	resFile.close();
	return 0;
}