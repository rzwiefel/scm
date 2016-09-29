#ifndef PORT_H
#define PORT_H

#include <stdio.h>

#include "object.h"

extern object_t eof;

FILE *port_pointer(object_t *port);

void print_port(object_t *port);
void define_port(object_t *env);

#endif
