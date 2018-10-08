# How to create Trees

You have mainly two ways to create Behavior Trees.

- __Statically, at compilation time__.
- __Dynamically, at run-time__, i.e. parsing a file.

You are strongly encourage to use the latter approach, but we will describe
the first for the sake of completeness.

## How to create your own ActionNodes

You can find the source code here: [dummy_nodes.h](../sample_nodes/ dummy_nodes.h)

The default (and recommended) way to create a TreeNode is by inheritance.

``` c++
// Example of custom ActionNodeBase (synchronous Action)
class ApproachObject: public BT::ActionNodeBase
{
public:
    ApproachObject(const std::string& name):
        BT::ActionNodeBase(name) {}

    // You must override the virtual function tick()
    BT::NodeStatus tick() override
    {
		std::cout << "ApproachObject: " << this->name() << std::endl;
		return BT::NodeStatus::SUCCESS;
	}

    // You must override the virtual function halt()
    virtual void halt() override 
    {
		// Do nothing. This is used by asynchronous nodes.
    }
};
``` 

As you can see:

- Any TreeNode as a name. This identifier is meant to be user-readable and it 
 doesn't need to be unique.
 
- The method __tick()__ is the place where the actual Action takes place.
It must return a NodeStatus RUNNING, SUCCESS or FAILURE. 

- The method __halt()__ is used to stop an asynchronous Action. ApproachObject
doesn't need it.
 
 
Alternatively, we can use __dependecy injection to create a TreeNode given 
a __functor__ (function pointer). 

The only requirement of the funtor is to have either one of these signatures:

    BT::NodeStatus myFunction()
    BT::NodeStatus myFunction(TreeNode& self) 


``` c++
BT::NodeStatus SayHello() {
    std::cout << "Robot says: \"Hello!!!\"" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

class GripperInterface
{
public:
    GripperInterface(): _open(true) {}
    
	BT::NodeStatus open() {
		_open = true;
		std::cout << "GripperInterface::open" << std::endl;
		return BT::NodeStatus::SUCCESS;
	}

	BT::NodeStatus close() {
		std::cout << "GripperInterface::close" << std::endl;
		_open = false;
		return BT::NodeStatus::SUCCESS;
	}

private:
    bool _open;
};

``` 

In the example, we can build a __SimpleActionNode__ from:

- SayHello()
- GripperInterface::open()
- GripperInterface::close()


## Tutorial 01: a statically created Tree



``` c++
#include "dummy_nodes.h"

int main()
{
	using namespace BT;
    using namespace DummyNodes;
    
    GripperInterface gi;

    SequenceNode sequence_root("sequence");
    SimpleActionNode say_hello("action_hello", std::bind(SayHello) );
    SimpleActionNode open_gripper("open_gripper",   
                                  std::bind( &GripperInterface::open,  &gi) );
    SimpleActionNode close_gripper("close_gripper", 
                                   std::bind( &GripperInterface::close, &gi) );
    ApproachObject approach_object("approach_object");

    // Add children to the sequence. 
    // They will be executed in the same order they are added.
    sequence_root.addChild(&say_hello);
    sequence_root.addChild(&open_gripper);
    sequence_root.addChild(&approach_object);
    sequence_root.addChild(&close_gripper);

    sequence_root.executeTick();
    return 0;
}

/* Expected output:

    Robot says: "Hello!!!"
    GripperInterface::open
    ApproachObject: approach_object
    GripperInterface::close
*/

``` 

## Tutorial 02: a dynamically created Tree

Give the following XML stored in the file __my_tree.xml__

``` XML
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
```

We must first register our custom TreeNodes into the __BehaviorTreeFactory__
 and the load the XMl from file or text.


``` c++
#include "dummy_nodes.h"

int main()
{
	using namespace BT;
    using namespace DummyNodes;

    GripperInterface gi;    
    BehaviorTreeFactory factory;

    factory.registerSimpleAction("SayHello", std::bind(SayHello) );
    factory.registerSimpleAction("OpenGripper", 
                                 std::bind( &GripperInterface::open, &gi));
    factory.registerSimpleAction("CloseGripper", 
                                  std::bind( &GripperInterface::close, &gi));

    factory.registerNodeType<ApproachObject>("ApproachObject");

    // IMPORTANT: when the object tree goes out of scope,
    // all the TreeNodes are destroyed
    auto tree = buildTreeFromFile(factory, "./my_tree.xml");

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



