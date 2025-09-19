#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cctype>
#include <cmath>
#include <map>
#include <functional>

double evaluate_rpn(const std::string& expression) {
    std::stack<double> stack;
    std::istringstream iss(expression);
    std::string token;
    std::vector<std::string> tokens;
    
    // Разбиваем выражение на токены
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    for (const auto& token : tokens) {
        // Если токен - число
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            try {
                double num = std::stod(token);
                stack.push(num);
            } catch (const std::exception& e) {
                throw std::invalid_argument("Invalid number: " + token);
            }
        }
        // Если токен - оператор или функция
        else {
            // Унарные операции (требуют 1 операнд)
            if (token == "~" || token == "!" || token == "++" || token == "--" ||
                token == "sqrt" || token == "abs" || token == "sin" || token == "cos" ||
                token == "tan" || token == "asin" || token == "acos" || token == "atan" ||
                token == "ln" || token == "log" || token == "exp" || token == "floor" ||
                token == "ceil" || token == "round" || token == "deg" || token == "rad") {
                
                if (stack.empty()) {
                    throw std::invalid_argument("Not enough operands for operator: " + token);
                }
                
                double a = stack.top(); stack.pop();
                double result;
                
                if (token == "~") {
                    result = -a;
                }
                else if (token == "!") {
                    if (a < 0 || std::floor(a) != a) {
                        throw std::invalid_argument("Factorial requires non-negative integer");
                    }
                    result = 1;
                    for (int i = 2; i <= a; i++) {
                        result *= i;
                    }
                }
                else if (token == "++") {
                    result = a + 1;
                }
                else if (token == "--") {
                    result = a - 1;
                }
                else if (token == "sqrt") {
                    if (a < 0) {
                        throw std::invalid_argument("Square root of negative number");
                    }
                    result = std::sqrt(a);
                }
                else if (token == "abs") {
                    result = std::abs(a);
                }
                else if (token == "sin") {
                    result = std::sin(a);
                }
                else if (token == "cos") {
                    result = std::cos(a);
                }
                else if (token == "tan") {
                    result = std::tan(a);
                }
                else if (token == "asin") {
                    if (a < -1 || a > 1) {
                        throw std::invalid_argument("asin argument out of range [-1, 1]");
                    }
                    result = std::asin(a);
                }
                else if (token == "acos") {
                    if (a < -1 || a > 1) {
                        throw std::invalid_argument("acos argument out of range [-1, 1]");
                    }
                    result = std::acos(a);
                }
                else if (token == "atan") {
                    result = std::atan(a);
                }
                else if (token == "ln") {
                    if (a <= 0) {
                        throw std::invalid_argument("Logarithm of non-positive number");
                    }
                    result = std::log(a);
                }
                else if (token == "log") {
                    if (a <= 0) {
                        throw std::invalid_argument("Logarithm of non-positive number");
                    }
                    result = std::log10(a);
                }
                else if (token == "exp") {
                    result = std::exp(a);
                }
                else if (token == "floor") {
                    result = std::floor(a);
                }
                else if (token == "ceil") {
                    result = std::ceil(a);
                }
                else if (token == "round") {
                    result = std::round(a);
                }
                else if (token == "deg") {
                    result = a * 180.0 / M_PI;
                }
                else if (token == "rad") {
                    result = a * M_PI / 180.0;
                }
                
                stack.push(result);
            }
            // Бинарные операции (требуют 2 операнда)
            else {
                if (stack.size() < 2) {
                    throw std::invalid_argument("Not enough operands for operator: " + token);
                }
                
                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();
                double result;
                
                if (token == "+") {
                    result = a + b;
                }
                else if (token == "-") {
                    result = a - b;
                }
                else if (token == "*") {
                    result = a * b;
                }
                else if (token == "/") {
                    if (b == 0) {
                        throw std::invalid_argument("Division by zero");
                    }
                    result = a / b;
                }
                else if (token == "^") {
                    result = std::pow(a, b);
                }
                else if (token == "%") {
                    if (b == 0) {
                        throw std::invalid_argument("Modulo by zero");
                    }
                    result = std::fmod(a, b);
                }
                else if (token == "min") {
                    result = std::min(a, b);
                }
                else if (token == "max") {
                    result = std::max(a, b);
                }
                else if (token == "pow") {
                    result = std::pow(a, b);
                }
                else {
                    throw std::invalid_argument("Unknown operator: " + token);
                }
                
                stack.push(result);
            }
        }
    }
    
    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression: too many operands");
    }
    return stack.top();
}

// Пример использования
int example() {
    std::vector<std::pair<std::string, std::string>> test_cases = {
        {"2 3 ^", "Возведение в степень: 2^3 = 8"},
        {"7 3 %", "Остаток от деления: 7%3 = 1"},
        {"5 ~", "Унарный минус: -5 = -5"},
        {"5 ++", "Инкремент: 5++ = 6"},
        {"5 --", "Декремент: 5-- = 4"},
        {"5 !", "Факториал: 5! = 120"},
        {"9 sqrt", "Квадратный корень: sqrt(9) = 3"},
        {"-5 abs", "Модуль числа: abs(-5) = 5"},
        {"0 sin", "Синус: sin(0) = 0"},
        {"0 cos", "Косинус: cos(0) = 1"},
        {"0 tan", "Тангенс: tan(0) = 0"},
        {"0.5 asin", "Арксинус: asin(0.5) ≈ 0.5236"},
        {"0.5 acos", "Арккосинус: acos(0.5) ≈ 1.0472"},
        {"1 atan", "Арктангенс: atan(1) ≈ 0.7854"},
        {"2.718 ln", "Натуральный логарифм: ln(e) ≈ 1"},
        {"100 log", "Десятичный логарифм: log(100) = 2"},
        {"1 exp", "Экспонента: exp(1) ≈ 2.718"},
        {"3.7 floor", "Округление вниз: floor(3.7) = 3"},
        {"3.2 ceil", "Округление вверх: ceil(3.2) = 4"},
        {"3.5 round", "Округление: round(3.5) = 4"},
        {"3.2 4.5 max", "Максимум: max(3.2, 4.5) = 4.5"},
        {"3.2 4.5 min", "Минимум: min(3.2, 4.5) = 3.2"},
        {"180 deg", "Градусы в радианы: 180° = π"},
        {"3.14159 rad", "Радианы в градусы: π rad = 180°"},
        {"10 2 /", "Деление: 10/2 = 5"},
        {"3 4 5 * +", "Сложное выражение: 3 + 4*5 = 23"},
        {"5 1 2 + 4 * + 3 -", "Еще сложнее: 5 + (1+2)*4 - 3 = 14"}
    };
    
    for (const auto& test : test_cases) {
        try {
            double result = evaluate_rpn(test.first);
            std::cout << test.second << " -> " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Ошибка в '" << test.first << "': " << e.what() << std::endl;
        }
    }
    
    return 0;
}

/*
1. Возведение в степень: Добавь оператор ^ для возведения числа в степень
(например, 2 3 ^ → 8).
2. Остаток от деления: Реализуй оператор % для вычисления остатка от деления
(например, 7 3 % → 1).
3. Унарный минус: Добавь поддержку унарного минуса через
оператор ~ (например, 5 ~ → -5).
4. Инкремент/декремент: Добавь операторы ++ и --, которые увеличивают или
уменьшают число на вершине стека на 1.
5. Факториал: Реализуй оператор ! для вычисления факториала числа (например, 5
! → 120).
6. Квадратный корень: Реализуй функцию sqrt для вычисления квадратного
корня.
7. Модуль числа: Добавь функцию abs для вычисления абсолютного значения
числа.
8. Тригонометрия: Реализуй функции sin, cos, tan (работают с радианами).
9. Обратная тригонометрия: Добавь функции asin, acos, atan.
10. Логарифмы: Реализуй натуральный логарифм ln и десятичный логарифм log.
*/