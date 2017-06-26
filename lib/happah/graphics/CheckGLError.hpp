// Copyright 2017
//   Obada Mahdi - Karlsruhe Institute of Technology - omahdi@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#define _happah_CHECK_GL_ERROR_STR__(s) #s
#define _happah_CHECK_GL_ERROR_STR(s) _happah_CHECK_GL_ERROR_STR__(s)
#define _happah_CHECK_GL_ERROR__LINE__ _happah_CHECK_GL_ERROR_STR(__LINE__)

#ifndef HAPPAH_GL_ERROR_PERMISSIVE
#define HAPPAH_GL_ERROR_PERMISSIVE	1
#endif

#if HAPPAH_GL_ERROR_PERMISSIVE
#  define CHECK_GL_ERROR() \
     do { \
          auto err = glGetError(); \
          if (err != GL_NO_ERROR) \
               std::cerr << "GL error at " << __FILE__ << ":" << _happah_CHECK_GL_ERROR__LINE__ << ": (" << err << ")\n"; \
     } while (false)
#else
#  define CHECK_GL_ERROR() assert(glGetError() == GL_NO_ERROR)
#endif
