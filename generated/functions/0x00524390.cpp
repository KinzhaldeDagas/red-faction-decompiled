// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00524390 rf_world_decal_translate_and_rebind_preserved
// UNREALRED VERIFIED [decal-updates-20261028]: Collects at most128 active records with flags+80 mask0x400 into fixed local array; extra protected records untouched. For each adds caller vec3 offset to decal position, sets owner+72=caller context, resolves primary owner+64 through0x517060, clears secondary owner+68 and flag0x400. Saves old bitmap, replaces bitmap+60 with-1, scans old-handle table0xA704FC (count0xA704F8), loads mapped32-byte filename0xA70520+32*k on first match. Returns polygons to pool after clearing polygon vertex-count+208/owner+1312 and unlinking per-decal list; no owner-removal callback in this manual loop. If remapped bitmap>=0 and fading flag0x40000000 clear, rebuilds via0x524030. Otherwise calls full spatial-remove/recycle0x524100. Return number processed, not number successfully rebound. No rollback on failed remap.
int __cdecl rf_world_decal_translate_and_rebind_preserved(void *a1, float *a2)
{
  int result; // eax
  float *v3; // [esp+0h] [ebp-230h]
  float *v4; // [esp+4h] [ebp-22Ch]
  float *v5; // [esp+8h] [ebp-228h]
  float *n; // [esp+10h] [ebp-220h]
  float *m; // [esp+18h] [ebp-218h]
  int v8; // [esp+1Ch] [ebp-214h]
  int k; // [esp+20h] [ebp-210h]
  float *i; // [esp+24h] [ebp-20Ch]
  float *v11; // [esp+24h] [ebp-20Ch]
  int v12; // [esp+28h] [ebp-208h]
  int j; // [esp+2Ch] [ebp-204h]
  _DWORD v14[128]; // [esp+30h] [ebp-200h]

  v12 = 0;
  for ( i = (float *)unk_A7051C; i; i = v5 )
  {
    if ( ((_DWORD)i[20] & 0x400) != 0 && v12 < 128 )
      v14[v12++] = i;
    if ( *((_DWORD *)i + 56) == unk_A7051C )
      v5 = nullptr;
    else
      v5 = *((float **)i + 56);
  }
  for ( j = 0; ; ++j )
  {
    result = j;
    if ( j >= v12 )
      break;
    v11 = (float *)v14[j];
    rf_vector_accumulate(v11, a2);
    *((_DWORD *)v11 + 18) = a1;
    *((_DWORD *)v11 + 16) = rf_world_resolve_cached_room(a1, nullptr, v11, v11, 0);
    v11[17] = 0.0;
    *((_DWORD *)v11 + 20) &= ~0x400u;
    v8 = *((_DWORD *)v11 + 15);
    v11[15] = NAN;
    for ( k = 0; k < dword_A704F8; ++k )
    {
      if ( v8 == unk_A704FC[k] )
      {
        *((_DWORD *)v11 + 15) = rf_bitmap_load_with_optional_mipmap_generation(
                                  &unk_A70520[32 * k],
                                  (void *)0xFFFFFFFF,
                                  1);
        break;
      }
    }
    if ( *((int *)v11 + 15) > -1 && ((_DWORD)v11[20] & 0x40000000) == 0 )
    {
      for ( m = *((float **)v11 + 53); ; m = v4 )
      {
        if ( !m )
        {
          rf_world_decal_recreate_from_current_fields((int)v11);
          goto LABEL_12;
        }
        if ( *((_DWORD *)m + 330) == *((_DWORD *)v11 + 53) )
          v4 = nullptr;
        else
          v4 = *((float **)m + 330);
        m[52] = 0.0;
        m[328] = 0.0;
        if ( *((float **)v11 + 53) == m )
        {
          if ( *((float **)m + 330) == m )
          {
            m[330] = 0.0;
            m[331] = 0.0;
            v11[53] = 0.0;
            goto LABEL_31;
          }
          v11[53] = m[330];
        }
        *(float *)(*((_DWORD *)m + 331) + 1320) = m[330];
        *(float *)(*((_DWORD *)m + 330) + 1324) = m[331];
        m[330] = 0.0;
        m[331] = 0.0;
LABEL_31:
        rf_decal_polygon_pool_release(dword_A70648, m);
        --*((_DWORD *)v11 + 54);
      }
    }
    for ( n = *((float **)v11 + 53); n; n = v3 )
    {
      if ( *((_DWORD *)n + 330) == *((_DWORD *)v11 + 53) )
        v3 = nullptr;
      else
        v3 = *((float **)n + 330);
      n[52] = 0.0;
      n[328] = 0.0;
      if ( *((float **)v11 + 53) == n )
      {
        if ( *((float **)n + 330) == n )
        {
          n[330] = 0.0;
          n[331] = 0.0;
          v11[53] = 0.0;
          goto LABEL_43;
        }
        v11[53] = n[330];
      }
      *(float *)(*((_DWORD *)n + 331) + 1320) = n[330];
      *(float *)(*((_DWORD *)n + 330) + 1324) = n[331];
      n[330] = 0.0;
      n[331] = 0.0;
LABEL_43:
      rf_decal_polygon_pool_release(dword_A70648, n);
      --*((_DWORD *)v11 + 54);
    }
    rf_world_decal_remove_spatial_links_and_recycle(v11);
LABEL_12:
    ;
  }
  return result;
}

