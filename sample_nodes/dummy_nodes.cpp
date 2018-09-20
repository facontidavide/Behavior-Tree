#include "dummy_nodes.h"

// This function must be implemented in the .cpp file to create
// a plugin that can be loaded at run-time
BT_REGISTER_NODES(factory)
{
    DummyNodes::RegisterNodes(factory);
}


namespace DummyNodes
{

BT::NodeStatus SayHello()
{
    std::cout << "Hello!!!" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CheckBattery()
{
    std::cout << "[ Battery: OK ]" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CheckTemperature()
{
    std::cout << "[ Temperature: OK ]" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus Foo::actionOne()
{
    _val = 42;
    std::cout << "Foo::actionOne -> set val to 42" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus Foo::actionTwo()
{
    std::cout << "Foo::actionTwo -> reading val => "<< _val << std::endl;
    _val = 0;
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CustomAction::tick()
{
    std::cout << "CustomAction: " << this->name() << std::endl;
    return BT::NodeStatus::SUCCESS;
}

void CustomAction::halt()
{
    setStatus(BT::NodeStatus::IDLE);
}

}
