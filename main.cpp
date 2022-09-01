
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>
#define INCL_DOSPROCESS
#include <os2.h>
#include <iostream.h>
#include <stddef.h>
#include <time.h>


const int mode = 1;
const double a = 20;
const double b = 0.2;
const double c = 2*3.14;
const double abs_err = 10;
const double rel_err = 10;
const int number_of_threads = 4;
double array[number_of_threads];
double division;

typedef struct{

    double x_start;
    double x_finish;
    double y_start;
    double y_finish;
    int step;
    int counter;
    int division;

} parser;

double calculate_function(double x, double y){
    double function_result = -a * exp(-b*sqrt(0.5*(pow(x,2)+pow(y,2))))
                             -exp(0.5 * (cos(c*x) + cos(c*y))) + a + exp(1);
    return function_result;
}

double calculate_thread(double x_start, double x_finish, double y_start, double y_finish, int step){


    double delta_x = (x_finish - x_start) / step;
    double delta_y = (y_finish - y_start) / step;

    double result = 0;

    for (int i = 0; i < step; i++){
        for (int j = 0; j < step; j++){
            result += calculate_function(x_start+(i*delta_x), y_start+(j*delta_y));
        }
    }

    result = result * delta_x * delta_y;
    return result;
}

void thread_code(void *param){
    parser *args = (parser*) param;
    double x_start1 = args->x_start;
    double x_finish1 = args->x_finish;
    double y_start1 = args->y_start;
    double y_finish1 = args->y_finish;
    int step1 = args->step;
    int counter1 = args->counter;
    int division1 = args->division;
    double result1 = 0;
    double result2 = 0;

    double stepp;

    while(true){
        result1 = calculate_thread(x_start1, x_finish1, y_start1, y_finish1, step1);
        stepp = step1 * 2;
        result2 = calculate_thread(x_start1, x_finish1, y_start1, y_finish1, step1);
        step1 = stepp;
        if ((fabs(result1-result2) < abs_err) && (fabs((result1-result2)/result1)) < rel_err){
            array[counter1] = result1;
            break;
        }
    }
    free(args);
    _endthread();
    return;
}

void start_thread(double x_start, double x_finish, double y_start, double y_finish, int step, int counter, int division) {

    int thread_id;
    parser *arg;
    arg = (parser *) malloc(4096 * 10);

    arg->x_start = x_start + division * (counter);
    arg->x_finish = x_start + division * (counter + 1);
    arg->y_start = y_start;
    arg->y_finish = y_finish;
    arg->step = step / number_of_threads;
    arg->counter = counter;
    arg->division = division;
    _beginthread(thread_code, 0, 8096, (void *) arg);
}


double calculate_single_thread(double x_start, double x_finish, double y_start, double y_finish, int step){


    double delta_x = (x_finish - x_start) / step;
    double delta_y = (y_finish - y_start) / step;

    double result = 0;

    for (int i = 0; i < step; i++){
        for (int j = 0; j < step; j++){
            result += calculate_function(i, j);
        }
    }

    result = result * delta_x * delta_y;
    return result;
}

double check_results(double x_start, double x_finish, double y_start, double y_finish, int step){
    double result1;
    double result2;
    int step1 = step;
    while(true){
        result1 = calculate_single_thread(x_start, x_finish, y_start, y_finish,step);
        step1 = step*2;
        result2 = calculate_single_thread(x_start, x_finish, y_start, y_finish,step1);
        step = step1;
        if ((fabs(result1-result2) < abs_err) || (fabs((result1-result2)/result1)) < rel_err){
            return result1;
        }
    }
}

int main(){

    if (mode == 1){
        clock_t start = clock();
        division = 200/number_of_threads;
        for (int i =0; i < number_of_threads; i++){
            start_thread(-100,100,-100,100,200,i,division);
        }
        double final = 0;
        for (int j =0; j < number_of_threads; j++){
            final += array[j];
        }
        clock_t finish = clock();
        double final_time = finish - start;
        printf("%f\n", final);
        printf("%f\n", final_time);
        return 0;
    }
    else{
        clock_t start = clock();
        double res = check_results(-100,100,-100,100,200);
        clock_t finish = clock();
        double final_time = finish - start;
        printf("%f\n", res);
        printf("%f\n", final_time);
    }


    getchar();
    return 0;

}