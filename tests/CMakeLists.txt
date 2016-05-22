enable_testing()

include_directories(../include)

#Test Socket
add_executable(SocketTest
        packet/SocketTest.cpp
        ../src/network/Socket.cpp
)
target_link_libraries(SocketTest pthread)
add_test(SocketTest SocketTest)

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

#Test AddEntity
add_executable(PacketAddEntityTest
        packet/PacketAddEntityTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketAddEntity.cpp)
add_test(PacketAddEntityTest PacketAddEntityTest)

#Test PhysicCollideLayer
add_executable(PhysicCollideLayer
            ../src/world/PhysicCollideLayer.cpp
            ./PhysicTest/PhysicCollierLayerTest.cpp
        )
add_test(PhysicCollideLayer PhysicCollideLayer)

