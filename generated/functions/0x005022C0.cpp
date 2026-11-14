// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005022C0 rf_event_state_collect_armed_generic
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Scan event registry vector0x90B0E0. Skip types16,20,24,35,45 because specialized collectors handle them; among other types pack ONLY armed deadline+0x298 events, stride20, through0x502230. Write total low byte to supplied count pointer. No capacity argument or count clamp in body; current enabled/disabled flag is not a collection gate.
char __cdecl rf_event_state_collect_armed_generic(int a1, _BYTE *a2)
{
  int v2; // eax
  int *v3; // eax
  int i; // [esp+Ch] [ebp-8h]
  int v6; // [esp+10h] [ebp-4h]

  v6 = 0;
  for ( i = 0; i < rf_receiver_get_first_dword(unk_90B0E0); ++i )
  {
    switch ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 656) )
    {
      case 0x10:
      case 0x14:
      case 0x18:
      case 0x23:
      case 0x2D:
        continue;
      default:
        v2 = sub_552200(unk_90B0E0, i);
        if ( rf_replicator_is_armed((_DWORD *)(*(_DWORD *)v2 + 664)) )
        {
          v3 = (int *)sub_552200(unk_90B0E0, i);
          rf_event_state_pack_header(*v3, a1 + 20 * v6++);
        }
        break;
    }
  }
  *a2 = v6;
  return v6;
}

