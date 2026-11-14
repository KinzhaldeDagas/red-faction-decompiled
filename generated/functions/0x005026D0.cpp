// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005026D0 rf_event_state_collect_invulnerability
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Collect ALL current registry events with numeric type24, irrespective of armed shared delay or enabled state. Each 24-byte entry gets common20-byte header0x502230 plus packed deadline event+0x2BC at entry+0x14. Write number of entries through byte count pointer; no local count/capacity clamp or full-entry padding clear. Runtime voice/resource objects and other authored fields are not included in this tail.
int __cdecl rf_event_state_collect_invulnerability(int a1, _BYTE *a2)
{
  int result; // eax
  int *v3; // eax
  int v4; // [esp+0h] [ebp-Ch]
  int v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v5 = 0;
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_90B0E0);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 656) == 24 )
    {
      v4 = *(_DWORD *)sub_552200(unk_90B0E0, i);
      v3 = (int *)sub_552200(unk_90B0E0, i);
      rf_event_state_pack_header(*v3, a1 + 24 * v5);
      rf_snapshot_pack_replicator_remaining((int *)(v4 + 700), (int *)(a1 + 24 * v5++ + 20));
    }
  }
  *a2 = v5;
  return result;
}

