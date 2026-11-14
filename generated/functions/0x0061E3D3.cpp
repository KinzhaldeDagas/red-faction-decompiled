// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E3D3 ___free_lconv_num
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Cdecl(lconvPointer),void;correctedfalseintargumenttopointer. NULL->return.
// Independentlyfreefirstthreepointerfieldsat0/4/8UNLESSeachmatchesLIVEpointerVALUEloadedfromglobal66607C/666080/666084respectively.
// ComparisonisnotagainstADDRESSofthoseglobals;sharedliteralidentityprotectedonlybycorrespondingfielddefault.
// DoesNOTfreeouterlconv,clearfields,checkrefcounts,lockordetectalias/duplicatepointers;NULLfielddifferentfromdefaultmaystillbepassedtofree(NULL). No ownerrnoorinvalidcallback.
void __cdecl __free_lconv_num(void **a1)
{
  void *v1; // esi

  if ( a1 )
  {
    if ( *a1 != off_66607C )
      free(*a1);
    if ( a1[1] != off_666080 )
      free(a1[1]);
    v1 = a1[2];
    if ( v1 != off_666084 )
      free(v1);
  }
}

