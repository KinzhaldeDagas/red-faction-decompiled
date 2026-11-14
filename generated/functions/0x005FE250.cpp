// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FE250 rf_jpeg_out_of_memory
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:out_of_memory matched): Localcdecl(cinfo,caseCode). Storeserror54 OutOfMemory inerr.msg_code20,caseCode intoerr.msg_parm24,thenerr.error_exit(cinfo). No allocation,cleanup orNULLreturnpolicy here;defaultcallback exits,butcaller overridesmustnotreturnnormally. APIvoid;incidentalcallback result.
int __cdecl rf_jpeg_out_of_memory(int a1, int a2)
{
  *(_DWORD *)(*(_DWORD *)a1 + 20) = 54;
  *(_DWORD *)(*(_DWORD *)a1 + 24) = a2;
  return (**(int (__cdecl ***)(int))a1)(a1);
}

