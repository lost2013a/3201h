#ifndef __GDI_PLAY_H__
#define __GDI_PLAY_H__

#include <time.h>
#include <limits.h>
#include "gxcore.h"

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

#define MAX_COMMENT_SIZE 2000

#define MAX_DATE_COPIES 10

__BEGIN_DECLS

typedef enum _IMG_TYPE{
	IMAGE_BMP,
	IMAGE_JPG,
	IMAGE_GIF,
	IMAGE_PNG,
	IMAGE_TIFF,
	IMAGE_MPEG
} IMG_TYPE;

//--------------------------------------------------------------------------
// This structure stores Exif header image elements in a simple manner
// Used to store camera data as extracted from the various ways that it can be
// stored in an exif header
typedef struct {
	char  FileName[PATH_MAX+1];
	time_t FileDateTime;

	struct {
		// Info in the jfif header.
		// This info is not used much - jhead used to just replace it with default
		// values, and over 10 years, only two people pointed this out.
		char  Present;
		char  ResolutionUnits;
		short XDensity;
		short YDensity;
	} JfifHeader;

	unsigned int FileSize;
	char  CameraMake   [32];
	char  CameraModel  [40];
	char  DateTime     [20];
	int   Height, Width;
	int   Orientation;
	int   IsColor;
	int   Process;
	int   FlashUsed;
	float FocalLength;
	float ExposureTime;
	float ApertureFNumber;
	float Distance;
	float CCDWidth;
	float ExposureBias;
	float DigitalZoomRatio;
	int   FocalLength35mmEquiv; // Exif 2.2 tag - usually not present.
	int   Whitebalance;
	int   MeteringMode;
	int   ExposureProgram;
	int   ExposureMode;
	int   ISOequivalent;
	int   LightSource;
	int   DistanceRange;

	float xResolution;
	float yResolution;
	int   ResolutionUnit;

	char  Comments[MAX_COMMENT_SIZE];
	int   CommentWidthchars; // If nonzero, widechar comment, indicates number of chars.

	unsigned ThumbnailOffset;          // Exif offset to thumbnail
	unsigned ThumbnailSize;            // Size of thumbnail.
	unsigned LargestExifOffset;        // Last exif data referenced (to check if thumbnail is at end)

	char  ThumbnailAtEnd;              // Exif header ends with the thumbnail
	// (we can only modify the thumbnail if its at the end)
	int   ThumbnailSizeOffset;

	int  DateTimeOffsets[MAX_DATE_COPIES];
	int  numDateTimeTags;

	int GpsInfoPresent;
	char GpsLat[31];
	char GpsLong[31];
	char GpsAlt[20];
} ImageInfo_t;

typedef struct _Image_Exif {
	int width;
	int height;
	int horizontal_pixel;
	int vertical_pixel;
	int bpp;
	int frame_num;
	IMG_TYPE type;
	ImageInfo_t image_ext_info;
} Image_Exif;

int IMG_scale(int width, int height);
int GDI_PlayImage(const char *pFile, int screen_width, int screen_height);
int GDI_PlayImage_Cordinate(const char *pFile, unsigned int x, unsigned int y);
int GDI_StopImage(const char *pFile);
int GDI_ImageInformation(const char *pFile, Image_Exif *img_info);
int GDI_Load_Image(const char *path,
		unsigned int *width,
		unsigned int *height,
		unsigned char *bpp,
		unsigned char **data);
int GDI_DecodeImage(const char *path,
		unsigned int index, //多帧图像的第Ｎ帧 
		unsigned int width,
		unsigned int height,
		unsigned int pitch,
		GxColorFormat colortype,
		unsigned char *data);

void *hd_get_clut(void);

__END_DECLS

#endif

