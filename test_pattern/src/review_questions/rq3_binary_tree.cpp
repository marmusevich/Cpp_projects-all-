#include "macros.h"

#include <stack>
#include <queue>
#include <memory>
#include <optional>
#include <initializer_list>
#include <iostream>
#include <array>
#include <vector>

namespace
{
	/**
	 * Definition for a binary tree node.   FROM LEETCODE
	 * struct TreeNode {
	 *     int val;
	 *     TreeNode *left;
	 *     TreeNode *right;
	 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
	 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	 * };
	 */
	struct TreeNode
	{
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};


	//======================================================================================================
		//help and manege raw pointered tree for tests
	class Tree final
	{
		std::unique_ptr<TreeNode> mRoot;

		//std::vector<std::unique_ptr<TreeNode>>  holdAll;



		//disble move / copy
		Tree(const Tree&) = delete;
		Tree& operator=(const Tree&) = delete;
		Tree(Tree&&) = delete;
		Tree& operator=(Tree&&) = delete;

	public:
		using tElementOfList = std::optional<int>;

		Tree()
		: mRoot{nullptr}
		{
		}

		Tree(std::initializer_list<tElementOfList> il)
			: Tree()
		{
			if (std::empty(il))
			{
				return;
			}
			std::queue< TreeNode*> nodes;

			auto it = il.begin();

			mRoot.reset( new TreeNode(it->value()) );
			nodes.push(mRoot.get());
			++it;

			while (it != il.end())
			{
				auto n = nodes.front();
				nodes.pop();
				
				//left
				if (*it)
				{
					nodes.push(new TreeNode(it->value()));
					n->left = nodes.back();
				}
				++it;

				//right
				if (*it)
				{
					nodes.push(new TreeNode(it->value()));
					n->right = nodes.back();
				}
				++it;
			}
		}

		~Tree()
		{
			//todo delete
			//std::vector<TreeNode*>  holdAll
		}

		TreeNode* get()
		{
			return mRoot.get();
		}

		template <typename FN>
		void BFS(FN fn)
		{
			std::queue< TreeNode*> nodes;
			if (mRoot)
			{
				nodes.push(mRoot.get());
			}
			
			while (!std::empty(nodes))
			{
				auto* n = nodes.front();
				nodes.pop();
				if(n)
				{
					fn(*n);
					nodes.push(n->left);
					nodes.push(n->right);
				}
			}
		}

		template <typename FN>
		void DFS(FN fn)
		{
			std::stack< TreeNode*> nodes;
			if (mRoot)
			{
				nodes.push(mRoot.get());
			}

			while (!std::empty(nodes))
			{
				auto* n = nodes.top();
				nodes.pop();
				if (n)
				{
					fn(*n);
					nodes.push(n->right);
					nodes.push(n->left);
				}
			}
		}

		//----------------------------------------------------------------------------------
		template <typename FN>
		friend void BFS_r(TreeNode* n, FN fn)
		{

		}

		template <typename FN>
		friend void DFS_r(TreeNode* n, FN fn)
		{

		}

		friend int maxSum(TreeNode* n)
		{
			if (n == nullptr)
			{
				return 0;
			}
			return n->val + std::max(maxSum(n->left), maxSum(n->right));
		}


		friend int maxlev(TreeNode* n)
		{
			if (n == nullptr)
			{
				return 0;
			}
			return 1 + std::max(maxlev(n->left), maxlev(n->right));

			//int v = 1;
			//int l = maxlev(n->left);
			//int r = maxlev(n->right);
			//int m = std::max(l, r);
			//printf("v = %d, l = %d, r = %d, m = %d, (v + m) = %d \n", v, l, r, m, v + m);
			//return v + m;
		}


		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "Binary Tree Helper \n";
			std::cout << "----------------------------------------------------- \n";

			auto fnPrint = [](const TreeNode& n)
				{
					std::cout << "val = " << n.val //<< " \n"
						<< "\t left = " <<(n.left != nullptr ? n.left->val : -1) //<< " \n"
						<< "\t right = " << (n.right != nullptr ? n.right->val : -1) << " \n"
						<< ""; 
				};


			Tree t1{ 1, std::nullopt ,2 };
			//t1.BFS(fnPrint);
			//std::cout << "----- \n";
			//t1.DFS(fnPrint);
			//std::cout << "----- \n";
			auto m1 = maxlev(t1.get());
			std::cout << "maxlev = " << m1 << " \n";


			std::cout << "***----------------------------------------------------- \n";
			Tree  t2{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
			//t2.BFS(fnPrint);
			//std::cout << "----- \n";
			//t2.DFS(fnPrint);
			//std::cout << "----- \n";
			auto m2 = maxlev(t2.get());
			std::cout << "maxlev = " << m2 << " \n";


			std::cout << "***----------------------------------------------------- \n";
			Tree  t3{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
			//t3.BFS(fnPrint);
			//std::cout << "----- \n";
			//t3.DFS(fnPrint);
			//std::cout << "----- \n";
			auto m3 = maxlev(t3.get());
			std::cout << "maxlev = " << m3 << " \n";



			//IS_TRUE(? ? ? == EXPECT);

			/*
				Example 1:
				Input: root = [3,9,20,null,null,15,7]
				Output: 3

				Example 2:
				Input: root = [1,null,2]
				Output: 2

			*/


		}


	};


	//======================================================================================================
	/*   >>>>>>>>>>>>>>>>>>> template for solution
		//
		class Solution_
		{
		public:


			static void test()
			{
				std::cout << "----------------------------------------------------- \n";
				std::cout << " \n";
				std::cout << "----------------------------------------------------- \n";

				Solution_ s;
				IS_TRUE(??? == EXPECT);
			}
		};
	*/
	//======================================================================================================



	//104. Maximum Depth of Binary Tree
	// https://leetcode.com/problems/maximum-depth-of-binary-tree/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_104
	{
	public:

		int maxDepth(TreeNode* root) 
		{
			if (root == nullptr)
			{
				return 0;
			}
			return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
		}

		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "104. Maximum Depth of Binary Tree \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_104 s;

			Tree t1{ 1, std::nullopt ,2 };
			IS_TRUE(s.maxDepth(t1.get()) == 2);

			Tree  t2{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
			IS_TRUE(s.maxDepth(t2.get()) == 3);
		}
	};



}

void rq3_binary_tree_test()
{
	Solution_104::test();



	//helper
	Tree::test();

}
