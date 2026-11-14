// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00422CC0 rf_entity_resolve_firing_transform
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl SIX slots(entity,requested weapon index,outPoint3,outMatrix9,tagIndex,primaryBYTE). Outputs determine behavior; EAX/AL forward
// heterogeneous helper results, not a Boolean success. Ordered branch chain RE-CALLS438AC0 rather than caching it. First any-nonzero438AC0 and camera slot state DWORD+8==EXACT2: copy
// referenced camera common position+60 and retained matrix+2016 via player(entity+5168)->slot+196 to outputs. Second any-nonzero438AC0 plus requested weapon DWORD[912264+1360*index]
// mask400: copy entity retained point+2004 and matrix+2016. No requested index bounds check before flag indexing. Third player-association4BCF40==EXACT AL1 plus same weapon mask:
// player flag4BB430==EXACT AL1 uses entity pose, outPoint=retained point+FLOAT0.20000000298023224*retained forward+2040; outMatrix=retained2016. Otherwise find local entry/related
// owner4BCED0(entity), dereference its+20 WITHOUT NULL test, resolve ENTITY; missing entity exits with BOTH outputs untouched and EAX0, no later fallback. Found entity supplies the
// same0.2-offset pose. Fourth any-nonzero438AC0 and FPGun muzzle helper4EB9E0(player,&localPoint,NULLorientation)==EXACT AL1:
// outPoint=localPoint-forward*float32(dot(localPoint-retainedPoint,forward)), outMatrix=entity retained2016. No divide by forward length or normalization. If these branches do not
// select, BYTE primary==EXACT1 queries cached model50FFA0(entity primary+676); EVERY other byte queries secondary+680. This selected-weapon model test is distinct from requested
// weapon argument. Any nonzero full EAX calls423370(entity,requested index,outPoint,outMatrix), then player flag EXACT1 applies the same float32-dot subtraction to newly written
// point, preserving orientation. Other player-flag results skip subtraction. Model0 instead calls423090(entity,outPoint,outMatrix,tagIndex,zeroextended primaryBYTE), FIVE slots. In
// that callee ANY nonzero primary byte selects primary tags, unlike this exact1 model selection. No common success byte, finite/output/pointer guards, alias snapshot across branches
// or rollback; outputs can be unchanged or partially updated after delegate failure. Matrix-copy branches return final row-copy pointer bits (outMatrix+24); projection ends with
// LOCAL hidden vector-copy result bits.
char __cdecl rf_entity_resolve_firing_transform(float *a1, int a2, float *destination, float *a4, int a5, char a6)
{
  float *v6; // eax
  const float *v7; // eax
  int v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float v17[3]; // [esp+4h] [ebp-11Ch] BYREF
  float v18[3]; // [esp+10h] [ebp-110h] BYREF
  float v19[3]; // [esp+1Ch] [ebp-104h] BYREF
  float v20[3]; // [esp+28h] [ebp-F8h] BYREF
  float v21[3]; // [esp+34h] [ebp-ECh] BYREF
  float v22[3]; // [esp+40h] [ebp-E0h] BYREF
  float v23[3]; // [esp+4Ch] [ebp-D4h] BYREF
  float v24[3]; // [esp+58h] [ebp-C8h] BYREF
  float v25[3]; // [esp+64h] [ebp-BCh] BYREF
  float sum_result[3]; // [esp+70h] [ebp-B0h] BYREF
  float scaled_result[3]; // [esp+7Ch] [ebp-A4h] BYREF
  float v28[3]; // [esp+88h] [ebp-98h] BYREF
  _BYTE v29[36]; // [esp+94h] [ebp-8Ch] BYREF
  float copy_result[3]; // [esp+B8h] [ebp-68h] BYREF
  float v31[3]; // [esp+C4h] [ebp-5Ch] BYREF
  float v32[3]; // [esp+D0h] [ebp-50h] BYREF
  float v33[3]; // [esp+DCh] [ebp-44h] BYREF
  float rhs[3]; // [esp+E8h] [ebp-38h] BYREF
  float v35; // [esp+F4h] [ebp-2Ch]
  float out_vector[3]; // [esp+F8h] [ebp-28h] BYREF
  float scalar; // [esp+104h] [ebp-1Ch]
  float lhs[3]; // [esp+108h] [ebp-18h] BYREF
  int local_player_entry_or_related_owner; // [esp+114h] [ebp-Ch]
  const float *v40; // [esp+118h] [ebp-8h]
  int v41; // [esp+11Ch] [ebp-4h]

  if ( sub_438AC0((int)a1) && rf_view_wrapper_get_dword8(*(_DWORD *)(*((_DWORD *)a1 + 1292) + 196)) == 2 )
  {
    v6 = rf_entity_view_copy_referenced_position(v31, *(_DWORD *)(*((_DWORD *)a1 + 1292) + 196));
    rf_vector_copy(destination, copy_result, v6);
    v7 = (const float *)rf_entity_view_copy_referenced_matrix_2016((int)v29, *(_DWORD **)(*((_DWORD *)a1 + 1292) + 196));
    LOBYTE(v8) = rf_matrix3_copy(a4, v7);
  }
  else if ( sub_438AC0((int)a1) && (unk_912264[340 * a2] & 0x400) != 0 )
  {
    rf_vector_copy(destination, v28, a1 + 501);
    LOBYTE(v8) = rf_matrix3_copy(a4, a1 + 504);
  }
  else if ( rf_object_is_player_associated((int)a1) == 1 && (unk_912264[340 * a2] & 0x400) != 0 )
  {
    if ( rf_object_has_player_flag((int)a1) )
    {
      v9 = rf_vector_multiply_scalar(a1 + 510, scaled_result, 0.2);
      v10 = rf_vector_add(a1 + 501, sum_result, v9);
      rf_vector_copy(destination, v25, v10);
      LOBYTE(v8) = rf_matrix3_copy(a4, a1 + 504);
    }
    else
    {
      local_player_entry_or_related_owner = rf_object_find_local_player_entry_or_related_owner((int)a1);
      v8 = rf_entity_resolve_handle(*(_DWORD *)(local_player_entry_or_related_owner + 20));
      v40 = (const float *)v8;
      if ( v8 )
      {
        v11 = rf_vector_multiply_scalar(v40 + 510, v24, 0.2);
        v12 = rf_vector_add(v40 + 501, v23, v11);
        rf_vector_copy(destination, v22, v12);
        LOBYTE(v8) = rf_matrix3_copy(a4, v40 + 504);
      }
    }
  }
  else if ( sub_438AC0((int)a1)
         && (rf_vector3_default_construct_noop(lhs),
             rf_player_compose_fpgun_muzzle_world_transform(*((void **)a1 + 1292), lhs, nullptr)) )
  {
    rf_vector_subtract(lhs, out_vector, a1 + 501);
    scalar = rf_vector_dot(out_vector, a1 + 510);
    v13 = rf_vector_multiply_scalar(a1 + 510, v21, scalar);
    v14 = rf_vector_subtract(lhs, v20, v13);
    rf_vector_copy(destination, v19, v14);
    LOBYTE(v8) = rf_matrix3_copy(a4, a1 + 504);
  }
  else
  {
    v41 = 0;
    if ( a6 == 1 )
      v41 = sub_50FFA0(*((_DWORD *)a1 + 169));
    else
      v41 = sub_50FFA0(*((_DWORD *)a1 + 170));
    if ( v41 )
    {
      rf_entity_compute_weapon_muzzle_transform(a1, a2, (int)destination, (int)a4);
      LOBYTE(v8) = rf_object_has_player_flag((int)a1);
      if ( (unsigned __int8)v8 == 1 )
      {
        rf_vector3_copy_return_destination(v32, destination);
        rf_vector_subtract(v32, v33, a1 + 501);
        v35 = rf_vector_dot(v33, a1 + 510);
        rf_vector_multiply_scalar(a1 + 510, rhs, v35);
        v15 = rf_vector_subtract(v32, v18, rhs);
        LOBYTE(v8) = (unsigned __int8)rf_vector_copy(destination, v17, v15);
      }
    }
    else
    {
      LOBYTE(v8) = rf_entity_compose_tag_or_retained_firing_transform((int)a1, destination, (int)a4, a5, a6);
    }
  }
  return v8;
}

