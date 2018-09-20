#ifndef SIMPLE_BT_NODES_H
#define SIMPLE_BT_NODES_H

#include "behavior_tree_core/behavior_tree.h"
#include "behavior_tree_core/bt_factory.h"

namespace DummyNodes
{

BT::NodeStatus SayHello();

BT::NodeStatus CheckBattery();

BT::NodeStatus CheckTemperature();


class Foo
{
public:
    Foo(): _val(0) {}

    BT::NodeStatus actionOne();

    BT::NodeStatus actionTwo();

private:
    int _val;
};

//--------------------------------------

class CustomAction: public BT::ActionNodeBase
{
public:
    CustomAction(const std::string& name):
        BT::ActionNodeBase(name) {}

    BT::NodeStatus tick() override;
    virtual void halt() override;
};

inline void RegisterNodes(BT::BehaviorTreeFactory& factory)
{
    static Foo foo;
    factory.registerSimpleAction("SayHello", std::bind(SayHello) );
    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery) );
    factory.registerSimpleCondition("CheckTemperature", std::bind(CheckTemperature) );
    factory.registerSimpleAction("ActionOne", std::bind( &Foo::actionOne, &foo));
    factory.registerSimpleAction("ActionTwo", std::bind( &Foo::actionTwo, &foo));
    factory.registerNodeType<CustomAction>("CustomAction");
}

}

#endif // SIMPLE_BT_NODES_H
