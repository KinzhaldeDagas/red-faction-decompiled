// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CDE4 ___initstdio
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): FILE32 offsets
// ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28; dynamic critical section+32. Descriptor record R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags
// BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20. Noargs initialization. LIVE signed stream limit2022F80:0->512; otherwise
// signed<20 (including negative)->20; store normalized limit. calloc_crt(limit,4), overwrite pointer2021F68. Failure force limit20, retrycalloc20x4 andoverwrite pointer;
// secondfailure return26, leavingNULL global. Success fill first20 entries with static FILE addresses664DE0+i*32, ending665060 exclusive; extra slots rely on calloc zeroing. For
// standard fds0..2 read descriptor handle; raw0,-1,-2 sets corresponding static FILE fd field=-2, valid handles leave that field unchanged. Does not query GetStdHandle, set active
// flags, initialize all FILE fields, lock table, free old pointer array or roll back failed initialization. Return0 on success; signed bounds and address-stop constants independently
// checked.
int __initstdio()
{
  size_t v0; // eax
  int v1; // eax
  int v3; // edx
  _UNKNOWN **v4; // ecx
  int v5; // edx
  _DWORD *v6; // ecx
  int v7; // eax

  v0 = dword_2022F80;
  if ( !dword_2022F80 )
  {
    v0 = 512;
LABEL_5:
    dword_2022F80 = v0;
    goto LABEL_6;
  }
  if ( dword_2022F80 < 20 )
  {
    v0 = 20;
    goto LABEL_5;
  }
LABEL_6:
  v1 = _calloc_crt(v0, 4);
  unk_2021F68 = v1;
  if ( !v1 )
  {
    dword_2022F80 = 20;
    v1 = _calloc_crt(0x14u, 4);
    unk_2021F68 = v1;
    if ( !v1 )
      return 26;
  }
  v3 = 0;
  v4 = &off_664DE0;
  while ( 1 )
  {
    *(_DWORD *)(v3 + v1) = v4;
    v4 += 8;
    v3 += 4;
    if ( (int)v4 >= (int)off_665060 )
      break;
    v1 = unk_2021F68;
  }
  v5 = 0;
  v6 = &unk_664DF0;
  do
  {
    v7 = *(_DWORD *)(((v5 & 0x1F) << 6) + unk_2021E40[v5 >> 5]);
    if ( v7 == -1 || v7 == -2 || !v7 )
      *v6 = -2;
    v6 += 8;
    ++v5;
  }
  while ( (int)v6 < (int)dword_664E50 );
  return 0;
}

