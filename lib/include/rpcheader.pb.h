// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rpcheader.proto

#ifndef PROTOBUF_INCLUDED_rpcheader_2eproto
#define PROTOBUF_INCLUDED_rpcheader_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_rpcheader_2eproto 

namespace protobuf_rpcheader_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_rpcheader_2eproto
namespace mprpc {
class rpcheader;
class rpcheaderDefaultTypeInternal;
extern rpcheaderDefaultTypeInternal _rpcheader_default_instance_;
}  // namespace mprpc
namespace google {
namespace protobuf {
template<> ::mprpc::rpcheader* Arena::CreateMaybeMessage<::mprpc::rpcheader>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace mprpc {

// ===================================================================

class rpcheader : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:mprpc.rpcheader) */ {
 public:
  rpcheader();
  virtual ~rpcheader();

  rpcheader(const rpcheader& from);

  inline rpcheader& operator=(const rpcheader& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  rpcheader(rpcheader&& from) noexcept
    : rpcheader() {
    *this = ::std::move(from);
  }

  inline rpcheader& operator=(rpcheader&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const rpcheader& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const rpcheader* internal_default_instance() {
    return reinterpret_cast<const rpcheader*>(
               &_rpcheader_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(rpcheader* other);
  friend void swap(rpcheader& a, rpcheader& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline rpcheader* New() const final {
    return CreateMaybeMessage<rpcheader>(NULL);
  }

  rpcheader* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<rpcheader>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const rpcheader& from);
  void MergeFrom(const rpcheader& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(rpcheader* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes servicename = 1;
  void clear_servicename();
  static const int kServicenameFieldNumber = 1;
  const ::std::string& servicename() const;
  void set_servicename(const ::std::string& value);
  #if LANG_CXX11
  void set_servicename(::std::string&& value);
  #endif
  void set_servicename(const char* value);
  void set_servicename(const void* value, size_t size);
  ::std::string* mutable_servicename();
  ::std::string* release_servicename();
  void set_allocated_servicename(::std::string* servicename);

  // bytes methodname = 2;
  void clear_methodname();
  static const int kMethodnameFieldNumber = 2;
  const ::std::string& methodname() const;
  void set_methodname(const ::std::string& value);
  #if LANG_CXX11
  void set_methodname(::std::string&& value);
  #endif
  void set_methodname(const char* value);
  void set_methodname(const void* value, size_t size);
  ::std::string* mutable_methodname();
  ::std::string* release_methodname();
  void set_allocated_methodname(::std::string* methodname);

  // uint32 argssize = 3;
  void clear_argssize();
  static const int kArgssizeFieldNumber = 3;
  ::google::protobuf::uint32 argssize() const;
  void set_argssize(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:mprpc.rpcheader)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr servicename_;
  ::google::protobuf::internal::ArenaStringPtr methodname_;
  ::google::protobuf::uint32 argssize_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_rpcheader_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// rpcheader

// bytes servicename = 1;
inline void rpcheader::clear_servicename() {
  servicename_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& rpcheader::servicename() const {
  // @@protoc_insertion_point(field_get:mprpc.rpcheader.servicename)
  return servicename_.GetNoArena();
}
inline void rpcheader::set_servicename(const ::std::string& value) {
  
  servicename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mprpc.rpcheader.servicename)
}
#if LANG_CXX11
inline void rpcheader::set_servicename(::std::string&& value) {
  
  servicename_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mprpc.rpcheader.servicename)
}
#endif
inline void rpcheader::set_servicename(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  servicename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mprpc.rpcheader.servicename)
}
inline void rpcheader::set_servicename(const void* value, size_t size) {
  
  servicename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mprpc.rpcheader.servicename)
}
inline ::std::string* rpcheader::mutable_servicename() {
  
  // @@protoc_insertion_point(field_mutable:mprpc.rpcheader.servicename)
  return servicename_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* rpcheader::release_servicename() {
  // @@protoc_insertion_point(field_release:mprpc.rpcheader.servicename)
  
  return servicename_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void rpcheader::set_allocated_servicename(::std::string* servicename) {
  if (servicename != NULL) {
    
  } else {
    
  }
  servicename_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), servicename);
  // @@protoc_insertion_point(field_set_allocated:mprpc.rpcheader.servicename)
}

// bytes methodname = 2;
inline void rpcheader::clear_methodname() {
  methodname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& rpcheader::methodname() const {
  // @@protoc_insertion_point(field_get:mprpc.rpcheader.methodname)
  return methodname_.GetNoArena();
}
inline void rpcheader::set_methodname(const ::std::string& value) {
  
  methodname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mprpc.rpcheader.methodname)
}
#if LANG_CXX11
inline void rpcheader::set_methodname(::std::string&& value) {
  
  methodname_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mprpc.rpcheader.methodname)
}
#endif
inline void rpcheader::set_methodname(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  methodname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mprpc.rpcheader.methodname)
}
inline void rpcheader::set_methodname(const void* value, size_t size) {
  
  methodname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mprpc.rpcheader.methodname)
}
inline ::std::string* rpcheader::mutable_methodname() {
  
  // @@protoc_insertion_point(field_mutable:mprpc.rpcheader.methodname)
  return methodname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* rpcheader::release_methodname() {
  // @@protoc_insertion_point(field_release:mprpc.rpcheader.methodname)
  
  return methodname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void rpcheader::set_allocated_methodname(::std::string* methodname) {
  if (methodname != NULL) {
    
  } else {
    
  }
  methodname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), methodname);
  // @@protoc_insertion_point(field_set_allocated:mprpc.rpcheader.methodname)
}

// uint32 argssize = 3;
inline void rpcheader::clear_argssize() {
  argssize_ = 0u;
}
inline ::google::protobuf::uint32 rpcheader::argssize() const {
  // @@protoc_insertion_point(field_get:mprpc.rpcheader.argssize)
  return argssize_;
}
inline void rpcheader::set_argssize(::google::protobuf::uint32 value) {
  
  argssize_ = value;
  // @@protoc_insertion_point(field_set:mprpc.rpcheader.argssize)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace mprpc

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_rpcheader_2eproto