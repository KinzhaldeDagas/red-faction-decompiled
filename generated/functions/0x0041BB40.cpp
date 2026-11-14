// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041BB40 rf_glare_process_current_local_player_pass
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl low-byte render flag. Finds FIRST current-player0x87C640 match in local-player array/count; absent match returns with no fog/list work. Found index is used directly for per-player floats+668+4*i/+676+4*i, with NO local two-slot cap. Enables doubled fog/far helper, walks glare list until sentinel0x680AE8. Common flags+124 mask1 skips record entirely, retaining its flags/caches. Other records: flags+692 sign clear zeroes that player cache pair; sign set calls0x41AB70(glare,index). Nonzero input BYTE additionally calls0x41BC60(glare). Clears flags+692 mask0x80000000 afterward and only THEN reads next+696. Thus unlike deletion-safe walks it does not cache next across callbacks. Finally restores
// configured fog/far helper0; no previous state snapshot, unwind/reentrant guard or list validation.
void __cdecl rf_glare_process_current_local_player_pass(char a1)
{
  int v1; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  _DWORD *v3; // [esp+8h] [ebp-4h]

  v1 = -1;
  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    if ( rf_local_player_entries[i] == unk_87C640 )
    {
      v1 = i;
      break;
    }
  }
  if ( v1 != -1 )
  {
    rf_renderer_set_configured_fog_far_for_glare_pass(1);
    v3 = (_DWORD *)unk_680DA0;
    while ( v3 != (_DWORD *)&unk_680AE8 )
    {
      if ( (v3[31] & 1) != 0 )
      {
        v3 = (_DWORD *)v3[174];
      }
      else
      {
        if ( (int)v3[173] >= 0 )
        {
          *(float *)&v3[v1 + 167] = 0.0;
          *(float *)&v3[v1 + 169] = 0.0;
        }
        else
        {
          rf_glare_update_fade_and_render_corona(v3, v1);
        }
        if ( a1 )
          rf_glare_render_surface_reflection_quad((int)v3);
        v3[173] &= ~0x80000000;
        v3 = (_DWORD *)v3[174];
      }
    }
    rf_renderer_set_configured_fog_far_for_glare_pass(0);
  }
}

