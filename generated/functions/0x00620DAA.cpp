// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00620DAA _$I10_OUTPUT
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl ABI24 caller-popped bytes: raw significand64
// in first8 stack bytes, sign/exponentWORD in next4-byte slot (upper2 padding ignored), int requestedDigits, LOW BYTE flags, output*. Copy exactly10 input bytes locally. Output
// format {signed WORD decimalPoint at0,char sign at2 ('-' or SPACE),BYTE digitCount at3,char digits[22] at4}; no output NULL/capacity validation, no locale, own errno assignment or
// x87 arithmetic; cookie checked on normal return. Zero exponent AND significand0 -> decimalPoint0,count1,digits '0', preserve sign, return1. Exponent7FFF -> decimalPoint1, return0
// special string: exact significand8000000000000000 ->'1#INF'/count5; other significands with bit62 CLEAR ->'1#SNAN'/6; exact NEGATIVE C000000000000000 ->'1#IND'/5; remaining
// ->'1#QNAN'/6. Sign remains input sign; secure copy hardcodes capacity22, failure Watson5zeros. No FP signaling/quieting instruction for SNAN. Finite path builds internal12-byte
// value {80-bit significand at0..9,sign/exponentWORD at10}: input significand shifted LEFT16 with low guardWORD0, sign cleared. Let E=unsigned input exponent, H=highDWORD of input
// significand. Estimated decimal exponent k=SIGNED lowWORD of SAR32(19728*E+77*((E>>8)+2*(H>>24))-134312F4h,16). Select table6660F8 for k<0 (positive powers),666258 for k>0 (negative
// powers), no table multiplication if k0. Consume abs(k) in BASE8, low digit first; for nonzero digit d in group j, entry=selectedBase+84*j+12*(d-1). Original-PE-matching reviewed
// four7-entry groups encode 10^(+/-d*8^j). BEFORE multiplication, if entry lowWORD>=8000, COPY12 bytes locally and DECREMENT ONLY DWORD+2 (native bias correction). Exact-rational
// verification of all56 entries AFTER this correction gives relative error<2^-70 against expected power; raw table bytes are not interpreted as already unbiased. No index/domain
// bound for larger exponents. Each selected multiplication is integer fixed precision: clear96-bit product scratch; triangular5x5 unsigned16-bit convolution over significand limbs
// (15 products), explicit DWORD carry plus adjacent WORD increment; exponent sum in low16 bits, sign XOR. Exponent input>=7FFF or sum>BFFD -> signed extended infinity; sum<=3FBF ->
// zero. Zero-exponent operands increment exponent sum, with explicit all-mantissa-zero shortcuts. Subtract3FFE from exponent, normalize96-bit product left until top bit set or signed
// exponent<=0. Underflow shifts right by lowWORD negative exponent magnitude, sticky-OR lowbit if any bit lost. Round guard16 nearest-even using guard>8000 OR low17==18000; propagate
// carry through product DWORD+2,+6,WORD+10, increment exponent on top carry. Retain product bits16..95 as80-bit significand; exponent>=7FFF -> infinity. This is the exact native
// selected-limb algorithm, not an assertion of unlimited-precision multiplication. After scaling, if internal exponent>=3FFF, increment k and repeat same multiplier pipeline with
// local12-byte truncated 0.1 constant CCCCCCCCCCCCCCCCCCCCFB3F (raw bytes as stored), WITHOUT table-entry bias-decrement step for that local constant. Store lowWORD k as
// decimalPoint. If flags mask1, requestedDigits += SIGNED current k (32-bit arithmetic); result<=0 -> canonical signed zero/return1. Clamp requests>21 to21; DEFAULT mode has no
// lower-bound validation, negative requests can skip generation and read existing output-header bytes. For valid positive request: convert internal value to96-bit fixed fraction by
// clearing exponent, left-shift8, then right-shift by LOW8(-[oldExponent-3FFE]) iff oldExponent-3FFE<0. Generate requested+1 digits by96-bit multiply10, emit highBYTE+ASCII0 and
// clear that topBYTE each iteration. Extra digit>=ASCII5 -> round backward over9s; full carry increments decimalPoint and leaves leading1. Otherwise trim retained trailing0s.
// All-zero retained digits -> canonical signed zero. Publish BYTE count from low8 pointer difference (sign-extended for NUL address), NUL at output+4+count, return1. Finite status1
// versus special0 is classification, not errno-style success/failure. Does not emit decimal separator/exponent suffix or validate normalized input/precision/domain.
int __cdecl _I10_OUTPUT(unsigned __int64 a1, unsigned __int16 a2, int a3, unsigned __int8 a4, _BYTE *a5)
{
  __int16 v5; // cx
  unsigned __int16 v6; // dx
  __int64 v7; // rdi
  errno_t v9; // eax
  errno_t v10; // eax
  __int16 v11; // ax
  int v12; // ebx
  int v13; // ecx
  char *v14; // eax
  int *v15; // esi
  __int16 v16; // dx
  unsigned __int16 v17; // dx
  unsigned __int16 v18; // di
  _WORD *v19; // esi
  unsigned int v20; // edx
  unsigned int v21; // ecx
  unsigned int v22; // eax
  __int16 v23; // di
  unsigned int v24; // ecx
  unsigned int v25; // edx
  int v26; // eax
  unsigned int v27; // ecx
  int v28; // esi
  int v29; // ecx
  unsigned __int16 v30; // si
  int v31; // eax
  _WORD *v32; // edi
  unsigned __int16 *v33; // eax
  unsigned int v34; // ecx
  unsigned int v35; // edx
  unsigned int v36; // ebx
  __int16 v37; // si
  unsigned int v38; // ecx
  unsigned int v39; // edx
  int v40; // eax
  unsigned int v41; // ecx
  int v42; // edi
  int v43; // ecx
  int v44; // edi
  int v45; // esi
  unsigned int v46; // eax
  int v47; // ebx
  int v48; // eax
  bool v49; // zf
  int v50; // esi
  int v51; // eax
  int v52; // ebx
  int v53; // eax
  _BYTE *v54; // ebx
  unsigned int v55; // edx
  unsigned int v56; // edi
  unsigned int v57; // ecx
  int v58; // esi
  int v59; // ecx
  unsigned int v60; // esi
  unsigned int v61; // edi
  int v62; // edx
  unsigned int v63; // edx
  char *v64; // ebx
  char v65; // al
  char *v66; // ebx
  _BYTE *v67; // eax
  char v68; // bl
  __int16 v69; // [esp+10h] [ebp-70h]
  unsigned __int16 *v70; // [esp+14h] [ebp-6Ch]
  unsigned __int16 *v71; // [esp+18h] [ebp-68h]
  char *v72; // [esp+1Ch] [ebp-64h]
  int v73; // [esp+24h] [ebp-5Ch]
  __int16 v74; // [esp+24h] [ebp-5Ch]
  int v75; // [esp+28h] [ebp-58h]
  int v76; // [esp+28h] [ebp-58h]
  int v77; // [esp+2Ch] [ebp-54h]
  int v78; // [esp+2Ch] [ebp-54h]
  int v79; // [esp+30h] [ebp-50h]
  int v80; // [esp+30h] [ebp-50h]
  __int16 v81; // [esp+34h] [ebp-4Ch]
  int k; // [esp+34h] [ebp-4Ch]
  __int16 v83; // [esp+38h] [ebp-48h]
  int *v84; // [esp+38h] [ebp-48h]
  char *v85; // [esp+3Ch] [ebp-44h]
  int v86; // [esp+3Ch] [ebp-44h]
  int v87; // [esp+3Ch] [ebp-44h]
  unsigned int v88; // [esp+3Ch] [ebp-44h]
  int i; // [esp+40h] [ebp-40h]
  int j; // [esp+40h] [ebp-40h]
  char *v91; // [esp+40h] [ebp-40h]
  __int64 v92; // [esp+44h] [ebp-3Ch] BYREF
  int v93; // [esp+4Ch] [ebp-34h]
  int v94; // [esp+50h] [ebp-30h]
  int v95; // [esp+54h] [ebp-2Ch]
  int v96; // [esp+58h] [ebp-28h] BYREF
  _BYTE v97[12]; // [esp+60h] [ebp-20h] BYREF
  _BYTE v98[12]; // [esp+70h] [ebp-10h] BYREF

  *(_QWORD *)v98 = a1;
  *(_WORD *)&v98[8] = a2;
  v5 = a2 & 0x8000;
  v6 = a2 & 0x7FFF;
  v94 = -858993460;
  v95 = -858993460;
  v96 = 1073466572;
  v69 = a2 & 0x8000;
  if ( (a2 & 0x8000u) == 0 )
    a5[2] = 32;
  else
    a5[2] = 45;
  v7 = *(_QWORD *)v98;
  if ( !v6 && !*(_QWORD *)v98 )
  {
    *(_WORD *)a5 = 0;
    a5[2] = v5 != -32768 ? 32 : 45;
    a5[3] = 1;
    a5[4] = 48;
    a5[5] = 0;
    return 1;
  }
  if ( v6 == 0x7FFF )
  {
    *(_WORD *)a5 = 1;
    if ( v7 != 0x8000000000000000uLL && (v7 & 0x4000000000000000LL) == 0 )
    {
      v9 = strcpy_s(a5 + 4, 0x16u, "1#SNAN");
LABEL_22:
      if ( v9 )
        _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
      a5[3] = 6;
      return 0;
    }
    if ( v5 && HIDWORD(v7) == -1073741824 )
    {
      if ( !(_DWORD)v7 )
      {
        v10 = strcpy_s(a5 + 4, 0x16u, "1#IND");
LABEL_18:
        if ( v10 )
          _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
        a5[3] = 5;
        return 0;
      }
    }
    else if ( v7 == 0x8000000000000000uLL )
    {
      v10 = strcpy_s(a5 + 4, 0x16u, "1#INF");
      goto LABEL_18;
    }
    v9 = strcpy_s(a5 + 4, 0x16u, "1#QNAN");
    goto LABEL_22;
  }
  v11 = (77 * (HIBYTE(v6) + 2 * HIBYTE(*(_DWORD *)&v98[4])) + 19728 * (unsigned int)v6 - 323162868) >> 16;
  *(_WORD *)v97 = 0;
  v12 = -v11;
  v81 = v11;
  *(_WORD *)&v97[10] = a2 & 0x7FFF;
  *(_QWORD *)&v97[2] = *(_QWORD *)v98;
  v72 = (char *)&unk_6660F8 - 96;
  if ( v11 )
  {
    if ( v11 > 0 )
    {
      v12 = v11;
      v72 = (char *)&unk_666258 - 96;
    }
    while ( v12 )
    {
      v72 += 84;
      v13 = v12 & 7;
      v12 >>= 3;
      if ( v13 )
      {
        v14 = &v72[12 * v13];
        v85 = v14;
        if ( *(_WORD *)v14 >= 0x8000u )
        {
          v92 = *(_QWORD *)v14;
          v15 = (int *)(v14 + 8);
          v14 = (char *)&v92;
          v93 = *v15;
          --*(_DWORD *)((char *)&v92 + 2);
          v85 = (char *)&v92;
        }
        v16 = *((_WORD *)v14 + 5);
        v77 = 0;
        memset(v98, 0, sizeof(v98));
        v83 = (*(_WORD *)&v97[10] ^ v16) & 0x8000;
        v17 = v16 & 0x7FFF;
        v18 = v17 + (*(_WORD *)&v97[10] & 0x7FFF);
        if ( (*(_WORD *)&v97[10] & 0x7FFF) == 0x7FFF || v17 >= 0x7FFFu || v18 > 0xBFFDu )
        {
          *(_DWORD *)&v97[8] = v83 == 0 ? 2147450880 : -32768;
        }
        else
        {
          if ( v18 > 0x3FBFu )
          {
            if ( (*(_WORD *)&v97[10] & 0x7FFF) == 0 )
            {
              ++v18;
              if ( (*(_DWORD *)&v97[8] & 0x7FFFFFFF) == 0 && !*(_DWORD *)&v97[4] && !*(_DWORD *)v97 )
              {
                *(_WORD *)&v97[10] = 0;
                continue;
              }
            }
            if ( v17 || (++v18, (*((_DWORD *)v14 + 2) & 0x7FFFFFFF) != 0) || *((_DWORD *)v14 + 1) || *(_DWORD *)v14 )
            {
              v75 = 0;
              v19 = &v98[4];
              for ( i = 5; i > 0; --i )
              {
                v79 = i;
                v70 = (unsigned __int16 *)&v97[2 * v75];
                v71 = (unsigned __int16 *)(v14 + 8);
                do
                {
                  v20 = *((_DWORD *)v19 - 1);
                  v21 = *v71 * *v70;
                  v73 = 0;
                  v22 = v20 + v21;
                  if ( v20 + v21 < v20 || v22 < v21 )
                    v73 = 1;
                  *((_DWORD *)v19 - 1) = v22;
                  if ( v73 )
                    ++*v19;
                  ++v70;
                  --v71;
                  --v79;
                }
                while ( v79 > 0 );
                v14 = v85;
                ++v19;
                ++v75;
              }
              v23 = v18 - 16382;
              if ( v23 <= 0 )
                goto LABEL_170;
              do
              {
                if ( *(int *)&v98[8] < 0 )
                  break;
                v24 = *(_DWORD *)v98;
                *(_DWORD *)v98 *= 2;
                v25 = *(_DWORD *)&v98[4];
                *(_DWORD *)&v98[4] = (v24 >> 31) | (2 * *(_DWORD *)&v98[4]);
                --v23;
                *(_DWORD *)&v98[8] = (v25 >> 31) | (2 * *(_DWORD *)&v98[8]);
              }
              while ( v23 > 0 );
              if ( v23 <= 0 )
              {
LABEL_170:
                if ( --v23 < 0 )
                {
                  v26 = (unsigned __int16)-v23;
                  v23 = 0;
                  do
                  {
                    if ( (v98[0] & 1) != 0 )
                      ++v77;
                    v27 = *(_DWORD *)&v98[8];
                    *(_DWORD *)&v98[8] >>= 1;
                    v28 = __SPAIR64__(v27, *(unsigned int *)&v98[4]) >> 1;
                    v29 = *(__int64 *)v98 >> 1;
                    --v26;
                    *(_DWORD *)&v98[4] = v28;
                    *(_DWORD *)v98 = v29;
                  }
                  while ( v26 );
                  if ( v77 )
                    *(_WORD *)v98 |= 1u;
                }
              }
              if ( *(_WORD *)v98 > 0x8000u || (*(_DWORD *)v98 & 0x1FFFF) == 0x18000 )
              {
                if ( *(_DWORD *)&v98[2] == -1 )
                {
                  *(_DWORD *)&v98[2] = 0;
                  if ( *(_DWORD *)&v98[6] == -1 )
                  {
                    *(_DWORD *)&v98[6] = 0;
                    if ( *(_WORD *)&v98[10] == 0xFFFF )
                    {
                      *(_WORD *)&v98[10] = 0x8000;
                      ++v23;
                    }
                    else
                    {
                      ++*(_WORD *)&v98[10];
                    }
                  }
                  else
                  {
                    ++*(_DWORD *)&v98[6];
                  }
                }
                else
                {
                  ++*(_DWORD *)&v98[2];
                }
              }
              if ( (unsigned __int16)v23 < 0x7FFFu )
              {
                *(_WORD *)v97 = *(_WORD *)&v98[2];
                *(_DWORD *)&v97[2] = *(_DWORD *)&v98[4];
                *(_DWORD *)&v97[6] = *(_DWORD *)&v98[8];
                *(_WORD *)&v97[10] = v83 | v23;
              }
              else
              {
                *(_DWORD *)&v97[4] = 0;
                *(_DWORD *)v97 = 0;
                *(_DWORD *)&v97[8] = v83 == 0 ? 2147450880 : -32768;
              }
              continue;
            }
          }
          *(_DWORD *)&v97[8] = 0;
        }
        *(_DWORD *)&v97[4] = 0;
        *(_DWORD *)v97 = 0;
      }
    }
  }
  if ( *(_WORD *)&v97[10] >= 0x3FFFu )
  {
    ++v81;
    v80 = 0;
    memset(v98, 0, sizeof(v98));
    v74 = (*(_WORD *)&v97[10] ^ HIWORD(v96)) & 0x8000;
    v30 = (HIWORD(v96) & 0x7FFF) + (*(_WORD *)&v97[10] & 0x7FFF);
    if ( (*(_WORD *)&v97[10] & 0x7FFF) == 0x7FFF || (HIWORD(v96) & 0x7FFF) == 0x7FFF || v30 > 0xBFFDu )
    {
      *(_DWORD *)&v97[4] = 0;
      v31 = ((*(_WORD *)&v97[10] ^ HIWORD(v96)) & 0x8000u) == 0 ? 2147450880 : -32768;
      *(_DWORD *)v97 = 0;
    }
    else
    {
      if ( v30 > 0x3FBFu )
      {
        v31 = 0;
        if ( (*(_WORD *)&v97[10] & 0x7FFF) == 0 )
        {
          ++v30;
          if ( (*(_DWORD *)&v97[8] & 0x7FFFFFFF) == 0 && !*(_DWORD *)&v97[4] && !*(_DWORD *)v97 )
          {
            *(_WORD *)&v97[10] = 0;
            goto LABEL_132;
          }
        }
        if ( (v96 & 0x7FFF0000) != 0 || (++v30, (v96 & 0x7FFFFFFF) != 0) || v95 || v94 )
        {
          v76 = 0;
          v32 = &v98[4];
          for ( j = 5; j > 0; --j )
          {
            v78 = j;
            v84 = &v96;
            v33 = (unsigned __int16 *)&v97[2 * v76];
            do
            {
              v86 = 0;
              v34 = *v33 * *(unsigned __int16 *)v84;
              v35 = *((_DWORD *)v32 - 1);
              v36 = v35 + v34;
              if ( v35 + v34 < v35 || v36 < v34 )
                v86 = 1;
              *((_DWORD *)v32 - 1) = v36;
              if ( v86 )
                ++*v32;
              v84 = (int *)((char *)v84 - 2);
              ++v33;
              --v78;
            }
            while ( v78 > 0 );
            ++v32;
            ++v76;
          }
          v37 = v30 - 16382;
          if ( v37 <= 0 )
            goto LABEL_171;
          do
          {
            if ( *(int *)&v98[8] < 0 )
              break;
            v38 = *(_DWORD *)v98;
            *(_DWORD *)v98 *= 2;
            v39 = *(_DWORD *)&v98[4];
            *(_DWORD *)&v98[4] = (v38 >> 31) | (2 * *(_DWORD *)&v98[4]);
            --v37;
            *(_DWORD *)&v98[8] = (v39 >> 31) | (2 * *(_DWORD *)&v98[8]);
          }
          while ( v37 > 0 );
          if ( v37 <= 0 )
          {
LABEL_171:
            if ( --v37 < 0 )
            {
              v40 = (unsigned __int16)-v37;
              v37 = 0;
              do
              {
                if ( (v98[0] & 1) != 0 )
                  ++v80;
                v41 = *(_DWORD *)&v98[8];
                *(_DWORD *)&v98[8] >>= 1;
                v42 = __SPAIR64__(v41, *(unsigned int *)&v98[4]) >> 1;
                v43 = *(__int64 *)v98 >> 1;
                --v40;
                *(_DWORD *)&v98[4] = v42;
                *(_DWORD *)v98 = v43;
              }
              while ( v40 );
              if ( v80 )
                *(_WORD *)v98 |= 1u;
            }
          }
          if ( *(_WORD *)v98 > 0x8000u || (*(_DWORD *)v98 & 0x1FFFF) == 0x18000 )
          {
            if ( *(_DWORD *)&v98[2] == -1 )
            {
              *(_DWORD *)&v98[2] = 0;
              if ( *(_DWORD *)&v98[6] == -1 )
              {
                *(_DWORD *)&v98[6] = 0;
                if ( *(_WORD *)&v98[10] == 0xFFFF )
                {
                  *(_WORD *)&v98[10] = 0x8000;
                  ++v37;
                }
                else
                {
                  ++*(_WORD *)&v98[10];
                }
              }
              else
              {
                ++*(_DWORD *)&v98[6];
              }
            }
            else
            {
              ++*(_DWORD *)&v98[2];
            }
          }
          if ( (unsigned __int16)v37 < 0x7FFFu )
          {
            *(_WORD *)v97 = *(_WORD *)&v98[2];
            *(_DWORD *)&v97[2] = *(_DWORD *)&v98[4];
            *(_DWORD *)&v97[6] = *(_DWORD *)&v98[8];
            *(_WORD *)&v97[10] = v74 | v37;
          }
          else
          {
            *(_DWORD *)&v97[4] = 0;
            *(_DWORD *)v97 = 0;
            *(_DWORD *)&v97[8] = v74 == 0 ? 2147450880 : -32768;
          }
          goto LABEL_132;
        }
      }
      else
      {
        v31 = 0;
      }
      *(_DWORD *)&v97[4] = 0;
      *(_DWORD *)v97 = 0;
    }
    *(_DWORD *)&v97[8] = v31;
  }
LABEL_132:
  v44 = a3;
  *(_WORD *)a5 = v81;
  if ( (a4 & 1) != 0 )
  {
    v44 = v81 + a3;
    if ( v44 <= 0 )
    {
      *(_WORD *)a5 = 0;
      a5[3] = 1;
      a5[2] = v69 != -32768 ? 32 : 45;
      a5[4] = 48;
      a5[5] = 0;
      return 1;
    }
  }
  if ( v44 > 21 )
    v44 = 21;
  v45 = *(unsigned __int16 *)&v97[10] - 16382;
  *(_WORD *)&v97[10] = 0;
  v87 = 8;
  do
  {
    v46 = *(_DWORD *)v97;
    *(_DWORD *)v97 *= 2;
    v47 = (v46 >> 31) | (2 * *(_DWORD *)&v97[4]);
    v48 = *(__int64 *)&v97[4] >> 31;
    v49 = v87-- == 1;
    *(_DWORD *)&v97[4] = v47;
    *(_DWORD *)&v97[8] = v48;
  }
  while ( !v49 );
  if ( v45 < 0 )
  {
    v50 = (unsigned __int8)-(char)v45;
    if ( v50 )
    {
      do
      {
        v51 = *(_DWORD *)&v97[8];
        *(_DWORD *)&v97[8] >>= 1;
        v52 = (v51 << 31) | (*(_DWORD *)&v97[4] >> 1);
        v53 = *(__int64 *)v97 >> 1;
        --v50;
        *(_DWORD *)&v97[4] = v52;
        *(_DWORD *)v97 = v53;
      }
      while ( v50 > 0 );
    }
  }
  v54 = a5 + 4;
  v91 = a5 + 4;
  for ( k = v44 + 1; k > 0; v97[11] = 0 )
  {
    v55 = *(_DWORD *)v97;
    v92 = *(_QWORD *)v97;
    v93 = *(_DWORD *)&v97[8];
    *(_DWORD *)v97 *= 2;
    v56 = *(_DWORD *)v97;
    *(_DWORD *)v97 *= 2;
    v57 = (v55 >> 31) | (2 * *(_DWORD *)&v97[4]);
    v58 = 2 * v57;
    v59 = (v57 >> 31) | (2 * (*(__int64 *)&v97[4] >> 31));
    v60 = (v56 >> 31) | v58;
    v61 = v92 + *(_DWORD *)v97;
    if ( (unsigned int)(v92 + *(_DWORD *)v97) < *(_DWORD *)v97 || v61 < (unsigned int)v92 )
    {
      v62 = 0;
      if ( v60 + 1 < v60 || v60 == -1 )
        v62 = 1;
      ++v60;
      if ( v62 )
        ++v59;
    }
    v63 = HIDWORD(v92) + v60;
    v88 = HIDWORD(v92) + v60;
    if ( HIDWORD(v92) + v60 < v60 || v63 < HIDWORD(v92) )
      ++v59;
    *(_DWORD *)v97 = 2 * v61;
    *(_DWORD *)&v97[8] = (v63 >> 31) | (2 * (v93 + v59));
    *v54++ = v97[11] + 48;
    --k;
    *(_DWORD *)&v97[4] = (v61 >> 31) | (2 * v88);
  }
  v64 = v54 - 1;
  v65 = *v64;
  v66 = v64 - 1;
  if ( v65 >= 53 )
  {
    while ( v66 >= v91 && *v66 == 57 )
      *v66-- = 48;
    v67 = a5;
    if ( v66 < v91 )
    {
      ++v66;
      ++*(_WORD *)a5;
    }
    ++*v66;
  }
  else
  {
    while ( v66 >= v91 && *v66 == 48 )
      --v66;
    v67 = a5;
    if ( v66 < v91 )
    {
      *(_WORD *)a5 = 0;
      a5[3] = 1;
      a5[2] = v69 != -32768 ? 32 : 45;
      *v91 = 48;
      a5[5] = 0;
      return 1;
    }
  }
  v68 = (_BYTE)v66 - (_BYTE)v67 - 3;
  v67[3] = v68;
  v67[v68 + 4] = 0;
  return 1;
}

