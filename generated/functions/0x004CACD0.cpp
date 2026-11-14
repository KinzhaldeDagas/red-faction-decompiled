// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CACD0 rf_particle_pools_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl initialization of two 252-byte pool descriptors: 0x866600 -> 500 records at 0x857BA0; 0x8666FC -> 1100 records at 0x837800. Each descriptor stores base at +0, capacity +4,
// embedded free sentinel +8, embedded unowned active sentinel +128, active count +248. Self-links both sentinels and clears active count. For each 120-byte record, clears DWORD flags
// +88 and WORD packed flags +78, then appends it to the free list using links +0/+4. No full record memset, payload constructor, or detachment from former emitter-owned lists occurs
// here.
// Resets debug peak 0x8377E0 to 0, double sample sum 0x8377E8 to 0, and sample divisor/counter 0x662DF0 to 1. Does not reset moved/rendered counters or cached particle world. The HUD
// consequently starts with a zero-valued implicit sample in its divisor. Return register is incidental, not a success/count API.
_DWORD *rf_particle_pools_initialize()
{
  _DWORD *result; // eax
  int i; // [esp+0h] [ebp-8h]
  int j; // [esp+0h] [ebp-8h]

  unk_866604 = 500;
  unk_866600 = &unk_857BA0;
  unk_866608 = &unk_866608;
  dword_86660C[0] = (int)&unk_866608;
  dword_866680 = &dword_866680;
  unk_866684 = &dword_866680;
  unk_8666F8 = 0;
  for ( i = 0; i < unk_866604; ++i )
  {
    *(_DWORD *)(unk_866600 + 120 * i + 88) = 0;
    *(_WORD *)(unk_866600 + 120 * i + 78) = 0;
    *(_DWORD *)(unk_866600 + 120 * i + 4) = dword_86660C[0];
    *(_DWORD *)(120 * i + unk_866600) = &unk_866608;
    *(_DWORD *)dword_86660C[0] = unk_866600 + 120 * i;
    dword_86660C[0] = unk_866600 + 120 * i;
  }
  dword_866700 = 1100;
  unk_8666FC[0] = &unk_837800;
  unk_866704 = &unk_866704;
  unk_866708 = &unk_866704;
  unk_86677C[0] = unk_86677C;
  result = unk_8666FC;
  unk_866780 = unk_86677C;
  unk_8667F4 = 0;
  for ( j = 0; j < dword_866700; ++j )
  {
    *(_DWORD *)(unk_8666FC[0] + 120 * j + 88) = 0;
    *(_WORD *)(unk_8666FC[0] + 120 * j + 78) = 0;
    *(_DWORD *)(unk_8666FC[0] + 120 * j + 4) = unk_866708;
    *(_DWORD *)(120 * j + unk_8666FC[0]) = &unk_866704;
    *unk_866708 = unk_8666FC[0] + 120 * j;
    unk_866708 = unk_8666FC[0] + 120 * j;
    result = (_DWORD *)(j + 1);
  }
  unk_8377E0 = 0;
  unk_8377E8 = 0.0;
  dword_662DF0 = 1;
  return result;
}

