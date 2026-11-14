// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061FAD6 crt_ld12_to_binary32
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl(source12,destination). Read unsigned signExponent WORD+10; preserve signbit15 and e=(exponent&0x7fff)-16383. Build96-bit work words high-to-low
// W=[DWORDsource+6,DWORDsource+2,WORDsource+0<<16]; source is not overwritten (argument stack slot reused as scratch). Integer-only conversion, no x87/floating rounding-mode
// dependency, heap, errno or explicit helper calls. Six LIVE parameter DWORDs drive all arithmetic; no range/index/NULL/overlap validation. Original source exp0 and all W zero
// ->signed zero,status0; exp0 and any W nonzero ->signed zero,status2. Otherwise save original W/e. Rounding helper tests guard bit at index P from high end; ONLY guard1 AND any
// lower sticky bit causes increment of retained bit P-1 with carry across words; exact halfway leaves magnitude unchanged regardless retained parity. Clear bits below guard and
// following words; initial carry increments e. If rounded e<m-P ->zero fraction,biased exponent0,status2. If m-P<=rounded e<=m: restore ORIGINAL unrounded W, shift right by
// m-original_e, repeat same guard/sticky rounding, then shift right by S+1,biased exponent0,status2 even for nonzero subnormal result. If m<rounded e<M: clear leading explicit bit,
// shift right by S,biased exponent=e+B,status0. If rounded e>=M: replace W with leading bit only,shift by S,biased exponent=M+B,status1 (infinity); no separate NaN/payload branch, so
// exp0x7fff also takes range overflow. Pack high word=workHigh OR sign0x80000000 OR(biasedExponent<<(31-S)); configured width64 writes destination+4 high FIRST, then destination0
// low; width32 writes high to destination0,other widths leave destination untouched. Parameter changes are not validated and native shifts use x86 masked counts. Original PE
// table006660DC=[M128,m-127,P24,S8,width32,B127]. Thus normal binary32 exponent/fraction packing; raw statuses0 normal/zero,1 overflow,2 underflow. All518 native instructions and1348
// bytes independently paired with other precision after ONLY six absolute parameter-address substitutions (+24); every branch/displacement otherwise byte-identical. This precise
// rounding/subnormal algorithm is recorded instead of claiming general ties-to-even/NaN-preserving IEEE conversion.
int __cdecl crt_ld12_to_binary32(const unsigned __int8 *a1, unsigned int *a2)
{
  __int16 v2; // bx
  int v3; // ebx
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int result; // eax
  int v8; // esi
  unsigned int *v9; // edi
  int v10; // eax
  bool i; // zf
  int v12; // eax
  unsigned int v13; // edx
  unsigned int *v14; // ecx
  bool v15; // cf
  unsigned int v16; // esi
  int v17; // eax
  int v18; // edx
  int *v19; // ebx
  unsigned int v20; // esi
  char v21; // cl
  int v22; // edx
  unsigned int *v23; // ecx
  int v24; // esi
  int v25; // eax
  unsigned int *v26; // ebx
  bool j; // zf
  int v28; // eax
  unsigned int v29; // edx
  unsigned int *v30; // ecx
  unsigned int v31; // edi
  int k; // ecx
  unsigned int *v33; // ecx
  unsigned int v34; // esi
  int v35; // edi
  int v36; // eax
  int v37; // edx
  int *v38; // ebx
  unsigned int v39; // esi
  char v40; // cl
  int v41; // edx
  unsigned int *v42; // ecx
  int v43; // eax
  int v44; // edx
  int *v45; // ebx
  unsigned int v46; // esi
  char v47; // cl
  int v48; // edx
  unsigned int *v49; // ecx
  int v50; // eax
  int v51; // edx
  unsigned int v52; // edi
  int v53; // edx
  unsigned int *v54; // ecx
  unsigned int v55; // ebx
  unsigned int v56; // edx
  unsigned int v57; // [esp+8h] [ebp-2Ch]
  unsigned int v58; // [esp+Ch] [ebp-28h]
  int v59; // [esp+10h] [ebp-24h]
  unsigned int v60; // [esp+14h] [ebp-20h] BYREF
  unsigned int v61; // [esp+18h] [ebp-1Ch]
  int v62; // [esp+1Ch] [ebp-18h] BYREF
  int v63; // [esp+20h] [ebp-14h]
  int v64; // [esp+24h] [ebp-10h]
  int v65; // [esp+28h] [ebp-Ch]
  int v66; // [esp+2Ch] [ebp-8h]
  int v67; // [esp+30h] [ebp-4h]
  const unsigned __int8 *v68; // [esp+3Ch] [ebp+8h]
  const unsigned __int8 *v69; // [esp+3Ch] [ebp+8h]
  const unsigned __int8 *v70; // [esp+3Ch] [ebp+8h]
  int v71; // [esp+3Ch] [ebp+8h]
  const unsigned __int8 *v72; // [esp+3Ch] [ebp+8h]
  const unsigned __int8 *v73; // [esp+3Ch] [ebp+8h]
  const unsigned __int8 *v74; // [esp+3Ch] [ebp+8h]

  v2 = *((_WORD *)a1 + 5);
  v63 = v2 & 0x8000;
  v60 = *(_DWORD *)(a1 + 6);
  v3 = (v2 & 0x7FFF) - 0x3FFF;
  v4 = *(unsigned __int16 *)a1 << 16;
  v61 = *(_DWORD *)(a1 + 2);
  v62 = v4;
  if ( v3 != -16383 )
  {
    v68 = nullptr;
    v57 = v60;
    v58 = v61;
    v59 = v62;
    v8 = dword_6660E4 - 1;
    v64 = v3;
    v65 = dword_6660E4 / 32;
    v9 = &v60 + dword_6660E4 / 32;
    v66 = 31 - dword_6660E4 % 32;
    if ( ((1 << (31 - dword_6660E4 % 32)) & *v9) != 0 )
    {
      v10 = v65;
      for ( i = (~(-1 << (31 - dword_6660E4 % 32)) & *(&v60 + v65)) == 0; i; i = *(&v60 + v10) == 0 )
      {
        if ( ++v10 >= 3 )
          goto LABEL_22;
      }
      v12 = v8 / 32;
      v67 = 0;
      v13 = 1 << (31 - v8 % 32);
      v14 = &v60 + v8 / 32;
      v69 = (const unsigned __int8 *)(v13 + *v14);
      if ( (unsigned int)v69 >= *v14 )
      {
        v15 = (unsigned int)v69 < v13;
        goto LABEL_18;
      }
LABEL_19:
      v67 = 1;
      while ( 1 )
      {
        --v12;
        *v14 = (unsigned int)v69;
        if ( v12 < 0 || !v67 )
          break;
        v67 = 0;
        v14 = &v60 + v12;
        v16 = *v14 + 1;
        v69 = (const unsigned __int8 *)v16;
        if ( v16 >= *v14 )
        {
          v15 = v16 == 0;
LABEL_18:
          if ( !v15 )
            continue;
        }
        goto LABEL_19;
      }
      v68 = (const unsigned __int8 *)v67;
    }
LABEL_22:
    *v9 &= -1 << v66;
    if ( v65 + 1 < 3 )
      memset(&v60 + v65 + 1, 0, 4 * (3 - (v65 + 1)));
    if ( v68 )
      ++v3;
    if ( v3 >= dword_6660E0 - dword_6660E4 )
    {
      if ( v3 > dword_6660E0 )
      {
        if ( v3 < dword_6660DC )
        {
          v60 &= ~0x80000000;
          v5 = dword_6660F0 + v3;
          v50 = dword_6660E8 / 32;
          v51 = dword_6660E8 % 32;
          v65 = 0;
          v74 = nullptr;
          v67 = 32 - dword_6660E8 % 32;
          do
          {
            v52 = *(&v60 + (_DWORD)v74);
            v64 = ~(-1 << v51) & v52;
            *(&v60 + (_DWORD)v74++) = v65 | (v52 >> v51);
            v65 = v64 << v67;
          }
          while ( (int)v74 < 3 );
          v53 = 2;
          v54 = (unsigned int *)(&v62 - v50);
          do
          {
            if ( v53 < v50 )
              *(&v60 + v53) = 0;
            else
              *(&v60 + v53) = *v54;
            --v53;
            --v54;
          }
          while ( v53 >= 0 );
          result = 0;
        }
        else
        {
          v61 = 0;
          v62 = 0;
          v60 = 0x80000000;
          v43 = dword_6660E8 / 32;
          v44 = dword_6660E8 % 32;
          v65 = 0;
          v73 = nullptr;
          v67 = 32 - dword_6660E8 % 32;
          do
          {
            v45 = (int *)(&v60 + (_DWORD)v73);
            v46 = *v45;
            v64 = ~(-1 << v44) & *v45;
            v47 = v67;
            *v45 = v65 | (v46 >> v44);
            ++v73;
            v65 = v64 << v47;
          }
          while ( (int)v73 < 3 );
          v48 = 2;
          v49 = (unsigned int *)(&v62 - v43);
          do
          {
            if ( v48 < v43 )
              *(&v60 + v48) = 0;
            else
              *(&v60 + v48) = *v49;
            --v48;
            --v49;
          }
          while ( v48 >= 0 );
          v5 = dword_6660F0 + dword_6660DC;
          result = 1;
        }
        goto LABEL_79;
      }
      v60 = v57;
      v61 = v58;
      v17 = (dword_6660E0 - v64) / 32;
      v62 = v59;
      v18 = (dword_6660E0 - v64) % 32;
      v65 = 0;
      v70 = nullptr;
      v67 = 32 - v18;
      do
      {
        v19 = (int *)(&v60 + (_DWORD)v70);
        v20 = *v19;
        v64 = ~(-1 << v18) & *v19;
        v21 = v67;
        *v19 = v65 | (v20 >> v18);
        ++v70;
        v65 = v64 << v21;
      }
      while ( (int)v70 < 3 );
      v22 = 2;
      v23 = (unsigned int *)(&v62 - v17);
      do
      {
        if ( v22 < v17 )
          *(&v60 + v22) = 0;
        else
          *(&v60 + v22) = *v23;
        --v22;
        --v23;
      }
      while ( v22 >= 0 );
      v24 = dword_6660E4 - 1;
      v25 = dword_6660E4 / 32;
      v65 = dword_6660E4 / 32;
      v26 = &v60 + dword_6660E4 / 32;
      v64 = 31 - dword_6660E4 % 32;
      if ( ((1 << (31 - dword_6660E4 % 32)) & *v26) != 0 )
      {
        for ( j = (~(-1 << (31 - dword_6660E4 % 32)) & *(&v60 + v25)) == 0; j; j = *(&v60 + v25) == 0 )
        {
          if ( ++v25 >= 3 )
            goto LABEL_52;
        }
        v28 = v24 / 32;
        v71 = 0;
        v29 = 1 << (31 - v24 % 32);
        v30 = &v60 + v24 / 32;
        v31 = *v30 + v29;
        if ( v31 < *v30 || v31 < v29 )
          v71 = 1;
        *v30 = v31;
        for ( k = v71; --v28 >= 0 && k; k = v35 )
        {
          v33 = &v60 + v28;
          v34 = *v33 + 1;
          v35 = 0;
          if ( v34 < *v33 || *v33 == -1 )
            v35 = 1;
          *v33 = v34;
        }
      }
LABEL_52:
      *v26 &= -1 << v64;
      if ( v65 + 1 < 3 )
        memset(&v60 + v65 + 1, 0, 4 * (3 - (v65 + 1)));
      v36 = (dword_6660E8 + 1) / 32;
      v37 = (dword_6660E8 + 1) % 32;
      v65 = 0;
      v72 = nullptr;
      v67 = 32 - v37;
      do
      {
        v38 = (int *)(&v60 + (_DWORD)v72);
        v39 = *v38;
        v64 = ~(-1 << v37) & *v38;
        v40 = v67;
        *v38 = v65 | (v39 >> v37);
        ++v72;
        v65 = v64 << v40;
      }
      while ( (int)v72 < 3 );
      v41 = 2;
      v42 = (unsigned int *)(&v62 - v36);
      do
      {
        if ( v41 < v36 )
          *(&v60 + v41) = 0;
        else
          *(&v60 + v41) = *v42;
        --v41;
        --v42;
      }
      while ( v41 >= 0 );
    }
    else
    {
      v60 = 0;
      v61 = 0;
      v62 = 0;
    }
    v5 = 0;
    result = 2;
    goto LABEL_79;
  }
  v5 = 0;
  v6 = 0;
  while ( !*(&v60 + v6) )
  {
    if ( ++v6 >= 3 )
    {
      result = 0;
      goto LABEL_79;
    }
  }
  v60 = 0;
  v61 = 0;
  v62 = 0;
  result = 2;
LABEL_79:
  v55 = v60 | (v63 != 0 ? 0x80000000 : 0) | (v5 << (31 - dword_6660E8));
  if ( dword_6660EC == 64 )
  {
    v56 = v61;
    a2[1] = v55;
    *a2 = v56;
  }
  else if ( dword_6660EC == 32 )
  {
    *a2 = v55;
  }
  return result;
}

