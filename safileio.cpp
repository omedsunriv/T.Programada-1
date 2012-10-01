#include "shapefil.h"

#include <math.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

SHP_CVSID("$Id: safileio.c,v 1.4 2008-01-16 20:05:14 bram Exp $");

#ifdef SHPAPI_UTF8_HOOKS
#   ifdef SHPAPI_WINDOWS
#       define WIN32_LEAN_AND_MEAN
#       define NOMINMAX
#       include <windows.h>
#       pragma comment(lib, "kernel32.lib")
#   endif
#endif

/************************************************************************/
/*                              SADFOpen()                              */
/************************************************************************/

SAFile SADFOpen( const char *pszFilename, const char *pszAccess )

{
    return (SAFile) fopen( pszFilename, pszAccess );
}

/************************************************************************/
/*                              SADFRead()                              */
/************************************************************************/

SAOffset SADFRead( void *p, SAOffset size, SAOffset nmemb, SAFile file )

{
    return (SAOffset) fread( p, (size_t) size, (size_t) nmemb, 
                             (FILE *) file );
}

/************************************************************************/
/*                             SADFWrite()                              */
/************************************************************************/

SAOffset SADFWrite( void *p, SAOffset size, SAOffset nmemb, SAFile file )

{
    return (SAOffset) fwrite( p, (size_t) size, (size_t) nmemb, 
                              (FILE *) file );
}

/************************************************************************/
/*                              SADFSeek()                              */
/************************************************************************/

SAOffset SADFSeek( SAFile file, SAOffset offset, int whence )

{
    return (SAOffset) fseek( (FILE *) file, (long) offset, whence );
}

/************************************************************************/
/*                              SADFTell()                              */
/************************************************************************/

SAOffset SADFTell( SAFile file )

{
    return (SAOffset) ftell( (FILE *) file );
}

/************************************************************************/
/*                             SADFFlush()                              */
/************************************************************************/

int SADFFlush( SAFile file )

{
    return fflush( (FILE *) file );
}

/************************************************************************/
/*                             SADFClose()                              */
/************************************************************************/

int SADFClose( SAFile file )

{
    return fclose( (FILE *) file );
}

/************************************************************************/
/*                             SADFClose()                              */
/************************************************************************/

int SADRemove( const char *filename )

{
    return remove( filename );
}

/************************************************************************/
/*                              SADError()                              */
/************************************************************************/

void SADError( const char *message )

{
    fprintf( stderr, "%s\n", message );
}

/************************************************************************/
/*                        SASetupDefaultHooks()                         */
/************************************************************************/

void SASetupDefaultHooks( SAHooks *psHooks )

{
    psHooks->FOpen   = SADFOpen;
    psHooks->FRead   = SADFRead;
    psHooks->FWrite  = SADFWrite;
    psHooks->FSeek   = SADFSeek;
    psHooks->FTell   = SADFTell;
    psHooks->FFlush  = SADFFlush;
    psHooks->FClose  = SADFClose;
    psHooks->Remove  = SADRemove;

    psHooks->Error   = SADError;
    psHooks->Atof    = atof;
}




#ifdef SHPAPI_WINDOWS

/************************************************************************/
/*                          Utf8ToWideChar                              */
/************************************************************************/

const wchar_t* Utf8ToWideChar( const char *pszFilename )
{
    int nMulti, nWide;
    wchar_t *pwszFileName;
    
    nMulti = strlen(pszFilename) + 1;
    nWide = MultiByteToWideChar( CP_UTF8, 0, pszFilename, nMulti, 0, 0);
    if( nWide == 0 )
    {
        return NULL;
    }
    pwszFileName = (wchar_t*) malloc(nWide * sizeof(wchar_t));
    if ( pwszFileName == NULL )
    {
        return NULL;
    }
    if( MultiByteToWideChar( CP_UTF8, 0, pszFilename, nMulti, pwszFileName, nWide ) == 0 )
    {
        free( pwszFileName );
        return NULL;
    }
    return pwszFileName;
}

/************************************************************************/
/*                           SAUtf8WFOpen                               */
/************************************************************************/

SAFile SAUtf8WFOpen( const char *pszFilename, const char *pszAccess )
{
    SAFile file = NULL;
    const wchar_t *pwszFileName, *pwszAccess;
    pwszFileName = Utf8ToWideChar( pszFilename );
    pwszAccess = Utf8ToWideChar( pszAccess );
    if( pwszFileName != NULL && pwszFileName != NULL)
    {
        file = (SAFile) _wfopen( pwszFileName, pwszAccess );
    }
    free ((wchar_t*) pwszFileName);
    free ((wchar_t*) pwszAccess);
    return file;
}

/************************************************************************/
/*                             SAUtf8WRemove()                          */
/************************************************************************/

int SAUtf8WRemove( const char *pszFilename )
{
    const wchar_t *pwszFileName = Utf8ToWideChar( pszFilename );
    int rc = -1; 
    if( pwszFileName != NULL )
    {
        rc = _wremove( pwszFileName );
    }
    free ((wchar_t*) pwszFileName);
    return rc;
}

#endif

#ifdef SHPAPI_UTF8_HOOKS

/************************************************************************/
/*                          SASetupUtf8Hooks()                          */
/************************************************************************/

void SASetupUtf8Hooks( SAHooks *psHooks )
{
#ifdef SHPAPI_WINDOWS    
    psHooks->FOpen   = SAUtf8WFOpen;
    psHooks->Remove  = SAUtf8WRemove;
#else
#   error "no implementations of UTF-8 hooks available for this platform"
#endif
    psHooks->FRead   = SADFRead;
    psHooks->FWrite  = SADFWrite;
    psHooks->FSeek   = SADFSeek;
    psHooks->FTell   = SADFTell;
    psHooks->FFlush  = SADFFlush;
    psHooks->FClose  = SADFClose;

    psHooks->Error   = SADError;
    psHooks->Atof    = atof;
}

#endif
