/*

    OpenPnp-Capture: a video capture subsystem.

    Linux platform code, MJPEG decoding using libjpeg-turbo

    Created by Niels Moseley on 7/6/17.
    Copyright (c) 2017 Niels Moseley.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

*/

#include "mjpeghelper.h"

#include "contrib/stb_image.h"
#include "../common/logging.h"

bool MJPEGHelper::decompressFrame(
    const uint8_t *inBuffer,
    size_t inBytes, uint8_t *outBuffer,
    uint32_t outBufWidth, uint32_t outBufHeight)
{
    int32_t width, height, jpegSubsamp;
    uint8_t *jpegPtr = stbi_load_from_memory(inBuffer, inBytes, &width, &height, &jpegSubsamp, 3);
    
    if ((width != outBufWidth) || (height != outBufHeight))
    {
        LOG(LOG_ERR, "JPEG load failed");
        stbi_image_free(jpegPtr);
        return false;
    }
    else
    {
        LOG(LOG_VERBOSE, "MJPG: %d %d size %d bytes\n", width, height, inBytes);
    }
    return true;
}