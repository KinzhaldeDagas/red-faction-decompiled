// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00485A70 rf_material_system_shutdown
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl noargs. Iterates prefix registry0x70046C, calls scalar deleting destructor486BB0(flags1) on each nonnull entry, releases vector storage. Then releases ONLY upper-triangle
// pair sound vectors: i=0..9,j=i..9, vector address0x6FFFB0 +120*i +12*j. Finally iterates custom-set registry0x700460, calls scalar deleting destructor486BE0(flags1) on each nonnull
// entry, releases vector storage. Container release clears count/capacity and deletes backing array, not its elements; explicit entry destruction is separate. Does not call
// sound-resource unload, release debris bitmap handles, zero physics/count tables, or visit lower-triangle pair vectors. Custom-set destructor only clears/destroys its name string;
// embedded sound handles are not owned allocations here.
void __cdecl rf_material_system_shutdown()
{
  void *v0; // [esp+Ch] [ebp-14h]
  void *v1; // [esp+14h] [ebp-Ch]
  int k; // [esp+18h] [ebp-8h]
  int i; // [esp+1Ch] [ebp-4h]
  int j; // [esp+1Ch] [ebp-4h]
  int m; // [esp+1Ch] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(rf_material_bitmap_prefix_registry); ++i )
  {
    v1 = *(void **)sub_552200(rf_material_bitmap_prefix_registry, i);
    if ( v1 )
      rf_material_prefix_entry_scalar_delete(v1, 1);
  }
  rf_pointer_array_release_storage((void **)rf_material_bitmap_prefix_registry);
  for ( j = 0; j < 10; ++j )
  {
    for ( k = j; k < 10; ++k )
      rf_pointer_array_release_storage((void **)&rf_material_hit_sound_pair_vectors[30 * j + 3 * k]);
  }
  for ( m = 0; m < rf_receiver_get_first_dword(rf_material_custom_sound_sets); ++m )
  {
    v0 = *(void **)sub_552200(rf_material_custom_sound_sets, m);
    if ( v0 )
      rf_material_custom_sound_set_scalar_delete(v0, 1);
  }
  rf_pointer_array_release_storage((void **)rf_material_custom_sound_sets);
}

