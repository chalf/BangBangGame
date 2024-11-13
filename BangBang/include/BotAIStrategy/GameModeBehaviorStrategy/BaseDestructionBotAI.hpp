#pragma once 

#include "BotAIStrategy/GameModeBehavior.hpp"

class BaseDestructionBotAI : public GameModeBehavior {
public:
    void play(GAMEMOD mode, float deltaTime) override;
};