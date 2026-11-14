// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A370 rf_geomod_cutter_registry_exit_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl exit callback. Signed loop i<count6EDEDC over12-byte records6EDEE0: assigns empty C string634178 to RFString0, destroys nonnull owned solid pointer+8 with delete flag1 and
// clears pointer. Then count0. Does not call RFString destructor here, visit unused records, clear operation queues/history, or destroy borrowed solids elsewhere. No own count
// capacity check; cached NULL entries only clear their names.
void __cdecl rf_geomod_cutter_registry_exit_cleanup()
{
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < dword_6EDEDC; ++i )
  {
    rf_string_assign_from_cstr(&byte_6EDEE0[12 * i], (char *)byte_634178);
    if ( unk_6EDEE8[3 * i] )
    {
      rf_solid_destroy((char *)unk_6EDEE8[3 * i], 1);
      unk_6EDEE8[3 * i] = 0;
    }
  }
  dword_6EDEDC = 0;
}

