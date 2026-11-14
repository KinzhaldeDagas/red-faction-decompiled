// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0090 rf_sound_resource_unregister_all
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Calls resource_unregister for indices 0..resource_count-1, then sets resource_count=0. EAX is incidental; does not itself clear every record field.
int rf_sound_resource_unregister_all()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_sound_resource_count; ++i )
  {
    rf_sound_resource_unregister(i);
    result = i + 1;
  }
  rf_sound_resource_count = 0;
  return result;
}

