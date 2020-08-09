/*
 * ----------------------------------------------------------------------
 * File:      Human.cpp
 * Project:   MessagePassing
 * Author:    Sanjay Vyas
 * 
 * Description:
 *  Implement dynamic language like "message passing" in C++ 
 * ----------------------------------------------------------------------
 * Revision History:
 * 2020-Aug-10	[SV]: Created
 * ----------------------------------------------------------------------
 */
#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;

class Human
{
    // using is like typedef.. 
    // Behaviour is a function pointer which takes Human ref and string
    using Behaviour = function<void(Human &, string)>;

private:
    string name;  // Name of current human

    // Map of behaviour ("eat", "sleep") mapped to function pointers or lambdas
    map<string, Behaviour> messageMap = {
        {"eat", Behaviour([](auto This, auto food) {    // Lambda
                cout << This.name << " is eating " << food << endl; })
            },
        {"sleep", &Human::sleep} // Function pointer

    };

    // We are not using this because we have used a lambda for eat
    void eat(string food) const
    {
        cout << name << " is eating " << food << endl;
    }

    void sleep(string time) const
    {
        cout << name << " is sleeping for " << time << endl;
    }

public:
    Human(string name) : name(name)
    {
    }

    // This is the cor of "message passing" implementation
    auto message(string receiverName, string param)
    {
        // Check in map if receiver ("eat", "sleep" etc.) exists
        if (auto receiver = messageMap[receiverName] ) 
        {
            receiver(*this, param);
            return true;
        }
        return false;
    }

    // Sweetness of C++ 😘
    // Shortcut for .message()
    auto operator()(string receivername, string param)
    {
        return message(receivername, param);
    }
};

int main(int argc, char **argv, char **envp)
{
    Human human("Stroustrup");
    human.message("eat", "banana") 
      || cout << "Human doesn't understand eat" << endl;

    // Remove the "message" part and make it look more natural
    human("sleep", "12 hours") 
      || cout << "Human doesn't understand sleep" << endl;
      
    human("getlost", "forever") 
      || cout << "Human doesn't understand getlost" << endl;

    return 0;
}