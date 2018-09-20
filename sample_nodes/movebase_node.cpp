#include "movebase_node.h"
#include "behavior_tree_core/bt_factory.h"


// This function must be implemented in the .cpp file to create
// a plugin that can be loaded at run-time
BT_REGISTER_NODES(factory)
{
    factory.registerNodeType<MoveBaseAction>("MoveBase");
}


const BT::NodeParameters &MoveBaseAction::requiredNodeParameters()
{
    static BT::NodeParameters params = {{"goal","0;0;0"}};
    return params;
}

BT::NodeStatus MoveBaseAction::tick()
{
    Pose2D goal;

    // retrieve the parameter using getParam()
    if( getParam<Pose2D>("goal", goal) )
    {
        printf("[MoveBase] goal: x=%.f y=%.1f theta=%.2f\n",
               goal.x, goal.y, goal.theta);

        std::this_thread::sleep_for( std::chrono::milliseconds(180) );

        std::cout << "[ Move: finished ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    else{
        printf("The NodeParameter does not contain the key [goal] "
               " or the blackboard does not contain the provided key\n");
        return BT::NodeStatus::FAILURE;
    }
}
