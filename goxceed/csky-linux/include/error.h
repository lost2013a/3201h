#ifndef error_h_
#define error_h_

#include "parser.h"

void GXxmlParserError(GXxmlParserCtxtPtr ctxt, const char *msg, ...);
void GXxmlParserWarning(GXxmlParserCtxtPtr ctxt, const char *msg, ...);
#endif
