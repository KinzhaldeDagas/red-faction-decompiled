// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006174A0 __IsNonwritableInCurrentImage
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(address), canonicalBOOL, fixed current
// imagebase0x400000 (not dynamic module discovery). InlineEH4 scope65EEA0 guardsValidateImageBase(400000),FindPESection(400000,address-400000 wrapped),sectionCharacteristics+36 read.
// Invalidheaders/no matchingsection ->0. Matchingsection ->1 iff bit31/0x80000000 WRITE flagCLEAR,else0. DoesNOTdereference inputtargetaddress, querypageprotection, testread/execute
// bits orrequirepointertofunction. Filter61752B returns1 ONLYfor0xC0000005 accessviolation,handler61753F restoresESP andreturns0; otherexceptionscontinue search.
// Normal/handledreturns restoreFS:0 registration; originalPEscopebytes verified.
BOOL __cdecl _IsNonwritableInCurrentImage(int a1)
{
  int PESection; // eax

  return _ValidateImageBase(0x400000)
      && (PESection = _FindPESection(0x400000, a1 - 0x400000)) != 0
      && *(int *)(PESection + 36) >= 0;
}

