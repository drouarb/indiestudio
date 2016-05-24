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

#Test MoveEntity
add_executable(PacketMoveEntityTest
        packet/PacketMoveEntityTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketMoveEntity.cpp)
add_test(PacketMoveEntityTest PacketMoveEntityTest)

#Test PacketFactory
add_executable(PacketFactoryTest
        packet/PacketFactoryTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketConnect.cpp
        ../src/network/packet/PacketDisconnect.cpp
        ../src/network/packet/PacketHandshake.cpp
        ../src/network/packet/PacketSelectPlayer.cpp
        ../src/network/packet/PacketMap.cpp
        ../src/network/packet/PacketAddEntity.cpp
        ../src/network/packet/PacketMoveEntity.cpp
        ../src/network/listener/PacketListener.cpp
        ../src/network/listener/PacketConnectListener.cpp
        ../src/network/listener/PacketDisconnectListener.cpp
        ../src/network/listener/PacketHandshakeListener.cpp
        ../src/network/listener/PacketSelectPlayerListener.cpp
        ../src/network/listener/PacketMapListener.cpp
        ../src/network/listener/PacketAddEntityListener.cpp
        ../src/network/listener/PacketMoveEntityListener.cpp
        ../src/network/PacketFactory.cpp
        ../src/network/PacketFactorySocketDisconnectionListener.cpp
        ../src/network/Socket.cpp
        )
target_link_libraries(PacketFactoryTest pthread)
add_test(PacketFactoryTest PacketFactoryTest)


#Test PhysicCollideLayer
add_executable(PhysicCollideLayer
            ../src/world/PhysicCollideLayer.cpp
            ./PhysicTest/PhysicCollierLayerTest.cpp
        )
add_test(PhysicCollideLayer PhysicCollideLayer)

