// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515F80 rf_room_face_spatial_tree_rebuild
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, embedded cutter literal geometry,all vertex/index/UV words and registry/procedural accessors,original ECX/stack flow and PE bytes): Thiscall room,no stack args. If rootDWORD60 nonnull, recursively destroy it then clear root60. Always allocate replacement40-byte node and immediately store root60,then invoke THISCALL build(root,roomFaceList40),forward itsEAX result. Does not preserve old tree or test allocation/build failure,clear room face-list,detach room ownership or rebuild solid bounds. Builder receives counted intrusive room list,not solid+112 or decal links; it assigns actual spatial face ownership72. NoNULLroom check and no transactional recovery to old tree. Embedded cutter invokes after finalizing/attaching all its faces.
int __thiscall rf_room_face_spatial_tree_rebuild(int *this)
{
  if ( *(this + 15) )
  {
    rf_geomod_spatial_tree_destroy_recursive(*(this + 15));
    *(this + 15) = 0;
  }
  *(this + 15) = (int)rf_geomod_spatial_node_allocate();
  return rf_spatial_tree_build_from_face_list(*(this + 15), this + 10);
}

