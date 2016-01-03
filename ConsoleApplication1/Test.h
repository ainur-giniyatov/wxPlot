#pragma once
#include <vector>

class Test
{
public:
	Test();
	virtual ~Test();

	const char *GetTestName() { return test_name; }
	bool PerformTest();
	static void AddTests();
	static void DestroyTests();
protected:
	virtual bool DoTest() = 0;
	const char *test_name;

private:
};


class TestData : public Test
{
public:
	TestData() { test_name = "Test Data Class"; };

private:
	// Inherited via Test
	virtual bool DoTest() override;

};

class TestSeries2D : public Test
{
public:
	TestSeries2D() { test_name = "Test Series2D Class"; };

private:
	// Inherited via Test
	virtual bool DoTest() override;

};

class TestSeries2DwithData : public Test
{
public:
	TestSeries2DwithData() { test_name = "Test Series2D Class with Data added"; };

private:
	// Inherited via Test
	virtual bool DoTest() override;

};

class TestArea : public Test
{
public:
	TestArea() { test_name = "Test Area2D Class"; };

private:
	// Inherited via Test
	virtual bool DoTest() override;

};

class TestAreawithSeries : public Test
{
public:
	TestAreawithSeries() { test_name = "Test Area2D Class with Series2D added"; };

private:
	// Inherited via Test
	virtual bool DoTest() override;

};

class TestPlot : public Test
{
public:
	TestPlot() { test_name = "Test Plot Class"; };

private:
	// Inherited via Test
	virtual bool DoTest() override;

};

class TestPlotWithArea : public Test
{
public:
	TestPlotWithArea() { test_name = "Test Plot Class with Area added"; };

private:
	// Inherited via Test
	virtual bool DoTest() override;

};