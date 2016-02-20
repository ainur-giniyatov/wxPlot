#include "Axis.h"

#include <assert.h>

using namespace plot;

Axis::Axis(AXIS_DIR axis_dir)
{
	DPRINTF("Axis ctor\n");
	m_offset = 0.;
	m_range = 100.0;
	m_owner = nullptr;
	m_commonscale = nullptr;
	m_axis_dir = axis_dir;
}


Axis::~Axis()
{
	DPRINTF("Axis dtor\n");
	if (m_commonscale != nullptr)
		m_commonscale->RemoveAxis(this);
}


const std::vector<DataNoType*> plot::Axis::_get_adj_datas()
{
	std::vector<DataNoType*> datas;

	for (auto series : m_owner->GetSerie())
	{
		if (series->GetData(m_axis_dir) != nullptr)
			datas.push_back(series->GetData(m_axis_dir));
	}

	return datas;
}

