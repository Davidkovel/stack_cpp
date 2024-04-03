#include <iostream>
#include <stack>

using namespace std;

enum class BracketError
{
    NoError,
    NoOpen,
    NoClose
};

BracketError checkBrackets(string expr, char openBracket, char closeBracket, int& errorPos);

int main()
{
    cout << "Checking brackets" << endl << endl;
    string expr[]
    {
        "([x-y-z} * [x + 2y) - {z + 4x)]", "({x-y-z} * [x + 2y] - (z + 4x))",
     //   "(2 + 3 + (8 - 4 * (1 + 9))", "(2 + 3) + 8) - (4 * ((1 + 9))"
    };
    int errorPos;
    int const size = 3;
    char* arrayOpenBrackets = new char[size] {'[', '(', '{'};
    char* arrayCloseBrackets = new char[size] { ']', ')', '}'};
    for (int i = 0; i < sizeof(expr) / sizeof(string); i++)
    {
        cout << expr[i] << endl;
        bool isCorrect = false;
        for (int j = 0; j < size; j++) {
            BracketError result = checkBrackets(expr[i], arrayOpenBrackets[j], arrayCloseBrackets[j], errorPos);
            if (result != BracketError::NoError)
            {
                isCorrect = true;
                string errorMsg = result == BracketError::NoOpen ? "No opening bracket" : "No closing bracket";
                cout << "Error in " << errorPos << " : " << errorMsg << endl;
            }
        }
        if (!isCorrect)
        {
            cout << "The expression is correct! " << endl;
        }
        cout << endl;
    }

    cout << endl;
    return 0;
}

BracketError checkBrackets(string expr, char openBracket, char closeBracket, int& errorPos)
{
    stack<int> stack;
    for (int i = 0; i < expr.size(); i++)
    {
        if (expr[i] == openBracket)
        {
            stack.push(i);
        }
        if (expr[i] == closeBracket)
        {
            if (!stack.empty())
            {
                stack.pop();
            }
            else
            {
                errorPos = i;
                return BracketError::NoOpen;
            }
        }
    }
    if (!stack.empty())
    {
        errorPos = stack.top();
        return BracketError::NoClose;
    }
    return BracketError::NoError;
}


/*

Checking brackets

([x-y-z} * [x + 2y) - {z + 4x)]
Error in 1 : No closing bracket
Error in 29 : No opening bracket
Error in 7 : No opening bracket

({x-y-z} * [x + 2y] - (z + 4x))
The expression is correct!



C:\Users\David\source\repos\ConsoleApplication2\x64\Debug\ConsoleApplication2.exe

*/