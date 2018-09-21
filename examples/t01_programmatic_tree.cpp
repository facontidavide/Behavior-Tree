#include "Blackboard/blackboard_local.h"
#include "dummy_nodes.h"

using namespace BT;

int main()
{
    using namespace DummyNodes;
    Foo foo;

    // sequence_root will be the root of our tree
    BT::SequenceNode sequence_root("sequence");

    // Simple functions can be wrapped inside in ActionNodeBase
    // using the SimpleActionNode
    SimpleActionNode act_simple("action_hello", std::bind(SayHello) );

    // SimpleActionNode works also with class methods, using std::bind
    SimpleActionNode act_1("action_one", std::bind( &Foo::actionOne, &foo) );
    SimpleActionNode act_2("action_two", std::bind( &Foo::actionTwo, &foo) );

    // To be able to use ALL the functionalities of a TreeNode,
    //  your should create a class that inherits from either:
    // - ConditionNode  (synchronous execution)
    // - ActionNodeBase (synchronous execution)
    // - ActionNode     (asynchronous execution in a separate thread).
    CustomAction act_custom("my_action");

    // Add children to the sequence.
    // they will be executed in the same order they are added.
    sequence_root.addChild(&act_simple);
    sequence_root.addChild(&act_1);
    sequence_root.addChild(&act_2);
    sequence_root.addChild(&act_custom);

    // The tick is propagated to all the children.
    // until one of them returns FAILURE or RUNNING.
    // In this case all of them return SUCCESS immediately
    sequence_root.executeTick();

    return 0;
}
