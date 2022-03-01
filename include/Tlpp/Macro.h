#ifndef TLPP_MACRO_H
#define TLPP_MACRO_H

#define CONCAT_(A, B) A##B
#define CONCAT(A, B)  CONCAT_(A, B)

#define QUOTE(I)   #I
#define QUOTE_L(I) L## #I

#endif // TLPP_MACRO_H