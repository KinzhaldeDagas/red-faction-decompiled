// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596C40 rf_file_transfer_service_record
// UNREALRED VERIFIED [file-transfer-20261028]: Record pointer. Success bit0x80 returns immediately. For serialized bit0x10000 without granted0x400, scans60 active send records for same peer with serialized+granted flags; if found defers. Otherwise sets granted0x400 and pending8. Pending8 sends offer0x596970, arms10-second deadline, clears8 and sets waiting0x10. Armed expired deadline sets timeout0x200; auto-release0x8000 calls abort0x596470. Does not retry packets. Incidental low-byte return is not a success boolean.
char __cdecl rf_file_transfer_service_record(_DWORD *a1)
{
  int v1; // eax
  int *v3; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int v5; // [esp+8h] [ebp-4h]

  LOBYTE(v1) = (_BYTE)a1;
  if ( (*a1 & 0x80) != 0 )
    return v1;
  v1 = *a1 & 0x10000;
  if ( !v1 || (*a1 & 0x400) != 0 )
    goto LABEL_16;
  v5 = 0;
  for ( i = 0; i < 60; ++i )
  {
    v3 = &unk_1BC3CC8[109 * i];
    if ( (*v3 & 1) != 0 && v3[105] == a1[105] && (*v3 & 2) != 0 && (*v3 & 0x10000) != 0 )
    {
      v1 = *v3 & 0x400;
      if ( v1 )
      {
        v5 = 1;
        break;
      }
    }
    LOBYTE(v1) = i + 1;
  }
  if ( !v5 )
  {
    *a1 |= 0x400u;
    *a1 |= 8u;
LABEL_16:
    if ( (*a1 & 8) != 0 )
    {
      rf_file_transfer_send_offer_packet((int)a1);
      rf_replicator_arm_milliseconds(a1 + 106, 10000);
      *a1 &= ~8u;
      *a1 |= 0x10u;
    }
    LOBYTE(v1) = rf_replicator_is_armed(a1 + 106);
    if ( (_BYTE)v1 )
    {
      LOBYTE(v1) = rf_replicator_has_elapsed(a1 + 106);
      if ( (_BYTE)v1 )
      {
        LOBYTE(v1) = (_BYTE)a1;
        *a1 |= 0x200u;
        if ( (*a1 & 0x8000) != 0 )
          LOBYTE(v1) = rf_file_transfer_abort_record((int)a1);
      }
    }
  }
  return v1;
}

