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


namespace
{
	//27. Remove Element
	// https://leetcode.com/problems/remove-element/description/?envType=study-plan-v2&envId=top-interview-150
	class Solution_27
	{
	public:
		int removeElement_it_ver(std::vector<int>& nums, int val) 
		{
			auto it1 = nums.begin();
			auto it2 = nums.end();

			while (it1 < it2)
			{
				if (*it1 == val)
				{
					while (it1 < it2 && *(--it2) == val) {}
					std::swap(*it1, *it2);
				}
				++it1;
			}

			return std::distance(nums.begin(), it1);
		}

		int removeElement_2(std::vector<int>& nums, int val)
		{
			int ib = 0;
			int ik = nums.size();

			if (nums.size() == 1)
			{
				if (nums[0] != val) ib = 1;
			}
			else if (!nums.empty())
			{

				--ik;

				while (ib < ik)
				{
					if (nums[ib] == val)
					{
						while (ib < ik && nums[ik] == val) { --ik; }
						if (ib != ik) std::swap(nums[ib], nums[ik]);
					}
					++ib;
				}
			}
			else {}

			return ib;
		}

		int removeElement(std::vector<int>& nums, int val)
		{
			int ib = 0;
			int ik = nums.size();

			if (nums.size() == 1)
			{
				if (nums[0] != val) ib = 1;
			}
			else if (!nums.empty())
			{
				
				--ik;

				while (ib < ik)
				{
					if (nums[ib] == val)
					{
						while (ib < ik && nums[ik] == val) { --ik; }
						if(ib !=ik) std::swap(nums[ib], nums[ik]);
					}
					++ib;
				}
			}
			else {}

			return ib;
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
				IS_TRUE(std::is_permutation(nums.begin(), std::next(nums.begin(), k), EXPECT.begin()) );
			}

			{
				std::vector<int> nums{ 3, 2, 2, 3 };
				const int val = 3;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{ 2, 2 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::is_permutation(nums.begin(), std::next(nums.begin(), k), EXPECT.begin()));
			}
			{
				std::vector<int> nums{ 3, 3 };
				const int val = 3;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{ };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::is_permutation(nums.begin(), std::next(nums.begin(), k), EXPECT.begin()));
			}


			{
				std::vector<int> nums{ 0, 1, 2, 2, 3, 0, 4, 2 };
				const int val = 2;
				int k = s.removeElement(nums, val);

				const std::vector<int> EXPECT{ 0, 1, 4, 0, 3 };
				IS_TRUE(k == EXPECT.size());
				IS_TRUE(std::is_permutation(nums.begin(), std::next(nums.begin(), k), EXPECT.begin()));
			}
		}
	};


	//26. Remove Duplicates from Sorted Array
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

			//it_read++;

			while (it_read != nums.end())
			{
				if (*it_write != *it_read)
				{
					it_write++;
					if (it_write != it_read)
					{
						*it_write = *it_read;
					}
				}

				it_read++;
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




}


void rq3_test()
{
	//Solution_27::test();
	Solution_26::test();

}
