// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005923E0 rf_vfile_construct_unopened
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Thiscall VFile receiver, returns receiver pointer in EAX. Sets filename first byte+5=0, packed-member pointer/index DWORD+264=0, stream-slot DWORD+272=-1, resolved/existing byte+4=0. Leaves root id+0, media byte+268, remainder of filename storage and other fields untouched; installs no vtable. Callers provide at least280-byte stack storage. Does not open, allocate or register a file.
void *__thiscall rf_vfile_construct_unopened(void *self)
{
  *((_BYTE *)self + 5) = 0;
  *((_DWORD *)self + 66) = 0;
  *((_DWORD *)self + 68) = -1;
  *((_BYTE *)self + 4) = 0;
  return self;
}

