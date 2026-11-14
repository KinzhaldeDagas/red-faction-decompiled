// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005924C0 rf_vfile_set_open_slot_version
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile and integer version. Uses receiver DWORD+272 as slot index, writes version at slot189CEB0+32832*index+8, returns receiver. No open-state, index-range or supported-version validation. Matches existing get_slot_version5924A0 and version-dependent stream readers.
_DWORD *__thiscall rf_vfile_set_open_slot_version(_DWORD *this, int a2)
{
  unk_189CEB8[8208 * *(this + 68)] = a2;
  return this;
}

