// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E1A6 __mtterm
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): No arguments, teardown with no semantic status. If
// provider index6650C0!=-1, decode global20213BC and indirect stdcall free(index), ignore return, THEN set index=-1. If getter TLS index6650C4!=-1, TlsFree(index), ignore BOOL, set
// it=-1. Tail-jump mtdeletelocks. Does not clear encoded provider globals or explicitly free a local uninstalled PTD allocation. Provider pointer has no NULL guard; reset happens
// after call, not before. Corrected void prototype: final EAX is teardown residue rather than success code; sole direct caller immediately XORs EAX0.
void __cdecl _mtterm()
{
  void (__stdcall *v0)(int); // eax
  int v1; // [esp-4h] [ebp-4h]

  if ( dword_6650C0 != -1 )
  {
    v1 = dword_6650C0;
    v0 = (void (__stdcall *)(int))_decode_pointer(unk_20213BC);
    v0(v1);
    dword_6650C0 = -1;
  }
  if ( dwTlsIndex != -1 )
  {
    TlsFree(dwTlsIndex);
    dwTlsIndex = -1;
  }
  _mtdeletelocks();
}

