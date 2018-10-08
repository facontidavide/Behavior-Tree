# Getting started

__BehaviorTree.CPP__ is a C++ library that can be easily integrated into
your favourite distributed middleware, such as __ROS__ of __SmartSoft__.

You can also statically link it into your application (for example a game).

There are some main concepts  that you need to understand first.

## Nodes vs Trees

The user must create his/her own ActionNodes and ConditionNodes (LeafeNodes) and this 
library helps you to compose them easily into trees. 

Think about the LeafNodes as the building blocks that you need to compose
a complex system.

Keep in mind that, by definition, your custom Nodes are (or should be) highly reusable.
Therefore, even if some heavy litfing might be needed at the beginning,
the added productivity will compensate that.  


## The tick() callbacks

Any TreeNode can be seen as a mechanism to invoke a __callback__, i.e. to 
run a piece of code. What this callback does is up to you.

Don't be puzzled by the fact that in most of the examples the Actions just
print messages on the screen of sleep for a certain amount of time to simulate
a long calculation.

## Inheritance vs dependency injection.

To create a custom TreeNode, you should inherit from the proper type.

For instance, to create your own Action, you should inherit from the 
class __ActionNodeBase__. 

Alternatively, we provided a mechanism to create a TreeNode passins a 
__function pointer__ to a wrapper.

This approach reduce the amount of boilerplate in your code but has also 
some limitations; the most important one is that TreeNodes created using 
function pointers can not support NodeParameters.

## NodeParameters

NodeParameters are conceptually similar to the arguments of a function.

They are passed statically when the tree is instantiated.

They are expressed as a list of __key/value__ pairs, where both the the
key and the value are strings.

This is not surprising, since NodeParameters are usually parsed from file.

The library provides some methods and utlity functions to correctly convert
values from string to the proper C++ type.  

