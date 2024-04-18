#include <algorithm>
#include <assert.h>
#include <iostream>
#include "Binary_Search_Tree.h"
#include "SearchTreeTester.h"

SearchTreeTester::SearchTreeTester(const bool useConsoleOutput,
                                   const bool enableAllTests)
    : BinaryTreeTester(useConsoleOutput, enableAllTests)
{}

BinaryTree *SearchTreeTester::allocateTree()
{
    return new SearchTree;
}

void SearchTreeTester::check_addAndCount(const BinaryTree *tree, const int size)
{
    BinaryTreeTester::check_addAndCount(tree, size);
    assert(isSearchTree(tree));
}

void SearchTreeTester::check_remove(BinaryTree *tree, const int key,
                                    const bool result, const int size)
{
    BinaryTreeTester::check_remove(tree, key, result, size);
    assert(isSearchTree(tree));
}

void SearchTreeTester::check_clear(const BinaryTree *tree, const int size)
{
    BinaryTreeTester::check_clear(tree, size);
    assert(isSearchTree(tree));
}

void SearchTreeTester::check_assign(const BinaryTree *first,
                                    const BinaryTree *second)
{
    BinaryTreeTester::check_assign(first, second);
    assert(isSearchTree(first));
    assert(isSearchTree(second));
}


void SearchTreeTester::assign()
{
    if (!assignCheckEnabled()) {
        return;
    }

    SearchTree tree1;

    std::vector<int> nodeKeys = generateKeys();
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree1.add(nodeKeys[i]);
    }

    SearchTree tree2 = tree1; //Конструктор копирования
    check_assign(&tree1, &tree2);

    tree1 = tree1; //Присваивание самому себе
    check_assign(&tree1, &tree2); //Проверяем, что tree1 не сломалось

    tree1 = tree2; //Присваивание одинаковых по размеру деревьев
    check_assign(&tree1, &tree2);

    SearchTree tree3;
    tree1 = tree3; //Присваивание дерева меньшего размера
    check_assign(&tree1, &tree3);

    tree3 = tree2; //Присваивание дерева большего размера
    check_assign(&tree2, &tree3);
}

bool SearchTreeTester::isSearchTree(const BinaryTree *tree)
{
    if (useConsoleOutput()) {
        tree->printHorizontal();
        std::cout << "======\n";
    }
    std::vector<int> keys;
    treeKeysLnr(tree->root(), keys);
    return std::is_sorted(keys.begin(), keys.end());
}

void SearchTreeTester::treeKeysLnr(BinaryTree::Node *root, std::vector<int> &keys)
{
    if (!root) {
        return;
    }

    treeKeysLnr(root->left(), keys);
    keys.push_back(root->key());
    treeKeysLnr(root->right(), keys);
}
