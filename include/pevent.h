#pragma once
#include <vector>
#include "plot_defs.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB PEventHandler;
	class DLLIMPEXP_PLOTLIB PEventList;
	class DLLIMPEXP_PLOTLIB PEvent;

	typedef void (PEventHandler::*HandlerMethod )(PEvent &);
	
	struct EventHandlerStruct
	{
		int event_id;
		PEventHandler *ev_handler;
		HandlerMethod handlermethod;
	};

	class DLLIMPEXP_PLOTLIB PEventHandler
	{
	public:
		PEventHandler();
		virtual ~PEventHandler();

		void Connect(int event_id, HandlerMethod handlermethod);
		void Disconnect(int event_id, HandlerMethod handlermethod);

		//void Sink();
		//virtual bool Dispatcher();

	protected:
		PEventList *m_eventslist;

	private:
	};


	class DLLIMPEXP_PLOTLIB PEvent
	{
	public:
		PEvent();
		virtual ~PEvent();
		void *GetData() { return m_event_data; }
		void SetData(void *data) { m_event_data = data; }
	protected:
		int m_event_id;
		void *m_event_data;
	private:
		friend class PEventList;
		int _getevid() { return m_event_id; };
		//static const int s_event_id;
	};

	class DLLIMPEXP_PLOTLIB PEventList
	{
	public:
		PEventList();
		virtual ~PEventList();
		
		static int GetNewEventId();
		void ProcessEvent(PEvent *evt);

	protected:
	private:
		friend class PEventHandler;
		std::vector<EventHandlerStruct> m_events;
		static int s_next_eventid;
	};
}