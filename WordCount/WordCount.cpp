#include <iostream>
#include <fstream>
using namespace std;

int charsCount = 0;//字符个数
int wordsCount = 0;//单词个数
int linesCount = 0;//行数
FILE *file;

int countFunc(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	countFunc(argc, argv);
	getchar();
	return 0;
}

//是否是空格
bool isSpace(char c)
{
	if (c == ' ')
		return true;
	return false;
}

//是否是水平制表符
bool isTab(char c)
{
	if (c == '\t')
		return true;
	return false;
}

//是否是换行符
bool isEndline(char c)
{
	if (c == '\n')
		return true;
	return false;
}

//是否是英文逗号
bool isComma(char c)
{
	if (c == ',')
		return true;
	return false;
}

//是不是分隔符
bool isSep(char c)
{
	if ( c == ' ' || c == ',' || c == '\t' || c == '\n')
		return true;
	return false;
}

//统计单词数、字符数、行数
void CountWord()
{
	charsCount = 0,wordsCount = 0,linesCount = 0;
	char c;
	//fgetc函数：读到文件末尾或者读取出错时返回EOF
	while ((c = fgetc(file)) != -1) //循环读取整个文本里的字符
	{
		charsCount++;//字符数+1
		if (!isSep(c)) //不是分隔符的话，那就是单词的一个字符
		{
			wordsCount++;//单词数+1
			while ((c = fgetc(file)) != -1) //循环读取某个单词里的字符
			{
				charsCount++;//字符数+1
				if (isEndline(c))//新行
				{
					linesCount++;//行数+1
					break;
				}
				else if (isSpace(c) || isComma(c) || isTab(c))
				{
					break;//该单词结束了
				}
			}
		}
		else if (isEndline(c))//是分隔符，且为换行符
			linesCount++;//行数+1
	}

	if (charsCount != 0)
		linesCount++;//最后一行没有换行符，也要算上该行
}

//文件的输入输出
int countFunc(int argc, char *argv[])
{
	int _cIndex = 0, _wIndex = 0, _lIndex = 0, _oIndex = 0;
	char* outputFile;//输出的文件名
	char temp[11]= "result.txt";//默认的输出的文件名
	outputFile = temp;
	char* inputFile = nullptr;
	for (int i = 0; i < argc; i++)//遍历每个参数
	{
		//strcmp函数：字符串1＝字符串2，返回值＝0
		if (strcmp(argv[i], "-o") == 0)//如果参数为"-o"
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

			if (i <= argc - 2)//不能为最后一个参数
				outputFile = argv[i + 1];//-o后面那个参数是输出文件名
			else//如果是最后一个参数，就报错
			{
				cout << "No output file" << endl;
				return 0;
			}
		}
		else if (strcmp(argv[i], "-c") == 0)//如果参数为"-c"
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
		else if (strcmp(argv[i], "-w") == 0)//如果参数为"-w"
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
		else if (strcmp(argv[i], "-l") == 0)//如果参数为"-l"
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
		else if (i != 0 && i <= 4 && argv[i][0] != '-'&& inputFile == nullptr)//如果参数为输出文件名
		{
			inputFile = argv[i];
		}
	}

	//-o不为第一个参数，且是除了输出文件名外的最后一个参数
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

	file = fopen(inputFile, "r");//读取input file
	if (file == nullptr)
	{
		cout << "Can not open input file." << endl;
		return 0;
	}
	CountWord();
	fclose(file);//关闭input file
	
	//输出到指定的文件outputFile
	fstream resFile;
	resFile.open(outputFile, ios_base::out);//打开该文件
	for (int i = 0; i <= argc-1; i++)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			cout << "charsCount:" << charsCount << endl;
			if (resFile.is_open())
			{
				resFile << inputFile << ", 字符数：" << charsCount << "\n" << endl;
			}
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			cout << "wordsCount:" << wordsCount << endl;
			if (resFile.is_open())
			{
				resFile << inputFile << ", 单词数：" << wordsCount << "\n" << endl;
			}
		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			cout << "linesCount:" << linesCount << endl;
			if (resFile.is_open())
			{
				resFile << inputFile << ", 行数：" << linesCount << "\n" << endl;
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