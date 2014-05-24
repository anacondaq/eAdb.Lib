/*=============================================================================
   file: util.h
   date: 5/9/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: general utility functions
   note: very simple code
=============================================================================*/
#ifndef UTILITY_H
#define UTILITY_H
	#include <stdio.h>
   #include <stdlib.h>
   #include <stdarg.h>
   #include <string.h>
   #include <errno.h>
   #include <ctype.h>
   #include <stdint.h>
	
   /* simple array */
	typedef struct {  /* array wrapper */
      void * array;  /* array to int, long, etc  */
      int32_t size;  /* total number of elements */
      char delimit;  /* delimiter to separate elements when writing */
   } array_w;
   void array_io(array_w, FILE *);
   void array_unload(array_w);

	/* BUF_SIZE is the standard static buffer size */
	#define BUF_SIZE 4096

	/* FIELD_INT_EMPTY is used to indicate an integer field for an item is empty. */
	#define FIELD_INT_EMPTY -1

	/* DB_BEGIN is the starting index for all databases, i.e. any database entry at 
	   index zero is initialize to default or used for special cases.
	   1. Binary search can return an index at 0 if the index is used.
	   2. Heap sort does not have to handle child offset. */
	#define DB_BEGIN 1

	/* string of ASCII character set used for generating random string */
   #define ASCII_SET "abcdefghijklmnopqrstuvwxyz0123456789"
   #define ASCII_SZE 36
	
	/* type definition for function pointers */
	typedef void (*DBSWAP)(void *, int32_t, int32_t);				/* using a void * to a db, swap the element given the two index positions. */
	typedef int32_t * (*DBFIELD)(void *);								/* using a void * to an entry in the db, return the field of type integer. */
	typedef int32_t * (*DBTYPE)(void *, int, DBFIELD);				/* using a void * to a db, return the field at the index. */
	typedef char * (*DBFIELD_STR)(void *);								/* using a void * to an entry in the db, return the field of type string. */
	typedef char * (*DBTYPE_STR)(void *, int32_t, DBFIELD_STR);	/* using a void * to a db, return the field at the string. */
	
	/* binary search for integers, case-sensitive strings, and non-case sensitive strings. */
	int32_t bsearch_int(void * db, int32_t db_size, int32_t key, DBFIELD, DBTYPE);
	int32_t bsearch_str(void * db, int32_t db_size, char * key, DBFIELD_STR, DBTYPE_STR);
	int32_t bsearch_ncs_str(void * db, int32_t db_size, char * key, DBFIELD_STR field, DBTYPE_STR type);
	
	/* heap sort for integers, case-sensitive strings, and non-case sensitive strings. */
	void hpsort_int(void * db, int32_t db_size, DBFIELD, DBTYPE, DBSWAP);
	void hpsort_str(void * db, int32_t db_size, DBFIELD_STR, DBTYPE_STR, DBSWAP);

	/* comparsion functions */
	int32_t greater_than(int32_t a, int32_t b);
	int32_t less_than(int32_t a, int32_t b);
	int32_t equal_to(int32_t a, int32_t b);
	int32_t notequal_to(int32_t a, int32_t b);
	int32_t bitmask(int32_t a, int32_t b);
	int32_t notbitmask(int32_t a, int32_t b);
	int32_t strcmp_greater(char * a, char * b);
	int32_t strcmp_less(char * a, char * b);
	int32_t strcmp_equal(char * a, char * b);
	int32_t strstr_equal(char * a, char * b);
	int32_t strstr_notequal(char * a, char * b);
	int32_t underscore_equal(char * a, char * b);

   /* string functions */
	int32_t ncs_strcmp(const char *, const char *);
	char * substr_delimit(char *, char *, char);
	char * substr_delimit_list(char *, char *, char *);
	char * random_string(int32_t);
	int32_t convert_integer(const char *, int32_t);
	uint32_t convert_uinteger(const char *, uint32_t);
	char * convert_string(const char *);
	void convert_delimit_integer(char *, char, int32_t, ...);
	void convert_integer_list(char *, char *, array_w *);
#endif