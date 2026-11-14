// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004123C0 rf_camera_slot_clear_room
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): One cdecl slot pointer. Reads slot DWORD0 into ECX and invokes4BC210(camera,room=NULL), returning delegated EAX=0 unchanged.
// Delegate first copies camera COMMON position+60 into cached position+4, then writes room DWORD0=NULL; does not resolve or link rooms. No slot/camera guards, player/state/handle
// writes or object deletion. Does not merely overwrite first camera DWORD: position cache is updated even with roomNULL.
int __cdecl rf_camera_slot_clear_room(float **a1)
{
  return rf_object_set_room_and_cache_position(*a1, 0);
}

