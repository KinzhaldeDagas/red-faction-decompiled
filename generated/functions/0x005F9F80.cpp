// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F9F80 rf_com_audio_backend_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one rawDWORD caller argument; used by5BFEC0 sound backend mode2 admission. ReadyBYTE1F6A960==EXACTLY1 returns0 immediately; other nonzero values still
// initialize. Call CoInitialize(NULL), IGNORE HRESULT. CoCreateInstance(CLSID bytes664B88,IID664BB8,outerNULL,context1,out1F6A950); signed HRESULT<0 returns-1 without
// CoUninitialize/cleanup. Success makes stdcall virtual(slot+60)(object,0,0,0), then(slot+76)(object,callerArg,1); BOTH results ignored. QueryInterface slot0 with
// IID664BA8,out1F6A954; negative result returns-1 with prior interface retained. Next QueryInterface IID664B98,out1F6A958; negative result also returns-1 without releasing any
// earlier interfaces/COM apartment. Only all checked calls nonnegative sets readyBYTE1 and returns0. Does not zero outputs first or validate pointers after nonnegative HRESULT; no
// rollback. Descriptive COM/audio name avoids inferring interface identities from GUID alone; exact64 GUID bytes independently matched to original PE.
int __cdecl rf_com_audio_backend_initialize(int a1)
{
  if ( byte_1F6A960[0] == 1 )
    return 0;
  CoInitialize(nullptr);
  if ( CoCreateInstance(&stru_664B88, nullptr, 1u, &stru_664BB8, &unk_1F6A950) < 0 )
    return -1;
  (*(void (__stdcall **)(LPVOID, _DWORD, _DWORD, _DWORD))(*(_DWORD *)unk_1F6A950 + 60))(unk_1F6A950, 0, 0, 0);
  (*(void (__stdcall **)(LPVOID, int, int))(*(_DWORD *)unk_1F6A950 + 76))(unk_1F6A950, a1, 1);
  if ( (**(int (__stdcall ***)(LPVOID, void *, void *))unk_1F6A950)(unk_1F6A950, &unk_664BA8, &unk_1F6A954) < 0 )
    return -1;
  if ( (**(int (__stdcall ***)(LPVOID, void *, void *))unk_1F6A950)(unk_1F6A950, &unk_664B98, &unk_1F6A958) < 0 )
    return -1;
  byte_1F6A960[0] = 1;
  return 0;
}

