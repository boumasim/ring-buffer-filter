#pragma once

// #include "envoy/envoy/http/filter.h"
// #include "envoy/envoy/http/header_map.h"
// #include "envoy/envoy/buffer/buffer.h"
// #include "envoy/envoy/http/metadata_interface.h"

#include "envoy/http/filter.h"
#include "envoy/http/header_map.h"
#include "envoy/buffer/buffer.h"
#include "envoy/http/metadata_interface.h"

#include "ring_buffer_filter.pb.h"

namespace Envoy {
namespace Http{

class RingBufferFilterConfig {
public:
  RingBufferFilterConfig(const ring::filter::Config& )  ;
private:
};

using RingBufferFilterConfigSharedPtr = std::shared_ptr<RingBufferFilterConfig>;

class RingBufferFilter : public StreamFilter {
public:
  RingBufferFilter() = default;
  RingBufferFilter(const RingBufferFilterConfigSharedPtr& config);
  ~RingBufferFilter() override;

  void onDestroy() override;

  FilterHeadersStatus decodeHeaders(Http::RequestHeaderMap& request_headers, bool end_stream) override;
  FilterDataStatus decodeData(Buffer::Instance& data, bool end_stream) override;
  FilterTrailersStatus decodeTrailers(Http::RequestTrailerMap& request_headers) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks&) override;

  FilterHeadersStatus encodeHeaders(Http::ResponseHeaderMap& response_headers, bool end_stream) override;
  FilterDataStatus encodeData(Buffer::Instance& data, bool end_stream) override;
  FilterTrailersStatus encodeTrailers(Http::ResponseTrailerMap& response_headers) override;
  void setEncoderFilterCallbacks(StreamEncoderFilterCallbacks&) override;

  Filter1xxHeadersStatus encode1xxHeaders(ResponseHeaderMap&) override;
  FilterMetadataStatus encodeMetadata(MetadataMap&) override;

private:
  const RingBufferFilterConfigSharedPtr config_;
  StreamDecoderFilterCallbacks* decoder_callbacks_;
  StreamEncoderFilterCallbacks* encoder_callbacks_;
};

}
}
