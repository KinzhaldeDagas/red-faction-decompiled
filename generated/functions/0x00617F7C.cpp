// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617F7C __rtpiby2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal x87 replacement: FSTP ST0 discards currenttop,FLD TBYTE66509A loads original80-bit3fff:c90fdaa22168c235 (pi/2),RET. Net stack depth unchanged; no GP
// result/flags/CW mutation or scalar memory output. Static constant bytes independently matched to originalPE.
void _rtpiby2()
{
  __asm
  {
    fstp    st; UNREALRED VERIFIED: Complete native adapter contract verified; Internal x87 replacement: FSTP ST0 discards currenttop,FLD TBYTE66509A loads original80-bit3fff:c90fdaa22168c235 (pi/2),RET.
    fld     tbyte_66509A
  }
}

