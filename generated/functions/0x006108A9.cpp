// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006108A9 __output_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(FILE*,const format*,optional
// localeInfo*,byteCursorToVarargs), int count/error; format/cursor types corrected. LocaleUpdate BEFORE validation, conditional PTD+112 mask2 cleanup and cookie check on normal
// returns; no SEH/finally. Require FILE nonNULL. FILE flag40 bypasses fd checks; others fileno, fd-1/-2 use dummy665C30, other fd uses global2021E40[fd SAR5]+64*(fd&31), NO own
// fd-range guard. Require descriptor BYTE+36 low7zero AND highbit0, then format nonNULL. Failure errno22,invalid_parameter5zeros,-1. No vararg NULL check,own FILE lock,NUL
// append,errno reset,count/width overflow guard or partial-output rollback. Count0 initially; count-only FILE behavior and errno42 '?' substitution belong to reviewed writer helpers.
// Outer loop checks signed count<0 only at next iteration. Original-PE89-byte joint table64BB18: class=(table[byte-32]&15) for unsigned byte32..120,else0; nextState=SIGNED
// table[class*8+state] SAR4. Eight dispatch entries611421 verified. Classes ordinary0,%1,dot2,star3,zero4,digits1..9 class5,space/#/+/- class6,F/I/L/N/h/l/w class7,conversion
// A/C/E/G/S/X/Z/a/c/d/e/f/g/i/n/o/p/s/u/x class8. States literal0,percent reset1,flags2,width3,dot4,precision5,size6,type7. NUL ends WITHOUT final-state validation:
// trailing%/incomplete widths/ordinary size modifiers return prior count silently. Unknown specifier becomes literal byte, discarding prior%/modifiers; %% emits%. Literal lead byte
// is written BEFORE reading trail; trailNUL ->EINVAL after partial output, otherwise emit trail without validating it. New% resets flags,width,prefix
// length,uppercase,wide,suppression; precision=-1. Bits plus1,space2,left4,zero8,alternate80h. Width digits wrap32; star consumes DWORD,negative sets left/NEG32 (INT_MIN unchanged).
// Dot sets precision0; precision digits wrap32; star negative ->-1. h sets20h (repeated h still16-bit),l10h,ll1000h and consumes second l,w800h. F/L/N ignored size modifiers,
// uppercase F is NOT float conversion. I64 sets8000h/consumes64; I32 clears ONLY8000h (not ll1000h); bare I before d/i/o/u/x/X means native32; other lookahead forces literal I. No
// modifier-combination validation. Integers d/i signed40h,u decimal,o octal,x/X hex. I64/ll fetch8 bytes; others one DWORD, h selects low16 sign/zero extension. Signed negative uses
// unsigned64 two's-complement magnitude/negative flag100h; force highDWORD0 unless I64/ll. Missing/negative precision ->1; explicit>=0 clears zero pad and clamps512. Generate
// backwards in512-byte scratch with aulldvrm quotient EDX:EAX,remainder EBX:ECX, until magnitude0 AND signed precision<=0. Hex digits add39 lowercase/7 uppercase aboveASCII9. Zero
// magnitude suppresses hex prefix; # nonzero hex ->0x/0X; #octal ensures leading0 including zero precision/value. p forces min precision8,uppercase hex; same fetch flags (I64/ll
// still8 bytes), no default0x; #adds0X only nonzero. Plus/space apply only signed40h. Floating a/A/e/E/f/g/G ALWAYS consumes raw double8. A/E/G lowercased with uppercase flag1.
// Default precision6,g0->1,positive max512. Above163 try malloc_crt(precision+349); failure silently reduces precision163/keeps local512-byte scratch (allocator errno can persist).
// Decode LIVE665078, indirect7-slot cdecl(binary64copy*,buffer,capacity,format,precision,uppercase,selectedLocaleInfo*); IGNORE returned status, no decodedNULL/output check. # with
// precision0 decodes/calls LIVE665084 decimal-point helper; g without# decodes/calls LIVE665080 crop helper. Do not assume fixed callback from raw PE values. Strip leading minus into
// sign prefix; strlen body. Free dynamic buffer after field even if count negative; escaping delegate can bypass free/locale cleanup. c/C fetch DWORD; narrow lowBYTE
// includingNUL,length1. C defaults wide absent h/l/w; wide selected by l/w. Wide CHAR uses NON-locale wctomb_s(count*,scratch,512,lowWORD), therefore NULL/current locale rather than
// supplied formatter locale. Failure suppresses WHOLE field and continues without own count=-1. s/S fetch pointer; S defaults wide absent h/l/w. Precision-1 ->INT_MAX units;
// otherwise raw decrementing precision (other negatives from decimal overflow not normalized). Narrow scans bytes,wide scans16-bit units. NULL uses LIVE665104/665108, original PE
// pointers to narrow/wide '(null)'. Z record uses buffer+4,signed WORD length0,ignores maxLength+2 and precision. wZ divides signed length by2 toward zero; lZ alone stays narrow.
// NULL record/buffer uses narrow replacement/strlen even for wZ. No pointer/length validation; negative counted lengths remain unvalidated. Emission sign priority minus,plus,space
// when signed40h; padding=width-bodyLength-prefixLength modulo32. Leading spaces iff neither left norzero,then prefix,then zeros iffzero&&!left,then body,then trailing spaces iffleft
// AND count>=0. Wide body positive length converts EACH16-bit unit through NON-locale wctomb_s(count*,local6bytes,6,WCh); padding measured in code units, writer count in converted
// BYTES. Conversion error or zero bytes ->count=-1; no own count check between successful units. Other bodies use raw write_string signed length, including embedded NUL;
// count-only/negative-length/error replacement behavior delegated. No core termination. n fetches pointer BEFORE get_printf_count_output. Getter must return nonzero (token equals
// securityCookie OR1), otherwise EINVAL/-1, prior output retained/no destination write. Enabled h stores low16 count; ALL other modifiers store DWORD, I64/ll do NOT store8. No
// destinationNULL/range guard. Suppress field output,continue; cursor changes local only.
int __cdecl _output_l(FILE *Stream, const char *a2, struct localeinfo_struct *a3, char *a4)
{
  const char *v4; // ebx
  char *v5; // edi
  int v7; // eax
  _BYTE *v8; // ecx
  char *v9; // eax
  int v10; // ecx
  char v11; // dl
  const char *v12; // ebx
  int v13; // eax
  char v14; // al
  bool v15; // zf
  int v16; // eax
  char *v17; // ebx
  int v18; // ecx
  char *v19; // edi
  char *v20; // eax
  char *v21; // edi
  __int16 *v22; // eax
  char *v23; // ecx
  int v24; // eax
  _WORD *v25; // esi
  __int64 v26; // rax
  char *v27; // edi
  int v28; // esi
  void *v29; // eax
  int v30; // eax
  char *v31; // edi
  void (__cdecl *v32)(_DWORD *, char *, int, int, int, int, __crt_locale_pointers *); // eax
  int v33; // edi
  void (__cdecl *v34)(char *, __crt_locale_pointers *); // eax
  void (__cdecl *v35)(char *, __crt_locale_pointers *); // eax
  unsigned int v36; // ebx
  unsigned int v37; // edi
  char *j; // esi
  int v39; // eax
  unsigned __int64 v40; // rcx
  int v41; // ecx
  char *v42; // eax
  char *v43; // esi
  char *i; // eax
  int v45; // ebx
  FILE *v46; // edi
  wchar_t *v47; // esi
  wchar_t v48; // ax
  char v49; // al
  int v50; // [esp-14h] [ebp-298h]
  int v51; // [esp-10h] [ebp-294h]
  unsigned __int64 v52; // [esp-10h] [ebp-294h]
  int v53; // [esp-Ch] [ebp-290h]
  int v54; // [esp-8h] [ebp-28Ch]
  _DWORD v55[2]; // [esp+Ch] [ebp-278h] BYREF
  int v56; // [esp+14h] [ebp-270h]
  int v57; // [esp+18h] [ebp-26Ch]
  int v58; // [esp+1Ch] [ebp-268h] BYREF
  int v59; // [esp+24h] [ebp-260h]
  __crt_locale_pointers Locale; // [esp+28h] [ebp-25Ch] BYREF
  int v61; // [esp+30h] [ebp-254h]
  char v62; // [esp+34h] [ebp-250h]
  FILE *File; // [esp+38h] [ebp-24Ch]
  int v64; // [esp+3Ch] [ebp-248h]
  void *Block; // [esp+40h] [ebp-244h]
  int v66; // [esp+44h] [ebp-240h]
  const char *v67; // [esp+48h] [ebp-23Ch]
  int v68; // [esp+4Ch] [ebp-238h]
  int v69; // [esp+50h] [ebp-234h]
  int v70; // [esp+54h] [ebp-230h]
  _BYTE v71[4]; // [esp+58h] [ebp-22Ch] BYREF
  int v72; // [esp+5Ch] [ebp-228h] BYREF
  char *v73; // [esp+60h] [ebp-224h]
  int SizeConverted; // [esp+64h] [ebp-220h] BYREF
  char *v75; // [esp+68h] [ebp-21Ch]
  int v76; // [esp+6Ch] [ebp-218h]
  char v77; // [esp+73h] [ebp-211h]
  int v78; // [esp+74h] [ebp-210h]
  char MbCh[511]; // [esp+78h] [ebp-20Ch] BYREF
  char v80; // [esp+277h] [ebp-Dh] BYREF
  char v81[8]; // [esp+278h] [ebp-Ch] BYREF

  v4 = a2;
  v5 = a4;
  File = Stream;
  v73 = a4;
  v64 = 0;
  v78 = 0;
  v69 = 0;
  v76 = 0;
  v70 = 0;
  v66 = 0;
  v68 = 0;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Locale, a3);
  if ( Stream
    && ((Stream->_flag & 0x40) != 0
     || ((v7 = _fileno(Stream), v7 == -1) || v7 == -2
       ? (v8 = &unk_665C30)
       : (v8 = (_BYTE *)(unk_2021E40[v7 >> 5] + ((v7 & 0x1F) << 6))),
         (v8[36] & 0x7F) == 0
      && (v7 == -1 || v7 == -2 ? (v9 = (char *)&unk_665C30) : (v9 = (char *)(unk_2021E40[v7 >> 5] + ((v7 & 0x1F) << 6))),
          v9[36] >= 0)))
    && (v10 = 0, a2) )
  {
    v11 = *a2;
    v72 = 0;
    SizeConverted = 0;
    Block = nullptr;
    v77 = v11;
    if ( v11 )
    {
      while ( 1 )
      {
        v12 = v4 + 1;
        v67 = v12;
        if ( v72 < 0 )
          break;
        if ( (unsigned __int8)(v11 - 32) > 0x58u )
          v13 = 0;
        else
          v13 = *((_BYTE *)&off_64BAF8 + v11) & 0xF;
        v57 = byte_64BB18[8 * v13 + v10] >> 4;
        switch ( v57 )
        {
          case 0:
            goto $NORMAL_STATE$28981;
          case 1:
            v76 = -1;
            v56 = 0;
            v66 = 0;
            v69 = 0;
            v70 = 0;
            v78 = 0;
            v68 = 0;
            goto LABEL_218;
          case 2:
            switch ( v11 )
            {
              case ' ':
                v78 |= 2u;
                break;
              case '#':
                v78 |= 0x80u;
                break;
              case '+':
                v78 |= 1u;
                break;
              case '-':
                v78 |= 4u;
                break;
              case '0':
                v78 |= 8u;
                break;
            }
            goto LABEL_218;
          case 3:
            if ( v11 == 42 )
            {
              v73 = v5 + 4;
              v69 = *(_DWORD *)v5;
              if ( v69 < 0 )
              {
                v78 |= 4u;
                v69 = -v69;
              }
            }
            else
            {
              v69 = 10 * v69 + v11 - 48;
            }
            goto LABEL_218;
          case 4:
            v76 = 0;
            goto LABEL_218;
          case 5:
            if ( v11 == 42 )
            {
              v73 = v5 + 4;
              v76 = *(_DWORD *)v5;
              if ( v76 < 0 )
                v76 = -1;
            }
            else
            {
              v76 = 10 * v76 + v11 - 48;
            }
            goto LABEL_218;
          case 6:
            switch ( v11 )
            {
              case 'I':
                v14 = *v12;
                if ( *v12 == 54 && v12[1] == 52 )
                {
                  v78 |= 0x8000u;
                  v67 = v12 + 2;
                }
                else if ( v14 == 51 && v12[1] == 50 )
                {
                  v78 &= ~0x8000u;
                  v67 = v12 + 2;
                }
                else if ( v14 != 100 && v14 != 105 && v14 != 111 && v14 != 117 && v14 != 120 && v14 != 88 )
                {
                  v57 = 0;
$NORMAL_STATE$28981:
                  v68 = 0;
                  v16 = _isleadbyte_l((unsigned __int8)v11, &Locale);
                  v15 = v16 == 0;
                  LOBYTE(v16) = v77;
                  if ( !v15 )
                  {
                    v16 = write_char(File, v16, &v72);
                    LOBYTE(v16) = *v12;
                    v67 = v12 + 1;
                    if ( !(_BYTE)v16 )
                      goto LABEL_2;
                  }
                  write_char(File, v16, &v72);
                }
                break;
              case 'h':
                v78 |= 0x20u;
                break;
              case 'l':
                if ( *v12 == 108 )
                {
                  v78 |= 0x1000u;
                  v67 = v12 + 1;
                }
                else
                {
                  v78 |= 0x10u;
                }
                break;
              case 'w':
                v78 |= 0x800u;
                break;
            }
            goto LABEL_218;
          case 7:
            if ( v11 <= 100 )
            {
              if ( v11 == 100 )
              {
LABEL_118:
                v78 |= 0x40u;
                goto LABEL_119;
              }
              if ( v11 > 83 )
              {
                if ( v11 == 88 )
                  goto LABEL_140;
                if ( v11 == 90 )
                {
                  v22 = *(__int16 **)v5;
                  v73 = v5 + 4;
                  if ( v22 && (v23 = *((char **)v22 + 1)) != nullptr )
                  {
                    v24 = *v22;
                    v75 = v23;
                    if ( (v78 & 0x800) != 0 )
                    {
                      v24 /= 2;
                      v68 = 1;
                    }
                    else
                    {
                      v68 = 0;
                    }
                  }
                  else
                  {
                    v75 = off_665104;
                    v24 = strlen(off_665104);
                  }
                  goto LABEL_189;
                }
                if ( v11 != 97 )
                {
                  if ( v11 != 99 )
                    goto LABEL_190;
                  goto LABEL_93;
                }
              }
              else
              {
                if ( v11 == 83 )
                {
                  if ( (v78 & 0x830) == 0 )
                    v78 |= 0x800u;
                  goto LABEL_83;
                }
                if ( v11 != 65 )
                {
                  if ( v11 != 67 )
                  {
                    if ( v11 != 69 && v11 != 71 )
                      goto LABEL_190;
                    goto LABEL_76;
                  }
                  if ( (v78 & 0x830) == 0 )
                    v78 |= 0x800u;
LABEL_93:
                  v21 = v5 + 4;
                  v73 = v21;
                  if ( (v78 & 0x810) != 0 )
                  {
                    if ( wctomb_s(&SizeConverted, MbCh, 0x200u, *((_WORD *)v21 - 2)) )
                      v66 = 1;
                  }
                  else
                  {
                    MbCh[0] = *(v21 - 4);
                    SizeConverted = 1;
                  }
                  v75 = MbCh;
                  goto LABEL_190;
                }
LABEL_76:
                v11 += 32;
                v56 = 1;
                v77 = v11;
              }
LABEL_77:
              v78 |= 0x40u;
              v17 = MbCh;
              v75 = MbCh;
              v59 = 512;
              if ( v76 >= 0 )
              {
                if ( v76 )
                {
                  if ( v76 > 512 )
                    v76 = 512;
                  if ( v76 > 163 )
                  {
                    v28 = v76 + 349;
                    v29 = _malloc_crt(v76 + 349);
                    v11 = v77;
                    Block = v29;
                    if ( v29 )
                    {
                      v75 = (char *)v29;
                      v59 = v28;
                      v17 = (char *)v29;
                    }
                    else
                    {
                      v76 = 163;
                    }
                  }
                }
                else
                {
                  v76 = v11 == 103;
                }
              }
              else
              {
                v76 = 6;
              }
              v30 = *(_DWORD *)v5;
              v31 = v5 + 8;
              v55[0] = v30;
              v55[1] = *((_DWORD *)v31 - 1);
              v54 = v56;
              v53 = v76;
              v73 = v31;
              v51 = v11;
              v50 = v59;
              v32 = (void (__cdecl *)(_DWORD *, char *, int, int, int, int, __crt_locale_pointers *))_decode_pointer(off_665078[0]);
              v32(v55, v17, v50, v51, v53, v54, &Locale);
              v33 = v78 & 0x80;
              if ( (v78 & 0x80) != 0 && !v76 )
              {
                v34 = (void (__cdecl *)(char *, __crt_locale_pointers *))_decode_pointer(off_665084);
                v34(v17, &Locale);
              }
              if ( v77 == 103 && !v33 )
              {
                v35 = (void (__cdecl *)(char *, __crt_locale_pointers *))_decode_pointer(off_665080[0]);
                v35(v17, &Locale);
              }
              if ( *v17 == 45 )
              {
                v78 |= 0x100u;
                v75 = ++v17;
              }
              v24 = strlen(v17);
              goto LABEL_189;
            }
            if ( v11 > 112 )
            {
              if ( v11 != 115 )
              {
                if ( v11 != 117 )
                {
                  if ( v11 != 120 )
                    goto LABEL_190;
                  v64 = 39;
                  goto $COMMON_HEX$29142;
                }
LABEL_119:
                SizeConverted = 10;
                goto $COMMON_INT$29135;
              }
LABEL_83:
              v18 = v76;
              if ( v76 == -1 )
                v18 = 0x7FFFFFFF;
              v73 = v5 + 4;
              v19 = *(char **)v5;
              v75 = v19;
              if ( (v78 & 0x810) != 0 )
              {
                if ( !v19 )
                  v75 = (char *)off_665108;
                v20 = v75;
                v68 = 1;
                while ( v18 )
                {
                  --v18;
                  if ( !*(_WORD *)v20 )
                    break;
                  v20 += 2;
                }
                v24 = (v20 - v75) >> 1;
              }
              else
              {
                if ( !v19 )
                  v75 = off_665104;
                for ( i = v75; v18; ++i )
                {
                  --v18;
                  if ( !*i )
                    break;
                }
                v24 = i - v75;
              }
LABEL_189:
              SizeConverted = v24;
              goto LABEL_190;
            }
            if ( v11 == 112 )
            {
              v76 = 8;
LABEL_140:
              v64 = 7;
$COMMON_HEX$29142:
              SizeConverted = 16;
              if ( (v78 & 0x80u) != 0 )
              {
                v71[0] = 48;
                v71[1] = v64 + 81;
                v70 = 2;
              }
              goto $COMMON_INT$29135;
            }
            if ( v11 < 101 )
              goto LABEL_190;
            if ( v11 <= 103 )
              goto LABEL_77;
            if ( v11 == 105 )
              goto LABEL_118;
            if ( v11 != 110 )
            {
              if ( v11 != 111 )
                goto LABEL_190;
              SizeConverted = 8;
              if ( (v78 & 0x80u) != 0 )
                v78 |= 0x200u;
$COMMON_INT$29135:
              if ( (v78 & 0x8000) != 0 || (v78 & 0x1000) != 0 )
              {
                v26 = *(_QWORD *)v5;
                v27 = v5 + 8;
              }
              else
              {
                v27 = v5 + 4;
                if ( (v78 & 0x20) != 0 )
                {
                  v73 = v27;
                  if ( (v78 & 0x40) != 0 )
                    LODWORD(v26) = *((__int16 *)v27 - 2);
                  else
                    LODWORD(v26) = *((unsigned __int16 *)v27 - 2);
                  v26 = (int)v26;
LABEL_157:
                  if ( (v78 & 0x40) != 0 && v26 < 0 )
                  {
                    v26 = -v26;
                    v78 |= 0x100u;
                  }
                  v36 = HIDWORD(v26);
                  v37 = v26;
                  if ( (v78 & 0x9000) == 0 )
                    v36 = 0;
                  if ( v76 >= 0 )
                  {
                    v78 &= ~8u;
                    if ( v76 > 512 )
                      v76 = 512;
                  }
                  else
                  {
                    v76 = 1;
                  }
                  if ( !(v36 | (unsigned int)v26) )
                    v70 = 0;
                  for ( j = &v80; ; --j )
                  {
                    v39 = v76--;
                    if ( v39 <= 0 && !(v36 | v37) )
                      break;
                    v52 = __PAIR64__(v36, v37);
                    v40 = __PAIR64__(v36, v37) % SizeConverted;
                    v41 = v40 + 48;
                    v59 = HIDWORD(v40);
                    v36 = (v52 / SizeConverted) >> 32;
                    v37 = v52 / SizeConverted;
                    if ( v41 > 57 )
                      LOBYTE(v41) = v64 + v41;
                    *j = v41;
                  }
                  v42 = (char *)(&v80 - j);
                  v43 = j + 1;
                  SizeConverted = (int)v42;
                  v75 = v43;
                  if ( (v78 & 0x200) != 0 && (!v42 || *v43 != 48) )
                  {
                    *--v75 = 48;
                    v24 = (int)(v42 + 1);
                    goto LABEL_189;
                  }
LABEL_190:
                  if ( v66 )
                    goto LABEL_216;
                  if ( (v78 & 0x40) != 0 )
                  {
                    if ( (v78 & 0x100) != 0 )
                    {
                      v71[0] = 45;
                      goto LABEL_198;
                    }
                    if ( (v78 & 1) != 0 )
                    {
                      v71[0] = 43;
                      goto LABEL_198;
                    }
                    if ( (v78 & 2) != 0 )
                    {
                      v71[0] = 32;
LABEL_198:
                      v70 = 1;
                    }
                  }
                  v45 = v69 - SizeConverted - v70;
                  if ( (v78 & 0xC) == 0 )
                    write_multi_char(&v72, 32, v69 - SizeConverted - v70, File);
                  v46 = File;
                  write_string(&v72, v71, (int)File, v70);
                  if ( (v78 & 8) != 0 && (v78 & 4) == 0 )
                    write_multi_char(&v72, 48, v45, v46);
                  if ( v68 && SizeConverted > 0 )
                  {
                    v47 = (wchar_t *)v75;
                    v59 = SizeConverted;
                    while ( 1 )
                    {
                      v48 = *v47;
                      --v59;
                      ++v47;
                      if ( wctomb_s(&v58, v81, 6u, v48) || !v58 )
                        break;
                      write_string(&v72, v81, (int)v46, v58);
                      if ( !v59 )
                        goto LABEL_213;
                    }
                    v72 = -1;
                  }
                  else
                  {
                    write_string(&v72, v75, (int)v46, SizeConverted);
                  }
LABEL_213:
                  if ( v72 >= 0 && (v78 & 4) != 0 )
                    write_multi_char(&v72, 32, v45, v46);
                  goto LABEL_216;
                }
                LODWORD(v26) = *((_DWORD *)v27 - 1);
                if ( (v78 & 0x40) != 0 )
                  v26 = (int)v26;
                else
                  HIDWORD(v26) = 0;
              }
              v73 = v27;
              goto LABEL_157;
            }
            v25 = *(_WORD **)v5;
            v73 = v5 + 4;
            if ( !_get_printf_count_output() )
              goto LABEL_2;
            if ( (v78 & 0x20) != 0 )
              *v25 = v72;
            else
              *(_DWORD *)v25 = v72;
            v66 = 1;
LABEL_216:
            if ( Block )
            {
              free(Block);
              Block = nullptr;
            }
LABEL_218:
            v4 = v67;
            v49 = *v67;
            v77 = v49;
            if ( !v49 )
              goto LABEL_220;
            v10 = v57;
            v5 = v73;
            v11 = v49;
            break;
          default:
            goto LABEL_218;
        }
      }
    }
LABEL_220:
    if ( v62 )
      *(_DWORD *)(v61 + 112) &= ~2u;
    return v72;
  }
  else
  {
LABEL_2:
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v62 )
      *(_DWORD *)(v61 + 112) &= ~2u;
    return -1;
  }
}

