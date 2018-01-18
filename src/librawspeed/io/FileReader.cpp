/*
    RawSpeed - RAW file decoder.

    Copyright (C) 2009-2014 Klaus Post

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "io/FileReader.h"
#include "io/Buffer.h"          // for Buffer
#include "io/FileIOException.h" // for FileIOException
#include <cstdio>               // for fclose, fseek, fopen, fread, ftell
#include <fcntl.h>              // for SEEK_END, SEEK_SET

namespace RawSpeed {

Buffer readFile(const char* fn)
{
  std::unique_ptr<FILE, decltype(&fclose)> file(fopen(fn, "rb"), &fclose);
  if (!file)
    ThrowFIE("Could not open file.");

  fseek(file.get(), 0, SEEK_END);
  long size = ftell(file.get());
  if (size <= 0)
    ThrowFIE("File is empty or has unknown size.");

  fseek(file.get(), 0, SEEK_SET);

  Buffer data(size);

  size_t bytes_read = fread((char *)data.getDataWrt(0, size), 1, size, file.get());
  if ((size_t)size != bytes_read)
    ThrowFIE("Could not read file.");

  return data;
}

} // namespace RawSpeed
