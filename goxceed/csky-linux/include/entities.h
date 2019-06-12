#ifndef __XML_ENTITIES_H__
#define __XML_ENTITIES_H__

#include "parser.h"
#include "gxcore.h"

__BEGIN_DECLS

#define XML_INTERNAL_GENERAL_ENTITY		1
#define XML_EXTERNAL_GENERAL_PARSED_ENTITY	2
#define XML_EXTERNAL_GENERAL_UNPARSED_ENTITY	3
#define XML_INTERNAL_PARAMETER_ENTITY		4
#define XML_EXTERNAL_PARAMETER_ENTITY		5
#define XML_INTERNAL_PREDEFINED_ENTITY		6

/*
 * An unit of storage for an entity, contains the string, the value
 * and the linkind data needed for the linking in the hash table.
 */

typedef struct GXxmlEntity {
    int type;			/* The entity type */
    int len;			/* The lenght of the name */
    const CHAR    *name;	/* Name of the entity */
    const CHAR    *ExternalID;	/* External identifier for PUBLIC Entity */
    const CHAR    *SystemID;	/* URI for a SYSTEM or PUBLIC Entity */
    CHAR *content;		/* The entity content or ndata if unparsed */
} GXxmlEntity, *GXxmlEntityPtr;

/*
 * ALl entities are stored in a table there is one table per DTD
 * and one extra per document.
 */

#define XML_MIN_ENTITIES_TABLE	32

typedef struct GXxmlEntitiesTable {
    int nb_entities;		/* number of elements stored */
    int max_entities;		/* maximum number of elements */
    GXxmlEntityPtr table;	        /* the table of entities */
} GXxmlEntitiesTable, *GXxmlEntitiesTablePtr;


/*
 * External functions :
 */

extern void GXxmlAddDocEntity(GXxmlDocPtr doc, const CHAR *name, int type,
			      const CHAR *ExternalID, const CHAR *SystemID, CHAR *content);
extern void GXxmlAddDtdEntity(GXxmlDocPtr doc, const CHAR *name, int type,
			      const CHAR *ExternalID, const CHAR *SystemID, CHAR *content);
extern GXxmlEntityPtr GXxmlGetPredefinedEntity(const CHAR *name);
extern GXxmlEntityPtr GXxmlGetDocEntity(GXxmlDocPtr doc, const CHAR *name);
extern GXxmlEntityPtr GXxmlGetDtdEntity(GXxmlDocPtr doc, const CHAR *name);
extern CHAR *GXxmlEncodeEntities(GXxmlDocPtr doc, const CHAR *input);
extern GXxmlEntitiesTablePtr GXxmlCreateEntitiesTable(void);
extern GXxmlEntitiesTablePtr GXxmlCopyEntitiesTable(GXxmlEntitiesTablePtr table);
extern void GXxmlFreeEntitiesTable(GXxmlEntitiesTablePtr table);
extern void GXxmlDumpEntitiesTable(GXxmlEntitiesTablePtr table);
extern GXxmlParserInputPtr GXxmlNewEntityInputStream(GXxmlParserCtxtPtr ctxt,
						   GXxmlEntityPtr entity);
extern GXxmlEntitiesTablePtr GXxmlCopyEntitiesTable(GXxmlEntitiesTablePtr table);

__END_DECLS

# endif /* __XML_ENTITIES_H__ */
