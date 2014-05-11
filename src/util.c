// file: util.c
// date: 5/9/2014
// auth: trickyloki3
// desc: general utility functions
#include "util.h"
static void sift_down_int(void * db, int root, int size, DBFIELD, DBTYPE, DBSWAP);
static void sift_down_str(void * db, int root, int size, DBFIELD_STR, DBTYPE_STR, DBSWAP);

void array_io(array_w array, FILE * file_stm) {
   int32_t i = 0;
   int32_t * list = array.array;
   int32_t size = array.size;
   for(i = 0; i < size - 1; i++)
      fprintf(file_stm,"%d%c", list[i], array.delimit);
   fprintf(file_stm,"%d,", list[i]);
}

void array_unload(array_w array) {
   if(array.array != NULL) free(array.array);
}

// binary search functions
int32_t bsearch_int(void * db, int32_t db_size, int32_t key, DBFIELD field, DBTYPE type) {
	int32_t top = db_size - 1;				
	int32_t bottom = DB_BEGIN;
	int32_t middle = 0;
	
	while(bottom <= top) {									// Distance between top and bottom is being searched
		middle = (top + bottom) / 2;
		if(*(*type)(db, middle, field) == key)			// keyValue is found, return middle (position)
			return middle;
		else if(*(*type)(db, middle, field) < key)	// keyValue is greater, search right side
			bottom = middle + 1;
		else if(*(*type)(db, middle, field) > key)	// keyValue is less, search left side
			top = middle - 1;
	}
	
	return 0;
}

int32_t bsearch_str(void * db, int32_t db_size, char * key, DBFIELD_STR field, DBTYPE_STR type) {
	int32_t top = db_size - 1;				
	int32_t bottom = DB_BEGIN;
	int32_t middle = 0;
	
	while(bottom <= top) {														// Distance between top and bottom is being searched
		middle = (top + bottom) / 2;
		if(strcmp((*type)(db, middle, field), key) == 0) {				// keyValue is found, return middle (position)
			return middle;
		} else if(strcmp((*type)(db, middle, field), key) == -1)		// keyValue is greater, search right side
			bottom = middle + 1;
		else if(strcmp((*type)(db, middle, field), key) == 1)			// keyValue is less, search left side
			top = middle - 1;
	}
	return 0;
}

int32_t bsearch_ncs_str(void * db, int32_t db_size, char * key, DBFIELD_STR field, DBTYPE_STR type) {
	int32_t top = db_size - 1;				
	int32_t bottom = DB_BEGIN;
	int32_t middle = 0;
	
	while(bottom <= top) {												// Distance between top and bottom is being searched
		middle = (top + bottom) / 2;
		if(ncs_strcmp((*type)(db, middle, field), key) == 0) {			// keyValue is found, return middle (position)
			return middle;
		} else if(ncs_strcmp((*type)(db, middle, field), key) == -1) {	// keyValue is greater, search right side
			bottom = middle + 1;
		} else if(ncs_strcmp((*type)(db, middle, field), key) == 1)	{ 	// keyValue is less, search left side
			top = middle - 1;
		}
	}
	return 0;
}

// max-heap sort functions
void hpsort_int(void * db, int32_t db_size, DBFIELD field, DBTYPE type, DBSWAP swap) {
	for(int32_t r = db_size / 2; r >= DB_BEGIN; r--)
		sift_down_int(db, r, db_size - DB_BEGIN, field, type, swap);
		
	for(int32_t i = db_size - DB_BEGIN; i >= 2; i--) {
		(*swap)(db, DB_BEGIN, i);
		sift_down_int(db, DB_BEGIN, i - DB_BEGIN, field, type, swap);
	}
}

void hpsort_str(void * db, int32_t db_size, DBFIELD_STR field, DBTYPE_STR type, DBSWAP swap) {
	for(int32_t r = db_size / 2; r >= DB_BEGIN; r--)
		sift_down_str(db, r, db_size - DB_BEGIN, field, type, swap);
		
	for(int32_t i = db_size - DB_BEGIN; i >= 2; i--) {
		swap(db, DB_BEGIN, i);
		sift_down_str(db, DB_BEGIN, i - DB_BEGIN, field, type, swap);
	}
}

static void sift_down_int(void * db, int32_t root, int32_t size, DBFIELD field, DBTYPE type, DBSWAP swap) {
	int32_t child = 2 * root;										// Left child of root
	
	while(root <= size) {										// Percolate down to the last level
		if(child < size && *(type(db, child, field)) < *(type(db, child+1, field))) 
			child++;													// Right child of root
			
		if(child <= size && *(type(db, root, field)) < *(type(db, child, field))) {
			swap(db, root, child);
			root = child;											// New root is the largest child
			child = 2 * child;									// Left child of root
		} else {
			break;
		}
	}
}

static void sift_down_str(void * db, int32_t root, int32_t size, DBFIELD_STR field, DBTYPE_STR type, DBSWAP swap) {
	int32_t child = 2 * root;										// Left child of root
	
	while(root <= size) {										// Percolate down to the last level
		if(child < size && ncs_strcmp(type(db, child, field), type(db, child+1, field)) == -1) 
			child++;													// Right child of root
			
		if(child <= size && ncs_strcmp(type(db, root, field), type(db, child, field)) == -1) {
			swap(db, root, child);
			root = child;											// New root is the largest child
			child = 2 * child;									// Left child of root
		} else {
			break;
		}
	}
}

// comparsion functions
int32_t greater_than(int32_t a, int32_t b) { return (a > b); }
int32_t less_than(int32_t a, int32_t b) { return (a < b); }
int32_t equal_to(int32_t a, int32_t b) { return (a == b); }
int32_t notequal_to(int32_t a, int32_t b) { return (a != b); }
int32_t bitmask(int32_t a, int32_t b) { if(a > 0 && b > 0) return (a & b); else return 0; }
int32_t notbitmask(int32_t a, int32_t b) { return !(a & b); }
int32_t strcmp_greater(char * a, char * b) { return (strcmp(a,b) == 1); }
int32_t strcmp_less(char * a, char * b) { return (strcmp(a,b) == -1); }
int32_t strcmp_equal(char * a, char * b) { return (strcmp(a,b) == 0); }
int32_t strstr_equal(char * a, char * b) { if(strstr(a,b)) return 1; else return 0; }
int32_t strstr_notequal(char * a, char * b) { if(strstr(a,b)) return 0; else return 1; }
int32_t underscore_equal(char * a, char * b) { if(a[0] == b[0] && a[1] == '_') return 1; else return 0; }

// not case sensitive string comparsion; 
// -1 str1 < str2 0 str1 == str2 1 str1 > str2
int32_t ncs_strcmp(const char * str1, const char * str2) {
	int32_t offset1 = 0;
	int32_t offset2 = 0;
	// Check whether both strings exist
	if(str1 == NULL || str2 == NULL) exit(EXIT_FAILURE);

	// Attempt to find mismatch
	for(int32_t i = 0; str1[i+offset1] != '\0' || str2[i+offset2] != '\0'; i++) {
		if(str1[i+offset1] == '_') offset1++;						// Exclude comparing '_'
		if(str2[i+offset2] == '_') offset2++;
		if(toupper(str1[i+offset1]) != toupper(str2[i+offset2])) {
			if(toupper(str1[i+offset1]) > toupper(str2[i+offset2]))
				return 1;
			else
				return -1;
		}
	}
	return 0;
}

int32_t ncs_nstrcmp(const char * str1, const char * str2, int length) {
   int32_t offset1 = 0;
   int32_t offset2 = 0;
   // Check whether both strings exist
   if(str1 == NULL || str2 == NULL) exit(EXIT_FAILURE);

   // Attempt to find mismatch
   for(int32_t i = 0; (str1[i+offset1] != '\0' || str2[i+offset2] != '\0') && i < length; i++) {
      if(str1[i+offset1] == '_') offset1++;                  // Exclude comparing '_'
      if(str2[i+offset2] == '_') offset2++;
      if(toupper(str1[i+offset1]) != toupper(str2[i+offset2])) {
         if(toupper(str1[i+offset1]) > toupper(str2[i+offset2]))
            return 1;
         else
            return -1;
      }
   }
   return 0;
}

// Retrieve a substring of the string and stop on delimiter.
char * substr_delimit(char * src, char * dest, char delimit) {
   int32_t i;
   int32_t src_cnt = strlen(src);
   for(i = 0; i < src_cnt; i++)
      if((src[i] == delimit || src[i] == '\0') && i > 0) {
         strncpy(dest, src, i);
         dest[i] = '\0';
         return &src[i];
      }
   // retrieve the whole string if unmatch delimit
   strncpy(dest, src, src_cnt);
   dest[src_cnt] = '\0';
   return &src[src_cnt];
}

char * substr_delimit_list(char * src, char * dest, char * delimit) {
   int32_t i, j;
   int32_t src_cnt = strlen(src);
   int32_t del_cnt = strlen(delimit);

   for(i = 0; i < src_cnt; i++) {
      for(j = 0; j < del_cnt; j++)
         if(src[i] == delimit[j] && i > 0) {
            strncpy(dest, src, i);
            dest[i] = '\0';
            return &src[i];
         }
   }

   // retrieve the whole string if unmatch delimit
   strncpy(dest, src, src_cnt);
   dest[src_cnt] = '\0';
   return &src[src_cnt];
}

// Generate a string using the ASCII character set.
// int length - length of the string to generate.
char * random_string(int32_t length) {
   int32_t i = 0;
   char * random_string = malloc(sizeof(char) * (length + 1));
   if(random_string == NULL) return NULL;
   for(i = 0; i < length; i++)
      random_string[i] = ASCII_SET[rand() % ASCII_SZE];
   random_string[i] = '\0';
   return random_string;
}

// Convert the string into an integer.
// char * str - The string containing the integer.
// int base - The integer notation of the string, i.e
// binary, octal, decimal, hexadecimal, ... (2 - 32)
int32_t convert_integer(const char * str, int32_t base) {
   int64_t value = 0;
   char * endptr = NULL;

   if(str == NULL || *str == '\0')    // check the paramater string
      return FIELD_INT_EMPTY;

   // override the base for hexadecimal numbers
   if(strlen(str) > 2 && str[0] == '0' && str[1] == 'x')
      base = 16;

   value = strtol(str, &endptr, base);

   if(errno == ERANGE)               // check if value is valid (out of range of the strtol function)
      fprintf(stdout,"warn: convert_integer detected out-of-range string conversion to (int32_t) %s.\n", str);

   if(*endptr != '\0')               // check if string consume
      fprintf(stdout,"warn: convert_integer failed to consume entire string for conversion %s; unconsumed %s; base %d.\n", str, endptr, base);

   if(value > INT32_MAX)            // check if out of range (although this might not work)
      fprintf(stdout,"warn: convert_integer possible out-of-range string conversion to (int32_t) %s.\n", str);

   return (int32_t) value;
}

uint32_t convert_uinteger(const char * str, uint32_t base) {
   uint64_t value = 0;
   char * endptr = NULL;

   if(str == NULL || *str == '\0')    // check the paramater string
      return FIELD_INT_EMPTY;

   value = strtoul(str, &endptr, base);

   if(errno == ERANGE)               // check if value is valid (out of range of the strtoul function)
      fprintf(stdout,"warn: convert_integer detected out-of-range string for conversion to long %s.\n", str);

   if(*endptr != '\0')               // check if string consume
      fprintf(stdout,"warn: convert_integer failed to consume entire string for conversion %s; unconsumed %s; base %d.\n", str, endptr, base);

   if(value > UINT32_MAX)            // check if out of range (although this might not work)
      fprintf(stdout,"warn: convert_integer possible out-of-range string conversion to (uint32_t) %s.\n", str);

   return (uint32_t) value;
}

// Allocate memory for the string.
// char * str - The string to be placed into memory.
char * convert_string(const char * str) {
   char * temp = NULL;
   if(str != NULL && *str != '\0') {                 // check the paramater string
      temp = malloc(sizeof(char) * (strlen(str) + 1)); // allocate space for the string
      if(temp != NULL) strcpy(temp, str);            // check if memory allocated
   }
   return temp;                                      // may be NULL or copied string
}

// Extract a list of integers delimited by (delimiter) and place
// the value into (argc) paramaters in a variable length argument
// list.
void convert_delimit_integer(char * str, char delimit, int32_t argc, ...) {
   int32_t i = 0;
   int32_t * temp = NULL;      // current integer variable to fill
   char * curptr = str;    // current string position
   char * endptr = str;    // last string position
   va_list argv;
   va_start(argv, argc);

   // check the paramater string
   if(str != NULL && *str != '\0') {
      // extract the integer from string
      for(i = 0; i < argc && *endptr != '\0'; i++) {
         temp = va_arg(argv, int32_t *);
         *temp = (int32_t) strtol(curptr, &endptr, 10);
         curptr = endptr + 1;                        // skip delimiter

         if(errno == ERANGE)                         // check if conversion is valid
            fprintf(stdout,"warn: convert_delimit_integer detected out-of-range string for conversion to long.\n");

         if(*endptr != delimit && *endptr != '\0')   // check if delimiter or null
            fprintf(stdout,"warn: convert_delimit_integer failed to match delimiter for %s.\n", str);
      }

      // check if the entire string is consumed
      if(*endptr != '\0')
         fprintf(stdout,"warn: convert_delimit_integer failed to match all integers in %s, missing paramaters.\n", str);
   }

   // set all remaining paramaters to default
   for(; i < argc; i++) {
      temp = va_arg(argv, int32_t *);
      *temp = FIELD_INT_EMPTY;
   }
   va_end(argv);
}

void convert_integer_list(char * str, char * delimit, array_w * list) {
   int32_t i, j;
   int32_t * int_list = NULL;
   int32_t str_cnt = strlen(str);
   int32_t del_cnt = strlen(delimit);
   int32_t fld_cnt = 1;
   char * end_ptr = NULL;
   char fld[BUF_SIZE];

   // check the paramater
   if(str == NULL || delimit == NULL || list == NULL) {
      fprintf(stdout,"warn: convert_integer_list detected NULL paramaters.\n");
      return;
   }

   // find the total number of fields
   for(i = 0; i < str_cnt; i++)
      for(j = 0; j < del_cnt; j++)
         if(str[i] == delimit[j]) {
            fld_cnt++;
            break;
         }

   // allocate memory for the list
   int_list = malloc(sizeof(int32_t) * fld_cnt);

   // extract the fields
   end_ptr = substr_delimit_list(str, fld, delimit);
   int_list[0] = convert_integer(fld, 10);
   for(i = 1; end_ptr != NULL && i < fld_cnt; i++) {
      end_ptr = substr_delimit_list(end_ptr + 1, fld, delimit);
      int_list[i] = convert_integer(fld, 10);
   }

   // set the new array
   list->array = (void *) int_list;
   list->size = fld_cnt;
   list->delimit = delimit[0];
}