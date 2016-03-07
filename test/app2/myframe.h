#pragma once
#include "mainframe.h"
namespace plot { class Series; }
class MyFrame :
	public MainFrame
{
public:
	MyFrame();
	virtual ~MyFrame();

private:

	void fillseries(plot::Series *series);
	DECLARE_EVENT_TABLE()
};

