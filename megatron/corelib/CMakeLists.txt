#cmake_minimum_required (VERSION 2.6)

#project(dfsCore)

#ADD_SUBDIRECTORY(test)


add_library(megatron-core STATIC
            DBH.cpp
            Integer.cpp
            Rational.cpp
            _QUERY.cpp
            __crc32.cpp
            __crc64.cpp
            __crc16.cpp
            _bitStream.cpp
            broadcaster.cpp
            commonError.cpp
            configDB.cpp
            epoll_socket_info.cpp
            event_mt.cpp
            eventDeque.cpp
            httpConnection.cpp
            ioBuffer.cpp
            jpge.cpp
            js_utils.cpp
            jsonHandler.cpp
            listenerBase.cpp
            listenerBuffered.cpp
            listenerBuffered1Thread.cpp
            listenerPolled.cpp
            listenerSimple.cpp
            logging.cpp
            msockaddr_in.cpp
            mtimespec.cpp
            mutexInspector.cpp
            mutexable.cpp
            objectHandler.cpp
            route_t.cpp
            socketsContainer.cpp
	    networkMultiplexor.cpp
            st_rsa.cpp
            unknown.cpp
            url.cpp
            trashable.cpp
            webDumpable.cpp
            neighbours.cpp
            ../lib/jsoncpp-0.5.0/src/lib_json/json_reader.cpp
            ../lib/jsoncpp-0.5.0/src/lib_json/json_value.cpp
            ../lib/jsoncpp-0.5.0/src/lib_json/json_writer.cpp


           )
#install(TARGETS megatron-core DESTINATION ${LIB_TARGET_DIR})

