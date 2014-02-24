#include <stdio.h>
#include "vectormath.h"
#include "vectormath.c"


int main(){
        vector test = {2.0, 3.141592653589, 1.414};
        double result;

        result = vdot(test, test);

        printf("%f\n", result);

        return 0;
}
