// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436100 rf_entity_apply_crouch_shape_centers
// [UnrealRed physical spheres 2026-11-12; verified ASM] Crouch sets Entity810 bit400 then copies ONLY XYZ from MODELclass crouch40 center+24 into each physical24. Calls real4D9960 support/snap and writes floatclock6FC428 toEntity7B4. No4D9F50 extents recomputation here. UE IsCrouched alone does not establish native support/admission completion.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity), void. NULL exits; otherwise immediately OR entity2064 stance bit0x400, even already set. Signed
// i starts0; EACH iteration re-reads physical-array count DWORD entity388 via486DE0 and continues while signed i<count. For each i use unchecked inline40 getter on MODEL-INFO pointer
// entity668+3632, take source element+24, then unchecked array24 getter on entity+388 (backing pointer atcollection+8), sequentially copy ONLY XYZ into physical element+0. Does not
// compare source logical count/capacity with physical count or copy radius/remaining12bytes. Negative physical count skips loop; no reset/shrink/allocation or shape-index guard.
// After all copies call4D9960(entity), ignoring support/snap result; this delegate can update support/fall/position, not just bounds. Finally copy current FLOAT seconds clock6FC428
// to entity1972. Bit and earlier center writes survive later failure; no uncrouch clearance query, preexisting-stance/action/dead/authority admission, direct extent/radius rewrite or
// rollback.
void __cdecl rf_entity_apply_crouch_shape_centers(int a1)
{
  int first_dword; // eax
  float *element_address_unchecked; // eax
  const float *v3; // [esp-4h] [ebp-14h]
  float copy_result[3]; // [esp+0h] [ebp-10h] BYREF
  int i; // [esp+Ch] [ebp-4h]

  if ( a1 )
  {
    *(_DWORD *)(a1 + 2064) |= 0x400u;
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((void *)(a1 + 388));
      if ( i >= first_dword )
        break;
      v3 = (const float *)(rf_inline_array40_get_element_address((void *)(*(_DWORD *)(a1 + 668) + 3632), i) + 24);
      element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
      rf_vector_copy(element_address_unchecked, copy_result, v3);
    }
    sub_4D9960(a1);
    *(float *)(a1 + 1972) = *(float *)&dword_6FC428;
  }
}

