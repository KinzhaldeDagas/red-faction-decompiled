// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BFDF0 rf_physics_pair_contacts_solve
// UNREALRED VERIFIED [trigger-geometry-20261020] Retained contact-pair walker invokes4BE850 for trigger pairs when either body physics flags includes0x40000000, removing invalid entries through existing pair-list lifecycle. Repeated active-pair visits are gated by trigger same-frame flag0x40/cooldown, not a UE BeginOverlap-only contract. UnrealRed now processes current movement-update samples and uses its shared per-frame trigger commit guard.
int *rf_physics_pair_contacts_solve()
{
  int *result; // eax
  char v1; // [esp+3h] [ebp-Dh]
  int next_stdcall; // [esp+4h] [ebp-Ch]
  int *v3; // [esp+8h] [ebp-8h]
  int *v4; // [esp+Ch] [ebp-4h]

  result = (int *)rf_receiver_get_first_dword(dword_813BD0);
  v3 = result;
  v4 = nullptr;
  while ( v3 )
  {
    next_stdcall = rf_intrusive_node_get_next_stdcall((int)v3);
    v1 = 0;
    if ( rf_collision_pair_reject_projectile_facing(v3) == 1 )
    {
      if ( v4 )
        rf_intrusive_slist_remove_with_previous(dword_813BD0, v3, v4);
      else
        rf_intrusive_slist_remove_search_unchecked_count(dword_813BD0, v3);
      rf_intrusive_slist_push_front(dword_813C18, v3);
      v1 = 1;
    }
    else
    {
      if ( ((*(_DWORD *)(v3[2] + 424) | *(_DWORD *)(v3[1] + 424)) & 0x40000000) == 0 )
        goto LABEL_36;
      if ( *(_DWORD *)(v3[1] + 36) == 5 || *(_DWORD *)(v3[2] + 36) == 5 )
      {
        if ( !rf_trigger_collision_pair_update((int)v3) )
        {
          if ( v4 )
            rf_intrusive_slist_remove_with_previous(dword_813BD0, v3, v4);
          else
            rf_intrusive_slist_remove_search_unchecked_count(dword_813BD0, v3);
          rf_intrusive_slist_push_front(dword_813C18, v3);
          v1 = 1;
        }
      }
      else
      {
        if ( !rf_collision_pair_passes_association_and_inactive_gate((int)v3) )
          goto LABEL_36;
        if ( (v3[3] & 0x20) != 0 )
        {
          if ( *(_DWORD *)(*(_DWORD *)(v3[1] + 2136) + 4) == 1 && *(_DWORD *)(*(_DWORD *)(v3[2] + 2136) + 4) == 1 )
          {
            rf_physics_pair_contact_horizontal_radius_approximation(v3[1], v3[2]);
            goto LABEL_36;
          }
        }
        else
        {
          if ( (v3[3] & 4) != 0 && *(_DWORD *)(v3[2] + 128) )
          {
            rf_physics_pair_contact_against_model((float *)v3[1], (float *)v3[2]);
            goto LABEL_36;
          }
          if ( (v3[3] & 2) != 0 && *(_DWORD *)(v3[1] + 128) )
          {
            rf_physics_pair_contact_against_model((float *)v3[2], (float *)v3[1]);
            goto LABEL_36;
          }
          if ( (v3[3] & 0x10) != 0 && *(_DWORD *)(v3[2] + 36) == 3 )
          {
            rf_physics_pair_contact_against_backing_solid((float *)v3[1], (float *)v3[2]);
            goto LABEL_36;
          }
          if ( (v3[3] & 8) != 0 && *(_DWORD *)(v3[1] + 36) == 3 )
          {
            rf_physics_pair_contact_against_backing_solid((float *)v3[2], (float *)v3[1]);
            goto LABEL_36;
          }
        }
        rf_physics_pair_contact_sphere_samples(v3[1], v3[2]);
      }
    }
LABEL_36:
    if ( !v1 )
      v4 = v3;
    result = (int *)next_stdcall;
    v3 = (int *)next_stdcall;
  }
  return result;
}

