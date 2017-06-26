# Copyright 2017
#   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

lib_LTLIBRARIES = libhappah-graphics.la
libhappah_graphics_la_SOURCES = \
     happah/graphics/Buffer.cpp \
     happah/graphics/DataType.cpp \
     happah/graphics/glad.c \
     happah/graphics/Program.cpp \
     happah/graphics/RenderContext.cpp \
     happah/graphics/Shader.cpp \
     happah/graphics/Uniform.cpp \
     happah/graphics/VertexArray.cpp \
     happah/graphics/Viewport.cpp
nobase_include_HEADERS = \
     happah/graphics.hpp \
     happah/graphics/Buffer.hpp \
     happah/graphics/CheckGLError.hpp \
     happah/graphics/DataType.hpp \
     happah/graphics/glad.h \
     happah/graphics/Program.hpp \
     happah/graphics/RenderContext.hpp \
     happah/graphics/Shader.hpp \
     happah/graphics/Uniform.hpp \
     happah/graphics/VertexArray.hpp \
     happah/graphics/Viewport.hpp
libhappah_graphics_la_CPPFLAGS = -std=c++1y -I/usr/include/eigen3 -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable
libhappah_graphics_la_LDFLAGS = -version-info 0:0:0 -lhappah

