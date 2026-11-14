// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CF93 _vscan_fn
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal vscan_fn accepts sourceCString inESI plus FOUR cdecl stackslots(callback,format,locale,vaList),returnintEAX. FIRST call strlen(source), BEFORE
// checking sourceNULL; a NULLsource can fault before intended errno22 path. Afterstrlen require source andformat nonNULL;invalid sets errno22/five-zero invalidhandler/return-1
// ifreturns. Build local FILE-like first16bytes: ptr=source,count=minUnsigned(strlen,INT_MAX),base=source,flags0x49;remaining reservedbytes notexplicitlyinitialized. Call
// suppliedcallback(&localStream,format,locale,vaList),ADD16,returnresult. No callbackNULLcheck,FILE lock,source copy/destinationbounds or locale snapshot; localstream does notescape
// exceptduringdelegate. Corrected pointer/count signature and ESI source reflect actualpublicsscanf adapter.
int __usercall vscan_fn@<eax>(
        const char *source@<esi>,
        int (__cdecl *scanner)(void *, const char *, void *, char *),
        const char *format,
        void *locale,
        char *arguments)
{
  size_t v5; // eax
  const char *v7; // [esp+0h] [ebp-28h]
  const char *v8; // [esp+8h] [ebp-20h] BYREF
  int v9; // [esp+Ch] [ebp-1Ch]
  const char *v10; // [esp+10h] [ebp-18h]
  int v11; // [esp+14h] [ebp-14h]

  v5 = strlen(v7);
  if ( source && format )
  {
    v11 = 73;
    v10 = source;
    v8 = source;
    v9 = 0x7FFFFFFF;
    if ( v5 <= 0x7FFFFFFF )
      v9 = v5;
    return scanner(&v8, format, locale, arguments);
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

