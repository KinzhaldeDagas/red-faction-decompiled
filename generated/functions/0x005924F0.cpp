// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005924F0 rf_vfile_get_filename_buffer_pointer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile. Returns receiver+5, borrowed writable cstring buffer containing resolved filename/path, without copying, basename stripping, allocation or state checks. Pointer lifetime follows receiver.
char *__thiscall rf_vfile_get_filename_buffer_pointer(char *this)
{
  return this + 5;
}

