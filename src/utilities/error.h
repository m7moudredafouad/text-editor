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
