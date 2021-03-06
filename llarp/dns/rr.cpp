#include <dns/rr.hpp>
#include <logger.hpp>

namespace llarp
{
  namespace dns
  {
    ResourceRecord::ResourceRecord(const ResourceRecord& other)
        : rr_name(other.rr_name)
        , rr_type(other.rr_type)
        , rr_class(other.rr_class)
        , ttl(other.ttl)
        , rData(other.rData)
    {
    }

    ResourceRecord::ResourceRecord(ResourceRecord&& other)
        : rr_name(std::move(other.rr_name))
        , rr_type(std::move(other.rr_type))
        , rr_class(std::move(other.rr_class))
        , ttl(std::move(other.ttl))
        , rData(std::move(other.rData))
    {
    }

    bool
    ResourceRecord::Encode(llarp_buffer_t* buf) const
    {
      if(!EncodeName(buf, rr_name))
      {
        return false;
      }
      if(!llarp_buffer_put_uint16(buf, rr_type))
      {
        return false;
      }
      if(!llarp_buffer_put_uint16(buf, rr_class))
      {
        return false;
      }
      if(!llarp_buffer_put_uint32(buf, ttl))
      {
        return false;
      }
      if(!EncodeRData(buf, rData))
      {
        return false;
      }
      return true;
    }

    bool
    ResourceRecord::Decode(llarp_buffer_t* buf)
    {
      if(!DecodeName(buf, rr_name))
      {
        llarp::LogError("failed to decode rr name");
        return false;
      }
      if(!llarp_buffer_read_uint16(buf, &rr_type))
      {
        llarp::LogError("failed to decode rr type");
        return false;
      }
      if(!llarp_buffer_read_uint16(buf, &rr_class))
      {
        llarp::LogError("failed to decode rr class");
        return false;
      }
      if(!llarp_buffer_read_uint32(buf, &ttl))
      {
        llarp::LogError("failed to decode ttl");
        return false;
      }
      if(!DecodeRData(buf, rData))
      {
        llarp::LogError("failed to decode rr rdata");
        return false;
      }
      return true;
    }
  }  // namespace dns
}  // namespace llarp
