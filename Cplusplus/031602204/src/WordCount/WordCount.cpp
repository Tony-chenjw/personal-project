// wordcount.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main(int argc, char **argv)
{
	charcount(argv[1]);
	wordcount(argv[1]);
	linecount(argv[1]);
	wordmax(argv[1]);

	return 0;
}
