# Plugins

In the previous examples we linked the user-defined nodes where included
and linked statically into out projects.

We used the `BehaviorTreeFactory` to registed manualy these custom TreeNodes.

We can avoid these steps loading user-defined TreeNodes at run-time using 
pre-compiled dynamic shared libraries, i.e. __plugins__.

# Example

Let's consider the [first tutorial](tutorial_A_create_trees.md).

We can encapsulate the registration of multiple TreeNodes into a single 
function like this:

``` c++
BT_REGISTER_NODES(factory)
{
    static GripperInterface gi; // we can't have more than instance
    
    factory.registerSimpleAction("SayHello", std::bind(SayHello) );
    factory.registerSimpleAction("OpenGripper",  
                                 std::bind( &GripperInterface::open, &gi));
    factory.registerSimpleAction("CloseGripper", 
                                 std::bind( &GripperInterface::close, &gi));
    factory.registerNodeType<ApproachObject>("ApproachObject");
    factory.registerNodeType<SaySomething>("SaySomething");
}
```


`BT_REGISTER_NODES` is a macro that defines a function which symbol can be loaded
from a dynamic library.

!!! note
    This function must be placed in __.cpp__ file, not an header file.
    
In this particular example we assume that BT_REGISTER_NODES and
the definitions of our custom TreeNodes are defined in the file __dummy_nodes.cpp__.

In __cmake__ the plugin can be compiled using the argument SHARED in
`add_library`.

```cmake
add_library(dummy_nodes  SHARED dummy_nodes.cpp )
``` 

In Linux the file __libdummy_nodes.so__ is created.

Our first tutorial is, as a result, much simpler now:


```c++ hl_lines="3 24"
#include "behavior_tree_core/xml_parsing.h"
#include "Blackboard/blackboard_local.h"
// #include "dummy_nodes.h" YOU DON'T NEED THIS ANYMORE

using namespace BT;

const std::string xml_text = R"(
	 <root main_tree_to_execute = "MainTree" >
		 <BehaviorTree ID="MainTree">
			<Sequence name="root_sequence">
				<SayHello       name="action_hello"/>
				<OpenGripper    name="open_gripper"/>
				<ApproachObject name="approach_object"/>
				<CloseGripper   name="close_gripper"/>
			</Sequence>
		 </BehaviorTree>
	 </root>
)";

int main()
{
	using namespace BT;
    BehaviorTreeFactory factory;
    factory.registerFromPlugin("./libdummy_nodes.so");

    auto tree = buildTreeFromText(factory, xml_text);

    tree.root_node->executeTick();
    return 0;
}
/* Expected output:

    Robot says: "Hello!!!"
    GripperInterface::open
    ApproachObject: approach_object
    GripperInterface::close
*/

```

## Display the manifest of a plugin

BehaviorTree.CPP provides a command line tool called 
__bt_plugin_manifest__; it shows all user-defind TreeNodes
registered into the plugin and their corresponding NodeParameters.


``` 
$> ./bt_plugin_manifest ./libdummy_nodes.so 

---------------
ApproachObject [Action]
  NodeParameters: 0
---------------
CloseGripper [Action]
  NodeParameters: 0
---------------
OpenGripper [Action]
  NodeParameters: 0
---------------
SayHello [Action]
  NodeParameters: 0
---------------
SaySomething [Action]
  NodeParameters: 1:
    - [Key]: "message" / [Default]: "" 
```






