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

/*
Задачи
от Андрея
2   и найти уникальный елемент в неотсортированом масиве или вернуть что-то что будет значить что его нет например optional

3   когда-то давно еще просили написать бинарное дерево и релизовать find и insert
*/


namespace
{
	/*1   развернуть слова в строке "I am a programmer" -> "programmer a am I"*/
struct cTack1
{
	using tTokens = std::list<std::string>;

    static constexpr char* DELIMITERS { " \t\n" };

	static tTokens tokenize1(std::string_view in)
	{
		using namespace std;

		//auto it = find_if(cbegin(in), cend(in), 
		//	[](auto&& c) 
		//	{
		//		return any_of(cbegin(DELIMITERS), cend(DELIMITERS), c);
		//	});


		std::istringstream ss{ in.data()};


		return { };
	}

	static std::string reverse(std::string const& in)
	{
		auto const& tok = tokenize1(in);

		std::ostringstream ss;
		//std::copy(crbegin(tok), crend(tok), std::ostream_iterator<std::string>(ss, " "));

		if (!tok.empty())
		{
			auto itEnd = std::prev(crend(tok), 1);
			for (auto it = crbegin(tok); it != itEnd; ++it)
			{
				ss << *it << " ";
			}
			ss << *itEnd;
		}

		std::cout <<" >>" << ss.str() << "<< ";
		return ss.str();
	}

	static void test()
	{
		std::cout << "cTack1 - reverse words in sentence: \n";

		IS_TRUE(reverse("a b c") == "c b a");
		IS_TRUE(reverse("a b  \t \n  c") == "c b a");
		IS_TRUE(reverse("abc") == "abc");
		IS_TRUE(reverse("") == "");
		IS_TRUE(reverse("  \t  \n") == "");
	}
private:

};

/*  note need return size insted string
3. Longest Substring Without Repeating Characters
https://leetcode.com/problems/longest-substring-without-repeating-characters/
*/
struct Solution_3
{
	static std::string find_v1(const std::string_view in)
	{
		std::string res;
		auto l = in.begin();
		auto r = in.begin();
		const auto end = in.end();

		std::unordered_set<char> uniq;

		while (l != end && r != end)
		{
			while (r != end && uniq.find(*r) == uniq.end())
			{
				uniq.insert(*r);
				++r;
			}
			std::string temp_res{l, r};
			if (temp_res.size() > res.size())
			{
				res = temp_res;
			}
			if (auto it = uniq.find(*l); it != uniq.end())
			{
				uniq.erase(it);
			}
			++l;
		}

		return res;
	}

	static std::string find_v2(const std::string_view in)
	{
		std::string res;
		auto l = in.begin();
		auto r = in.begin();
		const auto end = in.end();

		std::unordered_set<char> uniq;

		while (l != end && r != end)
		{
			bool isInsert = true;
			while (r != end && isInsert)
			{
				isInsert = uniq.insert(*r).second;
				if(isInsert) ++r;
			}

			std::string temp_res{ l, r };
			if (temp_res.size() > res.size())
			{
				res = temp_res;
			}

			(void)uniq.extract(*l);
			++l;
		}

		return res;
	}

	static void test()
	{
		const std::array strs
		{
			"abcabcbb",
			"",
			"1",
			"bbbbbb",
			"pwwkew",
		};
		std::cout << " Longest Substring Without Repeating Characters   V - 1 \n";
		for (const auto s : strs)
		{
			const auto subStr{ find_v1(s) };
			std::cout << "<" << s << ">\t\t<" << subStr << ">\n";
		}

		//not work
		std::cout << " Longest Substring Without Repeating Characters   V - 2 \n";
		for (const auto s : strs)
		{
			const auto subStr{ find_v2(s) };
			std::cout << "<" << s << ">\t\t<" << subStr << ">\n";
		}
	}
};

void rotate_window()
{
	const int k = 3;
	const int s = 6;
	for (int i = 0; i <= k; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			const int indexR = (s - k + i + j) % (s); // сдвиг в право
			const int indexL = (s - i + j) % (s); // сдвиг в лево
			std::cout << "i = " << i << " j = " << j << " i+j = " << i + j << " R = " << indexR << "  L = " << indexL << "\n";
		}
		std::cout << "  \n";

	}
}

//67. Add Binary
class Solution_67 {
public:
	std::string addBinary(std::string a, std::string b) 
	{
		std::string res;
		auto it_a = a.crbegin();
		auto it_b = b.crbegin();

		const auto end_a = a.crend();
		const auto end_b = b.crend();

		char p{'0'};
		while (it_a != end_a || it_b != end_b)
		{
			char s{ '0' };
			char np{ '0' };

			const auto ca = (it_a != end_a) ? *it_a : '0';
			const auto cb = (it_b != end_b) ? *it_b : '0';

			if (ca == '1' && cb == '1') { np = '1'; }
			else if (ca == '1' || cb == '1') { s = '1';}
			else {/*nop*/ }

			if (s == '1' && p == '1') { np = '1'; s = '0'; }
			else if (s == '1' || p == '1') { s = '1'; }
			else {/*nop*/ }

			p = np;
			res = s + res;
			if (it_a != end_a) { ++it_a; }
			if (it_b != end_b) { ++it_b; }
		}

		if (p == '1') { res = p + res; }

		return res;
	}

	static void test()
	{
		std::cout << "----------------------------------------------------- \n";
		std::cout << "67. Add Binary \n";
		Solution_67 s;

		IS_TRUE(s.addBinary("11", "1") == "100");
		IS_TRUE(s.addBinary("1",  "11") == "100");
		IS_TRUE(s.addBinary("111", "1") == "1000");
		IS_TRUE(s.addBinary("1", "111") == "1000");
		IS_TRUE(s.addBinary("1010", "1011") == "10101");

		std::cout << "----------------------------------------------------- \n";
	}
};

//1. Two Sum
class Solution_1
{
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target)
	{
		std::unordered_map<int, int> valToIndex;
		for (int i = 0; i < nums.size(); ++i)
		{
			const auto val = nums[i];
			const auto neded = target - val;//must be: val + neded = target
			auto it = valToIndex.find(neded);
			if (it != valToIndex.end())
			{
				return { it->second, i };
			}
			valToIndex[val] = i;
		}

		return {};
	}

	static void test()
	{
		std::cout << "----------------------------------------------------- \n";
		std::cout << "1. Two Sum \n";
		Solution_1 s;

		{
			auto res = s.twoSum(std::vector<int>{ 2, 7, 11, 15 }, 9);
			const std::vector<int> EXPECT{ 0, 1 };
			IS_TRUE(res == EXPECT);
		}
		{
			auto res = s.twoSum(std::vector<int>{ 3, 2, 4 }, 6);
			const std::vector<int> EXPECT{ 1, 2 };
			IS_TRUE(res == EXPECT);
		}
		{
			auto res = s.twoSum(std::vector<int>{ 3, 3 }, 6);
			const std::vector<int> EXPECT{ 0, 1 };
			IS_TRUE(res == EXPECT);
		}

		std::cout << "----------------------------------------------------- \n";
	}
};

//209. Minimum Size Subarray Sum
class Solution_209 {
public:
    int minSubArrayLen(int target, const std::vector<int>& nums)
	{
		int a = 0;
		int b = 0;
		int minLen = std::numeric_limits<int>::max();
		int curLen = 0;
		int curSum = 0;

		while (a < nums.size() /*|| b < nums.size()*/ //we in array
			&& minLen != 1 // it is the best of posible solution - so stop iterate
			)
		{
			if (curSum < target && b < nums.size())
			{
				curSum += nums[b];
				++b;
			}
			else //if (curSum >= target /*&& a < nums.size()*/)
			{
				curSum -= nums[a];
				++a;
			}
			if (curSum >= target)
			{
				curLen = b - a;
				minLen = std::min(minLen, curLen);
			}
		}

		return (minLen == std::numeric_limits<int>::max()) ? 0 : minLen;
	}

	static void test()
	{
		std::cout << "----------------------------------------------------- \n";
		std::cout << "209. Minimum Size Subarray Sum \n";
		Solution_209 s;

		IS_TRUE((s.minSubArrayLen(4, std::vector<int>{1, 4, 4}) == 1));
		IS_TRUE((s.minSubArrayLen(7, std::vector<int>{2, 3, 1, 2, 4, 3}) == 2));
		IS_TRUE((s.minSubArrayLen(11, std::vector<int>{1, 1, 1, 1, 1, 1, 1, 1}) == 0));

		std::cout << "----------------------------------------------------- \n";
	}
};

//2. Add Two Numbers
class Solution_2 {

	/**
	 * Definition for singly-linked list.
	 * struct ListNode {
	 *     int val;
	 *     ListNode *next;
	 *     ListNode() : val(0), next(nullptr) {}
	 *     ListNode(int x) : val(x), next(nullptr) {}
	 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
	 * };
	 */

	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}

		//my
		~ListNode()
		{
			if (next != nullptr)
			{
				delete next;
				next = nullptr;
			}
		}
	};


public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
	{
		if (l1 == nullptr || l2 == nullptr)
		{
			return nullptr;
		}

		ListNode* cur = new ListNode;
		ListNode* head = cur;

		int sum = 0;
		int carr = 0;

		while (l1 != nullptr || l2 != nullptr)
		{
			int v1 = 0;
			int v2 = 0;

			if (l1 != nullptr)
			{
				v1 = l1->val;
				l1 = l1->next;
			}
			if (l2 != nullptr)
			{
				v2 = l2->val;
				l2 = l2->next;
			}

			sum = v1 + v2 + carr;
			carr = sum / 10;

			cur->val = sum % 10;


			if ((l1 != nullptr || l2 != nullptr) || carr != 0)
			{
				cur->next = new ListNode(carr);
			}

			cur = cur->next;
		} 

		return head;
	}


	/*
		std::cout << "v1 = " << v1 << ", v2 = " << v2 << ", s = " << sum << ", c = " << carr << ",        s % 10 = " << (sum % 10)
			<<"\t\t cur = " <<(cur ? "v" : "N") << ", cur->next = " << (cur->next ? "v" : "N")
			<< " \n";


	*/

	static void test()
	{
		std::cout << "----------------------------------------------------- \n";
		std::cout << "2. Add Two Numbers Sum \n";
		Solution_2 s;

		auto fnCreate = [](int x) -> std::unique_ptr<ListNode>
			{
				std::unique_ptr<ListNode> head;
				ListNode* cur = nullptr;
				ListNode* pred = nullptr;

				int r = 0;
				do
				{
					r = x % 10;
					x /= 10;
					cur = new ListNode(r);
					if (head == nullptr) head.reset(cur);
					if (pred != nullptr) pred->next = cur;

					pred = cur;
				}
				while (x != 0);
				
				return head;
			};


		// todo add tests
		{
			std::cout << "6+4 \n";

			auto l1 = fnCreate(6);
			auto l2 = fnCreate(4);
			auto l3 = s.addTwoNumbers(l1.get(), l2.get());
		}
		{
			std::cout << "1+2 \n";
			auto l1 = fnCreate(1);
			auto l2 = fnCreate(2);
			auto l3 = s.addTwoNumbers(l1.get(), l2.get());
		}

		{
			std::cout << "0+0 \n";
			auto l1 = fnCreate(0);
			auto l2 = fnCreate(0);
			auto l3 = s.addTwoNumbers(l1.get(), l2.get());
		}
		{
			std::cout << "99+1 \n";
			auto l1 = fnCreate(99);
			auto l2 = fnCreate(1);
			auto l3 = s.addTwoNumbers(l1.get(), l2.get());
		}


		//Input: l1 = [2,4,3], l2 = [5,6,4]
		//Output: [7,0,8]
		//Explanation: 342 + 465 = 807.
		{
			//auto l1 = fnCreate(0);
			//auto l2 = fnCreate(123);
			//auto l3 = s.addTwoNumbers(l1.get(), l2.get());


			//IS_TRUE((s.addTwoNumbers() == ));
		}




		//Input: l1 = [0], l2 = [0]
		//Output: [0]

		//Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
		//Output: [8,9,9,9,0,0,0,1]

		std::cout << "----------------------------------------------------- \n";
	}
};

//9. Palindrome Number
//https://leetcode.com/problems/palindrome-number/description/
class Solution_9 {
public:
	bool isPalindrome(int x) 
	{
		if (x < 0) return false;

		long revert{ 0 };
		for (auto copy = x; copy > 0; copy = copy / 10)
		{
			revert = revert * 10 + copy % 10;
		}

		if (revert > std::numeric_limits<int>::max()) return false;

		return x == static_cast<int>(revert);
	}

	static void test()
	{
		std::cout << "----------------------------------------------------- \n";
		std::cout << "9. Palindrome Number \n";
		Solution_9 s;

		IS_TRUE((s.isPalindrome(123) == true));
		IS_TRUE((s.isPalindrome(121) == true));
		IS_TRUE((s.isPalindrome(-121) == false));
		IS_TRUE((s.isPalindrome(10) == false));
		IS_TRUE((s.isPalindrome(4) == true));
		IS_TRUE((s.isPalindrome(0) == true));

		std::cout << "----------------------------------------------------- \n";
	}
};

//125. Valid Palindrome
//https://leetcode.com/problems/valid-palindrome/description/?envType=study-plan-v2&envId=top-interview-150
class Solution_125
{
public:
	bool isPalindrome_(std::string s)
	{
		if (s.empty()) return true;

		auto lit = std::cbegin(s);
		auto rit = std::cend(s);
		--rit;

		auto fnToLower = [](const char c) -> char
			{
				return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
			};

		auto fnIsLetter = [](const char c) -> bool
			{
				return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z');
			};

		while (lit < rit)
		{
			while (!fnIsLetter(*lit) && lit < rit)
			{
				++lit;
			}
			char l = fnToLower(*lit);

			while (!fnIsLetter(*rit) && lit < rit)
			{
				--rit;
			}
			char r = fnToLower(*rit);

			if (l != r) return false;
			++lit;
			--rit;
		}
		return true;
	}

	bool isPalindrome(std::string s)
	{
		if (s.empty()) return true;

		auto lit = std::cbegin(s);
		auto rit = std::cend(s);
		--rit;

		while (lit < rit)
		{
			while (!std::isalnum(static_cast<unsigned char>(*lit)) && lit < rit) ++lit;
			while (!std::isalnum(static_cast<unsigned char>(*rit)) && lit < rit) --rit;

			const char r = std::tolower(static_cast<unsigned char>(*rit));
			const char l = std::tolower(static_cast<unsigned char>(*lit));
			if (l != r) return false;
			++lit;
			--rit;
		}
		return true;
	}


	static void test()
	{
		std::cout << "----------------------------------------------------- \n";
		std::cout << "125. Valid Palindrome \n";
		Solution_125 s;

		IS_TRUE((s.isPalindrome("A man, a plan, a canal: Panama") == true));
		IS_TRUE((s.isPalindrome("race a car") == false));
		IS_TRUE((s.isPalindrome("0P") == false));
		IS_TRUE((s.isPalindrome(" ") == true));
		IS_TRUE((s.isPalindrome("") == true));

		std::cout << "----------------------------------------------------- \n";
	}
};
}


void rq2_test()
{
//	cTack1::test();

	Solution_3::test();
	Solution_67::test();
	Solution_1::test();
	Solution_209::test();
	Solution_2::test();
	Solution_125::test();
	Solution_9::test();
}

/*

16. Экранирование символов.
19. Взвести / сбросить бит.Порядок байт в памяти.
20. Сериализация / Десериализация.
24. Наследование от STL контейнеров.
25. ООП.
26. Виды Полиморфизма.
27. Наследование.
28. protected наследование.
29. Задача максимальный элемент в массиве(с подвохом по крайним случаям).
30. Зачем нужны алгоритмы.
30. Исключение в деструкторе.
30. POD типы.
30. Размер пустого класса.

код по - умолчанию для абстрактного метода. struct A { virtual void f() = 0 { "Tyt kakoyto kod"; } };

копи он врайт
написать на итератарах: сорт, финд, мин, макс, бинарный поиск
ПОД типб лайоуты
эмпти басе оптимизация
передвинуть нули в масиве
 ** написать  спин лок, мютекс 
 
 таил рекуршен - схлопнится рекурсия

 звдвча острава  

 пирамидальная сортировка

  */
