//
// Created by Falldot on 26.11.2021.
//

//#define CORSAC_TEST_TIME_OFF
//#define CORSAC_TEST_RESULT_OFF
#define TEST_ENABLE
#define CORSAC_DEBUG 1

#include "Test.h"

void* __cdecl operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{
    return new uint8_t[size];
}

void* __cdecl operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
    return new uint8_t[size];
}

//#include "Corsac/Component.h"

#include <iostream>
#include "Corsac/ecs.h"


//#include "Corsac/Entity.h"

namespace ecs
{
    corsac::ComponentMake<30, true> Tag;
    corsac::ComponentMake<30, true, int> Position;
    corsac::ComponentMake<30, true, int, int> Direction;

    inline void Move(corsac::Group entities) noexcept
    {
        for(auto it = entities.begin(), itEnd = entities.end(); it != itEnd; ++it)
        {
            std::cout << "Up " << *it << std::endl;
        }
    }
    corsac::System<Move, corsac::Update> Translate;
}

int main()
{
    corsac::Entity player;
    corsac::Entity enemy;
    corsac::Entity person;

    player.add<ecs::Tag>();
    enemy.add<ecs::Tag>();
    person.add<ecs::Tag>();

    for (size_t i = 0; i < ecs::Tag.size(); ++i)
    {
        std::cout << ecs::Tag[i] << std::endl;
    }
    for(auto it = ecs::Tag.begin(), itEnd = ecs::Tag.end(); it != itEnd; ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "__________________________" << std::endl;

    player.add<ecs::Position>(3);
    enemy.add<ecs::Position>(323);
    person.add<ecs::Position>(13213);

    std::cout << player.get<ecs::Position>() << std::endl;

    for (size_t i = 0; i < ecs::Position.size(); ++i)
    {
        std::cout << ecs::Position[i] << std::endl;
    }
    for(auto it = ecs::Position.begin(), itEnd = ecs::Position.end(); it != itEnd; ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "__________________________" << std::endl;

    player.add<ecs::Direction>(3, 11);
    enemy.add<ecs::Direction>(323, 43);
    person.add<ecs::Direction>(13213, 3123);

    auto X = ecs::Direction.get<0>();
    auto Y = ecs::Direction.get<1>();

    std::cout << player.get<ecs::Direction, 0>() << std::endl;

    for (size_t i = 0; i < ecs::Direction.size(); ++i)
    {
        std::cout << X[i] << "/" << Y[i] << std::endl;
    }
    std::cout << "__________________________" << std::endl;

    player.add<ecs::Translate>();
    enemy.add<ecs::Translate>();

    ecs::Translate.call();
}
