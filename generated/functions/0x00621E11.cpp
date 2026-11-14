// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00621E11 __setmode_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Cdecl(rawfd,mode), returns COLLAPSED PREVIOUS mode, no inputvalidation/lock/errno. Snapshotoldflags&0x80 andsigned7-bit oldencoding fromBYTE+36 (bit7excluded). Newmode0x4000:
// setflags80,clearencodinglow7,preservehigh80. New0x8000: clearflags80,LEAVEencodingbyteunchanged. New0x10000 OR0x20000: setflags80,encoding=(oldbyte&0x80)|2.
// New0x40000:setflags80,encoding=(oldbyte&0x80)|1. Othermode leavesrecordunchanged,stillreturnsoldmode. Oldbinaryflagclear ->0x8000; oldtextANDoldencodinglow7==0 ->0x4000;
// oldtextANDANYnonzeroencoding ->0x10000, soUTFkinds are not round-trip-preserved by return. Recordtable refetched between somewrites, no OSSetMode orflush.
int __cdecl _setmode_nolock(int a1, int a2)
{
  int v2; // esi
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  _BYTE *v6; // ecx
  char v7; // dl

  v2 = (a1 & 0x1F) << 6;
  v3 = unk_2021E40[a1 >> 5] + v2;
  v4 = *(_BYTE *)(v3 + 4) & 0x80;
  v5 = (char)(2 * *(_BYTE *)(v3 + 36)) >> 1;
  if ( a2 == 0x4000 )
  {
    *(_BYTE *)(v3 + 4) |= 0x80u;
    *(_BYTE *)(unk_2021E40[a1 >> 5] + v2 + 36) &= 0x80u;
  }
  else if ( a2 == 0x8000 )
  {
    *(_BYTE *)(v3 + 4) &= ~0x80u;
  }
  else
  {
    if ( a2 == 0x10000 || a2 == 0x20000 )
    {
      *(_BYTE *)(v3 + 4) |= 0x80u;
      v6 = (_BYTE *)(unk_2021E40[a1 >> 5] + v2 + 36);
      v7 = *v6 & 0x80 | 2;
    }
    else
    {
      if ( a2 != 0x40000 )
        goto LABEL_11;
      *(_BYTE *)(v3 + 4) |= 0x80u;
      v6 = (_BYTE *)(unk_2021E40[a1 >> 5] + v2 + 36);
      v7 = *v6 & 0x80 | 1;
    }
    *v6 = v7;
  }
LABEL_11:
  if ( v4 )
    return v5 != 0 ? 0x10000 : 0x4000;
  else
    return 0x8000;
}

