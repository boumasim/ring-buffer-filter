#include "RingBufferFilter.h"
#include "envoy/envoy/registry/registry.h"
#include "envoy/envoy/server/filter_config.h"
#include "envoy/source/common/protobuf/protobuf.h"
#include "envoy/envoy/http/filter_factory.h"
#include "envoy/envoy/server/factory_context.h"
#include "envoy/source/common/protobuf/utility.h"

#include "ring_buffer_filter.pb.h"
#include "ring_buffer_filter.pb.validate.h"

namespace Envoy {
  namespace Server {
    namespace Configuration {

      class RingBufferFilterConfigFactory : public NamedHttpFilterConfigFactory {
      public:
        Http::FilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                           const std::string&,
                                                           FactoryContext& context) override {

          return createFilter(Envoy::MessageUtil::downcastAndValidate<const ring_filter::Config&>(
                                  proto_config, context.messageValidationVisitor()),
                              context);
        }

        /**
         *  Return the Protobuf Message that represents your config incase you have config proto
         */
        ProtobufTypes::MessagePtr createEmptyConfigProto() override {
          return ProtobufTypes::MessagePtr{new ring_filter::Config()};
        }

        std::string name() const override { return "ring_filter"; }

      private:
        Http::FilterFactoryCb createFilter(const ring_filter::Config& proto_config, FactoryContext&) {
          Http::RingBufferFilterConfigSharedPtr config =
              std::make_shared<Http::RingBufferFilterConfig>(proto_config)>(
                  Http::RingBufferFilterConfig(proto_config));

          return [config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
            auto filter = new Http::RingBufferFilter(config);
            callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{filter});
          };
        }
      };

      /**
       * Static registration for this sample filter. @see RegisterFactory.
       */
      static Registry::RegisterFactory<RingBufferFilterConfigFactory, NamedHttpFilterConfigFactory>
          register_;

    } // namespace Configuration
  } // namespace Server
} // namespace Envoy