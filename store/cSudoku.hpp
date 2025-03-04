#pragma once

//#include <array>

#include <string>

#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <functional>  // for std::hash

#include "util.hpp"
#include "rand.hpp"


using tMatrix = std::vector<uint8_t>;
using tSize = tMatrix::size_type;
using tPoint = std::tuple<tSize, tSize>;

inline auto getX(const tPoint p) { return std::get<0>(p); }
inline auto getY(const tPoint p) { return std::get<1>(p); }


//inline bool operator==(const tPoint& lhs, const tPoint& rhs) {
//   return lhs == rhs;
//}
//inline bool operator!=(const tPoint& lhs, const tPoint& rhs) {
//   return !(lhs == rhs);
//}


namespace std {

   template <>
   struct hash<tPoint> {

      std::size_t operator ()(const tPoint &item) const noexcept {
         std::size_t h1 = std::hash<tSize>{}(std::get<0>(item));
         std::size_t h2 = std::hash<tSize>{}(std::get<1>(item));
         return h1 ^ (h2 << 1); // or use boost::hash_combine
      }
   };
} // namespace std


class cSudoku {

public:
   cSudoku(const uint8_t blockSize = 3)
   : mBlockSize{blockSize}
   , mSize{tSize(mBlockSize * mBlockSize)}
   , mMatrix{}
   {
      mMatrix.resize(mSize * mSize);
      //simpleFull();

      print();
      
      printf("\n---------------------------------------------------------\n\n");

      wcf();

      print();
   }

   void print() const
   {
      const uint8_t elemSize = mBlockSize / 10 + 1;

      printf("+%s+\n", std::string( (elemSize + 2) * mSize + (mBlockSize -1)*2+1, '-' ).c_str());

      //for (tSize y = 0; y < mSize; y++) {
      //   for (tSize x = 0; x < mSize; x++) {         
      //      if (x % mBlockSize == 0) {
      //         printf("| ");
      //      }
      //      printf("%2d ", get(x, y));
      //   }
      //   printf("|\n");
      //   if ((y + 1) % mBlockSize == 0) {
      //      printf("+%s+\n", std::string( (elemSize + 2) * mSize + (mBlockSize -1)*2+1, '-' ).c_str());
      //   }
      //}

      enumerare(
         [&](const tSize x, const tSize y) {
            if (x % mBlockSize == 0) {
               printf("| ");
            }
            printf("%2d ", get(x, y));
         },
         [&](const tSize y) {
            printf("|\n");
            if ((y + 1) % mBlockSize == 0) {
               printf("+%s+\n", std::string( (elemSize + 2) * mSize + (mBlockSize -1)*2+1, '-' ).c_str());
            }
         }
      );
   }

private:
   template <typename FNX, typename FNY>
   inline void enumerare(FNX&& fnX, FNY&& fnY) {
      for (tSize y = 0; y < mSize; y++) {
         for (tSize x = 0; x < mSize; x++) {
            fnX(x, y);
         }
         fnY(y);
      }
   }

   template <typename FNX, typename FNY>
   inline void enumerare(FNX&& fnX, FNY&& fnY) const {
      for (tSize y = 0; y < mSize; y++) {
         for (tSize x = 0; x < mSize; x++) {
            fnX(x, y);
         }
         fnY(y);
      }
   }

   template <typename FN>
   inline void enumerare(FN&& fn) {
      enumerare(std::forward<FN>(fn), [&](const tSize y) {});
   }

   template <typename FN>
   inline void enumerare(FN&& fn) const {
      enumerare(std::forward<FN>(fn), [&](const tSize y) {});
   }

   //---

   void simpleFull() {
      enumerare([&](const tSize x, const tSize y) { set(x, y, uint8_t(x % mBlockSize +1) + uint8_t(y % mBlockSize) * mBlockSize );});
   }

   
   //WaveFunctionCollapse
   void wcf() {
      using tElements = std::unordered_set<uint8_t>;

      tElements elements(mSize);
      for (uint8_t i = 1; i < mSize + 1; i++) {
         elements.insert(i);
      }

      std::vector<tElements> mtx(mMatrix.size(), elements);
      std::unordered_set<tPoint> toFill;


      auto fnSet = [&](const tPoint p, const tElements val) -> void {
         mtx[getY(p) * mSize + getX(p)] = val;
      };
      auto fnGet = [&](const tPoint p) -> tElements {
         return mtx[getY(p) * mSize + getX(p)];
      };

      //-----------------------------------------------------------
      auto fnPrEl = [&elements](const auto& elToPr) {
         static const size_t MAX = elements.size();

         printf("{");
         
         for (const auto& e : elToPr){
            printf("%d ", (int)e);
         }
         printf("%s", std::string( (MAX - elToPr.size())*2, ' ' ).c_str());
         printf("}");
      };

      auto fnPrMtx = [&]() {
         for (tSize y = 0; y < mSize; y++) {
            if (y % mBlockSize == 0) {
               printf("\n");
            }

            for (tSize x = 0; x < mSize; x++) {
               if (x % mBlockSize == 0) {
                  printf(" ");
               }

               fnPrEl(fnGet({x , y}));
            }
            printf("\n");
         }
      };

      auto fnPrPoints = [&](const std::string& title, const std::unordered_set<tPoint>& points) {
         printf("%s\t", title.c_str());
         for (const auto& p : points) {
            printf(" [%lld, %lld] ", getX(p), getY(p));
            fnPrEl(fnGet(p));
         }
         printf("\n");
      };

      //-----------------------------------------------------------
      auto fnCallapse = [&](const tPoint point) -> std::unordered_set<tPoint> {
         std::unordered_set<tPoint> toCallapse;
         std::unordered_set<tPoint> touched;

         toCallapse.insert(point);

         auto fnRow = [&](const tSize x, const tSize y, const uint8_t v) {
            for (tSize xx = 0; xx < mSize; xx++) {
               if (xx != x) {
                  auto el = fnGet({ xx, y });
                  if (el.size() > 1) {
                     el.erase(v);
                     fnSet({ xx, y }, el);

                     if (el.size() == 1) {
                        toCallapse.insert({ xx, y });
                     }
                     else {
                        touched.insert({ xx, y });
                     }
                  }
               }
            }
         };

         auto fnCol = [&](const tSize x, const tSize y, const uint8_t v) {
            for (tSize yy = 0; yy < mSize; yy++) {
               if (yy != y) {
                  auto el = fnGet({ x, yy });
                  if (el.size() > 1) {
                     el.erase(v);
                     fnSet({ x, yy }, el);

                     if (el.size() == 1) {
                        toCallapse.insert({ x, yy });
                     }
                     else {
                        touched.insert({ x, yy });
                     }
                  }
               }
            }
         };

         auto fnBlock = [&](const tSize x, const tSize y, const uint8_t v) {
            const auto block_x = x / mBlockSize;
            const auto block_y = y / mBlockSize;

            for (tSize by = 0; by < mBlockSize; by++) {
               for (tSize bx = 0; bx < mBlockSize; bx++) {
                  const tSize xx = block_x * mBlockSize + bx;
                  const tSize yy = block_y * mBlockSize + by;

                  if (yy != y || xx != x) {
                     auto el = fnGet({ xx, yy });
                     if (el.size() > 1) {
                        el.erase(v);
                        fnSet({ xx, yy }, el);

                        if (el.size() == 1) {
                           toCallapse.insert({ xx, yy });
                        }
                        else {
                           touched.insert({ xx, yy });
                        }
                     }
                  }
               }
            }
         };

         // calapse
         while (!toCallapse.empty()) {
            const auto p = *toCallapse.begin();
            toCallapse.erase(p);

            const auto x = getX(p);
            const auto y = getY(p);
            const auto v = *fnGet(p).begin();

            fnRow(x, y, v);
            fnCol(x, y, v);
            fnBlock(x, y, v);

            printf("    - \n");
            printf("       touched.size() = %lld, toCallapse.size() = %lld \n", touched.size(), toCallapse.size());
            fnPrPoints("touched", touched);
            fnPrPoints("toCallapse", toCallapse);

            fnPrMtx();
            printf("    - \n");
         }


         printf("before remove       touched.size() = %lld,  \n", touched.size());
         fnPrPoints("touched", touched);

         for (auto it = touched.begin(); it != touched.end();)
         {
            if (fnGet(*it).size() <= 1)
               it = touched.erase(it);
            else
               ++it;
         }

         printf("after remove       touched.size() = %lld,  \n", touched.size());
         fnPrPoints("touched", touched);


         return touched;
      };



      auto fnEntropy = [&](std::unordered_set<tPoint>&& touched) -> std::unordered_set<tPoint> {
         std::unordered_set<tPoint> toFill;

         if (touched.empty()) {
            return toFill;
         }

         auto it = touched.begin();
         auto cur_min = fnGet(*it).size();
         toFill.insert(*it);
         it++;
         while (it != touched.end()) {
            auto cur = fnGet(*it).size();
            if (cur < cur_min) {
               cur_min = cur;
               toFill.clear();
               toFill.insert(*it);
            }
            else if (cur == cur_min) {
               toFill.insert(*it);
            }
            else {
            }

            it++;
         }
         return toFill;
      };


      //-----------------------------------------------------------

      Rn<std::minstd_rand> rnd(10);
      toFill.insert({ rnd.get(mSize), rnd.get(mSize) });

      //fnPrMtx();

      while (!toFill.empty()) {
         printf("\n====================================================\n");
         printf("toFill.size() = %d\n", (int)toFill.size());

         const auto p = rnd.select(toFill);
         if (p == std::make_tuple(0, 8))
            printf("");


         const uint8_t val =  rnd.select(fnGet(p));
         fnSet(p, tElements{ val });

         printf("    ===> p[%lld, %lld] = %d \n", getX(p), getY(p), val);
         printf("before calapse \n");
         fnPrMtx();
         printf(" ---- \n");


         //----
         printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
         auto touched = fnCallapse(p);
         printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

         printf("-------------------------------------------\n");
         printf("after comllaps\n");
         //fnPrMtx();
         printf("    touched.size() = %lld  \n", touched.size());
         fnPrPoints("touched", touched);
         printf(" - \n");
         printf("-------------------------------------------\n");

         toFill = fnEntropy(std::move(touched));


         printf("-------------------------------------------\n");
         printf("ENTROPY       ");
         printf("    toFill.size() = %lld  \n", toFill.size());
         fnPrPoints("toFill", toFill);
         printf("\n");
      }

      std::transform(mtx.begin(), mtx.end(), mMatrix.begin(), [](auto el) {return *el.begin(); });
   }




   void set(const tSize x, const tSize y, const uint8_t val)
   {
      mMatrix[y * mSize + x] = val;
   }

   uint8_t get(const tSize x, const tSize y) const
   {
      return mMatrix[y * mSize + x];
   }

private:
   const uint8_t mBlockSize;
   const tSize mSize;
   tMatrix mMatrix;
};
