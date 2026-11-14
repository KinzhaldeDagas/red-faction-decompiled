// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B154 __setjmp3
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): Runtime context saver has cdecl(buffer,unwindCount,...),not explicit EBX/EBP/EDI/ESI arguments. Stores current EBP,EBX,EDI,ESI at offsets0/4/8/12,entryESP16,returnEIP20,FS0 SEHhead24,signature56433230 at32,initial0at36. FS0==-1 stores tryLevel-1 at28. Otherwise count0 takes DWORD(SEHhead+12);count1 stores first variadic pointer at36 and takes DWORD(thatPointer+12);other counts store second variadicDWORD at28 and copy min(UNSIGNED(count-2),6) additionalDWORDs to40..63. Uses REP MOVSD without clearingDF;preserves ESI/EDI around copy. ReturnsEAX0 on ordinary path;console calls buffer180A3C0,count0 and parser longjmp restores context for nonzero resumption. Register stores capture execution context;they
// do not require callers to supply register parameters. No pointer/count/buffer-size validation.
int _setjmp3(void *buffer, int unwind_count, ...)
{
  int v2; // ebx
  int v3; // ebp
  int v4; // edi
  int v5; // esi
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  unsigned int v7; // ecx
  _UNKNOWN *retaddr; // [esp+0h] [ebp+0h] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v10; // [esp+Ch] [ebp+Ch]
  int v11; // [esp+10h] [ebp+10h]
  va_list va; // [esp+14h] [ebp+14h] BYREF

  va_start(va, unwind_count);
  v10 = va_arg(va, struct _EXCEPTION_REGISTRATION_RECORD *);
  v11 = va_arg(va, _DWORD);
  *(_DWORD *)buffer = v3;
  *((_DWORD *)buffer + 1) = v2;
  *((_DWORD *)buffer + 2) = v4;
  *((_DWORD *)buffer + 3) = v5;
  *((_DWORD *)buffer + 4) = &retaddr;
  *((_DWORD *)buffer + 5) = retaddr;
  *((_DWORD *)buffer + 8) = 1447244336;
  *((_DWORD *)buffer + 9) = 0;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  *((_DWORD *)buffer + 6) = ExceptionList;
  if ( ExceptionList == (struct _EXCEPTION_REGISTRATION_RECORD *)-1 )
  {
    *((_DWORD *)buffer + 7) = -1;
  }
  else if ( unwind_count && (ExceptionList = v10, *((_DWORD *)buffer + 9) = v10, unwind_count != 1) )
  {
    *((_DWORD *)buffer + 7) = v11;
    v7 = unwind_count - 2;
    if ( unwind_count != 2 )
    {
      if ( v7 > 6 )
        v7 = 6;
      qmemcpy((char *)buffer + 40, va, 4 * v7);
    }
  }
  else
  {
    *((_DWORD *)buffer + 7) = ExceptionList[1].Handler;
  }
  return 0;
}

