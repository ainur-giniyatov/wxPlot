// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "stdafx.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "Test.h"

extern std::vector<Test *> *g_tests;
int main(int argc, char **argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Tests for plot classes\n");
	
	Test::AddTests();

	for (auto test : *g_tests)
	{
		test->PerformTest();
	}

	Test::DestroyTests();
	printf("Done.\n");
	getchar();
	_CrtDumpMemoryLeaks();
    return 0;
}

