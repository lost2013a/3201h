/*
 * debugXML.h : Interfaces to a set of routines used for debugging the tree
 *              produced by the XML parser.
 *
 * Daniel Veillard <Daniel.Veillard@w3.org>
 */

#ifndef __DEBUG_XML__
#define __DEBUG_XML__
#include "tree.h"

extern void GXxmlDebugDumpString(FILE *output, const CHAR *str);
extern void GXxmlDebugDumpAttr(FILE *output, GXxmlAttrPtr attr, int depth);
extern void GXxmlDebugDumpAttrList(FILE *output, GXxmlAttrPtr attr, int depth);
extern void GXxmlDebugDumpNode(FILE *output, GXxmlNodePtr node, int depth);
extern void GXxmlDebugDumpNodeList(FILE *output, GXxmlNodePtr node, int depth);
extern void GXxmlDebugDumpDocument(FILE *output, GXxmlDocPtr doc);
#endif /* __DEBUG_XML__ */
