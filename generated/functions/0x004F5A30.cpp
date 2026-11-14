// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5A30 rf_restore_apply_object_identifier_fixups
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Walk all queued count0x88E7C8 entries. Saved-1 writes destination=-1. Otherwise resolve stable id with0x4BC680; hit writes common-object runtime identifier+0x2C and miss writes-1. Does not clear queue count afterward. Event header restoration queues destinations+0x2A8/+0x2AC; this later phase publishes runtime references.
void rf_restore_apply_object_identifier_fixups()
{
  int v0; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < unk_88E7C8; ++i )
  {
    if ( unk_88E8D0[i] == -1 )
    {
      *(_DWORD *)unk_8935B8[i] = -1;
    }
    else
    {
      v0 = rf_object_find_by_saved_identifier(unk_88E8D0[i]);
      if ( v0 )
        *(_DWORD *)unk_8935B8[i] = *(_DWORD *)(v0 + 44);
      else
        *(_DWORD *)unk_8935B8[i] = -1;
    }
  }
}

