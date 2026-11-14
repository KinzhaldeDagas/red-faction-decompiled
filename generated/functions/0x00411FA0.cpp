// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411FA0 rf_camera_slot_enter_state2_and_detach_nonnegative_handle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required slot), returns explicit AL1 on every normal path. Capture camera slotDWORD0 BEFORE calling4119E0(slot) under OLD
// state; ignore update result, subsequent record writes keep captured camera. Write slot stateDWORD2=2, obtain movement descriptor445740(13) and store camera+2136 (unloaded13 falls
// back0 and updates global selected descriptor index). SIGNED camera handle+512>-1 is the ONLY admission to ENTITY resolver433EE0. Thus negative full handles INCLUDING values below-1
// are skipped AND PRESERVED, despite identifier resolver otherwise supporting such bit patterns. For admitted nonnegative handle: resolver result is only a presence test; no
// resolved-entity pose is read. If valid, snapshot camera OWN position+60 to vector+228 and common orientation+72 to matrix+252; extract retained orientation+2016 using55AC10(ECX
// matrix, outPitch=&localX,outBank=&localZ,outHeading=&localY), yielding contiguous input(Pitch,Heading,Bank).445990(localOut,camera,input) consumes descriptor selectors and copied
// camera matrix+252, result assigned vector+2148;445B80(localOut,camera,input) row-transforms/filter-selects axes, result assigned vector+2172. Both helper results copied with
// distinct hidden vector-assignment outputs. Regardless of resolver success, admitted nonnegative handle then becomes-1. Failed resolution retains those pose/angle vectors but still
// changes slot state, descriptor, handle and final flags. Finally OR camera DWORD+424 mask0x00800000 on every path and returnAL1. No reciprocal owner+2252 update, no own
// pointer/descriptor/finite validation or rollback; no relation inferred to generic AI attachment from camera+512 alone.
char __cdecl rf_camera_slot_enter_state2_and_detach_nonnegative_handle(int *a1)
{
  float *v1; // eax
  float *v2; // eax
  float v4[3]; // [esp+0h] [ebp-50h] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-44h] BYREF
  float v6[3]; // [esp+18h] [ebp-38h] BYREF
  float v7[3]; // [esp+24h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+30h] [ebp-20h] BYREF
  float input_vector; // [esp+3Ch] [ebp-14h] BYREF
  float v10; // [esp+40h] [ebp-10h] BYREF
  float v11; // [esp+44h] [ebp-Ch] BYREF
  int entity; // [esp+4Ch] [ebp-4h]

  entity = *a1;
  rf_camera_update_slot_by_numeric_state((void **)a1);
  a1[2] = 2;
  *(_DWORD *)(entity + 2136) = sub_445740(0xDu);
  if ( *(int *)(entity + 512) > -1 )
  {
    if ( rf_entity_resolve_handle(*(_DWORD *)(entity + 512)) )
    {
      rf_vector_copy((float *)(entity + 228), copy_result, (const float *)(entity + 60));
      rf_matrix3_copy((float *)(entity + 252), (const float *)(entity + 72));
      rf_vector3_default_construct_noop(&input_vector);
      rf_matrix3_extract_euler_angles_retail((float *)(entity + 2016), &input_vector, &v11, &v10);
      v1 = rf_entity_filter_vector_by_descriptor_axis_modes(v7, entity, &input_vector);
      rf_vector_copy((float *)(entity + 2148), v6, v1);
      v2 = rf_entity_rotate_then_filter_view_offset_axes(out_vector, entity, &input_vector);
      rf_vector_copy((float *)(entity + 2172), v4, v2);
    }
    *(_DWORD *)(entity + 512) = -1;
  }
  *(_DWORD *)(entity + 424) |= (unsigned int)&unk_800000;
  return 1;
}

