#include "alphabets.hpp"       // itsp3::asciiAlphabet
#include "bcrypt.hpp"          // itsp3::Bcrypt
#include "bruteforce.hpp"      // itsp3::bruteforce
#include "log.hpp"             // ITSP3_LOG
#include "string_scrubber.hpp" // itsp3::StringScrubber
#include <ciso646>             // not, and
#include <cstddef>             // std::size_t
#include <cstdlib>             // EXIT_SUCCESS
#include <iostream>            // std::cout

namespace itsp3 {
namespace {
void addUser(Bcrypt& bcrypt)
{
  std::string username{};
  std::string password{};

  StringScrubber pwScrubber{password};

  std::cout << "Enter username: ";
  std::getline(std::cin, username);
  std::cout << "Enter password: ";
  std::getline(std::cin, password);

  ITSP3_LOG << "Username: \"" << username << '"' << '\n'
            << "Password: \"" << password << '"';

  const auto retVal = bcrypt.addUser(username, password);

  if (not retVal) {
    std::cout << "Could not add user: " << retVal << '\n';
    return;
  }

  std::cout << "Added user \"" << username << "\"\n";
}

void checkPasswordValidity(Bcrypt& bcrypt)
{
  std::string username{};
  std::string password{};

  StringScrubber pwScrubber{password};

  std::cout << "Enter username: ";
  std::getline(std::cin, username);
  std::cout << "Enter password: ";
  std::getline(std::cin, password);

  ITSP3_LOG << "Username: \"" << username << '"' << '\n'
            << "Password: \"" << password << '"';

  const bool retVal{bcrypt.checkPasswordValidity(username, password)};

  if (not retVal) {
    std::cout << "Password invalid\n";
    return;
  }

  std::cout << "Password ok.\n";
}

void crackPassword(Bcrypt& bcrypt)
{
  std::string username{};

  std::cout << "Enter the username to crack the password of: ";
  std::getline(std::cin, username);
  std::string password{};

  try {
    std::cout << "Cracking password of user \"" << username << '"' << '\n'
              << "This will take a long time, be patient...\n";

    password = bruteforce(
      [&username, &bcrypt](std::string_view test) {
        return bcrypt.checkPasswordValidity(username, test);
      },
      asciiAlphabet);
  }
  catch (const NoMatchInBruteforceAlgorithmException& ex) {
    std::cerr << "Failed to crack password for user: \"" << username << '"'
              << ": " << ex.what() << '\n';
    return;
  }

  std::cout << "The password of \"" << username << "\" is: \"" << password
            << "\"\n";
}
} // anonymous namespace
} // namespace itsp3a

int main()
{
  itsp3::Bcrypt bcrypt{"./data.bin"};

  std::string input{};

  for (;;) {
    std::cout << "[A] Add user\n"
                 "[B] Check password\n"
                 "[C] Crack password\n";
    std::getline(std::cin, input);

    if (input == "A") {
      itsp3::addUser(bcrypt);
      return EXIT_SUCCESS;
    }
    else if (input == "B") {
      itsp3::checkPasswordValidity(bcrypt);
      return EXIT_SUCCESS;
    }
    else if (input == "C") {
      itsp3::crackPassword(bcrypt);
      return EXIT_SUCCESS;
    }
  }
}
