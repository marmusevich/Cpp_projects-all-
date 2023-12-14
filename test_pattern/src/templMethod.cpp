#include <iostream>
#include <memory>


namespace
{
   class ADificultCalc
   {
   public:
      ADificultCalc() = default;
      virtual ~ADificultCalc() = default;

      void calc()
      {
         p1();
         m1();
         p2();
         m2();
         p3();
         m3();
         p4();
      }

   protected:
      virtual void m1() = 0;
      virtual void m2() = 0;
      virtual void m3() = 0
      {
         std::cout <<" ---  m3 - default\n";
      }

   private:
      void p1()
      {
         std::cout <<"part 1\n";
      }

      void p2()
      {
         std::cout <<"part 2\n";
      }

      void p3()
      {
         std::cout <<"part 3\n";
      }

      void p4()
      {
         std::cout <<"part 4\n";
      }
   };

   class cConcreteCalc1 : public ADificultCalc
   {
   protected:
      void m1() override
      {
         std::cout << "   m1 - variant 1\n";
      }

      void m2() override
      {
         std::cout << "   m2 - variant 1\n";
      }

      void m3() override
      {
         std::cout << "   m3 - variant 1\n";
      }
   };

   class cConcreteCalc2 : public ADificultCalc
   {
   protected:
      void m1() override
      {
         std::cout << "        m1 - variant 2 !!!! \n";
      }

      void m2() override
      {
         //do nothing
      }

      void m3() override
      {
         //use default impl
         ADificultCalc::m3();
      }

   private:
      void p1()
      {
         std::cout <<"ERROR MUST NOT CALL  cConcreteCalc2::p1\n";
      }
   };
}


void templMethod_test()
{
   auto c1 = std::make_shared<cConcreteCalc1>();
   auto c2 = std::make_shared<cConcreteCalc2>();

   std::cout << "*** variant   <I> \n";
   c1->calc();
   std::cout << "*** variant   <II> \n";
   c2->calc();
}

