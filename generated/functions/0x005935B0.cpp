// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005935B0 rf_vfile_get_root_id
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile. Returns receiver DWORD0 root/search-context id in EAX. No pointer chasing, range validation, allocation or stream-state check; existing unknown_libname_37 library flag retained.
int __thiscall rf_vfile_get_root_id(void *this)
{
  return *(_DWORD *)this;
}

