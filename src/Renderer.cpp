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

}


Renderer::~Renderer()
{
	DPRINTF("Renderer dtor\n");

}

void Renderer::_setowner(Series * series)
{
	m_owner_series = series;
}

void plot::Renderer::SetMarker(Marker * marker)
{
	if(m_marker != nullptr)
		delete m_marker;

	m_marker = marker;
}

void plot::Renderer::SetLine(Line * line)
{
	if(m_line != nullptr)
		delete m_line;

	m_line = line;
}
