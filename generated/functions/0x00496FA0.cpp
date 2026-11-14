// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496FA0 rf_ctf_register_flag_home
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(item). Instance DWORD +700 bit20 selects red, otherwise blue regardless of actual item category. Stores selected global flag pointer, common position +60, common matrix +72
// and room DWORD0 as home pose. Red globals: pointer77D6E4/position77D714/matrix77D6EC/room77D6D0; blue77D6E8/77D720/77D738/77D6D4. Sets initialized byte77D6E2=1 after EITHER
// registration; does not require both flags. No mode, authority, type or null guard; no allocation, carrier/counter/timer reset. Return register is room-getter artifact.
int __cdecl rf_ctf_register_flag_home(int a1)
{
  int result; // eax
  float v2[3]; // [esp+0h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-Ch] BYREF

  if ( (*(_DWORD *)(a1 + 700) & 0x20) != 0 )
  {
    dword_77D6E4 = a1;
    rf_vector_copy(unk_77D714, copy_result, (const float *)(a1 + 60));
    rf_matrix3_copy(&flt_77D6EC, (const float *)(a1 + 72));
    result = rf_receiver_get_first_dword((void *)a1);
    unk_77D6D0 = result;
  }
  else
  {
    dword_77D6E8 = a1;
    rf_vector_copy(unk_77D720, v2, (const float *)(a1 + 60));
    rf_matrix3_copy(&flt_77D738, (const float *)(a1 + 72));
    result = rf_receiver_get_first_dword((void *)a1);
    unk_77D6D4 = result;
  }
  byte_77D6E2 = 1;
  return result;
}

