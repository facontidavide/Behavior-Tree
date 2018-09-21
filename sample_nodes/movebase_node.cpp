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
        printf("[ MoveBase: STARTED ]. goal: x=%.f y=%.1f theta=%.2f\n",
               goal.x, goal.y, goal.theta);

        _halt_requested.store(false);
        int count = 0;

        // "compute" for 250 milliseconds or until _halt_requested is true
        while( !_halt_requested && count++ < 25)
        {
            SleepMS(10);
        }

        std::cout << "[ MoveBase: FINISHED ]" << std::endl;
        return _halt_requested ? BT::NodeStatus::SUCCESS : BT::NodeStatus::SUCCESS;
    }
    else{
        printf("The NodeParameter does not contain the key [goal] "
               " or the blackboard does not contain the provided key\n");
        return BT::NodeStatus::FAILURE;
    }
}

void MoveBaseAction::halt()
{
    _halt_requested.store(true);
}
