#ifndef _MBIS_CLIENT_XML_PARSE_H_
#define _MBIS_CLIENT_XML_PARSE_H_

#include "tree.h"
#include "jansson.h"

typedef unsigned char xmlChar; 
//#define XML_PRASE_DEBUG   0   //å¼€å…³æ‰“å°è°ƒè¯•

#define XML_FREE(x) if(x){GxCore_Free(x);x=NULL;}
#define XML_GET_CHILD(node) node->childs
#define XML_GET_NEXT(node) node->next
#define XML_GET_ROOT(doc)   doc->root
#define XML_GET_PROPERTIES(node) node->properties

#define GROUP_BG         ((xmlChar *) "Background"            )
#define GROUP_FG         ((xmlChar *) "FgColor"            )

enum {                                                                                                                             
    GX_ERROR_XML_DOC_PARSE = 3,
    GX_ERROR_XML_DOC_EMPTY,
    GX_ERROR_CLUT_INVALID,
    GX_ERROR_FILE_WIDGET_INVALID,
    GX_ERROR_FILE_STYLE_INVALID,
    GX_ERROR_FILE_I18N_INVALID,
    GX_ERROR_FILE_IMAGE_INVALID,
    GX_ERROR_FILE_FONT_INVALID,
    GX_ERROR_FILE_PAL_INVALID
};

/* ÊÓÆµ²ÎÊý */ 
typedef struct _mbis_video_info_t_{
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	char pOID[256]; 
}mbis_video_info_t;

#define MAX_HREF_LENGTH		(64)

extern int GXxmlStrcmp(const CHAR *str1, const CHAR *str2);
extern GXxmlDocPtr GXxmlParseFile(const char *filename);

void mbis_xml_init_file_path(void); 
extern char *mbis_xml_get_file_path(void); 
extern GXxmlNodePtr mbis_xml_get_node(GXxmlNodePtr root, uint8_t level, uint8_t index);
extern unsigned char *mbis_xml_get_content(GXxmlNodePtr node); 
extern int8_t mbis_xml_get_child_count(GXxmlNodePtr node); 
extern unsigned char *mbis_xml_get_property_str(GXxmlNodePtr node, char *property); 
extern int32_t mbis_xml_get_property_int(GXxmlNodePtr node, char *property); 
extern int32_t mbis_xml_get_property_video(GXxmlNodePtr node, mbis_video_info_t *p_video_para, uint8_t rect_enable); 
extern char* mbis_xml_replace_disk_symbol(const char *old_path, char *new_path); 
extern char *mbis_xml_extract_file_name(const char *str); 
extern char *mbis_xml_extract_file_path(const char *str); 
extern int32_t mbis_xml_set_video_para(mbis_video_info_t *para); 
extern int32_t mbis_xml_get_video_para(mbis_video_info_t *para); 
extern char *mbis_xml_get_full_path(char *src, char *dst); 




extern void mbis_window_del_widget(char *widget_name); 
extern void mbis_window_exit(const char* cur_widget_name, const char* last_focus_widget_name); 


#endif
