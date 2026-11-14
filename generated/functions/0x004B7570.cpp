// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7570 rf_object_release_slot_and_storage
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): One cdecl raw slot index, without range/null admission. Loads table7B7E10[index]; unlinks common-list next+16/previous+20 by previous.next=next and
// next.previous=previous; clears both links and decrements DWORD7B4DF8. Storage routing by DWORD+36: types1/2/3/7 return to item/projectile/physical-debris/corpse pools
// at7D1290/7BEB30/physical-debris pool/7B8E20; type6 deletes mission-event subtype using object-4; all others call common scalar deleting destructor with flag1 when nonnull. Only
// after storage release clears table entry. Performs an otherwise unused full free-list traversal to sentinel7B4DFC, then appends 12-byte node7B4E10+12*index to free-list tail7B4E00
// (node+0 next sentinel, +4 previous tail; retained +8 index). Returns node address in EAX. Does not itself run full type-specific resource cleanup;4B73B0 does that first.
int *__cdecl rf_object_release_slot_and_storage(int a1)
{
  int *result; // eax
  _DWORD *v2; // [esp+14h] [ebp-8h]
  void **i; // [esp+18h] [ebp-4h]

  v2 = (_DWORD *)unk_7B7E10[a1];
  *(_DWORD *)(v2[5] + 16) = v2[4];
  *(_DWORD *)(v2[4] + 20) = v2[5];
  v2[4] = 0;
  v2[5] = 0;
  --unk_7B4DF8;
  switch ( v2[9] )
  {
    case 1:
      rf_item_pool_release_to_free_list(dword_7D1290, v2);
      break;
    case 2:
      rf_projectile_pool_release_to_free_list(dword_7BEB30, v2);
      break;
    case 3:
      rf_physical_debris_pool_release_to_free_list(rf_physical_debris_object_pool, v2);
      break;
    case 6:
      if ( v2 )
        rf_mission_event_delete_by_subtype((int)(v2 - 1));
      else
        rf_mission_event_delete_by_subtype(0);
      break;
    case 7:
      rf_corpse_pool_release_to_free_list(dword_7B8E20, v2);
      break;
    default:
      if ( v2 )
        rf_common_scalar_deleting_destructor(v2, 1);
      break;
  }
  unk_7B7E10[a1] = 0;
  for ( i = (void **)dword_7B4DFC; i != &dword_7B4DFC; i = (void **)*i )
    ;
  unk_7B4E14[3 * a1] = unk_7B4E00;
  unk_7B4E10[3 * a1] = (int)&dword_7B4DFC;
  *unk_7B4E00 = &unk_7B4E10[3 * a1];
  result = &unk_7B4E10[3 * a1];
  unk_7B4E00 = result;
  return result;
}

