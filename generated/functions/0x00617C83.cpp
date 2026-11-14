// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617C83 __setargv
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, startup argv setup0/-1. Initialize mb table
// if needed, zero byte2021DAC (one beyond module-name260 buffer), GetModuleFileNameA(NULL,2021CA8,260) return IGNORED, publish programname2021370=buffer. Choose commandline2022F84 if
// nonNULL/nonempty else module buffer. parse_cmdline count-only into byteCount/slotCount including terminating NULL. Reject UNSIGNED slotCount>=0x3FFFFFFF,byteCount==UINT_MAX,or
// unsigned4*slotCount+byteCount wrap below byteCount. malloc_crt single combined pointer-array+character allocation, NULL ->-1. Reparse into allocation with chars immediately after
// 4*slotCount; publish argc2021354=slots-1,argv2021358=allocation,return0. No wildcard expansion, parse-status check, lock or previous argv free; sizing failure leaves argc/argv
// prior state but module-name globals already changed.
int _setargv()
{
  int v0; // edi
  size_t v1; // eax
  char **v2; // esi
  size_t v4; // [esp+Ch] [ebp-Ch] BYREF
  unsigned int v5; // [esp+10h] [ebp-8h] BYREF
  char *v6; // [esp+14h] [ebp-4h]

  if ( !unk_2022F94 )
    __initmbctable();
  unk_2021DAC = 0;
  GetModuleFileNameA(nullptr, unk_2021CA8, 0x104u);
  unk_2021370 = unk_2021CA8;
  if ( !dword_2022F84 || (v6 = dword_2022F84, !*dword_2022F84) )
    v6 = unk_2021CA8;
  parse_cmdline(v6, &v4, nullptr, nullptr, &v5);
  if ( v5 >= 0x3FFFFFFF )
    return -1;
  if ( v4 == -1 )
    return -1;
  v0 = v5;
  v1 = 4 * v5 + v4;
  if ( v1 < v4 )
    return -1;
  v2 = (char **)_malloc_crt(v1);
  if ( !v2 )
    return -1;
  parse_cmdline(v6, &v4, v2, (char *)&v2[v0], &v5);
  unk_2021354 = v5 - 1;
  unk_2021358 = v2;
  return 0;
}

