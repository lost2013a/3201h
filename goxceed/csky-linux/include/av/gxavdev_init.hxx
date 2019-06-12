#ifndef	GXAVDEV_INIT_H
#define	GXAVDEV_INIT_H

extern "C" int gxav_init(char* profile);

class cyg_av_init_class {
public:
   cyg_av_init_class(const char* profile = NULL) 
	{ 
		gxav_init((char*)profile);
	}
};

#endif
