// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00484090 rf_geomod_debris_subdivide
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl drains active44-byte work FIFO0x6FDD18; initializes five static scratch guard bits with no-op vector/matrix constructors. One split-attempt counter starts0 for the ENTIRE
// call, not per piece. Pop current head logically by processing it until spawn/requeue. Record solid+8 original radius R=FLOAT solid+96; aspect A=FLOAT record+36, maximum extent
// E=FLOAT+40. Spawn final debris and recycle record to free tail0x6FF4D0 when ordered R<1.5, OR no ordered A>3 AND no ordered E/A>10, OR split counter>=10. Radius NaN passes the
// first gate; quotient equality/unordered does not request a split. No A-zero or finite guard.
// Split attempt increments budget BEFORE creating a slab box with width/height F32(E+E), thickness binary32 0.2, subdivision counts0. Samples slab normal in cone min-dot binary32
// 0.95 around measured major axis+24, builds orientation, samples offset scalar between F32(-E*double0.1000000014901161) and F32(E*same), then offset=ORIGINAL measured axis*scalar
// (not jittered slab normal). Reverses source solid faces, runs synchronous mode1 Boolean with slab and offset/orientation, reverses faces back, deletes slab when nonnull. No own
// cutter allocation/Boolean success check before classification. Classifies all debris components without terrain eligibility/largest-shell policy, unlinks current work record from
// active list, then extracts labels1..N-1, leaving label0 in source.
// Each extracted child is recentered; admits radius child<=original R OR unordered. Larger ordered child is destroyed. Admitted child takes first free work record; if none, destroys
// child copy. Accepted child stores solid, position=old record position+recenter delta, measures, appends FIFO. This happens after topology mutation and never rolls back world/source
// geometry. Remaining source is recentered too: when its radius<=original R OR unordered, accumulates recenter delta into old work position, remeasures, requeues same record. When
// remaining source radius is ordered GREATER than original R, destroys solid but DOES NOT return its now-unlinked work record to free list; it is lost from both lists with stale
// solid pointer. Do not add a recycle edge absent from native code.
// Final spawn delegates rf_geomod_debris_spawn(solid,position), then unlinks current work and appends free tail, without clearing stale solid/payload fields. Newly requeued
// children/remainder are processed later in this same call. Once ten attempts exhausted, all later pieces spawn without more splitting. Return EAX is incidental branch-dependent
// pointer/register; no Boolean success contract.
char *rf_geomod_debris_subdivide()
{
  char *result; // eax
  float *v1; // eax
  float *v2; // eax
  float v3; // [esp+8h] [ebp-B8h] BYREF
  float v4; // [esp+Ch] [ebp-B4h]
  float v5; // [esp+10h] [ebp-B0h]
  float scalar; // [esp+14h] [ebp-ACh]
  char *v7; // [esp+1Ch] [ebp-A4h]
  char *v8; // [esp+20h] [ebp-A0h]
  char *v9; // [esp+24h] [ebp-9Ch]
  char *v10; // [esp+28h] [ebp-98h]
  float v11; // [esp+2Ch] [ebp-94h]
  float v12; // [esp+30h] [ebp-90h]
  float v13; // [esp+34h] [ebp-8Ch]
  float v14; // [esp+38h] [ebp-88h]
  char *v15; // [esp+3Ch] [ebp-84h]
  char *v16; // [esp+40h] [ebp-80h]
  float v17[3]; // [esp+44h] [ebp-7Ch] BYREF
  float sum_result[4]; // [esp+50h] [ebp-70h] BYREF
  char *v19; // [esp+60h] [ebp-60h]
  float *v20; // [esp+64h] [ebp-5Ch]
  char *v21; // [esp+68h] [ebp-58h]
  int v22; // [esp+6Ch] [ebp-54h]
  char *v23; // [esp+70h] [ebp-50h]
  float copy_result[3]; // [esp+74h] [ebp-4Ch] BYREF
  float scaled_result[4]; // [esp+80h] [ebp-40h] BYREF
  float *v26; // [esp+90h] [ebp-30h]
  float *v27; // [esp+94h] [ebp-2Ch]
  int v28; // [esp+98h] [ebp-28h]
  int v29; // [esp+9Ch] [ebp-24h]
  int v30; // [esp+A0h] [ebp-20h]
  float v31; // [esp+A4h] [ebp-1Ch]
  int v32; // [esp+A8h] [ebp-18h]
  int i; // [esp+ACh] [ebp-14h]
  char v34; // [esp+B3h] [ebp-Dh]
  int v35; // [esp+BCh] [ebp-4h]

  if ( (rf_geomod_debris_split_scratch_init_mask[0] & 1) == 0 )
  {
    rf_geomod_debris_split_scratch_init_mask[0] |= 1u;
    rf_vector3_default_construct_noop(&rf_geomod_debris_recenter_delta);
    v35 = -1;
  }
  if ( (rf_geomod_debris_split_scratch_init_mask[0] & 2) == 0 )
  {
    rf_geomod_debris_split_scratch_init_mask[0] |= 2u;
    rf_vector3_default_construct_noop(&unk_6FF868);
    v35 = -1;
  }
  if ( (rf_geomod_debris_split_scratch_init_mask[0] & 4) == 0 )
  {
    rf_geomod_debris_split_scratch_init_mask[0] |= 4u;
    rf_vector3_default_construct_noop(&rf_geomod_debris_split_jittered_axis);
    v35 = -1;
  }
  result = (char *)(rf_geomod_debris_split_scratch_init_mask[0] & 8);
  if ( (rf_geomod_debris_split_scratch_init_mask[0] & 8) == 0 )
  {
    rf_geomod_debris_split_scratch_init_mask[0] |= 8u;
    result = rf_matrix3_construct((char *)rf_geomod_debris_split_orientation);
    v35 = -1;
  }
  if ( (rf_geomod_debris_split_scratch_init_mask[0] & 0x10) == 0 )
  {
    rf_geomod_debris_split_scratch_init_mask[0] |= 0x10u;
    result = (char *)rf_vector3_default_construct_noop(&rf_geomod_debris_split_offset);
    v35 = -1;
  }
  v34 = 1;
  v32 = 0;
  while ( (_DWORD *)rf_geomod_debris_work_active_head != &rf_geomod_debris_work_active_head )
  {
    v30 = rf_geomod_debris_work_active_head;
    v31 = *(float *)(*(_DWORD *)(rf_geomod_debris_work_active_head + 8) + 96);
    if ( v31 < 1.5 || *(float *)(v30 + 36) <= 3.0 && *(float *)(v30 + 40) / *(float *)(v30 + 36) <= 10.0 || v32 >= 10 )
    {
      rf_geomod_debris_spawn(*(_DWORD *)(v30 + 8), (float *)(v30 + 12));
      **(_DWORD **)(v30 + 4) = *(_DWORD *)v30;
      *(_DWORD *)(*(_DWORD *)v30 + 4) = *(_DWORD *)(v30 + 4);
      *(_DWORD *)v30 = 0;
      *(_DWORD *)(v30 + 4) = 0;
      *(_DWORD *)(v30 + 4) = rf_geomod_debris_work_free_tail;
      *(_DWORD *)v30 = &rf_geomod_debris_work_free_head;
      *rf_geomod_debris_work_free_tail = v30;
      rf_geomod_debris_work_free_tail = v30;
      result = nullptr;
    }
    else
    {
      ++v32;
      scalar = 0.0;
      v5 = 0.0;
      v4 = 0.0;
      v3 = 0.2;
      v14 = *(float *)(v30 + 40) + *(float *)(v30 + 40);
      v13 = *(float *)(v30 + 40) + *(float *)(v30 + 40);
      v28 = (int)rf_solid_gridded_box_create(v13, v14, 0.2, 0, 0, 0);
      scalar = 0.94999999;
      LODWORD(scaled_result[3]) = &v3;
      rf_vector3_copy_return_destination(&v3, (float *)(v30 + 24));
      rf_random_unit_vector_in_cone(&rf_geomod_debris_split_jittered_axis, v3, v4, v5, scalar);
      rf_orientation_matrix_from_direction(
        rf_geomod_debris_split_orientation,
        (int)&rf_geomod_debris_split_jittered_axis);
      v12 = *(float *)(v30 + 40) * 0.1000000014901161;
      scalar = v12;
      v11 = -*(float *)(v30 + 40) * 0.1000000014901161;
      scalar = rf_random_float_range(v11, v12);
      v1 = rf_vector_multiply_scalar((const float *)(v30 + 24), scaled_result, scalar);
      rf_vector_copy(&rf_geomod_debris_split_offset, copy_result, v1);
      rf_solid_reverse_all_faces(*(_DWORD *)(v30 + 8));
      rf_geomod_boolean_run_synchronous(
        *(_DWORD *)(v30 + 8),
        v28,
        1,
        0,
        (int)&rf_geomod_debris_split_offset,
        (int)rf_geomod_debris_split_orientation,
        0,
        0,
        0.0,
        0,
        0,
        0,
        0);
      rf_solid_reverse_all_faces(*(_DWORD *)(v30 + 8));
      v22 = v28;
      v23 = (char *)v28;
      if ( v28 )
        v10 = rf_solid_destroy(v23, 1);
      else
        v10 = nullptr;
      v29 = rf_geomod_debris_split_components_classify(*(_DWORD *)(v30 + 8));
      **(_DWORD **)(v30 + 4) = *(_DWORD *)v30;
      *(_DWORD *)(*(_DWORD *)v30 + 4) = *(_DWORD *)(v30 + 4);
      *(_DWORD *)v30 = 0;
      *(_DWORD *)(v30 + 4) = 0;
      for ( i = 1; i < v29; ++i )
      {
        v26 = (float *)rf_geomod_component_extract(*(char **)(v30 + 8), i);
        rf_geomod_component_recenter(v26, (int)&rf_geomod_debris_recenter_delta);
        if ( v31 >= (double)v26[24] )
        {
          if ( rf_geomod_debris_work_free_head == &rf_geomod_debris_work_free_head )
          {
            LODWORD(sum_result[3]) = v26;
            v19 = (char *)v26;
            if ( v26 )
              v8 = rf_solid_destroy(v19, 1);
            else
              v8 = nullptr;
          }
          else
          {
            v27 = (float *)rf_geomod_debris_work_free_head;
            *(_DWORD *)rf_geomod_debris_work_free_head[1] = *rf_geomod_debris_work_free_head;
            *(float *)(*(_DWORD *)v27 + 4) = v27[1];
            *v27 = 0.0;
            v27[1] = 0.0;
            *((_DWORD *)v27 + 2) = v26;
            v2 = rf_vector_add((const float *)(v30 + 12), sum_result, &rf_geomod_debris_recenter_delta);
            rf_vector_copy(v27 + 3, v17, v2);
            rf_geomod_debris_work_measure((int)v27);
            rf_geomod_debris_work_enqueue_fifo((int)v27);
          }
        }
        else
        {
          v20 = v26;
          v21 = (char *)v26;
          if ( v26 )
            v9 = rf_solid_destroy(v21, 1);
          else
            v9 = nullptr;
        }
      }
      rf_geomod_component_recenter(*(float **)(v30 + 8), (int)&rf_geomod_debris_recenter_delta);
      if ( v31 >= (double)*(float *)(*(_DWORD *)(v30 + 8) + 96) )
      {
        rf_vector_accumulate((float *)(v30 + 12), &rf_geomod_debris_recenter_delta);
        rf_geomod_debris_work_measure(v30);
        result = (char *)rf_geomod_debris_work_enqueue_fifo(v30);
      }
      else
      {
        result = *(char **)(v30 + 8);
        v15 = result;
        v16 = result;
        if ( result )
        {
          result = rf_solid_destroy(v16, 1);
          v7 = result;
        }
        else
        {
          v7 = nullptr;
        }
      }
    }
  }
  return result;
}

