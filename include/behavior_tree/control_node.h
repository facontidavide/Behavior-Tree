#ifndef CONTROLNODE_H
#define CONTROLNODE_H

#include <vector>

#include "behavior_tree/tree_node.h"

namespace BT
{
    class ControlNode : public TreeNode
    {
    protected:
        // Children vector
        std::vector<TreeNode*> children_nodes_;

        // Children states
        std::vector<ReturnStatus> children_states_;

        // Vector size
        unsigned int N_of_children_;
        //child i status. Used to rout the ticks
        ReturnStatus child_i_status_;

    public:
        // Constructor
        ControlNode(std::string name);
        ~ControlNode() = default;

        // The method used to fill the child vector
        void AddChild(TreeNode* child);

        // The method used to know the number of children
        unsigned int ChildrenCount() const;

        const std::vector<TreeNode*>& Children() const;

        // The method used to interrupt the execution of the node
        virtual void Halt() override;

        void HaltChildren(int i);

        // Methods used to access the node state without the
        // conditional waiting (only mutual access)
        bool WriteState(ReturnStatus new_state);

        virtual NodeType Type() const override { return CONTROL_NODE; }
    };
}

#endif
