#pragma once

#include "plot_defs.h"
#include "Data.h"
#include "Renderer.h"
#include "Space.h"

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Renderer1D;
class WXDLLIMPEXP_PLOTLIB Renderer2D;

class WXDLLIMPEXP_PLOTLIB SeriesND
{
public:
	SeriesND(size_t dims_count, const char *series_name = NULL);
	virtual ~SeriesND();

	void SetSeriesName(const char *series_name = NULL, bool update = true);
	const char *GetSeriesName() { return m_series_name; }

	void SetOwner(SpaceND *space) { m_owner_space = space; };
	SpaceND *GetOwner() { return m_owner_space; }

	//virtual void Clear(bool update = true) = 0;
	//virtual void RemoveData(DataNoType *data) = 0;
	void SeriesUpdated();

	void SetNData(DataNoType *data, AXIS_DIR axis_dir, bool update = true);//previous Datas will be deleted
	DataNoType *GetNData(AXIS_DIR axis_dir);

	std::vector<DataNoType *> &GetDatas() { return m_datas; }
	//virtual void RemoveNData(DataNoType *data, size_t dim_num) override;
	//virtual void Clear(bool update = true) override;
	void Fit(bool update = true);

	void SetRenderer(Renderer2D *renderer2d);//previous renderer will be deleted
	//void SetRenderer(Renderer *renderer);
	Renderer *GetRenderer();
protected:
	char *m_series_name;
	//Area *m_owner_area;
	SpaceND *m_owner_space;
	Renderer *m_renderer;

	size_t m_dims_count;
	std::vector<DataNoType *> m_datas;

};
