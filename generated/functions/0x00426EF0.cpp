// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00426EF0 rf_entity_update_two_node_rotation_overrides
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity,required character runtime,LOWBYTE rampIn), FLOAT32 weight returned through ST0 despite double type. No own
// pointer/index/record-distinctness checks. Node indices come from MODEL-INFO pointer ENTITY+668 DWORD+5080/+5084, NOT the class pointer+660 tested by caller426890. Precompute
// records runtime+5012+48*index with native32-bit arithmetic, even for negative indices. Bias startsFLOAT0. If multiplayer BYTE any nonzero, signed entity5248>=0 loads row DWORD
// from77D768+320*slot; only signed selected primary676>=0 and row>=0 then bias=round32(FLOAT681E84+FLOAT[68495C+5396*row+4*primary]); no upper bounds or resource fallback. Add
// current frameDeltaSeconds to entity FLOAT5220 and roundFLOAT32; no own phase reset. Let t be stored time. TEST AH1 treats t<DOUBLE0.75 OR UNORDERED as division branch: nonzero
// rampIn gives round32(t/0.75), zero rampIn gives round32(1-t/0.75). Ordered t>=0.75 saturates to1/0 respectively. Negative time is not lower-clamped; NaN propagates through division
// branch. Process first node completely before second. For each, clear record BYTE+40 BEFORE585C50(runtime,outAffine48,current index), which may rebuild pose/cache. Extract its
// nine-float rotation. Once before first node, form u=5590A0(entity vector2040,COMMON matrix72), then per-node local=5590A0(u,resolvedRotation); row-dot helper rounds each result
// componentFLOAT32, and the same stored u is reused for second node. Let local Y=y,Z=z; only ORDERED z==0 sets raw angle0, otherwise raw=round32(atan(round32(y/z))) using
// float-rounded43C8B0/43C8D0, including unordered z. With P=DOUBLE3.1415927410125732: first raw adds P only for ordered y>0,z<0, subtracts P only for ordered y<0,z<0; each correction
// roundsFLOAT32, then base1=round32(corrected*DOUBLE0.5). Second raw instead adds P for ordered y>0,z<0, and uses round32(P-raw) for ordered y<0,z<0, with NO half-angle. Zero Y or
// unordered sign tests receive neither quadrant adjustment; do not replace this with atan2. First appliedAngle=round32(bias*P/DOUBLE180*DOUBLE0.5+base1);
// second=round32(bias*P/DOUBLE180+base2), with x87 arithmetic until each final store. BOTH are computed BEFORE local base-angle clamping. Local base clamp afterwards has no further
// consumer. Applied angles clamp only ordered above H=0.44999998807907104 or below L=-0.785398006439209; equality/NaN preserved.55C330 rotates resolved up row around right and
// recomputes forward, without own basis normalization. Copy rotated nine-float matrix to record+4; weight to FLOAT+44; ALWAYS set BYTE+40=1, even weight0/NaN; decrement WORD+2 then
// WORD+0 modulo65536. Resolver/first-record effects survive second-node failure; equal indices are not deduplicated and second pass can overwrite first. Return final stored weight
// unchanged in ST0; no success Boolean, timer arm, owner authority/death gate, finite guard or rollback.
double __cdecl rf_entity_update_two_node_rotation_overrides(int a1, int a2, char a3)
{
  void *v3; // eax
  float *v4; // eax
  float v6; // [esp+4h] [ebp-E4h]
  float v7; // [esp+8h] [ebp-E0h]
  float copy_result[3]; // [esp+Ch] [ebp-DCh] BYREF
  float v9[3]; // [esp+18h] [ebp-D0h] BYREF
  _BYTE v10[48]; // [esp+24h] [ebp-C4h] BYREF
  int v11; // [esp+54h] [ebp-94h]
  float v12[9]; // [esp+58h] [ebp-90h] BYREF
  float v13; // [esp+7Ch] [ebp-6Ch]
  float v14; // [esp+80h] [ebp-68h]
  float v15; // [esp+84h] [ebp-64h]
  int v16; // [esp+88h] [ebp-60h]
  float v17[3]; // [esp+8Ch] [ebp-5Ch] BYREF
  int v18; // [esp+98h] [ebp-50h]
  _BYTE v19[12]; // [esp+9Ch] [ebp-4Ch] BYREF
  float v20[12]; // [esp+A8h] [ebp-40h] BYREF
  float destination; // [esp+D8h] [ebp-10h] BYREF
  float v22; // [esp+DCh] [ebp-Ch]
  float v23; // [esp+E0h] [ebp-8h]
  float v24; // [esp+E4h] [ebp-4h]

  v18 = a2 + 48 * *(_DWORD *)(*(_DWORD *)(a1 + 668) + 5080) + 5012;
  v16 = a2 + 48 * *(_DWORD *)(*(_DWORD *)(a1 + 668) + 5084) + 5012;
  rf_vector3_default_construct_noop(v19);
  rf_matrix3_construct((char *)v12);
  v13 = 0.0;
  if ( rf_multiplayer_runtime_mode )
  {
    if ( *(int *)(a1 + 5248) > -1 )
    {
      v11 = unk_77D768[80 * *(_DWORD *)(a1 + 5248)];
      if ( *(int *)(a1 + 676) > -1 && v11 > -1 )
        v13 = unk_681E84 + flt_68492C[1349 * v11 + 12 + *(_DWORD *)(a1 + 676)];
    }
  }
  *(float *)(a1 + 5220) = *(float *)(a1 + 5220) + rf_frame_delta_seconds;
  if ( a3 )
  {
    if ( *(float *)(a1 + 5220) < 0.75 )
      v24 = *(float *)(a1 + 5220) / 0.75;
    else
      v24 = 1.0;
  }
  else if ( *(float *)(a1 + 5220) < 0.75 )
  {
    v24 = 1.0 - *(float *)(a1 + 5220) / 0.75;
  }
  else
  {
    v24 = 0.0;
  }
  *(_BYTE *)(v18 + 40) = 0;
  rf_character_instance_resolve_node_transform(a2, v20, *(_DWORD *)(*(_DWORD *)(a1 + 668) + 5080));
  rf_affine48_copy_rotation_return_self(v20, v12);
  rf_vector3_transform_by_matrix_rows((float *)(a1 + 2040), v17, (float *)(a1 + 72));
  rf_vector3_transform_by_matrix_rows(v17, &destination, v12);
  if ( v23 == 0.0 )
  {
    v15 = 0.0;
  }
  else
  {
    v7 = v22 / v23;
    v15 = rf_atan_float_wrapper(v7);
  }
  if ( v22 <= 0.0 || v23 >= 0.0 )
  {
    if ( v22 < 0.0 && v23 < 0.0 )
      v15 = v15 - 3.141592741012573;
  }
  else
  {
    v15 = v15 + 3.141592741012573;
  }
  v15 = v15 * 0.5;
  v14 = v13 * 3.141592741012573 / 180.0 * 0.5 + v15;
  if ( v15 <= 0.449999988079071 )
  {
    if ( v15 < -0.785398006439209 )
      v15 = -0.78539801;
  }
  else
  {
    v15 = 0.44999999;
  }
  if ( v14 <= 0.449999988079071 )
  {
    if ( v14 < -0.785398006439209 )
      v14 = -0.78539801;
  }
  else
  {
    v14 = 0.44999999;
  }
  rf_matrix3_rotate_up_about_right_axis(v12, v14);
  rf_matrix3_copy((float *)(v18 + 4), v12);
  *(float *)(v18 + 44) = v24;
  *(_BYTE *)(v18 + 40) = 1;
  --*(_WORD *)(v18 + 2);
  --*(_WORD *)v18;
  *(_BYTE *)(v16 + 40) = 0;
  v3 = rf_character_instance_resolve_node_transform(a2, v10, *(_DWORD *)(*(_DWORD *)(a1 + 668) + 5084));
  rf_fixed_block48_copy(v20, v3);
  rf_affine48_copy_rotation_return_self(v20, v12);
  v4 = rf_vector3_transform_by_matrix_rows(v17, v9, v12);
  rf_vector_copy(&destination, copy_result, v4);
  if ( v23 == 0.0 )
  {
    v15 = 0.0;
  }
  else
  {
    v6 = v22 / v23;
    v15 = rf_atan_float_wrapper(v6);
  }
  if ( v22 <= 0.0 || v23 >= 0.0 )
  {
    if ( v22 < 0.0 && v23 < 0.0 )
      v15 = 3.141592741012573 - v15;
  }
  else
  {
    v15 = v15 + 3.141592741012573;
  }
  v14 = v13 * 3.141592741012573 / 180.0 + v15;
  if ( v15 <= 0.449999988079071 )
  {
    if ( v15 < -0.785398006439209 )
      v15 = -0.78539801;
  }
  else
  {
    v15 = 0.44999999;
  }
  if ( v14 <= 0.449999988079071 )
  {
    if ( v14 < -0.785398006439209 )
      v14 = -0.78539801;
  }
  else
  {
    v14 = 0.44999999;
  }
  rf_matrix3_rotate_up_about_right_axis(v12, v14);
  rf_matrix3_copy((float *)(v16 + 4), v12);
  *(float *)(v16 + 44) = v24;
  *(_BYTE *)(v16 + 40) = 1;
  --*(_WORD *)(v16 + 2);
  --*(_WORD *)v16;
  return v24;
}

