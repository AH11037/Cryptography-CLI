
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int inputter(std::string x, int upper, int lower) {
  int temp;
  do {
    std::cout << x << std::endl;
    std::cin >> temp;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      temp = 0;
    }
  } while (temp < lower || temp > upper);

  return temp;
}

char shift(char c, int shift) {
  shift %= 26;
  return std::isupper(c)   ? (c - 'A' + shift + 26) % 26 + 'A'
         : std::islower(c) ? (c - 'a' + shift + 26) % 26 + 'a'
                           : c;
}

int main(int, char **) {
  std::cout << "Here are the cipher types:"
               "\n1.Atbash Cipher"
               "\n2.Substitution Cipher "
               "\n3.Vigenère Cipher"
               "\n4.Affine Cipher"
               "\n";

  int type = inputter("What type of cipher do you want? ", 5, 1);
  int type2ElectricBoogaloo =
      3 - 2 * inputter("Encryption or decryption?\n1.Encryption\n2.Decryption",
                       2, 1);

  std::string message;
  std::cin.ignore(1000, '\n');
  std::cout << "Type your message: ";
  std::getline(std::cin, message);
  std::string cryptogram = "";

  switch (type) {
  case 1: // Atbash cipher or smth
    for (char c : message)
      cryptogram += std::isupper(c)   ? 'Z' - (c - 'A')
                    : std::islower(c) ? 'z' - (c - 'a')
                                      : c;
    break;

  case 2: { // sub :)
    int shifter =
        inputter("What do you want the letters to be shifted by?", 1000000, 0);
    for (char c : message)
      cryptogram += shift(c, shifter * type2ElectricBoogaloo);
    break;
  }

  case 3: { // vigenere
    std::string key;
    std::cout << "What is your key? ";
    std::cin >> key;
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    int x = 0;
    for (char c : message)
      cryptogram += shift(c, std::isalpha(c) ? (key[x++ % key.length()] - 'A') *
                                                   type2ElectricBoogaloo
                                             : 0);
    break;
  }

  case 4: // affine
    int a;
    do {
      a = inputter("What is a? (Must be coprime with 26): ", 25, 1);
    } while (a % 2 == 0 || a == 13);
    int b = inputter("What is b?", 1000000, 0);
    int inverse;
    for (inverse = 1; inverse < 26; inverse++)
      if (a * inverse % 26 == 1)
        break;
    for (char c : message)
      if (std::isalpha(c))
        cryptogram +=
            (type2ElectricBoogaloo == 1
                 ? a * (c - (std::isupper(c) ? 'A' : 'a')) + b
                 : inverse * (c - (std::isupper(c) ? 'A' : 'a') - b + 26)) %
                26 +
            (std::isupper(c) ? 'A' : 'a');
      else
        cryptogram += c;
    break;
  }

  std::cout << cryptogram;
}