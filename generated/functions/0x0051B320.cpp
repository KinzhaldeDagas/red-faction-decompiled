// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051B320 rf_geomod_terrain_components_classify
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall solid no stack args. Clear BYTE28 visited on all vertices120 and set every face label44=-1 BEFORE early exits. Return0 if face-list DWORD4 count zero, authored-room array144 count<1, or stack allocation returnsNULL. Allocate4*facecount scratch with overflow-to-FFFFFFFF sizing. Seed in array156 room order, skipping rooms whose authored-sky predicate byte is nonzero, then room face-list40 order. Seed and propagated face must be unlabeled and pass517CC0 (metadata bits8/4 clear, signed WORD52<=0). DFS through each corner vertex incidence32, globally mark vertex BYTE28 once; connectivity is shared vertex identity, not shared edge or distance. Propagation may leave seed room and does not repeat
// sky-room test. Track first STRICTLY greatest facecount component (ties first), free DFS scratch. If total<=1 return0 leaving labels intact. Else swap largest label with final label across entire solid list. Iterate labels: final/largest is always excluded WITHOUT shell validation; every smaller label kept only if5324F0 returns true. Exclusion relabels matching faces -1 and decrements all larger labels, retry same slot; largest stays last as count shrinks. Return surviving extractable component count, with compact labels0..count-1. Does not extract geometry or reset visited flags at end.
int __thiscall rf_geomod_terrain_components_classify(int this)
{
  _DWORD *v2; // [esp+0h] [ebp-64h]
  int v5; // [esp+14h] [ebp-50h]
  int ii; // [esp+18h] [ebp-4Ch]
  int v7; // [esp+1Ch] [ebp-48h]
  int v8; // [esp+20h] [ebp-44h]
  _DWORD *n; // [esp+24h] [ebp-40h]
  int v10; // [esp+28h] [ebp-3Ch]
  int v11; // [esp+2Ch] [ebp-38h]
  int v12; // [esp+30h] [ebp-34h]
  _BYTE *v13; // [esp+34h] [ebp-30h]
  int v14; // [esp+3Ch] [ebp-28h]
  int *v15; // [esp+40h] [ebp-24h]
  int v16; // [esp+44h] [ebp-20h]
  int v17; // [esp+48h] [ebp-1Ch]
  int first_dword; // [esp+4Ch] [ebp-18h]
  int j; // [esp+50h] [ebp-14h]
  int m; // [esp+50h] [ebp-14h]
  int jj; // [esp+50h] [ebp-14h]
  int kk; // [esp+50h] [ebp-14h]
  int v23; // [esp+54h] [ebp-10h]
  int i; // [esp+58h] [ebp-Ch]
  int k; // [esp+58h] [ebp-Ch]
  int v26; // [esp+58h] [ebp-Ch]
  int v27; // [esp+5Ch] [ebp-8h]
  int v28; // [esp+60h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword((void *)(this + 120));
  for ( i = 0; i < first_dword; ++i )
    *(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)(this + 120), i) + 28) = 0;
  for ( j = rf_receiver_get_first_dword((void *)(this + 112)); j; j = rf_solid_face_next_link(j) )
    *(_DWORD *)(j + 44) = -1;
  v17 = 0;
  v27 = -1;
  v14 = -1;
  v16 = rf_shared_second_dword_getter_518050((_DWORD *)(this + 112));
  if ( !v16 )
    return 0;
  if ( rf_receiver_get_first_dword((void *)(this + 144)) < 1 )
    return 0;
  v15 = (int *)operator new(4 * v16);
  if ( !v15 )
    return 0;
  for ( k = 0; k < rf_receiver_get_first_dword((void *)(this + 156)); ++k )
  {
    v13 = *(_BYTE **)sub_552200((_DWORD *)(this + 156), k);
    if ( !rf_room_is_authored_sky(v13) )
    {
      for ( m = rf_receiver_get_first_dword(v13 + 40); m; m = rf_face_next_room_link(m) )
      {
        if ( *(_DWORD *)(m + 44) == -1 && rf_geomod_terrain_component_face_eligible((__int16 *)(m + 40)) )
        {
          v11 = 1;
          *(_DWORD *)(m + 44) = v17++;
          v12 = 0;
          *v15 = m;
          while ( v12 > -1 )
          {
            v10 = v15[v12--];
            for ( n = *(_DWORD **)(v10 + 64); n; n = v2 )
            {
              v8 = *n;
              if ( !*(_BYTE *)(*n + 28) )
              {
                *(_BYTE *)(v8 + 28) = 1;
                v7 = rf_receiver_get_first_dword((void *)(v8 + 32));
                for ( ii = 0; ii < v7; ++ii )
                {
                  v5 = *(_DWORD *)sub_552200((_DWORD *)(v8 + 32), ii);
                  if ( *(_DWORD *)(v5 + 44) == -1 && rf_geomod_terrain_component_face_eligible((__int16 *)(v5 + 40)) )
                  {
                    *(_DWORD *)(v5 + 44) = *(_DWORD *)(m + 44);
                    ++v11;
                    v15[++v12] = v5;
                  }
                }
              }
              if ( n[5] == *(_DWORD *)(v10 + 64) )
                v2 = nullptr;
              else
                v2 = (_DWORD *)n[5];
            }
          }
          if ( v27 == -1 || v11 > v14 )
          {
            v27 = *(_DWORD *)(m + 44);
            v14 = v11;
          }
        }
      }
    }
  }
  operator delete(v15);
  if ( v17 <= 1 )
    return 0;
  v23 = v17 - 1;
  if ( v27 != v17 - 1 )
  {
    for ( jj = rf_receiver_get_first_dword((void *)(this + 112)); jj; jj = rf_solid_face_next_link(jj) )
    {
      if ( *(_DWORD *)(jj + 44) == v23 )
      {
        *(_DWORD *)(jj + 44) = v27;
      }
      else if ( *(_DWORD *)(jj + 44) == v27 )
      {
        *(_DWORD *)(jj + 44) = v23;
      }
    }
  }
  v28 = 0;
  v26 = 0;
  while ( v26 < v17 )
  {
    if ( v26 == v17 - 1 || !rf_geomod_component_shell_validate((char *)this, v26) )
    {
      ++v28;
      --v17;
      for ( kk = rf_receiver_get_first_dword((void *)(this + 112)); kk; kk = rf_solid_face_next_link(kk) )
      {
        if ( *(_DWORD *)(kk + 44) == v26 )
        {
          *(_DWORD *)(kk + 44) = -1;
        }
        else if ( *(_DWORD *)(kk + 44) > v26 )
        {
          --*(_DWORD *)(kk + 44);
        }
      }
    }
    else
    {
      ++v26;
    }
  }
  return v17;
}

