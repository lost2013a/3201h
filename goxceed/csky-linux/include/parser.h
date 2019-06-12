#ifndef __XML_PARSER_H__
#define __XML_PARSER_H__

#include "tree.h"
#include "gxcore.h"

__BEGIN_DECLS

/*
 * Constants.
 */
#define XML_DEFAULT_VERSION	"1.0"

typedef struct GXxmlParserInput {
	const char *filename;             /* The file analyzed, if any */
	const CHAR *base;                 /* Base of the array to parse */
	const CHAR *cur;                  /* Current char being parsed */
	int line;                         /* Current line */
	int col;                          /* Current column */
} GXxmlParserInput, *GXxmlParserInputPtr;

typedef struct GXxmlParserNodeInfo {
	const struct GXxmlNode* node;
	/* Position & line # that text that created the node begins & ends on */
	unsigned long begin_pos;
	unsigned long begin_line;
	unsigned long end_pos;
	unsigned long end_line;
} GXxmlParserNodeInfo;

typedef struct GXxmlParserNodeInfoSeq {
	unsigned long maximum;
	unsigned long length;
	GXxmlParserNodeInfo* buffer;
} GXxmlParserNodeInfoSeq, *GXxmlParserNodeInfoSeqPtr;

typedef struct GXxmlParserCtxt {
	struct GXxmlSAXHandler *sax;        /* The SAX handler */
	GXxmlDocPtr doc;                    /* the document being built */

	/* Input stream stack */
	GXxmlParserInputPtr  input;         /* Current input stream */
	int		     inputNr;       /* Number of current input streams */
	int                  inputMax;      /* Max number of input streams */
	GXxmlParserInputPtr  *inputTab;      /* stack of inputs */

	/* Node analysis stack */
	GXxmlNodePtr       node;          /* Current parsed Node */
	int                nodeNr;        /* Depth of the parsing stack */
	int                nodeMax;       /* Max depth of the parsing stack */
	GXxmlNodePtr       *nodeTab;       /* array of nodes */

	int record_info;                  /* Whether node info should be kept */
	GXxmlParserNodeInfoSeq node_seq;    /* info about each node parsed */
} GXxmlParserCtxt, *GXxmlParserCtxtPtr;

/*
 * a SAX Locator.
 */

typedef struct GXxmlSAXLocator {
	const CHAR *(*getPublicId)(GXxmlParserCtxtPtr ctxt);
	const CHAR *(*getSystemId)(GXxmlParserCtxtPtr ctxt);
	int (*getLineNumber)(GXxmlParserCtxtPtr ctxt);
	int (*getColumnNumber)(GXxmlParserCtxtPtr ctxt);
} GXxmlSAXLocator, *GXxmlSAXLocatorPtr;

/*
 * a SAX Exception.
 */

typedef GXxmlParserInputPtr (*resolveEntitySAXFunc) (GXxmlParserCtxtPtr ctxt,
			     const CHAR *publicId, const CHAR *systemId);
typedef void (*notationDeclSAXFunc)(GXxmlParserCtxtPtr ctxt, const CHAR *name,
			     const CHAR *publicId, const CHAR *systemId);
typedef void (*unparsedEntityDeclSAXFunc)(GXxmlParserCtxtPtr ctxt,
					  const CHAR *name, const CHAR *publicId,
					  const CHAR *systemId, const CHAR *notationName);
typedef void (*setDocumentLocatorSAXFunc) (GXxmlParserCtxtPtr ctxt,
					   GXxmlSAXLocatorPtr loc);
typedef void (*startDocumentSAXFunc) (GXxmlParserCtxtPtr ctxt);
typedef void (*endDocumentSAXFunc) (GXxmlParserCtxtPtr ctxt);
typedef void (*startElementSAXFunc) (GXxmlParserCtxtPtr ctxt, const CHAR *name);
typedef void (*endElementSAXFunc) (GXxmlParserCtxtPtr ctxt, const CHAR *name);
typedef void (*attributeSAXFunc) (GXxmlParserCtxtPtr ctxt, const CHAR *name,
				  const CHAR *value);
typedef void (*charactersSAXFunc) (GXxmlParserCtxtPtr ctxt, const CHAR *ch,
				   int start, int len);
typedef void (*ignorableWhitespaceSAXFunc) (GXxmlParserCtxtPtr ctxt,
					    const CHAR *ch, int start, int len);
typedef void (*processingInstructionSAXFunc) (GXxmlParserCtxtPtr ctxt,
					      const CHAR *target, const CHAR *data);
typedef void (*warningSAXFunc) (GXxmlParserCtxtPtr ctxt, const char *msg, ...);
typedef void (*errorSAXFunc) (GXxmlParserCtxtPtr ctxt, const char *msg, ...);
typedef void (*fatalErrorSAXFunc) (GXxmlParserCtxtPtr ctxt, const char *msg, ...);

typedef struct GXxmlSAXHandler {
	resolveEntitySAXFunc resolveEntity;
	notationDeclSAXFunc notationDecl;
	unparsedEntityDeclSAXFunc unparsedEntityDecl;
	setDocumentLocatorSAXFunc setDocumentLocator;
	startDocumentSAXFunc startDocument;
	endDocumentSAXFunc endDocument;
	startElementSAXFunc startElement;
	endElementSAXFunc endElement;
	attributeSAXFunc attribute;
	charactersSAXFunc characters;
	ignorableWhitespaceSAXFunc ignorableWhitespace;
	processingInstructionSAXFunc processingInstruction;
	warningSAXFunc warning;
	errorSAXFunc error;
	fatalErrorSAXFunc fatalError;
} GXxmlSAXHandler, *GXxmlSAXHandlerPtr;

/*
 * Global variables: just the SAX interface tables we are looking for full
 *      reentrancy of the code !
 */
extern GXxmlSAXLocator GXxmlDefaultSAXLocator;
extern GXxmlSAXHandler GXxmlDefaultSAXHandler;

#include "entities.h"

/*
 * Interfaces
 */
extern int GXxmlParseDocument(GXxmlParserCtxtPtr ctxt);
extern GXxmlDocPtr GXxmlParseDoc(CHAR *cur);
extern GXxmlDocPtr GXxmlParseMemory(char *buffer, int size);
extern GXxmlDocPtr GXxmlParseFile(const char *filename);
extern GXxmlDocPtr GXxmlSAXParseDoc(GXxmlSAXHandlerPtr sax, CHAR *cur);
extern GXxmlDocPtr GXxmlSAXParseMemory(GXxmlSAXHandlerPtr sax, char *buffer, int size);
extern GXxmlDocPtr GXxmlSAXParseFile(GXxmlSAXHandlerPtr sax, const char *filename);
extern CHAR *GXxmlStrdup(const CHAR *input);
extern CHAR *GXxmlStrndup(const CHAR *input, int n);
extern CHAR *GXxmlStrchr(const CHAR *str, CHAR val);
extern int GXxmlStrcmp(const CHAR *str1, const CHAR *str2);
extern int GXxmlStrncmp(const CHAR *str1, const CHAR *str2, int len);
extern int GXxmlStrlen(const CHAR *str);
extern CHAR *GXxmlStrcat(CHAR *cur, const CHAR *add);
extern CHAR *GXxmlStrncat(CHAR *cur, const CHAR *add, int len);

extern void GXxmlInitParserCtxt(GXxmlParserCtxtPtr ctx);
extern void GXxmlClearParserCtxt(GXxmlParserCtxtPtr ctx);
extern void GXxmlSetupParserForBuffer(GXxmlParserCtxtPtr ctx, const CHAR* buffer,
				      const char* filename);

extern void GXxmlParserError(GXxmlParserCtxtPtr ctxt, const char *msg, ...);

extern const GXxmlParserNodeInfo* GXxmlParserFindNodeInfo(const GXxmlParserCtxt* c,
							  const GXxmlNode* node);
extern void GXxmlInitNodeInfoSeq(GXxmlParserNodeInfoSeqPtr seq);
extern void GXxmlClearNodeInfoSeq(GXxmlParserNodeInfoSeqPtr seq);
unsigned long GXxmlParserFindNodeInfoIndex(const GXxmlParserNodeInfoSeq* seq,
					   const GXxmlNode* node);
extern void GXxmlParserAddNodeInfo(GXxmlParserCtxtPtr ctx,
		const GXxmlParserNodeInfo* info);

extern void GXxmlParserWarning(GXxmlParserCtxtPtr ctxt, const char *msg, ...);
extern void GXxmlParserError(GXxmlParserCtxtPtr ctxt, const char *msg, ...);
extern void GXxmlDefaultSAXHandlerInit(void);

__END_DECLS

#endif /* __XML_PARSER_H__ */

