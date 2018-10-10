# Blackboards

The blackboard is a a key/value storage that can be shared by all the Nodes
of a tree.

The __key__ is a string and the value is a type-erased container (called `SafeAny::Any`) 
that allows the user to store any C++ object and to cast it back to its original form.

Contrariwise to `boost::any` and `std::any`, this container will also try to 
avoid common type casting errors.

For instance, you can't cast a negative number into an `unsigned integer`,
nor a very large number that exceeds 2^8 into a `char`.

The user can create his/her own Blackboards backend; it is possible, for instance,
to create a persistent blackboard using a database.

## Assign a blackboard to a tree

In the following code sample we can see two equivalent ways to assign a 
Blackboard to a tree.



