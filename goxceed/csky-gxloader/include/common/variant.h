#ifndef _VARIANT_H_
#define _VARIANT_H_

#include <stdint.h>
#include <stdarg.h>

__BEGIN_DECLS
enum gx_variant_type {
	GX_UINT		= 0,
	GX_INT		= 1,
	GX_UINT8	= 2,
	GX_SINT8	= 3,
	GX_UINT16	= 4,
	GX_SINT16	= 5,
	GX_UINT32	= 6,
	GX_SINT32	= 7,
	GX_UINT64	= 8,	/* MD */
	GX_SINT64	= 9,	/* MD */
	GX_FLOAT	= 10,
	GX_DOUBLE	= 11,
	GX_LONG_DOUBLE	= 12,	/* MD */
	GX_STRING	= 13,
	GX_POINTER	= 14,
	GX_BOOL		= 15,
	
	/*
	 * Application extensions
	 */
	GX_PRIVATE		= 10001,
};

typedef struct gx_variant{
	enum gx_variant_type type;

	union {
		unsigned int u;
		int          i;
		uint8_t      u8;
		int8_t       s8;
		uint16_t     u16;
		int16_t      s16;
		uint32_t     u32;
		int32_t      s32;
#ifdef HAVE_64BIT
		uint64_t     u64;
		int64_t      s64;
#else
		int32_t      u64[4];	/* Padding */
#endif	
		float        f;
		double	     d;
		char	     *s;
		void	     *p;
#ifdef HAVE_LONG_DOUBLE
		long double  ld;		/* Keep at end of struct (padding) */
#endif
	}data;
}GxVariant;

#define GX_PROPERTY_NAME_MAX 32
typedef struct gx_prop{
	char       key[GX_PROPERTY_NAME_MAX];
	GxVariant  value;
}GxProp;


GxVariant *GxSetVariantV(GxVariant * var, enum gx_variant_type type, va_list ap);
GxVariant *GxSetVariant(GxVariant *var, enum gx_variant_type type, ...);
void FreeVariant(void *p);

#define GxSetUint(var, i)        GxSetVariant((var), GX_UINT        , (i))
#define GxSetInt(var, i)         GxSetVariant((var), GX_INT         , (i))
#define GxSetUint8(var, i)       GxSetVariant((var), GX_UINT8       , (i))
#define GxSetSint8(var, i)       GxSetVariant((var), GX_SINT8       , (i))
#define GxSetUint16(var, i)      GxSetVariant((var), GX_UINT16      , (i))
#define GxSetSint16(var, i)      GxSetVariant((var), GX_SINT16      , (i))
#define GxSetUint32(var, i)      GxSetVariant((var), GX_UINT32      , (i))
#define GxSetSint32(var, i)      GxSetVariant((var), GX_SINT32      , (i))
#define GxSetUint64(var, i)      GxSetVariant((var), GX_UINT64      , (i))
#define GxSetSint64(var, i)      GxSetVariant((var), GX_SINT64      , (i))
#define GxSetFloat(var, i)       GxSetVariant((var), GX_FLOAT       , (i))
#define GxSetDouble(var, i)      GxSetVariant((var), GX_DOUBLE      , (i))
#define GxSetLongDouble(var, i)  GxSetVariant((var), GX_LONG_DOUBLE , (i))
#define GxSetString(var, i)      GxSetVariant((var), GX_STRING      , (i))
#define GxSetPointer(var, i)     GxSetVariant((var), GX_POINTER     , (i))
#define GxSetBool(var, i)        GxSetVariant((var), GX_BOOL        , (i))


#define GxGetUint(var)       ((var)->data.u   )
#define GxGetInt(var)        ((var)->data.i   )
#define GxGetUint8(var)      ((var)->data.u8  )
#define GxGetSint8(var)      ((var)->data.s8  )
#define GxGetUint16(var)     ((var)->data.u16 )
#define GxGetSint16(var)     ((var)->data.s16 )
#define GxGetUint32(var)     ((var)->data.u32 )
#define GxGetSint32(var)     ((var)->data.s32 )
#define GxGetUint64(var)     ((var)->data.u64 )
#define GxGetSint64(var)     ((var)->data.s64 )
#define GxGetFloat(var)      ((var)->data.f   )
#define GxGetDouble(var)     ((var)->data.d   )
#define GxGetLongDouble(var) ((var)->data.ld  )
#define GxGetString(var)     ((var)->data.s   )
#define GxGetPointer(var)    ((var)->data.p   )
#define GxGetBool(var)       ((var)->data.i   )

__END_DECLS

#endif

