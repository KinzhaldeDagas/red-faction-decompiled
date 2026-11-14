// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608C56 __fsopen
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(filename,mode,share). NULLfilename,NULLmode ORempty mode
// ->invalid/NULL. Getstream;NULL ->errno24/NULL,NO invalidhandler. Returned FILE is held for open attempt,armSEHfinallyunlock. Empty filename is checked ONLY AFTER getstream:errno22
// thenlocal_unwind4(cookieAddress,&registration,-2) invokesunlock,returnNULL WITHOUT invalidhandler. Nonempty filename:openfile(filename,mode,share,FILE),save
// pointer,normalfinallyunlock,return savedvalue. No own modegrammar/share validation, filename length guard, FILEallocationfree or OSopen itself; dynamicstream ownership delegated.
// Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths retain their
// separately described policy.
FILE *__cdecl _fsopen(const char *FileName, const char *Mode, int ShFlag)
{
  void *v3; // ebp
  FILE *v6; // eax
  FILE *v7; // [esp+10h] [ebp-1Ch]
  CPPEH_RECORD ms_exc; // [esp+14h] [ebp-18h] BYREF
  FILE *FileNamea; // [esp+34h] [ebp+8h]

  if ( !FileName || !Mode || !*Mode )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return nullptr;
  }
  v6 = (FILE *)_getstream();
  FileNamea = v6;
  if ( !v6 )
  {
    *_errno() = 24;
    return nullptr;
  }
  ms_exc.registration.TryLevel = 0;
  if ( !*FileName )
  {
    *_errno() = 22;
    _local_unwind4(v3, (const unsigned int *)&dword_664BD8, &ms_exc.registration.Next, 0xFFFFFFFE);
    return nullptr;
  }
  v7 = (FILE *)_openfile((char *)FileName, Mode, ShFlag, v6);
  _unlock_file(FileNamea);
  return v7;
}

