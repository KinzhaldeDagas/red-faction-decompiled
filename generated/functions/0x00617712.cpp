// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617712 crt_get_decoded_pointer_02021c84
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments. Push LIVE globalDWORD2021C84, call60E0F7 __decode_pointer, POP ECX reclaims4 bytes, return decoded EAX. Does not clear/update stored
// encoded value, test NULL, call resulting pointer or enforce initialization/ownership. Decoder can return unchanged input when platform encoding provider is unavailable; wrapper
// performs no additional policy.
PVOID crt_get_decoded_pointer_02021c84()
{
  return _decode_pointer((void *)dword_2021C84);
}

