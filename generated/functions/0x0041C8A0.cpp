// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041C8A0 rf_glare_toggle_enabled_byte652
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall glare, no stack args. Replaces BYTE+652 with logical NOT of its prior value:0->1,any nonzero->0, using NEG/SBB/ADD. Returns receiver bits. Does not touch cached visibility+653, per-player fade values, list links or DWORD flags+692. Disabling leaves existing corona caches available for fade-out in0x41AB70.
_BYTE *__thiscall rf_glare_toggle_enabled_byte652(_BYTE *this)
{
  *(this + 652) = *(this + 652) == 0;
  return this;
}

