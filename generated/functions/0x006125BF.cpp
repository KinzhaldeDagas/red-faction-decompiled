// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006125BF __NMSG_WRITE
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(runtimeMessageID), void reporting routine.
// Ordered first-match scan23(code,messagePointer) records6653A8,stride8; miss returns without mode query/output. If firstset_error_mode(3)==1 ORsecondread==0 ANDappType664D60==1:
// GetStdHandle(-12),rejectNULL/-1; strlen(selectedmessage),oneWriteFile(handle,message,length,&written,NULL),IGNORE BOOL/short-write,return. Otherroute: ID252 suppressed,others use
// SHARED globalbuffer2021858 capacity0x314. strcpy_s prefix Runtime Error!/Program:, Watson(5zeroargs) onanycopy/appenderror; programname starts2021871 (buffer+25),forceNUL at2021975
// (program+260),GetModuleFileNameA(NULL,program,260). API0 copies fallback withcapacity0x2FB. Ifstrlen(program)+1>60, strncpy_s(program+strlen(program)-59,2021B6C-target,"...",3):
// writesellipsis ANDNUL THERE; no memmove or pointer shift to expose last59characters, so do not replace with conventional suffix truncation. Append twoNL andselectedmessage via
// strcat_s(buffer,788,...); lazy messagebox dispatcher(buffer,title Microsoft Visual C++ Runtime Library,0x12010),ignore result. No ownexit, retry, synchronization or automatic
// buffer allocation; mode queried twice onfirstnot1 path. All23 tablepairs/literalmessagebytes independently matched originalPE.
void __cdecl _NMSG_WRITE(int a1)
{
  unsigned int v1; // edi
  size_t v2; // eax
  HANDLE StdHandle; // eax
  void *v4; // ebx
  size_t v5; // eax
  DWORD NumberOfBytesWritten; // [esp+Ch] [ebp-8h] BYREF
  unsigned int v7; // [esp+10h] [ebp-4h]

  v1 = 0;
  v7 = 0;
  do
  {
    if ( a1 == dword_6653A8[2 * v1] )
      break;
    v7 = ++v1;
  }
  while ( v1 < 0x17 );
  if ( v1 < 0x17 )
  {
    if ( _set_error_mode(3) == 1 || !_set_error_mode(3) && dword_664D60 == 1 )
    {
      StdHandle = GetStdHandle(0xFFFFFFF4);
      v4 = StdHandle;
      if ( StdHandle && StdHandle != (HANDLE)-1 )
      {
        v5 = strlen((&off_6653AC)[2 * v1]);
        WriteFile(v4, (&off_6653AC)[2 * v1], v5, &NumberOfBytesWritten, nullptr);
      }
    }
    else if ( a1 != 252 )
    {
      if ( strcpy_s(unk_2021858, 0x314u, "Runtime Error!\n\nProgram: ") )
        _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
      unk_2021975 = 0;
      if ( !GetModuleFileNameA(nullptr, MEMORY[0x2021871], 0x104u)
        && strcpy_s(MEMORY[0x2021871], 0x2FBu, "<program name unknown>") )
      {
        _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
      }
      if ( strlen(MEMORY[0x2021871]) + 1 > 0x3C )
      {
        v2 = strlen(MEMORY[0x2021871]);
        if ( strncpy_s(&MEMORY[0x2021871][v2 - 59], &unk_2021B6C - (_UNKNOWN *)&MEMORY[0x2021871][v2 - 59], "...", 3u) )
          _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
      }
      if ( strcat_s(unk_2021858, 0x314u, "\n\n") )
        _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
      if ( strcat_s(unk_2021858, 0x314u, (&off_6653AC)[2 * v7]) )
        _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
      crt_message_box_a_lazy_dispatch((int)unk_2021858, (int)"Microsoft Visual C++ Runtime Library", 73744);
    }
  }
}

