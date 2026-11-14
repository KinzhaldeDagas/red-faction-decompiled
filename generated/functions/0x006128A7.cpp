// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006128A7 ?setSBCS@@YAXPAUthreadmbcinfostruct@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Multibyte record layout:
// refcountLONG+0,codepageDWORD+4,multibyteFlagDWORD+8,LCIDDWORD+12,sixWORDdata+16..27,classBYTE[257]+28 (character c at+29+c),caseMapBYTE[256]+285,totalallocation544
// with3trailingpaddingbytes. Internal EAX=record pointer,void, no NULLguard/lock. memset(record+28,0,257),clearDWORD+4/+8/+12 andsixWORDs+16..27. Copy
// EXACT257classbytesfromfixeddefaultrecord665468+28 and256casemapbytesfrom665468+285 using fixedsource-minus-destination offset. Refcount+0 andpadding541..543 untouched. No dynamic
// OSquery, ownershipchange or casefoldcomputation. No aliasguard: passingfixeddefaultobjectitself zeroesclasssourcebeforecopy, so doesnot restore its originalclassbytes.
void __usercall setSBCS(_DWORD *a1@<eax>)
{
  _BYTE *v2; // eax
  int v3; // ecx
  int v4; // edi
  _BYTE *v5; // eax
  int v6; // esi

  memset(a1 + 7, 0, 0x101u);
  a1[1] = 0;
  a1[2] = 0;
  a1[3] = 0;
  a1[4] = 0;
  a1[5] = 0;
  a1[6] = 0;
  v2 = a1 + 7;
  v3 = &unk_665468 - (_UNKNOWN *)a1;
  v4 = 257;
  do
  {
    *v2 = v2[v3];
    ++v2;
    --v4;
  }
  while ( v4 );
  v5 = (char *)a1 + 285;
  v6 = 256;
  do
  {
    *v5 = v5[v3];
    ++v5;
    --v6;
  }
  while ( v6 );
}

