// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052CDD0 rf_geomod_candidate_pairs_refresh_after_face_split
// UNREALRED VERIFIED [finite-pair-20261028] Reclips face decal polygons onto replacements and walks complete candidate list from tail, replacing every pair containing the old face with ALL nonnull AABB-overlapping replacement faces. Reuses first pair node, allocates 16-byte nodes for additional replacements, deletes pair if none overlap, leaves unrelated pairs intact. Called at0x52C6C6 /0x52C8AB BEFORE old-face destruction at0x52C6D7 /0x52C8BC. A scheduled pair must not disappear after the first replacement.
// UNREALRED VERIFIED [combat-native-query-20261104]: Refresh walks pending tail backward saving previous. First overlapping replacement child reuses the existing pair node; extra children insert immediately after saved previous, preserving unrelated newer-pair priority. Each replacement is stored as(child,otherFace), regardless of original slot, so a(world,cutter) pair can become(cutterChild,world). This slot flip changes intersection-line direction and sorted record order.
void __cdecl rf_geomod_candidate_pairs_refresh_after_face_split(float *a1, int a2, int a3)
{
  float **v3; // [esp+8h] [ebp-1Ch]
  float *v4; // [esp+Ch] [ebp-18h]
  char v5; // [esp+13h] [ebp-11h]
  int j; // [esp+14h] [ebp-10h]
  float *v7; // [esp+18h] [ebp-Ch]
  float **v8; // [esp+1Ch] [ebp-8h]
  float **i; // [esp+20h] [ebp-4h]

  rf_geomod_face_decal_polygons_replace_after_split(a1, a2, a3);
  for ( i = (float **)rf_geomod_candidate_pair_list_tail; i != (float **)&rf_geomod_candidate_pair_list_sentinel; i = v8 )
  {
    v8 = (float **)i[2];
    v7 = nullptr;
    if ( *i == a1 )
    {
      v7 = i[1];
    }
    else if ( i[1] == a1 )
    {
      v7 = *i;
    }
    if ( v7 )
    {
      v5 = 0;
      for ( j = 0; j < a3; ++j )
      {
        v4 = *(float **)(a2 + 4 * j);
        if ( v4 && rf_geomod_face_bounds_overlap(v4, v7) )
        {
          if ( v5 )
          {
            v3 = (float **)operator new(0x10u);
            *((_DWORD *)v8[3] + 2) = v3;
            v3[3] = v8[3];
            v8[3] = (float *)v3;
            v3[2] = (float *)v8;
            ++rf_geomod_candidate_pair_count;
          }
          else
          {
            v5 = 1;
            v3 = i;
          }
          *v3 = v4;
          v3[1] = v7;
        }
      }
      if ( !v5 )
      {
        *((_DWORD *)i[3] + 2) = i[2];
        *((_DWORD *)i[2] + 3) = i[3];
        i[2] = nullptr;
        i[3] = nullptr;
        operator delete(i);
        --rf_geomod_candidate_pair_count;
      }
    }
  }
}

