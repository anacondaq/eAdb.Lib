// file: load.h
// date: 5/10/2014
// auth: trickyloki3
// desc: template for trim and load
#ifndef LOAD_H
#define LOAD_H
   #include "util.h"
   
   // generic function pointer type
   typedef int (*DB_TRIM)(FILE *, FILE *);
   typedef int (*DB_LOAD)(FILE *, void *, int32_t);

   // generic database wrapper 
   typedef struct {
      void * db;
      int32_t size;
   } generic_w;

   char * trim(const char *, int32_t *, DB_TRIM);
   void * load(const char *, DB_TRIM, DB_LOAD, size_t);
#endif