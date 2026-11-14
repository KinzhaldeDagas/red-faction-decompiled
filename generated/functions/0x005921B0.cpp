// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005921B0 rf_vfile_find_vpp_member_and_store_pointer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): STDCALL filename and output DWORD pointer (RET8), no ECX receiver. Calls rf_vpackfile_find and stores result even on miss (NULL), returns AL result!=0. VPP helper canonicalizes final-backslash basename and performs case-insensitive member lookup. Does not open archive/member or allocate/copy output; no NULL-output guard.
bool __stdcall rf_vfile_find_vpp_member_and_store_pointer(char *Str, _DWORD *a2)
{
  *a2 = rf_vpackfile_find(Str);
  return *a2 != 0;
}

