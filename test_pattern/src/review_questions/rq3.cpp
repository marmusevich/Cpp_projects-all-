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
#include <functional>
#include <thread>
#include <stack>


namespace
{
	//27. Remove Element
	// https://leetcode.com/problems/remove-element/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_27
	{
	public:
		int removeElement(std::vector<int>& nums, int val)
		{
			if (nums.empty()) // special case - empty 
			{
				return 0;
			}

			if (nums.size() == 1)// special case - only one element
			{
				if (*(nums.begin()) == val)//end we must delete it
				{
					return 0;
				}
				return 1;//or not
			}


			auto it_write = nums.begin();
			auto it_read = nums.begin();

			int c = 0;

			while (it_read != nums.end() && it_write != nums.end())
			{
				if (*it_write != val)
				{
					++it_write;
					++c;
				}
				else
				{
					if (it_read > it_write && *it_read != val)
					{
						//*it_write = *it_read;
						std::swap(*it_write, *it_read);
						++it_write;
						++c;
					}
				}
				++it_read;

			}

			return c;
		}


		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "27. Remove Element \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_27 s;

			{
				std::vector<int> nums{  };
				const int val = 2;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{  };
				IS_TRUE(k == EXPECT.size());
			}

			{
				std::vector<int> nums{ 1 };
				const int val = 1;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{  };
				IS_TRUE(k == EXPECT.size());
			}

			{
				std::vector<int> nums{ 1 };
				const int val = 2;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{ 1 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::is_permutation(nums.begin(), std::next(nums.begin(), k - 1), EXPECT.begin()));
			}

			{
				std::vector<int> nums{ 3, 2, 2, 3 };
				const int val = 3;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{ 2, 2 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::is_permutation(nums.begin(), std::next(nums.begin(), k - 1), EXPECT.begin()));
			}
			{
				std::vector<int> nums{ 3, 2, 2, 3 };
				const int val = 1;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{ 3, 2, 2, 3 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::is_permutation(nums.begin(), std::next(nums.begin(), k - 1), EXPECT.begin()));
			}
			{
				std::vector<int> nums{ 3, 3 };
				const int val = 3;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{ };
				IS_TRUE(k == EXPECT.size());
			}


			{
				std::vector<int> nums{ 0, 1, 2, 2, 3, 0, 4, 2 };
				const int val = 2;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{ 0, 1, 3, 0, 4 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::is_permutation(nums.begin(), std::next(nums.begin(), k - 1), EXPECT.begin()));
			}
		}
	};


	//26. Remove Duplicates from Sorted Array
	//
	class Solution_26
	{
	public:
		int removeDuplicates(std::vector<int>& nums)
		{
			if (nums.empty())
			{
				return 0;
			}

			auto it_write = nums.begin();
			auto it_read = nums.begin();

			while (it_read != nums.end())
			{
				if (*it_write != *it_read)
				{
					++it_write;
					if (it_write != it_read)
					{
						//*it_write = *it_read;
						std::swap(*it_write, *it_read);
					}
				}

				++it_read;
			}

			return std::distance(nums.begin(), it_write) + 1;
		}


		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "26. Remove Duplicates from Sorted Array \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_26 s;

			{
				std::vector<int> nums{  };
				int k = s.removeDuplicates(nums);

				const std::vector<int> EXPECT{  };
				IS_TRUE(k == EXPECT.size());
			}

			{
				std::vector<int> nums{ 1, 2, 3 };
				int k = s.removeDuplicates(nums);

				const std::vector<int> EXPECT{ 1, 2, 3 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::vector/*temp*/(nums.begin(), std::next(nums.begin(), k)) == EXPECT);
			}

			{
				std::vector<int> nums{ 1, 1, 2 };
				int k = s.removeDuplicates(nums);

				const std::vector<int> EXPECT{ 1, 2 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::vector/*temp*/(nums.begin(), std::next(nums.begin(), k)) == EXPECT);
			}

			{
				std::vector<int> nums{ 0,0,1,1,1,2,2,3,3,4 };
				int k = s.removeDuplicates(nums);

				const std::vector<int> EXPECT{ 0,1,2,3,4 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::vector/*temp*/(nums.begin(), std::next(nums.begin(), k)) == EXPECT);

			}
		}
	};

	//20. Valid Parentheses
	//https://leetcode.com/problems/valid-parentheses/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_20
	{
	public:
		bool isValid(std::string s)
		{
			std::stack<char> preds;
			for (const auto cur : s)
			{
				if (cur == '(' || cur == '{' || cur == '[') //open braces
				{
					preds.push(cur);
				}
				else //close braces
				{
					if (preds.empty()) { return false; }

					const auto last = preds.top();
					//close brace is equal close
					if ((last == '{' && cur == '}')
						|| (last == '(' && cur == ')')
						|| (last == '[' && cur == ']'))
					{
						preds.pop();
					}
					else
					{
						return false;
					}
				}
			}

			return preds.empty();
		}

		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "20. Valid Parentheses \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_20 s;

			IS_TRUE(s.isValid("") == true);
			IS_TRUE(s.isValid("()") == true);
			IS_TRUE(s.isValid("()[]{}") == true);
			IS_TRUE(s.isValid("(]") == false);
		}
	};

	//392. Is Subsequence
	//https://leetcode.com/problems/is-subsequence/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_392
	{
	public:
		bool isSubsequence(std::string s, std::string t)
		{
			auto it_s = s.begin();
			auto it_t = t.begin();
			while (it_s != s.end())
			{
				while (it_t != t.end() && *it_s != *it_t)
				{
					++it_t;
				}

				if (it_t == t.end()) // the end of t, bat not of s
				{
					return false;
				}

				if (*it_s == *it_t)
				{
					++it_s;
					++it_t;
				}
			}

			return it_s == s.end(); // check all charasters
		}

		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "392. Is Subsequence \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_392 s;

			IS_TRUE(s.isSubsequence("", "") == true);

			IS_TRUE(s.isSubsequence("abc", "ahbgdc") == true);
			IS_TRUE(s.isSubsequence("axc", "ahbgdc") == false);
			IS_TRUE(s.isSubsequence("a", "b") == false);
			IS_TRUE(s.isSubsequence("aaaaaa", "bbaaaa") == false);
		}
	};


	//383. Ransom Note
	//https://leetcode.com/problems/ransom-note/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_383
	{
	public:
		bool canConstruct(std::string ransomNote, std::string magazine)
		{

			std::unordered_map<char, int> chars;

			//hash 'magazine'
			for (const auto c : magazine)
			{
				auto it = chars.find(c);
				if (it != chars.end())
				{
					++(*it).second;
				}
				else
				{
					chars[c] = 1;
				}

			}

			//try build 'ransomNote' from 'magazine' chars
			for (const auto c : ransomNote)
			{
				auto it = chars.find(c);
				if (it == chars.end())
				{
					return false;
				}
				else
				{
					auto& count = (*it).second;
					--count;
					if (count < 0)
					{
						return false;
						/*and remove ch from map*/
					}
				}
			}

			return true;
		}

		static void test()
		{
			std::cout << "----------------------------------------------------- \n";
			std::cout << "383. Ransom Note \n";
			std::cout << "----------------------------------------------------- \n";

			Solution_383 s;

			IS_TRUE(s.canConstruct("", "") == true);

			IS_TRUE(s.canConstruct("a", "b") == false);
			IS_TRUE(s.canConstruct("aa", "ab") == false);
			IS_TRUE(s.canConstruct("aa", "aab") == true);
		}
	};

}


void rq3_test()
{
	Solution_26::test();
	Solution_27::test();
	Solution_20::test();
	Solution_392::test();
	Solution_383::test();
}
