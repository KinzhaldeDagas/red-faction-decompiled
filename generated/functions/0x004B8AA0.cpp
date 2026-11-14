// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B8AA0 rf_object_apply_parent_attachment_transform
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): Two cdecl pointers (child,parent); null parent returns without touching child. Child signed DWORD+516>=0 selects VMesh prop transform: parent
// model+128, child prop index, parent matrix+2016 if use-classification helper returns EXACT4 else parent matrix+72, parent position+60, output matrix and position; exactly six stack
// arguments. Negative index instead transforms child local vector+520 by parent matrix+252, adds parent vector+240, and composes child local matrix+532 with inverse(parent
// matrix+288) using the existing matrix helpers. Publishes computed position through4B8BB9 setter, updating position/physics bounds. Unless child common flags+124 bit0x100 is set,
// copies computed matrix to child+72,+252,+288; the flag suppresses orientation copies only, not position publication. Child type DWORD+36==0 additionally calls420870 to refresh
// retained entity reference point. No own parent-model/prop-index validation.
void __cdecl rf_object_apply_parent_attachment_transform(_DWORD *a1, int a2)
{
  float *v2; // eax
  float *v3; // eax
  const float *v4; // eax
  float *v5; // eax
  float v6[9]; // [esp+0h] [ebp-9Ch] BYREF
  _BYTE v7[36]; // [esp+24h] [ebp-78h] BYREF
  float copy_result[3]; // [esp+48h] [ebp-54h] BYREF
  float sum_result[3]; // [esp+54h] [ebp-48h] BYREF
  float v10[3]; // [esp+60h] [ebp-3Ch] BYREF
  float destination[3]; // [esp+6Ch] [ebp-30h] BYREF
  float v12[9]; // [esp+78h] [ebp-24h] BYREF

  if ( a2 )
  {
    rf_vector3_default_construct_noop(destination);
    rf_matrix3_construct((char *)v12);
    if ( (int)a1[129] >= 0 )
    {
      if ( rf_object_get_use_classification((_DWORD *)a2) == 4 )
        rf_vmesh_compose_prop_world_transform(
          *(_DWORD *)(a2 + 128),
          a1[129],
          (float *)(a2 + 2016),
          a2 + 60,
          (int)v12,
          destination);
      else
        rf_vmesh_compose_prop_world_transform(
          *(_DWORD *)(a2 + 128),
          a1[129],
          (float *)(a2 + 72),
          a2 + 60,
          (int)v12,
          destination);
    }
    else
    {
      v2 = rf_vector3_transform_by_matrix_rows((float *)a1 + 130, v10, (float *)(a2 + 252));
      v3 = rf_vector_add(v2, sum_result, (const float *)(a2 + 240));
      rf_vector_copy(destination, copy_result, v3);
      v4 = (const float *)rf_matrix3_inverse_to_output((const void *)(a2 + 288), (int)v7);
      v5 = rf_matrix3_argument_times_receiver_to_output(v4, v6, (const float *)a1 + 133);
      rf_matrix3_copy(v12, v5);
    }
    rf_object_publish_position_and_bounds((int)a1, destination);
    if ( (a1[31] & 0x100) == 0 )
    {
      rf_matrix3_copy((float *)a1 + 18, v12);
      rf_matrix3_copy((float *)a1 + 63, v12);
      rf_matrix3_copy((float *)a1 + 72, v12);
    }
    if ( !a1[9] )
      sub_420870((int)a1);
  }
}

