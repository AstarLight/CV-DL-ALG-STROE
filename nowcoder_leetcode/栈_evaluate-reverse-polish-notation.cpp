
/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are+,-,*,/. Each operand may be an integer or another expression.

Some examples:

  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<string> s;
        for(int i=0;i<tokens.size();i++)
        {
            if(isDigits(tokens[i]))
            {
                s.push(tokens[i]);
            }
            else
            {
                int num1 = atoi(s.top().c_str());
                //cout << "current num1 is " << num1 <<endl;
                s.pop();
                int num2 = atoi(s.top().c_str());
                //cout << "current num2 is " << num2 <<endl;
                s.pop();
                int result = calc(num2, num1, tokens[i]);
                //cout << "current result is " << result <<endl;
                s.push(to_string(result));
            }
        }
        return atoi(s.top().c_str());
    }

    int calc(int n1, int n2, string mode)
    {
        if(mode == "+")
            return n1 + n2;
        else if(mode == "-")
            return n1 - n2;
        else if(mode == "*")
            return n1*n2;
        else if(mode == "/")
            return n1/n2;

        return -1;
    }

    bool isDigits(string s)
    {
        if(s=="+" || s=="-" || s=="*" || s=="/")
            return false;
        return true;
    }
};
