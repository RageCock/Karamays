#ifndef GL_TRANSFORM_FEEDBACK_BUFFER_H
#define GL_TRANSFORM_FEEDBACK_BUFFER_H

#include "graphics/buffers/buffer/gl_buffer.h"

// 0xFC807e12026BedD66DD1f6e853fd93beBEA66558
struct gl_transform_feedback_buffer_descriptor{

};


class gl_transform_feedback_buffer {
public:
    gl_transform_feedback_buffer() = delete;
    explicit gl_transform_feedback_buffer(const gl_transform_feedback_buffer_descriptor& descriptor)
    {

        //_buffer = std::make_shared<gl_buffer>();
    }

    ~gl_transform_feedback_buffer() = default;


public:

    void initialize()
    {

    }


private:

    std::unique_ptr<gl_buffer> _buffer;

};


#endif
