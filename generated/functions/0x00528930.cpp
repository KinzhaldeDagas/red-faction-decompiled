// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528930 rf_light_build_active_list_for_world_receiver
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl receiverSolid,includeCategoryBYTE,includeCommonBYTE. Same suppression/master early-return0 WITHOUT clearing old active state. Globalallow663B10zero forces includeCategory0. Get528140 receiver cache (NULLreceiver ->NULL), markvalid1/count0, NULLcache returns0 safely. In cached order require enabled76, RGB at least one nonzero OR NaN, and(includeCategory||!category77)&&(includeCommon||category77). Thus(1,0)categorynonzero only, while(0,0)none. Increment diagnosticD035F4 before type switch. Type1append;types2/3 inclusive original lightposition12 in receiver bounds72/84 expandedrange60, not cone or exact sphere;type4 finite original segment12/24 against expandedreceiverAABB. Unknownskip. No
// sorting/dedup/32 cap or per-frame identity mask write; active array retains stale entries beyond returned count, no transform-space coords. Master/category toggles themselves do not invalidate old selection.
unsigned int __cdecl rf_light_build_active_list_for_world_receiver(int a1, char a2, char a3)
{
  float v4[3]; // [esp+10h] [ebp-34h] BYREF
  float v5[3]; // [esp+1Ch] [ebp-28h] BYREF
  float v6[3]; // [esp+28h] [ebp-1Ch] BYREF
  int v7; // [esp+34h] [ebp-10h]
  _DWORD *cached_world_receiver_candidates; // [esp+38h] [ebp-Ch]
  int i; // [esp+3Ch] [ebp-8h]
  int first_dword; // [esp+40h] [ebp-4h]

  if ( dword_663B0C || !rf_renderer_lights_enabled )
    return 0;
  if ( !byte_663B10 )
    a2 = 0;
  cached_world_receiver_candidates = (_DWORD *)rf_light_get_cached_world_receiver_candidates(a1);
  unk_D035FC = 1;
  rf_light_active_world_count = 0;
  if ( !cached_world_receiver_candidates )
    return 0;
  first_dword = rf_receiver_get_first_dword(cached_world_receiver_candidates);
  for ( i = 0; i < first_dword; ++i )
  {
    v7 = *(_DWORD *)sub_552200(cached_world_receiver_candidates, i);
    if ( *(_BYTE *)(v7 + 76)
      && (*(float *)(v7 + 64) != 0.0 || *(float *)(v7 + 68) != 0.0 || *(float *)(v7 + 72) != 0.0)
      && (a2 || !*(_BYTE *)(v7 + 77))
      && (a3 || *(_BYTE *)(v7 + 77)) )
    {
      ++unk_D035F4;
      switch ( *(_DWORD *)(v7 + 8) )
      {
        case 1:
          rf_light_active_world_records[rf_light_active_world_count++] = v7;
          break;
        case 2:
          if ( rf_point_within_expanded_aabb(
                 (float *)(v7 + 12),
                 *(float *)(v7 + 60),
                 (float *)(a1 + 72),
                 (float *)(a1 + 84)) )
          {
            rf_light_active_world_records[rf_light_active_world_count++] = v7;
          }
          break;
        case 3:
          if ( rf_point_within_expanded_aabb(
                 (float *)(v7 + 12),
                 *(float *)(v7 + 60),
                 (float *)(a1 + 72),
                 (float *)(a1 + 84)) )
          {
            rf_light_active_world_records[rf_light_active_world_count++] = v7;
          }
          break;
        case 4:
          rf_vector3_copy_return_destination(v6, (float *)(a1 + 72));
          rf_vector3_copy_return_destination(v4, (float *)(a1 + 84));
          rf_vector3_subtract_scalar_in_place(v6, *(float *)(v7 + 60));
          rf_vector3_add_scalar_in_place(v4, *(float *)(v7 + 60));
          rf_vector3_default_construct_noop(v5);
          if ( rf_segment_intersects_aabb(v6, v4, (float *)(v7 + 12), (float *)(v7 + 24), v5) )
            rf_light_active_world_records[rf_light_active_world_count++] = v7;
          break;
        default:
          continue;
      }
    }
  }
  return rf_light_active_world_count;
}

