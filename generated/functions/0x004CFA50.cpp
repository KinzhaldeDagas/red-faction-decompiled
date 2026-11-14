// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CFA50 rf_projectile_advance_to_next_geometry_contact
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Cdecl(start3f, direction3f, INOUT contact68); returns binary32-rounded advance distance in x87 ST0. Sole recorded caller0x511F67 supplies normalized velocity and writes remaining
// distance to contact FLOAT+24 before call. Let T=original contact+24, D=F32(direction*T). Keeps ray(start,D), endpoint=start+D, initial segment bounds, and ONE shared solid-result
// fraction bound t=T (not1). Result count/other local payload is not otherwise initialized by its no-op constructor.
// Traverses type9 mover list head0x704BCC, sentinel0x704940, next+652; no inactive or object-ignore filter. Strict ordered AABB overlap tests CURRENT clipped segment bounds against
// mover+400/+412. Admitted mover ray uses localStart=inverseRotate(start-mover common position+60, common matrix+72), localDir=inverseRotate(D,same matrix). Its initial endpoint is
// localStart+localDir*CURRENT t: D already includes T, so before any hit this spans direction*T*T in local space, not simply direction*T. Calls face-list nearest-hit0x4D00E0 with
// same shared fraction bound and clips local endpoint inside delegate.
// Accepted mover hit writes contact fraction+24=t, normal+12=rotate(result normal,mover common matrix), scalar+32=0, mapped material+28 from face raw+48, linear
// velocity+36=mover+324, UID+48=mover handle+44, raw material+52, face pointer+60, DWORD+64=0. Leaves contact+56 untouched. Sets advance=F32(t*T), rebuilds WORLD endpoint=start+D*t
// and bounds for subsequent movers. Shared t is never reset per mover. Local endpoint extra scaling and global AABB pruning are both preserved native behavior.
// Then traverses world solid pointer array+144; each element's root+60 goes to tree helper0x4CFEB0 with ORIGINAL ray(start,D), CURRENT world endpoint, same INOUT result bound t.
// Accepted world hit writes same contact fields but normal unrotated, velocity zero, UID=-1. World helper clips endpoint on each accepted face; no separate bounds rebuild needed
// here. Contact count or liquid DWORD+56 is never written.
// After traversal, ALWAYS adds exact double0.019999999552965164 to advance with a final F32 store, writes contact point=start+direction*that biased advance, and returns it; even if
// no hit, point becomes start+direction*(T+0.02) while old normal/material/UID/face and fraction+24 stay unchanged. On a hit contact+24 retains t (not t*T or biased advance). No AL
// hit result, finite/zero/range check, rollback, or normalization of normal. Caller subsequently normalizes result normal even on miss and only publishes position when ordered
// remaining>returned advance.
double __cdecl rf_projectile_advance_to_next_geometry_contact(float *lhs, float *vector, float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  int first_dword; // eax
  float *v12; // eax
  float *v13; // eax
  float v15[3]; // [esp+8h] [ebp-1B0h] BYREF
  float v16[3]; // [esp+14h] [ebp-1A4h] BYREF
  int v17[3]; // [esp+20h] [ebp-198h] BYREF
  float v18[3]; // [esp+2Ch] [ebp-18Ch] BYREF
  float v19[3]; // [esp+38h] [ebp-180h] BYREF
  float v20[3]; // [esp+44h] [ebp-174h] BYREF
  float v21[3]; // [esp+50h] [ebp-168h] BYREF
  float v22[3]; // [esp+5Ch] [ebp-15Ch] BYREF
  float v23[3]; // [esp+68h] [ebp-150h] BYREF
  float v24[3]; // [esp+74h] [ebp-144h] BYREF
  float v25[3]; // [esp+80h] [ebp-138h] BYREF
  float v26[3]; // [esp+8Ch] [ebp-12Ch] BYREF
  float v27[3]; // [esp+98h] [ebp-120h] BYREF
  float v28[3]; // [esp+A4h] [ebp-114h] BYREF
  float v29[3]; // [esp+B0h] [ebp-108h] BYREF
  float out_vector[3]; // [esp+BCh] [ebp-FCh] BYREF
  float v31[3]; // [esp+C8h] [ebp-F0h] BYREF
  float sum_result[3]; // [esp+D4h] [ebp-E4h] BYREF
  float v33[3]; // [esp+E0h] [ebp-D8h] BYREF
  float scaled_result[3]; // [esp+ECh] [ebp-CCh] BYREF
  float copy_result[3]; // [esp+F8h] [ebp-C0h] BYREF
  int v36; // [esp+104h] [ebp-B4h]
  float v37[3]; // [esp+108h] [ebp-B0h] BYREF
  float v38[3]; // [esp+114h] [ebp-A4h] BYREF
  _BYTE v39[4]; // [esp+120h] [ebp-98h] BYREF
  float scalar; // [esp+124h] [ebp-94h]
  float v41[4]; // [esp+134h] [ebp-84h] BYREF
  int v42; // [esp+144h] [ebp-74h]
  float v43; // [esp+148h] [ebp-70h]
  float v44[3]; // [esp+14Ch] [ebp-6Ch] BYREF
  float destination[3]; // [esp+158h] [ebp-60h] BYREF
  float source[3]; // [esp+164h] [ebp-54h] BYREF
  float v47; // [esp+170h] [ebp-48h]
  _BYTE v48[12]; // [esp+174h] [ebp-44h] BYREF
  _BYTE v49[12]; // [esp+180h] [ebp-38h] BYREF
  float v50[3]; // [esp+18Ch] [ebp-2Ch] BYREF
  int j; // [esp+198h] [ebp-20h]
  float v52[3]; // [esp+19Ch] [ebp-1Ch] BYREF
  int i; // [esp+1A8h] [ebp-10h]
  float v54[3]; // [esp+1ACh] [ebp-Ch] BYREF

  v47 = a3[6];
  v43 = v47;
  rf_vector3_default_construct_noop(v54);
  rf_vector3_default_construct_noop(v52);
  rf_vector3_default_construct_noop(v49);
  rf_vector3_default_construct_noop(v48);
  rf_vector3_default_construct_noop(v50);
  rf_vector3_default_construct_noop(v44);
  rf_force_sample44_construct_vectors_noop((char *)destination);
  rf_solid_collision_result_construct_noop((int)v39);
  scalar = a3[6];
  rf_vector_copy(destination, copy_result, lhs);
  v3 = rf_vector_multiply_scalar(vector, scaled_result, a3[6]);
  rf_vector_copy(source, v33, v3);
  v4 = rf_vector_add(destination, sum_result, source);
  rf_vector_copy(v50, v31, v4);
  rf_segment_bounds_build(v54, v52, destination, v50);
  for ( i = unk_704BCC; (_UNKNOWN *)i != &unk_704940; i = *(_DWORD *)(i + 652) )
  {
    if ( rf_aabb_overlap_strict_ordered(v54, v52, (float *)(i + 400), (float *)(i + 412)) )
    {
      rf_force_sample44_construct_vectors_noop((char *)v37);
      v5 = rf_vector_subtract(lhs, out_vector, (const float *)(i + 60));
      rf_vector_copy(v37, v29, v5);
      rf_matrix3_inverse_rotate_vector(v37, (float *)(i + 72));
      rf_vector_copy(v38, v28, source);
      rf_matrix3_inverse_rotate_vector(v38, (float *)(i + 72));
      v6 = rf_vector_multiply_scalar(v38, v27, scalar);
      v7 = rf_vector_add(v37, v26, v6);
      rf_vector_copy(v44, v25, v7);
      if ( rf_solid_face_list_segment_nearest_hit(*(_DWORD *)(i + 660), (int)v37, v44, (int)v39) )
      {
        a3[6] = scalar;
        v8 = rf_matrix3_rotate_vector(v41, v24, (float *)(i + 72));
        rf_vector_copy(a3 + 3, v23, v8);
        a3[8] = 0.0;
        *((_DWORD *)a3 + 7) = rf_bitmap_material_to_index(*(_DWORD *)(v42 + 48));
        rf_vector_copy(a3 + 9, v22, (const float *)(i + 324));
        a3[12] = *(float *)(i + 44);
        a3[13] = *(float *)(v42 + 48);
        *((_DWORD *)a3 + 15) = v42;
        a3[16] = 0.0;
        v43 = scalar * v47;
        v9 = rf_vector_multiply_scalar(source, v21, scalar);
        v10 = rf_vector_add(destination, v20, v9);
        rf_vector_copy(v50, v19, v10);
        rf_segment_bounds_build(v54, v52, destination, v50);
      }
    }
  }
  for ( j = 0; ; ++j )
  {
    first_dword = rf_receiver_get_first_dword((void *)(rf_world_solid + 144));
    if ( j >= first_dword )
      break;
    v36 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 144), j);
    if ( rf_world_tree_segment_nearest_nonportal_hit(*(_DWORD *)(v36 + 60), (int)destination, v50, (int)v39) )
    {
      a3[6] = scalar;
      rf_vector_copy(a3 + 3, v18, v41);
      a3[8] = 0.0;
      *((_DWORD *)a3 + 7) = rf_bitmap_material_to_index(*(_DWORD *)(v42 + 48));
      rf_vector3_zero_return_destination(a3 + 9);
      a3[12] = NAN;
      a3[13] = *(float *)(v42 + 48);
      *((_DWORD *)a3 + 15) = v42;
      a3[16] = 0.0;
      v43 = scalar * v47;
    }
  }
  v43 = v43 + 0.01999999955296516;
  v12 = rf_vector_scale((float *)v17, v43, vector);
  v13 = rf_vector_add(lhs, v16, v12);
  rf_vector_copy(a3, v15, v13);
  return v43;
}

