#ifndef __________imInvoicerService_EventInfo__HH
#define __________imInvoicerService_EventInfo__HH


inline std::set<EVENT_id> getEvents_imInvoicerService()
{

	std::set<EVENT_id> out;
	out.insert(dfsReferrerEventEnum::ToplinkDeliverREQ);
	out.insert(dfsReferrerEventEnum::ToplinkDeliverRSP);
	out.insert(invoiceEventEnum::GetInvoiceREQ);
	out.insert(invoiceEventEnum::GetInvoiceRSP);
	out.insert(invoiceEventEnum::MakeInvoiceREQ);
	out.insert(invoiceEventEnum::MakeInvoiceRSP);
	out.insert(rpcEventEnum::IncomingOnAcceptor);
	out.insert(systemEventEnum::startService);
	out.insert(telnetEventEnum::CommandEntered);
	out.insert(timerEventEnum::TickTimer);
	out.insert(webHandlerEventEnum::RequestIncoming);

	return out;
}

inline void regEvents_imInvoicerService()
{
	iUtils->registerEvent(dfsReferrerEvent::ToplinkDeliverREQ::construct);
	iUtils->registerEvent(dfsReferrerEvent::ToplinkDeliverRSP::construct);
	iUtils->registerEvent(invoiceEvent::GetInvoiceREQ::construct);
	iUtils->registerEvent(invoiceEvent::GetInvoiceRSP::construct);
	iUtils->registerEvent(invoiceEvent::MakeInvoiceREQ::construct);
	iUtils->registerEvent(invoiceEvent::MakeInvoiceRSP::construct);
	iUtils->registerEvent(rpcEvent::IncomingOnAcceptor::construct);
	iUtils->registerEvent(systemEvent::startService::construct);
	iUtils->registerEvent(telnetEvent::CommandEntered::construct);
	iUtils->registerEvent(timerEvent::TickTimer::construct);
	iUtils->registerEvent(webHandlerEvent::RequestIncoming::construct);
}
#endif
