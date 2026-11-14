// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B2370 rf_scene_record40_clear_low31_bits
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): ANDs firstDWORD with0x80000000,preserving only high flag bit and clearing low31bits;no pointer free or writes beyond firstDWORD. Used by40-byte pool adapter5CE940 stored at scene definition+204. Exact original type unproven;former GlobalNode association was false.
void __thiscall rf_scene_record40_clear_low31_bits(_DWORD *this)
{
  *this &= 0x80000000;
}

