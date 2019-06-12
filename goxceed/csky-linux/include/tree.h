#ifndef __XML_TREE_H__
#define __XML_TREE_H__

#include "gxcore.h"

__BEGIN_DECLS

/*
 * The different element types carried by an XML tree
 *
 * NOTE: This is synchronized with DOM Level1 values
 *       See http://www.w3.org/TR/REC-DOM-Level-1/
 */
typedef enum {
    XML_ELEMENT_NODE=		1,
    XML_ATTRIBUTE_NODE=		2,
    XML_TEXT_NODE=		3,
    XML_CDATA_SECTION_NODE=	4,
    XML_ENTITY_REF_NODE=	5,
    XML_ENTITY_NODE=		6,
    XML_PI_NODE=		7,
    XML_COMMENT_NODE=		8,
    XML_DOCUMENT_NODE=		9,
    XML_DOCUMENT_TYPE_NODE=	10,
    XML_DOCUMENT_FRAG_NODE=	11,
    XML_NOTATION_NODE=		12
} GXxmlElementType;

/*
 * Size of an internal character representation.
 *
 * Currently we use 8bit chars internal representation for memory efficiency,
 * but the parser is not tied to that, just define UNICODE to switch to
 * a 16 bits internal representation. Note that with 8 bits wide
 * CHARs one can still use UTF-8 to handle correctly non ISO-Latin
 * input.
 */
#ifdef UNICODE
typedef unsigned short CHAR;
#else
typedef unsigned char CHAR;
#endif

/*
 * a DTD Notation definition
 * TODO !!!!
 */

/*
 * a DTD Attribute definition
 * TODO !!!!
 */

/*
 * a DTD Element definition.
 */
#define XML_ELEMENT_TYPE_EMPTY		1
#define XML_ELEMENT_TYPE_ANY		2
#define XML_ELEMENT_TYPE_MIXED		3
#define XML_ELEMENT_TYPE_ELEMENT	4

typedef struct GXxmlElement {
    const CHAR    *name;	/* Element name */
    int            type;	/* type (too simple, to extend ...) */
    /* TODO !!! more needed */
} GXxmlElement, *GXxmlElementPtr;

/*
 * An XML namespace.
 * Note that prefix == NULL is valid, it defines the default namespace
 * within the subtree (until overriden).
 */

#define XML_GLOBAL_NAMESPACE		1 /* old style global namespace */
#define XML_LOCAL_NAMESPACE		2 /* new style local scoping */

typedef struct GXxmlNs {
    struct GXxmlNs  *next;	/* next Ns link for this node  */
    int            type;	/* global or local */
    const CHAR    *href;	/* URL for the namespace */
    const CHAR    *prefix;	/* prefix for the namespace */
} GXxmlNs, *GXxmlNsPtr;

/*
 * An XML DtD, as defined by <!DOCTYPE.
 */
typedef struct GXxmlDtd {
    const CHAR    *name;	/* Name of the DTD */
    const CHAR    *ExternalID;	/* External identifier for PUBLIC DTD */
    const CHAR    *SystemID;	/* URI for a SYSTEM or PUBLIC DTD */
    void          *elements;    /* Hash table for elements if any */
    void          *entities;    /* Hash table for entities if any */
    /* struct xmlDtd *next;	 * next  link for this document  */
} GXxmlDtd, *GXxmlDtdPtr;

/*
 * A attribute of an XML node.
 */
typedef struct GXxmlAttr {
#ifndef XML_WITHOUT_CORBA
    void           *_private;	/* for Corba, must be first ! */
    void           *vepv;	/* for Corba, must be next ! */
#endif
    GXxmlElementType  type;       /* XML_ATTRIBUTE_NODE, must be third ! */
    struct GXxmlNode *node;	/* attr->node link */
    struct GXxmlAttr *next;	/* parent->childs link */
    const CHAR       *name;       /* the name of the property */
    struct GXxmlNode *val;        /* the value of the property */
} GXxmlAttr, *GXxmlAttrPtr;

/*
 * A node in an XML tree.
 */
typedef struct GXxmlNode {
#ifndef XML_WITHOUT_CORBA
    void           *_private;	/* for Corba, must be first ! */
    void           *vepv;	/* for Corba, must be next ! */
#endif
    GXxmlElementType  type;	/* type number in the DTD, must be third ! */
    struct GXxmlDoc  *doc;	/* the containing document */
    struct GXxmlNode *parent;	/* child->parent link */
    struct GXxmlNode *next;	/* next sibling link  */
    struct GXxmlNode *prev;	/* previous sibling link  */
    struct GXxmlNode *childs;	/* parent->childs link */
    struct GXxmlAttr *properties;	/* properties list */
    const CHAR     *name;       /* the name of the node, or the entity */
    GXxmlNs          *ns;         /* pointer to the associated namespace */
    GXxmlNs          *nsDef;      /* namespace definitions on this node */
    CHAR           *content;    /* the content */
} GXxmlNode, *GXxmlNodePtr;

/*
 * An XML document.
 */
typedef struct GXxmlDoc {
#ifndef XML_WITHOUT_CORBA
    void           *_private;	/* for Corba, must be first ! */
    void           *vepv;	/* for Corba, must be next ! */
#endif
    GXxmlElementType  type;       /* XML_DOCUMENT_NODE, must be second ! */
    char           *name;	/* name/filename/URI of the document */
    const CHAR     *version;	/* the XML version string */
    const CHAR     *encoding;   /* encoding, if any */
    int             compression;/* level of zlib compression */
    int             standalone; /* standalone document (no external refs) */
    struct GXxmlDtd  *dtd;	/* the document DTD if available */
    struct GXxmlNs   *oldNs;	/* Global namespace, the old way */
    void           *entities;   /* Hash table for general entities if any */
    struct GXxmlNode *root;	/* the document tree */
} GXxmlDoc, *GXxmlDocPtr;

/*
 * Variables.
 */
extern GXxmlNsPtr GXbaseDTD;
extern int GXoldXMLWDcompatibility;/* maintain compatibility with old WD */
extern int GXxmlIndentTreeOutput;  /* try to indent the tree dumps */

/*
 * Creating/freeing new structures
 */
extern GXxmlDtdPtr GXxmlNewDtd(GXxmlDocPtr doc, const CHAR *name,
                    const CHAR *ExternalID, const CHAR *SystemID);
extern void GXxmlFreeDtd(GXxmlDtdPtr cur);
extern GXxmlNsPtr GXxmlNewGlobalNs(GXxmlDocPtr doc, const CHAR *href, const CHAR *AS);
extern GXxmlNsPtr GXxmlNewNs(GXxmlNodePtr node, const CHAR *href, const CHAR *AS); extern void GXxmlFreeNs(GXxmlNsPtr cur); extern GXxmlDocPtr GXxmlNewDoc(const CHAR *version);
extern void GXxmlFreeDoc(GXxmlDocPtr cur);
extern GXxmlAttrPtr GXxmlNewDocProp(GXxmlDocPtr doc, const CHAR *name,
                                    const CHAR *value);
extern GXxmlAttrPtr GXxmlNewProp(GXxmlNodePtr node, const CHAR *name,
                                 const CHAR *value);
extern void GXxmlFreePropList(GXxmlAttrPtr cur);
extern void GXxmlFreeProp(GXxmlAttrPtr cur);
extern GXxmlAttrPtr GXxmlCopyProp(GXxmlAttrPtr cur);
extern GXxmlAttrPtr GXxmlCopyPropList(GXxmlAttrPtr cur);
extern GXxmlDtdPtr GXxmlCopyDtd(GXxmlDtdPtr dtd);
extern GXxmlDocPtr GXxmlCopyDoc(GXxmlDocPtr doc, int recursive);

/*
 * Creating new nodes
 */
extern GXxmlNodePtr GXxmlNewDocNode(GXxmlDocPtr doc, GXxmlNsPtr ns,
                                    const CHAR *name, CHAR *content);
extern GXxmlNodePtr GXxmlNewNode(GXxmlNsPtr ns, const CHAR *name);
extern GXxmlNodePtr GXxmlNewChild(GXxmlNodePtr parent, GXxmlNsPtr ns,
                                const CHAR *name, CHAR *content);
extern GXxmlNodePtr GXxmlNewDocText(GXxmlDocPtr doc, const CHAR *content);
extern GXxmlNodePtr GXxmlNewText(const CHAR *content);
extern GXxmlNodePtr GXxmlNewDocTextLen(GXxmlDocPtr doc, const CHAR *content, int len);
extern GXxmlNodePtr GXxmlNewTextLen(const CHAR *content, int len);
extern GXxmlNodePtr GXxmlNewDocComment(GXxmlDocPtr doc, CHAR *content);
extern GXxmlNodePtr GXxmlNewTextLen(const CHAR *content, int len);
extern GXxmlNodePtr GXxmlNewReference(GXxmlDocPtr doc, const CHAR *name);
extern GXxmlNodePtr GXxmlCopyNode(GXxmlNodePtr node, int recursive);
extern GXxmlNodePtr GXxmlCopyNodeList(GXxmlNodePtr node);

/*
 * Navigating
 */
extern GXxmlNodePtr GXxmlGetLastChild(GXxmlNodePtr node);
extern int GXxmlNodeIsText(GXxmlNodePtr node);

/*
 * Changing the structure
 */
extern GXxmlNodePtr GXxmlAddChild(GXxmlNodePtr parent, GXxmlNodePtr cur);
extern void GXxmlUnlinkNode(GXxmlNodePtr cur);

extern GXxmlNodePtr GXxmlTextMerge(GXxmlNodePtr first, GXxmlNodePtr second);
extern void GXxmlTextConcat(GXxmlNodePtr node, const CHAR *content, int len);

extern void GXxmlFreeNodeList(GXxmlNodePtr cur);
extern void GXxmlFreeNode(GXxmlNodePtr cur);

/*
 * Namespaces
 */
extern GXxmlNsPtr GXxmlSearchNs(GXxmlDocPtr doc, GXxmlNodePtr node,
                                const CHAR *nameSpace);
extern GXxmlNsPtr GXxmlSearchNsByHref(GXxmlDocPtr doc, GXxmlNodePtr node,
                                      const CHAR *href);
extern void GXxmlSetNs(GXxmlNodePtr node, GXxmlNsPtr ns);
extern GXxmlNsPtr GXxmlCopyNamespace(GXxmlNsPtr cur);
extern GXxmlNsPtr GXxmlCopyNamespaceList(GXxmlNsPtr cur);

/*
 * Changing the content.
 */
extern GXxmlAttrPtr GXxmlSetProp(GXxmlNodePtr node, const CHAR *name,
                                 const CHAR *value);
extern CHAR *GXxmlGetProp(GXxmlNodePtr node, const CHAR *name);
extern GXxmlNodePtr GXxmlStringGetNodeList(GXxmlDocPtr doc, const CHAR *value);
extern GXxmlNodePtr GXxmlStringLenGetNodeList(GXxmlDocPtr doc, const CHAR *value,
                                            int len);
extern CHAR *GXxmlNodeListGetString(GXxmlDocPtr doc, GXxmlNodePtr list, int inLine);
extern void GXxmlNodeSetContent(GXxmlNodePtr cur, const CHAR *content);
extern void GXxmlNodeSetContentLen(GXxmlNodePtr cur, const CHAR *content, int len);
extern void GXxmlNodeAddContent(GXxmlNodePtr cur, const CHAR *content);
extern void GXxmlNodeAddContentLen(GXxmlNodePtr cur, const CHAR *content, int len);
extern CHAR *GXxmlNodeGetContent(GXxmlNodePtr cur);

/*
 * Internal, don't use
 */
extern void GXxmlBufferWriteCHAR(const CHAR *string);
extern void GXxmlBufferWriteChar(const char *string);

/*
 * Saving
 */
extern void GXxmlDocDumpMemory(GXxmlDocPtr cur, CHAR**mem, int *size);
extern void GXxmlDocDump(FILE *f, GXxmlDocPtr doc);
int GXxmlSaveFile(const char *filename, GXxmlDocPtr cur);

/*
 * Compression
 */
extern int  GXxmlGetDocCompressMode (GXxmlDocPtr doc);
extern void GXxmlSetDocCompressMode (GXxmlDocPtr doc, int mode);
extern int  GXxmlGetCompressMode(void);
extern void GXxmlSetCompressMode(int mode);

__END_DECLS

#endif /* __XML_TREE_H__ */

