// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C6740 rf_glass_shard_sweep_world
// UNREALRED VERIFIED [combat-particle-emission-20261104]: Glass liquid-entry splash call506E20 passes optional direction NULL, independently of the shard contact normal. Preserve authored inline source direction and native graph default RF+Y; do not supply the surface normal as an override.
// UNREALRED VERIFIED (2026-11-11; full recursive glass sweep and saved native state effects):
// Cdecl(shard,start,end,out20,signedDepth). Depth>=10 returnsAL0 BEFORE any output/owner writes; negative depth not separately clamped. Builds F32start/delta=end-start and bounds.
// Local result40 NOOP ctor then count0=0 ONLY; face/fraction/point/normal initially untouched. Loops attached owner pointers in current room104 array108; each uses owner+60 spatial
// root6B70. Every first-hit success copies face/fraction/point into output, shortens local delta to point-start and rebuilds bounds, remembersAL1. Thus later roots can replace with
// closer point on shortened segment, but within each tree first-hit traversal controls choice. Fractions remain RELATIVE to that root's current shortened delta, never rescaled to
// original segment; ties at t1 excluded.
// Then current room BYTE388 nonzero ->room face-list6A30; zero ->current room+60 tree6B70. Uses same shortened delta. A hit first tries portal crossing6D50; on transition immediately
// recurses(new local contact point,ORIGINAL end,out,depth+1), returns child AL directly. No EPS advance or rollback of bucket/owner/earlier output on recursion cap/failure.
// Transition may therefore discard remembered attached hit. No transition: nonliquid room branch copies current face/point/fraction and returns1. Liquid-room branch writes out.face
// BEFORE liquid predicate; liquid face==1 spawns VClip90B830 at contact with currentroom,sizeF32.2,optional directionNULL, then returns0 WITHOUT writing out.fraction/point from this
// hit, even if previous attached hit existed. Nonliquid face copies fraction/point and returns1. Main-room miss returns remembered attached-hit flag.
// Caller6370 false response moves FULL original predicted end, so liquid crossing/recursion failure can move through while retaining owner/bucket side effects. No
// world/room/root/finite/cycle guard, global face cache or full-output reset. Successful output is face,fraction,point first20B, normal derives face; candidate result.count remains0
// because search helpers never increment it. Existing splash optional-directionNULL finding preserved.
char __cdecl rf_glass_shard_sweep_world(int a1, float *rhs, float *lhs, float *a4, int a5)
{
  float *v5; // eax
  int first_dword; // eax
  int v7; // eax
  float *v8; // eax
  float v10[3]; // [esp+10h] [ebp-C0h] BYREF
  float v11[3]; // [esp+1Ch] [ebp-B4h] BYREF
  float v12[3]; // [esp+28h] [ebp-A8h] BYREF
  float v13[3]; // [esp+34h] [ebp-9Ch] BYREF
  float v14[3]; // [esp+40h] [ebp-90h] BYREF
  float v15[3]; // [esp+4Ch] [ebp-84h] BYREF
  float out_vector[3]; // [esp+58h] [ebp-78h] BYREF
  float copy_result[3]; // [esp+64h] [ebp-6Ch] BYREF
  float destination[3]; // [esp+70h] [ebp-60h] BYREF
  float v19[3]; // [esp+7Ch] [ebp-54h] BYREF
  float v20[3]; // [esp+88h] [ebp-48h] BYREF
  float v21[3]; // [esp+94h] [ebp-3Ch] BYREF
  int v22; // [esp+A0h] [ebp-30h] BYREF
  float v23; // [esp+A4h] [ebp-2Ch]
  float source[7]; // [esp+A8h] [ebp-28h] BYREF
  int v25; // [esp+C4h] [ebp-Ch]
  int i; // [esp+C8h] [ebp-8h]
  char v27; // [esp+CFh] [ebp-1h]

  v27 = 0;
  if ( a5 >= 10 )
    return 0;
  rf_vector3_default_construct_noop(v21);
  rf_vector3_default_construct_noop(v20);
  rf_force_sample44_construct_vectors_noop((char *)destination);
  rf_vector_copy(destination, copy_result, rhs);
  v5 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(v19, v15, v5);
  rf_segment_bounds_build(v21, v20, rhs, lhs);
  rf_solid_collision_result_construct_noop((int)&v22);
  v22 = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)(a1 + 104) + 108));
    if ( i >= first_dword )
      break;
    v7 = sub_552200((_DWORD *)(*(_DWORD *)(a1 + 104) + 108), i);
    if ( rf_glass_find_first_spatial_tree_segment_hit(
           *(_DWORD *)(*(_DWORD *)v7 + 60),
           (int)v21,
           (int)v20,
           (int)destination,
           (int)&v22) )
    {
      *(_DWORD *)a4 = v25;
      rf_vector_copy(a4 + 2, v14, source);
      a4[1] = v23;
      v8 = rf_vector_subtract(a4 + 2, v13, rhs);
      rf_vector_copy(v19, v12, v8);
      rf_segment_bounds_build(v21, v20, rhs, a4 + 2);
      v27 = 1;
    }
  }
  if ( !*(_BYTE *)(*(_DWORD *)(a1 + 104) + 388) )
  {
    if ( rf_glass_find_first_spatial_tree_segment_hit(
           *(_DWORD *)(*(_DWORD *)(a1 + 104) + 60),
           (int)v21,
           (int)v20,
           (int)destination,
           (int)&v22) )
    {
      if ( rf_glass_shard_cross_solid_transition(a1, v25) )
        return rf_glass_shard_sweep_world(a1, source, (int)lhs, (int)a4, a5 + 1);
      *(_DWORD *)a4 = v25;
      rf_vector_copy(a4 + 2, v10, source);
      a4[1] = v23;
      return 1;
    }
    return v27;
  }
  if ( !rf_glass_find_first_room_face_segment_hit(
          *(_DWORD *)(a1 + 104),
          (int)v21,
          (int)v20,
          (int)destination,
          (int)&v22) )
    return v27;
  if ( rf_glass_shard_cross_solid_transition(a1, v25) )
    return rf_glass_shard_sweep_world(a1, source, (int)lhs, (int)a4, a5 + 1);
  *(_DWORD *)a4 = v25;
  if ( rf_face_is_liquid((_DWORD *)(*(_DWORD *)a4 + 40)) )
  {
    rf_vclip_spawn_runtime_effect(unk_90B830, *(_DWORD *)(a1 + 104), 0, (int)source, 0.2, -1, 0, 1);
    return 0;
  }
  else
  {
    a4[1] = v23;
    rf_vector_copy(a4 + 2, v11, source);
    return 1;
  }
}

