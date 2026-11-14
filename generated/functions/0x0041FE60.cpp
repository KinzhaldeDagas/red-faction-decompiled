// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041FE60 rf_entity_ensure_selected_weapon_point_light
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl(required entity pointer), void. Primary DWORD entity+676 must differ from EXACT-1; no other sign/range guard before1360*index
// weapon-record address. Player-flag predicate4BB430 ANY nonzero required; predicate438FD0 EXACT AL1 rejects (canonical helper tests entity2064 mask0x2000). Weapon FLOAT+564 must be
// positive OR UNORDERED against DOUBLE0 (AH41/JP); ordered zero/negative reject. On admitted path create no-write local matrix/vector temporaries. Read signed first-DWORD count of
// entity pointer+668 record list+468: if>0, use its unchecked inline index0 tag; otherwise try class pointer+660 list+444 signed count>0. First matching list invokes5651D0(entity
// model handle128,tag,entity orientation72,entity position60,localMatrix,localPoint), with returned pointer ignored. No validation of model/tag or lower transform outcome; composer
// consumes node-transform outputs unconditionally, so no safe fallback is guaranteed for untouched-output adapter paths. If BOTH list counts<=0 copy entity COMMON position60 into
// localPoint. ONLY AFTER preparing point, inspect light handle entity+4984: any value!=EXACT-1 returns leaving existing handle untouched; no update/remove call here. Sentinel-1
// calls527470(localPoint,weapon FLOAT560,FLOAT564,FLOAT568,FLOAT572,FLOAT576,LOWBYTE1,DWORD1,DWORD0), nine stack slots/cleanup36, then stores returned fullEAX VERBATIM into
// entity4984, even failure sentinel. Eligibility rejection preserves existing handle too. No ownership transfer, point/matrix normalization, numerical clamp or NULL checks for
// entity/model-info/class records.
void __cdecl rf_entity_ensure_selected_weapon_point_light(_DWORD *a1)
{
  int *v1; // eax
  int *v2; // eax
  float copy_result[3]; // [esp+20h] [ebp-40h] BYREF
  char v4[36]; // [esp+2Ch] [ebp-34h] BYREF
  float destination[3]; // [esp+50h] [ebp-10h] BYREF
  float *v6; // [esp+5Ch] [ebp-4h]

  if ( a1[169] != -1 && rf_object_has_player_flag((int)a1) && !rf_entity_runtime_flags810_has_mask2000((int)a1) )
  {
    v6 = (float *)((char *)&rf_weapon_records + 1360 * a1[169]);
    if ( v6[141] > 0.0 )
    {
      rf_matrix3_construct(v4);
      rf_vector3_default_construct_noop(destination);
      if ( rf_receiver_get_first_dword((void *)(a1[167] + 468)) <= 0 )
      {
        if ( rf_receiver_get_first_dword((void *)(a1[165] + 444)) <= 0 )
        {
          rf_vector_copy(destination, copy_result, (const float *)a1 + 15);
        }
        else
        {
          v2 = (int *)rf_inline_dword_array4_element_address_unchecked((void *)(a1[165] + 444), 0);
          rf_vmesh_compose_prop_world_transform(a1[32], *v2, (float *)a1 + 18, (int)(a1 + 15), (int)v4, destination);
        }
      }
      else
      {
        v1 = (int *)rf_inline_dword_array4_element_address_unchecked((void *)(a1[167] + 468), 0);
        rf_vmesh_compose_prop_world_transform(a1[32], *v1, (float *)a1 + 18, (int)(a1 + 15), (int)v4, destination);
      }
      if ( a1[1246] == -1 )
        a1[1246] = rf_renderer_point_light_create(
                     (int)destination,
                     v6[140],
                     v6[141],
                     v6[142],
                     v6[143],
                     v6[144],
                     1,
                     1,
                     0);
    }
  }
}

