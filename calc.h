#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "list.h"

#define DELIM ' '

long long int expr_calc(list_t *expr);

list_t *get_expr();

bool is_mult_or_div(char ch);

bool is_plus_or_minus(char ch);

bool is_operator(char ch);

bool is_l_bracket(char ch);

bool is_r_bracket(char ch);

bool is_whitespace(char ch);

bool is_digit(char ch);

bool is_end_expr(char ch);

void add_delim(list_t *expr, bool digit_end);

#endif
