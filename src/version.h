#ifndef _H_VERSION
#define _H_VERSION

#define VERSION_CONFIG 85
#if defined(ANDROID) || defined(_3DS)
#define VERSION_ENTITY 24
#else
#define VERSION_ENTITY 8
#endif
#define VERSION_FILTER 2
#define VERSION_MAPS 27
#if defined(ANDROID)
#define VERSION_MEDIA 59
#elif defined(_3DS)
#define VERSION_MEDIA 58
#else
#define VERSION_MEDIA 26
#endif
#define VERSION_MODELS 36
#define VERSION_SOUNDS 1
#define VERSION_TEXTURES 17

#define ENTITY_IS_TGA(x)     ((x) < 9)
#define MEDIA_IS_TGA(x)      ((x) < 28)

#define HAS_SEPARATE_LAND(x) ((x) > 27)

#endif
