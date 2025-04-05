package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
)

load("@envoy_api//bazel:api_build_system.bzl", "api_proto_package")

api_proto_package()

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":RingBufferFilterConfig_lib",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)

envoy_cc_library(
    name = "RingBufferFilter_lib",
    hdrs = ["RingBufferFilter.h"],
    srcs = ["RingBufferFilter.cc"],
    repository = "@envoy",
    deps = [
        ":pkg_cc_proto",
        "@envoy//envoy/http:header_map_interface",
        "@envoy//envoy/http:filter_interface",
        "@envoy//envoy/buffer:buffer_interface",
        "@envoy//envoy/http:metadata_interface",
    ]
)

envoy_cc_library(
    name = "RingBufferFilterConfig_lib",
    srcs = ["RingBufferFilterConfig.cc"],
    repository = "@envoy",
    deps = [
        ":RingBufferFilter_lib",
        "@envoy//envoy/registry:registry",
        "@envoy//envoy/server:filter_config_interface",
        "@envoy//source/common/protobuf:protobuf",
        "@envoy//envoy/server:factory_context_interface",
        "@envoy//envoy/http:filter_factory_interface",
        "@envoy//source/common/protobuf:utility_lib_header",
        "@envoy//source/common/http:http3_status_tracker_impl_lib",
    ]
)
