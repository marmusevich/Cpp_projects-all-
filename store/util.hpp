template <typename FN>
auto measureTime(FN&& fn) {
   auto start = std::chrono::high_resolution_clock::now();

   fn();

   auto end = std::chrono::high_resolution_clock::now();
   auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
   return dur.count();
}
