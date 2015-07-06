#include <iostream>

namespace string {
   
   class formatter {
      std::string d_str;
   public:
      formatter(std::string const& str): d_str(str) {}
      
      template<typename T>
      formatter& format(T t);
      
      template<typename T1, typename... Args>
      formatter& format(T1 t, Args&&... rest);
      
      formatter& format(std::string const& t);
      
      operator char const* ()
      {
         return d_str.c_str();
      }
   };
   
   template<typename T>
   formatter& formatter::format(T t)
   {
      std::string::size_type idx = d_str.find_first_of("{}");
      if(idx != d_str.npos){
         d_str = d_str.replace(idx, 2, std::to_string(t));
         
      }
      return *this;
   }
   
   formatter& formatter::format(std::string const& t)
   {
      std::string::size_type idx = d_str.find_first_of("{}");
      if(idx != d_str.npos){
         d_str = d_str.replace(idx, 2, t);
      }
      return *this;
   }
   
   template<>
   formatter& formatter::format(char const* t)
   {
      return format(std::string(t));
   }
   
   
   template<typename T1, typename... Args>
   formatter& formatter::format(T1 t, Args&&... rest)
   {
      return format(t).format(std::forward<Args>(rest)...);
   }
   
} //namespace

int main(int argc, char *argv[]){
   std::cout << string::formatter("my name is {}. Today is {}th of July. I am in {}").
      format("amitabh", 6, "London") << std::endl;
   return 0;
}
