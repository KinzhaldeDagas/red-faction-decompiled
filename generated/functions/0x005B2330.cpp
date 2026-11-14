// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B2330 rf_scene_record40_construct_preserving_high_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): Thiscall40-byte scene pool element constructor. Invokes verified NO-OP vector defaults at+8 and+20, preserves ONLY original DWORD0 bit31 via AND80000000h, sets DWORD+4=0. Does not initialize bit31, either vector, or tail+32..39. No allocation/vtable; ordinary heap storage can therefore retain prior high flag/vector bytes. Current declared void; used by cookie-array construction at scene pool204.
void __thiscall rf_scene_record40_construct_preserving_high_flag(_DWORD *this)
{
  rf_vector3_default_construct_noop(this + 2);
  rf_vector3_default_construct_noop(this + 5);
  *this &= 0x80000000;
  *(this + 1) = 0;
}

