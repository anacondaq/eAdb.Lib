// file: util.h
// date: 5/9/2014
// auth: trickyloki3
// desc: general utility functions
#ifndef UTILITY_H
#define UTILITY_H
	#include <stdio.h>
   #include <stdlib.h>
   #include <stdarg.h>
   #include <string.h>
   #include <errno.h>
   #include <ctype.h>
   #include <stdint.h>
	
	// BUF_SIZE is the standard static buffer size
	#define BUF_SIZE 4096

	// FIELD_INT_EMPTY is used to indicate a integer field for an item is empty.
	#define FIELD_INT_EMPTY -1

	// DB_BEGIN is the starting index for all databases, i.e. any database entry at 
	// index zero is initialize to default or used for special cases.
	// 1. Binary search can return an index at 0 if the index is used.
	// 2. Heap sort does not have to handle child offset.
	#define DB_BEGIN 1

	// string of ASCII character set used for generating random string
   #define ASCII_SET "abcdefghijklmnopqrstuvwxyz0123456789"
   #define ASCII_SZE 36
	
	// type definition for function pointers
	typedef void (*DBSWAP)(void *, int, int);						// Using a void * to a db, swap the element given the two index positions.
	typedef int * (*DBFIELD)(void *);								// Using a void * to an entry in the db, return the field of type integer.
	typedef int * (*DBTYPE)(void *, int, DBFIELD);				// Using a void * to a db, return the field at the index.
	typedef char * (*DBFIELD_STR)(void *);							// Using a void * to an entry in the db, return the field of type string.
	typedef char * (*DBTYPE_STR)(void *, int, DBFIELD_STR);	// Using a void * to a db, return the field at the string.
	
	// binary search for integers, case-sensitive strings, and non-case sensitive strings.
	int bsearch_int(void * db, int db_size, int key, DBFIELD, DBTYPE);
	int bsearch_str(void * db, int db_size, char * key, DBFIELD_STR, DBTYPE_STR);
	int bsearch_ncs_str(void * db, int db_size, char * key, DBFIELD_STR field, DBTYPE_STR type);
	
	// heap sort for integers, case-sensitive strings, and non-case sensitive strings.
	void hpsort_int(void * db, int db_size, DBFIELD, DBTYPE, DBSWAP);
	void hpsort_str(void * db, int db_size, DBFIELD_STR, DBTYPE_STR, DBSWAP);

	// comparsion functions
	int greater_than(int a, int b);
	int less_than(int a, int b);
	int equal_to(int a, int b);
	int notequal_to(int a, int b);
	int bitmask(int a, int b);
	int notbitmask(int a, int b);
	int strcmp_greater(char * a, char * b);
	int strcmp_less(char * a, char * b);
	int strcmp_equal(char * a, char * b);
	int strstr_equal(char * a, char * b);
	int strstr_notequal(char * a, char * b);
	int underscore_equal(char * a, char * b);

	// string functions
	int ncs_strcmp(const char *, const char *);
	char * random_string(int32_t);
	int32_t convert_integer(const char *, int32_t);
	uint32_t convert_uinteger(const char *, uint32_t);
	char * convert_string(const char *);
	void convert_delimit_integer(char *, char, int32_t, ...);
#endif