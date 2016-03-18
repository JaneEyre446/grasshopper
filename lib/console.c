#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * Preloaded Code
 */

typedef struct {
  int length;
  char arr[];
} SPLArray_char;

/*
 * Procedures
 */

bool gputs(SPLArray_char* buffer) {
  bool null_terminated = false;
  for (int i = 0; i < buffer->length && !null_terminated; i++) {
    null_terminated = buffer->arr[i] != 0;
  }
  if (null_terminated) {
    return fputs(buffer->arr, stdout) >= 0;
  } else {
    char str[buffer->length + 1]; //allocate on the stack for simplicity
    memcpy(str, buffer->arr, buffer->length);
    str[buffer->length] = 0;
    return fputs(str, stdout) >= 0;
  }
}

int ggets(SPLArray_char* buffer) {
  if (fgets(buffer->arr, buffer->length, stdin) == NULL) {
    return -1;
  } else {
    return strnlen(buffer->arr, buffer->length);
  }
}
