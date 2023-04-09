#-------------------------------------------------

#
# Project created by QtCreator 2015-07-12T21:25:58
#
#-------------------------------------------------

QT       += core gui widgets
!android{
#QT+= printsupport
}

#greaterThan(QT_MAJOR_VERSION, 4): QT += webenginewidgets


TARGET = blockchain_app
TEMPLATE = app
CONFIG+=c++11

uiяве

DEFINES+=__FULL__ QT5   WITH_IO
DEFINES+= UPNP_STATICLIB NO_GETADDRINFO STATICLIB WITHOUT_UPNP MUTEX_INSPECTOR_DEBUG
CONFIG+= precompile_header
PRECOMPILED_HEADER  = stable.h


CONFIG(debug, debug|release) {
TARGET = blockchain_app-d
DEFINES+=DEBUG _DEBUG 
} else {
TARGET = blockchain_app
}

#LIBS+=../../../dfs_lib/lib/miniupnp-master/miniupnpc/libminiupnpc.a
INCLUDEPATH +=../../../megatron/corelib ../../../megatron/corelib/events ../../../megatron/main ../../../megatron\
        ../../../../dfs_lib/lib/openssl-1.1.0/include ../../../megatron/lib/jsoncpp-0.5.0/include ../../events ../../common\
          ../../../megatron/modules/common ../../../megatron/modules/common/events \
	../../../svs ../../../dfs_lib/lib/miniupnp-master\
        ../../../megatron/lib/sqlite3 ../../../megatron/lib  /usr/local/Cellar/openssl@3/3.0.7/include

#../../../dfs_lib/lib/miniupnp-master
INCLUDEPATH+= /usr/local/include

win32{
INCLUDEPATH+= ../../../dfs_lib/lib/regex
DEFINES+=__STDC_LIMIT_MACROS __STDC_CONSTANT_MACROS  __STDC_FORMAT_MACROS
#LIBS+=-L../../../dfs_lib\lib\regex -lgnurx
LIBS+=-lgdi32

}
android {
    LIBS+= -L../../../megatron/lib/libs/$$ANDROID_TARGET_ARCH

} else {
        LIBS+= -L../../../megatron/lib/openssl-1.0.1h
}
unix{
LIBS+=-lssl -lcrypto -ldl -lz
}

unix{
#LIBS+=-lmysqlclient
}

win32{
LIBS+=-lws2_32 -L../../../dfs_lib/lib/openssl-1.1.0 -lcrypto -lssl -lgdi32 -lz
}

#LIBS+= -L../../../dfs_lib/lib/openssl-1.1.0 -lssl -lcrypto
LIBS+= -lsqlite3
LIBS+= -L/usr/local/lib  -lssl -lcrypto

!win32{
#SOURCES+=    ../../../megatron/modules/mysql/mysqlService.cpp \

#HEADERS+=     ../../../megatron/modules/mysql/mysqlService.h \

}
LIBS+=-L../../../dfs_lib/lib/miniupnp-master/miniupnpc -lminiupnpc
win32{
#LIBS+=-L../../../dfs_lib/lib/miniupnp-master/miniupnpc -lminiupnpc
LIBS+=-lws2_32 -lIphlpapi -lgdi32 -lkernel32
}

SOURCES += main.cpp\
    ../../../svs/horiz/Referrer/horizReferrerService.cpp \
    ../../../svs/horiz/Referrer/horizUriReferals.cpp \
        mainwindow.cpp \
    ../../../megatron/corelib/__crc32.cpp \
    ../../../megatron/corelib/_QUERY.cpp \
    ../../../megatron/corelib/broadcaster.cpp \
    ../../../megatron/corelib/commonError.cpp \
    ../../../megatron/corelib/configDB.cpp \
    ../../../megatron/corelib/epoll_socket_info.cpp \
    ../../../megatron/corelib/event_mt.cpp \
    ../../../megatron/corelib/eventDeque.cpp \
    ../../../megatron/corelib/httpConnection.cpp \
    ../../../megatron/corelib/Integer.cpp \
    ../../../megatron/corelib/ioBuffer.cpp \
    ../../../megatron/corelib/jpge.cpp \
    ../../../megatron/corelib/listenerBase.cpp \
    ../../../megatron/corelib/listenerBuffered.cpp \
    ../../../megatron/corelib/listenerBuffered1Thread.cpp \
    ../../../megatron/corelib/listenerPolled.cpp \
    ../../../megatron/corelib/listenerSimple.cpp \
    ../../../megatron/corelib/logging.cpp \
    ../../../megatron/corelib/msockaddr_in.cpp \
    ../../../megatron/corelib/mtimespec.cpp \
    ../../../megatron/corelib/mutexable.cpp \
    ../../../megatron/corelib/mutexInspector.cpp \
    ../../../megatron/corelib/objectHandler.cpp \
    \
    ../../../megatron/corelib/Rational.cpp \
    ../../../megatron/corelib/route_t.cpp \
    ../../../megatron/corelib/socketsContainer.cpp \
    ../../../megatron/corelib/st_rsa.cpp \
    ../../../megatron/corelib/unknown.cpp \
    ../../../megatron/corelib/url.cpp \
    ../../../megatron/corelib/webDumpable.cpp \
    ../../../megatron/main/CInstance.cpp \
    ../../../megatron/main/configObj.cpp \
    ../../../megatron/main/CUtils.cpp \
    ../../../megatron/main/threadNameCtl.cpp \
    ../../../megatron/modules/errorDispatcher/errorDispatcherService.cpp \
    ../../../megatron/modules/http/httpService.cpp \
    ../../../megatron/modules/http/mime_types.cpp \
    ../../../megatron/modules/objectProxy/objectProxyService.cpp \
    ../../../megatron/modules/oscar/oscarService.cpp \
    ../../../megatron/modules/oscarSecure/oscarSecureService.cpp \
    ../../../megatron/modules/oscarSecure/oscarSecureUser.cpp \
    ../../../megatron/modules/rpc/rpcService.cpp \
    ../../../megatron/modules/socket/socketService.cpp \
    ../../../megatron/modules/ssl/ssl_reg.cpp \
    ../../../megatron/modules/ssl/st_rsa_impl.cpp \
    ../../../megatron/modules/telnet/telnetService.cpp \
    ../../../megatron/modules/timer/timerService.cpp \
    ../../../megatron/modules/webHandler/webHandlerService.cpp \
    ../../../megatron/modules/rpc/upnp_tr.c \
    ../../../megatron/lib/jsoncpp-0.5.0/src/lib_json/json_reader.cpp \
    ../../../megatron/lib/jsoncpp-0.5.0/src/lib_json/json_value.cpp \
    ../../../megatron/lib/jsoncpp-0.5.0/src/lib_json/json_writer.cpp \
    ../../../megatron/corelib/jsonHandler.cpp \
    ../../../megatron/corelib/js_utils.cpp \
    GuiBlockchainHandler.cpp  \
    ../../../megatron/modules/dfsReferrer/dfsReferrerService.cpp \
    ../../../megatron/modules/dfsReferrer/uplinkconnectionstate.cpp \
    ../../../megatron/modules/dfsReferrer/uriReferals.cpp \
    ../../../megatron/corelib/DBH.cpp \
    ../../common/blockchainHandler.cpp \
    ../../../megatron/modules/referrerClient/referrerClientService.cpp \
    ../../../megatron/corelib/__crc64.cpp \
    ../../../megatron/corelib/__crc16.cpp \
    ../../../megatron/corelib/neighbours.cpp \
    ../../../megatron/main/iutils_decl.cpp \
    ../../../megatron/main/megatronClient.cpp \
    ../../../megatron/corelib/networkMultiplexor.cpp \
    ../../../megatron/lib/SQLiteCpp/Backup.cpp \
    ../../../megatron/lib/SQLiteCpp/Column.cpp \
    ../../../megatron/lib/SQLiteCpp/Database.cpp \
    ../../../megatron/lib/SQLiteCpp/Exception.cpp \
    ../../../megatron/lib/SQLiteCpp/Statement.cpp \
    ../../../megatron/lib/SQLiteCpp/Transaction.cpp \
    ../../../megatron/lib/sqlite3/sqlite3.c \
    ../../../svs/p2p/p2pNode/p2pNodeService.cpp \
    ../../../svs/p2p/p2pTop/p2pTopService.cpp \
    ../../../svs/p2p/common/p2pHandler.cpp \
    ../../../svs/channelSpread/common/channelSpreadHandler.cpp \
    ../../../svs/channelSpread/node/channelSpreadNodeService.cpp \
    ../../../svs/channelSpread/top/channelSpreadTopService.cpp \
    ../../../svs/ImCloud/Broadcaster/node/ImCloudBroadcasterNodeService.cpp \
    ../../../svs/ImCloud/Broadcaster/top/ImCloudBroadcasterTopService.cpp \
    ../../../svs/ImCloud/common/ImCloudHandler.cpp \
    ../../../svs/common/encoder.cpp \
    ../../../megatron/modules/dfsCaps/CapsAlgorithm.cpp \
    ../../../megatron/modules/dfsCaps/dfsCapsService.cpp \
    ../../../svs/p2p/test/p2p_test_impl.cpp \
    ../../../svs/p2p/testOffline/p2p_testOffline_impl.cpp \
    ../../../svs/p2p/testOfflineService/p2pTestOfflineService.cpp \
    ../../../megatron/corelib/trashable.cpp



win32{
SOURCES+=    \
    ../../../dfs_lib/lib/regex/regcomp.c \
    ../../../dfs_lib/lib/regex/regex.c \
    ../../../dfs_lib/lib/regex/regex_internal.c \
    ../../../dfs_lib/lib/regex/regexec.c\
}


HEADERS  += mainwindow.h \
    ../../../megatron/corelib/SHA1_id.h \
    ../../../megatron/corelib/__crc32.h \
    ../../../megatron/corelib/_QUERY.h \
    ../../../megatron/corelib/AUTHCOOKIE_id.h \
    ../../../megatron/corelib/_bitStream.h \
    ../../../megatron/corelib/broadcaster.h \
    ../../../megatron/corelib/bufferVerify.h \
    ../../../megatron/corelib/CHUNK_id.h \
    ../../../megatron/corelib/CLASS_id.h \
    ../../../megatron/corelib/commonError.h \
    ../../../megatron/corelib/compat_win32.h \
    ../../../megatron/corelib/configDB.h \
    ../../../megatron/corelib/CONTAINER.h \
    ../../../megatron/corelib/DB_id.h \
    ../../../megatron/corelib/DBH.h \
    ../../../megatron/corelib/e_poll.h \
    ../../../megatron/corelib/epoll_socket_info.h \
    ../../../megatron/corelib/errorDispatcherCodes.h \
    ../../../megatron/corelib/event_mt.h \
    ../../../megatron/corelib/EVENT_id.h \
    ../../../megatron/corelib/eventDeque.h \
    ../../../megatron/corelib/eventEnum.h \
    ../../../megatron/corelib/GlobalCookie_id.h \
    ../../../megatron/corelib/httpConnection.h \
    ../../../megatron/corelib/IConfigDB.h \
    ../../../megatron/corelib/IConfigObj.h \
    ../../../megatron/corelib/ifaces.h \
    ../../../megatron/corelib/IInstance.h \
    ../../../megatron/corelib/ILogger.h \
    ../../../megatron/corelib/Integer.h \
    ../../../megatron/corelib/IObjectProxy.h \
    ../../../megatron/corelib/ioBuffer.h \
    ../../../megatron/corelib/IProgress.h \
    ../../../megatron/corelib/IRPC.h \
    ../../../megatron/corelib/ISSL.h \
    ../../../megatron/corelib/IThreadNameController.h \
    ../../../megatron/corelib/IUtils.h \
    ../../../megatron/corelib/JAVACOOKIE_id.h \
    ../../../megatron/corelib/jpge.h \
    ../../../megatron/corelib/listenerBase.h \
    ../../../megatron/corelib/listenerBuffered.h \
    ../../../megatron/corelib/listenerBuffered1Thread.h \
    ../../../megatron/corelib/listenerPolled.h \
    ../../../megatron/corelib/listenerSimple.h \
    ../../../megatron/corelib/logging.h \
    ../../../megatron/corelib/msockaddr_in.h \
    ../../../megatron/corelib/mtimespec.h \
    ../../../megatron/corelib/mutex_inspector_entry.h \
    ../../../megatron/corelib/mutexable.h \
    ../../../megatron/corelib/mutexInspector.h \
    ../../../megatron/corelib/objectHandler.h \
    ../../../megatron/corelib/queryResult.h \
    ../../../megatron/corelib/Rational.h \
    ../../../megatron/corelib/REF.h \
    ../../../megatron/corelib/refstring.h \
    ../../../megatron/corelib/route_t.h \
    ../../../megatron/corelib/SERVICE_id.h \
    ../../../megatron/corelib/serviceEnum.h \
    ../../../megatron/corelib/SOCKET_fd.h \
    ../../../megatron/corelib/SOCKET_id.h \
    ../../../megatron/corelib/socketsContainer.h \
    ../../../megatron/corelib/st_FILE.h \
    ../../../megatron/corelib/st_malloc.h \
    ../../../megatron/corelib/st_rsa.h \
    ../../../megatron/corelib/tools_mt.h \
    ../../../megatron/corelib/unknown.h \
    ../../../megatron/corelib/unknownCastDef.h \
    ../../../megatron/corelib/url.h \
    ../../../megatron/corelib/USER_id.h \
    ../../../megatron/corelib/VERSION_id.h \
    ../../../megatron/corelib/version_mega.h \
    ../../../megatron/corelib/webDumpable.h \
    ../../../megatron/main/CInstance.h \
    ../../../megatron/main/configObj.h \
    ../../../megatron/main/CUtils.h \
    ../../../megatron/main/megatron.h \
    ../../../megatron/main/threadNameCtl.h \
    ../../../megatron/modules/errorDispatcher/errorDispatcherService.h \
    ../../../megatron/modules/http/httpService.h \
    ../../../megatron/modules/objectProxy/objectProxyService.h \
    ../../../megatron/modules/oscar/oscarService.h \
    ../../../megatron/modules/oscarSecure/oscarSecureService.h \
    ../../../megatron/modules/oscarSecure/oscarSecureUser.h \
    ../../../megatron/modules/postgres/postgresService.h \
    ../../../megatron/modules/rpc/rpcService.h \
    ../../../megatron/modules/rpc/upnp_tr.h \
    ../../../megatron/modules/socket/socketService.h \
    ../../../megatron/modules/socket/socketStats.h \
    ../../../megatron/modules/ssl/rsa-pub_512_1387663237.h \
    ../../../megatron/modules/telnet/arpa/telnet.h \
    ../../../megatron/modules/telnet/telnet.h \
    ../../../megatron/modules/telnet/telnet_keys.h \
    ../../../megatron/modules/telnet/telnetService.h \
    ../../../megatron/modules/timer/timerService.h \
    ../../../megatron/modules/webHandler/webHandlerService.h \
    ../../../megatron/corelib/jsonHandler.h \
    ../../../megatron/corelib/js_utils.h \
    ../../../megatron/modules/dfsReferrer/dfsReferrerService.h \
    ../../../megatron/modules/dfsReferrer/neighbours.h \
    ../../../megatron/modules/dfsReferrer/uplinkconnectionstate.h \
    ../../../megatron/modules/dfsReferrer/uriReferals.h \
    ../../../svs/horiz/Referrer/horizReferrerService.h \
    ../../../svs/horiz/Referrer/horizUplinkconnectionstate.h \
    ../../../svs/horiz/Referrer/horizUriReferals.h \
    ../../common/blockchainHandler.h \
    GuiBlockchainHandler.h \
    ../../../megatron/modules/referrerClient/referrerClientService.h \
    ../../../megatron/Events/DFS/Caps/___dfsCapsEvent.h \
    ../../../megatron/Events/DFS/Caps/GetRefferrers.h \
    ../../../megatron/Events/DFS/Caps/RegisterMyRefferrer.h \
    ../../../megatron/Events/DFS/Referrer/___dfsReferrerEvent.h \
    ../../../megatron/Events/DFS/Referrer/Elloh.h \
    ../../../megatron/Events/DFS/Referrer/Hello.h \
    ../../../megatron/Events/DFS/Referrer/InitClient.h \
    ../../../megatron/Events/DFS/Referrer/NotifyReferrer.h \
    ../../../megatron/Events/DFS/Referrer/NotifyReferrer.h \
    ../../../megatron/Events/DFS/Referrer/NotifyReferrer.h \
    ../../../megatron/Events/DFS/Referrer/Ping.h \
    ../../../megatron/Events/DFS/Referrer/SubscribeNotifications.h \
    ../../../megatron/Events/DFS/Referrer/ToplinkDeliver.h \
    ../../../megatron/Events/DFS/Referrer/ToplinkDeliver.h \
    ../../../megatron/Events/DFS/Referrer/UpdateConfig.h \
    ../../../megatron/Events/DFS/Referrer/UpdateConfig.h \
    ../../../megatron/Events/System/Net/http/___httpEvent.h \
    ../../../megatron/Events/System/Net/http/DoListen.h \
    ../../../megatron/Events/System/Net/http/GetBindPorts.h \
    ../../../megatron/Events/System/Net/http/GetBindPorts.h \
    ../../../megatron/Events/System/Net/http/RegisterProtocol.h \
    ../../../megatron/Events/System/Net/http/RequestIncoming.h \
    ../../../megatron/Events/System/Net/jsonRef/___jsonRefEvent.h \
    ../../../megatron/Events/System/Net/jsonRef/Json.h \
    ../../../megatron/Events/System/Net/jsonRef/Json.h \
    ../../../megatron/Events/System/Net/oscar/___oscarEvent.h \
    ../../../megatron/Events/System/Net/oscar/Accepted.h \
    ../../../megatron/Events/System/Net/oscar/AddToListenTCP.h \
    ../../../megatron/Events/System/Net/oscar/AuthFailed.h \
    ../../../megatron/Events/System/Net/oscar/Connect.h \
    ../../../megatron/Events/System/Net/oscar/Connected.h \
    ../../../megatron/Events/System/Net/oscar/ConnectFailed.h \
    ../../../megatron/Events/System/Net/oscar/NotifyBindAddress.h \
    ../../../megatron/Events/System/Net/oscar/NotifyOutBufferEmpty.h \
    ../../../megatron/Events/System/Net/oscar/PacketOnAcceptor.h \
    ../../../megatron/Events/System/Net/oscar/PacketOnConnector.h \
    ../../../megatron/Events/System/Net/oscar/SendPacket.h \
    ../../../megatron/Events/System/Net/oscar/SocketClosed.h \
    ../../../megatron/Events/System/Net/rpc/___rpcEvent.h \
    ../../../megatron/Events/System/Net/rpc/Accepted.h \
    ../../../megatron/Events/System/Net/rpc/AuthFailed.h \
    ../../../megatron/Events/System/Net/rpc/Binded.h \
    ../../../megatron/Events/System/Net/rpc/Connected.h \
    ../../../megatron/Events/System/Net/rpc/ConnectFailed.h \
    ../../../megatron/Events/System/Net/rpc/CsTlPacket.h \
    ../../../megatron/Events/System/Net/rpc/Disaccept.h \
    ../../../megatron/Events/System/Net/rpc/Disaccepted.h \
    ../../../megatron/Events/System/Net/rpc/Disconnect.h \
    ../../../megatron/Events/System/Net/rpc/Disconnected.h \
    ../../../megatron/Events/System/Net/rpc/IncomingOnAcceptor.h \
    ../../../megatron/Events/System/Net/rpc/IncomingOnConnector.h \
    ../../../megatron/Events/System/Net/rpc/NotifyOutBufferEmpty.h \
    ../../../megatron/Events/System/Net/rpc/PassPacket.h \
    ../../../megatron/Events/System/Net/rpc/ProgressNotification.h \
    ../../../megatron/Events/System/Net/rpc/ProgressSetPosition.h \
    ../../../megatron/Events/System/Net/rpc/SendPacket.h \
    ../../../megatron/Events/System/Net/rpc/SubscribeNotifications.h \
    ../../../megatron/Events/System/Net/rpc/UnsubscribeNotifications.h \
    ../../../megatron/Events/System/Net/rpc/UpnpPortMap.h \
    ../../../megatron/Events/System/Net/socket/_________socketEvent.h \
    ../../../megatron/Events/System/Net/socket/Accepted.h \
    ../../../megatron/Events/System/Net/socket/AddToConnectTCP.h \
    ../../../megatron/Events/System/Net/socket/AddToListenTCP.h \
    ../../../megatron/Events/System/Net/socket/Connected.h \
    ../../../megatron/Events/System/Net/socket/ConnectFailed.h \
    ../../../megatron/Events/System/Net/socket/NotifyBindAddress.h \
    ../../../megatron/Events/System/Net/socket/NotifyOutBufferEmpty.h \
    ../../../megatron/Events/System/Net/socket/StreamRead.h \
    ../../../megatron/Events/System/Net/socket/Write.h \
    ../../../megatron/Events/System/Run/startService.h \
    ../../../megatron/Events/System/timer/___timerEvent.h \
    ../../../megatron/Events/System/timer/ResetAlarm.h \
    ../../../megatron/Events/System/timer/SetAlarm.h \
    ../../../megatron/Events/System/timer/SetTimer.h \
    ../../../megatron/Events/System/timer/StopAlarm.h \
    ../../../megatron/Events/System/timer/StopTimer.h \
    ../../../megatron/Events/System/timer/TickAlarm.h \
    ../../../megatron/Events/System/timer/TickTimer.h \
    ../../../megatron/Events/Tools/errorDispatcher/___errorDispatcherEvent.h \
    ../../../megatron/Events/Tools/errorDispatcher/NotifySubscriber.h \
    ../../../megatron/Events/Tools/errorDispatcher/SendMessage.h \
    ../../../megatron/Events/Tools/errorDispatcher/Subscribe.h \
    ../../../megatron/Events/Tools/errorDispatcher/Unsubscribe.h \
    ../../../megatron/Events/Tools/telnet/___telnetEvent.h \
    ../../../megatron/Events/Tools/telnet/CommandEntered.h \
    ../../../megatron/Events/Tools/telnet/RegisterCommand.h \
    ../../../megatron/Events/Tools/telnet/RegisterType.h \
    ../../../megatron/Events/Tools/telnet/Reply.h \
    ../../../megatron/Events/Tools/webHandler/___webHandlerEvent.h \
    ../../../megatron/Events/Tools/webHandler/RegisterDirectory.h \
    ../../../megatron/Events/Tools/webHandler/RegisterHandler.h \
    ../../../megatron/Events/Tools/webHandler/RequestIncoming.h \
    ../../Events/BlockchainChanged.h \
    ../../Events/GetBlocksSinceId.h \
    ../../Events/GetBlocksSinceId.h \
    ../../../megatron/corelib/__crc64.h \
    ../../Events/SubscribeClientNotifications.h \
    ../../Events/RegisterDownlink.h \
    ../../../megatron/corelib/__crc16.h \
    ../../Events/GetAmount.h \
    ../../Events/GetAmount.h \
    ../../Events/GetAmount.h \
    ../../Events/GetAmount.h \
    ../../Events/GetBlockForSingleIdForClient.h \
    ../../Events/GetBlockForSingleIdForClient.h \
    ../../../megatron/Events/DFS/Referrer/NotifyReferrer.h \
    ../../../megatron/corelib/neighbours.h \
    ../../../megatron/main/megatronClient.h \
    ../../../megatron/main/utils_local.h \
    ../../../megatron/corelib/networkMultiplexor.h \
    ../../../megatron/lib/SQLiteCpp/Assertion.h \
    ../../../megatron/lib/SQLiteCpp/Backup.h \
    ../../../megatron/lib/SQLiteCpp/Column.h \
    ../../../megatron/lib/SQLiteCpp/Database.h \
    ../../../megatron/lib/SQLiteCpp/Exception.h \
    ../../../megatron/lib/SQLiteCpp/SQLiteCpp.h \
    ../../../megatron/lib/SQLiteCpp/Statement.h \
    ../../../megatron/lib/SQLiteCpp/Transaction.h \
    ../../../megatron/lib/SQLiteCpp/Utils.h \
    ../../../megatron/lib/SQLiteCpp/VariadicBind.h \
    ../../../megatron/lib/sqlite3/sqlite3.h \
    ../../../megatron/Events/System/Error/Error.h \
    ../../../svs/p2p/p2pNode/p2pNodeService.h \
    ../../../svs/p2p/p2pTop/p2pTopService.h \
    ../../../svs/p2p/common/p2pHandler.h \
    ../../../svs/channelSpread/common/channelSpreadHandler.h \
    ../../../svs/channelSpread/node/channelSpreadNodeService.h \
    ../../../svs/channelSpread/top/channelSpreadTopService.h \
    ../../../svs/ImCloud/Broadcaster/node/ImCloudBroadcasterNodeService.h \
    ../../../svs/ImCloud/Broadcaster/top/ImCloudBroadcasterTopService.h \
    ../../../svs/ImCloud/common/ImCloudHandler.h \
    ../../../svs/common/encoder.h \
    ../../../megatron/modules/dfsCaps/CapsAlgorithm.h \
    ../../../megatron/modules/dfsCaps/dfsCapsService.h \
    ../../../svs/p2p/testOfflineService/p2pTestOfflineService.h \
    ../../../megatron/corelib/trashable.h


FORMS    += mainwindow.ui \
    

OTHER_FILES += \


ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \

DISTFILES += \
    ../../../megatron/lib/SQLiteCpp/CMakeLists.txt
