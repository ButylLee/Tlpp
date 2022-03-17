#ifndef TLPP_MACRO_H
#define TLPP_MACRO_H

#define CONCAT_(A, B) A##B
#define CONCAT(A, B)  CONCAT_(A, B)

#define QUOTE_(I)  #I
#define QUOTE(I)   QUOTE_(I)
#define QUOTE_L(I) CONCAT(L, QUOTE_(I))

#define WIDEN(S) CONCAT(L, S)

#endif // TLPP_MACRO_H