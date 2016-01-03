#pragma once

#include "Box.h"
#include "Scale.h"

class DLLIMPEXP_PLOTLIB ScaleBox : public Box, public Scale
{
public:
	ScaleBox(Plot *plot, Dir orient);
	virtual ~ScaleBox();

protected:
private:
	Dir m_orient;
	// Inherited via Scale
	virtual void ScaleRedraw() override;
};