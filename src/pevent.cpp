#include <assert.h>
#include "pevent.h"

using namespace plot;

//PEventHandler
PEventHandler::PEventHandler(PEventList *evlist)
{
	m_eventslist = evlist;
}

PEventHandler::~PEventHandler()
{

}

void plot::PEventHandler::AddHandler(int event_id, HandlerMethod handlermethod)
{
	EventHandlerStruct ehs;
	ehs.event_id = event_id;
	ehs.ev_handler = this;
	ehs.handlermethod = handlermethod;
	m_eventslist->m_events.push_back(ehs);
}

void plot::PEventHandler::RemoveHandler(int event_id, HandlerMethod handlermethod)
{
	for (auto entry_iter = m_eventslist->m_events.begin(); entry_iter != m_eventslist->m_events.end(); ++entry_iter)
	{
		if ((*entry_iter).event_id == event_id && (*entry_iter).ev_handler == this)
		{
			m_eventslist->m_events.erase(entry_iter);
			break;
		}
	}
}

void plot::PEventHandler::HandleEvent(PEvent & evt)
{
	m_eventslist->ProcessEvent(evt);
}

//PEventList

int PEventList::s_next_eventid = 0;
plot::PEventList::PEventList()
{
	
}

plot::PEventList::~PEventList()
{
}

int plot::PEventList::GetNewEventId()
{
	int id;
	id = s_next_eventid;
	s_next_eventid++;
	return id;
}

void plot::PEventList::ProcessEvent(PEvent &evt)
{
	//iterate events list and invoke registered handler for matched event ids
	for (auto event_enrty : m_events)
	{
		if (event_enrty.event_id == evt._getevid())
		{
			PEventHandler *evthandler;
			HandlerMethod handlermethod;
			evthandler = event_enrty.ev_handler;
			handlermethod = event_enrty.handlermethod;
			(evthandler->*handlermethod)(evt);
		}
	}

}

//PEvent

//const int PEvent::s_event_id = PEventList::GetNewEventId();
plot::PEvent::PEvent()
{
	m_event_data = nullptr;
	m_event_id = -1;
}

plot::PEvent::~PEvent()
{
}
