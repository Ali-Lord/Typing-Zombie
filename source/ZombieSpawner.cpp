#include "ZombieSpawner.h"
#include "UnigineMathLibCommon.h"
#include "UnigineMathLibVec3.h"
#include "UnigineObjects.h"
#include "UniginePlayers.h"

REGISTER_COMPONENT(ZombieSpawner)

void ZombieSpawner::Init() {
    // Creating a box 
    // Note: This is supposed to be temporary for testing
    primitiveBoxPtr = Primitives::createBox(Math::vec3_one);
    
}

void ZombieSpawner::Update() { 

}
