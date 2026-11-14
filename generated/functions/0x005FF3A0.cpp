// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF3A0 rf_jpeg_alloc_huff_table
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcomapi.c:jpeg_alloc_huff_table matched): Allocates280bytesfrompermanentpool0 viaalloc_small;setssent_table276=FALSE0,returnstablepointer. Leaves17bitsbytes and256symbolbytesuninitialized;callerpopulates. No slotinstallationorstatecheck.
int __cdecl rf_jpeg_alloc_huff_table(int a1)
{
  int result; // eax

  result = (**(int (__cdecl ***)(int, _DWORD, int))(a1 + 4))(a1, 0, 280);
  *(_DWORD *)(result + 276) = 0;
  return result;
}

