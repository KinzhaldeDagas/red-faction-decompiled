// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE3F0 rf_script_apply_resolved_entity_action
// UNREALRED VERIFIED [mission-play-animation-file-20261013] Internal type12 filename branch of serialized Play_Animation. If event+0x2C4!=-1, resolve ordered target handles, skip dead entities and entity numeric mode+0x520==7, then refresh idle deadline via0x437370. Action byte+0x2C0 nonzero starts instance action at mix1/hold(+0x2C8), stores index at Entity+0x1368, and sets Entity+0x810 bit8 iff hold==1. Unlike canonical held action, this path does NOT clear cyclic or action records and does NOT request canonical action sound. Loop branch stores index in custom state slot22 (Entity+0xA44) and sets Entity+0x810 bit0x02000000; hold is ignored. Common forwarding still follows.
// UNREALRED VERIFIED [ai-script-animation-capacity-20261013] The filename action branch does not inspect a start-result value: after rf_vfx_start_instance it always writes Entity+0x1368 to the requested animation index and sets Entity+0x810 bit 8 when hold is exactly 1. A full instance record pool therefore does not suppress these owner/hold side effects. Cleanup later tests actual remaining time, so an unallocated requested animation cannot by itself erase unrelated records.
int __fastcall rf_script_apply_resolved_entity_action(int a1)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  result = a1;
  if ( *(_DWORD *)(a1 + 708) != -1 )
  {
    for ( i = 0; ; ++i )
    {
      result = rf_receiver_get_first_dword((void *)(a1 + 668));
      if ( i >= result )
        break;
      v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
      v4 = rf_entity_resolve_handle(*v2);
      if ( v4 && !rf_entity_is_dead(v4) && *(_DWORD *)(v4 + 1312) != 7 )
      {
        rf_entity_refresh_idle_animation_deadline(v4);
        if ( *(_BYTE *)(a1 + 704) )
        {
          rf_vfx_start_instance(*(int **)(v4 + 128), *(_DWORD *)(a1 + 708), 1.0, *(_BYTE *)(a1 + 712));
          *(_DWORD *)(v4 + 4968) = *(_DWORD *)(a1 + 708);
          if ( *(_BYTE *)(a1 + 712) == 1 )
            *(_DWORD *)(v4 + 2064) |= 8u;
        }
        else
        {
          *(_DWORD *)(v4 + 2628) = *(_DWORD *)(a1 + 708);
          *(_DWORD *)(v4 + 2064) |= (unsigned int)&unk_2000000;
        }
      }
    }
  }
  return result;
}

