enable_testing()

include_directories(../include)

#Test PacketConnect
add_executable(PacketConnectTest
        packet/PacketConnectTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketConnect.cpp)
add_test(PacketConnectTest PacketConnectTest)

#Test Disconnect
add_executable(PacketDisconnectTest
        packet/PacketDisconnectTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketDisconnect.cpp)
add_test(PacketDisconnectTest PacketDisconnectTest)

#Test Handshake
add_executable(PacketHandshakeTest
        packet/PacketHandshakeTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketHandshake.cpp)
add_test(PacketHandshakeTest PacketHandshakeTest)

#Test SelectPlayer
add_executable(PacketSelectPlayerTest
        packet/PacketSelectPlayerTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketSelectPlayer.cpp)
add_test(PacketSelectPlayerTest PacketSelectPlayerTest)

#Test Map
add_executable(PacketMapTest
        packet/PacketMapTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketMap.cpp)
add_test(PacketMapTest PacketMapTest)

#Test AddPlayer
add_executable(PacketAddPlayerTest
        packet/PacketAddPlayerTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketAddPlayer.cpp)
add_test(PacketAddPlayerTest PacketAddPlayerTest)
