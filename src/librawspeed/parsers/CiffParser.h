/*
    RawSpeed - RAW file decoder.

    Copyright (C) 2009-2014 Klaus Post
    Copyright (C) 2014 Pedro Côrte-Real

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

#pragma once

#include "io/FileMap.h" // for FileMap

namespace RawSpeed {

class CiffIFD;

class RawDecoder;

class CiffParser final {
public:
  CiffParser(FileMap* input);
  ~CiffParser();

  void parseData();
  RawDecoder* getDecoder();
  /* Returns the Root IFD - this object still retains ownership */
  CiffIFD* RootIFD() const { return mRootIFD; }
  /* Merges root of other CIFF into this - clears the root of the other */
  void MergeIFD(CiffParser* other_ciff);
protected:
  FileMap *mInput;
  CiffIFD* mRootIFD;
};

} // namespace RawSpeed
