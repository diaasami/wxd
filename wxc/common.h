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
	
	operator wxString ()
	{
#if wxUSE_UNICODE
		return wxString(data, wxConvUTF8, length);
#else
		size_t ignored;
		//This buffer is needed to copy the charbuffer returned by cMB2WC,
		//which would otherwise be lost after the constructor returns
		static wxWCharBuffer buffer;
		// convert the UTF-8 to wide first, and then back to ansi:
		buffer = wxConvUTF8.cMB2WC(data, length, &ignored);
		return wxString(buffer);
#endif
	}
};

// Macro, for compatibility with wx.NET etc
// it converts a wxc_string into a wxString
#define wxstr(str)    wxString(str)

#endif /* _COMMON_H_ */
