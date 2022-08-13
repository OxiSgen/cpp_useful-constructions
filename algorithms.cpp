// Готовые реализации ходовых алгоритмов. Буду записывать то, что часто попадается на codewars как часть задачи.

// удаляем пробелы из строк

std::string str1 = "Text with some   spaces";
// Вариант 1.1
str1.erase(std::remove_if(str1.begin(), str1.end(),
                          [](unsigned char x){return std::isspace(x);}),
                          str1.end());
// Вариант 1.2
str1.erase(remove_if(str1.begin(),str1.end(),isspace),str1.end());

// Вариант 2
// Самый быстрой вариант (?). Используем std::remove для логического удаления пробелов, затем удаляем пробелы физически с помощью erase.
auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');
std::cout << std::string_view(str1.begin(), noSpaceEnd) << " size: " << str1.size() << '\n';   //Textwithsomespaces    size: 23
str1.erase(noSpaceEnd, str1.end());
std::cout << str1 << " size: " << str1.size() << '\n';                                         //Textwithsomespaces    size: 18

str1.erase(std::remove(str1.begin(), str1.end(), ' '), str1.end());                            // Короткий вариант.

// Вариант 3
// Создаём стрим из исходной строки и используем std::getline для получения кускса сроки до первого пробела.
std::stringstream stS(str1);
std::string s;
std::string res;
while (std::getline(stS, s, ' ')){
    res+=s;
}

// Вариант 4
// В лоб (полбу)
string v;
for(char c: str1) 
{
      if (c != ' ')
      {
          v += c; 
      }
}
str1 = v;
//---------------------------------------------------------------------------------------------------------------------------
