#include "RingBufferFilter.h"

#include <string>

namespace Envoy{
namespace Http{

RingBufferFilterConfig::RingBufferFilterConfig(const ring::filter::Config&){};

RingBufferFilter::RingBufferFilter(const RingBufferFilterConfigSharedPtr& config) : config_(config) {};

RingBufferFilter::~RingBufferFilter() = default;

void RingBufferFilter::onDestroy(){};

FilterHeadersStatus RingBufferFilter::decodeHeaders(RequestHeaderMap& , bool ){
  return FilterHeadersStatus::Continue;
};

FilterDataStatus RingBufferFilter::decodeData(Buffer::Instance& , bool ){
  return FilterDataStatus::Continue;
}

FilterTrailersStatus RingBufferFilter::decodeTrailers(RequestTrailerMap& ){
  return FilterTrailersStatus::Continue;
}

void RingBufferFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

FilterHeadersStatus RingBufferFilter::encodeHeaders(ResponseHeaderMap& , bool ){
  return FilterHeadersStatus::Continue;
}

FilterDataStatus RingBufferFilter::encodeData(Buffer::Instance& , bool ){
  return FilterDataStatus::Continue;
}

FilterTrailersStatus RingBufferFilter::encodeTrailers(ResponseTrailerMap& ){
  return FilterTrailersStatus::Continue;
}

void RingBufferFilter::setEncoderFilterCallbacks(StreamEncoderFilterCallbacks& callbacks) {
  encoder_callbacks_ = &callbacks;
}

Filter1xxHeadersStatus RingBufferFilter::encode1xxHeaders(ResponseHeaderMap&) {
  return Filter1xxHeadersStatus::Continue;
}

FilterMetadataStatus RingBufferFilter::encodeMetadata(MetadataMap&) {
  return FilterMetadataStatus::Continue;
}

}
}