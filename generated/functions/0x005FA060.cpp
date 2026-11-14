// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA060 rf_com_audio_backend_shutdown
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments, void. ANY nonzero readyBYTE1F6A960 admits shutdown, unlike initializer exact==1 shortcut. For each nonnull interface in
// order1F6A958,1F6A954,1F6A950, call vtable+8 Release with ONE explicitly pushed object DWORD and stdcall cleanup. Middle call is NOT a two-argument thiscall despite misleading
// pseudocode ECX value; native push proves actual stack contract. Ignore release results; do NOT null global pointers. Then CoUninitialize once and clear readyBYTE0. If flag0, skip
// ALL release/apartment work even if partial initializer left pointers; thus failure-path resources are not recovered here. No Close method, reference-loop, retry or ownership/thread
// check.
void rf_com_audio_backend_shutdown()
{
  if ( byte_1F6A960[0] )
  {
    if ( unk_1F6A958 )
      (*(void (__stdcall **)(_DWORD))(*unk_1F6A958 + 8))(unk_1F6A958);
    if ( dword_1F6A954 )
      (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1F6A954 + 8))(dword_1F6A954, dword_1F6A954);
    if ( unk_1F6A950 )
      (*(void (__stdcall **)(LPVOID))(*(_DWORD *)unk_1F6A950 + 8))(unk_1F6A950);
    CoUninitialize();
    byte_1F6A960[0] = 0;
  }
}

