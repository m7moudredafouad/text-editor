#pragma once

#include <iostream>
#include <stdlib.h>

#define COLOR_BLACK     "\033[30m"
#define COLOR_RED       "\033[31m"
#define COLOR_GREEN     "\033[32m"
#define COLOR_YELLOW    "\033[33m"
#define COLOR_BLUE      "\033[34m"
#define COLOR_Magenta   "\033[35m"
#define COLOR_CYAN      "\033[36m"
#define COLOR_WHITE     "\033[37m"

#define COLOR_B_BLACK    "\033[90m"
#define COLOR_B_RED      "\033[91m"
#define COLOR_B_GREEN    "\033[92m"
#define COLOR_B_YELLOW   "\033[93m"
#define COLOR_B_BLUE     "\033[94m"
#define COLOR_B_MAGENTA  "\033[95m"
#define COLOR_B_CYAN     "\033[96m"
#define COLOR_B_WHITE    "\033[97m"

#define WRITE_ERROR_MSG(MSG)\
        std::cerr << COLOR_B_RED << "ERROR::" << __FILE__ << ":" << __LINE__;\
        std::cerr << "\n\t" << COLOR_B_CYAN << MSG << COLOR_B_WHITE <<std::endl;

#define EXIT_FAILUR(MSG)\
        WRITE_ERROR_MSG(MSG);\
        exit(EXIT_FAILURE);

#define ASSERT(COND, MSG)\
        if((COND) == 0) {\
                WRITE_ERROR_MSG(MSG);\
                std::cerr << COLOR_B_CYAN << "\t" << #COND << COLOR_B_WHITE << std::endl;\
                exit(EXIT_FAILURE);\
        }

#define ASSERT_CB(COND, CB, MSG)\
        if(!(COND)) {\
                WRITE_ERROR_MSG(MSG);\
                std::cerr << COLOR_B_CYAN << "\t" << #COND << COLOR_B_WHITE << std::endl;\
                CB;\
                exit(EXIT_FAILURE);\
        }



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
