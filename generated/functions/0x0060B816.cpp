// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B816 __fullpath_helper
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(buffer,path,count,ownershipOut), pointer/NULL.
// Save errno, set errno0, call fullpath(buffer,path,count). First success restores saved errno and returns pointer WITHOUT writing ownershipOut. First failure with errno!=34
// returnsNULL retaining error. errno34 restores saved errno BEFORE retry fullpath(NULL,path,0), writes retry pointer EVEN NULL through ownershipOut, returns it without final errno
// restoration. No out-pointer NULL check, own allocation/free or retry beyond this one.
char *__cdecl _fullpath_helper(char *Buffer, char *Path, size_t BufferCount, char **a4)
{
  int v4; // esi
  char *v5; // edi
  int *v6; // eax
  char *result; // eax

  v4 = *_errno();
  *_errno() = 0;
  v5 = _fullpath(Buffer, Path, BufferCount);
  v6 = _errno();
  if ( v5 )
  {
    *v6 = v4;
    return v5;
  }
  else if ( *v6 == 34 )
  {
    *_errno() = v4;
    result = _fullpath(nullptr, Path, 0);
    *a4 = result;
  }
  else
  {
    return nullptr;
  }
  return result;
}

