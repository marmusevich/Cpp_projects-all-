
#include <array>

#include <string>

#include <iterator>
#include <random>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <functional>  // for std::hash





//////////////////////////////////////////////////////////////////////////////////////////////////


using tMatrix = std::vector<uint8_t>;
using tSize = tMatrix::size_type;
//using tPoint = std::pair<tSize, tSize>;
using tPoint = std::tuple<tSize, tSize>;

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

      //wcf_1(); not work
      wcf_2();
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
   void wcf_1() {
      using tElements = std::unordered_set<uint8_t>;

      tElements elements(mSize);
      for (uint8_t i = 1; i < mSize + 1; i++) {
         elements.insert(i);
      }

      std::vector<tElements> mtx(mMatrix.size(), elements);

      std::unordered_set<tPoint> toFill;
      enumerare([&](const tSize x, const tSize y) { toFill.emplace(x, y); });

      auto fnSet = [&](const tSize x, const tSize y, const tElements val) -> void {
         mtx[y * mSize + x] = val;
         };
      auto fnGet = [&](const tSize x, const tSize y) -> tElements {
         return mtx[y * mSize + x];
         };


      auto fnP = [](const auto els) {
         printf("{");
         for (const auto& e : els){
            printf("%d ", (int)e);
         }
      printf("}");
   };

      auto fnRow = [&](const tSize x, const tSize y, const uint8_t val) -> void {
         printf("\tfnRow(%d, %d, %d) -> ", (int)x, (int)y, (int)val);
         for (tSize xx = 0; xx < mSize; xx++) {
            if (xx != x) {
               printf("(%d,%d)", (int)xx, (int)y);
               auto el = fnGet(xx, y);
               fnP(el);
               if (el.size() > 1) {
                  el.erase(val);
                  fnSet(xx, y, el);
                  printf(">>>");
                  fnP(el);
                  if (el.size() == 1) {
                     printf("[!]");
                     toFill.erase(std::make_tuple(xx, y));
                  }
               }
               else {
                  printf("(!)");
                  toFill.erase(std::make_tuple(xx, y));
               }
               printf(", ");
            }
         }
         printf("\n");
      };
      auto fnCol = [&](const tSize x, const tSize y, const uint8_t val) -> void{
         printf("\tfnCol(%d, %d, %d) -> ", (int)x, (int)y, (int)val);
         for (tSize yy = 0; yy < mSize; yy++) {
            if (yy != y) {
               printf("(%d,%d)", (int)x, (int)yy);
               auto el = fnGet(x, yy);
               fnP(el);
               if (el.size() > 1) {
                  el.erase(val);
                  fnSet(x, yy, el);
                  printf(">>>");
                  fnP(el);
                  if (el.size() == 1) {
                     printf("[!]");
                     toFill.erase(std::make_tuple(x, yy));
                  }
               }
               else {
                  printf("(!)");
                  toFill.erase(std::make_tuple(x, yy));
               }
               printf(", ");
            }
         }
         printf("\n");
      };
      auto fnBlock = [&](const tSize x, const tSize y, const uint8_t val) -> void{
         printf("\tfnBlock(%d, %d, %d), ", (int)x, (int)y, (int)val);

         const auto block_x = x / mBlockSize;
         const auto block_y = y / mBlockSize;
         printf(" Block[%d, %d] -> ", (int)block_x, (int)block_y);

         for (tSize by = 0; by < mBlockSize; by++) {
            for (tSize bx = 0; bx < mBlockSize; bx++) {
               const tSize xx = block_x * mBlockSize + bx;
               const tSize yy = block_y * mBlockSize + by;

               if (yy != y || xx != x) {
                  printf("(%d,%d)", (int)xx, (int)yy);
                  auto el = fnGet(xx, yy);
                  fnP(el);
                  if (el.size() > 1) {
                     el.erase(val);
                     fnSet(xx, yy, el);
                     printf(">>>");
                     fnP(el);
                     if (el.size() == 1) {
                        printf("[!]");
                        toFill.erase(std::make_tuple(xx, yy));
                     }
                  }
                  else {
                     printf("(!)");
                     toFill.erase(std::make_tuple(xx, yy));
                  }
                  printf(", ");
               }
            }
         }
         printf("\n");
      };


      Rn<std::minstd_rand> rnd(10);

      while (!toFill.empty()) {
         printf("====================================================\n");
//         printf("toFill.size() = %d\n", (int)toFill.size());

         auto p = rnd.select(toFill);

         toFill.erase(p);

         auto x = std::get<0>(p);
         auto y = std::get<1>(p);

         tElements el = fnGet(x, y);
         uint8_t v = rnd.select(el);

         fnSet(x, y, tElements{v});

         fnRow(x, y, v);
         fnCol(x, y, v);
         fnBlock(x, y, v);

//         printf("toFill.size() = %d\n\n", (int)toFill.size());
      }

      std::transform(mtx.begin(), mtx.end(), mMatrix.begin(), [](auto el) {return *el.begin(); });
   }

   //WaveFunctionCollapse
   void wcf_2() {
      using tElements = std::unordered_set<uint8_t>;

      auto fnAllPosible = [&]() -> tElements {
         tElements elements(mSize);
         for (uint8_t i = 1; i < mSize + 1; i++) {
            elements.insert(i);
         }
         return elements;
      };

      auto fnRow = [&](const tSize x, const tSize y, tElements& elements) -> void {
         for (tSize xx = 0; xx < mSize; xx++) {
            if (xx != x) {
               auto el = get(xx, y);
               if (el != 0) {
                  elements.erase(el);
               }
            }
         }
      };
      auto fnCol = [&](const tSize x, const tSize y, tElements& elements) -> void{
         for (tSize yy = 0; yy < mSize; yy++) {
            if (yy != y) {
               auto el = get(x, yy);
               if (el != 0) {
                  elements.erase(el);
               }
            }
         }
      };
      auto fnBlock = [&](const tSize x, const tSize y, tElements& elements) -> void{
         const auto block_x = x / mBlockSize;
         const auto block_y = y / mBlockSize;

         for (tSize by = 0; by < mBlockSize; by++) {
            for (tSize bx = 0; bx < mBlockSize; bx++) {
               const tSize xx = block_x * mBlockSize + bx;
               const tSize yy = block_y * mBlockSize + by;

               if (yy != y || xx != x) {
                  auto el = get(xx, yy);
                  if (el != 0) {
                     elements.erase(el);
                  }
               }
            }
         }
      };


      std::unordered_set<tPoint> toFill;
      enumerare([&](const tSize x, const tSize y) { toFill.emplace(x, y); });



      auto fnP = [](const auto els) {
         printf("{");
         for (const auto& e : els){
            printf("%d ", (int)e);
         }
         printf("}");
         };


      Rn<std::minstd_rand> rnd(10);

      while (!toFill.empty()) {
         printf("====================================================\n");
         printf("toFill.size() = %d\n", (int)toFill.size());

         auto p = rnd.select(toFill);
         toFill.erase(p);
         auto x = std::get<0>(p);
         auto y = std::get<1>(p);

         tElements el = fnAllPosible();

         printf("[%d,%d]\t", (int)x, (int)y);

         printf("all:");
         fnP(el);

         fnRow(x, y, el);
         printf(", fnRow:");
         fnP(el);

         fnCol(x, y, el);
         printf(", fnCol:");
         fnP(el);

         fnBlock(x, y, el);
         printf(", fnBlock:");
         fnP(el);

         printf("\t\t");

         if (!el.empty()) {
            uint8_t v = rnd.select(el);

            printf("   [%d,%d] = %d", (int)x, (int)y, (int)v);

            set(x, y, v);
         }
         printf("\n");

         print();
      }
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
