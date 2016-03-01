#include <string>

using namespace std;

#include "evalobj.h"

/**
 * Handle evaluation of let expressions.
 * Add the variable for the let and then evaluate the expression with this new value.
 */
int Let::eval(env *environment) {
    env *newEnvironment = new env();
    newEnvironment->var = bvar;
    newEnvironment->value = bexp->eval(environment);
    newEnvironment->next = environment;

    return body->eval(newEnvironment);
}

/**
 * Handle evaluation of operators.
 * If the operator is plus then add the variables, if it's times then multiply them.
 */
int OpApp::eval(env *environment) {
    switch (op) {
        case plusop: {
            int sum = 0;
            while (args) {
                sum += args->head->eval(environment);
                args = args->tail;
            }

            return sum;
        }
        case timesop: {
            int product = 1;
            while (args) {
                product *= args->head->eval(environment);
                args = args->tail;
            }

            return product;
        }
    }
    return 0;
}

/**
 * Handle evaluation of variables.
 * Return the value of the variable.
 */
int Var::eval(env *environment) {
    while (environment) {
        if (name.compare(environment->var) == 0) {
            return environment->value;
        } else {
            environment = environment->next;
        }
    }
    return 0;
}

/**
 * Handle evaluation of constants.
 * Return the constant.
 */
int Constant::eval(env *) {
    return n;
}

