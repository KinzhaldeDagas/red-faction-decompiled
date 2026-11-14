// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004182C0 rf_physical_debris_expiry_health_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): If timer+676 is elapsed, first marks the object for deferred deletion, then flags+668 bit1 optionally spawns effect ID+672 using room DWORD0, common position+60 and radius+120. Continues to test health float+52: ordered <=0 marks deletion again; NaN skips the health deletion. Neither consumes timer/flag nor frees/unlinks object, so an expired effect can repeat until actual deletion.
void __cdecl rf_physical_debris_expiry_health_update(int a1)
{
  int first_dword; // eax
  float v2; // [esp+0h] [ebp-Ch]

  if ( rf_replicator_has_elapsed((int *)(a1 + 676)) )
  {
    rf_object_mark_for_deferred_delete(a1);
    if ( (*(_DWORD *)(a1 + 668) & 1) != 0 )
    {
      v2 = *(float *)(a1 + 120);
      first_dword = rf_receiver_get_first_dword((void *)a1);
      sub_448DC0(*(_DWORD *)(a1 + 672), first_dword, 0, (float *)(a1 + 60), v2, 1.0, 0);
    }
  }
  if ( *(float *)(a1 + 52) <= 0.0 )
    rf_object_mark_for_deferred_delete(a1);
}

