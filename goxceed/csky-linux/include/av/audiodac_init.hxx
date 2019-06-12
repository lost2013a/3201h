
struct audio_dac; 
extern "C" int register_audiodac(struct audio_dac *dac);

#define DEFINE_AUDIODAC(name)                                               \
	class cyg_audiodac_class_##name {                                   \
		public:                                                     \
			cyg_audiodac_class_##name(void) {                   \
				extern struct audio_dac audiodac_##name; \
				register_audiodac(&audiodac_##name);        \
			}                                                   \
	}

#ifdef ECOS_OS

DEFINE_AUDIODAC( cs4344 );
DEFINE_AUDIODAC( pt8211 );
DEFINE_AUDIODAC( pt8234 );
DEFINE_AUDIODAC( cs4334 );
DEFINE_AUDIODAC( cs4345 );

#else


#endif
