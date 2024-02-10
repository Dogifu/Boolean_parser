//
//  main.cpp
//  boolean_fu
//
//  Created by user on 01.02.2024.
//
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int evaluate(vector<bool>& values, string expression) {
    int result = 1;
    char op = '*';
    bool is_operand = false;

    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == 'x' && i + 1 < expression.size() && expression[i + 1] >= '1' && expression[i + 1] <= '9') {
            int index = expression[i + 1] - '1';
            bool value = values[index];
            
            if (op == '*') {
                result &= value;
            } else if (op == '+') {
                result |= value;
            } else if (op == '!') {
                result &= !value;
            }

            is_operand = true;
            i++;
        } else if (expression[i] == '*') {
            op = '*';
            is_operand = false;
        } else if (expression[i] == '+') {
            op = '+';
            is_operand = false;
        } else if (expression[i] == '!') {
            op = '!';
            is_operand = false;
        } else if (expression[i] == '(') {
            // Начало новой группы операций
            string sub_expression;
            int j = i + 1;
            int parentheses_count = 1;
            while (j < expression.size() && parentheses_count > 0) {
                if (expression[j] == '(') parentheses_count++;
                else if (expression[j] == ')') parentheses_count--;
                sub_expression += expression[j];
                j++;
            }
            i = j - 1;
            // Вычисляем результат вложенной группы операций и обновляем result
            int sub_result = evaluate(values, sub_expression);
            if (op == '*') {
                result &= sub_result;
            } else if (op == '+') {
                result |= sub_result;
            } else if (op == '!') {
                result &= !sub_result;
            }
            is_operand = true;
        }
    }
    return result;
}

void build_truth_table(string expression, int num_vars) {
    int num_rows = pow(2, num_vars);
    vector<vector<bool>> truth_table(num_rows, vector<bool>(num_vars, false));

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_vars; j++) {
            truth_table[i][j] = (i >> (num_vars - 1 - j)) & 1;
        }
    }

    for (int i = 0; i < num_vars; i++) {
        cout << "Var" << i + 1 << " ";
    }
    cout << "  | Output" << endl;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_vars; j++) {
            cout << truth_table[i][j] << "     ";
        }
        cout << "| " << evaluate(truth_table[i], expression) << endl;
    }
}

int main() {
    cout << "Заданы логические операции" << endl
         << "! - логическое не" << endl
         << "+ - дизъюнкция" << endl
         << "* - конъюнкция" << endl
         << "x1, x2, ..... xn - переменные" << endl;
    int num_vars;
    cout << "Введите количество переменных: ";
    cin >> num_vars;

    string expression;
    cout << "Введите булеву функцию без пробелов: ";
    cin >> expression;

    build_truth_table(expression, num_vars);

    return 0;
}
