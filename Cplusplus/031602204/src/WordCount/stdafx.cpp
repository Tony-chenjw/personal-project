// stdafx.cpp : 只包括标准包含文件的源文件
// wordcount.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

int charcount(char *tx)
{
	FILE *fp;
	fopen_s(&fp, tx, "r");
	ofstream outf("result.txt");

	int charcnt = 0;

	if (fp == NULL)
	{
		cout << "该文件不存在！" << endl;
		return 0;
	}

	while (!feof(fp))
	{
		char c = getc(fp);
		charcnt++;
	}
	outf << "characters: " << charcnt << endl;
	return charcnt;
}

int linecount(char *tx)
{
	FILE *fp;
	fopen_s(&fp, tx, "r");
	ofstream outf("result.txt", ios::app);

	int flag = 1;
	int linecnt = 0;
	char c;

	while (!feof(fp))
	{
		c = getc(fp);

		if ((c != 10) && (c != ' ') && (c != EOF) && (flag == 1))
		{
			linecnt++;
			flag = 0;
		}

		if (c == 10)
		{
			flag = 1;
		}

	}
	outf << "lines: " << linecnt << endl;
	return linecnt;
}

void  sor(wd *f, int n)
{
	int w;
	for (int i = 0; i<n - 1; i++)
		for (int j = 0; j<n - i - 1; j++)
		{
			w = 0;
			while (f[j].s[w] == f[j + 1].s[w])
				w++;
			if (f[j].s[w] > f[j + 1].s[w])
				swap(f[j], f[j + 1]);
		}
}

int wordcount(char *tx)
{
	FILE *fp;
	fopen_s(&fp, tx, "r");
	ofstream outf("result.txt", ios::app);

	int wordcnt = 0;
	int k, i, j;

	while (!feof(fp))
	{
		char c = getc(fp);
		if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))//可能是单词 
		{
			k = 0;//从第0位开始判断
			while ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z') || (c >= '0'&&c <= '9'&&k >= 4))//继续后几位的验证 
			{
				if (c >= 'A'&&c <= 'Z')
				{
					c = c + 32;
				}
				temp.s[k] = c;
				k++;

				c = getc(fp);
			}
			temp.s[k] = '\0';//结束标识 
			k++;//此词位数+1

			j = n;

			if (strlen(temp.s) >= 4)//确保大于4位英文字母 
			{
				wordcnt++;
				temp.frq = 1;//词频置1

				for (i = 0; i < j; i++)
				{
					if (strcmp(temp.s, word[i].s) == 0)//归于之前的 
					{
						word[i].frq++;
						break;
					}
				}

				if (n == 0 || i == j)//把新的空间给新单词
				{
					word[n] = temp;
					n++;
				}
			}
		}
	}
	outf << "words: " << wordcnt << endl;
	return wordcnt;
}

void wordmax(char *tx)
{
	FILE *fp;
	fopen_s(&fp, tx, "r");
	ofstream outf("result.txt", ios::app);

	int  i, j;

	sor(word, n);
	wd max[10];

	for (i = 0; i < 10; i++)//初始化前十名
	{
		max[i] = word[i];
	}

	for (j = 0; j < 10; j++)//前十名排序 
	{
		for (i = 0; i < 10 - j - 1; i++)
		{
			if (max[i].frq < max[i + 1].frq)
			{
				swap(max[i], max[i + 1]);
			}
		}
	}

	for (i = 10; i < n; i++)//找后面的数 
	{
		if (max[9].frq < word[i].frq)//比最小的还大 
		{
			int a = 8;
			while (max[a].frq < word[i].frq&&a >= 0)
			{
				a--;//定位到第一个比自己大的word
			}

			for (j = 9; j > a + 1; j--)
			{
				max[j] = max[j - 1];//前面的数后移一位 
			}
			if (a < 0)//说明word[i]比max[0]大
				max[0] = word[i];
			else
				max[j] = word[i];
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (strlen(max[i].s) == 0)
			continue;
		outf << "<" << max[i].s << ">" << ":" << max[i].frq << endl;
	}
	outf.close();
}

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用
