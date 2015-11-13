/*
 * Includes
 */
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Preloaded Code
 */

typedef struct {
  int length;
  int arr[];
} SPLArray_int;

typedef struct {
  int length;
  bool arr[];
} SPLArray_bool;

typedef struct {
  int length;
  char arr[];
} SPLArray_char;

typedef struct {
  int length;
  void* arr[];
} SPLArray_generic;


/*
 * Procedures
 */
int gclose (int fd);
int gopen (SPLArray_char* pathname, int flags);
int gread (int fd_2, SPLArray_char* buffer);
int greadOffset (int fd_3, SPLArray_char* buffer_1, int offset);
int gwrite (int fd_4, SPLArray_char* buffer_2);



/*
 * Main Function, here for compilability
 
int main() {
  return 0;
}
*/
