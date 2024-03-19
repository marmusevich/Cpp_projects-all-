#include "macros.h"

#include <algorithm>
#include <list>
#include <string_view>
#include <iterator>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <type_traits>
#include <cctype>
#include <limits>
#include <memory>

namespace
{
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


/**
 * Definition for a binary tree node.
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


	//104. Maximum Depth of Binary Tree
	// https://leetcode.com/problems/maximum-depth-of-binary-tree/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_104
	{
	public:

		int maxDepth(TreeNode* root) {

			return 0;
		}



		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "104. Maximum Depth of Binary Tree \n";
			std::cout << "----------------------------------------------------- \n";

			//Solution_104 s;
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



}

void rq3_binary_tree_test()
{
	Solution_104::test();
}
