// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611578 __invalid_parameter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl five diagnostic slots. Decode LIVE handler global20216F8. NonNULL restores own EBP frame then TAIL JMP handler, preserving all FIVE ORIGINAL caller
// stack arguments and returnPC (not zero-argument invocation). NULL path calls crt_clear_dword_02021e1c with ignored rawslot2, reclaims4,restoresframe,TAIL JMP invoke_watson with
// original five slots. No own errno assignment/handler catch or Boolean result; Watson policy nonreturn delegated. Clear helper only ANDs global0 and ignores2.
int __cdecl _invalid_parameter(
        const wchar_t *Expression,
        const wchar_t *FunctionName,
        const wchar_t *FileName,
        unsigned int LineNo,
        uintptr_t Reserved)
{
  int (*v5)(void); // eax

  v5 = (int (*)(void))_decode_pointer(unk_20216F8);
  if ( !v5 )
  {
    crt_clear_dword_02021e1c();
    _invoke_watson(Expression, FunctionName, FileName, LineNo, Reserved);
  }
  return v5();
}

