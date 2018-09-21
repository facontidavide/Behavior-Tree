#include "behavior_tree_core/xml_parsing.h"
#include "Blackboard/blackboard_local.h"

//#define MANUAL_STATIC_LINKING

#ifdef MANUAL_STATIC_LINKING
#include "dummy_nodes.h"
#endif

using namespace BT;

// clang-format off
const std::string xml_text = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <Sequence name="root_sequence">
            <SayHello       name="action_hello"/>
            <ActionOne      name="action_one"/>
            <ActionTwo      name="action_two"/>
            <CustomAction   name="my_action"/>
        </Sequence>
     </BehaviorTree>

 </root>
 )";

// clang-format on

int main()
{
    /* In this example we build a tree at run-time.
     * The tree is defined using an XML (see xml_text).
     * To achieve this we must first register our TreeNodes into
     * a BehaviorTreeFactory.
     */
    BehaviorTreeFactory factory;

    /* There are two ways to register nodes:
    *    - statically, including directly DummyNodes.
    *    - dynamically, loading the TreeNodes from a shared library (plugin).
    * */

#ifdef MANUAL_STATIC_LINKING
    // Note: the name used to register should be the same used in the XML.
    // Note that the same operations could be done using DummyNodes::RegisterNodes(factory)

    using namespace DummyNodes;

    factory.registerSimpleAction("SayHello", std::bind(SayHello) );
    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery) );
    factory.registerSimpleCondition("CheckTemperature", std::bind(CheckTemperature) );

    Foo foo;
    factory.registerSimpleAction("ActionOne", std::bind( &Foo::actionOne, &foo));
    factory.registerSimpleAction("ActionTwo", std::bind( &Foo::actionTwo, &foo));

    factory.registerNodeType<CustomAction>("CustomAction");
#else
    // Load dynamically a plugin and register the TreeNodes it contains
    factory.registerFromPlugin("./libdummy_nodes.so");
#endif

    // IMPORTANT: when the object tree goes out of scope, all the TreeNodes are destroyed
    auto tree = buildTreeFromText(factory, xml_text);

    // The tick is propagated to all the children.
    // until one of the returns FAILURE or RUNNING.
    // In this case all of the return SUCCESS
    tree.root_node->executeTick();

    return 0;
}
