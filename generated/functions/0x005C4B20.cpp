// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C4B20 rf_renderer_apply_room_clip_aperture
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl low BYTE reset,left,top,right,bottom floats;caller pops20 bytes. ANY nonzero reset delegates full world-plane rebuild5C4540 and ignores bounds,not just reset1. Zero reset calls screen-to-world-ray helper for TL,TR,BL,BR,each producing origin+direction; adds each pair to get endpoint,uses common point from global18CD5E8. Replaces4 fixed28-byte records via5C5960 with BY-VALUE3-vectors:18CD3C8 outcode4 uses(common,BL,TL);18CD3E4 outcode8(common,TR,BR);18CD400 outcode10h(common,BR,BL);18CD41C outcode20h(common,TL,TR). Initial no-op vector-prefix constructors do not clear temporaries; ray helper supplies origin/direction. Does NOT reset plane count,near/far/custom records,projection
// matrices or fog on aperture branch. No bounds sorting/clamping,degeneracy/pointer/finite checks,viewport conversion or allocation in this body. Existing repeatable summary retained.
void __cdecl rf_renderer_apply_room_clip_aperture(char a1, float a2, float a3, float a4, float a5)
{
  float v5; // [esp-1Ch] [ebp-F0h] BYREF
  float v6; // [esp-18h] [ebp-ECh]
  float v7; // [esp-14h] [ebp-E8h]
  float v8; // [esp-10h] [ebp-E4h] BYREF
  float v9; // [esp-Ch] [ebp-E0h]
  float v10; // [esp-8h] [ebp-DCh]
  float v11; // [esp-4h] [ebp-D8h] BYREF
  float v12; // [esp+0h] [ebp-D4h]
  float v13; // [esp+4h] [ebp-D0h]
  float v14[3]; // [esp+38h] [ebp-9Ch] BYREF
  float v15[3]; // [esp+44h] [ebp-90h] BYREF
  float sum_result[3]; // [esp+50h] [ebp-84h] BYREF
  float lhs[3]; // [esp+5Ch] [ebp-78h] BYREF
  float rhs[3]; // [esp+68h] [ebp-6Ch] BYREF
  float v19[3]; // [esp+74h] [ebp-60h] BYREF
  float v20[3]; // [esp+80h] [ebp-54h] BYREF
  float v21[3]; // [esp+8Ch] [ebp-48h] BYREF
  float v22[3]; // [esp+98h] [ebp-3Ch] BYREF
  float v23[3]; // [esp+A4h] [ebp-30h] BYREF
  float v24[3]; // [esp+B0h] [ebp-24h] BYREF
  float v25[3]; // [esp+BCh] [ebp-18h] BYREF
  float v26[3]; // [esp+C8h] [ebp-Ch] BYREF

  if ( a1 )
  {
    rf_renderer_rebuild_world_clip_planes();
  }
  else
  {
    rf_force_sample44_construct_vectors_noop((char *)lhs);
    rf_force_sample44_construct_vectors_noop((char *)v19);
    rf_force_sample44_construct_vectors_noop((char *)v24);
    rf_force_sample44_construct_vectors_noop((char *)v21);
    rf_renderer_screen_point_to_world_ray(lhs, a2, a3);
    rf_renderer_screen_point_to_world_ray(v24, a4, a3);
    rf_renderer_screen_point_to_world_ray(v19, a2, a5);
    rf_renderer_screen_point_to_world_ray(v21, a4, a5);
    rf_vector3_copy_return_destination(v15, &flt_18CD5E8);
    rf_vector_add(lhs, sum_result, rhs);
    rf_vector_add(v24, v23, v25);
    rf_vector_add(v19, v14, v20);
    rf_vector_add(v21, v26, v22);
    rf_vector3_copy_return_destination(&v11, sum_result);
    rf_vector3_copy_return_destination(&v8, v14);
    rf_vector3_copy_return_destination(&v5, v15);
    rf_clip_plane_record_from_three_points(byte_18CD3C8, 4u, v5, v6, v7, v8, v9, v10, v11, v12, v13);
    rf_vector3_copy_return_destination(&v11, v26);
    rf_vector3_copy_return_destination(&v8, v23);
    rf_vector3_copy_return_destination(&v5, v15);
    rf_clip_plane_record_from_three_points(&unk_18CD3E4, 8u, v5, v6, v7, v8, v9, v10, v11, v12, v13);
    rf_vector3_copy_return_destination(&v11, v14);
    rf_vector3_copy_return_destination(&v8, v26);
    rf_vector3_copy_return_destination(&v5, v15);
    rf_clip_plane_record_from_three_points(&unk_18CD400, 0x10u, v5, v6, v7, v8, v9, v10, v11, v12, v13);
    rf_vector3_copy_return_destination(&v11, v23);
    rf_vector3_copy_return_destination(&v8, sum_result);
    rf_vector3_copy_return_destination(&v5, v15);
    rf_clip_plane_record_from_three_points(&unk_18CD41C, 0x20u, v5, v6, v7, v8, v9, v10, v11, v12, v13);
  }
}

