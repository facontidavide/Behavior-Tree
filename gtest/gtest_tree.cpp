/* Copyright (C) 2015-2017 Michele Colledanchise - All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <gtest/gtest.h>
#include "action_test_node.h"
#include "condition_test_node.h"
#include "behavior_tree_core/behavior_tree.h"

using BT::NodeStatus;

struct SimpleSequenceTest : testing::Test
{
    BT::SequenceNode root;
    BT::ActionTestNode action;
    BT::ConditionTestNode condition;

    SimpleSequenceTest() : root("root_sequence"), action("action"), condition("condition")
    {
        root.addChild(&condition);
        root.addChild(&action);
    }
    ~SimpleSequenceTest()
    {
        HaltAllActions(&root);
    }
};

struct ComplexSequenceTest : testing::Test
{
    BT::SequenceNode root;
    BT::ActionTestNode action_1;
    BT::ConditionTestNode condition_1;
    BT::ConditionTestNode condition_2;

    BT::SequenceNode seq_conditions;

    ComplexSequenceTest()
      : root("root_sequence")
      , action_1("action_1")
      , condition_1("condition_1")
      , condition_2("condition_2")
      , seq_conditions("sequence_conditions")
    {
        root.addChild(&seq_conditions);
        {
            seq_conditions.addChild(&condition_1);
            seq_conditions.addChild(&condition_2);
        }
        root.addChild(&action_1);
    }
    ~ComplexSequenceTest()
    {
        HaltAllActions(&root);
    }
};

struct SequenceTripleActionTest : testing::Test
{
    BT::SequenceNode root;
    BT::ActionTestNode action_1;
    BT::ActionTestNode action_2;
    BT::ActionTestNode action_3;

    SequenceTripleActionTest() : root("root_sequence"), action_1("action_1"), action_2("action_2"), action_3("action_3")
    {
        root.addChild(&action_1);
        root.addChild(&action_2);
        root.addChild(&action_3);
    }
    ~SequenceTripleActionTest()
    {
        HaltAllActions(&root);
    }
};

struct ComplexSequence2ActionsTest : testing::Test
{
    BT::SequenceNode root;
    BT::ActionTestNode action_1;
    BT::ActionTestNode action_2;
    BT::SequenceNode seq_1;
    BT::SequenceNode seq_2;

    BT::ConditionTestNode condition_1;
    BT::ConditionTestNode condition_2;

    ComplexSequence2ActionsTest()
      : root("root_sequence")
      , action_1("action_1")
      , action_2("action_2")
      , seq_1("sequence_1")
      , seq_2("sequence_2")
      , condition_1("condition_1")
      , condition_2("condition_2")
    {
        root.addChild(&seq_1);
        {
            seq_1.addChild(&condition_1);
            seq_1.addChild(&action_1);
        }
        root.addChild(&seq_2);
        {
            seq_2.addChild(&condition_2);
            seq_2.addChild(&action_2);
        }
    }
    ~ComplexSequence2ActionsTest()
    {
        HaltAllActions(&root);
    }
};

struct SimpleFallbackTest : testing::Test
{
    BT::FallbackNode root;
    BT::ActionTestNode action;
    BT::ConditionTestNode condition;

    SimpleFallbackTest() : root("root_fallback"), action("action"), condition("condition")
    {
        root.addChild(&condition);
        root.addChild(&action);
    }
    ~SimpleFallbackTest()
    {
        HaltAllActions(&root);
    }
};

struct ComplexFallbackTest : testing::Test
{
    BT::FallbackNode root;
    BT::ActionTestNode action_1;
    BT::ConditionTestNode condition_1;
    BT::ConditionTestNode condition_2;

    BT::FallbackNode fal_conditions;

    ComplexFallbackTest()
      : root("root_fallback")
      , action_1("action_1")
      , condition_1("condition_1")
      , condition_2("condition_2")
      , fal_conditions("fallback_conditions")
    {
        root.addChild(&fal_conditions);
        {
            fal_conditions.addChild(&condition_1);
            fal_conditions.addChild(&condition_2);
        }
        root.addChild(&action_1);
    }
    ~ComplexFallbackTest()
    {
        HaltAllActions(&root);
    }
};

struct BehaviorTreeTest : testing::Test
{
    BT::SequenceNode root;
    BT::ActionTestNode action_1;
    BT::ConditionTestNode condition_1;
    BT::ConditionTestNode condition_2;

    BT::FallbackNode fal_conditions;

    BehaviorTreeTest()
      : root("root_sequence")
      , action_1("action_1")
      , condition_1("condition_1")
      , condition_2("condition_2")
      , fal_conditions("fallback_conditions")
    {
        root.addChild(&fal_conditions);
        {
            fal_conditions.addChild(&condition_1);
            fal_conditions.addChild(&condition_2);
        }
        root.addChild(&action_1);
    }
    ~BehaviorTreeTest()
    {
        HaltAllActions(&root);
    }
};

struct SimpleSequenceWithMemoryTest : testing::Test
{
    BT::SequenceNodeWithMemory root;
    BT::ActionTestNode action;
    BT::ConditionTestNode condition;

    SimpleSequenceWithMemoryTest() : root("root_sequence"), action("action"), condition("condition")
    {
        root.addChild(&condition);
        root.addChild(&action);
    }
    ~SimpleSequenceWithMemoryTest()
    {
        HaltAllActions(&root);
    }
};

struct ComplexSequenceWithMemoryTest : testing::Test
{
    BT::SequenceNodeWithMemory root;

    BT::ActionTestNode action_1;
    BT::ActionTestNode action_2;

    BT::ConditionTestNode condition_1;
    BT::ConditionTestNode condition_2;

    BT::SequenceNodeWithMemory seq_conditions;
    BT::SequenceNodeWithMemory seq_actions;

    ComplexSequenceWithMemoryTest()
      : root("root_sequence")
      , action_1("action_1")
      , action_2("action_2")
      , condition_1("condition_1")
      , condition_2("condition_2")
      , seq_conditions("sequence_conditions")
      , seq_actions("sequence_actions")
    {
        root.addChild(&seq_conditions);
        {
            seq_conditions.addChild(&condition_1);
            seq_conditions.addChild(&condition_2);
        }
        root.addChild(&seq_actions);
        {
            seq_actions.addChild(&action_1);
            seq_actions.addChild(&action_2);
        }
    }
    ~ComplexSequenceWithMemoryTest()
    {
        HaltAllActions(&root);
    }
};

struct SimpleFallbackWithMemoryTest : testing::Test
{
    BT::FallbackNodeWithMemory root;
    BT::ActionTestNode action;
    BT::ConditionTestNode condition;

    SimpleFallbackWithMemoryTest() : root("root_sequence"), action("action"), condition("condition")
    {
        root.addChild(&condition);
        root.addChild(&action);
    }
    ~SimpleFallbackWithMemoryTest()
    {
        HaltAllActions(&root);
    }
};

struct ComplexFallbackWithMemoryTest : testing::Test
{
    BT::FallbackNodeWithMemory root;

    BT::ActionTestNode action_1;
    BT::ActionTestNode action_2;

    BT::ConditionTestNode condition_1;
    BT::ConditionTestNode condition_2;

    BT::FallbackNodeWithMemory fal_conditions;
    BT::FallbackNodeWithMemory fal_actions;

    ComplexFallbackWithMemoryTest()
      : root("root_fallback")
      , action_1("action_1")
      , action_2("action_2")
      , condition_1("condition_1")
      , condition_2("condition_2")
      , fal_conditions("fallback_conditions")
      , fal_actions("fallback_actions")
    {
        root.addChild(&fal_conditions);
        {
            fal_conditions.addChild(&condition_1);
            fal_conditions.addChild(&condition_2);
        }
        root.addChild(&fal_actions);
        {
            fal_actions.addChild(&action_1);
            fal_actions.addChild(&action_2);
        }
    }
    ~ComplexFallbackWithMemoryTest()
    {
        HaltAllActions(&root);
    }
};

struct SimpleParallelTest : testing::Test
{
    BT::ParallelNode root;
    BT::ActionTestNode action_1;
    BT::ConditionTestNode condition_1;

    BT::ActionTestNode action_2;
    BT::ConditionTestNode condition_2;

    SimpleParallelTest()
      : root("root_parallel", 4)
      , action_1("action_1")
      , condition_1("condition_1")
      , action_2("action_2")
      , condition_2("condition_2")
    {
        root.addChild(&condition_1);
        root.addChild(&action_1);
        root.addChild(&condition_2);
        root.addChild(&action_2);
    }
    ~SimpleParallelTest()
    {
        HaltAllActions(&root);
    }
};

struct ComplexParallelTest : testing::Test
{
    BT::ParallelNode root;
    BT::ParallelNode parallel_1;
    BT::ParallelNode parallel_2;

    BT::ActionTestNode action_1;
    BT::ConditionTestNode condition_1;

    BT::ActionTestNode action_2;
    BT::ConditionTestNode condition_2;

    BT::ActionTestNode action_3;
    BT::ConditionTestNode condition_3;

    ComplexParallelTest()
      : root("root", 2)
      , parallel_1("par1", 3)
      , parallel_2("par2", 1)
      , action_1("action_1")
      , condition_1("condition_1")
      , action_2("action_2")
      , condition_2("condition_2")
      , action_3("action_3")
      , condition_3("condition_3")
    {
        root.addChild(&parallel_1);
        {
            parallel_1.addChild(&condition_1);
            parallel_1.addChild(&action_1);
            parallel_1.addChild(&condition_2);
            parallel_1.addChild(&action_2);
        }
        root.addChild(&parallel_2);
        {
            parallel_2.addChild(&condition_3);
            parallel_2.addChild(&action_3);
        }
    }
    ~ComplexParallelTest()
    {
        HaltAllActions(&root);
    }
};

/****************TESTS START HERE***************************/

TEST_F(SimpleSequenceTest, ConditionTrue)
{
    std::cout << "Ticking the root node !" << std::endl << std::endl;
    // Ticking the root node
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, action.status());
    ASSERT_EQ(NodeStatus::RUNNING, state);

}

TEST_F(SimpleSequenceTest, ConditionTurnToFalse)
{
    BT::NodeStatus state = root.executeTick();
    condition.set_boolean_value(false);

    state = root.executeTick();
    ASSERT_EQ(NodeStatus::FAILURE, state);
    ASSERT_EQ(NodeStatus::IDLE, condition.status());
    ASSERT_EQ(NodeStatus::IDLE, action.status());

}

TEST_F(ComplexSequenceTest, ComplexSequenceConditionsTrue)
{
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());

}

TEST_F(SequenceTripleActionTest, TripleAction)
{
    using namespace BT;
    using namespace std::chrono;
    const auto timeout = system_clock::now() + milliseconds(650);

    action_1.set_time(2);
    action_2.set_time(2);
    action_3.set_time(2);
    // the sequence is supposed to finish in (200 ms * 3) = 600 ms

    bool done_1 = false, done_2 = false, done_3 = false;

    auto sub1 = action_1.subscribeToStatusChange([&done_1](TimePoint, const TreeNode&, NodeStatus, NodeStatus status) {
        if (status == NodeStatus::SUCCESS)
            done_1 = true;
    });

    auto sub2 = action_2.subscribeToStatusChange([&done_2](TimePoint, const TreeNode&, NodeStatus, NodeStatus status) {
        if (status == NodeStatus::SUCCESS)
            done_2 = true;
    });

    auto sub3 = action_3.subscribeToStatusChange([&done_3](TimePoint, const TreeNode&, NodeStatus, NodeStatus status) {
        if (status == NodeStatus::SUCCESS)
            done_3 = true;
    });

    // first tick
    NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_3.status());

    // continue until succesfull
    while (state != NodeStatus::SUCCESS && system_clock::now() < timeout)
    {
        std::this_thread::sleep_for(milliseconds(20));
        state = root.executeTick();
    }

    ASSERT_EQ(NodeStatus::SUCCESS, state);
    ASSERT_TRUE(done_1);
    ASSERT_TRUE(done_2);
    ASSERT_TRUE(done_3);
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_3.status());
    ASSERT_TRUE(system_clock::now() < timeout);   // no timeout should occur


}

TEST_F(ComplexSequence2ActionsTest, ConditionsTrue)
{
    BT::NodeStatus state = root.executeTick();

    state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::RUNNING, seq_1.status());
    ASSERT_EQ(NodeStatus::SUCCESS, condition_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, seq_2.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, seq_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, seq_2.status());
    ASSERT_EQ(NodeStatus::SUCCESS, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_2.status());

    state = root.executeTick();

    // TODO: what is a reasonable behavior in this case?


}

TEST_F(ComplexSequenceTest, ComplexSequenceConditions1ToFalse)
{
    BT::NodeStatus state = root.executeTick();

    condition_1.set_boolean_value(false);

    state = root.executeTick();

    ASSERT_EQ(NodeStatus::FAILURE, state);
    ASSERT_EQ(NodeStatus::IDLE, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());

}

TEST_F(ComplexSequenceTest, ComplexSequenceConditions2ToFalse)
{
    BT::NodeStatus state = root.executeTick();

    condition_2.set_boolean_value(false);

    state = root.executeTick();

    ASSERT_EQ(NodeStatus::FAILURE, state);
    ASSERT_EQ(NodeStatus::IDLE, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());

}

TEST_F(SimpleFallbackTest, ConditionTrue)
{
    std::cout << "Ticking the root node !" << std::endl << std::endl;
    // Ticking the root node
    condition.set_boolean_value(true);
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::SUCCESS, state);
    ASSERT_EQ(NodeStatus::IDLE, condition.status());
    ASSERT_EQ(NodeStatus::IDLE, action.status());

}

TEST_F(SimpleFallbackTest, ConditionToFalse)
{
    condition.set_boolean_value(false);

    BT::NodeStatus state = root.executeTick();
    condition.set_boolean_value(true);

    state = root.executeTick();

    ASSERT_EQ(NodeStatus::SUCCESS, state);
    ASSERT_EQ(NodeStatus::IDLE, condition.status());
    ASSERT_EQ(NodeStatus::IDLE, action.status());

}

TEST_F(ComplexFallbackTest, Condition1ToTrue)
{
    condition_1.set_boolean_value(false);
    condition_2.set_boolean_value(false);

    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());

    condition_1.set_boolean_value(true);

    state = root.executeTick();

    ASSERT_EQ(NodeStatus::SUCCESS, state);
    ASSERT_EQ(NodeStatus::IDLE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());

}

TEST_F(ComplexFallbackTest, Condition2ToTrue)
{
    condition_1.set_boolean_value(false);
    condition_2.set_boolean_value(false);

    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());

    condition_2.set_boolean_value(true);

    state = root.executeTick();

    ASSERT_EQ(NodeStatus::SUCCESS, state);
    ASSERT_EQ(NodeStatus::IDLE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());

}

TEST_F(BehaviorTreeTest, Condition1ToFalseCondition2True)
{
    condition_1.set_boolean_value(false);
    condition_2.set_boolean_value(true);

    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());


}

TEST_F(BehaviorTreeTest, Condition2ToFalseCondition1True)
{
    condition_2.set_boolean_value(false);
    condition_1.set_boolean_value(true);

    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());


}

TEST_F(SimpleSequenceWithMemoryTest, ConditionTrue)
{
    BT::NodeStatus state = root.executeTick();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, condition.status());
    ASSERT_EQ(NodeStatus::RUNNING, action.status());

}

TEST_F(SimpleSequenceWithMemoryTest, ConditionTurnToFalse)
{
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, condition.status());
    ASSERT_EQ(NodeStatus::RUNNING, action.status());

    condition.set_boolean_value(false);
    state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, condition.status());
    ASSERT_EQ(NodeStatus::RUNNING, action.status());


}

TEST_F(ComplexSequenceWithMemoryTest, ConditionsTrue)
{
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, seq_actions.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(ComplexSequenceWithMemoryTest, Conditions1ToFase)
{
    BT::NodeStatus state = root.executeTick();

    condition_1.set_boolean_value(false);
    state = root.executeTick();
    // change in condition_1 does not affect the state of the tree,
    // since the seq_conditions was executed already
    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, seq_actions.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(ComplexSequenceWithMemoryTest, Conditions2ToFalse)
{
    BT::NodeStatus state = root.executeTick();

    condition_2.set_boolean_value(false);
    state = root.executeTick();
    // change in condition_2 does not affect the state of the tree,
    // since the seq_conditions was executed already
    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::SUCCESS, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, seq_actions.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(ComplexSequenceWithMemoryTest, Action1DoneSeq)
{
    root.executeTick();

    condition_2.set_boolean_value(false);
    root.executeTick();

    // change in condition_2 does not affect the state of the tree,
    // since the seq_conditions was executed already
    ASSERT_EQ(NodeStatus::SUCCESS, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, seq_actions.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    root.executeTick();

    ASSERT_EQ(NodeStatus::SUCCESS, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, seq_actions.status());
    ASSERT_EQ(NodeStatus::SUCCESS, action_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_2.status());

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    root.executeTick();

    ASSERT_EQ(NodeStatus::SUCCESS, root.status());
    ASSERT_EQ(NodeStatus::IDLE, seq_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, seq_actions.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(SimpleFallbackWithMemoryTest, ConditionFalse)
{
    condition.set_boolean_value(false);
    BT::NodeStatus state = root.executeTick();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, condition.status());
    ASSERT_EQ(NodeStatus::RUNNING, action.status());


}

TEST_F(SimpleFallbackWithMemoryTest, ConditionTurnToTrue)
{
    condition.set_boolean_value(false);
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, condition.status());
    ASSERT_EQ(NodeStatus::RUNNING, action.status());

    condition.set_boolean_value(true);
    state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, condition.status());
    ASSERT_EQ(NodeStatus::RUNNING, action.status());


}

TEST_F(ComplexFallbackWithMemoryTest, ConditionsTrue)
{
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::SUCCESS, state);
    ASSERT_EQ(NodeStatus::IDLE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, fal_actions.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(ComplexFallbackWithMemoryTest, Condition1False)
{
    condition_1.set_boolean_value(false);
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::SUCCESS, state);
    ASSERT_EQ(NodeStatus::IDLE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, fal_actions.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(ComplexFallbackWithMemoryTest, ConditionsFalse)
{
    condition_1.set_boolean_value(false);
    condition_2.set_boolean_value(false);
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, fal_actions.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(ComplexFallbackWithMemoryTest, Conditions1ToTrue)
{
    condition_1.set_boolean_value(false);
    condition_2.set_boolean_value(false);
    BT::NodeStatus state = root.executeTick();

    condition_1.set_boolean_value(true);
    state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, fal_actions.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(ComplexFallbackWithMemoryTest, Conditions2ToTrue)
{
    condition_1.set_boolean_value(false);
    condition_2.set_boolean_value(false);
    BT::NodeStatus state = root.executeTick();

    condition_2.set_boolean_value(true);
    state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, fal_actions.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());


}

TEST_F(ComplexFallbackWithMemoryTest, Action1Failed)
{
    action_1.set_boolean_value(false);
    condition_1.set_boolean_value(false);
    condition_2.set_boolean_value(false);

    BT::NodeStatus state = root.executeTick();

    state = root.executeTick();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    state = root.executeTick();

    ASSERT_EQ(NodeStatus::RUNNING, state);
    ASSERT_EQ(NodeStatus::FAILURE, fal_conditions.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, fal_actions.status());
    ASSERT_EQ(NodeStatus::FAILURE, action_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_2.status());


}

TEST_F(SimpleParallelTest, ConditionsTrue)
{
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, state);


}

TEST_F(SimpleParallelTest, Threshold_3)
{
    root.setThresholdM(3);
    action_2.set_time(200);
    root.executeTick();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());
    ASSERT_EQ(NodeStatus::SUCCESS, state);


}

TEST_F(SimpleParallelTest, Threshold_1)
{
    root.setThresholdM(1);
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());
    ASSERT_EQ(NodeStatus::SUCCESS, state);


}
TEST_F(ComplexParallelTest, ConditionsTrue)
{
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_3.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_3.status());
    ASSERT_EQ(NodeStatus::RUNNING, parallel_1.status());
    ASSERT_EQ(NodeStatus::IDLE, parallel_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, state);


}

TEST_F(ComplexParallelTest, Condition3False)
{
    condition_3.set_boolean_value(false);
    BT::NodeStatus state = root.executeTick();

    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_3.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_3.status());
    ASSERT_EQ(NodeStatus::RUNNING, parallel_1.status());
    ASSERT_EQ(NodeStatus::RUNNING, parallel_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, state);


}

TEST_F(ComplexParallelTest, Condition3FalseAction1Done)
{
    action_2.set_time(10);
    action_3.set_time(10);

    condition_3.set_boolean_value(false);
    BT::NodeStatus state = root.executeTick();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    ASSERT_EQ(NodeStatus::IDLE, condition_1.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_2.status());
    ASSERT_EQ(NodeStatus::IDLE, condition_3.status());
    ASSERT_EQ(NodeStatus::SUCCESS, action_1.status());   // success not read yet by the node parallel_1
    ASSERT_EQ(NodeStatus::RUNNING,
              parallel_1.status());   // parallel_1 hasn't realize (yet) that action_1 has succeeded

    state = root.executeTick();

    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, parallel_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, action_3.status());
    ASSERT_EQ(NodeStatus::RUNNING, parallel_2.status());
    ASSERT_EQ(NodeStatus::RUNNING, state);

    state = root.executeTick();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    state = root.executeTick();

    ASSERT_EQ(NodeStatus::IDLE, parallel_2.status());
    ASSERT_EQ(NodeStatus::IDLE, action_1.status());
    ASSERT_EQ(NodeStatus::IDLE, parallel_1.status());
    ASSERT_EQ(NodeStatus::IDLE, action_3.status());
    ASSERT_EQ(NodeStatus::IDLE, parallel_2.status());
    ASSERT_EQ(NodeStatus::SUCCESS, state);


}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
