// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F6F0 rf_string_object_c_str_or_empty
// UNREALRED VERIFIED [stream-serializers-20261029]: Thiscall object pointer. Returns DWORD pointer at object+4 when nonnull,else empty literal0x640809 (first byte0 independently checked against PE). Does not consult first DWORD,call vtable,allocate,throw or mutate object. RF string serialization0x5A0F30 and numerous other string consumers use this accessor. Original std::exception::what library label/inferred std::exception pointer type was misleading in these RF string call sites. Returned pointer is borrowed and lifetime follows underlying object storage.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Prototype correction from false std::exception* receiver to const opaque object pointer. Reads only buffer pointer at object+4;nonnull returns borrowed pointer,NULL returns verified empty literal640809. Does not inspect stored extent at0,call vtable,allocate,throw or mutate object. Used by custom formatter%t after temporary RFString8 copy;existing verified lifetime/layout comments preserved.
const char *__thiscall rf_string_object_c_str_or_empty(const void *this)
{
  if ( *((_DWORD *)this + 1) )
    return *((const char **)this + 1);
  else
    return (const char *)&unk_640809;
}

