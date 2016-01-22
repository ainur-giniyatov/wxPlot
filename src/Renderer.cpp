#include "wx/colorbase.h" //temporary
#include "Renderer.h"

using namespace plot;

static int s_text_pos = 5;
static int s_text_height = 13;

Renderer::Renderer()
{
	DPRINTF("Renderer ctor\n");
	m_owner_series = NULL;

	m_text_pos = s_text_pos;
	s_text_pos += s_text_height;

	m_visible = true;
	m_line_visible = true;
	m_markers_visible = true;
	m_marker_style = MARKER_CIRCLE;
	m_marker_size = rand() % 4 + 2;
	m_marker_color_index = rand() % COLOR_BASE_COUNT;

	switch (rand() % 5)
	{
	case 0:
		SetMarkerStyle(MARKER_CIRCLE);
		break;
	case 1:
		SetMarkerStyle(MARKER_ROMB);
		break;
	case 2:
		SetMarkerStyle(MARKER_SQUARE);
		break;
	case 3:
		SetMarkerStyle(MARKER_CROSS);
		break;
	case 4:
		SetMarkerStyle(MARKER_PLUS);
		break;
	default:;
		assert(0);
	}

	m_line_style = LINE_SOLID;
	m_line_thickness = rand() % 3 + 1;
	m_line_color_index = rand() % COLOR_BASE_COUNT;
}


Renderer::~Renderer()
{
	DPRINTF("Renderer dtor\n");

}

void Renderer::SetOwner(Series * series)
{
	m_owner_series = series;
}

void Renderer::SetMarkerStyle(MARKER_STYLES marker_style)
{
	m_marker_style = marker_style;
	if (m_owner_series != nullptr && m_owner_series->GetOwner() != nullptr)
		m_owner_series->GetOwner()->GetOwner()->_SetViewModifiedFlag();

}


void Renderer::SetMarkerSize(int marker_size)
{
	m_marker_size = marker_size;
	if (m_owner_series != nullptr && m_owner_series->GetOwner() != nullptr)
		m_owner_series->GetOwner()->GetOwner()->_SetViewModifiedFlag();

}

void Renderer::SetMarkerColourIndex(int marker_colour_index)
{
	m_marker_color_index = marker_colour_index;
	if (m_owner_series != nullptr && m_owner_series->GetOwner() != nullptr)
		m_owner_series->GetOwner()->GetOwner()->_SetViewModifiedFlag();

}

void Renderer::SetLineStyle(LINE_STYLES line_style)
{
	m_line_style = line_style;
	if (m_owner_series != nullptr && m_owner_series->GetOwner() != nullptr)
		m_owner_series->GetOwner()->GetOwner()->_SetViewModifiedFlag();

}

void Renderer::SetLineThickness(int line_thickness)
{
	m_line_thickness = line_thickness;
	if (m_owner_series != nullptr && m_owner_series->GetOwner() != nullptr)
		m_owner_series->GetOwner()->GetOwner()->_SetViewModifiedFlag();

}

void Renderer::SetLineColourIndex(int line_colour_index)
{
	m_line_color_index = line_colour_index;
	if (m_owner_series != nullptr && m_owner_series->GetOwner() != nullptr)
		m_owner_series->GetOwner()->GetOwner()->_SetViewModifiedFlag();

}
