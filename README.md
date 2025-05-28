Math Module for AgriStats

Overview

The mathModule.cpp is a high-performance C++ program designed for AgriStats to evaluate complex mathematical expressions. It supports basic arithmetic operations (+, -, *, /), parentheses, and floating-point numbers, making it ideal for precise calculations in agricultural data analysis, such as yield forecasting, cost analysis, or statistical modeling. The program uses a stack-based algorithm to process expressions in a single iteration, prioritizing performance over object-oriented design for efficiency in large-scale data processing.

Features





Expression Evaluation: Computes expressions with addition, subtraction, multiplication, division, and parentheses (e.g., (2.5 * 3 - 1.2) / 4).



Floating-Point Support: Handles decimal numbers with robust validation to ensure accuracy.



Error Handling: Detects and reports errors like invalid decimals, mismatched parentheses, or consecutive operators (e.g., ++, *-).



High Performance: Utilizes stack-based processing with a single-pass algorithm to minimize computational overhead.



Input Validation: Ensures expressions are mathematically valid, rejecting malformed inputs with specific error codes (e.g., BRACEMISSING, INVALID_DECIMAL).

Use Case

Developed for AgriStats, this module supports calculations critical to agricultural analytics, such as:





Calculating crop yield projections based on variable inputs.



Evaluating financial metrics for farm operations.



Processing statistical models for agricultural data.

Installation

Prerequisites





C++ compiler (e.g., g++ with C++11 or later).



Standard C++ libraries (iostream, stdio.h, stdlib.h, string).

Steps





Clone or download the repository:

git clone <repository-url>



Navigate to the project directory:

cd <project-directory>



Compile the program:

g++ -o mathModule mathModule.cpp



Run the executable:

./mathModule

Usage

The program processes mathematical expressions provided as strings. It validates the input, performs calculations, and returns the result or an error code.

Example

char expression[] = "(2.5 * 3 - 1.2) / 4";
long double result;
short int status = mathCalculate(expression, result);
if (status == 0) {
    printf("Result: %Lf\n", result); // Output: Result: 1.575
} else {
    printf("Error code: %d\n", status);
}

Error Codes





10001: Two non-negative operators simultaneously (e.g., +*).



10002: Multiple operators without values in between (e.g., +-).



10004: Negative brace negative continuously (not applicable in current code).



10005: Result exceeds maximum value.



10006: Invalid decimal format (e.g., 1.2.3).



10007: Mismatched parentheses.



10008: Input string exceeds limit.



10009: Space between consecutive numbers (e.g., 1 2).



10010: Back-to-back commas (e.g., 1,,2).



10011: Comma after decimal point (e.g., 1.2,).



10012: Invalid comma position.



10013: Blank space after decimal point (e.g., 1. ).



10014: Insufficient numbers for operation.



10015: Invalid input character.

Technical Details





Algorithm: Uses two stacks—one for operators (stack, stackFn) and one for numbers (intStack, intStackFn)—to evaluate expressions using operator precedence rules. The mathCalculate function processes the expression in a single pass, pushing/popping numbers and operators as needed.



Precedence Handling: Ensures operators like * and / are evaluated before + and -, respecting parentheses.



Validation: The validateStr function checks for syntax errors, and checkValidDecimals ensures proper decimal and comma usage.



Performance: Avoids object-oriented design to minimize overhead, suitable for high-volume calculations in AgriStats’ data pipelines.



Limitations:





Maximum input string length is 65,533 characters.



Results exceeding 999,999,999,999,999.999999999 trigger an error.



Does not support advanced mathematical functions (e.g., sin, cos).

Code Structure





Main Functions:





mathCalculate: Core function to evaluate the expression and return the result or error code.



calculatePart: Computes operations between two numbers with a given operator.



validateStr: Validates the input expression for syntax errors.



checkValidDecimals: Ensures proper decimal and comma formatting.



Stack Operations:





push, pop: Manage operator stack.



intPush, intPop: Manage number stack.



pushFn, popFn, intPushFn, intPopFn: Auxiliary stacks for final calculations.



Utility:





get_type: Identifies character types (number, operator, brace, etc.).



chech_precedence: Determines operator precedence for correct evaluation order.

Contributing

Contributions are welcome! Please submit issues or pull requests to the repository for bug fixes, performance improvements, or additional features (e.g., support for more operators or functions).

License

This project is licensed under the MIT License. See the LICENSE file for details.

Contact

For questions or support, contact the developer at jamierhmn@gmail.com or open an issue on the GitHub repository.
