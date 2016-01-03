#include "Test.h"

#include "Data.h"
#include "Series.h"
#include "Area.h"
#include "Grid.h"
#include "Plot.h"
#include "Box.h"

std::vector<Test *> *g_tests;

Test::Test()
{
}


Test::~Test()
{
}

bool Test::PerformTest()
{
	printf("\nTEST: %s ...\n", test_name);
	bool result;
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	result = DoTest();
	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		result = false;
		printf("leak detected\n");
		_CrtMemDumpStatistics(&s3);
	}

	if (result)
	{
		printf("RESULT: passed\n");
	}
	else
	{
		printf("RESULT: error\n");
	}
	return result;
}

void Test::AddTests()
{
	g_tests = new std::vector<Test *>();
	g_tests->push_back(new TestData());
	g_tests->push_back(new TestSeries2D());
	g_tests->push_back(new TestSeries2DwithData());
	g_tests->push_back(new TestArea());
	g_tests->push_back(new TestAreawithSeries());
	g_tests->push_back(new TestPlot());
	g_tests->push_back(new TestPlotWithArea());
}

void Test::DestroyTests()
{
	for (auto test : *g_tests)
		delete test;

	delete g_tests;
}



bool TestData::DoTest()
{
	DataTyped<double> *data;
	data = new DataTyped<double>(1000, "data");

	delete data;
	return true;
}

bool TestSeries2D::DoTest()
{
	Series *serie;
	serie = new Series2D("new series");

	delete serie;
	return true;
}

bool TestSeries2DwithData::DoTest()
{
	Series *serie;
	serie = new Series2D("new series");

	DataNoType *xdata, *ydata;
	xdata = new DataTyped<double>(100, "x-data");
	ydata = new DataTyped<double>(100, "y-data");

	serie->SetData(xdata, AXIS_X);
	serie->SetData(ydata, AXIS_Y);

	//delete ydata;
	delete xdata;
	delete serie;
	return true;
}

bool TestArea::DoTest()
{
	Area2D *area;
	area = new Area2D();


	delete area;
	return true;
}

bool TestAreawithSeries::DoTest()
{
	Area2D *area;
	area = new Area2D();

	Series2D *series1, *series2;
	series1 = new Series2D("series 1");
	series2 = new Series2D("series 2");

	Grid *grid;
	grid = new Grid(area);

	area->AddSeries(series1);
	area->AddSeries(series2);

	delete series1;
	delete grid;

	grid = new Grid(area);
	delete area;
	return true;
}

bool TestPlot::DoTest()
{
	Plot *plot;
	plot = new Plot();


	delete plot;
	return true;
}

bool TestPlotWithArea::DoTest()
{
	Plot *plot;
	plot = new Plot();

	Area *area = new Area2D();

	Box *box1, *box2;
	box1 = new Box(plot);
	
	box2 = new Box(plot);

	Series *series;
	series = new Series2D("Series");

	DataTyped<int> *xdata;
	xdata = new DataTyped<int>();

	series->SetData(xdata, AXIS_X);

	area->AddSeries(series);
	plot->AddArea(area);

	delete box1;


	delete plot;

	return true;
}
