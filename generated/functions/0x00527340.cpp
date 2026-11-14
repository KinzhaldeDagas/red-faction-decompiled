// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527340 rf_renderer_light_allocate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl lowBYTE category. Scan lowest index0..1099 whose typeDWORD8==0 in268-byte records. Full pool returns-1 before count/list/invalidation changes. Success increments renderer object count, appends slot at TAIL of circular list: category0 OR globalBYTE rf_fixed_pool_heap_spill_enabled nonzero ->common sentinelD03608; otherwise nonzero category ->sentinelD03720. Set record.next0=sentinel,prev4=oldTail,oldTail.next=record,sentinel.prev=record, preserving survivors order. Then clear active validity/count via528C20 and return index. Does NOT set type nonzero or clear payload, set categoryBYTE77, initialize referenceCounter88 or increment serial. Caller must construct immediately; repeated bare
// allocation before type initialization can choose same slot and corrupt ring. No heap allocation or thread safety.
int __cdecl rf_renderer_light_allocate(char a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 1100 && unk_D03838[67 * i]; ++i )
    ;
  if ( i >= 1100 )
    return -1;
  ++rf_renderer_object_count;
  if ( !a1 || rf_fixed_pool_heap_spill_enabled[0] )
  {
    unk_D03834[67 * i] = unk_D0360C;
    rf_renderer_light_records[67 * i] = (int)&rf_renderer_common_light_list_sentinel;
    *unk_D0360C = &rf_renderer_light_records[67 * i];
    unk_D0360C = &rf_renderer_light_records[67 * i];
  }
  else
  {
    unk_D03834[67 * i] = unk_D03724;
    rf_renderer_light_records[67 * i] = (int)&rf_renderer_category1_light_list_sentinel;
    *unk_D03724 = &rf_renderer_light_records[67 * i];
    unk_D03724 = &rf_renderer_light_records[67 * i];
  }
  rf_light_invalidate_active_world_list();
  return i;
}

