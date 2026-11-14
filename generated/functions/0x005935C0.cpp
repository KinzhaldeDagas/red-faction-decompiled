// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005935C0 rf_vfile_has_nonnegative_stream_slot
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile. Returns ALtrue iff SIGNED receiver DWORD+272>=0. Does not validate upper bound4, corresponding global slot ownership/mode or FILE/member pointer. Constructor5923E0 sets-1 and close593210 resets-1.
bool __thiscall rf_vfile_has_nonnegative_stream_slot(_DWORD *this)
{
  return *(this + 68) >= 0;
}

