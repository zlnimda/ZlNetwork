cmake_minimum_required(VERSION 2.8)

project(ZlNetwork)

##########################################
# Directories
##########################################

set(DIR_SOURCE			${PROJECT_SOURCE_DIR}/SourceFiles/)
set(DIR_SOURCE_NETWORK		${DIR_SOURCE}Network/)
set(DIR_SOURCE_SOCKET		${DIR_SOURCE_NETWORK}Socket/)
set(DIR_SOURCE_BUFFER		${DIR_SOURCE_NETWORK}Buffer/)
set(DIR_SOURCE_RESOLVER		${DIR_SOURCE_NETWORK}Resolver/)
set(DIR_SOURCE_HANDLER		${DIR_SOURCE_NETWORK}Handler/)

set(DIR_INCLUDE			${PROJECT_SOURCE_DIR}/IncludeFiles/)
set(DIR_INCLUDE_NETWORK		${DIR_INCLUDE}Network/)
set(DIR_INCLUDE_SOCKET		${DIR_INCLUDE_NETWORK}Socket/)
set(DIR_INCLUDE_BUFFER		${DIR_INCLUDE_NETWORK}Buffer/)
set(DIR_INCLUDE_RESOLVER	${DIR_INCLUDE_NETWORK}Resolver/)
set(DIR_INCLUDE_HANDLER		${DIR_INCLUDE_NETWORK}Handler/)

##########################################
# Include directories
##########################################
include_directories(${DIR_INCLUDE})
include_directories(${DIR_INCLUDE_NETWORK})
include_directories(${DIR_INCLUDE_SOCKET})
include_directories(${DIR_INCLUDE_BUFFER})
include_directories(${DIR_INCLUDE_RESOLVER})
include_directories(${DIR_INCLUDE_HANDLER})

##########################################
# Source files
##########################################

if (UNIX)
set(
	SOURCE_NETWORK_SPEC
	${DIR_SOURCE_SOCKET}AUnixSocket.cpp
	${DIR_SOURCE_RESOLVER}UnixAddrInfo.cpp
	${DIR_SOURCE_BUFFER}UnixSockBuffer.cpp
	${DIR_SOURCE_SOCKET}UnixTCPSocket.cpp
	${DIR_SOURCE_SOCKET}UnixUDPSocket.cpp
)
else (WIN32)
set(
	SOURCE_NETWORK_SPEC
	${DIR_SOURCE_SOCKET}AWinSocket.cpp
	${DIR_SOURCE_RESOLVER}WinAddrInfo.cpp
	${DIR_SOURCE_BUFFER}WinSockBuffer.cpp
	${DIR_SOURCE_SOCKET}WinSockStartup.cpp
	${DIR_SOURCE_SOCKET}WinTCPSocket.cpp
	${DIR_SOURCE_SOCKET}WinUDPSocket.cpp
)
endif (UNIX)

set(
	SOURCE_NETWORK
	${SOURCE_NETWORK_SPEC}
	${DIR_SOURCE_BUFFER}AdvSockBuffer.cpp
	${DIR_SOURCE_HANDLER}SocketHandler.cpp
	${DIR_SOURCE_HANDLER}Listener.cpp
)

set(
	SOURCE_FILES
	${SOURCE_NETWORK}
)

##########################################
# Header files
##########################################

if (UNIX)
set(
	HEADER_SOCKET_SPEC
	${DIR_INCLUDE_RESOLVER}UnixAddrInfo.hpp
	${DIR_INCLUDE_SOCKET}AUnixSocket.hpp
	${DIR_INCLUDE_SOCKET}UnixTCPSocket.hpp
	${DIR_INCLUDE_SOCKET}UnixUDPSocket.hpp
	${DIR_INCLUDE_BUFFER}UnixSockBuffer.hpp
)
else (WIN32)
set(
	HEADER_SOCKET_SPEC
	${DIR_INCLUDE_RESOLVER}WinAddrInfo.hpp
	${DIR_INCLUDE_SOCKET}AWinSocket.hpp
	${DIR_INCLUDE_SOCKET}WinSockStartup.hpp
	${DIR_INCLUDE_SOCKET}WinTCPSocket.hpp
	${DIR_INCLUDE_SOCKET}WinUDPSocket.hpp
	${DIR_INCLUDE_BUFFER}WinSockBuffer.hpp
)
endif (UNIX)

set(
	HEADER_SOCKET
	${DIR_INCLUDE_NETWORK}ZRP.hpp
	${DIR_INCLUDE_NETWORK}ZlNetwork.hpp
	${DIR_INCLUDE_SOCKET}ITCPSocket.hpp
	${DIR_INCLUDE_SOCKET}IUDPSocket.hpp
	${DIR_INCLUDE_SOCKET}ISocket.hpp
	${DIR_INCLUDE_RESOLVER}IAddrInfo.hpp
	${DIR_INCLUDE_BUFFER}ISockBuffer.hpp
	${DIR_INCLUDE_BUFFER}AdvSockBuffer.hpp
	${DIR_INCLUDE_BUFFER}SetBuffer.hpp
	${DIR_INCLUDE_HANDLER}SocketHandler.hpp
	${DIR_INCLUDE_HANDLER}Function.hpp
	${DIR_INCLUDE_HANDLER}Listener.hpp
)

set(
	HEADER_NETWORK
	${HEADER_SOCKET}
	${HEADER_SOCKET_SPEC}
)

set(
	HEADER_FILES
	${DIR_INCLUDE}CommunicateProtocol.hpp
	${HEADER_NETWORK}
)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Threads)

project(ZlClient)

add_executable(
	${PROJECT_NAME}
	${SOURCE_FILES}
	${DIR_SOURCE}main.cpp
	${HEADER_FILES}
)

target_link_libraries(
	${PROJECT_NAME}
	${CMAKE_THREAD_LIBS_INIT}
)

project(ZlServer)

add_executable(
	${PROJECT_NAME}
	${SOURCE_FILES}
	${DIR_SOURCE}mainS.cpp
	${HEADER_FILES}
)
