
#ifndef __GXPLAYER_SUBTITLE_H__
#define __GXPLAYER_SUBTITLE_H__

#define PLAYER_MAX_SUB_LINE                     (12)

typedef enum {
	PLAYER_SUB_ENC_UTF8     ,
	PLAYER_SUB_ENC_ANSI     ,
	PLAYER_SUB_ENC_UCS      ,
	PLAYER_SUB_ENC_SPU
}PlayerSubEncode;

typedef struct player_sub_text_page {
	int32_t                 lines;
	PlayerSubEncode         encode;
	uint32_t                 start;
	uint32_t                 end;
	char*                   text[PLAYER_MAX_SUB_LINE];

	struct player_sub_text_page*  next;
}PlayerSubTextPage;

typedef struct player_sub_spu_packet {
	unsigned char *packet;
	unsigned int palette[4];
	unsigned int alpha[4];
	unsigned int control_start;	/* index of start of control data */
	unsigned int current_nibble[2]; /* next data nibble (4 bits) to be
									   processed (for RLE decoding) for
									   even and odd lines */
	int deinterlace_oddness;	/* 0 or 1, index into current_nibble */
	unsigned int start_col, end_col;
	unsigned int start_row, end_row;
	unsigned int width, height, stride;
	unsigned int start_pts, end_pts;
	struct player_sub_spu_packet *next;
}PlayerSubSpuPacket;

typedef struct {
	PlayerSubSpuPacket *queue_head;
	PlayerSubSpuPacket *queue_tail;
	unsigned int global_palette[16];
	unsigned int orig_frame_width, orig_frame_height;
	unsigned char* packet;
	size_t packet_reserve;	/* size of the memory pointed to by packet */
	unsigned int packet_offset;	/* end of the currently assembled fragment */
	unsigned int packet_size;	/* size of the packet once all fragments are assembled */
	int packet_pts;		/* PTS for this packet */
	unsigned int palette[4];
	unsigned int alpha[4];
	unsigned int cuspal[4];
	unsigned int custom;
	unsigned int now_pts;
	unsigned int start_pts, end_pts;
	unsigned int start_col, end_col;
	unsigned int start_row, end_row;
	unsigned int width, height, stride;
	size_t image_size;		/* Size of the image buffer */
	unsigned char *image;		/* Grayscale value */
	unsigned char *aimage;	/* Alpha value */
	unsigned int scaled_frame_width, scaled_frame_height;
	unsigned int scaled_start_col, scaled_start_row;
	unsigned int scaled_width, scaled_height, scaled_stride;
	size_t scaled_image_size;
	unsigned char *scaled_image;
	unsigned char *scaled_aimage;
	int auto_palette; /* 1 if we lack a palette and must use an heuristic. */
	int font_start_level;  /* Darkest value used for the computed font */
	//  const vo_functions_t *hw_spu;
	int spu_changed;
	unsigned int forced_subs_only;     /* flag: 0=display all subtitle, !0 display only forced subtitles */
	unsigned int is_forced_sub;         /* true if current subtitle is a forced subtitle */
} PlayerSubSpuPage;

#endif
