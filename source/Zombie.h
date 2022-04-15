#include "UnigineMathLib.h"
#include "UniginePrimitives.h"
#include "UnigineComponentSystem.h"
#include "UnigineImport.h"
#include "UnigineNode.h"
#include "UnigineObjects.h"
#include <Unigine.h>

using namespace Unigine;

class Zombie : public Unigine::ComponentBase {

public:
  // Required macros
  COMPONENT_DEFINE(Zombie, ComponentBase)
  COMPONENT_INIT(Init)
  COMPONENT_UPDATE(Update)

protected:
  void Init();
  void Update();
  
  void GoToPlayer();
  float objectTransition(point1, point2, speed);
private:
  ObjectMeshDynamicPtr zombieMesh; // Mesh
  float walkSpeed; // TODO: Maybe use const?


  // Animations
  // Still
  // Walk 
  // Hit 
  // Die
 
  // Sound
  // Still
  // Walk
  // Hit
  // Die
  
  // AI - NEXT
  
};
