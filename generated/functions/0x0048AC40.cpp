// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048AC40 rf_mover_bind_authored_children
// UNREALRED VERIFIED [mission-mover-geometry-20261013] After level creation, resolves authored list at mover +0x2A8 through common UID lookup, appends common handles at +0x2C0, and resolves list +0x2B4 only to type9, appending solid handles at +0x2CC. Missing or wrong-type links are erased; originals are not editor member placements. Child common parent handle +0x30 is set. Calls 0x48B500(initial=true) after binding.
// UNREALRED VERIFIED [mission-mover-world-20261013] Binding eligibility: list0 resolves generic common objects and omits flag0x08000000 objects; list1 requires common type9. Missing generic links and missing/wrong-type solid links are erased in place. Both lists retain repeated valid references. The parent handle field is overwritten by later movers, but it is NOT the full contributor relation:0x48B500 rebuilds from both retained handle lists. Type9 in the common list therefore contributes too. The final call composes initial poses even for inactive movers.
// UNREALRED VERIFIED [mission-startup-20261020] New-level ordering continuation: startup mutations are visible before initial child pose composition and linked-pickup disable gates. For EACH valid list1 type9 link, when rotating, not restoring, direction is backward and flag0x100 is clear, negate first-key angle. Repeated links repeat this negation; generic list0 type9 links do not take that branch. Saved-state branch remains distinct.
int rf_mover_bind_authored_children()
{
  _DWORD *v0; // eax
  int *v1; // eax
  int *v2; // eax
  int v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  int *v7; // [esp+8h] [ebp-10h]
  _DWORD *v8; // [esp+8h] [ebp-10h]
  int v9; // [esp+Ch] [ebp-Ch]
  int v10; // [esp+Ch] [ebp-Ch]
  int v11; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int n; // [esp+10h] [ebp-8h]
  int j; // [esp+14h] [ebp-4h]
  int k; // [esp+14h] [ebp-4h]
  int m; // [esp+14h] [ebp-4h]
  int ii; // [esp+14h] [ebp-4h]
  int jj; // [esp+14h] [ebp-4h]

  for ( i = unk_70489C; (_UNKNOWN *)i != &unk_704610; i = *(_DWORD *)(i + 652) )
  {
    if ( rf_receiver_get_first_dword((void *)(i + 668)) > 0 )
    {
      for ( j = 0; j < 2; ++j )
      {
        v0 = (_DWORD *)sub_552200((_DWORD *)(i + 668), 0);
        v9 = rf_item_find_by_uid(*(_DWORD *)(*v0 + 4 * j + 76));
        if ( v9 )
          *(_DWORD *)(v9 + 700) |= 1u;
      }
    }
    for ( k = 0; k < rf_receiver_get_first_dword((void *)(i + 680)); ++k )
    {
      v1 = (int *)sub_552200((_DWORD *)(i + 680), k);
      v7 = (int *)rf_object_find_by_saved_identifier(*v1);
      if ( v7 )
      {
        if ( (v7[31] & 0x8000000) == 0 )
        {
          rf_pointer_array_append_dword((_DWORD *)(i + 704), v7[11]);
          v7[106] &= ~0x80000000;
          v7[12] = *(_DWORD *)(i + 44);
        }
      }
      else
      {
        rf_pointer_array_erase_index_unchecked((_DWORD *)(i + 680), k--);
      }
    }
    for ( m = 0; m < rf_receiver_get_first_dword((void *)(i + 692)); ++m )
    {
      v2 = (int *)sub_552200((_DWORD *)(i + 692), m);
      v8 = (_DWORD *)rf_object_find_by_saved_identifier(*v2);
      if ( v8 && v8[9] == 9 )
      {
        rf_pointer_array_append_dword((_DWORD *)(i + 716), v8[11]);
        v8[12] = *(_DWORD *)(i + 44);
        if ( (*(_DWORD *)(i + 792) & 0x1000) != 0 )
          v8[31] |= 0x40000u;
        if ( rf_mover_is_rotating(i)
          && !unk_704605
          && (*(_DWORD *)(i + 792) & 0x2000) == 0
          && (*(_DWORD *)(i + 792) & 0x100) == 0 )
        {
          v3 = sub_552200((_DWORD *)(i + 668), 0);
          *(float *)(*(_DWORD *)v3 + 84) = *(float *)(*(_DWORD *)v3 + 84) * -1.0;
        }
      }
      else
      {
        rf_pointer_array_erase_index_unchecked((_DWORD *)(i + 692), m--);
      }
    }
  }
  if ( unk_704605 )
  {
    for ( n = unk_70489C; (_UNKNOWN *)n != &unk_704610; n = *(_DWORD *)(n + 652) )
    {
      if ( rf_mover_is_rotating(n) )
      {
        if ( *(float *)(n + 768) == 0.0 )
        {
          if ( (*(_DWORD *)(n + 792) & 0x2000) != 0 )
          {
            *(_DWORD *)(n + 792) &= ~0x2000u;
          }
          else
          {
            *(_DWORD *)(n + 792) |= 0x2000u;
            if ( rf_receiver_get_first_dword((void *)(n + 668)) > 0 )
            {
              for ( ii = 0; ii < 2; ++ii )
              {
                v4 = (_DWORD *)sub_552200((_DWORD *)(n + 668), 0);
                v10 = rf_item_find_by_uid(*(_DWORD *)(*v4 + 4 * ii + 76));
                if ( v10 )
                  *(_DWORD *)(v10 + 700) &= ~1u;
              }
            }
          }
          if ( (*(_DWORD *)(n + 792) & 0x2000) != 0 )
            *(float *)(n + 752) = *(float *)(*(_DWORD *)sub_552200((_DWORD *)(n + 668), 0) + 84);
          else
            *(float *)(n + 752) = 0.0;
          *(_DWORD *)(n + 760) = 0;
          if ( (*(_DWORD *)(n + 792) & 0x2000) != 0 )
            *(_DWORD *)(n + 792) &= ~0x2000u;
          else
            *(_DWORD *)(n + 792) |= 0x2000u;
        }
      }
      else if ( *(float *)(n + 768) == 0.0
             && (*(_DWORD *)(n + 792) & 0x2000) == 0
             && (*(_DWORD *)(n + 792) & 0x100) == 0
             && rf_receiver_get_first_dword((void *)(n + 668)) > 0 )
      {
        for ( jj = 0; jj < 2; ++jj )
        {
          v5 = (_DWORD *)sub_552200((_DWORD *)(n + 668), 0);
          v11 = rf_item_find_by_uid(*(_DWORD *)(*v5 + 4 * jj + 76));
          if ( v11 )
            *(_DWORD *)(v11 + 700) &= ~1u;
        }
      }
    }
  }
  unk_704605 = 0;
  return rf_mover_compose_child_transforms(1);
}

