#include "macros.h"

#include <stack>
#include <queue>
#include <memory>
#include <optional>
#include <initializer_list>
#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>

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
	// iteration version
	template <typename FN>
	void BFS(TreeNode* node, FN fn)
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
			if (n)
			{
				fn(*n);
				nodes.push(n->left);
				nodes.push(n->right);
			}
		}
	}

	//Pre - order, NLR
	template <typename FN>
	void DFS(TreeNode* node, FN fn)
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
	void DFS_NLR_r(TreeNode* n, FN fn)
	{
		if (n == nullptr) return;

		fn(*n);
		DFS_NLR_r(n->left, fn);
		DFS_NLR_r(n->right, fn);
	}
	//Post - order, LRN
	template <typename FN>
	void DFS_LRN_r(TreeNode* n, FN fn)
	{
		if (n == nullptr) return;

		DFS_LRN_r(n->left, fn);
		DFS_LRN_r(n->right, fn);
		fn(*n);
	}
	//In - order, LNR
	template <typename FN>
	void DFS_LNR_r(TreeNode* n, FN fn)
	{
		if (n == nullptr) return;

		DFS_LNR_r(n->left, fn);
		fn(*n);
		DFS_LNR_r(n->right, fn);
	}
	//Reverse pre - order, NRL
	template <typename FN>
	void DFS_NRL_r(TreeNode* n, FN fn)
	{
		if (n == nullptr) return;

		fn(*n);
		DFS_NRL_r(n->right, fn);
		DFS_NRL_r(n->left, fn);
	}
	//Reverse post - order, RLN
	template <typename FN>
	void DFS_RLN_r(TreeNode* n, FN fn)
	{
		if (n == nullptr) return;

		DFS_RLN_r(n->right, fn);
		DFS_RLN_r(n->left, fn);
		fn(*n);
	}
	//Reverse in - order, RNL
	template <typename FN>
	void DFS_RNL_r(TreeNode* n, FN fn)
	{
		if (n == nullptr) return;

		DFS_RNL_r(n->right, fn);
		fn(*n);
		DFS_RNL_r(n->left, fn);
	}

	//----------------------------------------------------------------------------------
	void print(TreeNode* node, std::string_view caption = "")
	{
		std::queue<TreeNode*> nodes;
		nodes.push(node);

		std::cout << caption << " print:: { ";

		while (!std::empty(nodes))
		{
			auto* n = nodes.front();
			nodes.pop();
			if (n)
			{
				std::cout << n->val << ", ";
				nodes.push(n->left);
				nodes.push(n->right);
			}
			else
			{
				std::cout << "std::nullopt, ";
			}
		}

		std::cout << "};\n";
	}

	int maxSum(TreeNode* n)
	{
		if (n == nullptr)
		{
			return 0;
		}
		return n->val + std::max(maxSum(n->left), maxSum(n->right));
	}
	
	int maxlev(TreeNode* n)
	{
		if (n == nullptr)
		{
			return 0;
		}
		return 1 + std::max(maxlev(n->left), maxlev(n->right));
	}
	
	//======================================================================================================
	//help and manege raw pointered tree for tests
	class Tree final
	{
		std::unique_ptr<TreeNode> mRoot;

		//disble move / copy
		Tree(const Tree&) = delete;
		Tree& operator=(const Tree&) = delete;
		Tree(Tree&&) = delete;
		Tree& operator=(Tree&&) = delete;

	public:
		using tElementOfList = std::optional<int>;

		//empty
		Tree()
		: mRoot{nullptr}
		{
		}

		//take to own
		Tree(TreeNode* root)
			: mRoot{ root }
		{
		}

		//make from binary heap representation
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

				bool isInserted = false;
				//left
				if (*it)
				{
					nodes.push(new TreeNode(it->value()));
					n->left = nodes.back();
					isInserted = true;
				}
				++it;

				//right
				if (*it)
				{
					nodes.push(new TreeNode(it->value()));
					n->right = nodes.back();
					isInserted = true;
				}
				++it;
				
				if (isInserted)
				{
					nodes.pop();
				}
			}
		}

		TreeNode* get()
		{
			return mRoot.get();
		}

		~Tree()
		{
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


			//Tree t1{ 1, std::nullopt ,2 };
			//RUN(t1, BFS);
			//RUN(t1, DFS);
			//RUN(t1, DFS_NLR_r);
			//RUN(t1, DFS_LRN_r);
			//RUN(t1, DFS_LNR_r);
			//RUN(t1, DFS_NRL_r);
			//RUN(t1, DFS_RLN_r);
			//RUN(t1, DFS_RNL_r);


			//std::cout << "***----------------------------------------------------- \n";
			Tree  t2{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
			//Tree  t2{ 11,21,22,31,32,33,34 };
			print(t2.get(), "t2");
			RUN(t2, BFS);
			RUN(t2, DFS);
			RUN(t2, DFS_NLR_r);
			RUN(t2, DFS_LRN_r);
			RUN(t2, DFS_LNR_r);
			//RUN(t2, DFS_NRL_r);
			//RUN(t2, DFS_RLN_r);
			//RUN(t2, DFS_RNL_r);


			//std::cout << "***----------------------------------------------------- \n";
			//Tree  t3{ 11,21,22,31,32,33,34,41,42,43,44,45,46,47,48 };
			//RUN(t3, BFS);
			//RUN(t3, DFS);
			//RUN(t3, DFS_NLR_r);
			//RUN(t3, DFS_LRN_r);
			//RUN(t3, DFS_LNR_r);
			//RUN(t3, DFS_NRL_r);
			//RUN(t3, DFS_RLN_r);
			//RUN(t3, DFS_RNL_r);


			std::cout << "***----------------------------------------------------- \n";
			Tree  t4{ 11,21,22,31,32,33,34, 41, 42, 43, 44, 45, 46, 47, 48/*, 51, 52, 53, 54, 55, 56, 57, 58, 61, 62, 63, 64, 65, 66, 67, 68*/ };
			RUN(t4, BFS);
			RUN(t4, DFS);
			RUN(t4, DFS_NLR_r);
			RUN(t4, DFS_LRN_r);
			RUN(t4, DFS_LNR_r);

#undef RUN


			std::cout << "***----------------------------------------------------- \n";
			Tree  t_rigt_only{ 1, std::nullopt, 2, std::nullopt, std::nullopt, std::nullopt, 3 };
			print(t_rigt_only.get(), "rigt_only");
			Tree  t_left_only{ 1, 2, std::nullopt, 3, std::nullopt, std::nullopt, std::nullopt };
			print(t_left_only.get(), "left_only");
		}
	};
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

	//100. Same Tree
	// https://leetcode.com/problems/same-tree/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_100 
	{
	public:
		bool isSameTree(TreeNode* p, TreeNode* q) 
		{
			if (p == nullptr && q == nullptr) return true;
			if (p == nullptr || q == nullptr) return false;

			// both != NULL
			return (p->val == q->val) 
				&& isSameTree(p->left, q->left) 
				&& isSameTree(p->right, q->right);
		}

		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "100. Same Tree \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_100 s;

			{
				Tree t1{ 1, std::nullopt ,2 };
				Tree t2{ 1, std::nullopt ,2 };
				IS_TRUE(s.isSameTree(t1.get(), t2.get()));
			}
			{
				Tree t1{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
				Tree t2{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
				IS_TRUE(s.isSameTree(t1.get(), t2.get()));
			}

			{
				Tree t1{ 1, std::nullopt ,2 };
				Tree t2{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
				IS_TRUE(s.isSameTree(t1.get(), t2.get()) == false);
			}
		}
	};

	//101. Symmetric Tree
	// https://leetcode.com/problems/symmetric-tree/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_101 
	{
	public:

		bool isMirror(TreeNode* p, TreeNode* q)
		{
			if (p == nullptr && q == nullptr) return true;
			if (p == nullptr || q == nullptr) return false;

			// both != NULL
			return (p->val == q->val)
				&& isMirror(p->left, q->right)
				&& isMirror(p->right, q->left);
		}

		bool isSymmetric(TreeNode* root) 
		{
			if (root == nullptr ) return true;

			return isMirror(root->left, root->right);
		}

		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "101. Symmetric Tree \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_101 s;

			{
				Tree t{ 1, std::nullopt ,2 };
				IS_TRUE(s.isSymmetric(t.get()) == false);
			}
			{
				Tree t{ 1, 2 ,2 };
				IS_TRUE(s.isSymmetric(t.get()));
			}
			{
				Tree t{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
				IS_TRUE(s.isSymmetric(t.get()) == false);
			}
			{
				Tree t{ 1,2,2,3,4,4,3 };
				IS_TRUE(s.isSymmetric(t.get()));
			}
		}
	};

	//637. Average of Levels in Binary Tree
	// https://leetcode.com/problems/average-of-levels-in-binary-tree/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_637 
	{
	public:
		std::vector<double> averageOfLevels_v1(TreeNode* root)
		{
			std::vector<double> result;

			std::queue< TreeNode*> nodes;
			if (root != nullptr)
			{
				nodes.push(root);
			}

			while (!std::empty(nodes))
			{
				std::queue<TreeNode*> tmp;
				double summ = 0.0;
				int count = 0;

				while (!std::empty(nodes))
				{
					auto* n = nodes.front();
					nodes.pop();
					if (n)
					{
						summ += n->val;
						count ++;

						tmp.push(n->left);
						tmp.push(n->right);
					}
				}

				nodes = tmp;
				if(count != 0) result.push_back(summ / count);
			}

			return result;
		}

		std::vector<double> averageOfLevels(TreeNode* root)
		{
			std::vector<double> result;

			if (root == nullptr)
			{
				return result;
			}

			std::queue< TreeNode*> nodes;
			nodes.push(root);

			while (!std::empty(nodes))
			{
				double summ = 0.0;
				int count = nodes.size();
				for (int i = 0; i < count; ++i)
				{
					auto* n = nodes.front();
					nodes.pop();

					summ += n->val;
					if (n->left)
					{
						nodes.push(n->left);
					}
					if (n->right)
					{
						nodes.push(n->right);
					}
				}
				if (count != 0) result.push_back(summ / count);
			}

			return result;
		}


		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "637. Average of Levels in Binary Tree \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_637 s;

			std::vector<double> EXPECTED{ 3.0, 14.5, 11.0 };

			{
				Tree t{ 3, 9, 20, std::nullopt, std::nullopt, 15, 7 };
				IS_TRUE(s.averageOfLevels(t.get()) == EXPECTED);
			}
			{
				Tree t{ 3,9,20,15,7 };
				IS_TRUE(s.averageOfLevels(t.get()) == EXPECTED);
			}

			{
				Tree t{ 1, std::nullopt ,2 };
				std::vector<double> E{ 1.0, 2.0 };
				IS_TRUE(s.averageOfLevels(t.get()) == E);
			}
			{
				Tree t{ 1, 2 ,2 };
				std::vector<double> E{ 1.0, 2.0 };
				IS_TRUE(s.averageOfLevels(t.get()) == E);
			}
		}
	};

	//105. Construct Binary Tree from Preorder and Inorder Traversal
	// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_105
	{
	public:
		TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
		{
			if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size())
			{
				return nullptr;
			}

			std::unordered_map<int, int> indxes;
			for (int i = 0; i < inorder.size(); ++i)
			{
				indxes[inorder[i]] = i;
			}

			struct Builder
			{
				const std::vector<int>& m_preorder;
				const std::vector<int>& m_inorder;
				const std::unordered_map<int, int>& m_indxes;

				Builder(const std::vector<int>& preorder, const std::vector<int>& inorder, const std::unordered_map<int, int>& indxes)
					: m_preorder(preorder)
					, m_inorder(inorder)
					, m_indxes(indxes)
				{

				}

				TreeNode* build(int preBeg, int preEnd, int inBeg, int inEnd)
				{
					if (preBeg > preEnd) return nullptr;

					const int val = m_preorder[preBeg];
					const int index = m_indxes.at(val);
					const int len = index - inBeg;

					TreeNode* root = new TreeNode(val);
					root->left = build(preBeg + 1, preBeg + len, inBeg, inBeg + len);
					root->right = build(preBeg + len + 1, preEnd, inBeg + len + 1, inEnd);

					return root;
				}
			};
;
			Builder b{ preorder, inorder, indxes };

			return b.build(0, preorder.size()-1, 0, inorder.size()-1);
		}

		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "105. Construct Binary Tree from Preorder and Inorder Traversal \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_105 s;

			{
				std::vector<int> preorder{};
				std::vector<int> inorder{};
				Tree t{ s.buildTree(preorder, inorder)};

				print(t.get(), "1)");
			}

			{
				std::vector<int> preorder{ 3, 9, 20, 15, 7 };
				std::vector<int> inorder{ 9, 3, 15, 20, 7 };
				Tree t{ s.buildTree(preorder, inorder) };

				print(t.get(), "2)");
			}
		}
	};

	//112. Path Sum
	// https://leetcode.com/problems/path-sum/description/
	class Solution_112
	{
	public:
		bool hasPathSum(TreeNode* root, int targetSum) 
		{

		}

		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "112. Path Sum \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_112 s;
/*
Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.

Example 1:
Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path with the target sum is shown.


Example 2:
Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: There two root-to-leaf paths in the tree:
(1 --> 2): The sum is 3.
(1 --> 3): The sum is 4.
There is no root-to-leaf path with sum = 5.


Example 3:
Input: root = [], targetSum = 0
Output: false
Explanation: Since the tree is empty, there are no root-to-leaf paths.


*/
		}

	};

}

void rq3_binary_tree_test()
{
	//Solution_104::test();
	//Solution_100::test();
	//Solution_101::test();
	//Solution_637::test();
	//Solution_105::test();
	Solution_112::test();

	//helper
	//Tree::test();
}
