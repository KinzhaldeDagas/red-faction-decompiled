// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4410 rf_character_dispatch_morph_sample
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Resolves clip from instance action record/base-character handle list. Copies all mesh base positions into shared scratch18CDA30 using12*uint16 mesh vertex count, then calls morph sampler with scratch, nominal count,current integer record tick unchanged, mesh remap pointer+36 and caller field+68. No endpoint adjustment for legacy version7; sampler ignores nominal count and final argument. No independent destination-scratch capacity, action index, remap or clip pointer guard. Returns sampler incidental register.
char *__cdecl rf_character_dispatch_morph_sample(int a1, int a2, int a3, int a4)
{
  void *v5; // [esp+4h] [ebp-4h]

  v5 = *(void **)(*(_DWORD *)(a3 + 7504) + 4 * *(_DWORD *)(a3 + 12 * a4 + 4820) + 3932);
  memcpy(&unk_18CDA30, *(const void **)(a2 + 4), 12 * *(unsigned __int16 *)(a2 + 40));
  return rf_rfa_sample_morph_vertices(
           v5,
           (int)&unk_18CDA30,
           *(unsigned __int16 *)(a2 + 40),
           *(_DWORD *)(a3 + 12 * a4 + 4824),
           *(_DWORD *)(a2 + 36),
           *(_DWORD *)(a1 + 68));
}

