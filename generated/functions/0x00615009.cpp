// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00615009 __openfile
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) below means errno E plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated return follows only if handler returns. Cdecl(filename,modeString,share,FILE),noownNULLvalidation/lock.
// SnapshotdefaultFILEflags2021DD4,skipONLYASCIIspaces. Initialr setsFILEread1/oflag0;w setsFILEwrite2/oflag0x301;a FILEwrite2/oflag0x109; otherinitialcharinvalid(22)/NULL. Modifiers:
// plus clearsoflagbit0/sets2 andFILEflags=(old&~3)|0x80; b->oflag8000,t->4000; c->FILEcommit4000,n->clearcommit; D->oflag40,N->80,S->20,R->10,T->1000;spacesignored.
// Sharedone-useguards for c/n andR/S; b/tconflictguardC000; plus/D/Trepetitionguard. Crucial DUPLICATE/CONFLICT setsparseActive0 THENCONSUMES offendingcharacter;
// ifonlyspaces/NULremainit isACCEPTED withpriorflags,notautomaticallyinvalid. N repeatsunconditionally. Otherunknownmodifierinvalidimmediately. Comma setsencodingClause
// andstopsmodifierloop,thenrequiresdelegatedcase-sensitive3-bytecompareto"ccs",spaces,=,spaces; delegatedcase-insensitiveprefixmatches
// UTF-8(5)->oflag40000,UTF-16LE(8)->20000,UNICODE(7)->10000. Thereafteronlyspaces/NUL; noownbinary+ccsconflictcheck. Noncomma parse-stop alsoonlyspaces/NUL.
// Call_sopen_s(&fd,filename,oflag,share,0x180),nonzeroNULL. Successincrement20213AC,assignFILEflags
// snapshotwithmodifiers,cnt/ptr/base/tmpname0,fdoutput;bufsiz/charbufuntouched,returnoriginalFILE. No ownbufferalloc, closeonstatus0/badfd, filenamecopy, exceptioncleanup or
// headerreset onfailure.
_DWORD *__cdecl _openfile(char *FileName, _BYTE *OpenFlag, int ShareFlag, _DWORD *a4)
{
  char v5; // al
  int v7; // ecx
  const unsigned __int8 *v8; // esi
  signed __int8 v9; // al
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  const unsigned __int8 *i; // esi
  int v20; // ecx
  int FileHandle; // [esp+8h] [ebp-10h] BYREF
  int v22; // [esp+Ch] [ebp-Ch]
  int v23; // [esp+10h] [ebp-8h]
  unsigned int v24; // [esp+14h] [ebp-4h]
  unsigned int OpenFlaga; // [esp+24h] [ebp+Ch]

  v24 = unk_2021DD4;
  v22 = 0;
  v23 = 0;
  FileHandle = 0;
  while ( *OpenFlag == 32 )
    ++OpenFlag;
  v5 = *OpenFlag;
  if ( *OpenFlag == 97 )
  {
    OpenFlaga = 265;
  }
  else
  {
    if ( v5 == 114 )
    {
      v24 |= 1u;
      OpenFlaga = 0;
      goto LABEL_12;
    }
    if ( v5 != 119 )
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return nullptr;
    }
    OpenFlaga = 769;
  }
  v24 |= 2u;
LABEL_12:
  v7 = 1;
  v8 = OpenFlag + 1;
  v9 = *v8;
  if ( !*v8 )
    goto LABEL_66;
  while ( v7 )
  {
    if ( v9 > 83 )
    {
      v15 = v9 - 84;
      if ( !v15 )
      {
        if ( (OpenFlaga & 0x1000) == 0 )
        {
          OpenFlaga |= 0x1000u;
          goto LABEL_48;
        }
        goto LABEL_46;
      }
      v16 = v15 - 14;
      if ( v16 )
      {
        v17 = v16 - 1;
        if ( v17 )
        {
          v18 = v17 - 11;
          if ( v18 )
          {
            if ( v18 != 6 )
              goto LABEL_68;
            if ( (OpenFlaga & 0xC000) != 0 )
              goto LABEL_46;
            OpenFlaga |= 0x4000u;
          }
          else
          {
            if ( v22 )
              goto LABEL_46;
            v24 &= ~0x4000u;
            v22 = 1;
          }
        }
        else
        {
          if ( v22 )
            goto LABEL_46;
          v24 |= 0x4000u;
          v22 = 1;
        }
      }
      else
      {
        if ( (OpenFlaga & 0xC000) != 0 )
          goto LABEL_46;
        OpenFlaga |= 0x8000u;
      }
    }
    else if ( v9 == 83 )
    {
      if ( v23 )
        goto LABEL_46;
      OpenFlaga |= 0x20u;
      v23 = 1;
    }
    else
    {
      v10 = v9 - 32;
      if ( v10 )
      {
        v11 = v10 - 11;
        if ( v11 )
        {
          v12 = v11 - 1;
          if ( !v12 )
          {
            FileHandle = 1;
LABEL_46:
            v7 = 0;
            goto LABEL_48;
          }
          v13 = v12 - 24;
          if ( v13 )
          {
            v14 = v13 - 10;
            if ( v14 )
            {
              if ( v14 != 4 )
                goto LABEL_68;
              if ( v23 )
                goto LABEL_46;
              OpenFlaga |= 0x10u;
              v23 = 1;
            }
            else
            {
              OpenFlaga |= 0x80u;
            }
          }
          else
          {
            if ( (OpenFlaga & 0x40) != 0 )
              goto LABEL_46;
            OpenFlaga |= 0x40u;
          }
        }
        else
        {
          if ( (OpenFlaga & 2) != 0 )
            goto LABEL_46;
          OpenFlaga = OpenFlaga & 0xFFFFFFFC | 2;
          v24 = v24 & 0xFFFFFF7C | 0x80;
        }
      }
    }
LABEL_48:
    v9 = *++v8;
    if ( !*v8 )
      break;
  }
  if ( !FileHandle )
    goto LABEL_66;
  while ( *v8 == 32 )
    ++v8;
  if ( _mbsnbcmp(&Str1, v8, 3u) )
    goto LABEL_68;
  for ( i = v8 + 3; *i == 32; ++i )
    ;
  if ( *i != 61 )
    goto LABEL_68;
  do
    ++i;
  while ( *i == 32 );
  if ( !_mbsnbicmp(i, "UTF-8", 5u) )
  {
    v8 = i + 5;
    OpenFlaga |= 0x40000u;
    goto LABEL_66;
  }
  if ( !_mbsnbicmp(i, "UTF-16LE", 8u) )
  {
    v8 = i + 8;
    OpenFlaga |= 0x20000u;
    goto LABEL_66;
  }
  if ( _mbsnbicmp(i, "UNICODE", 7u) )
    goto LABEL_68;
  v8 = i + 7;
  OpenFlaga |= 0x10000u;
LABEL_66:
  while ( *v8 == 32 )
    ++v8;
  if ( *v8 )
  {
LABEL_68:
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return nullptr;
  }
  if ( _sopen_s(&FileHandle, FileName, OpenFlaga, ShareFlag, 384) )
    return nullptr;
  ++unk_20213AC;
  a4[3] = v24;
  v20 = FileHandle;
  a4[1] = 0;
  *a4 = 0;
  a4[2] = 0;
  a4[7] = 0;
  a4[4] = v20;
  return a4;
}

