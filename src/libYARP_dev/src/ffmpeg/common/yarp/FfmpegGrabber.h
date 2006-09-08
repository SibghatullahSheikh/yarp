// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef FfmpegGrabber_INC
#define FfmpegGrabber_INC

#include <ffmpeg/avcodec.h>
#include <ffmpeg/avformat.h>

/*
 * A Yarp 2 frame grabber device driver using ffmpeg to implement
 * image capture from AVI files.
 *
 */

namespace yarp {
    namespace dev {
        class FfmpegGrabber;
    }
}

#include <yarp/dev/AudioVisualInterfaces.h>
#include <yarp/dev/DeviceDriver.h>

/**
 * @ingroup dev_impl
 *
 * An image frame grabber device using ffmpeg to capture images from
 * AVI files.
 */
class yarp::dev::FfmpegGrabber : public IFrameGrabberImage, 
            public IAudioVisualGrabber,
            public DeviceDriver
{
public:

    FfmpegGrabber() {
        m_h = m_w = 0;
        pFormatCtx = NULL;
        packet.data = NULL;
        active = false;
    }
  
    virtual bool open(yarp::os::Searchable & config);
  
    virtual bool close();
  
    virtual bool getImage(yarp::sig::ImageOf<yarp::sig::PixelRgb> & image);

    virtual int height() const { return m_h; }
  
    virtual int width() const { return m_w; }
  
    virtual bool getAudioVisual(yarp::sig::ImageOf<yarp::sig::PixelRgb>& image,
                                yarp::sig::Sound& sound);
  

protected:

    AVFormatContext *pFormatCtx;
    AVPacket packet;
    bool active;
  
    /** Width of the images a grabber produces. */
    int m_w;
    /** Height of the images a grabber produces. */
    int m_h;
  
    /** Opaque ffmpeg structure for image capture. */
    void * m_capture;

};


/**
 * @ingroup dev_runtime
 * \defgroup cmd_device_ffmpeg ffmpeg_grabber

 A wrapper for the ffmpeg library's image sources, see yarp::dev::FfmpegGrabber.

*/


#endif

