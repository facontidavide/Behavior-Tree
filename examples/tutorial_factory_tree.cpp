#include "behavior_tree_core/xml_parsing.h"
#include "Blackboard/blackboard_local.h"

//#define MANUAL_STATIC_LINKING

#ifdef MANUAL_STATIC_LINKING
#include "dummy_nodes.h"
#endif

using namespace BT;

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

int main()
{
    BehaviorTreeFactory factory;

#ifdef MANUAL_STATIC_LINKING
    // This helper function is optional if you plan to link
    // your TreeNodes statically. Check dummy_nodes.h to see how it is implemented
    DummyNodes::RegisterNodes(factory);
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
