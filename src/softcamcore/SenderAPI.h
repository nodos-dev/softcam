#pragma once
#include "SoftcamCommon.h"

namespace softcam {
namespace sender {

using CameraHandle = void*;

CameraHandle    CreateCamera(int width, int height, float framerate = 60.0f, softcamTextureFormat format = SOFTCAM_TEXTURE_FORMAT_UNKNOWN);
void            DeleteCamera(CameraHandle camera);
void            SendFrame(CameraHandle camera, const void* image_bits);
bool            WaitForConnection(CameraHandle camera, float timeout = 0.0f);

} //namespace sender
} //namespace softcam
