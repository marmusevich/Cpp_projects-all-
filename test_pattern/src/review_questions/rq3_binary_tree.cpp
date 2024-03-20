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


		TreeNode* get()
		{
			return mRoot.get();
		}
		//----------------------------------------------------------------------------------
		// iteration version
		template <typename FN>
		friend void BFS(TreeNode* node, FN fn)
		{
			std::queue< TreeNode*> nodes;
			if (node != nullptr)
			{
				nodes.push(node);
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

		//Pre - order, NLR
		template <typename FN>
		friend void DFS(TreeNode* node, FN fn)
		{
			std::stack< TreeNode*> nodes;
			if (node != nullptr)
			{
				nodes.push(node);
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
		// recursion version
		//Pre - order, NLR
		template <typename FN>
		friend void DFS_NLR_r(TreeNode* n, FN fn)
		{
			if (n == nullptr) return;

			fn(*n);
			DFS_NLR_r(n->left, fn);
			DFS_NLR_r(n->right, fn);
		}
		//Post - order, LRN
		template <typename FN>
		friend void DFS_LRN_r(TreeNode* n, FN fn)
		{
			if (n == nullptr) return;

			DFS_LRN_r(n->left, fn);
			DFS_LRN_r(n->right, fn);
			fn(*n);
		}
		//In - order, LNR
		template <typename FN>
		friend void DFS_LNR_r(TreeNode* n, FN fn)
		{
			if (n == nullptr) return;

			DFS_LNR_r(n->left, fn);
			fn(*n);
			DFS_LNR_r(n->right, fn);
		}
		//Reverse pre - order, NRL
		template <typename FN>
		friend void DFS_NRL_r(TreeNode* n, FN fn)
		{
			if (n == nullptr) return;

			fn(*n);
			DFS_NRL_r(n->right, fn);
			DFS_NRL_r(n->left, fn);
		}
		//Reverse post - order, RLN
		template <typename FN>
		friend void DFS_RLN_r(TreeNode* n, FN fn)
		{
			if (n == nullptr) return;

			DFS_RLN_r(n->right, fn);
			DFS_RLN_r(n->left, fn);
			fn(*n);
		}
		//Reverse in - order, RNL
		template <typename FN>
		friend void DFS_RNL_r(TreeNode* n, FN fn)
		{
			if (n == nullptr) return;

			DFS_RNL_r(n->right, fn);
			fn(*n);
			DFS_RNL_r(n->left, fn);
		}
		//----------------------------------------------------------------------------------
		~Tree()
		{
			//todo delete
			//std::vector<TreeNode*>  holdAll


			DFS_LRN_r(mRoot.get(), [](TreeNode& n)
				{
					if (n.left != nullptr) 
					{
						delete n.left; 
						n.left = nullptr;
					}
					if (n.right != nullptr)
					{
						delete n.right;
						n.right = nullptr;
					}
				});
		}
		//----------------------------------------------------------------------------------



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

			auto fnPrint2 = [](const TreeNode& n)
				{
					std::cout << n.val << " ";
				};


#define RUN(TREE, FN) \
do \
{ \
	std::cout << #FN << " ==> { "; \
	FN(TREE.get(), fnPrint2); \
	std::cout << "}\n"; \
} \
while (false)
//[END] RUN(TREE, FN)


			Tree t1{ 1, std::nullopt ,2 };
			//BFS(t1.get(), fnPrint);
			//std::cout << "----- \n";
			//DFS(t1.get(), fnPrint);
			//std::cout << "----- \n";
			RUN(t1, BFS);
			RUN(t1, DFS);
			RUN(t1, DFS_NLR_r);
			RUN(t1, DFS_LRN_r);
			RUN(t1, DFS_LNR_r);
			RUN(t1, DFS_NRL_r);
			RUN(t1, DFS_RLN_r);
			RUN(t1, DFS_RNL_r);


			std::cout << "***----------------------------------------------------- \n";
			//Tree  t2{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
			Tree  t2{ 11,21,22,31,32,33,34 };
			//BFS(t2.get(), fnPrint);
			//std::cout << "----- \n";
			//DFS(t2.get(), fnPrint);
			//std::cout << "----- \n";
			RUN(t2, BFS);
			RUN(t2, DFS);
			RUN(t2, DFS_NLR_r);
			RUN(t2, DFS_LRN_r);
			RUN(t2, DFS_LNR_r);
			RUN(t2, DFS_NRL_r);
			RUN(t2, DFS_RLN_r);
			RUN(t2, DFS_RNL_r);


			std::cout << "***----------------------------------------------------- \n";
			Tree  t3{ 11,21,22,31,32,33,34,41,42,43,44,45,46,47,48 };
			//BFS(t3.get(), fnPrint);
			//std::cout << "----- \n";
			//DFS(t3.get(), fnPrint);
			//std::cout << "----- \n";
			RUN(t3, BFS);
			RUN(t3, DFS);
			RUN(t3, DFS_NLR_r);
			RUN(t3, DFS_LRN_r);
			RUN(t3, DFS_LNR_r);
			RUN(t3, DFS_NRL_r);
			RUN(t3, DFS_RLN_r);
			RUN(t3, DFS_RNL_r);


#undef RUN
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
