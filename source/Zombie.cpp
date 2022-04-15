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
  zombieMesh = Primitives::createBox(Math::Vec3_one); // TODO: How should mesh assignment work?
  walkSpeed = .005f;  
  // Visualizing GoToPlayer route
  Visualizer::setEnabled(1);
}

void Zombie::Update() {
  // Follow player location
  GoToPlayer();
}

// Since zombies always go to the player (to attack),
// this function does two things:
// 1. Find the route to the player
// 2. Go to the player with the found route
// TODO: Don't just move the mesh. Move the entire node.
// TODO: Fix bad point - player is outside the navSector, not able to create route outside of it.
void Zombie::GoToPlayer(){
  NodePtr pPlayerNode = World::getNodeByName("main_player");
  if (pPlayerNode == nullptr) { return; } // Is the player in the world?
  
  // The area in which route can be created.
  NodePtr navSectorNode = World::getNodeByName("NavSector"); 

  // The location of the player.
  Math::Vec3 playerWT = pPlayerNode->getWorldTransform().getTranslate();

  // Declare points between which the route should be calculated
  Math::Vec3 p0 = Math::vec3(0.0f, 0.0f, 0.5f); // TODO: Change to the location of the zombie.
  Math::Vec3 p1 = playerWT;

  // Create route
  PathRoutePtr route = PathRoute::create();
  route->setRadius(2.0f); // TODO: Investigate more regarding what the radius does.
  route->create2D(p0, p1);

  /*
  Math::Vec3 routePosition = route->getPoint(1);
  Math::Vec3 oldPosition = zombieMesh->getWorldTransform().getTranslate();
  Math::Vec3 newPositionCalc = (oldPosition + routePosition) / 2;
  newPositionCalc = newPositionCalc * 0.2;
  Math::Vec3 newPosition = oldPosition + newPositionCalc; 
  */
  
  // Go to the nearest point in the route.
  Math::Vec3 nearestPointPosition = route->getPoint(1);

  // We are only concerned about x and y axis due to the game nature.
  float zombiePositionX = zombieMesh->getPosition().x;
  float zombiePositionY = zombieMesh->getPosition().y;
  float xValueStorage = 0.f;
  float yValueStorage = 0.f;
 
  // TODO: Optimize
  // Does the axis needs update?
  if (zombiePositionX != nearestPointPosition.x){
    // Is point 1 smaller or larger than point 2? So we can decide to use negative or positive. 
    if (zombiePositionX < nearestPointPosition.x){
      // How small is point 1 when the speed is added? We don't want to cross point 2. 
      if (zombiePositionX + walkSpeed < nearestPointPosition.x){
        xValueStorage = walkSpeed; 
      } else{
        xValueStorage = nearestPointPosition.x - zombiePositionX; // Add the remaining distance.
      }
    } else{
      // How large is point 1 when the speed is added? We don't want to cross point 2.
      if (zombiePositionX + walkSpeed > nearestPointPosition.x){
        xValueStorage = -walkSpeed; 
      } else{
        xValueStorage = nearestPointPosition.x - zombiePositionX; // Add the remaining distance.
      }
    }
  }
  // Assigning position to the 
  Math::Vec3 resultPosition = zombieMesh->getPosition() + Math::Vec3(xValueStorage, yValueStorage, 0.f); 
  zombieMesh->setWorldPosition(resultPosition);
 
  // TEMP: For debugging
  route->renderVisualizer(Math::vec4(1.0f));
}
