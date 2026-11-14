// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595D30 rf_scene_point_track_release_pool_slot
// UNREALRED VERIFIED [transfer-scene-20261028]: Thiscall runtime record. If signed slot index+56>=0, calls0x5963A0 to mark scene-point pool record unused. Does not reset stored index, clear definition or flags, or validate upper bound50.
void __thiscall rf_scene_point_track_release_pool_slot(int *this)
{
  if ( *(this + 14) >= 0 )
    rf_scene_point_pool_release_index(*(this + 14));
}

