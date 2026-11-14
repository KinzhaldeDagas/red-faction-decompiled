// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D33A0 rf_physics_pair_registry_sweep_subject_segment
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, pair-contact selection, x87 unordered gates, partial contact writes and bounded near-time contact buckets): Cdecl subject,start,end,INOUT68-byte physics hit,ignored-other pointer. Walks global pair head813BD0,next through4C01F0; entries objectA4,objectB8,flags12. Admits pairs containing subject and whose OTHER pointer differs from ignored; orients source=subject,target=other. Priority chain: flags mask0x18 AND target type36==3 -> transformed-solid sweep; else flags mask6 AND target model128 nonNULL/kind1 -> model sweep; else target type3/4,owner48!=subject UID44,ORDERED global662E14<target radius384 -> sphere-pair shape sweep. Each path requires STRICT ORDERED stored source/target AABB overlap. First matching category owns pair even if AABB/narrow query misses: no lower-category fallback on a selected path miss.
// Delegates start,end,source physics136,target current position228/matrix252 or target shape136,shared output; no first-hit return. Each hit overwrites output material28 with target508,UID48 with target44,vector36 with target324; retains delegated point/normal/fraction/other fields. AL1 if any delegate reports hit. AL0 can still have output normal mutated by a rejected sphere candidate through delegated helper. No pair flag required for final sphere category beyond stated conditions; no own NULL/list-integrity/finite guard or initialization of output bound.
char __cdecl rf_physics_pair_registry_sweep_subject_segment(int a1, float *a2, float *a3, int a4, int a5)
{
  float v6[3]; // [esp+0h] [ebp-34h] BYREF
  float v7[3]; // [esp+Ch] [ebp-28h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-1Ch] BYREF
  char v9; // [esp+27h] [ebp-Dh]
  _DWORD *i; // [esp+28h] [ebp-Ch]
  int v11; // [esp+2Ch] [ebp-8h]
  float *v12; // [esp+30h] [ebp-4h]

  v9 = 0;
  for ( i = (_DWORD *)rf_receiver_get_first_dword(dword_813BD0); i; i = (_DWORD *)rf_intrusive_node_get_next_stdcall((int)i) )
  {
    if ( i[1] != a1 || i[2] == a5 )
    {
      if ( i[2] != a1 || i[1] == a5 )
        continue;
      v12 = (float *)i[2];
      v11 = i[1];
    }
    else
    {
      v12 = (float *)i[1];
      v11 = i[2];
    }
    if ( (i[3] & 0x18) != 0 && *(_DWORD *)(v11 + 36) == 3 )
    {
      if ( rf_aabb_overlap_strict_ordered(v12 + 100, v12 + 103, (float *)(v11 + 400), (float *)(v11 + 412)) )
      {
        if ( rf_physics_shape_sweep_against_transformed_solid(
               a2,
               a3,
               v12 + 34,
               (float *)(v11 + 228),
               (float *)(v11 + 252),
               *(char **)(v11 + 660),
               (float *)a4) )
        {
          *(_DWORD *)(a4 + 28) = *(_DWORD *)(v11 + 508);
          *(_DWORD *)(a4 + 48) = *(_DWORD *)(v11 + 44);
          rf_vector_copy((float *)(a4 + 36), copy_result, (const float *)(v11 + 324));
          v9 = 1;
        }
      }
    }
    else if ( (i[3] & 6) != 0 && *(_DWORD *)(v11 + 128) && rf_model_descriptor_get_kind(*(_DWORD *)(v11 + 128)) == 1 )
    {
      if ( rf_aabb_overlap_strict_ordered(v12 + 100, v12 + 103, (float *)(v11 + 400), (float *)(v11 + 412))
        && rf_physics_shape_sweep_against_model(
             a2,
             a3,
             (int)(v12 + 34),
             (float *)(v11 + 228),
             (float *)(v11 + 252),
             *(_DWORD **)(v11 + 128),
             (float *)a4) )
      {
        *(_DWORD *)(a4 + 28) = *(_DWORD *)(v11 + 508);
        *(_DWORD *)(a4 + 48) = *(_DWORD *)(v11 + 44);
        rf_vector_copy((float *)(a4 + 36), v7, (const float *)(v11 + 324));
        v9 = 1;
      }
    }
    else if ( (*(_DWORD *)(v11 + 36) == 4 || *(_DWORD *)(v11 + 36) == 3)
           && *(_DWORD *)(v11 + 48) != *(_DWORD *)(a1 + 44)
           && flt_662E14 < (double)*(float *)(v11 + 384)
           && rf_aabb_overlap_strict_ordered(v12 + 100, v12 + 103, (float *)(v11 + 400), (float *)(v11 + 412))
           && rf_physics_shape_sweep_spheres_against_shape(a2, a3, (int)(v12 + 34), v11 + 136, (float *)a4) )
    {
      *(_DWORD *)(a4 + 28) = *(_DWORD *)(v11 + 508);
      *(_DWORD *)(a4 + 48) = *(_DWORD *)(v11 + 44);
      rf_vector_copy((float *)(a4 + 36), v6, (const float *)(v11 + 324));
      v9 = 1;
    }
  }
  return v9;
}

