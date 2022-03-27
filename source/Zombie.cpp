#include "Zombie.h"
#include "UnigineLog.h"
#include "UnigineMathLib.h"
#include "UnigineMathLibCommon.h"
#include "UnigineMathLibMat4.h"
#include "UnigineMathLibSimd.h"
#include "UnigineNode.h"
#include <cmath>
#include <iostream>

// Macro to register the component to the engine
REGISTER_COMPONENT(Zombie)

void Zombie::Init() {
  zombieMesh = Primitives::createBox(Math::Vec3_one);
}

void Zombie::Update() {
  // follow player location
  NodePtr pPlayerNode = World::getNodeByName("main_player");
  if (pPlayerNode != nullptr) {
    Math::Mat4 playerWT = pPlayerNode->getWorldTransform();

    // Create path to player
    Math::Vec3 addedPlayerWT = playerWT.getTranslate() + Math::vec3(10,0,0); 
    zombieMesh->setWorldPosition(addedPlayerWT);

  }
}
