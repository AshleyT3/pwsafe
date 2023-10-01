/*
* Copyright (c) 2013-2023 Rony Shapiro <ronys@pwsafe.org>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/
// RFC3548_Base32Decoder.h
//-----------------------------------------------------------------------------
#ifndef __RFC3548_BASE32DECODER_H
#define __RFC3548_BASE32DECODER_H

#include <vector>

#include "../Util.h"
#include "./external/Chromium/base32.h"

class RFC3548_Base32Decoder
{
public:
  static const size_t BITS_PER_BASE32_CHAR = 5;
  static const size_t BITS_PER_BYTE = 8;
public:

  RFC3548_Base32Decoder(const char* base32_encoded_key)
  {
    decoded_bytes.resize((strlen(base32_encoded_key) * BITS_PER_BASE32_CHAR) / BITS_PER_BYTE);
    is_successful = base32_decode(&decoded_bytes[0], static_cast<int>(decoded_bytes.size()) * BITS_PER_BYTE, base32_encoded_key, 0);
    if (!is_successful)
      clear();
  }

  RFC3548_Base32Decoder(const RFC3548_Base32Decoder& other) {
    *this = other;
  }

  RFC3548_Base32Decoder(RFC3548_Base32Decoder&& other) noexcept {
    *this = std::move(other);
  }

  RFC3548_Base32Decoder& operator=(const RFC3548_Base32Decoder& other) {
    clear();
    is_successful = other.is_successful;
    decoded_bytes = other.decoded_bytes;
    return *this;
  }

  RFC3548_Base32Decoder& operator=(RFC3548_Base32Decoder&& other) noexcept {
    clear();
    is_successful = other.is_successful;
    decoded_bytes = std::move(other.decoded_bytes);
    other.is_successful = false;
    return *this;
  }

  virtual ~RFC3548_Base32Decoder() {
    clear();
  }

  bool is_decoding_successful() const { return is_successful;  }

  void clear() {
    if (!decoded_bytes.empty())
      trashMemory(&decoded_bytes[0], decoded_bytes.size());
    decoded_bytes.clear();
  }

  size_t get_size() const {
    return decoded_bytes.size();
  }

  const unsigned char* get_ptr() const {
    return decoded_bytes.empty() ? nullptr : & decoded_bytes[0];
  }

  const std::vector<uint8_t>& get_bytes() const {
    return decoded_bytes;
  }

private:
  bool is_successful;
  std::vector<uint8_t> decoded_bytes;
};


#endif /* __RFC3548_BASE32DECODER_H */
//-----------------------------------------------------------------------------
// Local variables:
// mode: c++
// End:
