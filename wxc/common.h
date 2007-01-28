#ifndef _COMMON_H_
#define _COMMON_H_

#include <string.h>

#include <wx/string.h>


// Can't use "bool", since the size varies...
typedef char            wxc_bool;   // D bool

// This is a char[] array, aliased "string"
typedef struct dstr     wxc_string; // D string

// This is something inherited from "Object"
typedef void*           wxc_object; // D object


/// length-prefixed string in UTF-8 format
struct dstr {
	size_t          length;
	const char*     data;

	dstr(const char* str, size_t len) {
		data = str;
		length = len;
	}

	dstr(const char* str) {
		data = str;
		length = strlen(data);
	}
	
	inline const wchar_t* wc_str()
	{ 
		size_t widelen;
		return wxConvUTF8.cMB2WC(data, length, &widelen);
	}

	operator wxString ()
	{
#if wxUSE_UNICODE
		return wxString(data, wxConvUTF8, length);
#else
		return wxString(wc_str());
#endif
	}
};

#if wxUSE_UNICODE
#define wxstr(str)    wxString(str.data, wxConvUTF8, str.length)
#else
#define wxstr(str)    wxString(str.wc_str())
#endif

#endif /* _COMMON_H_ */
