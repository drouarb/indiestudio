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

#Test StartGame
add_executable(PacketStartGameTest
        packet/PacketStartGameTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketStartGame.cpp)
add_test(PacketStartGameTest PacketStartGameTest)

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

#Test DeleteEntity
add_executable(PacketDeleteEntityTest
        packet/PacketDeleteEntityTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketDeleteEntity.cpp)
add_test(PacketDeleteEntityTest PacketDeleteEntityTest)

#Test AddParticle
add_executable(PacketAddParticleTest
        packet/PacketAddParticleTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketAddParticle.cpp)
add_test(PacketAddParticleTest PacketAddParticleTest)

#Test DeleteParticle
add_executable(PacketDeleteParticleTest
        packet/PacketDeleteParticleTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketDeleteParticle.cpp)
add_test(PacketDeleteParticleTest PacketDeleteParticleTest)

#Test PlaySound
add_executable(PacketPlaySoundTest
        packet/PacketPlaySoundTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketPlaySound.cpp)
add_test(PacketPlaySoundTest PacketPlaySoundTest)

#Test StopSound
add_executable(PacketStopSoundTest
        packet/PacketStopSoundTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketStopSound.cpp)
add_test(PacketStopSoundTest PacketStopSoundTest)

#Test Control
add_executable(PacketControlTest
        packet/PacketControlTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketControl.cpp)
add_test(PacketControlTest PacketControlTest)

#Test Animation
add_executable(PacketAnimationTest
        packet/PacketAnimationTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketAnimation.cpp)
add_test(PacketAnimationTest PacketAnimationTest)

#Test HUD
add_executable(PacketHUDTest
        packet/PacketHUDTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketHUD.cpp)
add_test(PacketHUDTest PacketHUDTest)

#Test PacketFactory
add_executable(PacketFactoryTest
        packet/PacketFactoryTest.cpp
        ../src/network/packet/Packet.cpp
        ../src/network/packet/PacketConnect.cpp
        ../src/network/packet/PacketDisconnect.cpp
        ../src/network/packet/PacketHandshake.cpp
        ../src/network/packet/PacketSelectPlayer.cpp
        ../src/network/packet/PacketStartGame.cpp
        ../src/network/packet/PacketMap.cpp
        ../src/network/packet/PacketAddEntity.cpp
        ../src/network/packet/PacketMoveEntity.cpp
        ../src/network/packet/PacketDeleteEntity.cpp
        ../src/network/packet/PacketAddParticle.cpp
        ../src/network/packet/PacketDeleteParticle.cpp
        ../src/network/packet/PacketPlaySound.cpp
        ../src/network/packet/PacketStopSound.cpp
        ../src/network/packet/PacketControl.cpp
        ../src/network/packet/PacketAnimation.cpp
        ../src/network/packet/PacketHUD.cpp
        ../src/network/listener/PacketListener.cpp
        ../src/network/listener/PacketDisconnectListener.cpp
        ../src/network/listener/PacketAddEntityListener.cpp
        ../src/network/PacketFactory.cpp
        ../src/network/PacketFactorySocketDisconnectionListener.cpp
        ../src/network/Socket.cpp
        )
target_link_libraries(PacketFactoryTest pthread)
add_test(PacketFactoryTest PacketFactoryTest)

