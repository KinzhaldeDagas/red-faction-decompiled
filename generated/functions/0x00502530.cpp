// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502530 rf_event_state_collect_when_dead
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Collect ALL current registry events with numeric type16, irrespective of armed shared delay or enabled state. Each 24-byte entry gets common20-byte header0x502230 plus raw byte event+0x2B8 latch at entry+0x14. Write number of entries through byte count pointer; no local count/capacity clamp or full-entry padding clear. Runtime voice/resource objects and other authored fields are not included in this tail.
_BYTE *__cdecl rf_event_state_collect_when_dead(int a1, _BYTE *a2)
{
  int *v2; // eax
  int v4; // [esp+0h] [ebp-Ch]
  int v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v5 = 0;
  for ( i = 0; i < rf_receiver_get_first_dword(unk_90B0E0); ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 656) == 16 )
    {
      v4 = *(_DWORD *)sub_552200(unk_90B0E0, i);
      v2 = (int *)sub_552200(unk_90B0E0, i);
      rf_event_state_pack_header(*v2, a1 + 24 * v5);
      *(_BYTE *)(a1 + 24 * v5++ + 20) = *(_BYTE *)(v4 + 696);
    }
  }
  *a2 = v5;
  return a2;
}

