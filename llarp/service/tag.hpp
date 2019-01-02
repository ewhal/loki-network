#ifndef LLARP_SERVICE_TAG_HPP
#define LLARP_SERVICE_TAG_HPP

#include <aligned.hpp>
#include <dht/key.hpp>

#include <sodium/crypto_generichash.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

namespace llarp
{
  namespace service
  {
    struct Tag : public llarp::AlignedBuffer< 16 >
    {
      Tag() : llarp::AlignedBuffer< SIZE >()
      {
      }

      Tag(const byte_t* d) : llarp::AlignedBuffer< SIZE >(d)
      {
      }

      Tag(const std::string& str) : Tag()
      {
        // evidently, does nothing on LP64 systems (where size_t is *already*
        // unsigned long but zero-extends this on LLP64 systems
        std::copy(str.begin(), str.begin() + std::min(16UL, str.size()),
                  as_array().begin());
      }

      Tag&
      operator=(const Tag& other)
      {
        as_array() = other.as_array();
        return *this;
      }

      Tag&
      operator=(const std::string& str)
      {
        std::copy(str.begin(), str.begin() + std::min(16UL, str.size()),
                  as_array().begin());
        return *this;
      }

      std::string
      ToString() const;

      bool
      Empty() const
      {
        return ToString().empty();
      }

      using Hash = AlignedBuffer< SIZE >::Hash;
    };
  }  // namespace service
}  // namespace llarp

#endif
