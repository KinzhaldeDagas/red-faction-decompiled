// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C25D __strlwr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. Cdecl(buffer),returnsoriginalbuffer/NULL.
// Ifglobal2021B8C!=0,callstrlwr_s_l(buffer,UINT_MAX,NULL),IGNOREstatus,returnoriginalbufferEVENformat/mapfailure. Ifglobal0,NULLbuffer
// invalid22/NULL;otherwiseinplaceASCIIA..Z->a..z,returninput. No owncapacity,allocation,rollbackorlocalecontextonASCIIpath.
char *__cdecl _strlwr(char *String)
{
  char *result; // eax
  char *i; // edx
  char v3; // cl

  if ( unk_2021B8C )
  {
    _strlwr_s_l(String, 0xFFFFFFFF, nullptr);
    return String;
  }
  else
  {
    result = String;
    if ( String )
    {
      for ( i = String; *i; ++i )
      {
        v3 = *i;
        if ( *i >= 65 && v3 <= 90 )
          *i = v3 + 32;
      }
    }
    else
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return nullptr;
    }
  }
  return result;
}

