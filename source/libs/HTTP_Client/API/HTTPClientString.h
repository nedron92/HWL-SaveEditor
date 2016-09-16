
#ifndef _HTTP_CLIENT_STRING
#define _HTTP_CLIENT_STRING

#include "HTTPClientWrapper.h" // Cross platform support
#include "HTTPClient.h" 

///////////////////////////////////////////////////////////////////////////////
//
// Section      : HTTP Api global definitions
// Last updated : 01/09/2005
//
///////////////////////////////////////////////////////////////////////////////

BOOL                    HTTPStrInsensitiveCompare   (CHAR *pSrc, CHAR* pDest, long unsigned int nLength);
BOOL                    HTTPStrSearch               (CHAR *pSrc, CHAR *pSearched, long unsigned int nOffset, long unsigned int nScope,HTTP_PARAM *HttpParam);
CHAR                    HTTPStrExtract              (CHAR *pParam,long unsigned int nOffset,CHAR Restore);
CHAR*                   HTTPStrCaseStr              (CHAR *pSrc, long unsigned int nSrcLength, CHAR *pFind); 
CHAR*                   HTTPStrGetToken             (CHAR *pSrc, long unsigned int nSrcLength, CHAR *pDest, long unsigned int *nDestLength);
long unsigned int                  HTTPStrGetDigestToken       (HTTP_PARAM pParamSrc, CHAR *pSearched, HTTP_PARAM *pParamDest);
long unsigned int                  HTTPStrHToL                 (CHAR * s); 
CHAR*                   HTTPStrLToH                 (CHAR * dest,long unsigned int nSrc);        
#endif
