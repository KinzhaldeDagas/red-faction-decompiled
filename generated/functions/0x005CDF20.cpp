// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CDF20 rf_scene_instance_stop_and_drain_particles
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): If runtime flags mask0x1 not set,sets it then ORs mask0x1 into each164-byte emitter state flags+16,disabling new particle spawn. Already-draining state does no traversal. Does not clear existing particles,reset time,mark inactive immediately or release resources; later update drains until live counts0. Returns receiver bits incidentally.
_DWORD *__thiscall rf_scene_instance_stop_and_drain_particles(_DWORD *this)
{
  _DWORD *result; // eax
  int i; // [esp+4h] [ebp-4h]

  result = this;
  if ( (*this & 1) == 0 )
  {
    *this |= 1u;
    for ( i = 0; ; ++i )
    {
      result = this;
      if ( i >= *(_DWORD *)(*(this + 2) + 92) )
        break;
      *(_DWORD *)(*(this + 7) + 164 * i + 16) |= 1u;
    }
  }
  return result;
}

