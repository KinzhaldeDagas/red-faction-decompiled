// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00434C80 rf_entity_try_detach_with_safe_exit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(child pointer), canonicalAL0/1. NULL child or ENTITY-resolution failure of child full parent handle512 returns0 before own writes. Capture
// resolved owner pointer; initial destination copies child COMMON position60. Only owner shared-use classification EXACT1 performs exit search; every other classification bypasses
// all collision probes and uses initial destination. For use1, scale=FLOAT32(owner FLOAT384/DOUBLE2) only when owner FLOAT268 ORDERED>0 AND authored class1828 mask0x1000 set,
// otherwise scale=owner FLOAT384. Five candidates in exact order: owner physics row264*(+scale iff ordered268>0, otherwise -scale includingNaN); row252*(-scale); row252*(+scale);
// row276*(+owner384); row276*(-owner384). Each is built with FLOAT32 vector helpers, then accumulated owner physics position228. Last two use full384 even if scale was halved. Clamp
// candidateY upward to child currentY232 ONLY on ordered childY>candidateY; equality/NaN preserves candidate. Hit-record constructor is no-op; only fractionFLOAT+24 initialized1.
// Pair registry sweep(child,child position228,destination,record,excluded owner) ANYnonzero rejects candidate and skips world query. Otherwise world shape
// sweep(child228,destination,child physics136,same record) ANYnonzero rejects. First BOTH-AL0 candidate wins; no ground/finite/radius clamp. All five rejected plays nonpositional
// event2(0,0,1) then explicitAL0 with no own position/association stores; query side effects are not rolled back.  Accepted or use!=1 path FIRST clears captured owner flags2064
// mask0x10000, THEN re-reads/preserves child parent handle512, then4343A0(captured owner,child fullhandle44,playSound1), IGNORING itsAL. Thus outer success does not guarantee
// reciprocal detach succeeded. Walk global active list68211C->sentinel681E90, next652 loaded AFTER delegates: for raw modeDWORD1312==3 AND raw target1376==preserved parent handle,
// call40B2D0(entity+672), then guarded40BA80(entity+672,detached child current fullhandle44), both results ignored; target writer may reject. No exclusion of owner/child or dead/role
// filter here. Zero captured owner FLOAT1828 then1832. Publish destination through4BC330(child), copying COMMON/current/predicted positions and bounds. Player-associated438AC0
// ANYnonzero clears child flags2064 mask0x4000. Stop captured owner PRIMARY676 firing via422A40(owner handle44,index), ignore result.  Owner turret predicate EXACTAL1 copies owner
// COMMON matrix72 into child matrices72,252,288 in order. Extract Euler from child72 with outputs Pitch,Bank,Heading placed in locals(Pitch,Heading,Bank), then child
// vector2148=(-Pitch,Heading,Bank) using x87FCHS. Other predicate bytes set child COMMON72 identity and copy it to child252 ONLY, preserving child288/vector2148. Neither branch
// writes child retained matrix2016 here. Finally zero OWNER angular vector336, call4D98A0 snap-down(child), ignore result, explicitAL1. No rollback of peer targets/flags/position or
// detach failure, no slotkey cleanup, transform interpolation or extra snap-success gate.
char __cdecl rf_entity_try_detach_with_safe_exit(int a1)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float v8; // [esp+0h] [ebp-11Ch]
  float scalar; // [esp+8h] [ebp-114h]
  float scalara; // [esp+8h] [ebp-114h]
  float scalarb; // [esp+8h] [ebp-114h]
  float v12[3]; // [esp+10h] [ebp-10Ch] BYREF
  float v13[3]; // [esp+1Ch] [ebp-100h] BYREF
  float v14[3]; // [esp+28h] [ebp-F4h] BYREF
  float v15[3]; // [esp+34h] [ebp-E8h] BYREF
  float v16[3]; // [esp+40h] [ebp-DCh] BYREF
  float v17[3]; // [esp+4Ch] [ebp-D0h] BYREF
  float v18[3]; // [esp+58h] [ebp-C4h] BYREF
  float v19[3]; // [esp+64h] [ebp-B8h] BYREF
  float v20[3]; // [esp+70h] [ebp-ACh] BYREF
  float v21[3]; // [esp+7Ch] [ebp-A0h] BYREF
  float copy_result[3]; // [esp+88h] [ebp-94h] BYREF
  float scaled_result[3]; // [esp+94h] [ebp-88h] BYREF
  float v24; // [esp+A0h] [ebp-7Ch] BYREF
  float v25; // [esp+A4h] [ebp-78h] BYREF
  float v26; // [esp+A8h] [ebp-74h] BYREF
  char v27[24]; // [esp+ACh] [ebp-70h] BYREF
  float v28; // [esp+C4h] [ebp-58h]
  float v29; // [esp+F8h] [ebp-24h]
  int i; // [esp+FCh] [ebp-20h]
  char v31; // [esp+103h] [ebp-19h]
  int j; // [esp+104h] [ebp-18h]
  float destination; // [esp+108h] [ebp-14h] BYREF
  float v34; // [esp+10Ch] [ebp-10h]
  int v35; // [esp+114h] [ebp-8h]
  _DWORD *v36; // [esp+118h] [ebp-4h]

  if ( !a1 )
    return 0;
  v36 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 512));
  if ( !v36 )
    return 0;
  rf_vector3_copy_return_destination(&destination, (float *)(a1 + 60));
  if ( rf_object_get_use_classification(v36) != 1 )
    goto LABEL_28;
  v31 = 0;
  if ( *((float *)v36 + 67) > 0.0 && (*(_DWORD *)(v36[165] + 1828) & 0x1000) != 0 )
    v29 = *((float *)v36 + 96) / 2.0;
  else
    v29 = *((float *)v36 + 96);
  for ( i = 0; i < 5; ++i )
  {
    switch ( i )
    {
      case 0:
        if ( *((float *)v36 + 67) <= 0.0 )
        {
          scalar = -v29;
          v3 = rf_vector_multiply_scalar((const float *)v36 + 66, v21, scalar);
          rf_vector_copy(&destination, v20, v3);
        }
        else
        {
          v2 = rf_vector_multiply_scalar((const float *)v36 + 66, scaled_result, v29);
          rf_vector_copy(&destination, copy_result, v2);
        }
        break;
      case 1:
        scalara = -v29;
        v4 = rf_vector_multiply_scalar((const float *)v36 + 63, v19, scalara);
        rf_vector_copy(&destination, v18, v4);
        break;
      case 2:
        v5 = rf_vector_multiply_scalar((const float *)v36 + 63, v17, v29);
        rf_vector_copy(&destination, v16, v5);
        break;
      case 3:
        v6 = rf_vector_multiply_scalar((const float *)v36 + 69, v15, *((float *)v36 + 96));
        rf_vector_copy(&destination, v14, v6);
        break;
      case 4:
        scalarb = -*((float *)v36 + 96);
        v7 = rf_vector_multiply_scalar((const float *)v36 + 69, v13, scalarb);
        rf_vector_copy(&destination, v12, v7);
        break;
      default:
        break;
    }
    rf_vector_accumulate(&destination, (float *)v36 + 57);
    if ( *(float *)(a1 + 232) > (double)v34 )
      v34 = *(float *)(a1 + 232);
    rf_physics_hit_record_construct_noop(v27);
    v28 = 1.0;
    if ( !rf_physics_pair_registry_sweep_subject_segment(a1, a1 + 228, (int)&destination, (int)v27, (int)v36)
      && !rf_physics_shape_sweep_movers_and_static_world(a1 + 228, (int)&destination, a1 + 136, (int)v27) )
    {
      v31 = 1;
      break;
    }
  }
  if ( v31 )
  {
LABEL_28:
    v36[516] &= ~0x10000u;
    v35 = *(_DWORD *)(a1 + 512);
    rf_entity_detach_first_matching_child((int)v36, *(_DWORD *)(a1 + 44), 1);
    for ( j = unk_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
    {
      if ( *(_DWORD *)(j + 1312) == 3 && *(_DWORD *)(j + 1376) == v35 )
      {
        sub_40B2D0((int *)(j + 672));
        sub_40BA80((int *)(j + 672), *(_DWORD *)(a1 + 44));
      }
    }
    *((float *)v36 + 457) = 0.0;
    *((float *)v36 + 458) = 0.0;
    rf_object_publish_position_and_bounds(a1, &destination);
    if ( sub_438AC0(a1) )
      *(_DWORD *)(a1 + 2064) &= ~0x4000u;
    rf_entity_stop_weapon_firing(v36[11], v36[169]);
    if ( rf_entity_has_turret_flag((int)v36) )
    {
      rf_matrix3_copy((float *)(a1 + 72), (const float *)v36 + 18);
      rf_matrix3_copy((float *)(a1 + 252), (const float *)v36 + 18);
      rf_matrix3_copy((float *)(a1 + 288), (const float *)v36 + 18);
      rf_vector3_default_construct_noop(&v24);
      rf_matrix3_extract_euler_angles_retail((float *)(a1 + 72), &v24, &v26, &v25);
      v8 = -v24;
      rf_vector3_set_components_thiscall((float *)(a1 + 2148), v8, v25, v26);
    }
    else
    {
      rf_identity_orientation_matrix((float *)(a1 + 72));
      rf_matrix3_copy((float *)(a1 + 252), (const float *)(a1 + 72));
    }
    rf_vector3_zero_return_destination((float *)v36 + 84);
    rf_object_snap_down_using_physics_shape_sweep(a1);
    return 1;
  }
  else
  {
    rf_gamesound_play_event(2, 0, 0.0, 1.0);
    return 0;
  }
}

