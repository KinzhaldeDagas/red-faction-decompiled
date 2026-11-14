// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515D90 rf_room460_destroy_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall room receiver,no stack args,void. If rootDWORD60 nonnull, recursively destroy spatial tree; DOES NOT clear root60 afterward. Clear count-only member156; release backing storage of arrays108,48,444 (count/capacity/backing reset; no pointed-element destruction). Normal compiler member destruction then visits444, no-op embedded156,108,48; after releases backing pointers areNULL. Does not unlink room from solid arrays144/156/168,delete receiver,walk/destroy room face list40,clear face.room68,or reset root/list/bounds flags. Scalar deleting wrapper517CF0 separately deletes receiver when flags&1. No guard for repeated destruction while stale root is nonnull;
// arrays108 are borrowed room references,48 portal pointers,444 light-cache pointers and their pointees are not freed by array release.
void __thiscall rf_room460_destroy_members(int this)
{
  if ( *(_DWORD *)(this + 60) )
    rf_geomod_spatial_tree_destroy_recursive(*(_DWORD *)(this + 60));
  rf_pointer_array_clear_count_keep_storage((_DWORD *)(this + 156));
  rf_pointer_array_release_storage((void **)(this + 108));
  rf_pointer_array_release_storage((void **)(this + 48));
  rf_pointer_array_release_storage((void **)(this + 444));
  rf_pointer_array_destroy_backing_storage((void **)(this + 444));
  rf_shared_noop_destructor_4580d0();
  rf_pointer_array_destroy_backing_storage((void **)(this + 108));
  rf_pointer_array_destroy_backing_storage((void **)(this + 48));
}

