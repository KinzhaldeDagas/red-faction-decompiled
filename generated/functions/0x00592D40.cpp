// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592D40 rf_vfile_set_feedback_xor_seed_or_disable
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall open VFile and seed. Nonzero seed ORs slot flags DWORD+4 with1, creates three-word seed array[seed,0,0] and initializes12-byte feedback state at slot+32820 via5EDE40. That helper copies nonzero first seed and replaces zero second/third with1816682354/1540656698. Returns state pointer on enabled path for these seeds. Zero seed only clears flag1 and returns VFile receiver, preserving prior state words. No slot/open validation, allocation or entropy generation; no consistent chaining pointer across branches.
void *__thiscall rf_vfile_set_feedback_xor_seed_or_disable(void *self, unsigned int seed)
{
  _DWORD v3[3]; // [esp+4h] [ebp-Ch] BYREF

  if ( seed )
  {
    dword_189CEB4[8208 * *((_DWORD *)self + 68)] |= 1u;
    v3[0] = seed;
    v3[2] = 0;
    v3[1] = 0;
    return rf_feedback_xor_state_set_nonzero_seeds(&dword_18A4EE4[8208 * *((_DWORD *)self + 68)], v3);
  }
  else
  {
    dword_189CEB4[8208 * *((_DWORD *)self + 68)] &= ~1u;
    return self;
  }
}

