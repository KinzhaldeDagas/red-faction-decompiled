// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F6EE0 rf_scene_key_tracks_construct_empty
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 20-byte track set:unsigned WORD counts0/2/4=0,three stream pointers DWORD8/12/16=NULL. Padding6/7 untouched. Streams0 and2 use40-byte vector keys;stream1 uses20-byte packed quaternion keys. Does not allocate/free or initialize key storage;no meaningful return. Used by scene loader0x5CAF80 array constructor iterator.
void __thiscall rf_scene_key_tracks_construct_empty(_DWORD *this)
{
  *(_WORD *)this = 0;
  *(this + 2) = 0;
  *((_WORD *)this + 1) = 0;
  *(this + 3) = 0;
  *((_WORD *)this + 2) = 0;
  *(this + 4) = 0;
}

