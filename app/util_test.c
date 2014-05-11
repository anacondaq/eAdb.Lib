#include "util.h"

int main(int argc, char * argv[]) {
   char test_des[BUF_SIZE];
   char * test_src = "5:10;15:20;25\0";
   char * end_ptr = NULL;

   printf("%s | %s\n", end_ptr = substr_delimit_list(test_src, test_des, ";:"), test_des);
   printf("%s | %s\n", end_ptr = substr_delimit_list(end_ptr + 1, test_des, ";:"), test_des);
   printf("%s | %s\n", end_ptr = substr_delimit_list(end_ptr + 1, test_des, ";:"), test_des);
   printf("%s | %s\n", end_ptr = substr_delimit_list(end_ptr + 1, test_des, ";:"), test_des);
   printf("%s | %s\n", end_ptr = substr_delimit_list(end_ptr + 1, test_des, ";:"), test_des);


   exit(EXIT_SUCCESS);
}