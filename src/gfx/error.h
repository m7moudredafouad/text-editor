#pragma once

#include <iostream>
#include <stdlib.h>
#include <utilities/error.h>

#define GLCall(x) GLClearError();\
                  x;\
                  ASSERT(GLCheckError(), "[OpenGl Error]");

void inline GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool inline GLCheckError() {
    while (GLenum error = glGetError()){
          switch(error) {
              case GL_INVALID_ENUM :
                WRITE_ERROR_MSG("GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument.");
                  break;
              case GL_INVALID_VALUE :
                WRITE_ERROR_MSG("GL_INVALID_OPERATION : A numeric argument is out of range.");
                  break;
              case GL_INVALID_OPERATION :
                WRITE_ERROR_MSG("GL_INVALID_OPERATION : The specified operation is not allowed in the current state.");
                  break;
              case GL_INVALID_FRAMEBUFFER_OPERATION :
                WRITE_ERROR_MSG("GL_INVALID_FRAMEBUFFER_OPERATION : The framebuffer object is not complete.");
                  break;
              case GL_OUT_OF_MEMORY :
                WRITE_ERROR_MSG("GL_OUT_OF_MEMORY : There is not enough memory left to execute the command.");
                  break;
              case GL_STACK_UNDERFLOW :
                WRITE_ERROR_MSG("GL_STACK_UNDERFLOW : An attempt has been made to perform an operation that would cause an internal stack to underflow.");
                  break;
              case GL_STACK_OVERFLOW :
                WRITE_ERROR_MSG("GL_STACK_OVERFLOW : An attempt has been made to perform an operation that would cause an internal stack to overflow.");
                  break;
              default :
                WRITE_ERROR_MSG( "Unrecognized error" << error);
          }
          return false;
    }
    return true;
}
