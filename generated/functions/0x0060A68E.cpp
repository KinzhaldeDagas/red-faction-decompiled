// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A68E __init_pointers
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs returns ENCODED pointer value PVOID, not
// directly callable function pointer (corrected stored return type). Compute encoded_null, pass identical raw DWORD to five setters for20216F0,2021CA0,20216F8,2021C9C,2021C90 and
// initp_misc_winsig (raw copies to2021C7C/80/84/88). Also push encoded_null before noop60598A and noargs initp_eh_hooks_0; both ignore those extra stack slots. EH hook helper
// independently encodes fixed terminate pointer into20213C0, rather than storing passed encoded_null. Finally encode quick _exit60A65A, store off664D58, return encoded EAX. Nine
// pushed DWORDs cleaned by ADD ESP,36. No own once guard, lock, pointer decoding or callback invocation.
PVOID __cdecl _init_pointers()
{
  PVOID v0; // esi
  PVOID result; // eax

  v0 = _encoded_null();
  crt_store_dword_020216f0((int)v0);
  crt_store_dword_02021ca0((int)v0);
  crt_store_dword_020216f8((int)v0);
  crt_store_dword_02021c9c((int)v0);
  crt_store_dword_02021c90((int)v0);
  _initp_misc_winsig((int)v0);
  crt_noop_ret_0060598a();
  _initp_eh_hooks_0();
  result = _encode_pointer(_exit);
  off_664D58 = (void (__cdecl __noreturn *)(int))result;
  return result;
}

