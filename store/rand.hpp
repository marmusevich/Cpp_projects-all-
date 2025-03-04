#pragma once


#include <random>
#include <cassert>


//std::ranlux24_base
//std::minstd_rand - faster
//std::mt19937
template <typename GEN>
struct Rn {
   Rn() 
      : mGen{std::random_device{}()}
   {}

   template <typename SEED>
   Rn(const SEED seed) 
      : mGen{ static_cast<GEN::result_type>(seed)}
   {}

   auto get() {
      return mGen();
   }

   template <typename VALUE>
   auto get(const VALUE max) {
      assert(max > 0);
      return static_cast<VALUE>( mGen() % max );
   }

   template <typename VALUE>
   auto get(const VALUE min, const VALUE max) {
      assert((max - min) > 0);
      return static_cast<VALUE>( mGen() % (max - min) + min );
   }

   /**
   * Reorders the elements in the given range [first, last)
   * such that each possible permutation of those elements has equal probability of appearance.
   * see https://en.cppreference.com/w/cpp/algorithm/random_shuffle
   */
   template< class IT >
   void shuffle(IT first, IT last)
   {
      typename std::iterator_traits<IT>::difference_type i, n;
      n = last - first;
      for (i = n - 1; i > 0; --i) {
         using std::swap;
         swap(first[i], first[ get(i + 1)]);
         // rand() % (i+1) isn't actually correct, because the generated number
         // is not uniformly distributed for most values of i. A correct implementation
         // will need to essentially reimplement C++11 std::uniform_int_distribution,
         // which is beyond the scope of this example.
      }
   }

   template< class RANGE >
   void shuffle(RANGE& range) {
      shuffle(std::begin(range), std::end(range));
   }


   template< class IT >
   auto select(IT first, IT last)
   {
      assert(first != last);

      auto it = first;
      std::advance(it, get(std::distance(first, last)));
      return  it == last ? *first : *it;
   }

   template< class RANGE >
   auto select(RANGE& range) {
      return select(std::begin(range), std::end(range));
   }


private:
   GEN mGen;
};



void main111() {
   auto fnPrint = [](auto& range) {
      for (auto& el : range) {
         std::cout << (int)el << ' ';
      }
      std::cout << '\n';
   };

   auto rnd = [](auto& range, const auto seed = -1 ){
      using GT = std::minstd_rand;

      auto gen = seed == -1 ? Rn<GT>() : Rn<GT>(seed);
      for (auto& el : range) {
         el = gen.get(1,9);
      }
   };


   std::vector<uint8_t> vec;
   vec.resize(10);

   std::cout << "\n";
   std::cout << "time = " << measureTime([&]() {rnd(vec, -1); }) << ":\t";
   fnPrint(vec);
   std::cout << "time = " << measureTime([&]() {rnd(vec, -1); }) << ":\t";
   fnPrint(vec);


   std::cout << "\n";
   std::cout << "time = " << measureTime([&]() {rnd(vec, 1); }) << ":\t";
   fnPrint(vec);
   std::cout << "time = " << measureTime([&]() {rnd(vec, 1); }) << ":\t";
   fnPrint(vec);


   std::cout << "\n";

   using GT = std::minstd_rand;
   auto gen = Rn<std::minstd_rand>();
   gen.shuffle(vec);
   std::cout << "        \t";
   fnPrint(vec);
}
