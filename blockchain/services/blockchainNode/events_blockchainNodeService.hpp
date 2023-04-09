#ifndef __________blockchainNodeService_EventInfo__HH
#define __________blockchainNodeService_EventInfo__HH


inline std::set<EVENT_id> getEvents_blockchainNodeService()
{

	std::set<EVENT_id> out;
	out.insert(ErrorEventEnum::ErrorRSP);
	out.insert(blockchainEventEnum::BlockchainChanged);
	out.insert(blockchainEventEnum::GetAmountREQ);
	out.insert(blockchainEventEnum::GetAmountRSP);
	out.insert(blockchainEventEnum::GetBlockForSingleIdForClientREQ);
	out.insert(blockchainEventEnum::GetBlockForSingleIdForClientRSP);
	out.insert(blockchainEventEnum::GetBlocksSinceIdREQ);
	out.insert(blockchainEventEnum::GetBlocksSinceIdRSP);
	out.insert(blockchainEventEnum::PublishBlockREQ);
	out.insert(blockchainEventEnum::PublishBlockRSP);
	out.insert(blockchainEventEnum::SubscribeClientNotifications);
	out.insert(dfsReferrerEventEnum::NotifyReferrerDownlinkDisconnected);
	out.insert(dfsReferrerEventEnum::NotifyReferrerUplinkIsConnected);
	out.insert(dfsReferrerEventEnum::NotifyReferrerUplinkIsDisconnected);
	out.insert(dfsReferrerEventEnum::SubscribeNotifications);
	out.insert(dfsReferrerEventEnum::ToplinkDeliverREQ);
	out.insert(dfsReferrerEventEnum::ToplinkDeliverRSP);
	out.insert(imEventEnum::RegisterDownlinkREQ);
	out.insert(imEventEnum::RegisterDownlinkRSP);
	out.insert(rpcEventEnum::IncomingOnAcceptor);
	out.insert(rpcEventEnum::IncomingOnConnector);
	out.insert(systemEventEnum::startService);
	out.insert(telnetEventEnum::CommandEntered);
	out.insert(timerEventEnum::TickTimer);
	out.insert(webHandlerEventEnum::RequestIncoming);

	return out;
}

inline void regEvents_blockchainNodeService()
{
	iUtils->registerEvent(ErrorEvent::ErrorRSP::construct);
	iUtils->registerEvent(blockchainEvent::BlockchainChanged::construct);
	iUtils->registerEvent(blockchainEvent::GetAmountREQ::construct);
	iUtils->registerEvent(blockchainEvent::GetAmountRSP::construct);
	iUtils->registerEvent(blockchainEvent::GetBlockForSingleIdForClientREQ::construct);
	iUtils->registerEvent(blockchainEvent::GetBlockForSingleIdForClientRSP::construct);
	iUtils->registerEvent(blockchainEvent::GetBlocksSinceIdREQ::construct);
	iUtils->registerEvent(blockchainEvent::GetBlocksSinceIdRSP::construct);
	iUtils->registerEvent(blockchainEvent::PublishBlockREQ::construct);
	iUtils->registerEvent(blockchainEvent::PublishBlockRSP::construct);
	iUtils->registerEvent(blockchainEvent::SubscribeClientNotifications::construct);
	iUtils->registerEvent(dfsReferrerEvent::NotifyReferrerDownlinkDisconnected::construct);
	iUtils->registerEvent(dfsReferrerEvent::NotifyReferrerUplinkIsConnected::construct);
	iUtils->registerEvent(dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected::construct);
	iUtils->registerEvent(dfsReferrerEvent::SubscribeNotifications::construct);
	iUtils->registerEvent(dfsReferrerEvent::ToplinkDeliverREQ::construct);
	iUtils->registerEvent(dfsReferrerEvent::ToplinkDeliverRSP::construct);
	iUtils->registerEvent(imEvent::RegisterDownlinkREQ::construct);
	iUtils->registerEvent(imEvent::RegisterDownlinkRSP::construct);
	iUtils->registerEvent(rpcEvent::IncomingOnAcceptor::construct);
	iUtils->registerEvent(rpcEvent::IncomingOnConnector::construct);
	iUtils->registerEvent(systemEvent::startService::construct);
	iUtils->registerEvent(telnetEvent::CommandEntered::construct);
	iUtils->registerEvent(timerEvent::TickTimer::construct);
	iUtils->registerEvent(webHandlerEvent::RequestIncoming::construct);
}
#endif
