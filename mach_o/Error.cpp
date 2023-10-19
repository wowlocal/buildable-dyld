/*
 * Copyright (c) 2017 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <uuid/uuid.h>
#include <errno.h>
#include <TargetConditionals.h>
#if !TARGET_OS_EXCLAVEKIT
  //#include <_simple.h>
#endif // !TARGET_OS_EXCLAVEKIT

#include <mach/machine.h>
#include <mach-o/fat.h>

#include "Error.h"

namespace mach_o {


Error::Error(Error&& other)
{
    _buffer = other._buffer;
    other._buffer = nullptr;
}

Error& Error::operator=(Error&& other)
{
    _buffer = other._buffer;
    other._buffer = nullptr;
    return *this;
}

Error::~Error()
{
#if TARGET_OS_EXCLAVEKIT
    *_strBuf = '\0';
#else
   if ( _buffer )
        //_simple_sfree(_buffer);
    _buffer = nullptr;
#endif
}

Error::Error(const char* format, ...)
{
    va_list    list;
    va_start(list, format);
#if TARGET_OS_EXCLAVEKIT
    vsnprintf(_strBuf, sizeof(_strBuf), format, list);
#else
    //if ( _buffer == nullptr )
        //_buffer = _simple_salloc();
    //_simple_vsprintf(_buffer, format, list);
#endif
    va_end(list);
}

Error::Error(const char* format, va_list list)
{
#if TARGET_OS_EXCLAVEKIT
    vsnprintf(_strBuf, sizeof(_strBuf), format, list);
#else
//    if ( _buffer == nullptr )
//        _buffer = _simple_salloc();
//    _simple_vsprintf(_buffer, format, list);
#endif
}

const char* Error::message() const
{
#if TARGET_OS_EXCLAVEKIT
    return _strBuf;
#else
//    return _buffer ? _simple_string(_buffer) : "";
#endif
}

bool Error::messageContains(const char* subString) const
{
    if ( _buffer == nullptr )
        return false;
#if TARGET_OS_EXCLAVEKIT
    return (strstr(_strBuf, subString) != nullptr);
#else
//    return (strstr(_simple_string(_buffer), subString) != nullptr);
    return false;
#endif
}

} // namespace mach_o
