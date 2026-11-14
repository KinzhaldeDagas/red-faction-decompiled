// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D98A0 rf_object_snap_down_using_physics_shape_sweep
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl object pointer. Constructs collision-result vector members (constructor does not zero scalar fields), explicitly sets result fraction+24=1. Copies object position60 into start/end, raises start Y by double0.25, lowers end Y by double2. Sweeps object physics shape at+136 using4D13C0. Any nonzero AL hit: computes start+(end-start)*returned fraction, adds double0.05000000074505806 to Y, calls thiscall object position setter4BC330 (ECX object, stack vector). No hit leaves object unchanged and returns0; hit forwards setter EAX. No own NULL, hit-fraction clamp, room reassignment or spawn-height validation.
int __cdecl rf_object_snap_down_using_physics_shape_sweep(int a1)
{
  int result; // eax
  float *v2; // eax
  float *v3; // eax
  float scalar; // [esp+0h] [ebp-8Ch]
  float scaled_result[3]; // [esp+4h] [ebp-88h] BYREF
  float out_vector[3]; // [esp+10h] [ebp-7Ch] BYREF
  float sum_result; // [esp+1Ch] [ebp-70h] BYREF
  float v8; // [esp+20h] [ebp-6Ch]
  float lhs; // [esp+28h] [ebp-64h] BYREF
  float v10; // [esp+2Ch] [ebp-60h]
  float v11[6]; // [esp+34h] [ebp-58h] BYREF
  float v12; // [esp+4Ch] [ebp-40h]
  float rhs; // [esp+80h] [ebp-Ch] BYREF
  float v14; // [esp+84h] [ebp-8h]

  rf_physics_hit_record_construct_noop((char *)v11);
  v12 = 1.0;
  rf_vector3_copy_return_destination(&rhs, (float *)(a1 + 60));
  rf_vector3_copy_return_destination(&lhs, (float *)(a1 + 60));
  v14 = v14 + 0.25;
  v10 = v10 - 2.0;
  result = (unsigned __int8)rf_physics_shape_sweep_movers_and_static_world(&rhs, &lhs, a1 + 136, v11);
  if ( (_BYTE)result )
  {
    scalar = v12;
    v2 = rf_vector_subtract(&lhs, out_vector, &rhs);
    v3 = rf_vector_multiply_scalar(v2, scaled_result, scalar);
    rf_vector_add(&rhs, &sum_result, v3);
    v8 = v8 + 0.05000000074505806;
    return rf_object_publish_position_and_bounds(a1, &sum_result);
  }
  return result;
}

