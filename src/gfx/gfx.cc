#include "./gfx.h"

size_t sizeofGlType(uint32_t type) {
    switch (type)
    {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
        return sizeof(uint8_t);
    
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
        return sizeof(uint16_t);
    
    case GL_INT:
    case GL_UNSIGNED_INT:
        return sizeof(uint32_t);
    
    case GL_FLOAT:
        return sizeof(float);

    }
    ASSERT(false, "Provided type is wrong");
    return 0;
}
