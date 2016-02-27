#include <string>

using namespace std;

#include "evalobj.h"

int Let::eval(env *environment) {
    env *newEnvironment = new env();
    newEnvironment->var = bvar;
    newEnvironment->value = bexp->eval(environment);
    newEnvironment->next = environment;

    return body->eval(newEnvironment);
}

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

int Constant::eval(env *) {
    return n;
}

