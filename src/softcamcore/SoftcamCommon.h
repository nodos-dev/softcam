#pragma once

extern "C" typedef enum softcamTextureFormat {
	SOFTCAM_TEXTURE_FORMAT_UNKNOWN = 0,
	SOFTCAM_TEXTURE_FORMAT_RGB24 = 1,
	SOFTCAM_TEXTURE_FORMAT_YUY2 = 2,
	SOFTCAM_TEXTURE_FORMAT_NV12 = 3
} softcamTextureFormat;