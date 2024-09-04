#ifndef RESULT_H
#define RESULT_H

enum result
{
    SUCCESS        = 0,
    EOF_FOUND      = 1,
    FILE_READ_ER   = 2,
    FILE_NOT_FOUND = 3,
    NULL_POINTER   = 4,
    UNKNOWN_ERROR  = 5
};

enum yes_no
{
    NO  = 0,
    YES = 1
};

enum compareResult
{
    SECOND_BIGGER = -1,
    EQUAL         =  0,
    FIRST_BIGGER  =  1
};

#endif
