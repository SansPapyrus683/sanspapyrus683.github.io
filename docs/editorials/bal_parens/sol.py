"""
https://www.codewars.com/kata/60790e04cc9178003077db43/train/python
"""
from typing import Optional
from math import comb
from functools import lru_cache


@lru_cache
def balanced_paren_num(par_amt: int) -> int:
    assert par_amt >= 0
    # formula from https://en.wikipedia.org/wiki/Catalan_number
    return comb(2 * par_amt, par_amt) // (par_amt + 1)


def balanced_parens(par_amt: int, ind: int) -> Optional[str]:
    assert par_amt >= 0

    total = balanced_paren_num(par_amt)  # total number of balanced parenthesis
    # simple bounds checking
    if not 0 <= ind < total or par_amt < 0:
        return None
    if par_amt in [0, 1]:  # idk if my function can handle these cases
        return '' if par_amt == 0 else '()'

    # this[o][c] = ways to complete given o opening parenthesis & c closing parenthesis
    complete_ways = [[0 for _ in range(par_amt + 1)] for _ in range(par_amt + 1)]
    complete_ways[par_amt][par_amt] = 1
    for o in range(par_amt, -1, -1):
        for c in range(o, -1, -1):
            if o + 1 <= par_amt:
                complete_ways[o][c] += complete_ways[o + 1][c]
            if c + 1 <= par_amt:
                complete_ways[o][c] += complete_ways[o][c + 1]

    def actual_calc(curr_str: str, o_amt: int, c_amt: int, rel_ind: int) -> str:
        if o_amt == par_amt:
            return curr_str + ')' * (par_amt - c_amt)
        # adding the o comes before adding the c
        add_o = complete_ways[o_amt + 1][c_amt]
        if rel_ind < add_o:
            return actual_calc(curr_str + '(', o_amt + 1, c_amt, rel_ind)
        return actual_calc(curr_str + ')', o_amt, c_amt + 1, rel_ind - add_o)
    return actual_calc('', 0, 0, ind)


print(balanced_parens(2, 0))  # should output (())
print(balanced_parens(2, 1))  # should output ()()
print(balanced_parens(3, 3))  # should output ()(())
print(balanced_parens(3, 5))  # should output None
