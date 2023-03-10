// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: logicalClock.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_logicalClock_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_logicalClock_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021006 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_logicalClock_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_logicalClock_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_logicalClock_2eproto;
namespace logicalclockservice {
class LogicalClockTime;
struct LogicalClockTimeDefaultTypeInternal;
extern LogicalClockTimeDefaultTypeInternal _LogicalClockTime_default_instance_;
class Reply;
struct ReplyDefaultTypeInternal;
extern ReplyDefaultTypeInternal _Reply_default_instance_;
}  // namespace logicalclockservice
PROTOBUF_NAMESPACE_OPEN
template<> ::logicalclockservice::LogicalClockTime* Arena::CreateMaybeMessage<::logicalclockservice::LogicalClockTime>(Arena*);
template<> ::logicalclockservice::Reply* Arena::CreateMaybeMessage<::logicalclockservice::Reply>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace logicalclockservice {

// ===================================================================

class LogicalClockTime final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:logicalclockservice.LogicalClockTime) */ {
 public:
  inline LogicalClockTime() : LogicalClockTime(nullptr) {}
  ~LogicalClockTime() override;
  explicit PROTOBUF_CONSTEXPR LogicalClockTime(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  LogicalClockTime(const LogicalClockTime& from);
  LogicalClockTime(LogicalClockTime&& from) noexcept
    : LogicalClockTime() {
    *this = ::std::move(from);
  }

  inline LogicalClockTime& operator=(const LogicalClockTime& from) {
    CopyFrom(from);
    return *this;
  }
  inline LogicalClockTime& operator=(LogicalClockTime&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const LogicalClockTime& default_instance() {
    return *internal_default_instance();
  }
  static inline const LogicalClockTime* internal_default_instance() {
    return reinterpret_cast<const LogicalClockTime*>(
               &_LogicalClockTime_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(LogicalClockTime& a, LogicalClockTime& b) {
    a.Swap(&b);
  }
  inline void Swap(LogicalClockTime* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(LogicalClockTime* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  LogicalClockTime* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<LogicalClockTime>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const LogicalClockTime& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const LogicalClockTime& from) {
    LogicalClockTime::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(LogicalClockTime* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "logicalclockservice.LogicalClockTime";
  }
  protected:
  explicit LogicalClockTime(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTimeFieldNumber = 1,
  };
  // int32 time = 1;
  void clear_time();
  int32_t time() const;
  void set_time(int32_t value);
  private:
  int32_t _internal_time() const;
  void _internal_set_time(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:logicalclockservice.LogicalClockTime)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t time_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_logicalClock_2eproto;
};
// -------------------------------------------------------------------

class Reply final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:logicalclockservice.Reply) */ {
 public:
  inline Reply() : Reply(nullptr) {}
  ~Reply() override;
  explicit PROTOBUF_CONSTEXPR Reply(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Reply(const Reply& from);
  Reply(Reply&& from) noexcept
    : Reply() {
    *this = ::std::move(from);
  }

  inline Reply& operator=(const Reply& from) {
    CopyFrom(from);
    return *this;
  }
  inline Reply& operator=(Reply&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Reply& default_instance() {
    return *internal_default_instance();
  }
  static inline const Reply* internal_default_instance() {
    return reinterpret_cast<const Reply*>(
               &_Reply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Reply& a, Reply& b) {
    a.Swap(&b);
  }
  inline void Swap(Reply* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Reply* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Reply* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Reply>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Reply& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Reply& from) {
    Reply::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Reply* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "logicalclockservice.Reply";
  }
  protected:
  explicit Reply(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kErrorMsgFieldNumber = 1,
  };
  // string errorMsg = 1;
  void clear_errormsg();
  const std::string& errormsg() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_errormsg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_errormsg();
  PROTOBUF_NODISCARD std::string* release_errormsg();
  void set_allocated_errormsg(std::string* errormsg);
  private:
  const std::string& _internal_errormsg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_errormsg(const std::string& value);
  std::string* _internal_mutable_errormsg();
  public:

  // @@protoc_insertion_point(class_scope:logicalclockservice.Reply)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr errormsg_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_logicalClock_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LogicalClockTime

// int32 time = 1;
inline void LogicalClockTime::clear_time() {
  _impl_.time_ = 0;
}
inline int32_t LogicalClockTime::_internal_time() const {
  return _impl_.time_;
}
inline int32_t LogicalClockTime::time() const {
  // @@protoc_insertion_point(field_get:logicalclockservice.LogicalClockTime.time)
  return _internal_time();
}
inline void LogicalClockTime::_internal_set_time(int32_t value) {
  
  _impl_.time_ = value;
}
inline void LogicalClockTime::set_time(int32_t value) {
  _internal_set_time(value);
  // @@protoc_insertion_point(field_set:logicalclockservice.LogicalClockTime.time)
}

// -------------------------------------------------------------------

// Reply

// string errorMsg = 1;
inline void Reply::clear_errormsg() {
  _impl_.errormsg_.ClearToEmpty();
}
inline const std::string& Reply::errormsg() const {
  // @@protoc_insertion_point(field_get:logicalclockservice.Reply.errorMsg)
  return _internal_errormsg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Reply::set_errormsg(ArgT0&& arg0, ArgT... args) {
 
 _impl_.errormsg_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:logicalclockservice.Reply.errorMsg)
}
inline std::string* Reply::mutable_errormsg() {
  std::string* _s = _internal_mutable_errormsg();
  // @@protoc_insertion_point(field_mutable:logicalclockservice.Reply.errorMsg)
  return _s;
}
inline const std::string& Reply::_internal_errormsg() const {
  return _impl_.errormsg_.Get();
}
inline void Reply::_internal_set_errormsg(const std::string& value) {
  
  _impl_.errormsg_.Set(value, GetArenaForAllocation());
}
inline std::string* Reply::_internal_mutable_errormsg() {
  
  return _impl_.errormsg_.Mutable(GetArenaForAllocation());
}
inline std::string* Reply::release_errormsg() {
  // @@protoc_insertion_point(field_release:logicalclockservice.Reply.errorMsg)
  return _impl_.errormsg_.Release();
}
inline void Reply::set_allocated_errormsg(std::string* errormsg) {
  if (errormsg != nullptr) {
    
  } else {
    
  }
  _impl_.errormsg_.SetAllocated(errormsg, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.errormsg_.IsDefault()) {
    _impl_.errormsg_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:logicalclockservice.Reply.errorMsg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace logicalclockservice

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_logicalClock_2eproto
