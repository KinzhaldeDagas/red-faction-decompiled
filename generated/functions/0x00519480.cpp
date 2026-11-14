// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00519480 rf_solid888_destruct_owned_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall solid,no stack args. FIRST rewinds shared scratch arena and clears its owners. Repeatedly unlinks face-list head112 and pooled-destroys each face. Deletes every room from array144 through517CF0(flags1),releases arrays144/156/168. Destroys every vertex in array120 through vertex-pool helper;recursively deletes child solids in132 via owning solid destructor(flags1). Destroys graph at BYTE768 through519180(not lightmap array192;decompiler cast+192 DWORDs means768). Deletes auxiliary/portal objects in180 via517D20(flags1),releases180. Deletes lightmap descriptors192 through their owning destructor,releases192. Deletes UV-scroll descriptors756 via51E980(flags1),releases756. If
// tree pointerDWORD0 nonNULL,recursively destroys spatial tree;does NOT clear stored tree pointer here. Clears live BYTE4. Releases capacity32 array864,then destructor864 again;destroys graph header768,header756,calls shared no-op member destructor,then backing destructors for228,216,204,192,180,168,156,144,132,120 in that order. Many headers are thus released twice after zeroing. Does not free OUTER888-byte allocation itself,reset bounds/center/flags beyond listed writes,filter global scratch owners by this solid,guard NULL/double-owned elements or roll back partial destruction. Member arrays own different object kinds;this is not a single flat pointer-array free.
void __thiscall rf_solid888_destruct_owned_members(char *this)
{
  int *v1; // eax
  void *v3; // [esp+20h] [ebp-38h]
  void *v4; // [esp+28h] [ebp-30h]
  void *v5; // [esp+30h] [ebp-28h]
  char *v6; // [esp+38h] [ebp-20h]
  void *v7; // [esp+40h] [ebp-18h]
  int j; // [esp+44h] [ebp-14h]
  int k; // [esp+44h] [ebp-14h]
  int m; // [esp+44h] [ebp-14h]
  int n; // [esp+44h] [ebp-14h]
  int ii; // [esp+44h] [ebp-14h]
  int jj; // [esp+44h] [ebp-14h]
  _DWORD *i; // [esp+48h] [ebp-10h]

  rf_scratch_arena_rewind_and_clear_owners();
  for ( i = (_DWORD *)rf_receiver_get_first_dword(this + 112); i; i = (_DWORD *)rf_receiver_get_first_dword(this + 112) )
  {
    rf_solid_face_list_remove((int *)this + 28, (int)i);
    rf_geomod_face_destroy(i);
  }
  for ( j = 0; j < rf_receiver_get_first_dword(this + 144); ++j )
  {
    v7 = *(void **)sub_552200((_DWORD *)this + 36, j);
    if ( v7 )
      rf_room460_scalar_deleting_destructor_517cf0(v7, 1);
  }
  rf_pointer_array_release_storage((void **)this + 36);
  rf_pointer_array_release_storage((void **)this + 39);
  rf_pointer_array_release_storage((void **)this + 42);
  for ( k = 0; k < rf_receiver_get_first_dword(this + 120); ++k )
  {
    v1 = (int *)sub_552200((_DWORD *)this + 30, k);
    rf_geomod_vertex_destroy_and_release_to_pool(*v1);
  }
  for ( m = 0; m < rf_receiver_get_first_dword(this + 132); ++m )
  {
    v6 = *(char **)sub_552200((_DWORD *)this + 33, m);
    if ( v6 )
      rf_solid_destroy(v6, 1);
  }
  rf_nav_graph_destroy_nodes_and_storage((_DWORD *)this + 192);
  for ( n = 0; n < rf_receiver_get_first_dword(this + 180); ++n )
  {
    v5 = *(void **)sub_552200((_DWORD *)this + 45, n);
    if ( v5 )
      rf_solid_aux_scalar_deleting_destructor_517d20(v5, 1);
  }
  rf_pointer_array_release_storage((void **)this + 45);
  for ( ii = 0; ii < rf_receiver_get_first_dword(this + 192); ++ii )
  {
    v4 = *(void **)sub_552200((_DWORD *)this + 48, ii);
    if ( v4 )
      rf_lightmap_descriptor_scalar_deleting_destructor(v4, 1);
  }
  rf_pointer_array_release_storage((void **)this + 48);
  for ( jj = 0; jj < rf_receiver_get_first_dword(this + 756); ++jj )
  {
    v3 = *(void **)sub_552200((_DWORD *)this + 189, jj);
    if ( v3 )
      rf_uv_scroll_descriptor_scalar_deleting_destructor(v3, 1);
  }
  rf_pointer_array_release_storage((void **)this + 189);
  if ( *(_DWORD *)this )
    rf_geomod_spatial_tree_destroy_recursive(*(_DWORD *)this);
  *(this + 4) = 0;
  rf_pointer_array_release_storage((void **)this + 216);
  rf_pointer_array_destroy_backing_storage((void **)this + 216);
  rf_pointer_array_destroy_backing_wrapper((void **)this + 192);
  rf_pointer_array_destroy_backing_storage((void **)this + 189);
  rf_shared_noop_destructor_4580d0();
  rf_pointer_array_destroy_backing_storage((void **)this + 57);
  rf_pointer_array_destroy_backing_storage((void **)this + 54);
  rf_pointer_array_destroy_backing_storage((void **)this + 51);
  rf_pointer_array_destroy_backing_storage((void **)this + 48);
  rf_pointer_array_destroy_backing_storage((void **)this + 45);
  rf_pointer_array_destroy_backing_storage((void **)this + 42);
  rf_pointer_array_destroy_backing_storage((void **)this + 39);
  rf_pointer_array_destroy_backing_storage((void **)this + 36);
  rf_pointer_array_destroy_backing_storage((void **)this + 33);
  rf_pointer_array_destroy_backing_storage((void **)this + 30);
}

