// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00563F20 rf_model_handle_allocate_initialized
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): No incoming receiver used:ECX overwritten by global pool17F1120 before allocation. Corrected cdecl(void). Allocates88byte handle, sets tag0=0,instance4=0,definition8=0,material pointer80=0,byte84=0. Filename12..76 and padding not cleared. Raw poolNULL dereferenced unconditionally; no constructor/resource load.
void *__cdecl rf_model_handle_allocate_initialized()
{
  void *result; // eax

  result = rf_model_handle88_pool_allocate_raw(dword_17F1120);
  *(_DWORD *)result = 0;
  *((_DWORD *)result + 2) = 0;
  *((_DWORD *)result + 1) = 0;
  *((_DWORD *)result + 20) = 0;
  *((_BYTE *)result + 84) = 0;
  return result;
}

