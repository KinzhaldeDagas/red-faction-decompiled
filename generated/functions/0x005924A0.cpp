// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005924A0 rf_vfile_get_slot_version
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall vfile,reads signed/integer slot DWORD at object+272,returns version DWORD at global189CEB8+32832*slot. No negative/upper-bound check,status/mode test or stream consumption. Used by cached-or-vfile adapter549EE0 and version-gated scalar readers through their comparison helper.
int __thiscall rf_vfile_get_slot_version(_DWORD *this)
{
  return unk_189CEB8[8208 * *(this + 68)];
}

