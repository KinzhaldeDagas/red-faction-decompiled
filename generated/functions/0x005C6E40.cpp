// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6E40 rf_positional_sound_shutdown
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): If initialized flag 1DAEE54 is nonzero, destroys every live instance with zero fade then clears the flag. Leaves the static pool storage allocated. Function boundaries recovered from original prologue, local branches and terminal RET.
void __cdecl rf_positional_sound_shutdown()
{
  if ( byte_1DAEE54 )
  {
    rf_positional_sound_destroy_all();
    byte_1DAEE54 = 0;
  }
}

