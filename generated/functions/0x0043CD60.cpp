// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CD60 rf_inline_array40_get_element_address
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Thiscall ECX inline array header plus one stack32-bit index, RET4. EAX=wrapping32(this+4+40*index); no load through computed element and no
// count/capacity/sign/bounds check or mutation. Negative indices/overflow retain literal address arithmetic. ENTITY sphere-center updater reads vector element+24 after this helper;
// this is not a pointer-array backing-store accessor.
int __thiscall rf_inline_array40_get_element_address(void *this, int a2)
{
  return (int)this + 40 * a2 + 4;
}

