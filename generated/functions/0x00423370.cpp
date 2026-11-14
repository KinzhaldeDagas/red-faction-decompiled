// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00423370 rf_entity_compute_weapon_muzzle_transform
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl FOUR slots(entity,requested signed weapon index,outPoint3,outMatrix9), output procedure with no uniform success result. SIGNED
// weapon<global911C7C selects attachment index entity+1296; >= selects entity+1292. Call510070(requested index) to resolve/cache literal muzzle_1 node, then50FFA0 for cached
// world-model value; only node EXACT-1 or model0 rejects. Both helpers independently require signed weapon0..63, while this wrapper does not use a global-count upper bound.
// Additional guard ALWAYS tests SIGNED count>0 at *(entity+668)+468, including >=cutoff branch. Fallback copies retained matrix2016 and
// point2004+FLOAT0.30000001192092896*forward2040; critically DOES NOT call423260 target-facing adjustment. Admitted path: node selector read unchecked from *(entity+668)+468 array
// when weapon<cutoff, ELSE from *(entity+660)+480 array, using previously captured attachment index. No own index/count consistency check, selected tag!=-1 test or entity model128
// nonnull check. Compose first5651D0(entity model128,selected attachment tag,entity COMMON matrix72,COMMON position60,local matrixA,local pointA), then second5651D0(weapon
// model,muzzle_1,matrixA,pointA,local matrixB,local pointB), both results ignored. Output point copies second pointB, but output orientation copies FIRST matrixA, NOT second
// muzzle-bone matrixB. Then423260(entity,outPoint,outMatrix) may adjust/preserve matrixA. No output guarantee on underlying model/node-transform failure, no rollback or finite/alias
// guard; no direct entity pose mutation except helper cache/flinch side effects.
void __cdecl rf_entity_compute_weapon_muzzle_transform(
        _DWORD *entity,
        signed int a2,
        float *destination,
        float *out_orientation)
{
  float *v4; // eax
  float v5[3]; // [esp+4h] [ebp-94h] BYREF
  float scaled_result[3]; // [esp+10h] [ebp-88h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-7Ch] BYREF
  float source[3]; // [esp+28h] [ebp-70h] BYREF
  char v9[36]; // [esp+34h] [ebp-64h] BYREF
  int v10; // [esp+58h] [ebp-40h]
  int v11; // [esp+5Ch] [ebp-3Ch]
  int muzzle_1_bone_index; // [esp+60h] [ebp-38h]
  float v13[9]; // [esp+64h] [ebp-34h] BYREF
  float v14[3]; // [esp+88h] [ebp-10h] BYREF
  int v15; // [esp+94h] [ebp-4h]

  if ( a2 >= unk_911C7C )
    v11 = entity[323];
  else
    v11 = entity[324];
  muzzle_1_bone_index = rf_weapon_get_muzzle_1_bone_index(a2);
  v10 = sub_50FFA0(a2);
  if ( muzzle_1_bone_index != -1 && v10 && rf_receiver_get_first_dword((void *)(entity[167] + 468)) > 0 )
  {
    rf_vector3_default_construct_noop(v14);
    rf_vector3_default_construct_noop(source);
    rf_matrix3_construct((char *)v13);
    rf_matrix3_construct(v9);
    if ( a2 >= unk_911C7C )
      v15 = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(entity[165] + 480), v11);
    else
      v15 = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(entity[167] + 468), v11);
    rf_vmesh_compose_prop_world_transform(entity[32], v15, (float *)entity + 18, (int)(entity + 15), (int)v13, v14);
    rf_vmesh_compose_prop_world_transform(v10, muzzle_1_bone_index, v13, (int)v14, (int)v9, source);
    rf_vector_copy(destination, v5, source);
    rf_matrix3_copy(out_orientation, v13);
    rf_entity_adjust_firing_orientation_toward_target((int)entity, destination, out_orientation);
  }
  else
  {
    rf_matrix3_copy(out_orientation, (const float *)entity + 504);
    rf_vector_copy(destination, copy_result, (const float *)entity + 501);
    v4 = rf_vector_multiply_scalar((const float *)entity + 510, scaled_result, 0.30000001);
    rf_vector_accumulate(destination, v4);
  }
}

