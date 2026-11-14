// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050FE50 rf_projectile_update_parent_attachments
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Walks projectile intrusive ring from911F74 to sentinel911CE8 through next+652. For signed parent UID+688>=0, resolves entity; if found and dead433F60 or predicate40D440 (entity definition+1828 mask04000000), detaches by setting parent=-1, zeroing velocity+324 and ORing physics flags+424 with80000000. Otherwise resolves generic parent: missing parent marks projectile deferred deletion; found parent rotates stored local offset+692 using parent matrix+72, adds parent position+60 and calls position setter4BC330. Computes orientation with413070 receiver=parent matrix, argument=projectile local matrix+704, copies result to projectile matrix+72, rebuilds basis55B770. Does not free
// or unlink projectiles; detached entries skip future updates.
int rf_projectile_update_parent_attachments()
{
  int result; // eax
  float *v1; // eax
  float v2[9]; // [esp+0h] [ebp-48h] BYREF
  float rhs[3]; // [esp+24h] [ebp-24h] BYREF
  float sum_result[3]; // [esp+30h] [ebp-18h] BYREF
  int v5; // [esp+3Ch] [ebp-Ch]
  int v6; // [esp+40h] [ebp-8h]
  int i; // [esp+44h] [ebp-4h]

  result = dword_911F74;
  for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
  {
    result = i;
    if ( *(int *)(i + 688) > -1 )
    {
      v6 = rf_entity_resolve_handle(*(_DWORD *)(i + 688));
      if ( v6 && (rf_entity_is_dead(v6) || rf_entity_class_flags724_has_mask4000000(v6)) )
      {
        *(_DWORD *)(i + 688) = -1;
        rf_vector3_zero_return_destination((float *)(i + 324));
        result = *(_DWORD *)(i + 424) | 0x80000000;
        *(_DWORD *)(i + 424) = result;
      }
      else
      {
        v5 = rf_object_resolve_handle(*(_DWORD *)(i + 688));
        if ( v5 )
        {
          rf_matrix3_rotate_vector((float *)(i + 692), rhs, (float *)(v5 + 72));
          rf_vector_add((const float *)(v5 + 60), sum_result, rhs);
          rf_object_publish_position_and_bounds(i, sum_result);
          v1 = rf_matrix3_argument_times_receiver_to_output((const float *)(v5 + 72), v2, (const float *)(i + 704));
          rf_matrix3_copy((float *)(i + 72), v1);
          result = rf_matrix3_rebuild_basis_from_forward_in_place((char *)(i + 72));
        }
        else
        {
          result = rf_object_mark_for_deferred_delete(i);
        }
      }
    }
  }
  return result;
}

