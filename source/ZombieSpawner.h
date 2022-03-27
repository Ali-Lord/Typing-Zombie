#include "UnigineNode.h"
#include "UniginePrimitives.h"
#include <Unigine.h>

using namespace Unigine;

class ZombieSpawner : public Unigine::ComponentBase {

public:
    // MACROS
    COMPONENT_DEFINE(ZombieSpawner, ComponentBase)
    COMPONENT_INIT(Init)
    COMPONENT_UPDATE(Update)

    PROP_PARAM(Int, RandomNum)

private:
    ObjectMeshDynamicPtr primitiveBoxPtr;

protected:
    void Init();
    void Update();
};
