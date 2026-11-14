// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004780B0 rf_geomod_georegions_apply
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl(point3f*,INOUT operation100*,BYTE apply_hardness), returns AL0/1. Native reads only three stack args [EBP+8/+12/+16], both callers push3/pop12; no incoming x87 value is
// consumed as a formal parameter. Typed the two pointer arguments and the byte mode from native field access. The old containment helper signature could cause decompiler inference of
// a phantom ST0 argument here; do not treat that transient inferred register argument as native ABI. Clears op constraint vectors76/88 immediately; failures below can leave partially
// mutated vectors/flags with no rollback. Scans region registry in order, admits through contains_point(point,region). No enabled check here other than region shape helper; direction
// BYTE+8 and ice BYTE+9 require EXACT1.
// For directional regions, initial direction=raw matrix row1 at region+40, scalar=FLOAT+12. With exactly one prior accepted direction, ordered dot(existing raw direction,new raw
// direction)>double0.949999988079071 marks duplicate and skips adding it; equality/NaN does not merge. First accepted copies direction to op76, scalar to local EBP-4. Second copies
// op88/local EBP-8 then requires dot(dir1,dir2)>=double-0.10000000149011612 OR unordered; ordered smaller rejects. With already two accepted directions, EVERY further directional
// region increments count3 and rejects, even if parallel: duplicate test only ran at count1. Non-directional contained regions still contribute hardness/ice.
// Maximum signed region hardness DWORD+4 starts-1; only strictly greater updates. If still-1 uses global hardness. Contained ice BYTE+9==1 ORs op.flags56 with0x10, never clears
// previous ice. Only apply_hardness BYTE==1: exact hardness100 rejects; otherwise factor=F32(1-H/100), clamp[0,1], op.scale60=F32(oldScale*factor). H>100 becomes factor0 but is NOT
// rejected by exact100 gate; negative values clamp factor1. Other apply bytes skip this scale/reject branch.
// Unconditionally multiplies op76 by NEGATED local EBP-4 scalar and op88 by NEGATED EBP-8 scalar, then copies input point to op.position8. IMPORTANT: scalar locals are assigned only
// for first/second accepted directions, respectively. Zero-direction path reads BOTH uninitialized stack locals; one-direction path still reads second uninitialized local, despite
// clearing its vector first. Do not replace these native reads with defined scalar0 or assume missing constraints remain finite zero: arbitrary/NaN stack data can affect
// multiplication. This is separate from the removed false x87 formal argument.
// If accepted-direction count>0, computes up to two correction vectors initially zero by scanning saved count6FCCF4, records32 at6FCD00 and sidecars36 at6FDD50. Stops at next record
// once correction1 nonzero for count1, or BOTH nonzero for count2. Saved first sidecar constraint+12 must be nonzero; second+24 adds a second candidate plane. Does NOT require
// matching saved cutter id/room/flags. Radius gate uses CURRENT operation cutter's radius96 * SAVED record scale28, roundedF32 then square roundedF32, strictly ORDERED greater than
// F32 distanceSquared(saved sidecar origin,input point). No cutter NULL guard.
// For each saved plane vector, normalize_get_length yields unit normal and original-length squared bound (F32 stores; helper fallback semantics retained). For each unmatched current
// direction slot, normalize its scaled constraint vector. Admit alignment dot(normal,currentDirection)>=double0.95 OR unordered, AND dot(normal,normalize(point-savedOrigin)) strictly
// ORDERED>0. Project ORIGINAL input point onto plane(normal,savedOrigin), require squared normal length strictly ORDERED>distanceSquared(projected,input). Store
// correction=projected-input into its slot. Then append correction1 followed by correction2 to op.position8. Not nearest-plane selection: first nonzero correction for each slot
// sticks; zero correction remains an unfilled sentinel and may be replaced. No iterative re-projection using already shifted position, finite validation or all-or-nothing failure
// semantics. AL1 on normal end.
char __cdecl rf_geomod_georegions_apply(const float *point, void *operation, unsigned __int8 apply_hardness)
{
  int first_dword; // eax
  float *v5; // eax
  float *v6; // eax
  double v7; // st7
  float *v8; // eax
  float *v9; // eax
  float scalar; // [esp+8h] [ebp-148h]
  float scalara; // [esp+8h] [ebp-148h]
  float v12[3]; // [esp+Ch] [ebp-144h] BYREF
  float v13[3]; // [esp+18h] [ebp-138h] BYREF
  float v14[3]; // [esp+24h] [ebp-12Ch] BYREF
  float v15[3]; // [esp+30h] [ebp-120h] BYREF
  float v16[3]; // [esp+3Ch] [ebp-114h] BYREF
  float v17[3]; // [esp+48h] [ebp-108h] BYREF
  float v18[3]; // [esp+54h] [ebp-FCh] BYREF
  float v19[3]; // [esp+60h] [ebp-F0h] BYREF
  float v20[3]; // [esp+6Ch] [ebp-E4h] BYREF
  float v21[3]; // [esp+78h] [ebp-D8h] BYREF
  float v22[3]; // [esp+84h] [ebp-CCh] BYREF
  float v23[3]; // [esp+90h] [ebp-C0h] BYREF
  float scaled_result[3]; // [esp+9Ch] [ebp-B4h] BYREF
  float v25[3]; // [esp+A8h] [ebp-A8h] BYREF
  float copy_result[3]; // [esp+B4h] [ebp-9Ch] BYREF
  float output[3]; // [esp+C0h] [ebp-90h] BYREF
  float destination[3]; // [esp+CCh] [ebp-84h] BYREF
  int m; // [esp+D8h] [ebp-78h]
  float length; // [esp+DCh] [ebp-74h]
  float normal[3]; // [esp+E0h] [ebp-70h] BYREF
  int k; // [esp+ECh] [ebp-64h]
  float out_vector[3]; // [esp+F0h] [ebp-60h] BYREF
  __int16 *v34; // [esp+FCh] [ebp-54h]
  int v35; // [esp+100h] [ebp-50h]
  float v36; // [esp+104h] [ebp-4Ch]
  float v37; // [esp+108h] [ebp-48h]
  float *plane_point; // [esp+10Ch] [ebp-44h]
  int v39; // [esp+110h] [ebp-40h]
  float v40[3]; // [esp+114h] [ebp-3Ch] BYREF
  float v41[3]; // [esp+120h] [ebp-30h] BYREF
  int j; // [esp+12Ch] [ebp-24h]
  float v43; // [esp+130h] [ebp-20h] BYREF
  bool v44; // [esp+137h] [ebp-19h]
  void *region; // [esp+138h] [ebp-18h]
  int v46; // [esp+13Ch] [ebp-14h]
  int v47; // [esp+140h] [ebp-10h]
  int i; // [esp+144h] [ebp-Ch]
  float v49; // [esp+148h] [ebp-8h]
  float v50; // [esp+14Ch] [ebp-4h]

  v47 = 0;
  v46 = -1;
  rf_vector3_zero_return_destination((float *)operation + 19);
  rf_vector3_zero_return_destination((float *)operation + 22);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(rf_geomod_georegion_registry);
    if ( i >= first_dword )
      break;
    region = *(void **)sub_552200(rf_geomod_georegion_registry, i);
    if ( rf_geomod_georegion_contains_point(point, region) )
    {
      if ( *((_BYTE *)region + 8) == 1 )
      {
        v44 = 1;
        if ( v47 == 1 )
          v44 = rf_vector_dot((float *)operation + 19, (float *)region + 10) <= 0.949999988079071;
        if ( v44 )
        {
          if ( ++v47 == 1 )
          {
            rf_vector_copy((float *)operation + 19, copy_result, (const float *)region + 10);
            v50 = *((float *)region + 3);
          }
          else
          {
            if ( v47 != 2 )
              return 0;
            rf_vector_copy((float *)operation + 22, v25, (const float *)region + 10);
            v49 = *((float *)region + 3);
            if ( rf_vector_dot((float *)operation + 19, (float *)operation + 22) < -0.1000000014901161 )
              return 0;
          }
        }
      }
      if ( *((_DWORD *)region + 1) > v46 )
        v46 = *((_DWORD *)region + 1);
      if ( *((_BYTE *)region + 9) == 1 )
        *((_DWORD *)operation + 14) |= 0x10u;
    }
  }
  if ( v46 == -1 )
    v46 = rf_geomod_global_hardness;
  if ( apply_hardness == 1 )
  {
    if ( v46 == 100 )
      return 0;
    v43 = 1.0 - (double)v46 / 100.0;
    rf_float_clamp_in_place(&v43, 0.0, 1.0);
    *((float *)operation + 15) = *((float *)operation + 15) * v43;
  }
  scalar = -v50;
  v5 = rf_vector_multiply_scalar((const float *)operation + 19, scaled_result, scalar);
  rf_vector_copy((float *)operation + 19, v23, v5);
  scalara = -v49;
  v6 = rf_vector_multiply_scalar((const float *)operation + 22, v22, scalara);
  rf_vector_copy((float *)operation + 22, v21, v6);
  rf_vector_copy((float *)operation + 2, v20, point);
  if ( v47 > 0 )
  {
    rf_vector3_set_components_return_destination(v40, 0.0, 0.0, 0.0);
    rf_vector3_set_components_return_destination(v41, 0.0, 0.0, 0.0);
    for ( j = 0; j < rf_geomod_save_record_count; ++j )
    {
      v34 = &rf_geomod_save_records[16 * j];
      plane_point = (float *)((char *)&unk_6FDD50 + 36 * j);
      if ( v47 == 1 && !rf_vector3_is_exact_zero(v40) )
        break;
      if ( v47 == 2 && !rf_vector3_is_exact_zero(v40) && !rf_vector3_is_exact_zero(v41) )
        break;
      if ( !rf_vector3_is_exact_zero(plane_point + 3) )
      {
        v35 = 1;
        if ( !rf_vector3_is_exact_zero(plane_point + 6) )
          v35 = 2;
        v36 = rf_vector_distance_squared(plane_point, point);
        v39 = rf_geomod_cutter_resolve(*(_DWORD *)operation);
        v37 = *(float *)(v39 + 96) * *((float *)v34 + 7);
        v37 = v37 * v37;
        if ( v37 > (double)v36 )
        {
          rf_vector_subtract(point, out_vector, plane_point);
          rf_vector_normalize(out_vector);
          for ( k = 0; k < v35; ++k )
          {
            rf_vector3_default_construct_noop(normal);
            if ( k )
              rf_vector_copy(normal, v18, plane_point + 6);
            else
              rf_vector_copy(normal, v19, plane_point + 3);
            length = rf_vector_normalize_get_length(normal);
            length = length * length;
            for ( m = 0; m < v47; ++m )
            {
              if ( (rf_vector3_is_exact_zero(v40) || m) && (rf_vector3_is_exact_zero(v41) || m != 1) )
              {
                rf_vector3_default_construct_noop(destination);
                if ( m )
                  rf_vector_copy(destination, v16, (const float *)operation + 22);
                else
                  rf_vector_copy(destination, v17, (const float *)operation + 19);
                rf_vector_normalize(destination);
                if ( rf_vector_dot(normal, destination) >= 0.95 && rf_vector_dot(normal, out_vector) > 0.0 )
                {
                  rf_vector3_default_construct_noop(output);
                  rf_point_project_to_plane(output, point, normal, plane_point);
                  v7 = rf_vector_distance_squared(output, point);
                  if ( length > v7 )
                  {
                    if ( !m )
                    {
                      v8 = rf_vector_subtract(output, v15, point);
                      rf_vector_copy(v40, v14, v8);
                    }
                    if ( m == 1 )
                    {
                      v9 = rf_vector_subtract(output, v13, point);
                      rf_vector_copy(v41, v12, v9);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    rf_vector_accumulate((float *)operation + 2, v40);
    rf_vector_accumulate((float *)operation + 2, v41);
  }
  return 1;
}

