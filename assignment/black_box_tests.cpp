//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Andrej Pavlovič <xpavlo14@stud.fit.vutbr.cz>
// $Date:       $2022-02-27
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Andrej Pavlovič
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"
#include "red_black_tree.h"


using namespace std;

class EmptyTree : public ::testing::Test {
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize small tree with values
        rootSmall = smallTree.InsertNode(1).second;

        // Initialize large tree with values
        for (int value: {10, 8, 9, 7, 11, 20, 1, -5, 3, -10}) {
            if (value == 7) { // node with value 7 will be root
                rootLarge = largeTree.InsertNode(value).second;
            } else {
                largeTree.InsertNode(value);
            }
        }
    }

    BinaryTree smallTree, largeTree;
    Node_t *rootSmall, *rootLarge;
};

class TreeAxioms : public NonEmptyTree {}; // For test suite naming prescription

// Pozn.: v zadaní je uvedené pomenovávanie testov s podtržítkom 'InsertNode_XXX' (str. 7),
// ale v GoogleTest GitHub doc je priamo spomenuté, že konvencia je podtržítka v názvoch
// testov nepoužívať
// https://github.com/google/googletest/blob/main/docs/primer.md#simple-tests

//============================================================================//
// Testing Red-Black Tree interface


// Tests Insert method conducted for empty tree
TEST_F(EmptyTree, InsertNode) {
    // Calling insert for empty tree with value 1
    pair<bool, Node_t *> pair = tree.InsertNode(1);
    Node_t *node = pair.second;

    // Test insert return values
    ASSERT_TRUE(node);
    EXPECT_TRUE(pair.first);

    // Test inserted node's properties
    EXPECT_FALSE(node->pParent);
    EXPECT_EQ(node->color, Color_t::BLACK);
    EXPECT_EQ(node->key, 1);
    ASSERT_TRUE(node->pLeft);
    ASSERT_TRUE(node->pRight);

    // Test its left child's properties
    Node_t *nodeLeft = node->pLeft;
    EXPECT_EQ(nodeLeft->pParent, node);
    EXPECT_FALSE(nodeLeft->pLeft);
    EXPECT_FALSE(nodeLeft->pRight);
    EXPECT_EQ(nodeLeft->color, Color_t::BLACK);

    // Test its right child's properties
    Node_t *nodeRight = node->pRight;
    EXPECT_EQ(nodeRight->pParent, node);
    EXPECT_FALSE(nodeRight->pLeft);
    EXPECT_FALSE(nodeRight->pRight);
    EXPECT_EQ(nodeRight->color, Color_t::BLACK);

    // Test inserting existing node with value 1
    pair = tree.InsertNode(1);
    EXPECT_FALSE(pair.first);
    EXPECT_EQ(pair.second, node);
}

// Tests Delete method conducted for empty tree
TEST_F(EmptyTree, DeleteNode) {
    // Test delete nodes with empty tree
    EXPECT_FALSE(tree.DeleteNode(1));
    EXPECT_FALSE(tree.DeleteNode(50));
    EXPECT_FALSE(tree.DeleteNode(-10));
    EXPECT_FALSE(tree.DeleteNode(0));
}

// Tests Find method conducted for empty tree
TEST_F(EmptyTree, FindNode) {
    // Test find nodes with empty tree
    EXPECT_FALSE(tree.FindNode(1));
    EXPECT_FALSE(tree.FindNode(50));
    EXPECT_FALSE(tree.FindNode(-10));
    EXPECT_FALSE(tree.FindNode(0));
}

// Tests Insert method conducted for NON-empty tree
// This test relies on a correct implementation of InsertNode method for empty tree
// which was tested above
TEST_F(NonEmptyTree, InsertNode_small) {
    // Calling insert with values 5 and -5
    pair<bool, Node_t *> pairSmaller, pairBigger;
    Node_t *nodeSmaller, *nodeBigger;
    pairSmaller = smallTree.InsertNode(-5);
    pairBigger = smallTree.InsertNode(5);
    nodeSmaller = pairSmaller.second;
    nodeBigger = pairBigger.second;

    // Test insert return values
    ASSERT_TRUE(nodeSmaller);
    ASSERT_TRUE(nodeBigger);
    EXPECT_TRUE(pairSmaller.first);
    EXPECT_TRUE(pairBigger.first);

    // Test root node's properties
    EXPECT_FALSE(rootSmall->pParent);
    EXPECT_EQ(rootSmall->color, Color_t::BLACK);
    EXPECT_EQ(rootSmall->key, 1);
    ASSERT_TRUE(rootSmall->pLeft);
    ASSERT_TRUE(rootSmall->pRight);

    // Test left (smaller) child's properties
    EXPECT_EQ(nodeSmaller->pParent, rootSmall);
    EXPECT_EQ(nodeSmaller->color, Color_t::RED);
    EXPECT_EQ(nodeSmaller->key, -5);
    ASSERT_TRUE(nodeSmaller->pLeft);
    ASSERT_TRUE(nodeSmaller->pRight);

    // Test right (bigger) child's properties
    EXPECT_EQ(nodeBigger->pParent, rootSmall);
    EXPECT_EQ(nodeBigger->color, Color_t::RED);
    EXPECT_EQ(nodeBigger->key, 5);
    ASSERT_TRUE(nodeBigger->pLeft);
    ASSERT_TRUE(nodeBigger->pRight);

    // Test both leaves of left (smaller) child
    for (Node_t *leafNode: {nodeSmaller->pLeft, nodeSmaller->pRight}) {
        EXPECT_EQ(leafNode->pParent, nodeSmaller);
        EXPECT_FALSE(leafNode->pLeft);
        EXPECT_FALSE(leafNode->pRight);
        EXPECT_EQ(leafNode->color, Color_t::BLACK);
    }

    // Test both leaves of right (bigger) child
    for (Node_t *leafNode: {nodeBigger->pLeft, nodeBigger->pRight}) {
        EXPECT_EQ(leafNode->pParent, nodeBigger);
        EXPECT_FALSE(leafNode->pLeft);
        EXPECT_FALSE(leafNode->pRight);
        EXPECT_EQ(leafNode->color, Color_t::BLACK);
    }
}

// Tests Delete method conducted for NON-empty tree
// This test relies on a correct implementation of InsertNode method for empty tree
// which was tested above
TEST_F(NonEmptyTree, DeleteNode_small) {
    EXPECT_TRUE(smallTree.DeleteNode(1));

    // No more tests possible, because tree is empty in this step
}

// Tests Find method conducted for NON-empty tree
// This test relies on a correct implementation of InsertNode method for empty tree
// which was tested above
TEST_F(NonEmptyTree, FindNode_small) {
    // Test find existing node
    Node_t *nodeFind = smallTree.FindNode(1);
    ASSERT_TRUE(nodeFind);
    EXPECT_EQ(nodeFind, rootSmall);

    // Test find non-existing node
    EXPECT_FALSE(smallTree.FindNode(2));
    EXPECT_FALSE(smallTree.FindNode(50));
    EXPECT_FALSE(smallTree.FindNode(-10));
    EXPECT_FALSE(smallTree.FindNode(0));
}

// Tests Insert method conducted for NON-empty tree
// This test relies on a correct implementation of InsertNode method for NON-empty tree
// which was tested above
TEST_F(NonEmptyTree, InsertNode_large) {
    // Insert node with value 2
    pair<bool, Node_t *> pair = largeTree.InsertNode(2);
    Node_t *newNode = pair.second;

    // Test insert return values
    ASSERT_TRUE(newNode);
    EXPECT_TRUE(pair.first);

    // Test new node's properties
    EXPECT_TRUE(newNode->pParent);
    EXPECT_EQ(newNode->color, Color_t::RED);
    EXPECT_EQ(newNode->key, 2);
    ASSERT_TRUE(newNode->pLeft);
    ASSERT_TRUE(newNode->pRight);

    // Test left child's properties of new node
    Node_t *leftNewNode = newNode->pLeft;
    EXPECT_EQ(leftNewNode->pParent, newNode);
    EXPECT_EQ(leftNewNode->color, Color_t::BLACK);
    EXPECT_FALSE(leftNewNode->pLeft);
    EXPECT_FALSE(leftNewNode->pRight);

    // Test right child's properties of new node
    Node_t *rightNewNode = newNode->pRight;
    EXPECT_EQ(rightNewNode->pParent, newNode);
    EXPECT_EQ(rightNewNode->color, Color_t::BLACK);
    EXPECT_FALSE(rightNewNode->pLeft);
    EXPECT_FALSE(rightNewNode->pRight);

    // Test overall correct place of new node in tree
    EXPECT_FALSE(newNode->pParent->pParent->pParent->pParent);
}

// Tests Delete method conducted for NON-empty tree
// This test relies on a correct implementation of InsertNode method for NON-empty tree
// which was tested above
TEST_F(NonEmptyTree, DeleteNode_large) {
    // Delete node and test its return value
    ASSERT_TRUE(largeTree.DeleteNode(10));

    // Test properties of parent value (should not be changed except left child pointer)
    Node_t *nodeParent = rootLarge->pRight->pRight;
    EXPECT_TRUE(nodeParent->pParent);
    EXPECT_TRUE(nodeParent->pRight);
    EXPECT_EQ(nodeParent->color, Color_t::BLACK);
    EXPECT_EQ(nodeParent->key, 11);
    ASSERT_TRUE(nodeParent->pLeft);

    // Test properties of left parent's node (should be black leaf now)
    Node_t *leftNode = nodeParent->pLeft;
    EXPECT_TRUE(leftNode->pParent);
    EXPECT_FALSE(leftNode->pRight);
    EXPECT_FALSE(leftNode->pLeft);
    EXPECT_EQ(nodeParent->color, Color_t::BLACK);
}

// Tests Find method conducted for NON-empty tree
// This test relies on a correct implementation of InsertNode method for NON-empty tree
// which was tested above
TEST_F(NonEmptyTree, FindNode_large) {
    // Test find existing node
    Node_t *nodeFind1 = largeTree.FindNode(9);
    Node_t *nodeFind2 = largeTree.FindNode(-10);
    Node_t *nodeFind3 = largeTree.FindNode(3);
    ASSERT_TRUE(nodeFind1);
    ASSERT_TRUE(nodeFind2);
    ASSERT_TRUE(nodeFind3);
    EXPECT_EQ(nodeFind1, rootLarge->pRight);
    EXPECT_EQ(nodeFind2, rootLarge->pLeft->pLeft->pLeft);
    EXPECT_EQ(nodeFind3, rootLarge->pLeft->pRight);

    // Test find non-existing node
    EXPECT_FALSE(smallTree.FindNode(2));
    EXPECT_FALSE(smallTree.FindNode(50));
    EXPECT_FALSE(smallTree.FindNode(-11));
    EXPECT_FALSE(smallTree.FindNode(0));
}


//============================================================================//
// Testing Red-Black Tree axioms
//
// These tests rely on a correct implementation of InsertNode method for empty and
// NON-empty tree, which was tested above
// These tests might crash with seg fault if some tests of InsertNode above fail


// Tests 1. axiom: All leaf nodes are considered black.
TEST_F(TreeAxioms, Axiom1) {
    vector<Node_t *> nodes = {
            rootLarge->pLeft->pLeft->pLeft,
            rootLarge->pLeft->pRight,
            rootLarge->pRight->pLeft,
            rootLarge->pRight->pRight->pLeft,
            rootLarge->pRight->pRight->pRight
    };

    // Iterate through all n-1 height nodes with no children to test their children (leaves) colors
    for (Node_t *node: nodes) {
        EXPECT_EQ(node->pLeft->color, Color_t::BLACK);
        EXPECT_EQ(node->pRight->color, Color_t::BLACK);
    }

    // Check nodes with one child and one leaf node (only one of that kind exists)
    EXPECT_EQ(rootLarge->pLeft->pLeft->pRight->color, Color_t::BLACK);
}

// Tests 2. axiom: A red node does not have a red child.
TEST_F(TreeAxioms, Axiom2) {
    vector<Node_t *> redNodes = {
            rootLarge->pLeft,
            rootLarge->pRight,
            rootLarge->pLeft->pLeft->pLeft,
            rootLarge->pRight->pRight->pRight,
            rootLarge->pRight->pRight->pLeft,
    };

    // Iterate through all red nodes and test their children colors
    for (Node_t *redNode: redNodes) {
        EXPECT_EQ(redNode->pLeft->color, Color_t::BLACK);
        EXPECT_EQ(redNode->pRight->color, Color_t::BLACK);
    }
}

// Tests 3. axiom: Every path from a given node to any of its descendant
// leave nodes goes through the same number of black nodes.
TEST_F(TreeAxioms, Axiom3) {
    vector<Node_t *> redNodes = {
            rootLarge->pLeft,
            rootLarge->pRight,
            rootLarge->pLeft->pLeft->pLeft,
            rootLarge->pRight->pRight->pRight,
            rootLarge->pRight->pRight->pLeft
    };

    vector<Node_t *> blackNodes = {
            rootLarge,
            rootLarge->pRight->pRight,
            rootLarge->pLeft->pLeft,
            rootLarge->pRight->pLeft,
            rootLarge->pLeft->pRight
    };

    // Test correct color of all (except leaves - which we already tested) nodes, which
    // will ensure 3rd axiom
    for (Node_t *redNode: redNodes) {
        EXPECT_EQ(redNode->color, Color_t::RED);
        EXPECT_EQ(redNode->color, Color_t::RED);
    }
    for (Node_t *blackNode: blackNodes) {
        EXPECT_EQ(blackNode->color, Color_t::BLACK);
        EXPECT_EQ(blackNode->color, Color_t::BLACK);
    }
}

/*** Konec souboru black_box_tests.cpp ***/
