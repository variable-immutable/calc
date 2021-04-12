#include "calc.h"

int main() {
    list_t *expression = get_expr();

    list_print(expression);
    
    long long int result = expr_calc(expression);

    printf(" = %lli\n", result);

    list_free(expression);

    return 0;
}

long long int expr_calc(list_t *expr) {
    if(!expr->size) {
        printf("Нечего считать\n");
        exit(0);
    }

    char ch;
    bool is_dig = false;
    long long int value = 0;
    stack_t *operands = stack_init(sizeof(long long int));
    stack_t *digit = stack_init(sizeof(char));
    list_iter_t *iter = list_get_iter(expr);

    while((ch = list_iter_next(iter))) {
        if(is_digit(ch)) {
            is_dig = true;
            stack_push(digit, &ch);
        } else if(is_dig) {
            is_dig = false;
            value = ch_stack_join_in_lli(digit);
            stack_push(operands,  &value);
        }

        if(is_operator(ch)) {
            long long int r_op = *(long long int *) stack_pop(operands);
            long long int l_op = *(long long int *) stack_pop(operands);

            switch(ch) {
                case '+':
                    value = l_op + r_op;
                    stack_push(operands, &value);
                    break;

                case '-':
                    value = l_op - r_op;
                    stack_push(operands, &value);
                    break;

                case '*':
                    value = l_op * r_op;
                    stack_push(operands, &value);
                    break;

                case '/':
                    value = l_op / r_op;
                    stack_push(operands, &value);
                    break;

                case '%':
                    value = l_op % r_op;
                    stack_push(operands, &value);
                    break;

            }
        }
    }
    
    if(operands->size == 1) {
        value = *(long long int *) stack_pop(operands);
        stack_free(operands);
        stack_free(digit);

        return value; 
    }

    printf("Неверно составлено выражение\n");
    exit(0);
}

list_t *get_expr() {
    bool end_expr = false;
    bool digit_end = false;
    list_t *expression = list_init();
    stack_t *operators = stack_init(sizeof(char));

    while(!end_expr) {
        char ch = getc(stdin);
        char op_top;
        if(!stack_peek(operators, &op_top)) {
            op_top = 0;
        }

        if(is_end_expr(ch)) {
            if(ch == EOF) printf("\n");

            if(stack_is_empty(operators)) {
                end_expr = true;
            } else if(is_operator(op_top)) {
                add_delim(expression, true);
                list_push(expression, *(char *) stack_pop(operators));
                ungetc(ch, stdin);
            } else if(is_l_bracket(op_top)) {
                printf("Лишний символ '%c'\n", ch);
                exit(0);
            }
        }

        else if(is_digit(ch)) {
            add_delim(expression, digit_end);
            list_push(expression, ch);
            digit_end = false;
        } 

        else if(is_plus_or_minus(ch)) {
            if(stack_is_empty(operators) || is_l_bracket(op_top)) {
                digit_end = true;
                stack_push(operators, &ch);
            } else if(is_operator(op_top)) {
                add_delim(expression, true);
                list_push(expression, *(char *) stack_pop(operators));
                ungetc(ch, stdin);
            }
        }

        else if(is_mult_or_div(ch)) {
            if(stack_is_empty(operators) || is_plus_or_minus(op_top) || is_l_bracket(op_top)) {
                digit_end = true;
                stack_push(operators, &ch);
            } else if (is_mult_or_div(op_top)) {
                add_delim(expression, true);
                list_push(expression, *(char *) stack_pop(operators));
                ungetc(ch, stdin);
            }
        }

        else if(is_r_bracket(ch)) {
            if(stack_is_empty(operators)) {
                printf("Лишний символ '%c'\n", ch);
                exit(0);
            } else if(is_operator(op_top)) {
                add_delim(expression, true);
                list_push(expression, *(char *) stack_pop(operators));
                ungetc(ch, stdin);
            } else if(is_l_bracket(op_top)) {
                stack_pop(operators);
            }
        }

        else if(is_l_bracket(ch)) {
            digit_end = true;
            stack_push(operators, &ch);
        }

        else if(is_whitespace(ch)) {
            //~
        }

        else {
            printf("Недопустимый символ '%c'\n", ch);
            exit(0);
        }
    }

    stack_free(operators);
    return expression;
}

bool is_mult_or_div(char ch) {
    return ch == '*' || ch == '/' || ch == '%';
}

bool is_plus_or_minus(char ch) {
    return ch == '-' || ch == '+';
}

bool is_operator(char ch) {
    return is_mult_or_div(ch) || is_plus_or_minus(ch);
}

bool is_l_bracket(char ch) {
    return ch == '(';
}

bool is_r_bracket(char ch) {
    return ch == ')';
}

bool is_whitespace(char ch) {
    return ch == ' ' || ch == '\t';
}

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool is_end_expr(char ch) {
    return ch == '\n' || ch == EOF;
}

void add_delim(list_t *expr, bool digit_end) {
    if(digit_end && expr->size) {
        list_push(expr, DELIM);
    }
}

long long int ch_stack_join_in_lli(stack_t *stack) {
    long long int result = 0;
    char *ch;
    int mult = 1;

    while((ch = stack_pop(stack))) {
        result += (*(char *) ch - '0') * mult;
        mult *= 10; 
    }

    return result;
}
